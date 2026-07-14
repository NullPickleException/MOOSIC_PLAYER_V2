#include "StandardPlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

    void StandardPlayerBar::Draw()
    {
        //----------------------------------------------------------
        // Album Art + Song Information
        //----------------------------------------------------------
        ImGui::BeginGroup();
        DrawAlbumArt();
        ImGui::EndGroup();

        ImGui::SameLine();
        ImGui::BeginGroup();
        DrawSongTitle();
        DrawArtistName();
        ImGui::EndGroup();

        //----------------------------------------------------------
        // Playback Timeline
        //----------------------------------------------------------
        float windowWidth = ImGui::GetWindowWidth();
        float padding = 15.0f;

        float elapsedWidth = ImGui::CalcTextSize("00:00").x;
        float totalWidth = ImGui::CalcTextSize("00:00").x;
        float timeTotalWidth = elapsedWidth + totalWidth + 10.0f;

        float sliderWidth = windowWidth - timeTotalWidth - (padding * 2.0f);
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

        ImGui::Spacing();
        ImGui::Spacing();

        //----------------------------------------------------------
        // Playback Controls Row
        //----------------------------------------------------------
        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 160.0f;

        float prevWidth = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
        float volWidth = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

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

        ImGui::Spacing();

        //----------------------------------------------------------
        // Draw Album Art Lightbox (on top of everything)
        //----------------------------------------------------------
        m_lightbox.Draw();
    }

} // namespace moosic