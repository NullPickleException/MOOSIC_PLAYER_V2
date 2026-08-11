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
    ImVec2 bgPos;
    {
        bgPos = ImGui::GetCursorScreenPos();
        bgPos.x -= ImGui::GetStyle().WindowPadding.x;
        float bgWidth = ImGui::GetWindowWidth();
        float bgHeight = ImGui::GetContentRegionAvail().y;
        DrawPlayerBarBackground(bgPos, ImVec2(bgWidth, bgHeight));
    }

    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);

    float availWidth = ImGui::GetContentRegionAvail().x;
    float availHeight = ImGui::GetContentRegionAvail().y;

    float padding = 4.0f;
    float infoLineHeight = ImGui::GetTextLineHeight() + 2.0f;
    float visHeight = 40.0f;
    float progressHeight = ImGui::GetFrameHeight() + 8.0f;
    float controlsHeight = ImGui::GetFrameHeight() + 8.0f;
    float bottomPadding = 12.0f;
    
    float totalFixedHeight = padding + infoLineHeight * 2 + padding + visHeight + padding + progressHeight + padding + controlsHeight + padding + bottomPadding;
    float artAvailableHeight = availHeight - totalFixedHeight;
    
    //--------------------------------------------------------------------------
    // Large Album Art - Centered, uses remaining space
    //--------------------------------------------------------------------------
    float maxArtSize = (std::min)(availWidth * 0.65f, artAvailableHeight);
    float artSize = (std::max)(maxArtSize, 100.0f);

    if (Data().trackJustChanged)
        m_artLoadAttempted = false;
    LoadAlbumArtForCurrentTrack();

    float artOffsetX = (availWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(artOffsetX);
    m_albumArtBox.Draw(artSize, 8.0f, true, true);
    
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        OnAlbumArtClicked();

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Song Info - Options button at right edge of text area
    //--------------------------------------------------------------------------
    float textWidth = (std::min)(availWidth * 0.85f, 500.0f);
    float textLeftX = (availWidth - textWidth) * 0.5f;
    float textRightX = textLeftX + textWidth;

    ImGui::SetCursorPosX(textLeftX);
    ImGui::TextColored(m_theme.TextPrimary, "%s", Data().title.c_str());

    ImGui::SameLine();
    ImGui::SetCursorPosX(textRightX - 30.0f);
    DrawTrackOptionsButton();

    ImGui::SetCursorPosX(textLeftX);
    ImGui::TextColored(m_theme.TextSecondary, "%s", Data().artist.c_str());

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Visualizer - Centered
    //--------------------------------------------------------------------------
    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = (std::min)(visStyle.BoxWidth * 1.5f, textWidth);
    m_visualizer.SetBoxSize(visWidth, visHeight);
    
    float visOffsetX = (availWidth - visWidth) * 0.5f;
    ImGui::SetCursorPosX(visOffsetX);
    DrawVisualizer();
    m_visualizer.SetBoxSize(visStyle.BoxWidth, visStyle.BoxHeight);

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Progress + Time - Centered
    //--------------------------------------------------------------------------
    float timeWidth = ImGui::CalcTextSize("00:00").x;
    float sliderWidth = textWidth - timeWidth * 2 - 20.0f;
    if (sliderWidth < 100.0f) sliderWidth = 100.0f;
    
    float totalWidth = timeWidth + 10.0f + sliderWidth + 10.0f + timeWidth;
    float progressStartX = (availWidth - totalWidth) * 0.5f;
    float sliderCenterX = progressStartX + timeWidth + 10.0f + sliderWidth * 0.5f;

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
    // Controls - Play/Pause centered under slider
    //--------------------------------------------------------------------------
    constexpr float Gap = 8.0f;
    float btnWidth = 40.0f;
    float playWidth = 48.0f;
    float modeWidth = ImGui::CalcTextSize(Data().modeLabel.c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f + 8.0f;
    float volSliderWidth = 100.0f;

    float playStartX = sliderCenterX - playWidth * 0.5f;
    float prevStartX = playStartX - Gap - btnWidth;
    float nextStartX = playStartX + playWidth + Gap;
    float modeStartX = nextStartX + btnWidth + Gap;
    float volStartX = modeStartX + modeWidth + Gap;

    ImGui::SetCursorPosX(prevStartX);

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

    ImGui::SetCursorPosX(volStartX);
    DrawVolumeIcon();

    ImGui::SameLine(0, 4.0f);
    ImGui::SetNextItemWidth(volSliderWidth);
    PushSliderStyle();
    float tempVolume = Data().volume;
    if (ImGui::SliderFloat("##TheaterVol", &tempVolume, 0.0f, 1.0f, ""))
        OnVolumeSliderChanged(tempVolume);
    PopSliderStyle();

    // Bottom spacing so buttons aren't on the border edge
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + bottomPadding);

    // Draw lightbox and edit track dialog
    m_lightbox.Draw();
    
    if (m_editTrackDialog)
        m_editTrackDialog->Draw();
}

} // namespace moosic