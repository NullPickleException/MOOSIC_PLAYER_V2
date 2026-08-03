//==============================================================================
// SidebarLeftLayout.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Data/LayoutStateDataModel.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/SidePlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"
#include <SDL.h>

namespace moosic
{
    class SidebarLeftLayout : public ILayout
    {
    public:
        SidebarLeftLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                          PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                          MusicLibrary& library, PlaybackController& playbackController);
        void Draw(SDL_Renderer* renderer) override;
        void ApplyTheme(const Theme& theme) override { m_contentPanel.ApplyTheme(theme); m_playerBar.ApplyTheme(theme.PlayerBar); }
        WindowContentPanel* GetContentPanel() override { return &m_contentPanel; }
    private:
        LibraryDataModel& m_libraryData;
        DirectoryDataModel& m_directoryData;
        PlaylistDataModel& m_playlistData;
        LayoutStateDataModel& m_layoutState;
        WindowContentPanel m_contentPanel;
        SidePlayerBar m_playerBar;
        PlaybackController& m_playbackController;
        static constexpr float MIN_SIDEBAR_WIDTH = 180.0f;
        static constexpr float MAX_SIDEBAR_WIDTH = 320.0f;
    };
} // namespace moosic