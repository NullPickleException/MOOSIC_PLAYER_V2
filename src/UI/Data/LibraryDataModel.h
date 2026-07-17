//==============================================================================
// UI/Data/LibraryDataModel.h
//==============================================================================
// Central data store for library tracks.
// Handles filtering, sorting, selection, and playing state.
// The window just reads from this and renders - no data ownership.
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"
#include "../Widgets/TrackTable.h"  // Full definition of SortRequest and TrackColumn
#include <vector>
#include <string>
#include <functional>
#include <optional>

namespace moosic
{

class MusicLibrary; // Forward declaration

class LibraryDataModel
{
public:
    explicit LibraryDataModel(MusicLibrary& library);

    //--------------------------------------------------------------------------
    // Data Access (read-only for views)
    //--------------------------------------------------------------------------

    const std::vector<const MusicTrack*>& GetTracks() const { return m_filteredTracks; }
    size_t GetTrackCount() const { return m_filteredTracks.size(); }
    
    const MusicTrack* GetTrackAt(int index) const;
    int FindTrackIndex(const MusicTrack* track) const;
    int FindTrackIndex(std::size_t trackId) const;

    //--------------------------------------------------------------------------
    // Filtering & Sorting
    //--------------------------------------------------------------------------

    void SetSearchFilter(const std::string& query);
    const std::string& GetSearchFilter() const { return m_searchQuery; }
    
    void ApplySort(const SortRequest& request);
    bool HasActiveSort() const { return m_currentSort.has_value(); }
    void ClearSort();

    //--------------------------------------------------------------------------
    // Selection State
    //--------------------------------------------------------------------------

    void SetSelectedIndex(int index);
    int GetSelectedIndex() const { return m_selectedIndex; }
    const MusicTrack* GetSelectedTrack() const;
    void ClearSelection();

    //--------------------------------------------------------------------------
    // Playing State
    //--------------------------------------------------------------------------

    void SetPlayingIndex(int index);
    int GetPlayingIndex() const { return m_playingIndex; }
    const MusicTrack* GetPlayingTrack() const;
    void ClearPlaying();
    
    void SetPlayingTrack(const MusicTrack* track);
    void SyncPlayingTrack(const MusicTrack* currentTrack);

    //--------------------------------------------------------------------------
    // Data Refresh
    //--------------------------------------------------------------------------

    void Refresh();                          // Reload all tracks from MusicLibrary
    bool NeedsRefresh() const;               // Check if library has changed

    //--------------------------------------------------------------------------
    // Change Notification
    //--------------------------------------------------------------------------

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }

private:
    void RebuildMasterList();                // Pull all tracks from source
    void ApplyFilterAndSort();               // Re-apply filter + sort to master list
    
    bool MatchesSearch(const MusicTrack* track) const;

private:
    MusicLibrary& m_sourceLibrary;
    
    // Master list - all tracks from MusicLibrary (unfiltered)
    std::vector<const MusicTrack*> m_allTracks;
    
    // Display list - after filter + sort applied
    std::vector<const MusicTrack*> m_filteredTracks;
    
    // State
    std::string m_searchQuery;
    std::optional<SortRequest> m_currentSort;
    
    int m_selectedIndex = -1;
    int m_playingIndex = -1;
    
    size_t m_lastKnownTrackCount = 0;        // For detecting changes
    
    // Notification
    DataChangedCallback m_onDataChanged;
};

} // namespace moosic