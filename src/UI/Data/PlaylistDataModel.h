//==============================================================================
// UI/Data/PlaylistDataModel.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Widgets/TrackTable.h"
#include <string>
#include <vector>
#include <functional>
#include <optional>

namespace moosic
{

struct PlaylistInfo
{
    std::string name;
    std::vector<std::size_t> trackIds;
};

class PlaylistDataModel
{
public:
    explicit PlaylistDataModel(MusicLibrary& library);

    //--------------------------------------------------------------------------
    // Playlist Management
    //--------------------------------------------------------------------------

    void CreatePlaylist(const std::string& name);
    void DeletePlaylist(size_t playlistIndex);
    void RenamePlaylist(size_t playlistIndex, const std::string& newName);
    
    size_t GetPlaylistCount() const { return m_playlists.size(); }
    const PlaylistInfo* GetPlaylist(size_t index) const;
    const std::vector<PlaylistInfo>& GetAllPlaylists() const { return m_playlists; }
    
    void SetActivePlaylist(std::optional<size_t> index);
    std::optional<size_t> GetActivePlaylistIndex() const { return m_activePlaylistIndex; }
    const PlaylistInfo* GetActivePlaylist() const;

    //--------------------------------------------------------------------------
    // Track Management
    //--------------------------------------------------------------------------

    void AddTrackToPlaylist(size_t playlistIndex, std::size_t trackId);
    void RemoveTrackFromPlaylist(size_t playlistIndex, size_t trackIndexInPlaylist);
    void MoveTrack(size_t playlistIndex, size_t fromIndex, size_t toIndex);
    
    std::vector<const MusicTrack*> GetPlaylistTracks(size_t playlistIndex) const;
    std::vector<const MusicTrack*> GetActivePlaylistTracks() const;

    //--------------------------------------------------------------------------
    // Search within library (for adding tracks to playlist)
    //--------------------------------------------------------------------------

    void SetAddTrackSearchFilter(const std::string& query);
    const std::string& GetAddTrackSearchFilter() const { return m_addTrackSearchQuery; }
    std::vector<const MusicTrack*> SearchLibraryForTracks() const;

    //--------------------------------------------------------------------------
    // Data Access for Active Playlist (FILTERED + SORTED)
    //--------------------------------------------------------------------------

    const std::vector<const MusicTrack*>& GetFilteredTracks() const { return m_filteredTracks; }
    size_t GetFilteredTrackCount() const { return m_filteredTracks.size(); }
    const MusicTrack* GetTrackAt(int index) const;
    int FindTrackIndex(const MusicTrack* track) const;
    int FindTrackIndex(std::size_t trackId) const;

    //--------------------------------------------------------------------------
    // Selection & Playing State
    //--------------------------------------------------------------------------

    void SetSelectedIndex(int index);
    int GetSelectedIndex() const { return m_selectedIndex; }
    const MusicTrack* GetSelectedTrack() const;
    void ClearSelection();

    void SetPlayingIndex(int index);
    int GetPlayingIndex() const { return m_playingIndex; }
    const MusicTrack* GetPlayingTrack() const;
    void ClearPlaying();
    void SetPlayingTrack(const MusicTrack* track);
    void SyncPlayingTrack(const MusicTrack* currentTrack);

    //--------------------------------------------------------------------------
    // Sorting
    //--------------------------------------------------------------------------

    void ApplySort(const SortRequest& request);
    void ClearSort();

    //--------------------------------------------------------------------------
    // Search within active playlist
    //--------------------------------------------------------------------------

    void SetSearchFilter(const std::string& query);
    const std::string& GetSearchFilter() const { return m_searchQuery; }

    //--------------------------------------------------------------------------
    // Change Notification
    //--------------------------------------------------------------------------

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }

private:
    void RebuildActiveTrackList();
    void ApplyFilterAndSort();
    bool MatchesSearch(const MusicTrack* track) const;

private:
    MusicLibrary& m_library;
    
    std::vector<PlaylistInfo> m_playlists;
    std::optional<size_t> m_activePlaylistIndex;
    
    std::vector<const MusicTrack*> m_activeTracks;      // Full active playlist tracks (unfiltered)
    std::vector<const MusicTrack*> m_filteredTracks;    // After filter + sort (what UI displays)
    
    std::string m_searchQuery;
    std::string m_addTrackSearchQuery;
    std::optional<SortRequest> m_currentSort;
    
    int m_selectedIndex = -1;
    int m_playingIndex = -1;
    
    DataChangedCallback m_onDataChanged;
};

} // namespace moosic