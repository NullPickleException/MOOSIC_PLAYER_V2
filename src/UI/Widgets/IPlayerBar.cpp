#include "IPlayerBar.h"
#include <imgui.h>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace moosic
{

    void IPlayerBar::ApplyTheme(const PlayerBarTheme &theme)
    {
        m_theme = theme;
    }

    void IPlayerBar::SetPlaybackController(PlaybackController* controller)
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

        const MusicTrack* track = m_playbackController->GetCurrentTrack();
        
        // Check if track changed
        std::size_t currentTrackId = track ? track->GetId() : 0;
        if (currentTrackId != m_lastTrackId)
        {
            // Track changed - reset everything
            m_lastTrackId = currentTrackId;
            m_isSeeking = false;
            m_playbackProgress = 0.0f;
            m_elapsedTime = 0.0f;
            
            if (track)
            {
                m_songTitle = track->GetTitle().c_str();
                m_artistName = track->GetArtist().c_str();
                m_songDuration = static_cast<float>(track->GetDuration());
            }
            else
            {
                m_songTitle = "No Song Playing";
                m_artistName = "Unknown Artist";
                m_songDuration = 0.0f;
            }
        }

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

        if (track)
        {
            m_songTitle = track->GetTitle().c_str();
            m_artistName = track->GetArtist().c_str();
        }
        else
        {
            m_songTitle = "No Song Playing";
            m_artistName = "Unknown Artist";
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
    // Song Information
    //==========================================================

    void IPlayerBar::DrawAlbumArt()
    {
        PushAlbumArtStyle();
        ImGui::Button("Cover", ImVec2(m_theme.AlbumArtSize, m_theme.AlbumArtSize));
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
        // Updated mode labels
        const char* labels[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
        const char* label = labels[static_cast<int>(m_playbackMode)];
        
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
        
        // FIXED: Track if slider was just released
        static bool wasSeeking = false;
        
        if (ImGui::SliderFloat("##Playback", &m_playbackProgress, 0.0f, 1.0f))
        {
            // User started dragging or is currently dragging
            m_isSeeking = true;
            wasSeeking = true;
            
            // Update elapsed time from progress
            if (m_songDuration > 0.0f)
            {
                m_elapsedTime = m_playbackProgress * m_songDuration;
            }
            
            // Seek to the new position
            OnPlaybackSliderChanged(m_playbackProgress);
        }
        
        // FIXED: When user releases the slider, update from controller
        if (wasSeeking && !ImGui::IsItemActive())
        {
            // Slider was just released
            m_isSeeking = false;
            wasSeeking = false;
            
            // Force immediate update from controller
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
            std::cout << "[PlayerBar] Seeking to: " << position << "s (progress: " << value << ")\n";
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
            // Updated: Cycle through Normal -> Reverse -> Repeat -> Shuffle -> Normal
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