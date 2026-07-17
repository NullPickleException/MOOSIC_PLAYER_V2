#include "StandardArtLeftPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void StandardArtLeftPlayerBar::Draw()
{
    //----------------------------------------------------------
    // FINE-TUNE OFFSET: Adjust this to nudge play button X
    //----------------------------------------------------------
    constexpr float PLAY_CENTER_OFFSET_X = -4.0f;

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

    // Song Info - Scrolling text
    bool trackChanged = (m_lastTrackId != (m_playbackController ? 
                         m_playbackController->GetCurrentTrack() ? 
                         m_playbackController->GetCurrentTrack()->GetId() : 0 : 0));
    
    DrawScrollingText(m_songTitle, m_theme.TextPrimary, rightWidth, 
                      m_titleScrollOffset, m_lastTrackChangeTime, trackChanged);
    DrawScrollingText(m_artistName, m_theme.TextSecondary, rightWidth, 
                      m_artistScrollOffset, m_lastTrackChangeTime, trackChanged);
    
    ImGui::Spacing();

    // Measurements
    constexpr float ControlGap = 6.0f;
    constexpr float SectionGap = 12.0f;
    constexpr float VolumeSliderWidth = 90.0f;
    float timeWidth = ImGui::CalcTextSize("00:00").x;

    float prevW = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float playW = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
    float nextW = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float modeW = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float volBtnW = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

    // Playback Slider
    float sliderWidth = rightWidth - (timeWidth * 2) - 20.0f;
    if (sliderWidth < 100.0f) sliderWidth = 100.0f;
    float sliderRowWidth = timeWidth + 10.0f + sliderWidth + 10.0f + timeWidth;
    float sliderOffset = (rightWidth - sliderRowWidth) * 0.5f;
    if (sliderOffset < 0) sliderOffset = 0;

    float sliderStartX_rel = sliderOffset + timeWidth + 10.0f;
    float sliderCenterX_rel = sliderStartX_rel + sliderWidth * 0.5f;
    float playCenterX = sliderCenterX_rel + PLAY_CENTER_OFFSET_X;

    ImGui::SetCursorPosX(rightStartX + sliderOffset);
    DrawElapsedTime();
    ImGui::SameLine(0, 10.0f);
    ImGui::SetNextItemWidth(sliderWidth);
    DrawPlaybackSlider();
    ImGui::SameLine(0, 10.0f);
    DrawTotalTime();
    ImGui::Spacing();

    //----------------------------------------------------------
    // Controls
    //----------------------------------------------------------
    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = visStyle.BoxWidth;
    float visHeight = visStyle.BoxHeight;
    float visOffsetX = 4.0f;

    float leftOfPlayCenter = prevW + ControlGap + playW * 0.5f;
    float rightOfPlayCenter = playW * 0.5f + ControlGap + nextW + ControlGap + modeW;
    float controlsGroupWidth = leftOfPlayCenter + rightOfPlayCenter;
    float volumeSectionWidth = volBtnW + ControlGap + VolumeSliderWidth;
    float rowY = ImGui::GetCursorPosY();

    //==================================================================
    // CASE 1: All on one row
    //==================================================================
    float allOnOneRow = visWidth + SectionGap + controlsGroupWidth + SectionGap + volumeSectionWidth + visOffsetX;
    constexpr float EXTRA_PADDING = 20.0f;

    if (allOnOneRow + EXTRA_PADDING <= rightWidth)
    {
        ImGui::SetCursorPosX(rightStartX + visOffsetX);
        ImGui::SetCursorPosY(rowY);
        DrawVisualizer();

        ImGui::SameLine(0, SectionGap);

        float controlsStartX = rightStartX + playCenterX - leftOfPlayCenter;
        float minControlsX = rightStartX + visOffsetX + visWidth + SectionGap;
        if (controlsStartX < minControlsX) controlsStartX = minControlsX;

        ImGui::SetCursorPosX(controlsStartX);
        ImGui::SetCursorPosY(rowY);

        DrawPreviousButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, ControlGap);
        DrawNextButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayModeButton();

        float volumeStartX = rightStartX + rightWidth - volumeSectionWidth - 8.0f;
        float controlsEndX = controlsStartX + controlsGroupWidth;
        if (volumeStartX < controlsEndX + SectionGap)
            volumeStartX = controlsEndX + SectionGap;

        ImGui::SetCursorPosX(volumeStartX);
        ImGui::SetCursorPosY(rowY);
        DrawVolumeIcon();
        ImGui::SameLine(0, ControlGap);
        ImGui::SetNextItemWidth(VolumeSliderWidth);
        DrawVolumeSlider();
    }
    //==================================================================
    // CASE 2: Visualizer left, volume under, controls right
    //==================================================================
    else
    {
        float visColumnWidth = (std::min)(visWidth, rightWidth * 0.35f);
        float visColumnX = rightStartX + visOffsetX;

        ImGui::SetCursorPosX(visColumnX);
        ImGui::SetCursorPosY(rowY);
        m_visualizer.SetBoxWidth(visColumnWidth);
        DrawVisualizer();
        m_visualizer.SetBoxWidth(visWidth);

        float remainingForControls = rightWidth - visColumnWidth - SectionGap - visOffsetX;
        float controlsStartX = visColumnX + visColumnWidth + SectionGap;
        float controlsOffsetInRemaining = (remainingForControls - controlsGroupWidth) * 0.5f;
        if (controlsOffsetInRemaining > 0) controlsStartX += controlsOffsetInRemaining;

        float controlsY = rowY + (visHeight - ImGui::GetFrameHeight()) * 0.5f;

        ImGui::SetCursorPosX(controlsStartX);
        ImGui::SetCursorPosY(controlsY);

        DrawPreviousButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayPauseButton();
        ImGui::SameLine(0, ControlGap);
        DrawNextButton();
        ImGui::SameLine(0, ControlGap);
        DrawPlayModeButton();

        // Volume under visualizer
        ImGui::SetCursorPosX(visColumnX);
        ImGui::SetCursorPosY(rowY + visHeight + 4.0f);

        float volSliderWidth = visColumnWidth - volBtnW - ControlGap;
        if (volSliderWidth < 60.0f) volSliderWidth = 60.0f;

        DrawVolumeIcon();
        ImGui::SameLine(0, ControlGap);
        ImGui::SetNextItemWidth(volSliderWidth);
        DrawVolumeSlider();
    }

    ImGui::EndGroup();
    m_lightbox.Draw();
}

} // namespace moosic