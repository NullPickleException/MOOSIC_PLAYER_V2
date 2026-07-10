#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Widgets/TrackTable.h"
#include "IWindow.h"
#include "../../Services/PlaybackController.h"

#include <vector>

namespace moosic
{

    class LibraryWindow : public IWindow
    {
    public:
        explicit LibraryWindow(MusicLibrary &library, PlaybackController *playbackController = nullptr);
        void Draw() override;
        
        // External API
        void UpdatePlayingTrack(const MusicTrack* track);
        const std::vector<const MusicTrack*>& GetCurrentTrackList() const { return m_tracks; }

    private:
        // Drawing sections
        void SyncPlayingTrack();
        void DrawHeader();
        void DrawToolbar();
        void DrawLibraryInfo();
        void DrawTrackTable();
        void HandleSorting();
        void DrawFooter();

        // Track management
        void RefreshTrackList();
        int FindTrackIndex(std::size_t trackId) const;
        const MusicTrack* FindTrackById(std::size_t trackId) const;

    private:
        MusicLibrary &m_library;
        PlaybackController *m_playbackController;
        TrackTable m_trackTable;

        std::vector<const MusicTrack *> m_tracks;
        size_t m_lastTrackCount = 0;
        std::size_t m_playingTrackId = 0;
    };

} // namespace moosic