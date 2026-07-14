//==============================================================================
// CompactLayout.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/CompactPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class CompactLayout
{
public:
    CompactLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);

private:
    WindowContentPanel m_contentPanel;
    CompactPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic