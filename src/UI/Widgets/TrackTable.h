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
        //--------------------------------------------------------------------------
        // Header
        //--------------------------------------------------------------------------

        ImVec4 HeaderBackground = ImVec4(0.280f, 0.327f, 0.371f, 1.00f);  // GreyDark
        ImVec4 HeaderTextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);      // TextBright
        ImVec4 HeaderBorderColor = ImVec4(0.200f, 0.247f, 0.291f, 1.00f); // GreyDarker
        float HeaderHeight = 0.0f;                                        // 0 = use font size
        float HeaderSeparatorThickness = 1.0f;

        // Header interaction
        ImVec4 HeaderHovered = ImVec4(0.216f, 0.235f, 0.251f, 1.00f); // DarkBgHi
        ImVec4 HeaderActive = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);  // Blue

        //--------------------------------------------------------------------------
        // Row Colors
        //--------------------------------------------------------------------------

        ImVec4 RowDefault = ImVec4(0.149f, 0.161f, 0.173f, 1.00f);    // DarkBg
        ImVec4 RowDefaultAlt = ImVec4(0.176f, 0.192f, 0.204f, 1.00f); // DarkBgAlt
        ImVec4 RowHovered = ImVec4(0.216f, 0.235f, 0.251f, 1.00f);    // DarkBgHi
        ImVec4 RowClicked = ImVec4(0.459f, 0.671f, 0.851f, 0.35f);    // Blue @ 35%
        ImVec4 RowSelected = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);   // Blue (full)
        ImVec4 RowPlaying = ImVec4(0.459f, 0.671f, 0.851f, 0.10f);    // BlueSubtle

        //--------------------------------------------------------------------------
        // Row Layout
        //--------------------------------------------------------------------------

        float RowHeight = 18.0f;
        float RowPaddingX = 4.0f;
        float RowPaddingY = 2.0f;

        //--------------------------------------------------------------------------
        // Text Colors
        //--------------------------------------------------------------------------

        ImVec4 TextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);    // TextBright
        ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);      // TextDim
        ImVec4 TextSelected = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // TextWhite
        ImVec4 TextPlaying = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);  // TextWhite

        //--------------------------------------------------------------------------
        // Column Header Text Colors (per-column overrides)
        //--------------------------------------------------------------------------

        ImVec4 HeaderTextTitle = ImVec4(0.95f, 0.95f, 0.95f, 1.00f); // TextBright
        ImVec4 HeaderTextArtist = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 HeaderTextAlbum = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 HeaderTextExtension = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 HeaderTextDuration = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);

        //--------------------------------------------------------------------------
        // Row Text Colors (per-column overrides for data cells)
        //--------------------------------------------------------------------------

        ImVec4 RowTextTitle = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);     // TextBright
        ImVec4 RowTextArtist = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);    // TextMuted
        ImVec4 RowTextAlbum = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);     // TextMuted
        ImVec4 RowTextExtension = ImVec4(0.42f, 0.42f, 0.42f, 1.00f); // TextDim
        ImVec4 RowTextDuration = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);  // TextMuted

        //--------------------------------------------------------------------------
        // Border & Separator
        //--------------------------------------------------------------------------

        ImVec4 BorderColor = ImVec4(0.200f, 0.247f, 0.291f, 1.00f); // GreyDarker
        float BorderThickness = 1.0f;
        bool ShowRowSeparators = true;
        ImVec4 RowSeparatorColor = ImVec4(0.200f, 0.247f, 0.291f, 0.50f); // GreyDarker @ 50%

        //--------------------------------------------------------------------------
        // Scrollbar
        //--------------------------------------------------------------------------

        ImVec4 ScrollbarBg = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);          // DarkBgPanel
        ImVec4 ScrollbarGrab = ImVec4(0.28f, 0.33f, 0.37f, 1.00f);        // GreyDark
        ImVec4 ScrollbarGrabHovered = ImVec4(0.38f, 0.43f, 0.47f, 1.00f); // Grey
        ImVec4 ScrollbarGrabActive = ImVec4(0.46f, 0.67f, 0.85f, 1.00f);  // Blue
        float ScrollbarWidth = 8.0f;
        float ScrollbarRounding = 4.0f;

        //--------------------------------------------------------------------------
        // Column Widths
        //--------------------------------------------------------------------------

        float TitleWidth = 300.0f;
        float ArtistWidth = 200.0f;
        float AlbumWidth = 200.0f;
        float ExtensionWidth = 60.0f;
        float DurationWidth = 80.0f;
        float DefaultColumnWidth = 150.0f;

        //--------------------------------------------------------------------------
        // Smoothing / Animation
        //--------------------------------------------------------------------------

        float HoverFadeSpeed = 0.15f;     // How fast row hover highlight fades in (0=instant, 1=very slow)
        float SelectionFadeSpeed = 0.20f; // How fast selection highlight appears
        float ScrollSmoothing = 0.12f;    // Scroll momentum

        //--------------------------------------------------------------------------
        // Misc
        //--------------------------------------------------------------------------

        float TableRounding = 0.0f;   // Outer table corner rounding
        float MinColumnWidth = 30.0f; // Minimum width any column can be resized to
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
        // Configuration
        //--------------------------------------------------------------------------

        void ApplyTheme(const TrackTableStyle &style) { m_style = style; }
        void ApplyConfig(const TrackTableConfig &config) { m_config = config; }

        void Draw(const std::vector<const MusicTrack *> &tracks);

        std::optional<SortRequest> GetSortRequest() const;

        //--------------------------------------------------------------------------
        // Selection
        //--------------------------------------------------------------------------

        int GetSelectedRow() const { return m_selectedRow; }
        const MusicTrack *GetSelectedTrack() const { return m_selectedTrack; }
        void ClearSelection();

        void SetSelectedRow(int row, const MusicTrack *track = nullptr)
        {
            m_selectedRow = row;
            m_selectedTrack = track;
        }
        void SetPlayingRow(int row, const MusicTrack *track = nullptr)
        {
            m_playingRow = row;
            m_playingTrack = track;
        }

        const std::vector<const MusicTrack *> &GetCurrentTrackList() const { return m_currentTrackList; }
        int GetHoveredRowIndex() const { return m_hoveredRow; }

    private:
        //--------------------------------------------------------------------------
        // Drawing
        //--------------------------------------------------------------------------

        void DrawHeader();
        void DrawRows(const std::vector<const MusicTrack *> &tracks);

        //--------------------------------------------------------------------------
        // Helpers
        //--------------------------------------------------------------------------

        ImVec4 GetTextColorForColumn(TrackColumn column, bool isHeader) const;
        void PushRowTextColor(TrackColumn column);

        void HandleSort();
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
        const MusicTrack *m_selectedTrack = nullptr;
        int m_playingRow = -1;
        const MusicTrack *m_playingTrack = nullptr;
        int m_clickedRow = -1;
        int m_hoveredRow = -1;

        // Current track list being displayed
        std::vector<const MusicTrack *> m_currentTrackList;
    };

} // namespace moosic