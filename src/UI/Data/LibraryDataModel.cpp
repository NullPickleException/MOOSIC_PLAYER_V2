//==============================================================================
// UI/Data/LibraryDataModel.cpp
//==============================================================================

#include "LibraryDataModel.h"
#include "../../Models/MusicLibrary.h"
#include "../Widgets/TrackTable.h"

#include <algorithm>
#include <cctype>

namespace moosic
{

LibraryDataModel::LibraryDataModel(MusicLibrary &library)
    : m_sourceLibrary(library)
{
    m_tableConfig.Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
        TrackColumn::Album,
        TrackColumn::Genre,
        TrackColumn::Extension,
        TrackColumn::Duration};
    
    // ADD THIS - set VisibleColumns to match Columns
    m_tableConfig.VisibleColumns = m_tableConfig.Columns;
    
    m_tableConfig.Sortable = true;
    m_tableConfig.Resizable = true;
    m_tableConfig.Reorderable = true;
    m_tableConfig.Hideable = true;
    m_tableConfig.Borders = true;
    m_tableConfig.AlternateRows = true;

    Refresh();
}

    const MusicTrack *LibraryDataModel::GetTrackAt(int index) const
    {
        if (index >= 0 && index < static_cast<int>(m_filteredTracks.size()))
            return m_filteredTracks[index];
        return nullptr;
    }

    int LibraryDataModel::FindTrackIndex(const MusicTrack *track) const
    {
        if (!track)
            return -1;
        return FindTrackIndex(track->GetId());
    }

    int LibraryDataModel::FindTrackIndex(std::size_t trackId) const
    {
        for (size_t i = 0; i < m_filteredTracks.size(); ++i)
        {
            if (m_filteredTracks[i] && m_filteredTracks[i]->GetId() == trackId)
                return static_cast<int>(i);
        }
        return -1;
    }

    void LibraryDataModel::SetSearchFilter(const std::string &query)
    {
        if (m_searchQuery == query)
            return;
        m_searchQuery = query;
        ApplyFilterAndSort();
        if (m_onDataChanged)
            m_onDataChanged();
    }

    bool LibraryDataModel::MatchesSearch(const MusicTrack *track) const
    {
        if (!track)
            return false;
        if (m_searchQuery.empty())
            return true;

        std::string lowerQuery = m_searchQuery;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });

        auto matches = [&lowerQuery](const std::string &field) -> bool
        {
            std::string lower = field;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](unsigned char c)
                           { return std::tolower(c); });
            return lower.find(lowerQuery) != std::string::npos;
        };

        return matches(track->GetTitle()) ||
               matches(track->GetArtist()) ||
               matches(track->GetAlbum()) ||
               matches(track->GetGenre());
    }

    void LibraryDataModel::ApplySort(const SortRequest &request)
    {
        m_currentSort = request;

        std::sort(m_filteredTracks.begin(), m_filteredTracks.end(),
                  [&](const MusicTrack *a, const MusicTrack *b) -> bool
                  {
                      if (!a || !b)
                          return a != nullptr;
                      int result = 0;
                      switch (request.column)
                      {
                      case TrackColumn::Title:
                          result = a->GetTitle().compare(b->GetTitle());
                          break;
                      case TrackColumn::Artist:
                          result = a->GetArtist().compare(b->GetArtist());
                          break;
                      case TrackColumn::Album:
                          result = a->GetAlbum().compare(b->GetAlbum());
                          break;
                      case TrackColumn::Genre:
                          result = a->GetGenre().compare(b->GetGenre());
                          break;
                      case TrackColumn::Extension:
                      {
                          std::string ea = a->GetExtension(), eb = b->GetExtension();
                          std::transform(ea.begin(), ea.end(), ea.begin(), ::toupper);
                          std::transform(eb.begin(), eb.end(), eb.begin(), ::toupper);
                          result = ea.compare(eb);
                          break;
                      }
                      case TrackColumn::Duration:
                          result = static_cast<int>(a->GetDuration()) - static_cast<int>(b->GetDuration());
                          break;
                      }
                      return request.ascending ? (result < 0) : (result > 0);
                  });

        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::ClearSort()
    {
        m_currentSort = std::nullopt;
        ApplyFilterAndSort();
    }

    void LibraryDataModel::SetSelectedIndex(int index)
    {
        m_selectedIndex = index;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    const MusicTrack *LibraryDataModel::GetSelectedTrack() const
    {
        return GetTrackAt(m_selectedIndex);
    }

    void LibraryDataModel::ClearSelection()
    {
        m_selectedIndex = -1;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::SetPlayingIndex(int index)
    {
        m_playingIndex = index;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    const MusicTrack *LibraryDataModel::GetPlayingTrack() const
    {
        return GetTrackAt(m_playingIndex);
    }

    void LibraryDataModel::ClearPlaying()
    {
        m_playingIndex = -1;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::SetPlayingTrack(const MusicTrack *track)
    {
        if (track)
        {
            int i = FindTrackIndex(track);
            if (i >= 0)
            {
                m_playingIndex = i;
                m_selectedIndex = i;
            }
        }
        else
        {
            m_playingIndex = -1;
        }
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::SyncPlayingTrack(const MusicTrack *currentTrack)
    {
        if (currentTrack)
        {
            int i = FindTrackIndex(currentTrack);
            if (i >= 0 && i != m_playingIndex)
            {
                m_playingIndex = i;
                m_selectedIndex = i;
                if (m_onDataChanged)
                    m_onDataChanged();
            }
        }
        else if (m_playingIndex != -1)
        {
            m_playingIndex = -1;
            m_selectedIndex = -1;
            if (m_onDataChanged)
                m_onDataChanged();
        }
    }

    //==============================================================================
    // Track mutation
    //==============================================================================

    void LibraryDataModel::UpdateTrackMetadata(std::size_t trackId,
                                               const std::string &title,
                                               const std::string &artist,
                                               const std::string &album)
    {
        auto &tracks = m_sourceLibrary.GetTracks();
        for (auto &track : tracks)
        {
            if (track.GetId() == trackId)
            {
                track.UpdateTitle(title);
                track.UpdateArtist(artist);
                track.UpdateAlbum(album);
                // Keep filtered list consistent
                ApplyFilterAndSort();
                if (m_onDataChanged)
                    m_onDataChanged();
                return;
            }
        }
    }

    //==============================================================================
    // Table Configuration
    //==============================================================================

    void LibraryDataModel::SetTableConfig(const TrackTableConfig &config)
    {
        m_tableConfig = config;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::SetVisibleColumns(const std::vector<TrackColumn> &columns)
    {
        m_tableConfig.Columns = columns;
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::ShowColumn(TrackColumn column)
    {
        if (IsColumnVisible(column))
            return;
        m_tableConfig.Columns.push_back(column);
        if (m_onDataChanged)
            m_onDataChanged();
    }

    void LibraryDataModel::HideColumn(TrackColumn column)
    {
        auto &cols = m_tableConfig.Columns;
        cols.erase(std::remove(cols.begin(), cols.end(), column), cols.end());
        if (m_onDataChanged)
            m_onDataChanged();
    }

    bool LibraryDataModel::IsColumnVisible(TrackColumn column) const
    {
        const auto &cols = m_tableConfig.Columns;
        return std::find(cols.begin(), cols.end(), column) != cols.end();
    }

    void LibraryDataModel::MoveColumn(int fromIndex, int toIndex)
    {
        auto &cols = m_tableConfig.Columns;
        if (fromIndex < 0 || fromIndex >= static_cast<int>(cols.size()) ||
            toIndex < 0 || toIndex >= static_cast<int>(cols.size()) ||
            fromIndex == toIndex)
            return;

        TrackColumn col = cols[fromIndex];
        cols.erase(cols.begin() + fromIndex);
        cols.insert(cols.begin() + toIndex, col);
        if (m_onDataChanged)
            m_onDataChanged();
    }

    //==============================================================================
    // Refresh
    //==============================================================================

    void LibraryDataModel::Refresh()
    {
        m_allTracks.clear();
        m_filteredTracks.clear();

        const auto &sourceTracks = m_sourceLibrary.GetTracks();
        m_allTracks.reserve(sourceTracks.size() + 100);
        m_filteredTracks.reserve(sourceTracks.size() + 100);

        for (const auto &track : sourceTracks)
            m_allTracks.push_back(&track);

        ApplyFilterAndSort();
        m_lastKnownTrackCount = m_sourceLibrary.GetTrackCount();
        if (m_onDataChanged)
            m_onDataChanged();
    }

    bool LibraryDataModel::NeedsRefresh() const
    {
        return m_sourceLibrary.GetTrackCount() != m_lastKnownTrackCount;
    }

    void LibraryDataModel::ApplyFilterAndSort()
    {
        m_filteredTracks.clear();
        if (m_searchQuery.empty())
            m_filteredTracks = m_allTracks;
        else
            for (auto *track : m_allTracks)
                if (MatchesSearch(track))
                    m_filteredTracks.push_back(track);

        if (m_currentSort.has_value())
        {
            auto s = m_currentSort;
            m_currentSort = std::nullopt;
            ApplySort(s.value());
        }

        if (m_selectedIndex >= static_cast<int>(m_filteredTracks.size()))
            m_selectedIndex = -1;
        if (m_playingIndex >= static_cast<int>(m_filteredTracks.size()))
            m_playingIndex = -1;
    }

} // namespace moosic