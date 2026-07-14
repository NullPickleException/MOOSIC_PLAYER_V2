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

        ImGui::Spacing();

        //==================================================================
        // Album Art
        //==================================================================
        if (m_albumArtTexture && m_albumArtWidth > 0 && m_albumArtHeight > 0)
        {
            float imgAspect = static_cast<float>(m_albumArtWidth) / static_cast<float>(m_albumArtHeight);
            ImVec2 imageSize;
            if (imgAspect > 1.0f)
                { imageSize.x = artSize; imageSize.y = artSize / imgAspect; }
            else
                { imageSize.y = artSize; imageSize.x = artSize * imgAspect; }

            float offsetX = (sidebarWidth - imageSize.x) * 0.5f;
            ImGui::SetCursorPosX(offsetX);

            ImGui::InvisibleButton("##SideArtHitbox", imageSize, ImGuiButtonFlags_None);
            ImVec2 btnMin = ImGui::GetItemRectMin();

            ImGui::GetWindowDrawList()->AddImageRounded(
                m_albumArtTexture, btnMin,
                ImVec2(btnMin.x + imageSize.x, btnMin.y + imageSize.y),
                ImVec2(0, 0), ImVec2(1, 1),
                IM_COL32(255, 255, 255, 255), 6.0f);

            if (ImGui::IsItemClicked()) OnAlbumArtClicked();
            if (ImGui::IsItemHovered()) ImGui::SetTooltip("Click to enlarge");
        }
        else
        {
            float offsetX = (sidebarWidth - artSize) * 0.5f;
            ImGui::SetCursorPosX(offsetX);
            ImGui::Button("No Art", ImVec2(artSize, artSize));
        }

        ImGui::Spacing();
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
        // Lightbox
        //==================================================================
        m_lightbox.Draw();
    }

} // namespace moosic