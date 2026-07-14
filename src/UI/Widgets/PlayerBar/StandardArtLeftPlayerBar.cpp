//==============================================================================
// StandardArtLeftPlayerBar.cpp
//==============================================================================

#include "StandardArtLeftPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void StandardArtLeftPlayerBar::Draw()
{
    float availWidth = ImGui::GetContentRegionAvail().x;

    //----------------------------------------------------------
    // Album Art - Left Column
    //----------------------------------------------------------
    constexpr float ArtColumnWidth = 150.0f;
    constexpr float Gap = 12.0f;
    float artSize = ArtColumnWidth - 4.0f;

    ImGui::BeginGroup();
    m_albumArtBox.Draw(artSize, 4.0f, true, true);
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        OnAlbumArtClicked();
    ImGui::EndGroup();

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Gap);

    //----------------------------------------------------------
    // Right Panel
    //----------------------------------------------------------
    ImGui::BeginGroup();
    float rightWidth = availWidth - ArtColumnWidth - Gap - 10.0f;
    float rightStartX = ImGui::GetCursorPosX();

    // Song Info
    DrawSongTitle();
    DrawArtistName();
    ImGui::Spacing();

    // Measurements
    constexpr float ControlGap = 8.0f;
    constexpr float VolumeSliderWidth = 120.0f;
    float timeWidth = ImGui::CalcTextSize("00:00").x;

    float prevW = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float playW = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
    float nextW = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float modeW = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float volBtnW = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float controlsTotalWidth = prevW + ControlGap + playW + ControlGap + nextW + ControlGap + modeW + ControlGap + volBtnW + ControlGap + VolumeSliderWidth;

    // Playback Slider
    float sliderWidth = rightWidth - (timeWidth * 2) - 20.0f;
    if (sliderWidth < 100.0f) sliderWidth = 100.0f;
    float sliderRowWidth = timeWidth + 10.0f + sliderWidth + 10.0f + timeWidth;
    float sliderOffset = (rightWidth - sliderRowWidth) * 0.5f;
    if (sliderOffset < 0) sliderOffset = 0;

    ImGui::SetCursorPosX(rightStartX + sliderOffset);
    DrawElapsedTime();
    ImGui::SameLine(0, 10.0f);
    ImGui::SetNextItemWidth(sliderWidth);
    DrawPlaybackSlider();
    ImGui::SameLine(0, 10.0f);
    DrawTotalTime();
    ImGui::Spacing();

    //----------------------------------------------------------
    // Visualizer (LEFT) + Controls (RIGHT) - SAME ROW like Standard
    //----------------------------------------------------------
    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = visStyle.BoxWidth;
    float visHeight = visStyle.BoxHeight;
    float visOffsetX = 6.0f;

    float totalNeeded = visWidth + ControlGap + controlsTotalWidth;
    float rowY = ImGui::GetCursorPosY();

    if (totalNeeded + visOffsetX <= rightWidth)
    {
        // Visualizer LEFT | Controls RIGHT (same row)
        ImGui::SetCursorPosX(rightStartX + visOffsetX);
        ImGui::SetCursorPosY(rowY);
        DrawVisualizer();

        ImGui::SameLine(0, ControlGap);

        float remainingForControls = rightWidth - visWidth - ControlGap - visOffsetX;
        float controlsOffset = (remainingForControls - controlsTotalWidth) * 0.5f;
        if (controlsOffset < 0.0f) controlsOffset = 0.0f;

        ImGui::SetCursorPosX(rightStartX + visWidth + ControlGap + visOffsetX + controlsOffset);
        ImGui::SetCursorPosY(rowY);

        DrawPreviousButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, ControlGap);
        DrawNextButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayModeButton();
        ImGui::SameLine(0, ControlGap + 4.0f);
        DrawVolumeIcon();
        ImGui::SameLine(0, ControlGap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }
    else
    {
        // Not enough space - Visualizer on its own row above controls
        float visW = (std::min)(visWidth, rightWidth * 0.6f);
        float visOff = rightStartX + (rightWidth - visW) * 0.5f;

        ImGui::SetCursorPosX(visOff);
        ImGui::SetCursorPosY(rowY);
        m_visualizer.SetBoxWidth(visW);
        DrawVisualizer();
        m_visualizer.SetBoxWidth(visWidth);

        ImGui::Spacing();

        // Controls centered on next row
        float sliderStartX = rightStartX + sliderOffset + timeWidth + 10.0f;
        float sliderCenterX = sliderStartX + sliderWidth * 0.5f;
        float playHalfW = playW * 0.5f;
        float controlsStartX = sliderCenterX - playHalfW - prevW - ControlGap;

        if (controlsStartX < rightStartX) controlsStartX = rightStartX;
        float controlsEndX = controlsStartX + controlsTotalWidth;
        if (controlsEndX > rightStartX + rightWidth)
            controlsStartX = rightStartX + rightWidth - controlsTotalWidth;
        if (controlsStartX < rightStartX) controlsStartX = rightStartX;

        ImGui::SetCursorPosX(controlsStartX);
        DrawPreviousButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, ControlGap);
        DrawNextButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayModeButton();
        ImGui::SameLine(0, ControlGap + 4.0f);
        DrawVolumeIcon();
        ImGui::SameLine(0, ControlGap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }

    ImGui::EndGroup();
    m_lightbox.Draw();
}

} // namespace moosic