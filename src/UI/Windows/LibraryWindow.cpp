//==============================================================================
// LibraryWindow.cpp
//==============================================================================

#include "LibraryWindow.h"
#include "../Theme/Theme.h"
#include <iostream>
#include <algorithm>
#include <imgui.h>

namespace moosic
{

    //==========================================================================
    // Constructor
    //==========================================================================

    LibraryWindow::LibraryWindow(MusicLibrary &library, PlaybackController *playbackController)
        : m_library(library), m_playbackController(playbackController)
    {
        //----------------------------------------------------------------------
        // Table configuration (columns, sortable, resizable, etc.)
        //----------------------------------------------------------------------
        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
            TrackColumn::Extension,
            TrackColumn::Duration};
        m_trackTable.ApplyConfig(config);

        //----------------------------------------------------------------------
        // Layout-only style (widths, row height) — NO colors
        // Colors come from the theme via ApplyTrackTableTheme()
        //----------------------------------------------------------------------
        TrackTableStyle style;
        style.TitleWidth = 350.0f;
        style.ArtistWidth = 180.0f;
        style.AlbumWidth = 180.0f;
        style.ExtensionWidth = 50.0f;
        style.DurationWidth = 80.0f;
        style.RowHeight = 18.0f;
        m_trackTable.ApplyTheme(style);

        //----------------------------------------------------------------------
        // Default toolbar options
        //----------------------------------------------------------------------
        m_toolbarOptions.ShowSearchBar = true;
        m_toolbarOptions.ShowRefreshButton = true;
        m_toolbarOptions.ShowClearButton = false;
        m_toolbarOptions.ShowTrackCount = true;
        m_toolbarOptions.ShowBrandHeader = true;
        m_toolbarOptions.BrandText = "MOOSIC LIBRARY";
        m_toolbarOptions.SearchBarWidth = 300.0f;
        m_toolbarOptions.SearchHint = "Search title, artist or album...";

        //----------------------------------------------------------------------
        // Row click callback — play the selected track
        //----------------------------------------------------------------------
        m_trackTable.OnRowClick([this](const MusicTrack *track, int rowIndex)
        {
            if (!track) return;
            
            std::cout << "[LibraryWindow] Playing: " << track->GetTitle() 
                      << " (" << track->GetDuration() << "s)\n";
            
            if (m_playbackController)
            {
                m_playbackController->SetCurrentTrackList(m_tracks);
                m_playbackController->SelectTrack(*track);
                m_playbackController->Play();
            }
            
            m_trackTable.SetSelectedRow(rowIndex, track);
            m_trackTable.SetPlayingRow(rowIndex, track);
            m_playingTrackId = track->GetId();
        });

        //----------------------------------------------------------------------
        // Row double-click callback — same as single click
        //----------------------------------------------------------------------
        m_trackTable.OnRowDoubleClick([this](const MusicTrack *track, int rowIndex)
        {
            // Same behavior as single click
        });

