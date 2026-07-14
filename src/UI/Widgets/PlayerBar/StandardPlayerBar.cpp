#include "StandardPlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

    void StandardPlayerBar::Draw()
    {
        //----------------------------------------------------------
        // Row 1: Album Art + Song Information
        //----------------------------------------------------------
        ImGui::BeginGroup();
        DrawAlbumArt();
        ImGui::EndGroup();

        ImGui::SameLine();
        ImGui::BeginGroup();
        DrawSongTitle();
        DrawArtistName();
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
        // Row 3: Visualizer (LEFT) + Controls (RIGHT)
        //----------------------------------------------------------
        constexpr float Gap = 8.0f;
        constexpr float VolumeSliderWidth = 120.0f;

        const auto& visStyle = m_visualizer.GetStyle();
        float visWidth = visStyle.BoxWidth;
        float visHeight = visStyle.BoxHeight;
        float visOffsetX = 6.0f;

        float prevWidth = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float nextWidth = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float repeatWidth = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
        float playWidth = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
        float volWidth = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

        float controlsWidth = prevWidth + Gap + playWidth + Gap + nextWidth + Gap + repeatWidth + Gap + volWidth + Gap + VolumeSliderWidth;
        float availWidth = ImGui::GetContentRegionAvail().x;
        float totalNeeded = visWidth + Gap + controlsWidth;
        float rowY = ImGui::GetCursorPosY();

        if (totalNeeded + visOffsetX <= availWidth)
        {
            ImGui::SetCursorPosX(visOffsetX);
            ImGui::SetCursorPosY(rowY);
            DrawVisualizer();

            ImGui::SameLine(0, Gap);

            float controlsStartX = ImGui::GetCursorPosX();
            float remainingWidth = availWidth - visWidth - Gap - visOffsetX;
            float controlsOffset = (remainingWidth - controlsWidth) * 0.5f;
            if (controlsOffset < 0.0f) controlsOffset = 0.0f;

            ImGui::SetCursorPosX(controlsStartX + controlsOffset);
            ImGui::SetCursorPosY(rowY);

            DrawPreviousButton();
            ImGui::SameLine(0, Gap);
            DrawPlayPauseButton();
            ImGui::SameLine(0, Gap);
            DrawNextButton();
            ImGui::SameLine(0, Gap);
            DrawPlayModeButton();
            ImGui::SameLine(0, Gap);
            DrawVolumeIcon();
            ImGui::SameLine(0, Gap);
            ImGui::SetNextItemWidth(VolumeSliderWidth);
            DrawVolumeSlider();
        }
        else
        {
            float visW = (std::min)(visWidth, availWidth * 0.6f);
            float visOff = (availWidth - visW) * 0.5f;

            ImGui::SetCursorPosX(visOff);
            ImGui::SetCursorPosY(rowY);
            m_visualizer.SetBoxWidth(visW);
            DrawVisualizer();
            m_visualizer.SetBoxWidth(visWidth);

            ImGui::Spacing();

            float playCenterX = availWidth * 0.5f;
            float playOffsetInGroup = prevWidth + Gap + (playWidth * 0.5f);
            float centralStartX = playCenterX - playOffsetInGroup;
            if (centralStartX < 0.0f) centralStartX = 0.0f;

            ImGui::SetCursorPosX(centralStartX);
            DrawPreviousButton();
            ImGui::SameLine(0, Gap);
            DrawPlayPauseButton();
            ImGui::SameLine(0, Gap);
            DrawNextButton();
            ImGui::SameLine(0, Gap);
            DrawPlayModeButton();

            float volumeX = availWidth - VolumeSliderWidth - volWidth - Gap - 10.0f;
            if (volumeX < centralStartX + prevWidth + Gap + playWidth + Gap + nextWidth + Gap + repeatWidth + Gap)
            {
                ImGui::Spacing();
                ImGui::SetCursorPosX((availWidth - volWidth - Gap - VolumeSliderWidth) * 0.5f);
                DrawVolumeIcon();
                ImGui::SameLine(0, Gap);
                ImGui::SetNextItemWidth(VolumeSliderWidth);
                DrawVolumeSlider();
            }
            else
            {
                ImGui::SetCursorPosX(volumeX);
                DrawVolumeIcon();
                ImGui::SameLine(0, Gap);
                ImGui::SetNextItemWidth(VolumeSliderWidth);
                DrawVolumeSlider();
            }
        }

        ImGui::Spacing();
        m_lightbox.Draw();
    }

} // namespace moosic