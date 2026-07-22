//==============================================================================
// UI/Windows/PlaylistWindow.h
//==============================================================================

#pragma once

#include "../Data/PlaylistDataModel.h"
#include "../Widgets/TrackTable.h"
#include "../Widgets/PopupMenu.h"
#include "IWindow.h"
#include "../../Services/PlaybackController.h"
#include <string>

namespace moosic
{

    class PlaylistWindow : public IWindow
    {
    public:
        explicit PlaylistWindow(PlaylistDataModel &dataModel,
                                PlaybackController *playbackController = nullptr);

        void Draw() override;
        void ApplyTheme(const WindowTheme &theme) override { m_theme = theme; }
        void ApplyTrackTableTheme(const TrackTableStyle &theme)
        {
            m_trackTable.ApplyTheme(theme);
            m_addTrackTable.ApplyTheme(theme);
        }

    private:
        void DrawPlaylistSidebar();
        void DrawPlaylistContent();
        void DrawAddTrackPopup();
        void DrawCreatePlaylistPopup();
        void DrawRenamePlaylistPopup();

        void OnTrackClicked(const MusicTrack *track, int rowIndex);
        void HandleTableSorting();

    private:
        PlaylistDataModel &m_data;
        PlaybackController *m_playbackController;
        TrackTable m_trackTable;
        TrackTable m_addTrackTable;
        WindowTheme m_theme;

        // Sidebar splitter
        float m_sidebarWidth = 220.0f;
        static constexpr float MIN_SIDEBAR_WIDTH = 150.0f;
        static constexpr float MAX_SIDEBAR_WIDTH = 400.0f;

        // UI state
        char m_playlistSearchBuffer[256] = "";
        char m_newPlaylistNameBuffer[256] = "";
        char m_renamePlaylistBuffer[256] = "";
        char m_trackSearchBuffer[256] = "";
        char m_addTrackSearchBuffer[256] = "";

        bool m_showAddTrackPopup = false;
        bool m_showCreatePlaylistPopup = false;
        bool m_showRenamePopup = false;
        int m_selectedPlaylistForAdd = -1;
        int m_renamePlaylistIndex = -1;

        // Add track selection
        int m_selectedAddTrackIndex = -1;
        const MusicTrack *m_selectedAddTrack = nullptr;
    };

} // namespace moosic