//==============================================================================
// UI/Widgets/PlayerBar/IPlayerBar.cpp
//==============================================================================

#include "IPlayerBar.h"
#include "../../../Services/PlaybackController.h"
#include "../../../Services/Metadata/MetadataReader.h"
#include <imgui.h>
#include <iostream>
#include <cmath>

namespace moosic
{

    //==========================================================================
    // Setup & Configuration
    //==========================================================================

    void IPlayerBar::SetRenderer(SDL_Renderer *renderer)
    {
        m_renderer = renderer;
        m_lightbox.ApplyTheme(m_theme.Lightbox);
        m_albumArtBox.ApplyTheme(m_theme.AlbumArtBox);
        m_visualizer.ApplyTheme(m_theme.Visualizer);
    }

    void IPlayerBar::SetPlaybackController(PlaybackController *controller)
    {
        m_playbackController = controller;
        if (m_playbackController)
        {
            m_data = &m_playbackController->GetPlayerBarData();
            SyncChildWidgets();
        }
    }

    void IPlayerBar::ApplyTheme(const PlayerBarTheme &theme)
    {
        m_theme = theme;
        m_lightbox.ApplyTheme(theme.Lightbox);
        m_albumArtBox.ApplyTheme(theme.AlbumArtBox);
        m_visualizer.ApplyTheme(theme.Visualizer);
    }

    //==========================================================================
    // Child Widget Sync
    //==========================================================================

    void IPlayerBar::SyncChildWidgets()
    {
        if (!m_data)
            return;
        m_visualizer.SetAudioStream(m_data->audioStream);
        m_visualizer.SetVolume(m_data->volume);
        m_visualizer.SetMode(m_data->visualizerMode == 0 ? VisualizerMode::Spectrum : VisualizerMode::Oscilloscope);
        m_lastVisualizerMode = m_data->visualizerMode;
    }

    //==========================================================================
    // Album Art Cache Management
    //==========================================================================

    void IPlayerBar::ClearAlbumArtCache()
    {
        DestroyAlbumArtTexture();
        m_albumArtBox.ClearTexture();
        m_lightbox.SetTexture(nullptr, 0, 0);
        m_artLoadAttempted = false;
    }

    void IPlayerBar::DestroyAlbumArtTexture()
    {
        if (m_albumArtTexture)
        {
            m_imageLoader.DestroyImGuiTexture(m_albumArtTexture);
            m_albumArtTexture = nullptr;
        }
        m_albumArtWidth = 0;
        m_albumArtHeight = 0;
        m_lastAlbumArtTrackId = 0;
    }

    //==========================================================================
    // Album Art Management
    //==========================================================================

    void IPlayerBar::LoadAlbumArtForCurrentTrack()
    {
        if (!m_data || !m_renderer || m_artLoadAttempted)
            return;

        if (!m_data->hasTrack)
        {
            m_albumArtBox.ClearTexture();
            m_lightbox.SetTexture(nullptr, 0, 0);
            m_artLoadAttempted = true;
            return;
        }

        if (m_lastAlbumArtTrackId == m_data->currentTrackId && m_albumArtTexture)
            return;

        LoadAlbumArtFromData();
    }

