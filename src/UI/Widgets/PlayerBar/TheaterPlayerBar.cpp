//==============================================================================
// UI/Widgets/PlayerBar/TheaterPlayerBar.cpp
//==============================================================================

#include "TheaterPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void TheaterPlayerBar::Draw()
{
    float availWidth = ImGui::GetContentRegionAvail().x;
    float availHeight = ImGui::GetContentRegionAvail().y;

    //--------------------------------------------------------------------------
    // Large Album Art - Centered
    //--------------------------------------------------------------------------
    float maxArtSize = (std::min)(availWidth * 0.7f, availHeight * 0.65f);
    float artSize = (std::min)(maxArtSize, 400.0f);

    if (Data().trackJustChanged)
        m_artLoadAttempted = false;
    LoadAlbumArtForCurrentTrack();

    float offsetX = (availWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(offsetX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20.0f);

    m_albumArtBox.Draw(artSize, 8.0f, true, true);
    
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
    {
        OnAlbumArtClicked();
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Song Info - Centered
    //--------------------------------------------------------------------------
    float textWidth = (std::min)(availWidth * 0.8f, 500.0f);
    float textOffsetX = (availWidth - textWidth) * 0.5f;

    ImGui::SetCursorPosX(textOffsetX);
    ImGui::PushTextWrapPos(textOffsetX + textWidth);
    ImGui::TextColored(m_theme.TextPrimary, "%s", Data().title.c_str());
    ImGui::TextColored(m_theme.TextSecondary, "%s", Data().artist.c_str());
    ImGui::PopTextWrapPos();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Progress + Time
    //--------------------------------------------------------------------------
    ImGui::SetCursorPosX(textOffsetX);
    ImGui::SetNextItemWidth(textWidth);
    PushSliderStyle();
    float progress = Data().progress;
    if (ImGui::SliderFloat("##TheaterProgress", &progress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        OnPlaybackSliderChanged(progress);
    }
    if (!ImGui::IsItemActive() && m_isSeeking)
    {
        m_isSeeking = false;
    }
    PopStyle();

    ImGui::SetCursorPosX(textOffsetX);
    ImGui::TextColored(m_theme.TextSecondary, "%s / %s",
                       Data().elapsedFormatted.c_str(), Data().totalFormatted.c_str());

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Controls - Centered
    //--------------------------------------------------------------------------
    constexpr float Gap = 8.0f;
    float btnWidth = 44.0f;
    float playWidth = 52.0f;
    float modeWidth = ImGui::CalcTextSize(Data().modeLabel.c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f + 10.0f;
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
    if (ImGui::Button(Data().isPlaying ? "||" : ">", ImVec2(playWidth, 0))) OnPlayPauseButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Next
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Mode
    PushNormalButtonStyle();
    if (ImGui::Button(Data().modeLabel.c_str(), ImVec2(modeWidth, 0)))
        OnPlayModeButtonPressed();
    PopStyle();

    ImGui::SameLine(0, Gap);

    // Volume
    ImGui::SetNextItemWidth(volSliderWidth);
    PushSliderStyle();
    float tempVolume = Data().volume;
    if (ImGui::SliderFloat("##TheaterVol", &tempVolume, 0.0f, 1.0f, ""))
        OnVolumeSliderChanged(tempVolume);
    PopStyle();

    //--------------------------------------------------------------------------
    // Lightbox (on top of everything)
    //--------------------------------------------------------------------------
    m_lightbox.Draw();
}

} // namespace moosic