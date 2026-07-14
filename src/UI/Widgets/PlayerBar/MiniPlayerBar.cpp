//==============================================================================
// MiniPlayerBar.cpp
//==============================================================================

#include "MiniPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void MiniPlayerBar::Draw()
{
    if (!m_open) return;

    ImGui::SetNextWindowSize(ImVec2(320, 140), ImGuiCond_FirstUseEver);
    
    ImGuiWindowFlags flags = ImGuiWindowFlags_NoSavedSettings;
    
    if (!ImGui::Begin("Mini Player", &m_open, flags))
    {
        ImGui::End();
        return;
    }

    float winWidth = ImGui::GetContentRegionAvail().x;
    constexpr float Gap = 4.0f;

    // Song info
    ImGui::PushTextWrapPos(winWidth);
    ImGui::TextColored(m_theme.TextPrimary, "%s", m_songTitle);
    ImGui::TextColored(m_theme.TextSecondary, "%s", m_artistName);
    ImGui::PopTextWrapPos();

    ImGui::Spacing();

    // Progress bar
    ImGui::SetNextItemWidth(winWidth);
    PushSliderStyle();
    if (ImGui::SliderFloat("##MiniProgress", &m_playbackProgress, 0.0f, 1.0f, ""))
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

    ImGui::Spacing();

    // Controls row
    float btnWidth = (winWidth - Gap * 4) / 4.0f;
    float volWidth = btnWidth * 1.5f;

    // Previous
    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Play/Pause
    PushPrimaryButtonStyle();
    if (ImGui::Button(m_isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Next
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Shuffle/Repeat
    const char* modeLabels[] = {"Norm", "Rev", "Rep", "Shuf"};
    PushNormalButtonStyle();
    if (ImGui::Button(modeLabels[static_cast<int>(m_playbackMode)], ImVec2(btnWidth, 0)))
        OnPlayModeButtonPressed();
    PopStyle();

    ImGui::Spacing();

    // Volume
    ImGui::SetNextItemWidth(winWidth);
    PushSliderStyle();
    float tempVolume = m_volume;
    if (ImGui::SliderFloat("##MiniVol", &tempVolume, 0.0f, 1.0f, "Vol: %.2f"))
        OnVolumeSliderChanged(tempVolume);
    PopStyle();

    ImGui::End();
}

} // namespace moosic