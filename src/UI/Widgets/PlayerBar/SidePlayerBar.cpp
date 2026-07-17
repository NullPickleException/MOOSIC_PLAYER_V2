//==============================================================================
// SidePlayerBar.cpp
//==============================================================================

#include "SidePlayerBar.h"
#include "../../../Services/ImageLoader.h"
#include <imgui.h>

namespace moosic
{

void SidePlayerBar::Draw()
{
    float sidebarWidth = ImGui::GetContentRegionAvail().x;
    float padding = 4.0f;
    float contentWidth = sidebarWidth - (padding * 2.0f);
    float artSize = contentWidth;
    float centerX = padding;

    //==================================================================
    // Visualizer scaling factor
    //==================================================================
    constexpr float VISUALIZER_SCALE = 0.85f;
    
    const auto& visStyle = m_visualizer.GetStyle();
    float visWidth = contentWidth * VISUALIZER_SCALE;
    float visHeight = visStyle.BoxHeight * VISUALIZER_SCALE;
    float visOffsetX = (contentWidth - visWidth) * 0.5f;

    // Track change detection - compare with stored ID BEFORE UpdatePlaybackState changes it
    std::size_t currentTrackId = m_playbackController ? 
        (m_playbackController->GetCurrentTrack() ? m_playbackController->GetCurrentTrack()->GetId() : 0) : 0;
    bool trackChanged = (currentTrackId != m_lastTrackId && currentTrackId != 0);

    ImGui::Spacing();

    //==================================================================
    // Album Art - Centered
    //==================================================================
    float artX = (sidebarWidth - artSize) * 0.5f;
    ImGui::SetCursorPosX(artX);
    m_albumArtBox.Draw(artSize, 6.0f, true, true);
    
    if (m_albumArtBox.IsClicked() && m_albumArtTexture)
        OnAlbumArtClicked();
    
    if (m_albumArtBox.IsHovered() && m_albumArtTexture)
        ImGui::SetTooltip("Click to enlarge");

    ImGui::Spacing();

    //==================================================================
    // Visualizer
    //==================================================================
    m_visualizer.SetBoxSize(visWidth, visHeight);
    ImGui::SetCursorPosX(centerX + visOffsetX);
    DrawVisualizer();

    ImGui::Spacing();

    //==================================================================
    // Song Info - Scrolling text (minimum height enforced)
    //==================================================================
    float textMaxWidth = contentWidth;
    float minTextHeight = ImGui::GetTextLineHeight() + 2.0f;  // Ensure at least one line visible
    
    ImGui::SetCursorPosX(centerX);
    DrawScrollingText(m_songTitle, m_theme.TextPrimary, textMaxWidth, 
                      m_titleScrollOffset, m_lastTrackChangeTime, trackChanged);
    
    ImGui::SetCursorPosX(centerX);
    DrawScrollingText(m_artistName, m_theme.TextSecondary, textMaxWidth, 
                      m_artistScrollOffset, m_lastTrackChangeTime, trackChanged);

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //==================================================================
    // Controls - 3 buttons
    //==================================================================
    float btnSpacing = 4.0f;
    float btnWidth = (contentWidth - btnSpacing * 2.0f) / 3.0f;

    ImGui::SetCursorPosX(centerX);
    PushNormalButtonStyle();
    if (ImGui::Button("|<", ImVec2(btnWidth, 0))) OnPreviousButtonPressed();
    PopStyle();

    ImGui::SameLine(0, btnSpacing);
    PushPrimaryButtonStyle();
    if (ImGui::Button(m_isPlaying ? "||" : ">", ImVec2(btnWidth, 0))) OnPlayPauseButtonPressed();
    PopStyle();

    ImGui::SameLine(0, btnSpacing);
    PushNormalButtonStyle();
    if (ImGui::Button(">|", ImVec2(btnWidth, 0))) OnNextButtonPressed();
    PopStyle();

    ImGui::Spacing();

    //==================================================================
    // Play Mode
    //==================================================================
    ImGui::SetCursorPosX(centerX);
    const char* modeLabels[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
    PushNormalButtonStyle();
    if (ImGui::Button(modeLabels[static_cast<int>(m_playbackMode)], ImVec2(contentWidth, 0)))
        OnPlayModeButtonPressed();
    PopStyle();

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //==================================================================
    // Volume
    //==================================================================
    ImGui::SetCursorPosX(centerX);
    ImGui::TextColored(m_theme.TextSecondary, "Volume");
    ImGui::Spacing();

    ImGui::SetCursorPosX(centerX);
    ImGui::SetNextItemWidth(contentWidth);
    PushSliderStyle();
    float tempVolume = m_volume;
    if (ImGui::SliderFloat("##SideVol", &tempVolume, 0.0f, 1.0f, "%.2f"))
        OnVolumeSliderChanged(tempVolume);
    PopStyle();

    ImGui::Spacing();
    ImGui::SetCursorPosX(centerX);
    ImGui::Separator();
    ImGui::Spacing();

    //==================================================================
    // Progress
    //==================================================================
    ImGui::SetCursorPosX(centerX);
    ImGui::SetNextItemWidth(contentWidth);
    PushSliderStyle();
    
    static bool wasSeekingSide = false;
    if (ImGui::SliderFloat("##SideProgress", &m_playbackProgress, 0.0f, 1.0f, ""))
    {
        m_isSeeking = true;
        wasSeekingSide = true;
        if (m_songDuration > 0.0f)
            m_elapsedTime = m_playbackProgress * m_songDuration;
        OnPlaybackSliderChanged(m_playbackProgress);
    }
    if (wasSeekingSide && !ImGui::IsItemActive())
    {
        m_isSeeking = false;
        wasSeekingSide = false;
        if (m_playbackController)
        {
            m_elapsedTime = m_playbackController->GetCurrentPosition();
            m_songDuration = m_playbackController->GetCurrentDuration();
            if (m_songDuration > 0.0f)
                m_playbackProgress = m_elapsedTime / m_songDuration;
        }
    }
    PopStyle();

    ImGui::SetCursorPosX(centerX);
    DrawElapsedTime();
    ImGui::SameLine();
    ImGui::TextColored(m_theme.TextSecondary, " / ");
    ImGui::SameLine();
    DrawTotalTime();

    ImGui::Spacing();

    //==================================================================
    // Lightbox
    //==================================================================
    m_lightbox.Draw();
}

} // namespace moosic