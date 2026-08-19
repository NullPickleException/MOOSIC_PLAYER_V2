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
    std::vector<PlaylistInfo>& GetAllPlaylists() { return m_playlists; }
    
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
    // Search & Filter
    //--------------------------------------------------------------------------

    // Search within library (for adding tracks to playlist)
    void SetAddTrackSearchFilter(const std::string& query);
    const std::string& GetAddTrackSearchFilter() const { return m_addTrackSearchQuery; }
    std::vector<const MusicTrack*> SearchLibraryForTracks() const;

    // Search within active playlist
    void SetSearchFilter(const std::string& query);
    const std::string& GetSearchFilter() const { return m_searchQuery; }

    // Playlist sidebar search
    void SetPlaylistSearchFilter(const std::string& query);
    const std::string& GetPlaylistSearchFilter() const { return m_playlistSearchQuery; }
    std::vector<const PlaylistInfo*> GetFilteredPlaylists() const;

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
    // Add Track Selection State
    //--------------------------------------------------------------------------

    void SetSelectedAddTrackIndex(int index);
    int GetSelectedAddTrackIndex() const { return m_selectedAddTrackIndex; }
    const MusicTrack* GetSelectedAddTrack() const;
    void ClearAddTrackSelection();

    //--------------------------------------------------------------------------
    // Sorting
    //--------------------------------------------------------------------------

    void ApplySort(const SortRequest& request);
    void ClearSort();
    const std::optional<SortRequest>& GetCurrentSort() const { return m_currentSort; }

    //--------------------------------------------------------------------------
    // Track Table Configurations
    //--------------------------------------------------------------------------

    void SetTrackTableConfig(const TrackTableConfig& config);
    const TrackTableConfig& GetTrackTableConfig() const { return m_trackTableConfig; }
    
    void SetAddTrackTableConfig(const TrackTableConfig& config);
    const TrackTableConfig& GetAddTrackTableConfig() const { return m_addTrackTableConfig; }

    //--------------------------------------------------------------------------
    // UI State
    //--------------------------------------------------------------------------

    // Popup visibility states
    void SetShowAddTrackPopup(bool show);
    bool GetShowAddTrackPopup() const { return m_showAddTrackPopup; }
    
    void SetShowCreatePlaylistPopup(bool show);
    bool GetShowCreatePlaylistPopup() const { return m_showCreatePlaylistPopup; }
    
    void SetShowRenamePopup(bool show);
    bool GetShowRenamePopup() const { return m_showRenamePopup; }

    // Playlist selection for adding tracks
    void SetSelectedPlaylistForAdd(int index);
    int GetSelectedPlaylistForAdd() const { return m_selectedPlaylistForAdd; }

    // Rename playlist index
    void SetRenamePlaylistIndex(int index);
    int GetRenamePlaylistIndex() const { return m_renamePlaylistIndex; }

    // Context menu state
    void SetContextRow(int row);
    int GetContextRow() const { return m_contextRow; }
    void SetContextTrack(const MusicTrack* track);
    const MusicTrack* GetContextTrack() const { return m_contextTrack; }

    //--------------------------------------------------------------------------
    // Library Access
    //--------------------------------------------------------------------------

    MusicLibrary& GetLibrary() { return m_library; }

    //--------------------------------------------------------------------------
    // Change Notification
    //--------------------------------------------------------------------------

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }
    
    // Called by DirectoryDataModel to trigger notification after bulk changes
    void NotifyDataChanged() { if (m_onDataChanged) m_onDataChanged(); }
    
    // Called by DirectoryDataModel to clear active playlist data
    void ClearActivePlaylistData()
    {
        m_activeTracks.clear();
        m_filteredTracks.clear();
    }
    
    // Called by DirectoryDataModel to rebuild after track removal
    void RebuildActiveTrackList();

private:
    void ApplyFilterAndSort();
    bool MatchesSearch(const MusicTrack* track) const;
    void RebuildFilteredPlaylists();

private:
    MusicLibrary& m_library;
    
    std::vector<PlaylistInfo> m_playlists;
    std::optional<size_t> m_activePlaylistIndex;
    
    std::vector<const MusicTrack*> m_activeTracks;      // Full active playlist tracks (unfiltered)
    std::vector<const MusicTrack*> m_filteredTracks;    // After filter + sort (what UI displays)
    std::vector<const PlaylistInfo*> m_filteredPlaylists; // After playlist search filter
    std::vector<const MusicTrack*> m_addTrackSearchResults; // Cached library search results
    
    // Search queries
    std::string m_searchQuery;           // Track search within active playlist
    std::string m_addTrackSearchQuery;   // Library search for adding tracks
    std::string m_playlistSearchQuery;   // Playlist sidebar search
    
    std::optional<SortRequest> m_currentSort;
    
    // Selection state
    int m_selectedIndex = -1;
    int m_playingIndex = -1;
    int m_selectedAddTrackIndex = -1;
    const MusicTrack* m_selectedAddTrack = nullptr;
    
    // UI State
    bool m_showAddTrackPopup = false;
    bool m_showCreatePlaylistPopup = false;
    bool m_showRenamePopup = false;
    int m_selectedPlaylistForAdd = -1;
    int m_renamePlaylistIndex = -1;
    int m_contextRow = -1;
    const MusicTrack* m_contextTrack = nullptr;
    
    // Track table configurations
    TrackTableConfig m_trackTableConfig;
    TrackTableConfig m_addTrackTableConfig;
    
    DataChangedCallback m_onDataChanged;
};

} // namespace moosic