    void IPlayerBar::LoadAlbumArtFromData()
    {
        if (!m_data)
            return;

        DestroyAlbumArtTexture();
        m_albumArtBox.ClearTexture();

        const CachedAlbumArtData *cachedData = m_data->GetCurrentArt();

        std::vector<unsigned char> artData;

        if (cachedData && !cachedData->data.empty())
        {
            artData = cachedData->data;
        }
        else
        {
            const MusicTrack *track = m_playbackController->GetCurrentTrack();
            if (!track)
            {
                m_artLoadAttempted = true;
                return;
            }

            const auto &trackArt = track->GetAlbumArtData();
            if (!trackArt.empty())
            {
                artData = trackArt;
            }
            else
            {
                MetadataReader reader;
                MusicTrack refreshed = reader.ReadMetadataForSingleTrack(track->GetPath());
                if (refreshed.HasAlbumArt())
                    artData = refreshed.GetAlbumArtData();
            }

            if (!artData.empty())
                m_playbackController->CacheAlbumArt(m_data->currentTrackId, artData, 0, 0);
        }

        if (artData.empty())
        {
            m_artLoadAttempted = true;
            return;
        }

        ImageData image = m_imageLoader.LoadFromMemory(artData.data(), artData.size());
        if (image.data.empty())
        {
            m_artLoadAttempted = true;
            return;
        }

        int maxDim = 512;
        if (image.width > maxDim || image.height > maxDim)
        {
            float scale = (float)maxDim / (std::max)(image.width, image.height);
            image = m_imageLoader.Resize(image, (int)(image.width * scale), (int)(image.height * scale));
        }

        void *texture = m_imageLoader.CreateImGuiTexture(m_renderer, image);
        if (!texture)
        {
            m_artLoadAttempted = true;
            return;
        }

        m_albumArtTexture = texture;
        m_albumArtWidth = image.width;
        m_albumArtHeight = image.height;
        m_lastAlbumArtTrackId = m_data->currentTrackId;

        m_albumArtBox.SetTexture(texture, image.width, image.height);
        m_lightbox.SetTexture(texture, image.width, image.height);
        m_lightbox.SetInfo(m_data->title.c_str(), m_data->artist.c_str());
    }

    //==========================================================================
    // Classic 2000s Rendering Helpers
    //==========================================================================

    // ── Button Gloss Overlay ─────────────────────────────────────────────

    void IPlayerBar::DrawGlossOverlay(const ImVec2 &min, const ImVec2 &max, float rounding)
    {
        if (m_theme.ButtonGlossHighlight.w <= 0.0f || m_theme.ButtonGlossIntensity <= 0.0f)
            return;

        ImDrawList *dl = ImGui::GetWindowDrawList();

        float glossHeight = (max.y - min.y) * 0.40f;
        float inset = rounding > 4.0f ? rounding * 0.5f : 2.0f;
        ImVec2 glossMin(min.x + inset, min.y + 1.0f);
        ImVec2 glossMax(max.x - inset, min.y + glossHeight);

        if (glossMax.y <= glossMin.y)
            return;

        ImVec4 fadedOut = ImVec4(m_theme.ButtonGlossHighlight.x,
                                 m_theme.ButtonGlossHighlight.y,
                                 m_theme.ButtonGlossHighlight.z, 0.0f);
        ImVec4 glossColor = m_theme.ButtonGlossHighlight;
        glossColor.w *= m_theme.ButtonGlossIntensity;

        ImU32 colTop = ImGui::GetColorU32(glossColor);
        ImU32 colBot = ImGui::GetColorU32(fadedOut);

        dl->PushClipRect(min, max, true);
        dl->AddRectFilledMultiColor(glossMin, glossMax, colTop, colTop, colBot, colBot);
        dl->PopClipRect();
    }

    // ── Button Bevel Edges ───────────────────────────────────────────────

    void IPlayerBar::DrawBevelEdges(const ImVec2 &min, const ImVec2 &max, float rounding)
    {
        if (m_theme.ButtonBevelThickness <= 0.0f)
            return;

        ImDrawList *dl = ImGui::GetWindowDrawList();
        float t = m_theme.ButtonBevelThickness;
        float r = rounding;

        ImU32 lightCol = ImGui::GetColorU32(m_theme.ButtonBevelLight);
        ImU32 darkCol = ImGui::GetColorU32(m_theme.ButtonBevelDark);
        ImU32 borderCol = ImGui::GetColorU32(m_theme.ButtonBevelBorderColor);

        dl->PushClipRect(min, max, true);

        // Outer border
        dl->AddRect(min, max, borderCol, r, ImDrawFlags_RoundCornersAll, 1.0f);

        // Light highlight – concentric rounded rects fading inward
        for (float i = 0.0f; i < t; i += 0.5f)
        {
            float alpha = 1.0f - (i / t);
            ImU32 col = ImGui::GetColorU32(ImVec4(
                m_theme.ButtonBevelLight.x,
                m_theme.ButtonBevelLight.y,
                m_theme.ButtonBevelLight.z,
                m_theme.ButtonBevelLight.w * alpha));

            dl->AddRect(
                ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                col, r, ImDrawFlags_RoundCornersAll, 1.0f);
        }

        // Dark shadow – concentric rounded rects fading inward
        for (float i = 0.0f; i < t; i += 0.5f)
        {
            float alpha = 1.0f - (i / t);
            ImU32 col = ImGui::GetColorU32(ImVec4(
                m_theme.ButtonBevelDark.x,
                m_theme.ButtonBevelDark.y,
                m_theme.ButtonBevelDark.z,
                m_theme.ButtonBevelDark.w * alpha));

            dl->AddRect(
                ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                col, r, ImDrawFlags_RoundCornersAll, 1.0f);
        }

        dl->PopClipRect();
    }

