//==============================================================================
// UI/Data/PlaylistDataModel.cpp
//==============================================================================

#include "PlaylistDataModel.h"
#include <algorithm>
#include <cctype>
#include <iostream>

namespace moosic
{

//==============================================================================
// Constructor
//==============================================================================

PlaylistDataModel::PlaylistDataModel(MusicLibrary& library)
    : m_library(library)
{
    // Initialize main playlist track table config - ALL columns available
    m_trackTableConfig.Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
        TrackColumn::Album,
        TrackColumn::Genre,
        TrackColumn::Extension,
        TrackColumn::Duration
    };
    m_trackTableConfig.VisibleColumns = m_trackTableConfig.Columns;
    m_trackTableConfig.Sortable = true;
    m_trackTableConfig.Resizable = true;
    m_trackTableConfig.Reorderable = true;
    m_trackTableConfig.Hideable = true;
    m_trackTableConfig.Borders = true;
    m_trackTableConfig.AlternateRows = true;
    
    // Initialize add track table config - ALL columns available
    m_addTrackTableConfig.Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
        TrackColumn::Album,
        TrackColumn::Genre,
        TrackColumn::Extension,
        TrackColumn::Duration
    };
    m_addTrackTableConfig.VisibleColumns = m_addTrackTableConfig.Columns;
    m_addTrackTableConfig.Sortable = true;
    m_addTrackTableConfig.Resizable = true;
    m_addTrackTableConfig.Reorderable = true;
    m_addTrackTableConfig.Hideable = true;
    m_addTrackTableConfig.Borders = true;
    m_addTrackTableConfig.AlternateRows = true;
    
    // Initialize filtered playlists
    RebuildFilteredPlaylists();
    
    // Initialize search results
    m_addTrackSearchResults = SearchLibraryForTracks();
}

//==============================================================================
// Playlist Management
//==============================================================================

