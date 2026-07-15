//==============================================================================
// WindowContentPanel.h
//==============================================================================
// Content panel with tabs for Library, Directories, and Settings
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../../Services/PlaybackController.h"
#include "IWindow.h"
#include "DirectoryWindow.h"
#include "LibraryWindow.h"
#include "SettingsWindow.h"
#include "../Theme/Theme.h"

namespace moosic
{

//==============================================================================
// WindowContentPanel
//==============================================================================

class WindowContentPanel
{
public:
    WindowContentPanel(MusicLibrary &library,
                       PlaybackController *playbackController);

    void Draw();
    void UpdatePlayingTrack(const MusicTrack *track);

    void ApplyTheme(const Theme &theme)
    {
        m_theme = theme.ContentPanel;

        m_libraryWindow.ApplyTheme(theme.Window);
        m_libraryWindow.ApplyTrackTableTheme(theme.TrackTable);
        m_directoryWindow.ApplyTheme(theme.Window);
        m_settingsWindow.ApplyTheme(theme.Window);
    }

    //--------------------------------------------------------------------------
    // Accessors
    //--------------------------------------------------------------------------

    SettingsWindow &GetSettingsWindow() { return m_settingsWindow; }

private:
    //--------------------------------------------------------------------------
    // Tab Management
    //--------------------------------------------------------------------------

    enum class Tab
    {
        Library,
        Directory,
        Settings
    };

    void DrawTabBar();
    void DrawTabButtons();

private:
    Tab m_activeTab = Tab::Library;

    DirectoryWindow m_directoryWindow;
    LibraryWindow m_libraryWindow;
    SettingsWindow m_settingsWindow;

    WindowContentPanelTheme m_theme;
};

} // namespace moosic