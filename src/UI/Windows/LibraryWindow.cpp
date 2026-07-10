#include "LibraryWindow.h"

#include <iostream>
#include <algorithm>
#include <imgui.h>

namespace moosic
{

    //==============================================================================
    // Constructor
    //==============================================================================

    LibraryWindow::LibraryWindow(MusicLibrary &library, PlaybackController *playbackController)
        : m_library(library), m_playbackController(playbackController)
    {
        //----------------------------------------------------------------------
        // Configure table columns
        //----------------------------------------------------------------------
        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
            TrackColumn::Extension,
            TrackColumn::Duration
        };
        m_trackTable.ApplyConfig(config);

        //----------------------------------------------------------------------
        // Style the table
        //----------------------------------------------------------------------
        TrackTableStyle style;
        style.TitleWidth = 350.0f;
        style.ArtistWidth = 180.0f;
        style.AlbumWidth = 180.0f;
        style.ExtensionWidth = 50.0f;
        style.DurationWidth = 80.0f;
        style.RowHeight = 15.0f;
        style.RowPlaying = ImVec4(0.0f, 0.70f, 0.0f, 0.80f);
        m_trackTable.ApplyStyle(style);
        
        //----------------------------------------------------------------------
        // Click handler - select and play track
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
        // Double click - same as single click
        //----------------------------------------------------------------------
        m_trackTable.OnRowDoubleClick([this](const MusicTrack *track, int rowIndex)
        {
            // Same behavior as single click
        });

        //----------------------------------------------------------------------
        // Initial track list build
        //----------------------------------------------------------------------
        RefreshTrackList();
    }

    //==============================================================================
    // Draw
    //==============================================================================

    void LibraryWindow::Draw()
    {
        SyncPlayingTrack();
        DrawHeader();
        DrawToolbar();
        DrawLibraryInfo();
        DrawTrackTable();
        HandleSorting();
        DrawFooter();
    }

    //==============================================================================
    // Section: Sync Playing Track
    //==============================================================================

    void LibraryWindow::SyncPlayingTrack()
    {
        if (!m_playbackController) return;
        
        const MusicTrack* currentTrack = m_playbackController->GetCurrentTrack();
        
        if (currentTrack)
        {
            std::size_t currentId = currentTrack->GetId();
            
            // Only update if track changed
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
            // No track playing
            m_playingTrackId = 0;
            m_trackTable.SetPlayingRow(-1, nullptr);
        }
    }

    //==============================================================================
    // Section: Header
    //==============================================================================

    void LibraryWindow::DrawHeader()
    {
        ImGui::Text("Music Library");
        ImGui::Separator();
    }

    //==============================================================================
    // Section: Toolbar
    //==============================================================================

    void LibraryWindow::DrawToolbar()
    {
        static char searchBuffer[256] = "";

        ImGui::SetNextItemWidth(300.0f);
        ImGui::InputTextWithHint("##Search", "Search title, artist or album...", 
                                 searchBuffer, sizeof(searchBuffer));
        ImGui::SameLine();

        if (ImGui::Button("Clear"))
        {
            searchBuffer[0] = '\0';
        }

        ImGui::SameLine();

        if (ImGui::Button("Refresh"))
        {
            RefreshTrackList();
        }
    }

    //==============================================================================
    // Section: Library Info
    //==============================================================================

    void LibraryWindow::DrawLibraryInfo()
    {
        // Auto-refresh if library changed
        if (m_library.GetTrackCount() != m_lastTrackCount)
        {
            RefreshTrackList();
        }

        ImGui::Spacing();
        ImGui::Text("Tracks: %zu", m_tracks.size());
        ImGui::SameLine();
        ImGui::TextDisabled("|");
        ImGui::SameLine();

        // Show currently playing track
        if (m_playingTrackId != 0)
        {
            const MusicTrack* track = FindTrackById(m_playingTrackId);
            if (track)
            {
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), 
                                   "Playing: %s", track->GetTitle().c_str());
            }
            else
            {
                ImGui::TextDisabled("Not playing");
            }
        }
        else
        {
            ImGui::TextDisabled("Not playing");
        }

        ImGui::Separator();
    }

    //==============================================================================
    // Section: Track Table
    //==============================================================================

    void LibraryWindow::DrawTrackTable()
    {
        m_trackTable.Draw(m_tracks);
    }

    //==============================================================================
    // Section: Sort Handling
    //==============================================================================

    void LibraryWindow::HandleSorting()
    {
        auto sortRequest = m_trackTable.GetSortRequest();
        if (!sortRequest) return;

        // Sort the track pointers
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

        // Update playback controller with sorted list
        if (m_playbackController)
        {
            m_playbackController->SetCurrentTrackList(m_tracks);
        }
    }

    //==============================================================================
    // Section: Footer
    //==============================================================================

    void LibraryWindow::DrawFooter()
    {
        ImGui::Separator();
        ImGui::TextDisabled("Ready");
    }

    //==============================================================================
    // Track List Management
    //==============================================================================

    void LibraryWindow::RefreshTrackList()
    {
        const auto& libraryTracks = m_library.GetTracks();
        
        m_tracks.clear();
        m_tracks.reserve(libraryTracks.size());

        // Build fresh pointer list from library
        for (const auto& track : libraryTracks)
        {
            m_tracks.push_back(&track);
        }

        m_lastTrackCount = libraryTracks.size();

        // Restore playing track selection if it exists
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
                // Track no longer exists
                m_playingTrackId = 0;
                m_trackTable.SetPlayingRow(-1, nullptr);
                m_trackTable.SetSelectedRow(-1, nullptr);
            }
        }
    }

    //==============================================================================
    // External API
    //==============================================================================

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

    //==============================================================================
    // Helpers
    //==============================================================================

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