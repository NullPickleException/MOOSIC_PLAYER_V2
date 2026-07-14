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
    // Album Art
    //----------------------------------------------------------
    constexpr float ArtColumnWidth = 150.0f;
    constexpr float Gap = 12.0f;

    float savedArtSize = m_theme.AlbumArtSize;
    m_theme.AlbumArtSize = ArtColumnWidth - 4.0f;

    ImGui::BeginGroup();
    DrawAlbumArt();
    ImGui::EndGroup();

    m_theme.AlbumArtSize = savedArtSize;

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + Gap);

    //----------------------------------------------------------
    // Right Side
    //----------------------------------------------------------
    ImGui::BeginGroup();

    float rightWidth = availWidth - ArtColumnWidth - Gap - 10.0f;

    //----------------------------------------------------------
    // Song Info
    //----------------------------------------------------------
    DrawSongTitle();
    DrawArtistName();

    ImGui::Spacing();

    //----------------------------------------------------------
    // Measurements
    //----------------------------------------------------------
    constexpr float ControlGap = 8.0f;
    constexpr float VolumeSliderWidth = 120.0f;

    float timeWidth = ImGui::CalcTextSize("00:00").x;

    float prevW = ImGui::CalcTextSize("<<").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float playW = ImGui::CalcTextSize(" || ").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.PrimaryButtonExtraWidth;
    float nextW = ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float modeW = ImGui::CalcTextSize("Repeat").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;
    float volBtnW = ImGui::CalcTextSize("Vol").x + ImGui::GetStyle().FramePadding.x * 2.0f + m_theme.NormalButtonExtraWidth;

    // Controls group: Prev | Play | Next | Mode | VolBtn | VolSlider
    float controlsWidth = prevW + ControlGap + playW + ControlGap + nextW + ControlGap + modeW + ControlGap + volBtnW + ControlGap + VolumeSliderWidth;

    //----------------------------------------------------------
    // Playback Slider - stretch to fill rightWidth, times on sides
    //----------------------------------------------------------
    float sliderWidth = rightWidth - (timeWidth * 2) - 20.0f;
    if (sliderWidth < 100.0f) sliderWidth = 100.0f;

    float sliderRowWidth = timeWidth + 10.0f + sliderWidth + 10.0f + timeWidth;
    float sliderOffset = (rightWidth - sliderRowWidth) * 0.5f;
    if (sliderOffset < 0) sliderOffset = 0;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + sliderOffset);
    DrawElapsedTime();
    ImGui::SameLine(0, 10.0f);
    ImGui::SetNextItemWidth(sliderWidth);
    DrawPlaybackSlider();
    ImGui::SameLine(0, 10.0f);
    DrawTotalTime();

    ImGui::Spacing();

    //----------------------------------------------------------
    // Controls Row - Play button at center X of slider
    //----------------------------------------------------------
    // Find center of slider in screen space
    float sliderCenterX = ImGui::GetCursorPosX() + sliderOffset + timeWidth + 10.0f + sliderWidth * 0.5f;
    // Play button half-width
    float playHalfW = playW * 0.5f;
    // Start X so play button is centered on slider center
    float controlsStartX = sliderCenterX - playHalfW - prevW - ControlGap;
    float controlsEndX = controlsStartX + controlsWidth;

    // Clamp if it goes offscreen
    float cursorX = ImGui::GetCursorPosX();
    if (controlsStartX < cursorX) controlsStartX = cursorX;
    if (controlsEndX > cursorX + rightWidth) controlsStartX = cursorX + rightWidth - controlsWidth;

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

    ImGui::EndGroup();

    m_lightbox.Draw();
}

} // namespace moosic