void PlaylistDataModel::CreatePlaylist(const std::string& name)
{
    PlaylistInfo playlist;
    playlist.name = name;
    m_playlists.push_back(std::move(playlist));
    RebuildFilteredPlaylists();
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::DeletePlaylist(size_t playlistIndex)
{
    if (playlistIndex >= m_playlists.size()) return;
    
    m_playlists.erase(m_playlists.begin() + playlistIndex);
    
    if (m_activePlaylistIndex.has_value())
    {
        if (m_activePlaylistIndex.value() == playlistIndex)
        {
            m_activePlaylistIndex = std::nullopt;
            m_activeTracks.clear();
            m_filteredTracks.clear();
        }
        else if (m_activePlaylistIndex.value() > playlistIndex)
        {
            m_activePlaylistIndex = m_activePlaylistIndex.value() - 1;
        }
    }
    
    RebuildFilteredPlaylists();
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::RenamePlaylist(size_t playlistIndex, const std::string& newName)
{
    if (playlistIndex >= m_playlists.size()) return;
    m_playlists[playlistIndex].name = newName;
    RebuildFilteredPlaylists();
    
    if (m_onDataChanged) m_onDataChanged();
}

const PlaylistInfo* PlaylistDataModel::GetPlaylist(size_t index) const
{
    if (index < m_playlists.size())
        return &m_playlists[index];
    return nullptr;
}

void PlaylistDataModel::SetActivePlaylist(std::optional<size_t> index)
{
    m_activePlaylistIndex = index;
    m_selectedIndex = -1;
    m_playingIndex = -1;
    RebuildActiveTrackList();
    
    if (m_onDataChanged) m_onDataChanged();
}

const PlaylistInfo* PlaylistDataModel::GetActivePlaylist() const
{
    if (m_activePlaylistIndex.has_value())
        return GetPlaylist(m_activePlaylistIndex.value());
    return nullptr;
}

//==============================================================================
// Track Management
//==============================================================================

void PlaylistDataModel::AddTrackToPlaylist(size_t playlistIndex, std::size_t trackId)
{
    if (playlistIndex >= m_playlists.size()) return;
    
    auto& playlist = m_playlists[playlistIndex];
    
    // Don't add duplicates
    if (std::find(playlist.trackIds.begin(), playlist.trackIds.end(), trackId) != playlist.trackIds.end())
        return;
    
    playlist.trackIds.push_back(trackId);
    
    // Refresh if this is the active playlist
    if (m_activePlaylistIndex.has_value() && m_activePlaylistIndex.value() == playlistIndex)
        RebuildActiveTrackList();
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::RemoveTrackFromPlaylist(size_t playlistIndex, size_t trackIndexInPlaylist)
{
    if (playlistIndex >= m_playlists.size()) return;
    
    auto& playlist = m_playlists[playlistIndex];
    if (trackIndexInPlaylist >= playlist.trackIds.size()) return;
    
    playlist.trackIds.erase(playlist.trackIds.begin() + trackIndexInPlaylist);
    
    if (m_activePlaylistIndex.has_value() && m_activePlaylistIndex.value() == playlistIndex)
        RebuildActiveTrackList();
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::MoveTrack(size_t playlistIndex, size_t fromIndex, size_t toIndex)
{
    if (playlistIndex >= m_playlists.size()) return;
    
    auto& playlist = m_playlists[playlistIndex];
    if (fromIndex >= playlist.trackIds.size() || toIndex >= playlist.trackIds.size())
        return;
    
    auto id = playlist.trackIds[fromIndex];
    playlist.trackIds.erase(playlist.trackIds.begin() + fromIndex);
    playlist.trackIds.insert(playlist.trackIds.begin() + toIndex, id);
    
    if (m_activePlaylistIndex.has_value() && m_activePlaylistIndex.value() == playlistIndex)
        RebuildActiveTrackList();
    
    if (m_onDataChanged) m_onDataChanged();
}

std::vector<const MusicTrack*> PlaylistDataModel::GetPlaylistTracks(size_t playlistIndex) const
{
    std::vector<const MusicTrack*> tracks;
    
    if (playlistIndex >= m_playlists.size())
        return tracks;
    
    const auto& trackIds = m_playlists[playlistIndex].trackIds;
    const auto& libraryTracks = m_library.GetTracks();
    
    for (auto id : trackIds)
    {
        for (const auto& track : libraryTracks)
        {
            if (track.GetId() == id)
            {
                tracks.push_back(&track);
                break;
            }
        }
    }
    
    return tracks;
}

std::vector<const MusicTrack*> PlaylistDataModel::GetActivePlaylistTracks() const
{
    if (m_activePlaylistIndex.has_value())
        return GetPlaylistTracks(m_activePlaylistIndex.value());
    return {};
}

//==============================================================================
// Search & Filter
//==============================================================================

void PlaylistDataModel::SetAddTrackSearchFilter(const std::string& query)
{
    if (m_addTrackSearchQuery == query) return;
    m_addTrackSearchQuery = query;
    
    // Update cached search results
    m_addTrackSearchResults = SearchLibraryForTracks();
    
    ClearAddTrackSelection();
    if (m_onDataChanged) m_onDataChanged();
}

std::vector<const MusicTrack*> PlaylistDataModel::SearchLibraryForTracks() const
{
    if (m_addTrackSearchQuery.empty())
    {
        std::vector<const MusicTrack*> allTracks;
        const auto& libraryTracks = m_library.GetTracks();
        allTracks.reserve(libraryTracks.size());
        for (const auto& track : libraryTracks)
            allTracks.push_back(&track);
        return allTracks;
    }
    
    std::vector<const MusicTrack*> results;
    
    std::string lowerQuery = m_addTrackSearchQuery;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    auto matches = [&lowerQuery](const std::string& field) -> bool
    {
        std::string lower = field;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return lower.find(lowerQuery) != std::string::npos;
    };
    
    const auto& allTracks = m_library.GetTracks();
    for (const auto& track : allTracks)
    {
        if (matches(track.GetTitle()) || matches(track.GetArtist()) || matches(track.GetAlbum()) || matches(track.GetGenre()))
            results.push_back(&track);
    }
    
    return results;
}

void PlaylistDataModel::SetSearchFilter(const std::string& query)
{
    if (m_searchQuery == query) return;
    m_searchQuery = query;
    ApplyFilterAndSort();
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetPlaylistSearchFilter(const std::string& query)
{
    if (m_playlistSearchQuery == query) return;
    m_playlistSearchQuery = query;
    RebuildFilteredPlaylists();
    if (m_onDataChanged) m_onDataChanged();
}

std::vector<const PlaylistInfo*> PlaylistDataModel::GetFilteredPlaylists() const
{
    return m_filteredPlaylists;
}

//==============================================================================
// Data Access for Active Playlist
//==============================================================================

const MusicTrack* PlaylistDataModel::GetTrackAt(int index) const
{
    if (index >= 0 && index < static_cast<int>(m_filteredTracks.size()))
        return m_filteredTracks[index];
    return nullptr;
}

int PlaylistDataModel::FindTrackIndex(const MusicTrack* track) const
{
    if (!track) return -1;
    return FindTrackIndex(track->GetId());
}

int PlaylistDataModel::FindTrackIndex(std::size_t trackId) const
{
    for (size_t i = 0; i < m_filteredTracks.size(); ++i)
    {
        if (m_filteredTracks[i] && m_filteredTracks[i]->GetId() == trackId)
            return static_cast<int>(i);
    }
    return -1;
}

//==============================================================================
// Selection & Playing State
//==============================================================================

void PlaylistDataModel::SetSelectedIndex(int index)
{
    m_selectedIndex = index;
    if (m_onDataChanged) m_onDataChanged();
}

const MusicTrack* PlaylistDataModel::GetSelectedTrack() const
{
    return GetTrackAt(m_selectedIndex);
}

void PlaylistDataModel::ClearSelection()
{
    m_selectedIndex = -1;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetPlayingIndex(int index)
{
    m_playingIndex = index;
    if (m_onDataChanged) m_onDataChanged();
}

const MusicTrack* PlaylistDataModel::GetPlayingTrack() const
{
    return GetTrackAt(m_playingIndex);
}

void PlaylistDataModel::ClearPlaying()
{
    m_playingIndex = -1;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetPlayingTrack(const MusicTrack* track)
{
    if (track)
    {
        int index = FindTrackIndex(track);
        if (index >= 0)
        {
            m_playingIndex = index;
            m_selectedIndex = index;
        }
    }
    else
    {
        m_playingIndex = -1;
    }
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SyncPlayingTrack(const MusicTrack* currentTrack)
{
    if (currentTrack)
    {
        int index = FindTrackIndex(currentTrack);
        if (index >= 0 && index != m_playingIndex)
        {
            m_playingIndex = index;
            m_selectedIndex = index;
            if (m_onDataChanged) m_onDataChanged();
        }
    }
    else if (m_playingIndex != -1)
    {
        m_playingIndex = -1;
        m_selectedIndex = -1;
        if (m_onDataChanged) m_onDataChanged();
    }
}

//==============================================================================
// Add Track Selection State
//==============================================================================

void PlaylistDataModel::SetSelectedAddTrackIndex(int index)
{
    m_selectedAddTrackIndex = index;
    
    // Refresh search results to ensure they're up to date
    m_addTrackSearchResults = SearchLibraryForTracks();
    
    // Use cached search results (from library search, not active playlist)
    if (index >= 0 && index < static_cast<int>(m_addTrackSearchResults.size()))
    {
        m_selectedAddTrack = m_addTrackSearchResults[index];
    }
    else
    {
        m_selectedAddTrack = nullptr;
        m_selectedAddTrackIndex = -1;
    }
    
    if (m_onDataChanged) m_onDataChanged();
}

const MusicTrack* PlaylistDataModel::GetSelectedAddTrack() const
{
    // If we have a valid index but no track, try to get it from search results
    if (!m_selectedAddTrack && m_selectedAddTrackIndex >= 0 && 
        m_selectedAddTrackIndex < static_cast<int>(m_addTrackSearchResults.size()))
    {
        return m_addTrackSearchResults[m_selectedAddTrackIndex];
    }
    return m_selectedAddTrack;
}

void PlaylistDataModel::ClearAddTrackSelection()
{
    m_selectedAddTrackIndex = -1;
    m_selectedAddTrack = nullptr;
}

//==============================================================================
// Sorting
//==============================================================================

void PlaylistDataModel::ApplySort(const SortRequest& request)
{
    m_currentSort = request;
    ApplyFilterAndSort();
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::ClearSort()
{
    m_currentSort = std::nullopt;
    ApplyFilterAndSort();
    if (m_onDataChanged) m_onDataChanged();
}

//==============================================================================
// Track Table Configurations
//==============================================================================

void PlaylistDataModel::SetTrackTableConfig(const TrackTableConfig& config)
{
    m_trackTableConfig = config;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetAddTrackTableConfig(const TrackTableConfig& config)
{
    m_addTrackTableConfig = config;
    if (m_onDataChanged) m_onDataChanged();
}

//==============================================================================
// UI State
//==============================================================================

void PlaylistDataModel::SetShowAddTrackPopup(bool show)
{
    m_showAddTrackPopup = show;
    
    // When opening the popup, ensure search results are fresh
    if (show)
    {
        m_addTrackSearchResults = SearchLibraryForTracks();
    }
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetShowCreatePlaylistPopup(bool show)
{
    m_showCreatePlaylistPopup = show;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetShowRenamePopup(bool show)
{
    m_showRenamePopup = show;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetSelectedPlaylistForAdd(int index)
{
    m_selectedPlaylistForAdd = index;
    
    // Reset selection when changing target playlist
    ClearAddTrackSelection();
    
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetRenamePlaylistIndex(int index)
{
    m_renamePlaylistIndex = index;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetContextRow(int row)
{
    m_contextRow = row;
    if (m_onDataChanged) m_onDataChanged();
}

void PlaylistDataModel::SetContextTrack(const MusicTrack* track)
{
    m_contextTrack = track;
    if (m_onDataChanged) m_onDataChanged();
}

//==============================================================================
// Internal Helpers
//==============================================================================

void PlaylistDataModel::RebuildActiveTrackList()
{
    m_activeTracks = GetActivePlaylistTracks();
    ApplyFilterAndSort();
}

void PlaylistDataModel::RebuildFilteredPlaylists()
{
    m_filteredPlaylists.clear();
    
    if (m_playlistSearchQuery.empty())
    {
        for (const auto& playlist : m_playlists)
            m_filteredPlaylists.push_back(&playlist);
    }
    else
    {
        std::string lowerQuery = m_playlistSearchQuery;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        
        for (const auto& playlist : m_playlists)
        {
            std::string nameLower = playlist.name;
            std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            
            if (nameLower.find(lowerQuery) != std::string::npos)
                m_filteredPlaylists.push_back(&playlist);
        }
    }
}

void PlaylistDataModel::ApplyFilterAndSort()
{
    m_filteredTracks.clear();
    
    if (m_searchQuery.empty())
    {
        m_filteredTracks = m_activeTracks;
    }
    else
    {
        for (const auto* track : m_activeTracks)
        {
            if (MatchesSearch(track))
                m_filteredTracks.push_back(track);
        }
    }
    
    if (m_currentSort.has_value())
    {
        auto& request = m_currentSort.value();
        std::sort(m_filteredTracks.begin(), m_filteredTracks.end(),
                  [&](const MusicTrack* a, const MusicTrack* b) -> bool
                  {
                      if (!a || !b) return a != nullptr;
                      
                      int result = 0;
                      switch (request.column)
                      {
                      case TrackColumn::Title:
                          result = a->GetTitle().compare(b->GetTitle()); break;
                      case TrackColumn::Artist:
                          result = a->GetArtist().compare(b->GetArtist()); break;
                      case TrackColumn::Album:
                          result = a->GetAlbum().compare(b->GetAlbum()); break;
                      case TrackColumn::Genre:
                          result = a->GetGenre().compare(b->GetGenre()); break;
                      case TrackColumn::Duration:
                          result = static_cast<int>(a->GetDuration()) - static_cast<int>(b->GetDuration()); break;
                      case TrackColumn::Extension:
                      {
                          std::string extA = a->GetExtension();
                          std::string extB = b->GetExtension();
                          std::transform(extA.begin(), extA.end(), extA.begin(), ::toupper);
                          std::transform(extB.begin(), extB.end(), extB.begin(), ::toupper);
                          result = extA.compare(extB);
                          break;
                      }
                      }
                      
                      return request.ascending ? (result < 0) : (result > 0);
                  });
    }
    
    if (m_selectedIndex >= static_cast<int>(m_filteredTracks.size()))
        m_selectedIndex = -1;
    if (m_playingIndex >= static_cast<int>(m_filteredTracks.size()))
        m_playingIndex = -1;
}

bool PlaylistDataModel::MatchesSearch(const MusicTrack* track) const
{
    if (!track) return false;
    if (m_searchQuery.empty()) return true;
    
    std::string lowerQuery = m_searchQuery;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    
    auto matches = [&lowerQuery](const std::string& field) -> bool
    {
        std::string lower = field;
        std::transform(lower.begin(), lower.end(), lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return lower.find(lowerQuery) != std::string::npos;
    };
    
    return matches(track->GetTitle()) || matches(track->GetArtist()) || matches(track->GetAlbum()) || matches(track->GetGenre());
}

} // namespace moosic