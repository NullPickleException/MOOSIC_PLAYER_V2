//==============================================================================
// UI/Windows/LibraryWindow.cpp
//==============================================================================

#include "LibraryWindow.h"
#include "../Theme/Theme.h"
#include <iostream>
#include <imgui.h>

namespace moosic
{

    //==========================================================================
    // Constructor
    //==========================================================================

    LibraryWindow::LibraryWindow(LibraryDataModel& dataModel, 
                                  PlaybackController* playbackController)
        : m_data(dataModel)
        , m_playbackController(playbackController)
    {
        // Table configuration
        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
            TrackColumn::Extension,
            TrackColumn::Duration
        };
        m_trackTable.ApplyConfig(config);

        // Layout-only style
        TrackTableStyle style;
        style.TitleWidth = 350.0f;
        style.ArtistWidth = 180.0f;
        style.AlbumWidth = 180.0f;
        style.ExtensionWidth = 50.0f;
        style.DurationWidth = 80.0f;
        style.RowHeight = 18.0f;
        m_trackTable.ApplyTheme(style);

        // Default toolbar
        m_toolbarOptions.ShowSearchBar = true;
        m_toolbarOptions.ShowRefreshButton = true;
        m_toolbarOptions.ShowClearButton = false;
        m_toolbarOptions.ShowTrackCount = true;
        m_toolbarOptions.ShowBrandHeader = true;
        m_toolbarOptions.BrandText = "MOOSIC LIBRARY";
        m_toolbarOptions.SearchBarWidth = 300.0f;
        m_toolbarOptions.SearchHint = "Search title, artist or album...";

        // Row click callback - delegate to data model + playback
        m_trackTable.OnRowClick([this](const MusicTrack* track, int rowIndex) {
            OnTrackClicked(track, rowIndex);
        });

        m_trackTable.OnRowDoubleClick([this](const MusicTrack* track, int rowIndex) {
            OnTrackClicked(track, rowIndex);
        });
        
        // Listen for data changes
        m_data.SetOnDataChanged([this]() {
            // Data changed - next Draw() will pick it up
        });
    }

    //==========================================================================
    // Main Draw - Just coordinates rendering
    //==========================================================================

    void LibraryWindow::Draw()
    {
        // Auto-refresh if library has changed
        if (m_data.NeedsRefresh())
            m_data.Refresh();

        // Sync playing state from controller
        if (m_playbackController)
            m_data.SyncPlayingTrack(m_playbackController->GetCurrentTrack());

        DrawHeader();
        DrawToolbar();
        DrawTrackTable();
       // DrawFooter();
    }

    //==========================================================================
    // Header
    //==========================================================================

    void LibraryWindow::DrawHeader()
    {
        if (!m_toolbarOptions.ShowBrandHeader && !m_toolbarOptions.ShowTrackCount)
        {
            ImGui::Separator();
            return;
        }

        if (m_toolbarOptions.ShowBrandHeader)
            ImGui::TextColored(m_theme.BrandText, "%s", m_toolbarOptions.BrandText.c_str());

        if (m_toolbarOptions.ShowTrackCount)
        {
            if (m_toolbarOptions.ShowBrandHeader)
                ImGui::SameLine();
            ImGui::Text("(%zu Tracks)", m_data.GetTrackCount());
        }

        ImGui::Separator();
    }

    //==========================================================================
    // Toolbar
    //==========================================================================

    void LibraryWindow::DrawToolbar()
    {
        bool anyToolbar = m_toolbarOptions.ShowSearchBar ||
                          m_toolbarOptions.ShowRefreshButton ||
                          m_toolbarOptions.ShowClearButton;

        if (!anyToolbar) return;

        // Search bar
        if (m_toolbarOptions.ShowSearchBar)
        {
            ImGui::SetNextItemWidth(m_toolbarOptions.SearchBarWidth);
            if (ImGui::InputTextWithHint("##Search",
                                         m_toolbarOptions.SearchHint.c_str(),
                                         m_searchBuffer, sizeof(m_searchBuffer)))
            {
                // Delegate filtering to data model
                m_data.SetSearchFilter(m_searchBuffer);
            }
        }

        // Clear button
        if (m_toolbarOptions.ShowClearButton)
        {
            if (m_toolbarOptions.ShowSearchBar) ImGui::SameLine();
            if (ImGui::Button("Clear"))
            {
                m_searchBuffer[0] = '\0';
                m_data.SetSearchFilter("");
            }
        }

        // Refresh button
        if (m_toolbarOptions.ShowRefreshButton)
        {
            if (m_toolbarOptions.ShowSearchBar || m_toolbarOptions.ShowClearButton)
                ImGui::SameLine();
            if (ImGui::Button("Refresh"))
                m_data.Refresh();
        }

        ImGui::Spacing();
    }

    //==========================================================================
    // Track Table - Just passes data from model to view
    //==========================================================================

    void LibraryWindow::DrawTrackTable()
    {
        // Set selection/playing state from data model
        m_trackTable.SetSelectedRow(m_data.GetSelectedIndex(), 
                                     m_data.GetSelectedTrack());
        m_trackTable.SetPlayingRow(m_data.GetPlayingIndex(), 
                                    m_data.GetPlayingTrack());

        // Draw the table with data from the model
        m_trackTable.Draw(m_data.GetTracks());

        // Handle sort requests from table header clicks
        HandleTableSorting();
    }

    //==========================================================================
    // Track Click Handler
    //==========================================================================

    void LibraryWindow::OnTrackClicked(const MusicTrack* track, int rowIndex)
    {
        if (!track) return;

        std::cout << "[LibraryWindow] Playing: " << track->GetTitle()
                  << " (" << track->GetDuration() << "s)\n";

        // Update data model selection
        m_data.SetSelectedIndex(rowIndex);
        m_data.SetPlayingIndex(rowIndex);

        // Trigger playback through controller
        if (m_playbackController)
        {
            m_playbackController->SetCurrentTrackList(m_data.GetTracks());
            m_playbackController->SelectTrack(*track);
            m_playbackController->Play();
        }
    }

    //==========================================================================
    // Sort Handling - Delegates to data model
    //==========================================================================

    void LibraryWindow::HandleTableSorting()
    {
        auto sortRequest = m_trackTable.GetSortRequest();
        if (sortRequest)
        {
            // Let the data model handle sorting
            m_data.ApplySort(sortRequest.value());
        }
    }

    //==========================================================================
    // Footer
    //==========================================================================

    void LibraryWindow::DrawFooter()
    {
        ImGui::Separator();
        ImGui::TextDisabled("Ready");
    }

} // namespace moosic