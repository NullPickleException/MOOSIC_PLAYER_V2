//==============================================================================
// StandardArtLeftLayout.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/StandardArtLeftPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class StandardArtLeftLayout
{
public:
    StandardArtLeftLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);
    WindowContentPanel& GetContentPanel() { return m_contentPanel; }

private:
    WindowContentPanel m_contentPanel;
    StandardArtLeftPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic