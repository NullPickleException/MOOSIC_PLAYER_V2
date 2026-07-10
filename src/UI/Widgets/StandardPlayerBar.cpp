#include "StandardPlayerBar.h"
#include <imgui.h>

namespace moosic
{

    void StandardPlayerBar::Draw()
    {
        //----------------------------------------------------------
        // Album + Song Information
        //----------------------------------------------------------
        DrawAlbumArt();
        ImGui::SameLine();
        ImGui::BeginGroup();
        DrawSongTitle();
        DrawArtistName();
        ImGui::EndGroup();

        ImGui::Spacing();
        ImGui::Spacing();

        //----------------------------------------------------------
        // Playback Timeline - FIXED
        //----------------------------------------------------------
        float windowWidth = ImGui::GetWindowWidth();
        float padding = 15.0f;

        // Get text sizes
        float elapsedWidth = ImGui::CalcTextSize("00:00").x;
        float totalWidth = ImGui::CalcTextSize("00:00").x;
        float timeTotalWidth = elapsedWidth + totalWidth + 10.0f;

        float sliderWidth = windowWidth - timeTotalWidth - (padding * 2.0f);
        if (sliderWidth < 100.0f)
            sliderWidth = 100.0f;

        // Elapsed time (left side)
        ImGui::SetCursorPosX(padding);
        DrawElapsedTime();

        // Slider (center)
        ImGui::SameLine();
        ImGui::SetNextItemWidth(sliderWidth);
        DrawPlaybackSlider();

        // Total duration (right side) - FIXED: shows total duration, not elapsed
        ImGui::SameLine();
        ImGui::SetCursorPosX(windowWidth - totalWidth - padding);
        DrawTotalTime();

        ImGui::Spacing();
        ImGui::Spacing();

        //----------------------------------------------------------
        // Playback Controls Row
        //----------------------------------------------------------
        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 160.0f;

        // Get button widths
        float prevWidth = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
        float volWidth = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

        float centralGroupWidth = prevWidth + Gap + playWidth + Gap + nextWidth + Gap + repeatWidth;
        float volumeSectionWidth = volWidth + Gap + VolumeSliderWidth;

        float availWidth = ImGui::GetContentRegionAvail().x;

        // Save current Y position before drawing controls
        float controlsY = ImGui::GetCursorPosY();

        // Calculate start position so Play button is centered
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

        // Draw controls
        DrawPreviousButton();
        ImGui::SameLine(0, Gap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, Gap);
        DrawNextButton();
        ImGui::SameLine(0, Gap);
        DrawPlayModeButton();

        //----------------------------------------------------------
        // Volume (Same Row)
        //----------------------------------------------------------
        float volumeX = availWidth - volumeSectionWidth;
        ImGui::SetCursorPosX(volumeX);
        ImGui::SetCursorPosY(controlsY);
        DrawVolumeIcon();
        ImGui::SameLine(0, Gap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();

        ImGui::Spacing();
    }
}