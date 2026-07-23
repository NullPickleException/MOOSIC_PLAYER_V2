//==============================================================================
// TrackTable.h - Refactored with modular event system and context menu support
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"
#include <imgui.h>
#include <optional>
#include <string>
#include <vector>
#include <functional>
#include <memory>

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
// Style
//==============================================================================

struct TrackTableStyle
{
    // Header
    ImVec4 HeaderBackground = ImVec4(0.280f, 0.327f, 0.371f, 1.00f);
    ImVec4 HeaderTextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 HeaderBorderColor = ImVec4(0.200f, 0.247f, 0.291f, 1.00f);
    float HeaderHeight = 0.0f;
    float HeaderSeparatorThickness = 1.0f;

    ImVec4 HeaderHovered = ImVec4(0.216f, 0.235f, 0.251f, 1.00f);
    ImVec4 HeaderActive = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);

    // Row Colors
    ImVec4 RowDefault = ImVec4(0.149f, 0.161f, 0.173f, 1.00f);
    ImVec4 RowDefaultAlt = ImVec4(0.176f, 0.192f, 0.204f, 1.00f);
    ImVec4 RowHovered = ImVec4(0.216f, 0.235f, 0.251f, 1.00f);
    ImVec4 RowClicked = ImVec4(0.459f, 0.671f, 0.851f, 0.35f);
    ImVec4 RowSelected = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);
    ImVec4 RowPlaying = ImVec4(0.459f, 0.671f, 0.851f, 0.10f);

    // Row Layout
    float RowHeight = 18.0f;
    float RowPaddingX = 4.0f;
    float RowPaddingY = 2.0f;

    // Text Colors
    ImVec4 TextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    ImVec4 TextSelected = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TextPlaying = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

    // Per-column header colors
    ImVec4 HeaderTextTitle     = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 HeaderTextArtist    = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 HeaderTextAlbum     = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 HeaderTextExtension = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 HeaderTextDuration  = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);

    // Per-column row colors
    ImVec4 RowTextTitle     = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 RowTextArtist    = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
    ImVec4 RowTextAlbum     = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
    ImVec4 RowTextExtension = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
    ImVec4 RowTextDuration  = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);

    // Border & Separator
    ImVec4 BorderColor = ImVec4(0.200f, 0.247f, 0.291f, 1.00f);
    float BorderThickness = 1.0f;
    bool ShowRowSeparators = true;
    ImVec4 RowSeparatorColor = ImVec4(0.200f, 0.247f, 0.291f, 0.50f);

    // Scrollbar
    ImVec4 ScrollbarBg = ImVec4(0.12f, 0.13f, 0.15f, 1.00f);
    ImVec4 ScrollbarGrab = ImVec4(0.28f, 0.33f, 0.37f, 1.00f);
    ImVec4 ScrollbarGrabHovered = ImVec4(0.38f, 0.43f, 0.47f, 1.00f);
    ImVec4 ScrollbarGrabActive = ImVec4(0.46f, 0.67f, 0.85f, 1.00f);
    float ScrollbarWidth = 8.0f;
    float ScrollbarRounding = 4.0f;

    // Column Widths
    float TitleWidth = 300.0f;
    float ArtistWidth = 200.0f;
    float AlbumWidth = 200.0f;
    float ExtensionWidth = 60.0f;
    float DurationWidth = 80.0f;
    float DefaultColumnWidth = 150.0f;

    // Animation
    float HoverFadeSpeed = 0.15f;
    float SelectionFadeSpeed = 0.20f;
    float ScrollSmoothing = 0.12f;

    // Misc
    float TableRounding = 0.0f;
    float MinColumnWidth = 30.0f;
};

//==============================================================================
// Config
//==============================================================================

struct TrackTableConfig
{
    bool Sortable = true;
    bool Resizable = true;
    bool Reorderable = true;
    bool Hideable = true;
    bool Borders = true;
    bool AlternateRows = true;

    std::vector<TrackColumn> Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
        TrackColumn::Album,
        TrackColumn::Extension,
        TrackColumn::Duration
    };
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
// Row Event Data
//==============================================================================

struct RowEventData
{
    const MusicTrack* track = nullptr;
    int rowIndex = -1;
    bool isSelected = false;
    bool isPlaying = false;
};

//==============================================================================
// Context Menu Item
//==============================================================================

struct ContextMenuItem
{
    std::string label;
    bool enabled = true;
    bool isSeparator = false;
    std::function<void(const RowEventData&)> action;
};

//==============================================================================
// TrackTable
//==============================================================================

class TrackTable
{
public:
    //--------------------------------------------------------------------------
    // Types
    //--------------------------------------------------------------------------

    using RowEventCallback = std::function<void(const RowEventData&)>;
    using SortEventCallback = std::function<void(const SortRequest&)>;

    //--------------------------------------------------------------------------
    // Configuration
    //--------------------------------------------------------------------------

