//==============================================================================
// UI/Widgets/PlayerBar/SidePlayerBar.cpp
//==============================================================================

#include "SidePlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

void SidePlayerBar::Draw()
{
    //----------------------------------------------------------------------
    // Player Bar Background (fits the entire sidebar region edge-to-edge)
    //----------------------------------------------------------------------
    {
        ImVec2 bgPos = ImGui::GetWindowPos();
        ImVec2 bgSize = ImGui::GetWindowSize();
        DrawPlayerBarBackground(bgPos, bgSize);
    }
    
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6.0f);

    float sidebarWidth = ImGui::GetContentRegionAvail().x;
    float padding = 10.0f;
    float contentWidth = sidebarWidth - (padding * 2.0f);
    float artSize = contentWidth;
    float centerX = padding;

    constexpr float VISUALIZER_SCALE = 0.85f;

    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = contentWidth * VISUALIZER_SCALE;
    float visHeight = visStyle.BoxHeight * VISUALIZER_SCALE;
    float visOffsetX = (contentWidth - visWidth) * 0.5f;

    bool trackChanged = Data().trackJustChanged;

    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Album Art - Centered with padding from background edges
    //----------------------------------------------------------------------
    if (Data().trackJustChanged)
        m_artLoadAttempted = false;
    LoadAlbumArtForCurrentTrack();

    float artX = (sidebarWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(artX);
    m_albumArtBox.Draw(artSize, 6.0f, true, true);

    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        OnAlbumArtClicked();

    if (m_albumArtBox.IsHovered() && m_albumArtTexture)
        ImGui::SetTooltip("Click to enlarge");

    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Visualizer
    //----------------------------------------------------------------------
    m_visualizer.SetBoxSize(visWidth, visHeight);
    ImGui::SetCursorPosX(centerX + visOffsetX);
    DrawVisualizer();

    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Song Info - Push transparent child bg before scrolling text
    //----------------------------------------------------------------------
    float textMaxWidth = contentWidth;

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
    
    ImGui::SetCursorPosX(centerX);
    DrawScrollingText(Data().title.c_str(), m_theme.TextPrimary, textMaxWidth,
                      m_titleScrollOffset, m_lastTrackChangeTime, trackChanged);

    ImGui::SetCursorPosX(centerX);
    DrawScrollingText(Data().artist.c_str(), m_theme.TextSecondary, textMaxWidth,
                      m_artistScrollOffset, m_lastTrackChangeTime, trackChanged);

    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Controls - 3 buttons
    //----------------------------------------------------------------------
    float btnSpacing = 4.0f;
    float btnWidth = (contentWidth - btnSpacing * 2.0f) / 3.0f;

    ImGui::SetCursorPosX(centerX);
    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, btnSpacing);
    PushPrimaryButtonStyle();
    if (ImGui::Button(Data().isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::SameLine(0, btnSpacing);
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Play Mode
    //----------------------------------------------------------------------
    ImGui::SetCursorPosX(centerX);
    PushNormalButtonStyle();
    if (ImGui::Button(Data().modeLabel.c_str(), ImVec2(contentWidth, 0)))
        OnPlayModeButtonPressed();
    DrawClassicButtonDecorations(ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    PopStyle();

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Volume
    //----------------------------------------------------------------------
    ImGui::SetCursorPosX(centerX);
    ImGui::TextColored(m_theme.TextSecondary, "Volume");
    ImGui::Spacing();

    ImGui::SetCursorPosX(centerX);
    ImGui::SetNextItemWidth(contentWidth);
    PushSliderStyle();
    float tempVolume = Data().volume;
    if (ImGui::SliderFloat("##SideVol", &tempVolume, 0.0f, 1.0f, "%.2f"))
        OnVolumeSliderChanged(tempVolume);
    PopSliderStyle();

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //----------------------------------------------------------------------
    // Progress
    //----------------------------------------------------------------------
    ImGui::SetCursorPosX(centerX);
    ImGui::SetNextItemWidth(contentWidth);
    PushSliderStyle();

    static bool wasSeekingSide = false;
    float progress = Data().progress;
    if (ImGui::SliderFloat("##SideProgress", &progress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        wasSeekingSide = true;
        OnPlaybackSliderChanged(progress);
    }
    if (wasSeekingSide && !ImGui::IsItemActive())
    {
        m_isSeeking = false;
        wasSeekingSide = false;
    }
    PopSliderStyle();

    ImGui::SetCursorPosX(centerX);
    DrawElapsedTime();
    ImGui::SameLine();
    ImGui::TextColored(m_theme.TextSecondary, " / ");
    ImGui::SameLine();
    DrawTotalTime();

    ImGui::Spacing();

    m_lightbox.Draw();
    
    // Draw the edit track dialog (modal popup)
    if (m_editTrackDialog)
        m_editTrackDialog->Draw();
}

} // namespace moosic