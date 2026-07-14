#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"          // replaces 2 includes
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class MainLayout
{
public:
    MainLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);

private:
    WindowContentPanel m_contentPanel;              
    StandardPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic