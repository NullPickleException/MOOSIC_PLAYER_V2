//==============================================================================
// UI/Widgets/PlayerBar/StandardPlayerBar.cpp
//==============================================================================

#include "StandardPlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

void StandardPlayerBar::Draw()
{
    constexpr float PLAY_CENTER_OFFSET_X = -6.0f;

    //----------------------------------------------------------------------
    // Row 1: Album Art + Song Information
    //----------------------------------------------------------------------
    ImGui::BeginGroup();
    DrawAlbumArt();
    ImGui::EndGroup();

    ImGui::SameLine();

    float availWidth = ImGui::GetContentRegionAvail().x;
    float textMaxWidth = availWidth * 0.8f;

    bool trackChanged = Data().trackJustChanged;

    ImGui::BeginGroup();
    DrawScrollingText(Data().title.c_str(), m_theme.TextPrimary, textMaxWidth,
                      m_titleScrollOffset, m_lastTrackChangeTime, trackChanged);
    DrawScrollingText(Data().artist.c_str(), m_theme.TextSecondary, textMaxWidth,
                      m_artistScrollOffset, m_lastTrackChangeTime, trackChanged);
    ImGui::EndGroup();

    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Row 2: Playback Timeline
    //----------------------------------------------------------------------
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

    //----------------------------------------------------------------------
    // Row 3: Controls
    //----------------------------------------------------------------------
    constexpr float Gap = 8.0f;
    constexpr float VolumeSliderWidth = 160.0f;

    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = visStyle.BoxWidth;
    float visHeight = visStyle.BoxHeight;
    float visOffsetX = 6.0f;

    float prevWidth = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float nextWidth = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float repeatWidth = ImGui::CalcTextSize(Data().modeLabel.c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float playWidth = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
    float volBtnWidth = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

    float playCenterX = sliderCenterX + PLAY_CENTER_OFFSET_X;
    float leftOfPlayCenter = prevWidth + Gap + playWidth * 0.5f;
    float rightOfPlayCenter = playWidth * 0.5f + Gap + nextWidth + Gap + repeatWidth;
    float controlsGroupWidth = leftOfPlayCenter + rightOfPlayCenter;
    float volumeSectionWidth = volBtnWidth + Gap + VolumeSliderWidth;

    float rowY = ImGui::GetCursorPosY();
    float rightMargin = ImGui::GetStyle().WindowPadding.x + 10.0f;

    float controlsStartX = playCenterX - leftOfPlayCenter;
    float controlsEndX = controlsStartX + controlsGroupWidth;

    availWidth = ImGui::GetContentRegionAvail().x;

    //----------------------------------------------------------------------
    // CASE 1: All on one row
    //----------------------------------------------------------------------
    if (controlsEndX + Gap + volumeSectionWidth <= windowWidth - rightMargin)
    {
        float baseY = ImGui::GetCursorPosY();
        float centerLine = baseY + visHeight * 0.5f;

        ImGui::SetCursorPosX(visOffsetX);
        ImGui::SetCursorPosY(baseY);
        DrawVisualizer();

        float btnHeight = ImGui::GetFrameHeight();
        float controlsY = centerLine - btnHeight * 0.5f;

        ImGui::SetCursorPosX(controlsStartX);
        ImGui::SetCursorPosY(controlsY);
        DrawPreviousButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap);
        ImGui::SetCursorPosY(controlsY);
        DrawPlayPauseButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap + playWidth + Gap);
        ImGui::SetCursorPosY(controlsY);
        DrawNextButton();

        ImGui::SetCursorPosX(controlsStartX + prevWidth + Gap + playWidth + Gap + nextWidth + Gap);
        ImGui::SetCursorPosY(controlsY);
        DrawPlayModeButton();

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
    //----------------------------------------------------------------------
    // CASE 2: Volume wraps to next row
    //----------------------------------------------------------------------
    else if (visWidth + Gap + controlsGroupWidth + visOffsetX <= availWidth)
    {
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

        ImGui::Spacing();
        float volumeStartX = windowWidth - volumeSectionWidth - rightMargin;
        ImGui::SetCursorPosX(volumeStartX);
        ImGui::SetCursorPosY(rowY + 25.0f);
        DrawVolumeIcon();
        ImGui::SameLine(0, Gap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }
    //----------------------------------------------------------------------
    // CASE 3: Visualizer + Volume wrap
    //----------------------------------------------------------------------
    else
    {
        float visW = (std::min)(visWidth, availWidth * 0.6f);
        float visOff = (availWidth - visW) * 0.5f;

        ImGui::SetCursorPosX(visOff);
        ImGui::SetCursorPosY(rowY);
        m_visualizer.SetBoxWidth(visW);
        DrawVisualizer();
        m_visualizer.SetBoxWidth(visWidth);

        float playStartX = playCenterX - playWidth * 0.5f;
        float ctrlStartX = playStartX - prevWidth - Gap;
        if (ctrlStartX < 0.0f) ctrlStartX = 0.0f;

        ImGui::SetCursorPosX(ctrlStartX);
        DrawPreviousButton();
        ImGui::SameLine(0, Gap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, Gap);
        DrawNextButton();
        ImGui::SameLine(0, Gap);
        DrawPlayModeButton();

        float volumeStartX = windowWidth - volumeSectionWidth - rightMargin;
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