        RefreshTrackList();
    }

    //==========================================================================
    // Main Draw
    //==========================================================================

    void LibraryWindow::Draw()
    {
        // ── Auto-refresh: detect when library has new tracks ──
        if (m_library.GetTrackCount() != m_lastTrackCount)
        {
            RefreshTrackList();
        }

        SyncPlayingTrack();
        DrawHeader();
        DrawToolbar();
        DrawTrackTable();
        HandleSorting();
        DrawFooter();
    }

    //==========================================================================
    // Sync Playing Track
    //==========================================================================

    void LibraryWindow::SyncPlayingTrack()
    {
        if (!m_playbackController) return;
        
        const MusicTrack* currentTrack = m_playbackController->GetCurrentTrack();
        
        if (currentTrack)
        {
            std::size_t currentId = currentTrack->GetId();
            
            if (currentId != m_playingTrackId)
            {
                m_playingTrackId = currentId;
                int index = FindTrackIndex(currentId);
                
                if (index >= 0)
                {
                    m_trackTable.SetPlayingRow(index, m_tracks[index]);
                    m_trackTable.SetSelectedRow(index, m_tracks[index]);
                }
            }
        }
        else if (m_playingTrackId != 0)
        {
            m_playingTrackId = 0;
            m_trackTable.SetPlayingRow(-1, nullptr);
        }
    }

    //==========================================================================
    // Header — branded title + optional track count
    //==========================================================================

    void LibraryWindow::DrawHeader()
    {
        if (!m_toolbarOptions.ShowBrandHeader && !m_toolbarOptions.ShowTrackCount)
        {
            ImGui::Separator();
            return;
        }

        if (m_toolbarOptions.ShowBrandHeader)
        {
            ImGui::TextColored(m_theme.BrandText, "%s", m_toolbarOptions.BrandText.c_str());
        }

        if (m_toolbarOptions.ShowTrackCount)
        {
            if (m_toolbarOptions.ShowBrandHeader)
                ImGui::SameLine();
            ImGui::Text("(%zu Tracks)", m_tracks.size());
        }

        ImGui::Separator();
    }

    //==========================================================================
    // Toolbar — configurable search, refresh, clear
    //==========================================================================

    void LibraryWindow::DrawToolbar()
    {
        bool anyToolbarElement = m_toolbarOptions.ShowSearchBar ||
                                 m_toolbarOptions.ShowRefreshButton ||
                                 m_toolbarOptions.ShowClearButton;

        if (!anyToolbarElement)
            return;

        static char searchBuffer[256] = "";

        // ── Search bar ──
        if (m_toolbarOptions.ShowSearchBar)
        {
            ImGui::SetNextItemWidth(m_toolbarOptions.SearchBarWidth);
            ImGui::InputTextWithHint("##Search",
                                     m_toolbarOptions.SearchHint.c_str(),
                                     searchBuffer, sizeof(searchBuffer));
        }

        // ── Clear button ──
        if (m_toolbarOptions.ShowClearButton)
        {
            if (m_toolbarOptions.ShowSearchBar)
                ImGui::SameLine();

            if (ImGui::Button("Clear"))
            {
                searchBuffer[0] = '\0';
            }
        }

        // ── Refresh button ──
        if (m_toolbarOptions.ShowRefreshButton)
        {
            if (m_toolbarOptions.ShowSearchBar || m_toolbarOptions.ShowClearButton)
                ImGui::SameLine();

            if (ImGui::Button("Refresh"))
            {
                RefreshTrackList();
            }
        }

        ImGui::Spacing();
    }

    //==========================================================================
    // Track Table
    //==========================================================================

    void LibraryWindow::DrawTrackTable()
    {
        m_trackTable.Draw(m_tracks);
    }

    //==========================================================================
    // Sort Handling
    //==========================================================================

    void LibraryWindow::HandleSorting()
    {
        auto sortRequest = m_trackTable.GetSortRequest();
        if (!sortRequest) return;

        std::sort(m_tracks.begin(), m_tracks.end(),
            [&](const MusicTrack* a, const MusicTrack* b)
            {
                if (!a || !b) return false;
                
                switch (sortRequest->column)
                {
                    case TrackColumn::Title:
                        return sortRequest->ascending ? 
                               a->GetTitle() < b->GetTitle() : 
                               a->GetTitle() > b->GetTitle();

                    case TrackColumn::Artist:
                        return sortRequest->ascending ? 
                               a->GetArtist() < b->GetArtist() : 
                               a->GetArtist() > b->GetArtist();

                    case TrackColumn::Album:
                        return sortRequest->ascending ? 
                               a->GetAlbum() < b->GetAlbum() : 
                               a->GetAlbum() > b->GetAlbum();

                    case TrackColumn::Extension:
                    {
                        std::string extA = a->GetExtension();
                        std::string extB = b->GetExtension();
                        std::transform(extA.begin(), extA.end(), extA.begin(), ::toupper);
                        std::transform(extB.begin(), extB.end(), extB.begin(), ::toupper);
                        return sortRequest->ascending ? extA < extB : extA > extB;
                    }

                    case TrackColumn::Duration:
                        return sortRequest->ascending ? 
                               a->GetDuration() < b->GetDuration() : 
                               a->GetDuration() > b->GetDuration();
                }
                return false;
            });

        if (m_playbackController)
        {
            m_playbackController->SetCurrentTrackList(m_tracks);
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

    //==========================================================================
    // Refresh Track List
    //==========================================================================

    void LibraryWindow::RefreshTrackList()
    {
        const auto& libraryTracks = m_library.GetTracks();
        
        m_tracks.clear();
        m_tracks.reserve(libraryTracks.size());

        for (const auto& track : libraryTracks)
        {
            m_tracks.push_back(&track);
        }

        m_lastTrackCount = libraryTracks.size();

        if (m_playingTrackId != 0)
        {
            int index = FindTrackIndex(m_playingTrackId);
            if (index >= 0)
            {
                m_trackTable.SetPlayingRow(index, m_tracks[index]);
                m_trackTable.SetSelectedRow(index, m_tracks[index]);
            }
            else
            {
                m_playingTrackId = 0;
                m_trackTable.SetPlayingRow(-1, nullptr);
                m_trackTable.SetSelectedRow(-1, nullptr);
            }
        }
    }

    //==========================================================================
    // Update Playing Track (external call)
    //==========================================================================

    void LibraryWindow::UpdatePlayingTrack(const MusicTrack* track)
    {
        if (track)
        {
            m_playingTrackId = track->GetId();
            int index = FindTrackIndex(m_playingTrackId);
            if (index >= 0)
            {
                m_trackTable.SetSelectedRow(index, m_tracks[index]);
                m_trackTable.SetPlayingRow(index, m_tracks[index]);
            }
        }
        else
        {
            m_playingTrackId = 0;
            m_trackTable.SetPlayingRow(-1, nullptr);
        }
    }

    //==========================================================================
    // Helpers
    //==========================================================================

    int LibraryWindow::FindTrackIndex(std::size_t trackId) const
    {
        for (size_t i = 0; i < m_tracks.size(); ++i)
        {
            if (m_tracks[i] && m_tracks[i]->GetId() == trackId)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    const MusicTrack* LibraryWindow::FindTrackById(std::size_t trackId) const
    {
        for (const auto* track : m_tracks)
        {
            if (track && track->GetId() == trackId)
            {
                return track;
            }
        }
        return nullptr;
    }

} // namespace moosic