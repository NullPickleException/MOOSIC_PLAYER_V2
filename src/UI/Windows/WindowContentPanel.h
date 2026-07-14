//==============================================================================
// WindowContentPanel.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "IWindow.h"
#include "DirectoryWindow.h"
#include "LibraryWindow.h"
#include "SettingsWindow.h"
#include "../../Services/PlaybackController.h"

namespace moosic
{

//==============================================================================
// ContentPanelTheme - Styling only (hardcoded)
//==============================================================================

struct ContentPanelTheme
{
    ImVec4 TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    ImVec4 TabInactive = ImVec4(0.10f, 0.22f, 0.40f, 1.0f);
    ImVec4 TabHovered = ImVec4(0.18f, 0.40f, 0.70f, 1.0f);
    ImVec4 TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TabTextInactive = ImVec4(0.60f, 0.65f, 0.75f, 1.00f);
    ImVec4 BorderColor = ImVec4(0.26f, 0.59f, 0.98f, 1.0f);
    float BorderThickness = 2.0f;
    float TabSpacing = 2.0f;
};

//==============================================================================
// WindowContentPanel - No theme logic
//==============================================================================

class WindowContentPanel
{
public:
    WindowContentPanel(MusicLibrary& library, PlaybackController* playbackController);
    
    void Draw();
    void UpdatePlayingTrack(const MusicTrack* track);

private:
    enum class Tab { Library, Directory, Settings };

    Tab m_activeTab = Tab::Library;
    DirectoryWindow m_directoryWindow;
    LibraryWindow   m_libraryWindow;
    SettingsWindow  m_settingsWindow;
    ContentPanelTheme m_theme; 
};

} // namespace moosic