    // ── Button Decorations (gloss + bevel) ───────────────────────────────

    void IPlayerBar::DrawClassicButtonDecorations(const ImVec2 &min, const ImVec2 &max)
    {
        float r = m_theme.ButtonRounding;

        if (m_theme.UseButtonBevel)
            DrawBevelEdges(min, max, r);

        if (m_theme.UseButtonGloss)
            DrawGlossOverlay(min, max, r);
    }

    // ── Button Gradient Background ───────────────────────────────────────

    void IPlayerBar::DrawButtonGradientBg(const ImVec2 &min, const ImVec2 &max, float rounding,
                                          const ImVec4 &colorTop, const ImVec4 &colorBottom)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
        dl->PushClipRect(min, max, true);
        dl->AddRectFilledMultiColor(min, max,
                                    ImGui::GetColorU32(colorTop),
                                    ImGui::GetColorU32(colorTop),
                                    ImGui::GetColorU32(colorBottom),
                                    ImGui::GetColorU32(colorBottom));
        dl->PopClipRect();
    }

    // ── Player Bar Background (gradient + bevel) ─────────────────────────

    void IPlayerBar::DrawPlayerBarBackground(const ImVec2 &pos, const ImVec2 &size)
    {
        ImDrawList *dl = ImGui::GetWindowDrawList();
        float rounding = m_theme.PlayerBarGradientRounding;

        // Draw gradient background if enabled
        if (m_theme.UsePlayerBarGradient)
        {
            dl->AddRectFilledMultiColor(
                pos,
                ImVec2(pos.x + size.x, pos.y + size.y),
                ImGui::GetColorU32(m_theme.PlayerBarGradientTop),
                ImGui::GetColorU32(m_theme.PlayerBarGradientTop),
                ImGui::GetColorU32(m_theme.PlayerBarGradientBottom),
                ImGui::GetColorU32(m_theme.PlayerBarGradientBottom));
        }

        // Draw bevel around the player bar if enabled
        if (m_theme.UsePlayerBarBevel && m_theme.PlayerBarBevelThickness > 0.0f)
        {
            float t = m_theme.PlayerBarBevelThickness;
            float r = rounding;

            ImU32 borderCol = ImGui::GetColorU32(m_theme.PlayerBarBevelBorderColor);

            // Outer border
            dl->AddRect(
                ImVec2(pos.x + 1.0f, pos.y + 1.0f),
                ImVec2(pos.x + size.x - 1.0f, pos.y + size.y - 1.0f),
                borderCol, r, ImDrawFlags_RoundCornersAll, 1.0f);

            // Light highlight – concentric rounded rects fading inward
            for (float i = 0.0f; i < t; i += 0.5f)
            {
                float alpha = 1.0f - (i / t);
                ImU32 col = ImGui::GetColorU32(ImVec4(
                    m_theme.PlayerBarBevelLight.x,
                    m_theme.PlayerBarBevelLight.y,
                    m_theme.PlayerBarBevelLight.z,
                    m_theme.PlayerBarBevelLight.w * alpha));

                dl->AddRect(
                    ImVec2(pos.x + i + 2.0f, pos.y + i + 2.0f),
                    ImVec2(pos.x + size.x - i - 2.0f, pos.y + size.y - i - 2.0f),
                    col, r, ImDrawFlags_RoundCornersAll, 1.0f);
            }

            // Dark shadow – concentric rounded rects fading inward
            for (float i = 0.0f; i < t; i += 0.5f)
            {
                float alpha = 1.0f - (i / t);
                ImU32 col = ImGui::GetColorU32(ImVec4(
                    m_theme.PlayerBarBevelDark.x,
                    m_theme.PlayerBarBevelDark.y,
                    m_theme.PlayerBarBevelDark.z,
                    m_theme.PlayerBarBevelDark.w * alpha));

                dl->AddRect(
                    ImVec2(pos.x + i + 2.0f, pos.y + i + 2.0f),
                    ImVec2(pos.x + size.x - i - 2.0f, pos.y + size.y - i - 2.0f),
                    col, r, ImDrawFlags_RoundCornersAll, 1.0f);
            }
        }
    }

    // ── Slider Track Gradient Background ─────────────────────────────────

    void IPlayerBar::DrawSliderGradientBg(const ImVec2 &min, const ImVec2 &max, float rounding)
    {
        if (!m_theme.UseSliderTrackGradient)
            return;

        ImDrawList *dl = ImGui::GetWindowDrawList();
        dl->PushClipRect(min, max, true);
        dl->AddRectFilledMultiColor(min, max,
                                    ImGui::GetColorU32(m_theme.SliderTrackGradientTop),
                                    ImGui::GetColorU32(m_theme.SliderTrackGradientTop),
                                    ImGui::GetColorU32(m_theme.SliderTrackGradientBottom),
                                    ImGui::GetColorU32(m_theme.SliderTrackGradientBottom));
        dl->PopClipRect();
    }

    // ── Slider Grab Decorations (gloss + bevel) ──────────────────────────

    void IPlayerBar::DrawClassicSliderDecorations(const ImVec2 &min, const ImVec2 &max)
    {
        float r = m_theme.SliderRounding;

        // Slider grab bevel
        if (m_theme.UseSliderGrabBevel && m_theme.SliderGrabBevelThickness > 0.0f)
        {
            ImDrawList *dl = ImGui::GetWindowDrawList();
            float t = m_theme.SliderGrabBevelThickness;

            ImU32 lightCol = ImGui::GetColorU32(m_theme.SliderGrabBevelLight);
            ImU32 darkCol = ImGui::GetColorU32(m_theme.SliderGrabBevelDark);
            ImU32 borderCol = ImGui::GetColorU32(m_theme.SliderGrabBevelBorderColor);

            dl->PushClipRect(min, max, true);

            // Outer border
            dl->AddRect(min, max, borderCol, r, ImDrawFlags_RoundCornersAll, 1.0f);

            // Light highlight
            for (float i = 0.0f; i < t; i += 0.5f)
            {
                float alpha = 1.0f - (i / t);
                ImU32 col = ImGui::GetColorU32(ImVec4(
                    m_theme.SliderGrabBevelLight.x,
                    m_theme.SliderGrabBevelLight.y,
                    m_theme.SliderGrabBevelLight.z,
                    m_theme.SliderGrabBevelLight.w * alpha));

                dl->AddRect(
                    ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                    ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                    col, r, ImDrawFlags_RoundCornersAll, 1.0f);
            }

            // Dark shadow
            for (float i = 0.0f; i < t; i += 0.5f)
            {
                float alpha = 1.0f - (i / t);
                ImU32 col = ImGui::GetColorU32(ImVec4(
                    m_theme.SliderGrabBevelDark.x,
                    m_theme.SliderGrabBevelDark.y,
                    m_theme.SliderGrabBevelDark.z,
                    m_theme.SliderGrabBevelDark.w * alpha));

                dl->AddRect(
                    ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                    ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                    col, r, ImDrawFlags_RoundCornersAll, 1.0f);
            }

            dl->PopClipRect();
        }

        // Slider grab gloss
        if (m_theme.UseSliderGrabGloss && m_theme.SliderGrabGlossIntensity > 0.0f)
        {
            ImDrawList *dl = ImGui::GetWindowDrawList();

            float glossHeight = (max.y - min.y) * 0.40f;
            float inset = r > 4.0f ? r * 0.5f : 2.0f;
            ImVec2 glossMin(min.x + inset, min.y + 1.0f);
            ImVec2 glossMax(max.x - inset, min.y + glossHeight);

            if (glossMax.y > glossMin.y)
            {
                ImVec4 fadedOut = ImVec4(m_theme.SliderGrabGlossHighlight.x,
                                         m_theme.SliderGrabGlossHighlight.y,
                                         m_theme.SliderGrabGlossHighlight.z, 0.0f);
                ImVec4 glossColor = m_theme.SliderGrabGlossHighlight;
                glossColor.w *= m_theme.SliderGrabGlossIntensity;

                ImU32 colTop = ImGui::GetColorU32(glossColor);
                ImU32 colBot = ImGui::GetColorU32(fadedOut);

                dl->PushClipRect(min, max, true);
                dl->AddRectFilledMultiColor(glossMin, glossMax, colTop, colTop, colBot, colBot);
                dl->PopClipRect();
            }
        }
    }

    //==========================================================================
    // Style Helpers
    //==========================================================================

    void IPlayerBar::PushNormalButtonStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
    }

    void IPlayerBar::PushPrimaryButtonStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonPrimary);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonPrimaryHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonPrimaryActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
    }

    void IPlayerBar::PushSliderStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.SliderTrack);
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, m_theme.SliderGrab);
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, m_theme.SliderGrabActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.SliderRounding);
        ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, m_theme.SliderRounding);
    }

    void IPlayerBar::PushAlbumArtStyle()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.AlbumArtRounding);
    }

    void IPlayerBar::PopStyle()
    {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
    }

    void IPlayerBar::PopStyleVarOnly()
    {
        ImGui::PopStyleVar();
    }
    void IPlayerBar::PopSliderStyle()
    {
        ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(3);
    }
    //==========================================================================
    // Album Art Click Handler
    //==========================================================================

    void IPlayerBar::OnAlbumArtClicked()
    {
        m_lightbox.Toggle();
    }

    //==========================================================================
    // Scrolling Text
    //==========================================================================

    void IPlayerBar::DrawScrollingText(const char *text, const ImVec4 &color, float maxWidth,
                                       float &scrollOffset, float &lastTrackChangeTime, bool trackChanged)
    {
        if (!text || text[0] == '\0')
            return;

        float currentTime = static_cast<float>(ImGui::GetTime());

        if (trackChanged)
        {
            scrollOffset = 0.0f;
            lastTrackChangeTime = currentTime;
        }

        ImVec2 textSize = ImGui::CalcTextSize(text);

        if (textSize.x <= maxWidth)
        {
            scrollOffset = 0.0f;
            ImGui::TextColored(color, "%s", text);
            return;
        }

        float delay = m_theme.ScrollDelay;
        float speed = m_theme.ScrollSpeed;

        if (currentTime - lastTrackChangeTime > delay)
            scrollOffset += speed * ImGui::GetIO().DeltaTime;

        float totalScrollDistance = textSize.x + 40.0f;
        if (scrollOffset > totalScrollDistance)
            scrollOffset -= totalScrollDistance;

        ImGui::PushID(text);

        ImGui::BeginChild("##scroll", ImVec2(maxWidth, textSize.y), false,
                          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        ImVec2 cursorPos = ImGui::GetCursorPos();
        ImGui::SetCursorPosX(cursorPos.x - scrollOffset);
        ImGui::TextColored(color, "%s", text);

        if (scrollOffset > textSize.x - maxWidth + 40.0f)
        {
            ImGui::SameLine(0, 40.0f);
            ImGui::TextColored(color, "%s", text);
        }

        ImGui::EndChild();
        ImGui::PopID();
    }

    //==========================================================================
    // Modular Drawing Methods
    //==========================================================================

    void IPlayerBar::DrawAlbumArt()
    {
        if (!m_data)
            return;

        if (m_data->trackJustChanged)
            m_artLoadAttempted = false;

        LoadAlbumArtForCurrentTrack();

        m_albumArtBox.Draw(m_theme.AlbumArtSize, m_theme.AlbumArtRounding, true, true);

        if (m_albumArtBox.IsClicked() && m_albumArtTexture)
            OnAlbumArtClicked();

        if (m_albumArtBox.IsHovered() && m_albumArtTexture)
            ImGui::SetTooltip("Click to enlarge album art");
    }

    void IPlayerBar::DrawSongInfo()
    {
        DrawSongTitle();
        DrawArtistName();
    }

    void IPlayerBar::DrawPlaybackTimeline()
    {
        float windowWidth = ImGui::GetWindowWidth();
        float padding = 15.0f;

        float elapsedWidth = ImGui::CalcTextSize("00:00").x;
        float totalWidth = ImGui::CalcTextSize("00:00").x;

        float sliderWidth = windowWidth - elapsedWidth - totalWidth - (padding * 4.0f);
        if (sliderWidth < 100.0f)
            sliderWidth = 100.0f;

        ImGui::SetCursorPosX(padding);
        DrawElapsedTime();
        ImGui::SameLine();
        ImGui::SetNextItemWidth(sliderWidth);
        DrawPlaybackSlider();
        ImGui::SameLine();
        ImGui::SetCursorPosX(windowWidth - totalWidth - padding);
        DrawTotalTime();
    }

    void IPlayerBar::DrawVisualizer()
    {
        if (m_data)
        {
            m_visualizer.SetAudioStream(m_data->audioStream);
            m_visualizer.SetVolume(m_data->volume);

            if (m_playbackController)
            {
                int mode = m_playbackController->GetVisualizerMode();
                m_visualizer.SetMode(mode == 0 ? VisualizerMode::Spectrum : VisualizerMode::Oscilloscope);
            }
        }
        m_visualizer.Draw();
    }

    void IPlayerBar::DrawControls()
    {
        if (!m_data)
            return;

        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 160.0f;

        float prevWidth = ImGui::CalcTextSize("<<").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize(m_data->modeLabel.c_str()).x +
                            ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
        float volWidth = ImGui::CalcTextSize("Vol").x +
                         ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

        float centralGroupWidth = prevWidth + Gap + playWidth + Gap + nextWidth + Gap + repeatWidth;
        float volumeSectionWidth = volWidth + Gap + VolumeSliderWidth;

        float availWidth = ImGui::GetContentRegionAvail().x;
        float controlsY = ImGui::GetCursorPosY();

        float playCenterX = availWidth * 0.5f;
        float playOffsetInGroup = prevWidth + Gap + (playWidth * 0.5f);
        float centralStartX = playCenterX - playOffsetInGroup;

        if (centralStartX < 0.0f)
            centralStartX = 0.0f;
        if (centralStartX + centralGroupWidth + Gap + volumeSectionWidth > availWidth)
        {
            centralStartX = availWidth - centralGroupWidth - Gap - volumeSectionWidth;
            if (centralStartX < 0.0f)
                centralStartX = 0.0f;
        }

        ImGui::SetCursorPosX(centralStartX);
        ImGui::SetCursorPosY(controlsY);

        DrawPreviousButton();
        ImGui::SameLine(0, Gap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, Gap);
        DrawNextButton();
        ImGui::SameLine(0, Gap);
        DrawPlayModeButton();

        float volumeX = availWidth - volumeSectionWidth;
        ImGui::SetCursorPosX(volumeX);
        ImGui::SetCursorPosY(controlsY);
        DrawVolumeIcon();
        ImGui::SameLine(0, Gap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }

    //==========================================================================
    // Individual Control Drawers
    //==========================================================================

    void IPlayerBar::DrawPreviousButton()
    {
        const char *label = "<<";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
                          textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);
        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPreviousButtonPressed();
        DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
        PopStyle();
    }

    void IPlayerBar::DrawPlayPauseButton()
    {
        if (!m_data)
            return;
        const char *label = m_data->isPlaying ? " || " : " > ";
        ImVec2 textSize = ImGui::CalcTextSize(" || ");
        ImVec2 buttonSize(textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth,
                          textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);
        PushPrimaryButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPlayPauseButtonPressed();
        DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
        PopStyle();
    }

    void IPlayerBar::DrawNextButton()
    {
        const char *label = ">>";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
                          textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);
        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnNextButtonPressed();
        DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
        PopStyle();
    }

    void IPlayerBar::DrawPlayModeButton()
    {
        if (!m_data)
            return;
        const char *label = m_data->modeLabel.c_str();
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
                          textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);
        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPlayModeButtonPressed();
        DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
        PopStyle();
    }

    void IPlayerBar::DrawVolumeIcon()
    {
        const char *label = "Vol";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
                          textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);
        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnVolumeIconPressed();
        DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
        PopStyle();
    }

    void IPlayerBar::DrawVolumeSlider()
    {
        if (!m_data)
            return;
        PushSliderStyle();
        float tempVolume = m_data->volume;
        if (ImGui::SliderFloat("##Volume", &tempVolume, 0.0f, 1.0f))
            OnVolumeSliderChanged(tempVolume);
        PopSliderStyle();
    }

    //==========================================================================
    // Song Info Drawers
    //==========================================================================

    void IPlayerBar::DrawSongTitle()
    {
        if (!m_data)
            return;
        ImGui::TextColored(m_theme.TextPrimary, "%s", m_data->title.c_str());
    }

    void IPlayerBar::DrawArtistName()
    {
        if (!m_data)
            return;
        ImGui::TextColored(m_theme.TextSecondary, "%s", m_data->artist.c_str());
    }

    void IPlayerBar::DrawElapsedTime()
    {
        if (!m_data)
            return;
        ImGui::TextColored(m_theme.TextPrimary, "%s", m_data->elapsedFormatted.c_str());
    }

    void IPlayerBar::DrawTotalTime()
    {
        if (!m_data)
            return;
        ImGui::TextColored(m_theme.TextPrimary, "%s", m_data->totalFormatted.c_str());
    }

    void IPlayerBar::DrawPlaybackSlider()
    {
        if (!m_data)
            return;
        PushSliderStyle();
        float progress = m_data->progress;
        if (ImGui::SliderFloat("##Playback", &progress, 0.0f, 1.0f))
        {
            m_isSeeking = true;
            m_wasSeeking = true;
            OnPlaybackSliderChanged(progress);
        }
        if (m_wasSeeking && !ImGui::IsItemActive())
        {
            m_isSeeking = false;
            m_wasSeeking = false;
        }
        PopSliderStyle();
    }

    //==========================================================================
    // Event Handlers
    //==========================================================================

    void IPlayerBar::OnPreviousButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackController->Previous();
        }
    }

    void IPlayerBar::OnPlayPauseButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackController->TogglePlayPause();
        }
    }

    void IPlayerBar::OnNextButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackController->Next();
        }
    }

    void IPlayerBar::OnPlaybackSliderChanged(float value)
    {
        if (m_playbackController && m_data && m_data->durationSeconds > 0.0f)
        {
            float position = value * m_data->durationSeconds;
            m_playbackController->SeekTo(position);
        }
    }

    void IPlayerBar::OnVolumeIconPressed()
    {
        if (m_playbackController && m_data)
        {
            float newVolume = m_data->volume > 0.0f ? 0.0f : 0.80f;
            m_playbackController->SetVolume(newVolume);
        }
    }

    void IPlayerBar::OnVolumeSliderChanged(float value)
    {
        if (m_playbackController)
            m_playbackController->SetVolume(value);
    }

    void IPlayerBar::OnPlayModeButtonPressed()
    {
        if (m_playbackController)
        {
            PlaybackMode currentMode = m_playbackController->GetPlaybackMode();
            PlaybackMode newMode;
            switch (currentMode)
            {
            case PlaybackMode::Normal:
                newMode = PlaybackMode::Reverse;
                break;
            case PlaybackMode::Reverse:
                newMode = PlaybackMode::Repeat;
                break;
            case PlaybackMode::Repeat:
                newMode = PlaybackMode::Shuffle;
                break;
            case PlaybackMode::Shuffle:
            default:
                newMode = PlaybackMode::Normal;
                break;
            }
            m_playbackController->SetPlaybackMode(newMode);
        }
    }

} // namespace moosic