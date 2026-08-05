//==============================================================================
// TrackTable.cpp - Clean, modular implementation
//==============================================================================

#include "TrackTable.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace moosic
{

    //==============================================================================
    // Context Menu Setup
    //==============================================================================

    void TrackTable::SetContextMenu(const std::vector<ContextMenuItem> &items)
    {
        m_contextMenuItems = items;
        m_hasContextMenu = !items.empty();
        m_onRowRightClick = nullptr;
    }

    void TrackTable::ClearContextMenu()
    {
        m_contextMenuItems.clear();
        m_hasContextMenu = false;
        m_rightClickedRowIndex = -1;
        m_rightClickedTrack = nullptr;
        m_onRowRightClick = nullptr;
    }

    //==============================================================================
    // Selection
    //==============================================================================

    void TrackTable::SetSelectedRow(int row, const MusicTrack *track)
    {
        m_selectedRow = row;
        m_selectedTrack = track;
    }

    void TrackTable::SetPlayingRow(int row, const MusicTrack *track)
    {
        m_playingRow = row;
        m_playingTrack = track;
    }

    void TrackTable::ClearSelection()
    {
        m_selectedRow = -1;
        m_selectedTrack = nullptr;
        m_playingRow = -1;
        m_playingTrack = nullptr;
        m_hoveredRow = -1;
    }

    //==============================================================================
    // Row Event Creation
    //==============================================================================

    RowEventData TrackTable::CreateRowEvent(int rowIndex, const MusicTrack *track) const
    {
        RowEventData event;
        event.track = track;
        event.rowIndex = rowIndex;
        event.isSelected = (m_selectedRow == rowIndex);
        event.isPlaying = (m_playingRow == rowIndex);
        return event;
    }

    //==============================================================================
    // Main Draw
    //==============================================================================

    // Add to TrackTable::DrawRows or Draw method, after ImGui::EndTable()
    void TrackTable::Draw(const std::vector<const MusicTrack *> &tracks)
    {
        m_pendingSort = std::nullopt;
        m_hoveredRow = -1;
        m_currentTrackList = tracks;

        if (tracks.empty())
        {
            ImGui::TextDisabled("No tracks.");
            return;
        }

        PushStyle();

        char tableId[64];
        snprintf(tableId, sizeof(tableId), "TrackTable_%p", this);

        if (ImGui::BeginTable(tableId, static_cast<int>(m_config.Columns.size()), BuildFlags()))
        {
            DrawHeader();
            DrawRows(tracks);
            HandleSort();

            SyncHiddenColumns();

            ImGui::EndTable();
        }

        PopStyle();
    }

    //==============================================================================
    // Header
    //==============================================================================

    void TrackTable::DrawHeader()
    {
        ImGui::TableSetupScrollFreeze(0, 1);

        for (TrackColumn column : m_config.Columns)
        {
            ImGuiTableColumnFlags flags = ImGuiTableColumnFlags_None;
            float width = GetColumnWidth(column);

            switch (column)
            {
            case TrackColumn::Title:
            case TrackColumn::Artist:
            case TrackColumn::Album:
                flags |= ImGuiTableColumnFlags_WidthStretch;
                break;
            case TrackColumn::Extension:
                flags |= ImGuiTableColumnFlags_WidthFixed;
                break;
            case TrackColumn::Duration:
                flags |= ImGuiTableColumnFlags_WidthFixed;
                if (width < 70.0f)
                    width = 70.0f;
                break;
            }

            if (m_config.Sortable)
            {
                flags |= ImGuiTableColumnFlags_PreferSortAscending |
                         ImGuiTableColumnFlags_PreferSortDescending;
            }

            // Check if this column should be hidden based on saved config
            bool isVisible = std::find(m_config.VisibleColumns.begin(),
                                       m_config.VisibleColumns.end(),
                                       column) != m_config.VisibleColumns.end();

            if (!isVisible)
            {
                flags |= ImGuiTableColumnFlags_DefaultHide;
            }

            ImGui::TableSetupColumn(GetColumnName(column), flags, width);
        }

        ImGui::PushStyleColor(ImGuiCol_Header, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_style.HeaderHovered);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_style.HeaderActive);
        ImGui::PushStyleColor(ImGuiCol_Text, m_style.HeaderTextColor);
        ImGui::PushStyleColor(ImGuiCol_Border, m_style.HeaderBorderColor);

        ImGui::TableHeadersRow();

        // Draw header gradient overlay if enabled
        if (m_style.UseHeaderGradient)
        {
            ImVec2 headerMin = ImGui::GetItemRectMin();
            ImVec2 headerMax = ImGui::GetItemRectMax();
            ImDrawList *dl = ImGui::GetWindowDrawList();
            dl->AddRectFilledMultiColor(
                headerMin, headerMax,
                ImGui::GetColorU32(m_style.HeaderGradientTop),
                ImGui::GetColorU32(m_style.HeaderGradientTop),
                ImGui::GetColorU32(m_style.HeaderGradientBottom),
                ImGui::GetColorU32(m_style.HeaderGradientBottom));
        }

        // Draw header gloss if enabled
        if (m_style.UseGlossyHeader && m_style.HeaderGlossIntensity > 0.0f)
        {
            ImVec2 headerMin = ImGui::GetItemRectMin();
            ImVec2 headerMax = ImGui::GetItemRectMax();
            ImDrawList *dl = ImGui::GetWindowDrawList();
            float glossH = (headerMax.y - headerMin.y) * 0.45f;
            ImVec4 glossCol = m_style.HeaderGlossColor;
            glossCol.w *= m_style.HeaderGlossIntensity;
            ImVec4 fadeOut = ImVec4(glossCol.x, glossCol.y, glossCol.z, 0.0f);
            dl->AddRectFilledMultiColor(
                ImVec2(headerMin.x, headerMin.y + 1.0f),
                ImVec2(headerMax.x, headerMin.y + glossH),
                ImGui::GetColorU32(glossCol),
                ImGui::GetColorU32(glossCol),
                ImGui::GetColorU32(fadeOut),
                ImGui::GetColorU32(fadeOut));
        }

        ImGui::PopStyleColor(5);
    }

    //==============================================================================
    // Rows
    //==============================================================================

    void TrackTable::DrawRows(const std::vector<const MusicTrack *> &tracks)
    {
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));

        for (size_t i = 0; i < tracks.size(); ++i)
        {
            const MusicTrack *track = tracks[i];
            if (!track)
                continue;

            int rowIndex = static_cast<int>(i);
            bool isSelected = (m_selectedRow == rowIndex);
            bool isPlaying = (m_playingRow == rowIndex);
            bool isHovered = false;

            ImGui::TableNextRow(0, m_style.RowHeight);

            if (isSelected)
                ImGui::PushStyleColor(ImGuiCol_Text, m_style.TextSelected);
            else if (isPlaying)
                ImGui::PushStyleColor(ImGuiCol_Text, m_style.TextPlaying);

            for (size_t colIdx = 0; colIdx < m_config.Columns.size(); ++colIdx)
            {
                TrackColumn column = m_config.Columns[colIdx];
                ImGui::TableNextColumn();

                if (!isSelected && !isPlaying)
                    PushRowTextColor(column);

                float colWidth = GetColumnWidth(column) - 10.0f;
                std::string cellText;
                std::string fullText;

                switch (column)
                {
                case TrackColumn::Title:
                    fullText = track->GetTitle();
                    break;
                case TrackColumn::Artist:
                    fullText = track->GetArtist();
                    break;
                case TrackColumn::Album:
                    fullText = track->GetAlbum();
                    break;
                case TrackColumn::Extension:
                {
                    std::string ext = track->GetExtension();
                    fullText = ext.empty() ? "--" : [&]()
                    {
                        std::transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
                        return ext;
                    }();
                    break;
                }
                case TrackColumn::Duration:
                    fullText = track->GetDuration() > 0 ? FormatDuration(track->GetDuration()) : "--:--";
                    break;
                }

                cellText = TruncateText(fullText, colWidth);

                if (column == TrackColumn::Title)
                {
                    bool clicked = ImGui::Selectable(
                        cellText.c_str(), false,
                        ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns,
                        ImVec2(0, 0));

                    if (ImGui::IsItemHovered())
                    {
                        isHovered = true;
                        m_hoveredRow = rowIndex;

                        RowEventData event = CreateRowEvent(rowIndex, track);
                        if (m_onRowHover)
                            m_onRowHover(event);

                        if (fullText.length() > cellText.length())
                        {
                            ImGui::BeginTooltip();
                            ImGui::TextUnformatted(fullText.c_str());
                            ImGui::EndTooltip();
                        }
                    }

                    if (clicked)
                    {
                        m_selectedRow = rowIndex;
                        m_selectedTrack = track;

                        RowEventData event = CreateRowEvent(rowIndex, track);
                        if (m_onRowClick)
                            m_onRowClick(event);
                    }

                    if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered())
                    {
                        RowEventData event = CreateRowEvent(rowIndex, track);
                        if (m_onRowDoubleClick)
                            m_onRowDoubleClick(event);
                    }

                    if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                    {
                        m_selectedRow = rowIndex;
                        m_selectedTrack = track;
                        m_rightClickedRowIndex = rowIndex;
                        m_rightClickedTrack = track;

                        RowEventData event = CreateRowEvent(rowIndex, track);
                        if (m_onRowRightClick)
                            m_onRowRightClick(event);
                    }
                }
                else
                {
                    ImGui::TextUnformatted(cellText.c_str());

                    if (fullText.length() > cellText.length() && ImGui::IsItemHovered())
                    {
                        ImGui::BeginTooltip();
                        ImGui::TextUnformatted(fullText.c_str());
                        ImGui::EndTooltip();
                    }
                }

                if (!isSelected && !isPlaying)
                    ImGui::PopStyleColor();
            }

            if (isSelected || isPlaying)
                ImGui::PopStyleColor();

            ImVec4 rowColor;
            if (isPlaying)
                rowColor = m_style.RowPlaying;
            else if (isSelected)
                rowColor = m_style.RowSelected;
            else if (isHovered)
                rowColor = m_style.RowHovered;
            else
                rowColor = (rowIndex % 2 == 0) ? m_style.RowDefault : m_style.RowDefaultAlt;

            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(rowColor));

            // Glossy selection on hovered/selected rows
            if (m_style.UseGlossySelection && m_style.SelectionGlossIntensity > 0.0f && (isHovered || isSelected))
            {
                ImVec2 rowMin = ImGui::GetItemRectMin();
                ImVec2 rowMax = ImGui::GetItemRectMax();
                ImDrawList *dl = ImGui::GetWindowDrawList();
                float glossH = (rowMax.y - rowMin.y) * 0.40f;
                float glossAlpha = isSelected ? m_style.SelectionGlossIntensity * 0.6f : m_style.SelectionGlossIntensity * 0.3f;
                ImVec4 glossCol = ImVec4(1.0f, 1.0f, 1.0f, glossAlpha);
                ImVec4 fadeOut = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
                dl->AddRectFilledMultiColor(
                    ImVec2(rowMin.x + 2.0f, rowMin.y + 1.0f),
                    ImVec2(rowMax.x - 2.0f, rowMin.y + glossH),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(glossCol),
                    ImGui::GetColorU32(fadeOut),
                    ImGui::GetColorU32(fadeOut));
            }

            if (m_style.ShowRowSeparators && m_config.Borders)
            {
                ImVec2 rowMin = ImVec2(
                    ImGui::GetItemRectMin().x - ImGui::GetStyle().CellPadding.x,
                    ImGui::GetItemRectMax().y);
                ImVec2 rowMax = ImVec2(
                    ImGui::GetItemRectMax().x + ImGui::GetStyle().CellPadding.x,
                    ImGui::GetItemRectMax().y + 1.0f);
                ImGui::GetWindowDrawList()->AddLine(rowMin, rowMax,
                                                    ImGui::GetColorU32(m_style.RowSeparatorColor), 1.0f);
            }
        }

        ImGui::PopStyleColor(2);
    }

    //==============================================================================
    // Sort Handling
    //==============================================================================

    void TrackTable::HandleSort()
    {
        ImGuiTableSortSpecs *specs = ImGui::TableGetSortSpecs();
        if (!specs || !specs->SpecsDirty)
            return;
        specs->SpecsDirty = false;
        if (specs->SpecsCount == 0)
            return;

        const auto &spec = specs->Specs[0];
        m_pendingSort = SortRequest{
            m_config.Columns[spec.ColumnIndex],
            spec.SortDirection == ImGuiSortDirection_Ascending};

        if (m_onSort && m_pendingSort)
            m_onSort(*m_pendingSort);
    }

    //==============================================================================
    // Helpers
    //==============================================================================

    ImGuiTableFlags TrackTable::BuildFlags() const
    {
        ImGuiTableFlags flags =
            ImGuiTableFlags_ScrollY |
            ImGuiTableFlags_NoSavedSettings |
            ImGuiTableFlags_SizingStretchProp |
            ImGuiTableFlags_RowBg;

        if (m_config.Sortable)
            flags |= ImGuiTableFlags_Sortable;
        if (m_config.Resizable)
            flags |= ImGuiTableFlags_Resizable;
        if (m_config.Reorderable)
            flags |= ImGuiTableFlags_Reorderable;
        if (m_config.Hideable)
            flags |= ImGuiTableFlags_Hideable;
        if (m_config.Borders)
            flags |= ImGuiTableFlags_Borders;

        return flags;
    }

    void TrackTable::PushStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_Header, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_style.HeaderHovered);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_style.HeaderActive);
        ImGui::PushStyleColor(ImGuiCol_Border, m_style.BorderColor);
        ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, m_style.ScrollbarBg);
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrab, m_style.ScrollbarGrab);
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabHovered, m_style.ScrollbarGrabHovered);
        ImGui::PushStyleColor(ImGuiCol_ScrollbarGrabActive, m_style.ScrollbarGrabActive);

        // Apply rounded scrollbar if enabled
        if (m_style.UseRoundedScrollbar)
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, m_style.ScrollbarRounding);
            ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, m_style.ScrollbarWidth);
        }
    }

    void TrackTable::PopStyle()
    {
        if (m_style.UseRoundedScrollbar)
            ImGui::PopStyleVar(2);
        ImGui::PopStyleColor(9);
    }

    const char *TrackTable::GetColumnName(TrackColumn column)
    {
        switch (column)
        {
        case TrackColumn::Title:
            return "Title";
        case TrackColumn::Artist:
            return "Artist";
        case TrackColumn::Album:
            return "Album";
        case TrackColumn::Extension:
            return "Type";
        case TrackColumn::Duration:
            return "Duration";
        }
        return "";
    }

    std::string TrackTable::FormatDuration(unsigned int seconds)
    {
        unsigned int minutes = seconds / 60;
        unsigned int secs = seconds % 60;
        std::ostringstream stream;
        stream << std::setw(2) << std::setfill('0') << minutes
               << ":" << std::setw(2) << std::setfill('0') << secs;
        return stream.str();
    }

    float TrackTable::GetColumnWidth(TrackColumn column) const
    {
        switch (column)
        {
        case TrackColumn::Title:
            return m_style.TitleWidth;
        case TrackColumn::Artist:
            return m_style.ArtistWidth;
        case TrackColumn::Album:
            return m_style.AlbumWidth;
        case TrackColumn::Extension:
            return m_style.ExtensionWidth;
        case TrackColumn::Duration:
            return (m_style.DurationWidth < 70.0f) ? 70.0f : m_style.DurationWidth;
        default:
            return m_style.DefaultColumnWidth;
        }
    }

    ImVec4 TrackTable::GetTextColorForColumn(TrackColumn column, bool isHeader) const
    {
        if (isHeader)
        {
            switch (column)
            {
            case TrackColumn::Title:
                return m_style.HeaderTextTitle;
            case TrackColumn::Artist:
                return m_style.HeaderTextArtist;
            case TrackColumn::Album:
                return m_style.HeaderTextAlbum;
            case TrackColumn::Extension:
                return m_style.HeaderTextExtension;
            case TrackColumn::Duration:
                return m_style.HeaderTextDuration;
            default:
                return m_style.HeaderTextColor;
            }
        }
        else
        {
            switch (column)
            {
            case TrackColumn::Title:
                return m_style.RowTextTitle;
            case TrackColumn::Artist:
                return m_style.RowTextArtist;
            case TrackColumn::Album:
                return m_style.RowTextAlbum;
            case TrackColumn::Extension:
                return m_style.RowTextExtension;
            case TrackColumn::Duration:
                return m_style.RowTextDuration;
            default:
                return m_style.TextColor;
            }
        }
    }

    void TrackTable::PushRowTextColor(TrackColumn column)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, GetTextColorForColumn(column, false));
    }

    std::string TrackTable::TruncateText(const std::string &text, float maxWidth) const
    {
        if (text.empty())
            return text;

        ImFont *font = ImGui::GetFont();
        float textWidth = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f, text.c_str()).x;
        if (textWidth <= maxWidth)
            return text;

        std::string truncated = text;
        while (!truncated.empty())
        {
            truncated.pop_back();
            float w = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f,
                                          (truncated + "...").c_str())
                          .x;
            if (w <= maxWidth)
                return truncated + "...";
        }
        return text.substr(0, 1) + "...";
    }

    void TrackTable::SyncHiddenColumns()
    {
        std::vector<TrackColumn> newVisibleColumns;

        // Iterate through ALL columns to check which are visible
        for (size_t i = 0; i < m_config.Columns.size(); ++i)
        {
            ImGuiTableColumnFlags flags = ImGui::TableGetColumnFlags(static_cast<int>(i));

            // Check if column is NOT hidden
            // When hidden, ImGui sets the column status to Disabled and removes IsEnabled
            bool isVisible = (flags & ImGuiTableColumnFlags_IsEnabled) != 0 &&
                             (flags & ImGuiTableColumnFlags_Disabled) == 0;

            if (isVisible)
            {
                newVisibleColumns.push_back(m_config.Columns[i]);
            }
        }

        // Only update if visibility actually changed
        if (!newVisibleColumns.empty() && newVisibleColumns != m_config.VisibleColumns)
        {
            m_config.VisibleColumns = newVisibleColumns;

            // Notify listeners
            if (m_onColumnsChanged)
                m_onColumnsChanged(m_config);
        }
    }

} // namespace moosic