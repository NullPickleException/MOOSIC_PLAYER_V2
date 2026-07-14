//==============================================================================
// TheaterPlayerBar.cpp
//==============================================================================

#include "TheaterPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void TheaterPlayerBar::Draw()
{
    float availWidth = ImGui::GetContentRegionAvail().x;
    float availHeight = ImGui::GetContentRegionAvail().y;

    //==================================================================
    // Large Album Art - centered using AlbumArtBox
    //==================================================================
    float maxArtSize = (std::min)(availWidth * 0.7f, availHeight * 0.65f);
    float artSize = (std::min)(maxArtSize, 400.0f);

    float offsetX = (availWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(offsetX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);

    // Draw with custom size for theater mode, rounded corners, border, background
    m_albumArtBox.Draw(artSize, 8.0f, true, true);
    
    // Handle click for lightbox
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
    {
        OnAlbumArtClicked();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //==================================================================
    // Song Info - centered
    //==================================================================
    float textWidth = (std::min)(availWidth * 0.8f, 500.0f);
    float textOffsetX = (availWidth - textWidth) * 0.5f;

    ImGui::SetCursorPosX(textOffsetX);
    ImGui::PushTextWrapPos(textOffsetX + textWidth);
    ImGui::TextColored(m_theme.TextPrimary, "%s", m_songTitle);
    ImGui::TextColored(m_theme.TextSecondary, "%s", m_artistName);
    ImGui::PopTextWrapPos();

    ImGui::Spacing();

    //==================================================================
    // Progress + Time
    //==================================================================
    ImGui::SetCursorPosX(textOffsetX);
    ImGui::SetNextItemWidth(textWidth);
    PushSliderStyle();
    if (ImGui::SliderFloat("##TheaterProgress", &m_playbackProgress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        if (m_songDuration > 0.0f) m_elapsedTime = m_playbackProgress * m_songDuration;
        OnPlaybackSliderChanged(m_playbackProgress);
    }
    if (!ImGui::IsItemActive() && m_isSeeking)
    {
        m_isSeeking = false;
        if (m_playbackController)
        {
            m_elapsedTime = m_playbackController->GetCurrentPosition();
            m_songDuration = m_playbackController->GetCurrentDuration();
            if (m_songDuration > 0.0f) m_playbackProgress = m_elapsedTime / m_songDuration;
        }
    }
    PopStyle();

    ImGui::SetCursorPosX(textOffsetX);
    int elapsedMin = static_cast<int>(m_elapsedTime) / 60;
    int elapsedSec = static_cast<int>(m_elapsedTime) % 60;
    int totalMin = static_cast<int>(m_songDuration) / 60;
    int totalSec = static_cast<int>(m_songDuration) % 60;
    ImGui::TextColored(m_theme.TextSecondary, "%02d:%02d / %02d:%02d", elapsedMin, elapsedSec, totalMin, totalSec);

    ImGui::Spacing();

    //==================================================================
    // Controls - centered
    //==================================================================
    constexpr float Gap = 8.0f;
    float btnWidth = 44.0f;
    float playWidth = 52.0f;
    float modeWidth = ImGui::CalcTextSize("Shuffle").x + ImGui::GetStyle().FramePadding.x * 2.0f + 10.0f;
    float volSliderWidth = 120.0f;

    float controlsTotalWidth = btnWidth * 2 + playWidth + modeWidth + volSliderWidth + Gap * 5;
    float controlsOffsetX = (availWidth - controlsTotalWidth) * 0.5f;

    ImGui::SetCursorPosX(controlsOffsetX);

    // Previous
    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Play/Pause
    PushPrimaryButtonStyle();
    if (ImGui::Button(m_isPlaying ? "||" : ">", ImVec2(playWidth, 0))) OnPlayPauseButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Next
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Mode
    const char* modeLabels[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
    PushNormalButtonStyle();
    if (ImGui::Button(modeLabels[static_cast<int>(m_playbackMode)], ImVec2(modeWidth, 0)))
        OnPlayModeButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Volume
    ImGui::SetNextItemWidth(volSliderWidth);
    PushSliderStyle();
    float tempVolume = m_volume;
    if (ImGui::SliderFloat("##TheaterVol", &tempVolume, 0.0f, 1.0f, ""))
        OnVolumeSliderChanged(tempVolume);
    PopStyle();

    // Lightbox (on top of everything)
    m_lightbox.Draw();
}

} // namespace moosic