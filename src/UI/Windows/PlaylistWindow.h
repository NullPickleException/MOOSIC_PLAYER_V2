//==============================================================================
// UI/Windows/PlaylistWindow.h
//==============================================================================

#pragma once

#include "IWindow.h"
#include "../Widgets/TrackTable.h"
#include "../Widgets/PopupMenu.h"
#include "../Widgets/EditTrackDialog.h"
#include "../Data/PlaylistDataModel.h"
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
        void ApplyContextMenuTheme(const PopupMenuTheme &theme)
        {
            m_trackContextMenu.ApplyTheme(theme);
            m_playlistContextMenu.ApplyTheme(theme);
        }

    private:
        void DrawPlaylistSidebar();
        void DrawPlaylistContent();
        void DrawAddTrackPopup();
        void DrawCreatePlaylistPopup();
        void DrawRenamePlaylistPopup();

        void OnTrackClicked(const MusicTrack *track, int rowIndex);

    private:
        PlaylistDataModel &m_data;
        PlaybackController *m_playbackController;
        TrackTable m_trackTable;
        TrackTable m_addTrackTable;
        WindowTheme m_theme;

        // ── Context Menus ───────────────────────────
        ContextMenu m_trackContextMenu;
        ContextMenu m_playlistContextMenu;

        // ── Sidebar Splitter ────────────────────────
        float m_sidebarWidth = 220.0f;
        static constexpr float MIN_SIDEBAR_WIDTH = 100.0f;
        static constexpr float MAX_SIDEBAR_WIDTH = 400.0f;

        // ── Input Buffers (UI-only) ─────────────────
        char m_playlistSearchBuffer[256] = "";
        char m_newPlaylistNameBuffer[256] = "";
        char m_renamePlaylistBuffer[256] = "";
        char m_trackSearchBuffer[256] = "";
        char m_addTrackSearchBuffer[256] = "";

        // ── Edit Track Dialog ───────────────────────
        EditTrackDialog m_editTrackDialog;
    };

} // namespace moosic