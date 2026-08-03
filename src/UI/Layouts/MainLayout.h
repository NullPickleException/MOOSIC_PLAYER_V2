//==============================================================================
// MainLayout.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Data/LayoutStateDataModel.h"
#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"
#include <SDL.h>

namespace moosic
{
    class MainLayout : public ILayout
    {
    public:
        MainLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                   PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                   MusicLibrary& library, PlaybackController& playbackController);
        void Draw(SDL_Renderer* renderer) override;
        void ApplyTheme(const Theme& theme) override { m_contentPanel.ApplyTheme(theme); m_playerBar.ApplyTheme(theme.PlayerBar); }
        WindowContentPanel* GetContentPanel() override { return &m_contentPanel; }
    private:
        LibraryDataModel& m_libraryData;
        DirectoryDataModel& m_directoryData;
        PlaylistDataModel& m_playlistData;
        WindowContentPanel m_contentPanel;
        StandardPlayerBar m_playerBar;
        PlaybackController& m_playbackController;
    };
} // namespace moosic