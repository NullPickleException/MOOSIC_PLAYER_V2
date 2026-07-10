#include "TrackTable.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace moosic
{
    //==============================================================================
    // Configuration
    //==============================================================================
    void TrackTable::ApplyStyle(const TrackTableStyle &style)
    {
        m_style = style;
    }
    void TrackTable::ApplyConfig(const TrackTableConfig &config)
    {
        m_config = config;
    }

    //==============================================================================
    // Callbacks
    //==============================================================================
    void TrackTable::OnRowClick(RowClickCallback callback)
    {
        m_onRowClick = std::move(callback);
    }
    void TrackTable::OnRowDoubleClick(RowDoubleClickCallback callback)
    {
        m_onRowDoubleClick = std::move(callback);
    }
    void TrackTable::OnRowHover(RowHoverCallback callback)
    {
        m_onRowHover = std::move(callback);
    }

    //==============================================================================
    // Selection
    //==============================================================================
    void TrackTable::ClearSelection()
    {
        m_selectedRow = -1;
        m_selectedTrack = nullptr;
        m_playingRow = -1;
        m_playingTrack = nullptr;
        m_clickedRow = -1;
    }

    //==============================================================================
    // Draw
    //==============================================================================
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

        if (ImGui::BeginTable(
                "TrackTable",
                static_cast<int>(m_config.Columns.size()),
                BuildFlags()))
        {
            DrawHeader();
            DrawRows(tracks);
            HandleSort();
            ImGui::EndTable();
        }

        PopStyle();
    }

    //==============================================================================
    // GetColumnWidth
    //==============================================================================
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

            ImGui::TableSetupColumn(GetColumnName(column), flags, width);
        }

        ImGui::PushStyleColor(ImGuiCol_Header, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_style.RowHovered);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_style.RowSelected);
        ImGui::PushStyleColor(ImGuiCol_Text, m_style.TextColor);

        ImGui::TableHeadersRow();

        ImGui::PopStyleColor(4);
    }

    //==============================================================================
    // Rows
    //==============================================================================

    void TrackTable::DrawRows(const std::vector<const MusicTrack *> &tracks)
    {
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0, 0, 0, 0));

        static bool debugPrinted = false;

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

            // Column 0: Title
            ImGui::TableNextColumn();
            bool clicked = ImGui::Selectable(
                track->GetTitle().c_str(),
                false,
                ImGuiSelectableFlags_AllowDoubleClick);

            if (ImGui::IsItemHovered())
            {
                isHovered = true;
                m_hoveredRow = rowIndex;
                if (m_onRowHover)
                    m_onRowHover(track, rowIndex);
            }

            if (clicked)
            {
                m_selectedRow = rowIndex;
                m_selectedTrack = track;
                if (m_onRowClick)
                    m_onRowClick(track, rowIndex);
            }

            if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered())
            {
                if (m_onRowDoubleClick)
                    m_onRowDoubleClick(track, rowIndex);
            }

            // Row color priority: Playing > Selected > Hovered > Default
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

            // Column 1: Artist
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(track->GetArtist().c_str());

            // Column 2: Album
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(track->GetAlbum().c_str());

            // Column 3: Extension
            ImGui::TableNextColumn();
            std::string ext = track->GetExtension();
            if (!ext.empty())
            {
                std::transform(ext.begin(), ext.end(), ext.begin(), ::toupper);
                ImGui::TextUnformatted(ext.c_str());
            }
            else
            {
                ImGui::TextUnformatted("--");
            }

            // Column 4: Duration
            ImGui::TableNextColumn();
            unsigned int duration = track->GetDuration();
            
            // Debug: Print first few tracks with duration
            if (!debugPrinted && i < 3)
            {
                std::cout << "[TrackTable] Track " << i << ": " << track->GetTitle() 
                          << " | Duration: " << duration << "s" << std::endl;
                if (i == 2) debugPrinted = true;
            }

            if (duration > 0)
            {
                std::string durationStr = FormatDuration(duration);
                ImGui::TextUnformatted(durationStr.c_str());
            }
            else
            {
                ImGui::TextUnformatted("--:--");
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
        if (!specs)
            return;
        if (!specs->SpecsDirty)
            return;
        specs->SpecsDirty = false;
        if (specs->SpecsCount == 0)
            return;

        const auto &spec = specs->Specs[0];
        m_pendingSort = SortRequest{
            m_config.Columns[spec.ColumnIndex],
            spec.SortDirection == ImGuiSortDirection_Ascending};
    }

    std::optional<SortRequest> TrackTable::GetSortRequest() const
    {
        return m_pendingSort;
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
        if (m_config.AlternateRows)
            flags |= ImGuiTableFlags_RowBg;

        return flags;
    }

    void TrackTable::PushStyle()
    {
        ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_Header, m_style.HeaderBackground);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_style.RowHovered);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_style.RowSelected);
        ImGui::PushStyleColor(ImGuiCol_Border, m_style.BorderColor);
    }

    void TrackTable::PopStyle()
    {
        ImGui::PopStyleColor(5);
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

} // namespace moosic