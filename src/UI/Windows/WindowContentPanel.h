//==============================================================================
// WindowContentPanel.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Data/LayoutStateDataModel.h"
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
        WindowContentPanel(LibraryDataModel &libraryData,
                           DirectoryDataModel &directoryData,
                           PlaylistDataModel &playlistData,
                           LayoutStateDataModel &layoutState,
                           MusicLibrary &library,
                           PlaybackController *playbackController);

        void Draw();
        void UpdatePlayingTrack(const MusicTrack *track);

        // Call on layout switch so shared currentTab is applied on first Draw.
        void InvalidateTabSelection()
        {
            m_appliedTab = LayoutStateDataModel::Tab::Count;
        }

        void ApplyTheme(const Theme &theme)
        {
            m_theme = theme.ContentPanel;
            m_libraryWindow.ApplyTheme(theme.Window);
            m_libraryWindow.ApplyTrackTableTheme(theme.TrackTable);
            m_libraryWindow.ApplySearchBarTheme(theme.SearchBar);
            m_libraryWindow.ApplyContextMenuTheme(theme.ContextMenu);
            m_playlistWindow.ApplyTheme(theme.Window);
            m_playlistWindow.ApplyTrackTableTheme(theme.TrackTable);
            m_playlistWindow.ApplyContextMenuTheme(theme.ContextMenu);
            m_directoryWindow.ApplyTheme(theme.Window);
            m_settingsWindow.ApplyTheme(theme.Window);
        }

        SettingsWindow &GetSettingsWindow() { return m_settingsWindow; }
        LibraryDataModel &GetLibraryData() { return m_libraryData; }
        PlaylistDataModel &GetPlaylistData() { return m_playlistData; }

    private:
        LibraryDataModel &m_libraryData;
        DirectoryDataModel &m_directoryData;
        PlaylistDataModel &m_playlistData;
        MusicLibrary &m_library;
        LayoutStateDataModel &m_layoutState;
        DirectoryWindow m_directoryWindow;
        LibraryWindow m_libraryWindow;
        PlaylistWindow m_playlistWindow;
        SettingsWindow m_settingsWindow;
        WindowContentPanelTheme m_theme;
        int m_panelId = 0;

        // Count = not applied yet → forces SetSelected on next Draw
        LayoutStateDataModel::Tab m_appliedTab = LayoutStateDataModel::Tab::Count;
    };

} // namespace moosic