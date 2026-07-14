//==============================================================================
// SidebarLeftLayout.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/SidePlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class SidebarLeftLayout
{
public:
    SidebarLeftLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);

private:
    WindowContentPanel m_contentPanel;
    SidePlayerBar m_playerBar;
    PlaybackController& m_playbackController;
    
    float m_sidebarWidth = 220.0f;
    static constexpr float MIN_SIDEBAR_WIDTH = 180.0f;
    static constexpr float MAX_SIDEBAR_WIDTH = 320.0f;
};

} // namespace moosic