    void ApplyTheme(const TrackTableStyle& style) { m_style = style; }
    void ApplyConfig(const TrackTableConfig& config) { m_config = config; }

    //--------------------------------------------------------------------------
    // Event Registration
    //--------------------------------------------------------------------------

    void OnRowClick(RowEventCallback callback)      { m_onRowClick = std::move(callback); }
    void OnRowDoubleClick(RowEventCallback callback) { m_onRowDoubleClick = std::move(callback); }
    void OnRowHover(RowEventCallback callback)       { m_onRowHover = std::move(callback); }
    void OnRowRightClick(RowEventCallback callback)  { m_onRowRightClick = std::move(callback); }
    void OnSort(SortEventCallback callback)          { m_onSort = std::move(callback); }

    //--------------------------------------------------------------------------
    // Context Menu
    //--------------------------------------------------------------------------

    void SetContextMenu(const std::vector<ContextMenuItem>& items);
    void ClearContextMenu();
    bool HasContextMenu() const { return m_hasContextMenu; }

    //--------------------------------------------------------------------------
    // Drawing
    //--------------------------------------------------------------------------

    void Draw(const std::vector<const MusicTrack*>& tracks);

    //--------------------------------------------------------------------------
    // Sort Request
    //--------------------------------------------------------------------------

    std::optional<SortRequest> GetSortRequest() const { return m_pendingSort; }
    void ClearSortRequest() { m_pendingSort = std::nullopt; }

    //--------------------------------------------------------------------------
    // Selection State
    //--------------------------------------------------------------------------

    void SetSelectedRow(int row, const MusicTrack* track = nullptr);
    void SetPlayingRow(int row, const MusicTrack* track = nullptr);
    void ClearSelection();

    int GetSelectedRow() const { return m_selectedRow; }
    const MusicTrack* GetSelectedTrack() const { return m_selectedTrack; }
    int GetPlayingRow() const { return m_playingRow; }
    const MusicTrack* GetPlayingTrack() const { return m_playingTrack; }
    int GetHoveredRowIndex() const { return m_hoveredRow; }

    //--------------------------------------------------------------------------
    // Right-Click State (for external context menu handling)
    //--------------------------------------------------------------------------

    bool HasPendingRightClick() const { return m_rightClickedRowIndex >= 0 && m_rightClickedTrack != nullptr; }
    int GetRightClickedRowIndex() const { return m_rightClickedRowIndex; }
    const MusicTrack* GetRightClickedTrack() const { return m_rightClickedTrack; }
    void ClearRightClickState() { m_rightClickedRowIndex = -1; m_rightClickedTrack = nullptr; }

    //--------------------------------------------------------------------------
    // Track List
    //--------------------------------------------------------------------------

    const std::vector<const MusicTrack*>& GetCurrentTrackList() const { return m_currentTrackList; }

private:
    //--------------------------------------------------------------------------
    // Internal Drawing
    //--------------------------------------------------------------------------

    void DrawHeader();
    void DrawRows(const std::vector<const MusicTrack*>& tracks);

    //--------------------------------------------------------------------------
    // Helpers
    //--------------------------------------------------------------------------

    void HandleSort();
    ImGuiTableFlags BuildFlags() const;
    void PushStyle();
    void PopStyle();

    static const char* GetColumnName(TrackColumn column);
    static std::string FormatDuration(unsigned int seconds);
    float GetColumnWidth(TrackColumn column) const;
    ImVec4 GetTextColorForColumn(TrackColumn column, bool isHeader) const;
    void PushRowTextColor(TrackColumn column);

    RowEventData CreateRowEvent(int rowIndex, const MusicTrack* track) const;
    std::string TruncateText(const std::string& text, float maxWidth) const;

private:
    //--------------------------------------------------------------------------
    // Members
    //--------------------------------------------------------------------------

    TrackTableStyle m_style;
    TrackTableConfig m_config;

    // Event callbacks
    RowEventCallback m_onRowClick;
    RowEventCallback m_onRowDoubleClick;
    RowEventCallback m_onRowHover;
    RowEventCallback m_onRowRightClick;
    SortEventCallback m_onSort;

    // Context menu items (stored but rendered externally)
    std::vector<ContextMenuItem> m_contextMenuItems;
    bool m_hasContextMenu = false;

    // Sort state
    std::optional<SortRequest> m_pendingSort;

    // Selection state
    int m_selectedRow = -1;
    const MusicTrack* m_selectedTrack = nullptr;
    int m_playingRow = -1;
    const MusicTrack* m_playingTrack = nullptr;
    int m_hoveredRow = -1;

    // Right-click state (exposed for external popup handling)
    int m_rightClickedRowIndex = -1;
    const MusicTrack* m_rightClickedTrack = nullptr;

    // Current display data
    std::vector<const MusicTrack*> m_currentTrackList;
};

} // namespace moosic