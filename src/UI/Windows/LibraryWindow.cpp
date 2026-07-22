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

    LibraryWindow::LibraryWindow(LibraryDataModel &dataModel,
                                 PlaybackController *playbackController)
        : m_data(dataModel), m_playbackController(playbackController)
    {
        // Table configuration
        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
            TrackColumn::Extension,
            TrackColumn::Duration};
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
        m_toolbarOptions.SearchBarWidth = 500.0f;
        m_toolbarOptions.SearchHint = "Search title, artist or album...";

        // Setup search bar (dropdown mode only - does NOT filter main table)
        SetupSearchBar();

        // Row click callback - delegate to data model + playback
        m_trackTable.OnRowClick([this](const MusicTrack *track, int rowIndex)
                                { OnTrackClicked(track, rowIndex); });

        m_trackTable.OnRowDoubleClick([this](const MusicTrack *track, int rowIndex)
                                      { OnTrackClicked(track, rowIndex); });

        // Listen for data changes
        m_data.SetOnDataChanged([this]()
                                {
                                    // Data changed - next Draw() will pick it up
                                });
    }

    //==========================================================================
    // Main Draw
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
        ImGui::Separator();

        DrawTrackTable();
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

        if (!anyToolbar)
            return;

        // Search bar
        if (m_toolbarOptions.ShowSearchBar)
        {
            if (m_useDropdownSearch)
            {
                DrawDropdownSearch();
                m_searchBar.BlockExternalScroll(); // Block track table scroll immediately after dropdown draws
            }
            else
                DrawInlineSearch();
        }

        // Clear button (only for inline mode)
        if (m_toolbarOptions.ShowClearButton && !m_useDropdownSearch)
        {
            if (m_toolbarOptions.ShowSearchBar)
                ImGui::SameLine();
            if (ImGui::Button("Clear"))
            {
                m_searchBuffer[0] = '\0';
                m_data.SetSearchFilter("");
            }
        }

        // Refresh button
        if (m_toolbarOptions.ShowRefreshButton)
        {
            bool hasSearch = m_toolbarOptions.ShowSearchBar;
            bool hasClear = m_toolbarOptions.ShowClearButton && !m_useDropdownSearch;
            if (hasSearch || hasClear)
                ImGui::SameLine();
            if (ImGui::Button("Refresh"))
                m_data.Refresh();
        }

        ImGui::Spacing();
    }

    //==========================================================================
    // Dropdown Search (TrackSearchBar widget - does NOT filter main table)
    //==========================================================================

    void LibraryWindow::DrawDropdownSearch()
    {
        // Set width BEFORE drawing - this ensures the input uses the correct width
        m_searchBar.SetWidth(m_toolbarOptions.SearchBarWidth);
        m_searchBar.SetHint(m_toolbarOptions.SearchHint);
        m_searchBar.Draw();
    }

    //==========================================================================
    // Inline Search (original simple input - filters main table)
    //==========================================================================

    void LibraryWindow::DrawInlineSearch()
    {
        ImGui::SetNextItemWidth(m_toolbarOptions.SearchBarWidth);
        if (ImGui::InputTextWithHint("##Search",
                                     m_toolbarOptions.SearchHint.c_str(),
                                     m_searchBuffer, sizeof(m_searchBuffer)))
        {
            // Delegate filtering to data model (filters main track table)
            m_data.SetSearchFilter(m_searchBuffer);
        }
    }

    //==========================================================================
    // Track Table
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

    void LibraryWindow::OnTrackClicked(const MusicTrack *track, int rowIndex)
    {
        if (!track)
            return;

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
    // Sort Handling
    //==========================================================================

    void LibraryWindow::HandleTableSorting()
    {
        auto sortRequest = m_trackTable.GetSortRequest();
        if (sortRequest)
        {
            m_data.ApplySort(sortRequest.value());
        }
    }

    //==========================================================================
    // Search Bar Setup (dropdown mode - searches independently)
    //==========================================================================

    void LibraryWindow::SetupSearchBar()
    {
        m_searchBar.SetWidth(m_toolbarOptions.SearchBarWidth);
        m_searchBar.SetHint(m_toolbarOptions.SearchHint);

        // Search callback - searches tracks independently, does NOT filter main table
        m_searchBar.SetSearchCallback([this](const std::string &query) -> std::vector<TrackSearchResult>
                                      {
            // Clear any existing filter on the main table so it shows all tracks
            m_data.SetSearchFilter("");
            
            // Search through all tracks manually for dropdown display
            auto allTracks = m_data.GetTracks();
            std::vector<TrackSearchResult> results;
            
            std::string lowerQuery = query;
            std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                [](unsigned char c) { return std::tolower(c); });
            
            for (size_t i = 0; i < allTracks.size() && results.size() < 100; ++i)
            {
                std::string title = allTracks[i]->GetTitle();
                std::string artist = allTracks[i]->GetArtist();
                
                std::string lowerTitle = title;
                std::string lowerArtist = artist;
                std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                std::transform(lowerArtist.begin(), lowerArtist.end(), lowerArtist.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                
                if (lowerTitle.find(lowerQuery) != std::string::npos ||
                    lowerArtist.find(lowerQuery) != std::string::npos)
                {
                    TrackSearchResult r;
                    r.title = title;
                    r.artist = artist;
                    r.displayText = title + "  —  " + artist;
                    r.trackIndex = static_cast<int>(i);
                    results.push_back(r);
                }
            }
            return results; });

        // Select callback - plays the selected track from dropdown
        m_searchBar.SetSelectCallback([this](const TrackSearchResult &result)
                                      {
            auto tracks = m_data.GetTracks();
            if (result.trackIndex >= 0 && result.trackIndex < static_cast<int>(tracks.size()))
            {
                OnTrackClicked(tracks[result.trackIndex], result.trackIndex);
            } });
    }

} // namespace moosic