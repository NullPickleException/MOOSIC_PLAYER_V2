//==============================================================================
// SidePlayerBar.cpp
//==============================================================================

#include "SidePlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

    void SidePlayerBar::Draw()
    {
        float sidebarWidth = ImGui::GetContentRegionAvail().x;
        float contentWidth = sidebarWidth - 8.0f;
        float centerX = (sidebarWidth - contentWidth) * 0.5f;
        float artSize = contentWidth - 4.0f;

        //==================================================================
        // Visualizer scaling factor
        //==================================================================
        // This scales the visualizer proportionally relative to the sidebar width.
        // 1.0 = full width, 0.8 = 80% of content width, etc.
        // Adjust this value or make it part of the theme/style.
        constexpr float VISUALIZER_SCALE = 0.85f;  // 85% of content width
        
        // Calculate scaled visualizer dimensions
        const auto& visStyle = m_visualizer.GetStyle();
        float visWidth = contentWidth * VISUALIZER_SCALE;
        float visHeight = visStyle.BoxHeight * VISUALIZER_SCALE;
        float visOffsetX = (contentWidth - visWidth) * 0.5f;

        ImGui::Spacing();

        //==================================================================
        // Album Art - Using AlbumArtBox with custom size
        //==================================================================
        m_albumArtBox.Draw(artSize, 6.0f, true, true);
        
        if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        {
            OnAlbumArtClicked();
        }
        
        if (m_albumArtBox.IsHovered() && m_albumArtTexture)
        {
            ImGui::SetTooltip("Click to enlarge");
        }

        ImGui::Spacing();

        //==================================================================
        // Visualizer - Scaled width, centered in content area
        //==================================================================
        m_visualizer.SetBoxSize(visWidth, visHeight);
        
        ImGui::SetCursorPosX(centerX + visOffsetX);
        DrawVisualizer();

        ImGui::Spacing();

        //==================================================================
        // Song Info
        //==================================================================
        ImGui::PushTextWrapPos(sidebarWidth - 12.0f);
        DrawSongTitle();
        DrawArtistName();
        ImGui::PopTextWrapPos();

        ImGui::Spacing();
        ImGui::SetCursorPosX(centerX);
        ImGui::Separator();
        ImGui::Spacing();

        //==================================================================
        // Controls - 3 buttons in one row
        //==================================================================
        float btnSpacing = 4.0f;
        float btnWidth = (contentWidth - btnSpacing * 2.0f) / 3.0f;

        ImGui::SetCursorPosX(centerX);
        PushNormalButtonStyle();
        if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
        PopStyle();

        ImGui::SameLine(0, btnSpacing);
        PushPrimaryButtonStyle();
        if (ImGui::Button(m_isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
        PopStyle();

        ImGui::SameLine(0, btnSpacing);
        PushNormalButtonStyle();
        if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
        PopStyle();

        ImGui::Spacing();

        //==================================================================
        // Play Mode
        //==================================================================
        ImGui::SetCursorPosX(centerX);
        const char* modeLabels[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
        PushNormalButtonStyle();
        if (ImGui::Button(modeLabels[static_cast<int>(m_playbackMode)], ImVec2(contentWidth, 0)))
            OnPlayModeButtonPressed();
        PopStyle();

        ImGui::Spacing();
        ImGui::SetCursorPosX(centerX);
        ImGui::Separator();
        ImGui::Spacing();

        //==================================================================
        // Volume
        //==================================================================
        ImGui::SetCursorPosX(centerX);
        ImGui::TextColored(m_theme.TextSecondary, "Volume");
        ImGui::Spacing();

        ImGui::SetCursorPosX(centerX);
        ImGui::SetNextItemWidth(contentWidth);
        PushSliderStyle();
        float tempVolume = m_volume;
        if (ImGui::SliderFloat("##SideVol", &tempVolume, 0.0f, 1.0f, ""))
            OnVolumeSliderChanged(tempVolume);
        PopStyle();

        ImGui::Spacing();
        ImGui::SetCursorPosX(centerX);
        ImGui::Separator();
        ImGui::Spacing();

        //==================================================================
        // Progress
        //==================================================================
        ImGui::SetCursorPosX(centerX);
        ImGui::SetNextItemWidth(contentWidth);
        PushSliderStyle();
        
        static bool wasSeekingSide = false;
        if (ImGui::SliderFloat("##SideProgress", &m_playbackProgress, 0.0f, 1.0f, ""))
        {
            m_isSeeking = true;
            wasSeekingSide = true;
            if (m_songDuration > 0.0f)
                m_elapsedTime = m_playbackProgress * m_songDuration;
            OnPlaybackSliderChanged(m_playbackProgress);
        }
        if (wasSeekingSide && !ImGui::IsItemActive())
        {
            m_isSeeking = false;
            wasSeekingSide = false;
            if (m_playbackController)
            {
                m_elapsedTime = m_playbackController->GetCurrentPosition();
                m_songDuration = m_playbackController->GetCurrentDuration();
                if (m_songDuration > 0.0f)
                    m_playbackProgress = m_elapsedTime / m_songDuration;
            }
        }
        PopStyle();

        ImGui::SetCursorPosX(centerX);
        DrawElapsedTime();
        ImGui::SameLine();
        ImGui::TextColored(m_theme.TextSecondary, " / ");
        ImGui::SameLine();
        DrawTotalTime();

        ImGui::Spacing();

        //==================================================================
        // Lightbox (on top of everything)
        //==================================================================
        m_lightbox.Draw();
    }

} // namespace moosic