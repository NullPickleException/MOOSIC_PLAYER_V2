//==============================================================================
// TheaterLayout.h
//==============================================================================
// Theater mode - large centered album art (Key 6)
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Widgets/PlayerBar/TheaterPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class TheaterLayout
{
public:
    TheaterLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);

private:
    TheaterPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic