#include "IPlayerBar.h"
#include <imgui.h>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace moosic
{
    void IPlayerBar::SetRenderer(SDL_Renderer *renderer)
    {
        m_renderer = renderer;
        m_lightbox.SetTheme(m_theme.Lightbox);
    }

    void IPlayerBar::LoadAlbumArt(const MusicTrack *track)
    {
        if (track && track->GetId() != 0 && m_lastAlbumArtTrackId == track->GetId() && m_albumArtTexture)
            return;

        if (m_albumArtTexture)
        {
            m_imageLoader.DestroyImGuiTexture(m_albumArtTexture);
            m_albumArtTexture = nullptr;
            m_albumArtWidth = 0;
            m_albumArtHeight = 0;
        }

        if (!track || !track->HasAlbumArt() || !m_renderer)
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        const auto &artData = track->GetAlbumArtData();
        if (artData.empty())
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        ImageData image = m_imageLoader.LoadFromMemory(artData.data(), artData.size());
        if (image.data.empty())
        {
            m_lastAlbumArtTrackId = 0;
            return;
        }

        // Store original dimensions
        int originalWidth = image.width;
        int originalHeight = image.height;

        // Resize to a max dimension to save GPU memory (but keep aspect ratio)
        int maxDimension = 512; // Max texture size
        if (image.width > maxDimension || image.height > maxDimension)
        {
            float scale = static_cast<float>(maxDimension) / (std::max)(image.width, image.height);
            int newWidth = static_cast<int>(image.width * scale);
            int newHeight = static_cast<int>(image.height * scale);
            image = m_imageLoader.Resize(image, newWidth, newHeight);
        }

        // Create texture
        m_albumArtTexture = m_imageLoader.CreateImGuiTexture(m_renderer, image);
        if (m_albumArtTexture)
        {
            m_lastAlbumArtTrackId = track->GetId();
            // Store the ACTUAL image dimensions for UV calculations
            m_albumArtWidth = image.width;
            m_albumArtHeight = image.height;

            m_lightbox.SetTexture(m_albumArtTexture, image.width, image.height);
            m_lightbox.SetInfo(m_songTitle, m_artistName);
            m_lightbox.SetTheme(m_theme.Lightbox);
        }
        else
        {
            m_lastAlbumArtTrackId = 0;
        }
    }

    void IPlayerBar::UpdateAlbumArtTexture()
    {
        if (!m_playbackController)
            return;

        const MusicTrack *track = m_playbackController->GetCurrentTrack();

        // Check if track changed or texture missing
        std::size_t currentTrackId = track ? track->GetId() : 0;
        if (currentTrackId != m_lastAlbumArtTrackId || (track && !m_albumArtTexture && track->HasAlbumArt()))
        {
            LoadAlbumArt(track);
        }
    }

    void IPlayerBar::ApplyTheme(const PlayerBarTheme &theme)
    {
        m_theme = theme;
        m_lightbox.SetTheme(theme.Lightbox);
    }

    void IPlayerBar::SetPlaybackController(PlaybackController *controller)
    {
        m_playbackController = controller;
        if (m_playbackController)
        {
            UpdatePlaybackState();
        }
    }

    void IPlayerBar::UpdatePlaybackState()
    {
        if (!m_playbackController)
            return;

        const MusicTrack *track = m_playbackController->GetCurrentTrack();

        // Check if track changed
        std::size_t currentTrackId = track ? track->GetId() : 0;
        bool trackChanged = (currentTrackId != m_lastTrackId);

        if (trackChanged)
        {
            m_lastTrackId = currentTrackId;
            m_isSeeking = false;
            m_playbackProgress = 0.0f;
            m_elapsedTime = 0.0f;

            // Force reload album art for new track
            if (track)
            {
                m_lastAlbumArtTrackId = 0; // Force reload
                LoadAlbumArt(track);

                m_songTitle = track->GetTitle().c_str();
                m_artistName = track->GetArtist().c_str();
                m_songDuration = static_cast<float>(track->GetDuration());

                // Update lightbox info
                m_lightbox.SetInfo(m_songTitle, m_artistName);
            }
            else
            {
                // Clear album art when no track
                if (m_albumArtTexture)
                {
                    m_imageLoader.DestroyImGuiTexture(m_albumArtTexture);
                    m_albumArtTexture = nullptr;
                    m_albumArtWidth = 0;
                    m_albumArtHeight = 0;
                    m_lightbox.SetTexture(nullptr, 0, 0);
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
            // Even if track hasn't changed, check if we need to load album art
            if (track && track->HasAlbumArt() && !m_albumArtTexture)
            {
                LoadAlbumArt(track);
            }
        }

        // Update album art texture if needed (after potential reload)
        UpdateAlbumArtTexture();

        // Don't update from controller while user is dragging the slider
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

        // Update song info even if track didn't change (in case of metadata updates)
        if (track)
        {
            m_songTitle = track->GetTitle().c_str();
            m_artistName = track->GetArtist().c_str();
            m_lightbox.SetInfo(m_songTitle, m_artistName);
        }
    }

    //==========================================================
    // Style Helpers
    //==========================================================

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

    //==========================================================
    // Album Art Click Handler
    //==========================================================

    void IPlayerBar::OnAlbumArtClicked()
    {
        m_lightbox.Toggle();
    }

    //==========================================================
    // Song Information
    //==========================================================

    void IPlayerBar::DrawAlbumArt()
    {
        PushAlbumArtStyle();

        // FIXED display size - never changes
        ImVec2 displaySize(m_theme.AlbumArtSize, m_theme.AlbumArtSize);

        if (m_albumArtTexture && m_albumArtWidth > 0 && m_albumArtHeight > 0)
        {
            // Use InvisibleButton for click detection (fixed size)
            ImGui::InvisibleButton("##AlbumArtHitbox", displaySize, ImGuiButtonFlags_None);

            // Draw image centered and scaled to FIT within the fixed size (no cropping)
            ImVec2 btnMin = ImGui::GetItemRectMin();
            ImVec2 btnMax = ImGui::GetItemRectMax();

            float imgAspect = static_cast<float>(m_albumArtWidth) / static_cast<float>(m_albumArtHeight);
            float boxSize = m_theme.AlbumArtSize;

            ImVec2 imageSize;
            if (imgAspect > 1.0f)
            {
                // Wider than tall - fit width, center vertically
                imageSize.x = boxSize;
                imageSize.y = boxSize / imgAspect;
            }
            else
            {
                // Taller than wide - fit height, center horizontally
                imageSize.y = boxSize;
                imageSize.x = boxSize * imgAspect;
            }

            // Center the image within the fixed box
            ImVec2 imagePos;
            imagePos.x = btnMin.x + (boxSize - imageSize.x) * 0.5f;
            imagePos.y = btnMin.y + (boxSize - imageSize.y) * 0.5f;

            ImGui::GetWindowDrawList()->AddImage(
                m_albumArtTexture,
                imagePos,
                ImVec2(imagePos.x + imageSize.x, imagePos.y + imageSize.y),
                ImVec2(0, 0),
                ImVec2(1, 1),
                IM_COL32(255, 255, 255, 255));

            // Handle click on the InvisibleButton
            if (ImGui::IsItemClicked())
            {
                OnAlbumArtClicked();
            }

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Click to enlarge album art");
            }
        }
        else
        {
            // Placeholder - same fixed size
            ImGui::Button("No Art", displaySize);
        }

        PopStyleVarOnly();
    }

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

    //==========================================================
    // Controls
    //==========================================================

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

    //==========================================================
    // Playback & Volume
    //==========================================================

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

    //==========================================================
    // Behaviour - Core playback logic
    //==========================================================

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