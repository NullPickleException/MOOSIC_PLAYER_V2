//==============================================================================
// UI/Widgets/PlayerBar/MiniPlayerBar.cpp
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

    //--------------------------------------------------------------------------
    // Song Info
    //--------------------------------------------------------------------------
    ImGui::PushTextWrapPos(winWidth);
    ImGui::TextColored(m_theme.TextPrimary, "%s", Data().title.c_str());
    ImGui::TextColored(m_theme.TextSecondary, "%s", Data().artist.c_str());
    ImGui::PopTextWrapPos();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Progress Bar
    //--------------------------------------------------------------------------
    ImGui::SetNextItemWidth(winWidth);
    PushSliderStyle();
    float progress = Data().progress;
    if (ImGui::SliderFloat("##MiniProgress", &progress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        OnPlaybackSliderChanged(progress);
    }
    if (!ImGui::IsItemActive() && m_isSeeking)
    {
        m_isSeeking = false;
    }
    PopStyle();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Controls Row
    //--------------------------------------------------------------------------
    float btnWidth = (winWidth - Gap * 4) / 4.0f;

    // Previous
    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Play/Pause
    PushPrimaryButtonStyle();
    if (ImGui::Button(Data().isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Next
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Mode
    const char* modeLabels[] = {"Norm", "Rev", "Rep", "Shuf"};
    PushNormalButtonStyle();
    if (ImGui::Button(modeLabels[static_cast<int>(Data().playbackMode)], ImVec2(btnWidth, 0)))
        OnPlayModeButtonPressed();
    PopStyle();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Volume
    //--------------------------------------------------------------------------
    ImGui::SetNextItemWidth(winWidth);
    PushSliderStyle();
    float tempVolume = Data().volume;
    if (ImGui::SliderFloat("##MiniVol", &tempVolume, 0.0f, 1.0f, "Vol: %.2f"))
        OnVolumeSliderChanged(tempVolume);
    PopStyle();

    ImGui::End();
}

} // namespace moosic