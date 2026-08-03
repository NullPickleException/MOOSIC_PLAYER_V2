//==============================================================================
// UI/Windows/LibraryWindow.h
//==============================================================================

#pragma once

#include "IWindow.h"
#include "../Data/LibraryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Widgets/TrackTable.h"
#include "../Widgets/TrackSearchBar.h"
#include "../Widgets/PopupMenu.h"
#include "../Widgets/EditTrackDialog.h"
#include "../../Services/PlaybackController.h"

#include <vector>
#include <string>

namespace moosic
{

    struct LibraryToolbarOptions
    {
        bool ShowSearchBar = true;
        bool ShowRefreshButton = true;
        bool ShowClearButton = false;
        bool ShowTrackCount = true;
        bool ShowBrandHeader = true;

        std::string BrandText = "MOOSIC LIBRARY";
        std::string SearchHint = "Search title, artist or album...";
        float SearchBarWidth = 500.0f;
    };

    class LibraryWindow : public IWindow
    {
    public:
        explicit LibraryWindow(LibraryDataModel &dataModel,
                               PlaybackController *playbackController = nullptr);
        void Draw() override;

        void ApplyTheme(const WindowTheme &theme) override { m_theme = theme; }
        void ApplyTrackTableTheme(const TrackTableStyle &theme) { m_trackTable.ApplyTheme(theme); }
        void ApplySearchBarTheme(const TrackSearchBarTheme &theme) { m_searchBar.SetTheme(theme); }
        void ApplyContextMenuTheme(const PopupMenuTheme &theme)
        {
            m_contextMenu.ApplyTheme(theme);
        }

        void SetToolbarOptions(const LibraryToolbarOptions &options) { m_toolbarOptions = options; }
        LibraryToolbarOptions &GetToolbarOptions() { return m_toolbarOptions; }

        //----------------------------------------------------------------------
        // Playlist Data Model - for "Add to Playlist" context menu submenu
        //----------------------------------------------------------------------
        void SetPlaylistDataModel(PlaylistDataModel *playlistModel)
        {
            m_playlistModel = playlistModel;
        }

        //----------------------------------------------------------------------
        // Search Mode
        //----------------------------------------------------------------------
        void SetUseDropdownSearch(bool useDropdown) { m_useDropdownSearch = useDropdown; }
        bool IsUsingDropdownSearch() const { return m_useDropdownSearch; }

    private:
        void DrawHeader();
        void DrawToolbar();
        void DrawTrackTable();
        void DrawFooter();

        void OnTrackClicked(const MusicTrack *track, int rowIndex);
        void HandleTableSorting();
        void SetupSearchBar();

        //----------------------------------------------------------------------
        // Context Menu Builder
        //----------------------------------------------------------------------
        void BuildContextMenu(std::vector<MenuItem> &items);

        // Search modes
        void DrawDropdownSearch();
        void DrawInlineSearch();

    private:
        LibraryDataModel &m_data;
        PlaybackController *m_playbackController;
        PlaylistDataModel *m_playlistModel = nullptr;
        TrackTable m_trackTable;
        TrackSearchBar m_searchBar;
        WindowTheme m_theme;
        LibraryToolbarOptions m_toolbarOptions;

        // ── Context Menu ────────────────────────────
        ContextMenu m_contextMenu;
        int m_contextRow = -1;
        const MusicTrack *m_contextTrack = nullptr;

        // ── Edit Track Dialog ───────────────────────
        EditTrackDialog m_editTrackDialog;

        // Search state
        bool m_useDropdownSearch = false;
        char m_searchBuffer[256] = "";
    };

} // namespace moosic