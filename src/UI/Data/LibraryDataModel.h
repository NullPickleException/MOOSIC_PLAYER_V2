#pragma once

#include "../../Models/MusicTrack.h"
#include "../Widgets/TrackTable.h"
#include <vector>
#include <string>
#include <functional>
#include <optional>

namespace moosic
{

class MusicLibrary;

class LibraryDataModel
{
public:
    explicit LibraryDataModel(MusicLibrary& library);

    const std::vector<const MusicTrack*>& GetTracks() const { return m_filteredTracks; }
    size_t GetTrackCount() const { return m_filteredTracks.size(); }
    
    const MusicTrack* GetTrackAt(int index) const;
    int FindTrackIndex(const MusicTrack* track) const;
    int FindTrackIndex(std::size_t trackId) const;

    void SetSearchFilter(const std::string& query);
    const std::string& GetSearchFilter() const { return m_searchQuery; }
    
    void ApplySort(const SortRequest& request);
    bool HasActiveSort() const { return m_currentSort.has_value(); }
    void ClearSort();

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

    void Refresh();
    bool NeedsRefresh() const;

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }

private:
    void RebuildMasterList();
    void ApplyFilterAndSort();
    bool MatchesSearch(const MusicTrack* track) const;

    MusicLibrary& m_sourceLibrary;
    
    std::vector<const MusicTrack*> m_allTracks;
    std::vector<const MusicTrack*> m_filteredTracks;
    
    std::string m_searchQuery;
    std::optional<SortRequest> m_currentSort;
    
    int m_selectedIndex = -1;
    int m_playingIndex = -1;
    
    size_t m_lastKnownTrackCount = 0;
    DataChangedCallback m_onDataChanged;
};

} // namespace moosic
