//==============================================================================
// WindowContentPanel.h
//==============================================================================
// Content panel with tabs for Library, Playlists, Directories, and Settings
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../../Models/MusicLibrary.h"
#include "../../Services/PlaybackController.h"
#include "IWindow.h"
#include "DirectoryWindow.h"
#include "LibraryWindow.h"
#include "PlaylistWindow.h"
#include "SettingsWindow.h"
#include "../Theme/Theme.h"

namespace moosic
{

class WindowContentPanel
{
public:
    WindowContentPanel(LibraryDataModel& libraryData,
                       DirectoryDataModel& directoryData,
                       PlaylistDataModel& playlistData,
                       MusicLibrary& library,
                       PlaybackController* playbackController);

    void Draw();
    void UpdatePlayingTrack(const MusicTrack* track);

    void ApplyTheme(const Theme& theme)
    {
        m_theme = theme.ContentPanel;

        m_libraryWindow.ApplyTheme(theme.Window);
        m_libraryWindow.ApplyTrackTableTheme(theme.TrackTable);
        m_libraryWindow.ApplySearchBarTheme(theme.SearchBar);

        m_playlistWindow.ApplyTheme(theme.Window);
        m_playlistWindow.ApplyTrackTableTheme(theme.TrackTable);
        
        m_directoryWindow.ApplyTheme(theme.Window);
        
        m_settingsWindow.ApplyTheme(theme.Window);
    }

    SettingsWindow& GetSettingsWindow() { return m_settingsWindow; }
    LibraryDataModel& GetLibraryData() { return m_libraryData; }
    PlaylistDataModel& GetPlaylistData() { return m_playlistData; }

private:
    enum class Tab { Library, Playlists, Directory, Settings };

private:
    Tab m_activeTab = Tab::Library;

    LibraryDataModel& m_libraryData;
    DirectoryDataModel& m_directoryData;
    PlaylistDataModel& m_playlistData;
    MusicLibrary& m_library;

    DirectoryWindow m_directoryWindow;
    LibraryWindow m_libraryWindow;
    PlaylistWindow m_playlistWindow;
    SettingsWindow m_settingsWindow;

    WindowContentPanelTheme m_theme;
};

} // namespace moosic