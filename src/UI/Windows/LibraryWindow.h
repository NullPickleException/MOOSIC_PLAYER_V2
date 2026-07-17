//==============================================================================
// UI/Windows/LibraryWindow.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Widgets/TrackTable.h"
#include "IWindow.h"
#include "../../Services/PlaybackController.h"
#include <vector>
#include <string>

namespace moosic
{

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

    class LibraryWindow : public IWindow
    {
    public:
        // Now takes LibraryDataModel + optional PlaybackController
        explicit LibraryWindow(LibraryDataModel& dataModel, 
                               PlaybackController* playbackController = nullptr);
        void Draw() override;

        void ApplyTheme(const WindowTheme& theme) override { m_theme = theme; }
        void ApplyTrackTableTheme(const TrackTableStyle& theme) { m_trackTable.ApplyTheme(theme); }

        void SetToolbarOptions(const LibraryToolbarOptions& options) { m_toolbarOptions = options; }
        LibraryToolbarOptions& GetToolbarOptions() { return m_toolbarOptions; }

    private:
        void DrawHeader();
        void DrawToolbar();
        void DrawTrackTable();
        void DrawFooter();
        
        void OnTrackClicked(const MusicTrack* track, int rowIndex);
        void HandleTableSorting();

    private:
        LibraryDataModel& m_data;              // Shared data - we don't own it!
        PlaybackController* m_playbackController;
        TrackTable m_trackTable;
        WindowTheme m_theme;
        LibraryToolbarOptions m_toolbarOptions;
        
        // UI-only state (search buffer for the input field)
        char m_searchBuffer[256] = "";
    };

} // namespace moosic