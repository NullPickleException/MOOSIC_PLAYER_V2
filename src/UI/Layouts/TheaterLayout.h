//==============================================================================
// TheaterLayout.h
//==============================================================================

#pragma once

#include "../Data/LibraryDataModel.h"
#include "../Data/DirectoryDataModel.h"
#include "../Data/PlaylistDataModel.h"
#include "../Data/LayoutStateDataModel.h"
#include "../Widgets/PlayerBar/TheaterPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"
#include <SDL.h>

namespace moosic
{
    class TheaterLayout : public ILayout
    {
    public:
        TheaterLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                      PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                      MusicLibrary& library, PlaybackController& playbackController);
        void Draw(SDL_Renderer* renderer) override;
        void ApplyTheme(const Theme& theme) override { m_playerBar.ApplyTheme(theme.PlayerBar); }
        WindowContentPanel* GetContentPanel() override { return nullptr; }
    private:
        LibraryDataModel& m_libraryData;
        DirectoryDataModel& m_directoryData;
        PlaylistDataModel& m_playlistData;
        LayoutStateDataModel& m_layoutState;
        TheaterPlayerBar m_playerBar;
        PlaybackController& m_playbackController;
    };
} // namespace moosic