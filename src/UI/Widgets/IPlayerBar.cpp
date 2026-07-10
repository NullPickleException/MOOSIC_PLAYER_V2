#include "IPlayerBar.h"
#include "../../Services/ImageLoader.h"
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
        // Check if we already have a texture for this track
        if (track && track->GetId() != 0 && m_lastAlbumArtTrackId == track->GetId() && m_albumArtTexture)
            return;

        // Destroy old texture
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
            std::cout << "[PlayerBar] Failed to load album art data\n";
            return;
        }

        // Calculate target size maintaining aspect ratio
        int targetSize = static_cast<int>(m_theme.AlbumArtSize);
        int newWidth = image.width;
        int newHeight = image.height;

        // Only resize if image is larger than target or too small
        if (image.width != targetSize || image.height != targetSize)
        {
            // Maintain aspect ratio
            float aspect = static_cast<float>(image.width) / image.height;

            if (aspect > 1.0f)
            {
                // Wider than tall
                newWidth = targetSize;
                newHeight = static_cast<int>(targetSize / aspect);
            }
            else
            {
                // Taller than wide or square
                newHeight = targetSize;
                newWidth = static_cast<int>(targetSize * aspect);
            }

            // Ensure minimum size
            if (newWidth < 1)
                newWidth = 1;
            if (newHeight < 1)
                newHeight = 1;

            std::cout << "[PlayerBar] Resizing art from " << image.width << "x" << image.height
                      << " to " << newWidth << "x" << newHeight << "\n";

            image = m_imageLoader.Resize(image, newWidth, newHeight);
        }

        // Create texture
        m_albumArtTexture = m_imageLoader.CreateImGuiTexture(m_renderer, image);
        if (m_albumArtTexture)
        {
            m_lastAlbumArtTrackId = track->GetId();
            m_albumArtWidth = image.width;
            m_albumArtHeight = image.height;
            
            // Update lightbox
            m_lightbox.SetTexture(m_albumArtTexture, m_albumArtWidth, m_albumArtHeight);
            m_lightbox.SetInfo(m_songTitle, m_artistName);
            m_lightbox.SetTheme(m_theme.Lightbox);
            
            std::cout << "[PlayerBar] Album art loaded successfully for track ID: " << track->GetId()
                      << " (" << m_albumArtWidth << "x" << m_albumArtHeight << ")\n";
        }
        else
        {
            m_lastAlbumArtTrackId = 0;
            std::cout << "[PlayerBar] Failed to create texture for album art\n";
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

        // Use a fixed display size for the album art container
        ImVec2 displaySize(m_theme.AlbumArtSize, m_theme.AlbumArtSize);

        if (m_albumArtTexture && m_albumArtWidth > 0 && m_albumArtHeight > 0)
        {
            // Calculate the actual image size to maintain aspect ratio
            float aspect = static_cast<float>(m_albumArtWidth) / m_albumArtHeight;
            if (aspect > 1.0f)
            {
                // Wider than tall
                displaySize.x = m_theme.AlbumArtSize;
                displaySize.y = m_theme.AlbumArtSize / aspect;
            }
            else
            {
                // Taller than wide or square
                displaySize.y = m_theme.AlbumArtSize;
                displaySize.x = m_theme.AlbumArtSize * aspect;
            }

            // Make the album art clickable
            ImGui::PushID("AlbumArt");
            
            // Display actual album art with proper aspect ratio
            if (ImGui::ImageButton(
                m_albumArtTexture,
                displaySize,
                ImVec2(0.0f, 0.0f),
                ImVec2(1.0f, 1.0f),
                -1,  // No border
                ImVec4(0, 0, 0, 0),  // No background
                ImVec4(1, 1, 1, 1)   // Tint color
            ))
            {
                OnAlbumArtClicked();
            }
            
            // Add tooltip
            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Click to enlarge album art");
            }
            
            ImGui::PopID();

            // Debug info
            ImGui::SameLine();
            ImGui::TextDisabled("ID: %zu", m_lastAlbumArtTrackId);
        }
        else
        {
            // Display placeholder - not clickable
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