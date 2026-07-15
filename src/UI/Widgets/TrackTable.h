//==============================================================================
// TrackTable.h
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"

#include <imgui.h>

#include <optional>
#include <string>
#include <vector>
#include <functional>

namespace moosic
{

    //==============================================================================
    // Columns
    //==============================================================================

    enum class TrackColumn
    {
        Title,
        Artist,
        Album,
        Extension,
        Duration
    };

    //==============================================================================
    // Style - Contains all visual styling including widths
    //==============================================================================

    struct TrackTableStyle
    {
        // Colors
        ImVec4 HeaderBackground = ImVec4(0.18f, 0.18f, 0.18f, 1.0f);
        ImVec4 RowDefault = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
        ImVec4 RowDefaultAlt = ImVec4(0.16f, 0.16f, 0.16f, 1.0f);
        ImVec4 RowHovered = ImVec4(0.25f, 0.25f, 0.30f, 1.0f);
        ImVec4 RowClicked = ImVec4(0.3f, 0.3f, 0.5f, 0.8f);
        ImVec4 RowSelected = ImVec4(0.0f, 0.0f, 0.90f, 0.90f);
        ImVec4 RowPlaying = ImVec4(0.0f, 0.70f, 0.0f, 0.80f);
        ImVec4 BorderColor = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
        ImVec4 TextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImVec4 TextDisabled = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
        ImVec4 TextSelected = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

        // Column Widths
        float TitleWidth = 300.0f;
        float ArtistWidth = 200.0f;
        float AlbumWidth = 200.0f;
        float ExtensionWidth = 60.0f;
        float DurationWidth = 80.0f;
        float DefaultColumnWidth = 150.0f;
        float RowHeight = 9.0f;
    };

    //==============================================================================
    // Config - Separate from style (not theme)
    //==============================================================================

    struct TrackTableConfig
    {
        bool Sortable = true;
        bool Resizable = true;
        bool Reorderable = true;
        bool Hideable = true;
        bool Borders = true;
        bool AlternateRows = true;

        std::vector<TrackColumn> Columns =
            {
                TrackColumn::Title,
                TrackColumn::Artist,
                TrackColumn::Album,
                TrackColumn::Extension,
                TrackColumn::Duration};
    };

    //==============================================================================
    // Sort Request
    //==============================================================================

    struct SortRequest
    {
        TrackColumn column;
        bool ascending;
    };

    //==============================================================================
    // TrackTable
    //==============================================================================

    class TrackTable
    {
    public:
        //--------------------------------------------------------------------------
        // Callbacks
        //--------------------------------------------------------------------------

        using RowClickCallback = std::function<void(const MusicTrack *track, int rowIndex)>;
        using RowDoubleClickCallback = std::function<void(const MusicTrack *track, int rowIndex)>;
        using RowHoverCallback = std::function<void(const MusicTrack *track, int rowIndex)>;

        void OnRowClick(RowClickCallback callback);
        void OnRowDoubleClick(RowDoubleClickCallback callback);
        void OnRowHover(RowHoverCallback callback);

        //--------------------------------------------------------------------------
        // Configuration - All inline
        //--------------------------------------------------------------------------

        // Theme application
        void ApplyTheme(const TrackTableStyle &style) { m_style = style; }
        
        // Config is NOT part of theming - kept separate
        void ApplyConfig(const TrackTableConfig &config) { m_config = config; }

        void Draw(const std::vector<const MusicTrack *> &tracks);

        std::optional<SortRequest> GetSortRequest() const;

        //--------------------------------------------------------------------------
        // Selection
        //--------------------------------------------------------------------------

        int GetSelectedRow() const { return m_selectedRow; }
        const MusicTrack *GetSelectedTrack() const { return m_selectedTrack; }
        void ClearSelection();
        
        // Set external selection
        void SetSelectedRow(int row, const MusicTrack* track = nullptr) 
        { 
            m_selectedRow = row; 
            m_selectedTrack = track;
        }
        void SetPlayingRow(int row, const MusicTrack* track = nullptr) 
        { 
            m_playingRow = row; 
            m_playingTrack = track;
        }

        // Get the current track list (for playback)
        const std::vector<const MusicTrack*>& GetCurrentTrackList() const { return m_currentTrackList; }

    private:
        //--------------------------------------------------------------------------
        // Drawing
        //--------------------------------------------------------------------------

        void DrawHeader();
        void DrawRows(const std::vector<const MusicTrack *> &tracks);

        //--------------------------------------------------------------------------
        // Sort Handling
        //--------------------------------------------------------------------------

        void HandleSort();

        //--------------------------------------------------------------------------
        // Helpers
        //--------------------------------------------------------------------------

        ImGuiTableFlags BuildFlags() const;
        void PushStyle();
        void PopStyle();

        static const char *GetColumnName(TrackColumn column);
        static std::string FormatDuration(unsigned int seconds);

        float GetColumnWidth(TrackColumn column) const;

    private:
        TrackTableStyle m_style;
        TrackTableConfig m_config;

        std::optional<SortRequest> m_pendingSort;

        // Callbacks
        RowClickCallback m_onRowClick;
        RowDoubleClickCallback m_onRowDoubleClick;
        RowHoverCallback m_onRowHover;

        // Selection state
        int m_selectedRow = -1;
        const MusicTrack* m_selectedTrack = nullptr;
        int m_playingRow = -1;
        const MusicTrack* m_playingTrack = nullptr;
        int m_clickedRow = -1;
        int m_hoveredRow = -1;
        
        // Current track list being displayed
        std::vector<const MusicTrack*> m_currentTrackList;
    };

} // namespace moosic