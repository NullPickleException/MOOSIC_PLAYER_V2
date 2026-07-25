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
        if (!track) return -1;
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
        if (m_searchQuery == query) return;
        m_searchQuery = query;
        ApplyFilterAndSort();
        if (m_onDataChanged) m_onDataChanged();
    }

    bool LibraryDataModel::MatchesSearch(const MusicTrack *track) const
    {
        if (!track) return false;
        if (m_searchQuery.empty()) return true;

        std::string lowerQuery = m_searchQuery;
        std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        auto matches = [&lowerQuery](const std::string &field) -> bool
        {
            std::string lower = field;
            std::transform(lower.begin(), lower.end(), lower.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            return lower.find(lowerQuery) != std::string::npos;
        };

        return matches(track->GetTitle()) ||
               matches(track->GetArtist()) ||
               matches(track->GetAlbum());
    }

    void LibraryDataModel::ApplySort(const SortRequest &request)
    {
        m_currentSort = request;

        std::sort(m_filteredTracks.begin(), m_filteredTracks.end(),
                  [&](const MusicTrack *a, const MusicTrack *b) -> bool
                  {
                      if (!a || !b) return a != nullptr;
                      int result = 0;
                      switch (request.column)
                      {
                      case TrackColumn::Title: result = a->GetTitle().compare(b->GetTitle()); break;
                      case TrackColumn::Artist: result = a->GetArtist().compare(b->GetArtist()); break;
                      case TrackColumn::Album: result = a->GetAlbum().compare(b->GetAlbum()); break;
                      case TrackColumn::Extension: {
                          std::string ea = a->GetExtension(), eb = b->GetExtension();
                          std::transform(ea.begin(), ea.end(), ea.begin(), ::toupper);
                          std::transform(eb.begin(), eb.end(), eb.begin(), ::toupper);
                          result = ea.compare(eb); break;
                      }
                      case TrackColumn::Duration: result = (int)a->GetDuration() - (int)b->GetDuration(); break;
                      }
                      return request.ascending ? (result < 0) : (result > 0);
                  });

        if (m_onDataChanged) m_onDataChanged();
    }

    void LibraryDataModel::ClearSort() { m_currentSort = std::nullopt; ApplyFilterAndSort(); }

    void LibraryDataModel::SetSelectedIndex(int index) { m_selectedIndex = index; if (m_onDataChanged) m_onDataChanged(); }
    const MusicTrack *LibraryDataModel::GetSelectedTrack() const { return GetTrackAt(m_selectedIndex); }
    void LibraryDataModel::ClearSelection() { m_selectedIndex = -1; if (m_onDataChanged) m_onDataChanged(); }

    void LibraryDataModel::SetPlayingIndex(int index) { m_playingIndex = index; if (m_onDataChanged) m_onDataChanged(); }
    const MusicTrack *LibraryDataModel::GetPlayingTrack() const { return GetTrackAt(m_playingIndex); }
    void LibraryDataModel::ClearPlaying() { m_playingIndex = -1; if (m_onDataChanged) m_onDataChanged(); }

    void LibraryDataModel::SetPlayingTrack(const MusicTrack *track)
    {
        if (track) { int i = FindTrackIndex(track); if (i >= 0) { m_playingIndex = i; m_selectedIndex = i; } }
        else m_playingIndex = -1;
        if (m_onDataChanged) m_onDataChanged();
    }

    void LibraryDataModel::SyncPlayingTrack(const MusicTrack *currentTrack)
    {
        if (currentTrack) { int i = FindTrackIndex(currentTrack); if (i >= 0 && i != m_playingIndex) { m_playingIndex = i; m_selectedIndex = i; if (m_onDataChanged) m_onDataChanged(); } }
        else if (m_playingIndex != -1) { m_playingIndex = -1; m_selectedIndex = -1; if (m_onDataChanged) m_onDataChanged(); }
    }

    void LibraryDataModel::Refresh()
    {
        // KEY FIX: Reserve space BEFORE rebuilding pointers
        // This prevents reallocation when AddTrack is called later
        m_allTracks.clear();
        m_filteredTracks.clear();
        
        const auto &sourceTracks = m_sourceLibrary.GetTracks();
        m_allTracks.reserve(sourceTracks.size() + 100); // Extra space for future adds
        m_filteredTracks.reserve(sourceTracks.size() + 100);
        
        for (const auto &track : sourceTracks)
            m_allTracks.push_back(&track);

        ApplyFilterAndSort();
        m_lastKnownTrackCount = m_sourceLibrary.GetTrackCount();
        if (m_onDataChanged) m_onDataChanged();
    }

    bool LibraryDataModel::NeedsRefresh() const
    {
        return m_sourceLibrary.GetTrackCount() != m_lastKnownTrackCount;
    }

    void LibraryDataModel::RebuildMasterList()
    {
        // NOT USED - Refresh() does this directly now
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

        if (m_currentSort.has_value()) { auto s = m_currentSort; m_currentSort = std::nullopt; ApplySort(s.value()); }
        if (m_selectedIndex >= (int)m_filteredTracks.size()) m_selectedIndex = -1;
        if (m_playingIndex >= (int)m_filteredTracks.size()) m_playingIndex = -1;
    }

} // namespace moosic