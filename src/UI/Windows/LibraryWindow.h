//==============================================================================
// LibraryWindow.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Widgets/TrackTable.h"
#include "IWindow.h"
#include "../../Services/PlaybackController.h"
#include <vector>
#include <string>

namespace moosic
{

    //==========================================================================
    // ToolbarOptions — controls visibility of toolbar elements
    //==========================================================================

    struct LibraryToolbarOptions
    {
        bool ShowSearchBar      = true;
        bool ShowRefreshButton  = true;
        bool ShowClearButton    = false;
        bool ShowTrackCount     = true;
        bool ShowBrandHeader    = true;

        std::string BrandText   = "MOOSIC LIBRARY";
        std::string SearchHint  = "Search title, artist or album...";
        float SearchBarWidth    = 300.0f;
    };

    //==========================================================================
    // LibraryWindow
    //==========================================================================

    class LibraryWindow : public IWindow
    {
    public:
        explicit LibraryWindow(MusicLibrary &library, PlaybackController *playbackController = nullptr);
        void Draw() override;

        void ApplyTheme(const WindowTheme &theme)
        {
            m_theme = theme;
        }

        void ApplyTrackTableTheme(const TrackTableStyle &theme)
        {
            m_trackTable.ApplyTheme(theme);
        }

        // Toolbar configuration
        void SetToolbarOptions(const LibraryToolbarOptions &options) { m_toolbarOptions = options; }
        LibraryToolbarOptions &GetToolbarOptions() { return m_toolbarOptions; }

        void UpdatePlayingTrack(const MusicTrack *track);
        const std::vector<const MusicTrack *> &GetCurrentTrackList() const { return m_tracks; }

    private:
        void SyncPlayingTrack();
        void DrawHeader();
        void DrawToolbar();
        void DrawTrackTable();
        void HandleSorting();
        void DrawFooter();
        void RefreshTrackList();
        int FindTrackIndex(std::size_t trackId) const;
        const MusicTrack *FindTrackById(std::size_t trackId) const;

    private:
        MusicLibrary &m_library;
        PlaybackController *m_playbackController;
        TrackTable m_trackTable;
        std::vector<const MusicTrack *> m_tracks;
        size_t m_lastTrackCount = 0;
        std::size_t m_playingTrackId = 0;
        WindowTheme m_theme;
        LibraryToolbarOptions m_toolbarOptions;
    };

} // namespace moosic