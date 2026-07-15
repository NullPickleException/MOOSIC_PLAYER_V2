#include "TrackTable.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>

namespace moosic
{
   
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

        // Helper lambda to truncate text with ellipsis
        auto TruncateText = [](const std::string &text, float maxWidth) -> std::string
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
                float truncatedWidth = font->CalcTextSizeA(font->FontSize, FLT_MAX, 0.0f,
                                                           (truncated + "...").c_str())
                                           .x;

                if (truncatedWidth <= maxWidth)
                    return truncated + "...";
            }
            return text.substr(0, 1) + "...";
        };

        for (size_t i = 0; i < tracks.size(); ++i)
        {
            const MusicTrack *track = tracks[i];
            if (!track)
                continue;

            int rowIndex = static_cast<int>(i);
            bool isSelected = (m_selectedRow == rowIndex);
            bool isPlaying = (m_playingRow == rowIndex);
            bool isHovered = false;

            // Fixed row height - NO GROWING!
            ImGui::TableNextRow(0, m_style.RowHeight);

            // Get column widths for truncation
            float titleWidth = GetColumnWidth(TrackColumn::Title) - 10.0f;
            float artistWidth = GetColumnWidth(TrackColumn::Artist) - 10.0f;
            float albumWidth = GetColumnWidth(TrackColumn::Album) - 10.0f;

            // Column 0: Title (truncated)
            ImGui::TableNextColumn();
            std::string title = track->GetTitle();
            std::string truncatedTitle = TruncateText(title, titleWidth);

            bool clicked = ImGui::Selectable(
                truncatedTitle.c_str(),
                false,
                ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns,
                ImVec2(0, 0) // Fixed size - no expansion
            );

            if (ImGui::IsItemHovered())
            {
                isHovered = true;
                m_hoveredRow = rowIndex;
                if (m_onRowHover)
                    m_onRowHover(track, rowIndex);

                // Show tooltip with full text on hover
                if (title.length() > truncatedTitle.length())
                {
                    ImGui::BeginTooltip();
                    ImGui::TextUnformatted(title.c_str());
                    ImGui::EndTooltip();
                }
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

            // Row color
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

            // Column 1: Artist (truncated)
            ImGui::TableNextColumn();
            std::string artist = track->GetArtist();
            std::string truncatedArtist = TruncateText(artist, artistWidth);
            ImGui::TextUnformatted(truncatedArtist.c_str());
            if (artist.length() > truncatedArtist.length() && ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::TextUnformatted(artist.c_str());
                ImGui::EndTooltip();
            }

            // Column 2: Album (truncated)
            ImGui::TableNextColumn();
            std::string album = track->GetAlbum();
            std::string truncatedAlbum = TruncateText(album, albumWidth);
            ImGui::TextUnformatted(truncatedAlbum.c_str());
            if (album.length() > truncatedAlbum.length() && ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::TextUnformatted(album.c_str());
                ImGui::EndTooltip();
            }

            // Column 3: Extension (fixed, no truncation needed)
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

            // Column 4: Duration (fixed)
            ImGui::TableNextColumn();
            unsigned int duration = track->GetDuration();

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