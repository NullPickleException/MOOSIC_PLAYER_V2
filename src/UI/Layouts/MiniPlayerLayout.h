//==============================================================================
// MiniPlayerLayout.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Data/LayoutStateDataModel.h"
#include "../Windows/DirectoryWindow.h"
#include "../Windows/LibraryWindow.h"
#include "../Windows/PlaylistWindow.h"
#include "../Widgets/PlayerBar/MiniPlayerBar.h"
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"
#include <SDL.h>

namespace moosic
{
    class MiniPlayerLayout : public ILayout
    {
    public:
        MiniPlayerLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                         PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                         MusicLibrary& library, PlaybackController& playbackController);
        void Draw(SDL_Renderer* renderer) override;
        void ApplyTheme(const Theme& theme) override
        {
            m_libraryWindow.ApplyTheme(theme.Window);
            m_libraryWindow.ApplyTrackTableTheme(theme.TrackTable);
            m_playlistWindow.ApplyTheme(theme.Window);
            m_playlistWindow.ApplyTrackTableTheme(theme.TrackTable);
            m_directoryWindow.ApplyTheme(theme.Window);
            m_miniPlayerBar.ApplyTheme(theme.PlayerBar);
            m_mainPlayerBar.ApplyTheme(theme.PlayerBar);
        }
        WindowContentPanel* GetContentPanel() override { return nullptr; }
    private:
        using Tab = LayoutStateDataModel::Tab;
        LibraryDataModel& m_libraryData;
        DirectoryDataModel& m_directoryData;
        PlaylistDataModel& m_playlistData;
        LayoutStateDataModel& m_layoutState;
        DirectoryWindow m_directoryWindow;
        LibraryWindow m_libraryWindow;
        PlaylistWindow m_playlistWindow;
        MiniPlayerBar m_miniPlayerBar;
        StandardPlayerBar m_mainPlayerBar;
        PlaybackController& m_playbackController;
    };
} // namespace moosic