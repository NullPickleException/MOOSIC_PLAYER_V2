//==============================================================================
// UI/Widgets/PlayerBar/TheaterPlayerBar.cpp
//==============================================================================

#include "TheaterPlayerBar.h"
#include <imgui.h>

namespace moosic
{

void TheaterPlayerBar::Draw()
{
    //----------------------------------------------------------------------
    // Player Bar Background (edge-to-edge)
    //----------------------------------------------------------------------
    {
        ImVec2 bgPos = ImGui::GetCursorScreenPos();
        bgPos.x -= ImGui::GetStyle().WindowPadding.x;
        float bgWidth = ImGui::GetWindowWidth();
        float bgHeight = ImGui::GetContentRegionAvail().y;
        DrawPlayerBarBackground(bgPos, ImVec2(bgWidth, bgHeight));
    }
    
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);

    float availWidth = ImGui::GetContentRegionAvail().x;
    float availHeight = ImGui::GetContentRegionAvail().y;

    //--------------------------------------------------------------------------
    // Large Album Art - Centered
    //--------------------------------------------------------------------------
    float maxArtSize = (std::min)(availWidth * 0.5f, availHeight * 0.50f);
    float artSize = (std::min)(maxArtSize, 300.0f);

    if (Data().trackJustChanged)
        m_artLoadAttempted = false;
    LoadAlbumArtForCurrentTrack();

    float artOffsetX = (availWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(artOffsetX);
    m_albumArtBox.Draw(artSize, 8.0f, true, true);
    
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        OnAlbumArtClicked();

    ImGui::Spacing();
    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Song Info - Centered
    //--------------------------------------------------------------------------
    float textWidth = (std::min)(availWidth * 0.8f, 500.0f);
    float textOffsetX = (availWidth - textWidth) * 0.5f;

    ImGui::SetCursorPosX(textOffsetX);
    ImGui::TextColored(m_theme.TextPrimary, "%s", Data().title.c_str());
    ImGui::SetCursorPosX(textOffsetX);
    ImGui::TextColored(m_theme.TextSecondary, "%s", Data().artist.c_str());

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Visualizer - Centered
    //--------------------------------------------------------------------------
    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = (std::min)(visStyle.BoxWidth * 1.5f, textWidth);
    float visHeight = visStyle.BoxHeight * 1.3f;
    m_visualizer.SetBoxSize(visWidth, visHeight);
    
    float visOffsetX = (availWidth - visWidth) * 0.5f;
    ImGui::SetCursorPosX(visOffsetX);
    DrawVisualizer();
    m_visualizer.SetBoxSize(visStyle.BoxWidth, visStyle.BoxHeight);

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Progress + Time - Centered
    //--------------------------------------------------------------------------
    float timeWidth = ImGui::CalcTextSize("00:00:00").x;
    float sliderWidth = textWidth - timeWidth * 2 - 20.0f;
    if (sliderWidth < 100.0f) sliderWidth = 100.0f;
    float progressStartX = (availWidth - (timeWidth + 10.0f + sliderWidth + 10.0f + timeWidth)) * 0.5f;

    ImGui::SetCursorPosX(progressStartX);
    DrawElapsedTime();
    ImGui::SameLine(0, 10.0f);
    ImGui::SetNextItemWidth(sliderWidth);
    PushSliderStyle();
    float progress = Data().progress;
    if (ImGui::SliderFloat("##TheaterProgress", &progress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        OnPlaybackSliderChanged(progress);
    }
    if (!ImGui::IsItemActive() && m_isSeeking)
        m_isSeeking = false;
    PopSliderStyle();
    ImGui::SameLine(0, 10.0f);
    DrawTotalTime();

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
    if (controlsOffsetX < 0) controlsOffsetX = 0;

    ImGui::SetCursorPosX(controlsOffsetX);

    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    PushPrimaryButtonStyle();
    if (ImGui::Button(Data().isPlaying ? "||" : ">", ImVec2(playWidth, 0))) OnPlayPauseButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    PushNormalButtonStyle();
    if (ImGui::Button(Data().modeLabel.c_str(), ImVec2(modeWidth, 0))) OnPlayModeButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, Gap);

    ImGui::SetNextItemWidth(volSliderWidth);
    PushSliderStyle();
    float tempVolume = Data().volume;
    if (ImGui::SliderFloat("##TheaterVol", &tempVolume, 0.0f, 1.0f, ""))
        OnVolumeSliderChanged(tempVolume);
    PopSliderStyle();

    m_lightbox.Draw();
}

} // namespace moosic