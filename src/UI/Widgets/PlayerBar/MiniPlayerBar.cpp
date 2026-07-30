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

    //----------------------------------------------------------------------
    // Player Bar Background
    //----------------------------------------------------------------------
    {
        ImVec2 bgPos = ImGui::GetCursorScreenPos();
        bgPos.x -= ImGui::GetStyle().WindowPadding.x;
        float bgWidth = ImGui::GetWindowWidth();
        float bgHeight = ImGui::GetContentRegionAvail().y;
        DrawPlayerBarBackground(bgPos, ImVec2(bgWidth, bgHeight));
    }
    
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4.0f);

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
        m_isSeeking = false;
    PopSliderStyle();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Controls Row
    //--------------------------------------------------------------------------
    float btnWidth = (winWidth - Gap * 4) / 4.0f;

    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    PushPrimaryButtonStyle();
    if (ImGui::Button(Data().isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    const char* modeLabels[] = {"Norm", "Rev", "Rep", "Shuf"};
    PushNormalButtonStyle();
    if (ImGui::Button(modeLabels[static_cast<int>(Data().playbackMode)], ImVec2(btnWidth, 0)))
        OnPlayModeButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
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
    PopSliderStyle();

    ImGui::End();
}

} // namespace moosic