//==============================================================================
// IPlayerBar.cpp
//==============================================================================
// Base implementation for player bar functionality including playback controls,
// album art management, and audio visualization
//==============================================================================

#include "IPlayerBar.h"
#include <imgui.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace moosic
{

    //==============================================================================
    // Setup & Configuration
    //==============================================================================
    void IPlayerBar::SetRenderer(SDL_Renderer *renderer)
    {
        m_renderer = renderer;

        // Apply themes to child widgets
        m_lightbox.ApplyTheme(m_theme.Lightbox);
        m_albumArtBox.ApplyTheme(m_theme.AlbumArtBox);
        m_visualizer.ApplyTheme(m_theme.Visualizer);

        // Restore visualizer mode after theme application resets it
        m_visualizer.SetMode(m_lastVisualizerMode == 0 ? VisualizerMode::Spectrum : VisualizerMode::Oscilloscope);
    }

    void IPlayerBar::SetPlaybackController(PlaybackController *controller)
    {
        m_playbackController = controller;
        if (m_playbackController)
        {
            UpdatePlaybackState();
        }
    }

        void IPlayerBar::ApplyTheme(const PlayerBarTheme &theme)
    {
        m_theme = theme;

        // Forward theme to child widgets
        m_lightbox.ApplyTheme(theme.Lightbox);
        m_albumArtBox.ApplyTheme(theme.AlbumArtBox);
        m_visualizer.ApplyTheme(theme.Visualizer);
        
        // Restore visualizer mode after theme application resets it
        m_visualizer.SetMode(m_lastVisualizerMode == 0 ? VisualizerMode::Spectrum : VisualizerMode::Oscilloscope);
    }

    //==============================================================================
    // Album Art Management
    //==============================================================================

    void IPlayerBar::LoadAlbumArt(const MusicTrack *track)
    {
        // Check if we already have the art for this track
        if (track && track->GetId() != 0 &&
            m_lastAlbumArtTrackId == track->GetId() &&
            m_albumArtTexture)
            return;

        // Clear existing texture
        if (m_albumArtTexture)
        {
            m_imageLoader.DestroyImGuiTexture(m_albumArtTexture);
            m_albumArtTexture = nullptr;
            m_albumArtWidth = 0;
            m_albumArtHeight = 0;
            m_albumArtBox.ClearTexture();
        }

        // Validate track and renderer
        if (!track || !track->HasAlbumArt() || !m_renderer)
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        // Get album art data
        const auto &artData = track->GetAlbumArtData();
        if (artData.empty())
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        // Load image from memory
        ImageData image = m_imageLoader.LoadFromMemory(artData.data(), artData.size());
        if (image.data.empty())
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        // Resize if too large
        int maxDimension = 512;
        if (image.width > maxDimension || image.height > maxDimension)
        {
            float scale = static_cast<float>(maxDimension) / (std::max)(image.width, image.height);
            int newWidth = static_cast<int>(image.width * scale);
            int newHeight = static_cast<int>(image.height * scale);
            image = m_imageLoader.Resize(image, newWidth, newHeight);
        }

        // Create ImGui texture
        m_albumArtTexture = m_imageLoader.CreateImGuiTexture(m_renderer, image);
        if (m_albumArtTexture)
        {
            m_lastAlbumArtTrackId = track->GetId();
            m_albumArtWidth = image.width;
            m_albumArtHeight = image.height;

            // Update lightbox
            m_lightbox.SetTexture(m_albumArtTexture, image.width, image.height);
            m_lightbox.SetInfo(m_songTitle, m_artistName);
            m_lightbox.ApplyTheme(m_theme.Lightbox);

            // Update album art box
            m_albumArtBox.SetTexture(m_albumArtTexture, image.width, image.height);
            m_albumArtBox.ApplyTheme(m_theme.AlbumArtBox);
        }
        else
        {
            m_lastAlbumArtTrackId = 0;
            m_albumArtBox.ClearTexture();
        }
    }

    void IPlayerBar::UpdateAlbumArtTexture()
    {
        if (!m_playbackController)
            return;

        const MusicTrack *track = m_playbackController->GetCurrentTrack();

        std::size_t currentTrackId = track ? track->GetId() : 0;
        if (currentTrackId != m_lastAlbumArtTrackId ||
            (track && !m_albumArtTexture && track->HasAlbumArt()))
        {
            LoadAlbumArt(track);
        }
    }

    //==============================================================================
    // Playback State Management
    //==============================================================================

    void IPlayerBar::UpdatePlaybackState()
    {
        if (!m_playbackController)
            return;

        // Check for end-of-track auto-advance
        m_playbackController->Update();

        const MusicTrack *track = m_playbackController->GetCurrentTrack();

        std::size_t currentTrackId = track ? track->GetId() : 0;
        bool trackChanged = (currentTrackId != m_lastTrackId);

        // Handle track changes
        if (trackChanged)
        {
            m_lastTrackId = currentTrackId;
            m_isSeeking = false;
            m_playbackProgress = 0.0f;
            m_elapsedTime = 0.0f;

            // Reset scrolling
            m_titleScrollOffset = 0.0f;
            m_artistScrollOffset = 0.0f;
            m_lastTrackChangeTime = static_cast<float>(ImGui::GetTime());

            if (track)
            {
                // Load new track data
                m_lastAlbumArtTrackId = 0;
                LoadAlbumArt(track);

                m_songTitle = track->GetTitle().c_str();
                m_artistName = track->GetArtist().c_str();
                m_songDuration = static_cast<float>(track->GetDuration());

                m_lightbox.SetInfo(m_songTitle, m_artistName);
            }
            else
            {
                // Clear everything
                if (m_albumArtTexture)
                {
                    m_imageLoader.DestroyImGuiTexture(m_albumArtTexture);
                    m_albumArtTexture = nullptr;
                    m_albumArtWidth = 0;
                    m_albumArtHeight = 0;
                    m_lightbox.SetTexture(nullptr, 0, 0);
                    m_albumArtBox.ClearTexture();
                }
                m_lastAlbumArtTrackId = 0;
                m_songTitle = "No Song Playing";
                m_artistName = "Unknown Artist";
                m_songDuration = 0.0f;
                m_lightbox.SetInfo(m_songTitle, m_artistName);
            }
        }
        else
        {
            // Reload album art if missing
            if (track && track->HasAlbumArt() && !m_albumArtTexture)
            {
                LoadAlbumArt(track);
            }
        }

        UpdateAlbumArtTexture();

        // Update playback state (skip if seeking)
        if (!m_isSeeking)
        {
            m_isPlaying = m_playbackController->IsPlaying();
            m_elapsedTime = m_playbackController->GetCurrentPosition();
            m_songDuration = m_playbackController->GetCurrentDuration();
            m_volume = m_playbackController->GetVolume();

            if (m_songDuration > 0.0f)
                m_playbackProgress = m_elapsedTime / m_songDuration;
            else
                m_playbackProgress = 0.0f;
        }

        // Update track info
        if (track)
        {
            m_songTitle = track->GetTitle().c_str();
            m_artistName = track->GetArtist().c_str();
            m_lightbox.SetInfo(m_songTitle, m_artistName);
        }

        // Update visualizer with current stream and mode
        if (m_playbackController)
        {
            HSTREAM stream = m_playbackController->GetAudioStream();
            m_visualizer.SetAudioStream(stream);
            m_visualizer.SetVolume(m_volume);

            // Read visualizer mode from PlaybackController and track it
            m_lastVisualizerMode = m_playbackController->GetVisualizerMode();
            m_visualizer.SetMode(m_lastVisualizerMode == 0 ? VisualizerMode::Spectrum : VisualizerMode::Oscilloscope);
        }
    }

    //==============================================================================
    // Style Helpers
    //==============================================================================

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

    //==============================================================================
    // Album Art Click Handler
    //==============================================================================

    void IPlayerBar::OnAlbumArtClicked()
    {
        m_lightbox.Toggle();
    }

    //==============================================================================
    // Scrolling Text
    //==============================================================================

    void IPlayerBar::DrawScrollingText(const char *text, const ImVec4 &color, float maxWidth,
                                       float &scrollOffset, float &lastTrackChangeTime, bool trackChanged)
    {
        if (!text || text[0] == '\0')
            return;

        float currentTime = static_cast<float>(ImGui::GetTime());

        // Reset on track change
        if (trackChanged)
        {
            scrollOffset = 0.0f;
            lastTrackChangeTime = currentTime;
        }

        ImVec2 textSize = ImGui::CalcTextSize(text);

        // If text fits, just draw it normally
        if (textSize.x <= maxWidth)
        {
            scrollOffset = 0.0f;
            ImGui::TextColored(color, "%s", text);
            return;
        }

        // Calculate scroll
        float delay = m_theme.ScrollDelay;
        float speed = m_theme.ScrollSpeed;

        if (currentTime - lastTrackChangeTime > delay)
        {
            scrollOffset += speed * ImGui::GetIO().DeltaTime;
        }

        // Loop the scroll
        float totalScrollDistance = textSize.x + 40.0f; // 40px gap between loops
        if (scrollOffset > totalScrollDistance)
        {
            scrollOffset -= totalScrollDistance;
        }

        // Clip to a child region for scrolling
        ImGui::BeginChild("##scrollclip", ImVec2(maxWidth, textSize.y), false,
                          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        ImVec2 cursorPos = ImGui::GetCursorPos();
        ImGui::SetCursorPosX(cursorPos.x - scrollOffset);
        ImGui::TextColored(color, "%s", text);

        // Draw the repeating text for seamless loop
        if (scrollOffset > textSize.x - maxWidth + 40.0f)
        {
            ImGui::SameLine(0, 40.0f);
            ImGui::TextColored(color, "%s", text);
        }

        ImGui::EndChild();
    }

    //==============================================================================
    // Modular Drawing Methods
    //==============================================================================

    void IPlayerBar::DrawAlbumArt()
    {
        m_albumArtBox.Draw(m_theme.AlbumArtSize, m_theme.AlbumArtRounding, true, true);

        if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        {
            OnAlbumArtClicked();
        }

        if (m_albumArtBox.IsHovered() && m_albumArtTexture)
        {
            ImGui::SetTooltip("Click to enlarge album art");
        }
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
        m_visualizer.Draw();
    }

    void IPlayerBar::DrawControls()
    {
        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 160.0f;

        float prevWidth = ImGui::CalcTextSize("<<").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f +
                          m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f +
                          m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize("Repeat").x +
                            ImGui::GetStyle().FramePadding.x * 2.0f +
                            m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x +
                          ImGui::GetStyle().FramePadding.x * 2.0f +
                          m_theme.PrimaryButtonExtraWidth;
        float volWidth = ImGui::CalcTextSize("Vol").x +
                         ImGui::GetStyle().FramePadding.x * 2.0f +
                         m_theme.NormalButtonExtraWidth;

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

    //==============================================================================
    // Individual Control Drawers
    //==============================================================================

    void IPlayerBar::DrawPreviousButton()
    {
        const char *label = "<<";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(
            textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
            textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);

        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPreviousButtonPressed();
        PopStyle();
    }

    void IPlayerBar::DrawPlayPauseButton()
    {
        const char *label = m_isPlaying ? " || " : " > ";
        const char *maxLabel = " || ";
        ImVec2 textSize = ImGui::CalcTextSize(maxLabel);

        ImVec2 buttonSize(
            textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth,
            textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);

        PushPrimaryButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPlayPauseButtonPressed();
        PopStyle();
    }

    void IPlayerBar::DrawNextButton()
    {
        const char *label = ">>";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(
            textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
            textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);

        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnNextButtonPressed();
        PopStyle();
    }

    void IPlayerBar::DrawPlayModeButton()
    {
        const char *labels[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
        const char *label = labels[static_cast<int>(m_playbackMode)];

        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(
            textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
            textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);

        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnPlayModeButtonPressed();
        PopStyle();
    }

    void IPlayerBar::DrawVolumeIcon()
    {
        const char *label = "Vol";
        ImVec2 textSize = ImGui::CalcTextSize(label);
        ImVec2 buttonSize(
            textSize.x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth,
            textSize.y + ImGui::GetStyle().FramePadding.y * 2.0f + m_theme.ButtonHeightExtra);

        PushNormalButtonStyle();
        if (ImGui::Button(label, buttonSize))
            OnVolumeIconPressed();
        PopStyle();
    }

    void IPlayerBar::DrawVolumeSlider()
    {
        PushSliderStyle();
        float tempVolume = m_volume;
        if (ImGui::SliderFloat("##Volume", &tempVolume, 0.0f, 1.0f))
        {
            OnVolumeSliderChanged(tempVolume);
        }
        PopStyle();
    }

    //==============================================================================
    // Song Info Drawers
    //==============================================================================

    void IPlayerBar::DrawSongTitle()
    {
        ImGui::TextColored(m_theme.TextPrimary, "%s", m_songTitle);
    }

    void IPlayerBar::DrawArtistName()
    {
        ImGui::TextColored(m_theme.TextSecondary, "%s", m_artistName);
    }

    void IPlayerBar::DrawElapsedTime()
    {
        int min = static_cast<int>(m_elapsedTime) / 60;
        int sec = static_cast<int>(m_elapsedTime) % 60;
        ImGui::TextColored(m_theme.TextPrimary, "%02d:%02d", min, sec);
    }

    void IPlayerBar::DrawTotalTime()
    {
        int min = static_cast<int>(m_songDuration) / 60;
        int sec = static_cast<int>(m_songDuration) % 60;
        ImGui::TextColored(m_theme.TextPrimary, "%02d:%02d", min, sec);
    }

    void IPlayerBar::DrawPlaybackSlider()
    {
        PushSliderStyle();

        static bool wasSeeking = false;

        if (ImGui::SliderFloat("##Playback", &m_playbackProgress, 0.0f, 1.0f))
        {
            m_isSeeking = true;
            wasSeeking = true;

            if (m_songDuration > 0.0f)
            {
                m_elapsedTime = m_playbackProgress * m_songDuration;
            }

            OnPlaybackSliderChanged(m_playbackProgress);
        }

        if (wasSeeking && !ImGui::IsItemActive())
        {
            m_isSeeking = false;
            wasSeeking = false;

            if (m_playbackController)
            {
                m_elapsedTime = m_playbackController->GetCurrentPosition();
                m_songDuration = m_playbackController->GetCurrentDuration();
                if (m_songDuration > 0.0f)
                    m_playbackProgress = m_elapsedTime / m_songDuration;
            }
        }

        PopStyle();
    }

    //==============================================================================
    // Event Handlers
    //==============================================================================

    void IPlayerBar::OnPreviousButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackProgress = 0.0f;
            m_elapsedTime = 0.0f;
            m_playbackController->Previous();
            UpdatePlaybackState();
        }
    }

    void IPlayerBar::OnPlayPauseButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackController->TogglePlayPause();
            UpdatePlaybackState();
        }
    }

    void IPlayerBar::OnNextButtonPressed()
    {
        if (m_playbackController)
        {
            m_isSeeking = false;
            m_playbackProgress = 0.0f;
            m_elapsedTime = 0.0f;
            m_playbackController->Next();
            UpdatePlaybackState();
        }
    }

    void IPlayerBar::OnPlaybackSliderChanged(float value)
    {
        if (m_playbackController && m_songDuration > 0.0f)
        {
            float position = value * m_songDuration;
            m_playbackController->SeekTo(position);
        }
    }

    void IPlayerBar::OnVolumeIconPressed()
    {
        if (m_playbackController)
        {
            float newVolume = m_volume > 0.0f ? 0.0f : 0.80f;
            m_playbackController->SetVolume(newVolume);
            UpdatePlaybackState();
        }
    }

    void IPlayerBar::OnVolumeSliderChanged(float value)
    {
        if (m_playbackController)
        {
            m_playbackController->SetVolume(value);
            UpdatePlaybackState();
        }
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
            m_playbackMode = newMode;
            UpdatePlaybackState();
        }
    }

} // namespace moosic