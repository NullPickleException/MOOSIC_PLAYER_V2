//==============================================================================
// UI/Data/LibraryDataModel.cpp
//==============================================================================

#include "LibraryDataModel.h"
#include "../../Models/MusicLibrary.h"
#include "../Widgets/TrackTable.h" // For SortRequest, TrackColumn
#include <algorithm>
#include <cctype>

namespace moosic
{

    //==============================================================================
    // Constructor
    //==============================================================================

    LibraryDataModel::LibraryDataModel(MusicLibrary &library)
        : m_sourceLibrary(library)
    {
        Refresh();
    }

    //==============================================================================
    // Data Access
    //==============================================================================

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

    //==============================================================================
    // Filtering
    //==============================================================================

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
               matches(track->GetAlbum());
    }

    //==============================================================================
    // Sorting
    //==============================================================================

    void LibraryDataModel::ApplySort(const SortRequest &request)
    {
        m_currentSort = request;

        // Sort the filtered list in place
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

                      case TrackColumn::Extension:
                      {
                          std::string extA = a->GetExtension();
                          std::string extB = b->GetExtension();
                          std::transform(extA.begin(), extA.end(), extA.begin(), ::toupper);
                          std::transform(extB.begin(), extB.end(), extB.begin(), ::toupper);
                          result = extA.compare(extB);
                          break;
                      }

                      case TrackColumn::Duration:
                          result = static_cast<int>(a->GetDuration()) -
                                   static_cast<int>(b->GetDuration());
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
        // Re-apply just the filter to restore original order
        ApplyFilterAndSort();
    }

    //==============================================================================
    // Selection State
    //==============================================================================

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

    //==============================================================================
    // Playing State
    //==============================================================================

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
            int index = FindTrackIndex(track);
            if (index >= 0)
            {
                m_playingIndex = index;
                m_selectedIndex = index; // Auto-select playing track
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
            int index = FindTrackIndex(currentTrack);
            if (index >= 0 && index != m_playingIndex)
            {
                m_playingIndex = index;
                m_selectedIndex = index; // Also select the playing track

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
    // Data Refresh
    //==============================================================================

    void LibraryDataModel::Refresh()
    {
        RebuildMasterList();
        ApplyFilterAndSort();

        m_lastKnownTrackCount = m_sourceLibrary.GetTrackCount();

        if (m_onDataChanged)
            m_onDataChanged();
    }

    bool LibraryDataModel::NeedsRefresh() const
    {
        return m_sourceLibrary.GetTrackCount() != m_lastKnownTrackCount;
    }

    //==============================================================================
    // Internal Helpers
    //==============================================================================

    void LibraryDataModel::RebuildMasterList()
    {
        const auto &sourceTracks = m_sourceLibrary.GetTracks();

        m_allTracks.clear();
        m_allTracks.reserve(sourceTracks.size());

        for (const auto &track : sourceTracks)
            m_allTracks.push_back(&track);
    }

    void LibraryDataModel::ApplyFilterAndSort()
    {
        // Step 1: Apply search filter
        m_filteredTracks.clear();

        if (m_searchQuery.empty())
        {
            // No filter - use all tracks
            m_filteredTracks = m_allTracks;
        }
        else
        {
            // Filter by search query
            for (const auto *track : m_allTracks)
            {
                if (MatchesSearch(track))
                    m_filteredTracks.push_back(track);
            }
        }

        // Step 2: Re-apply sort if active
        if (m_currentSort.has_value())
        {
            // Save and restore - ApplySort works on m_filteredTracks
            auto savedSort = m_currentSort;
            m_currentSort = std::nullopt;
            ApplySort(savedSort.value());
        }

        // Invalidate indices if they're now out of bounds
        if (m_selectedIndex >= static_cast<int>(m_filteredTracks.size()))
            m_selectedIndex = -1;
        if (m_playingIndex >= static_cast<int>(m_filteredTracks.size()))
            m_playingIndex = -1;
    }

} // namespace moosic