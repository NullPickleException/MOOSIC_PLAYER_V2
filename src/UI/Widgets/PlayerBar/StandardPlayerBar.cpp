#include "StandardPlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

    void StandardPlayerBar::Draw()
    {
        //----------------------------------------------------------
        // FINE-TUNE OFFSET: Adjust this to nudge play button X
        // Positive = right, Negative = left
        //----------------------------------------------------------
        constexpr float PLAY_CENTER_OFFSET_X = -6.0f;

        //----------------------------------------------------------
        // Row 1: Album Art + Song Information
        //----------------------------------------------------------
        ImGui::BeginGroup();
        DrawAlbumArt();
        ImGui::EndGroup();

        ImGui::SameLine();

        // Song Info - Scrolling text
        float availWidth = ImGui::GetContentRegionAvail().x;
        float textMaxWidth = availWidth * 0.8f;

        std::size_t currentTrackId = m_playbackController ? (m_playbackController->GetCurrentTrack() ? m_playbackController->GetCurrentTrack()->GetId() : 0) : 0;
        bool trackChanged = (currentTrackId != m_lastTrackId && currentTrackId != 0);

        ImGui::BeginGroup();
        DrawScrollingText(m_songTitle, m_theme.TextPrimary, textMaxWidth,
                          m_titleScrollOffset, m_lastTrackChangeTime, trackChanged);
        DrawScrollingText(m_artistName, m_theme.TextSecondary, textMaxWidth,
                          m_artistScrollOffset, m_lastTrackChangeTime, trackChanged);
        ImGui::EndGroup();

        ImGui::Spacing();

        //----------------------------------------------------------
        // Row 2: Playback Timeline
        //----------------------------------------------------------
        float windowWidth = ImGui::GetWindowWidth();
        float padding = 15.0f;

        float elapsedWidth = ImGui::CalcTextSize("00:00").x;
        float totalWidth = ImGui::CalcTextSize("00:00").x;

        float sliderWidth = windowWidth - elapsedWidth - totalWidth - (padding * 4.0f);
        if (sliderWidth < 100.0f)
            sliderWidth = 100.0f;

        float sliderStartX = padding + elapsedWidth + padding;
        float sliderCenterX = sliderStartX + sliderWidth * 0.5f;

        ImGui::SetCursorPosX(padding);
        DrawElapsedTime();

        ImGui::SameLine();
        ImGui::SetNextItemWidth(sliderWidth);
        DrawPlaybackSlider();

        ImGui::SameLine();
        ImGui::SetCursorPosX(windowWidth - totalWidth - padding);
        DrawTotalTime();

        ImGui::Spacing();

        //----------------------------------------------------------
        // Row 3: Controls
        //----------------------------------------------------------
        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 160.0f;

        const auto &visStyle = m_visualizer.GetStyle();
        float visWidth = visStyle.BoxWidth;
        float visHeight = visStyle.BoxHeight;
        float visOffsetX = 6.0f;

        float prevWidth = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
        float volBtnWidth = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

        float playCenterX = sliderCenterX + PLAY_CENTER_OFFSET_X;
        float leftOfPlayCenter = prevWidth + Gap + playWidth * 0.5f;
        float rightOfPlayCenter = playWidth * 0.5f + Gap + nextWidth + Gap + repeatWidth;
        float controlsGroupWidth = leftOfPlayCenter + rightOfPlayCenter;
        float volumeSectionWidth = volBtnWidth + Gap + VolumeSliderWidth;

        float rowY = ImGui::GetCursorPosY();
        float rightMargin = ImGui::GetStyle().WindowPadding.x + 10.0f;
        float volumeYOffset = 0.0f;

        // Recapture availWidth here for accurate case switching
        availWidth = ImGui::GetContentRegionAvail().x;

        // Calculate the actual end X of the controls (repeat button right edge)
        float controlsStartX = playCenterX - leftOfPlayCenter;
        float controlsEndX = controlsStartX + controlsGroupWidth;
        float volumeStartX = windowWidth - volumeSectionWidth - rightMargin;

     //==================================================================
    // CASE 1: All on one row - PROPER CENTER ALIGNMENT
    //==================================================================
    if (controlsEndX + Gap + volumeSectionWidth <= windowWidth - rightMargin)
    {
        float baseY = ImGui::GetCursorPosY();
        
        // Target center line for all elements
        float centerLine = baseY + visHeight * 0.5f;

        // 1. Visualizer
        ImGui::SetCursorPosX(visOffsetX);
        ImGui::SetCursorPosY(baseY);                    // Visualizer starts at base
        DrawVisualizer();

        // 2. Playback Controls (centered)
        float btnHeight = ImGui::GetFrameHeight();
        float controlsY = centerLine - btnHeight * 0.5f;

        ImGui::SetCursorPosX(controlsStartX);
        ImGui::SetCursorPosY(controlsY);
        DrawPreviousButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap);   // manual positioning
        ImGui::SetCursorPosY(controlsY);
        DrawPlayPauseButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap + playWidth + Gap);
        ImGui::SetCursorPosY(controlsY);
        DrawNextButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap + playWidth + Gap + nextWidth + Gap);
        ImGui::SetCursorPosY(controlsY);
        DrawPlayModeButton();

        // 3. Volume Section (centered)
        float volX = controlsEndX + Gap;
        if (volX + volumeSectionWidth > windowWidth - ImGui::GetStyle().WindowPadding.x)
            volX = windowWidth - volumeSectionWidth - ImGui::GetStyle().WindowPadding.x;

        float volumeY = centerLine - btnHeight * 0.5f;

        ImGui::SetCursorPosX(volX);
        ImGui::SetCursorPosY(volumeY);
        DrawVolumeIcon();

        ImGui::SetCursorPosX(volX + volBtnWidth + Gap);
        ImGui::SetCursorPosY(volumeY);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }
        //==================================================================
        // CASE 2: Volume wraps to next row
        //==================================================================
        else if (visWidth + Gap + controlsGroupWidth + visOffsetX <= availWidth)
        {
            // Row A: Visualizer + Playback Controls
            ImGui::SetCursorPosX(visOffsetX);
            ImGui::SetCursorPosY(rowY);
            DrawVisualizer();

            ImGui::SameLine(0, Gap);

            ImGui::SetCursorPosX(controlsStartX);
            ImGui::SetCursorPosY(rowY);

            DrawPreviousButton();
            ImGui::SameLine(0, Gap);
            DrawPlayPauseButton();
            ImGui::SameLine(0, Gap);
            DrawNextButton();
            ImGui::SameLine(0, Gap);
            DrawPlayModeButton();

            // Row B: Volume slider only - anchored to right edge of window
            ImGui::Spacing();
            ImGui::SetCursorPosX(volumeStartX - 0.0f);
            ImGui::SetCursorPosY(rowY + volumeYOffset + 25.0f);
            DrawVolumeIcon();
            ImGui::SameLine(0, Gap);
            ImGui::SetNextItemWidth(VolumeSliderWidth);
            DrawVolumeSlider();
        }
        //==================================================================
        // CASE 3: Visualizer + Volume wrap
        //==================================================================
        else
        {
            // Row A: Visualizer (squeezed)
            float visW = (std::min)(visWidth, availWidth * 0.6f);
            float visOff = (availWidth - visW) * 0.5f;

            ImGui::SetCursorPosX(visOff);
            ImGui::SetCursorPosY(rowY);
            m_visualizer.SetBoxWidth(visW);
            DrawVisualizer();
            m_visualizer.SetBoxWidth(visWidth);

            // Row B: Controls and Volume on same row
            float playStartX = playCenterX - playWidth * 0.5f;
            float ctrlStartX = playStartX - prevWidth - Gap;
            if (ctrlStartX < 0.0f)
                ctrlStartX = 0.0f;

            ImGui::SetCursorPosX(ctrlStartX);
            DrawPreviousButton();
            ImGui::SameLine(0, Gap);
            DrawPlayPauseButton();
            ImGui::SameLine(0, Gap);
            DrawNextButton();
            ImGui::SameLine(0, Gap);
            DrawPlayModeButton();

            // Volume - anchored to right edge of window (on same row as controls)
            ImGui::SameLine();
            ImGui::SetCursorPosX(volumeStartX);
            DrawVolumeIcon();
            ImGui::SameLine(0, Gap);
            ImGui::SetNextItemWidth(VolumeSliderWidth);
            DrawVolumeSlider();
        }

        ImGui::Spacing();
        m_lightbox.Draw();
    }

} // namespace moosic