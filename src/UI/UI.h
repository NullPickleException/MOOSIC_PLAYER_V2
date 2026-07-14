//==============================================================================
// UI.h
//==============================================================================

#pragma once

#include "../Models/MusicLibrary.h"
#include "Layouts/MainLayout.h"
#include "Layouts/SidebarLeftLayout.h"
#include "Layouts/CompactLayout.h"
#include "Layouts/MiniPlayerLayout.h"
#include "Layouts/TheaterLayout.h"
#include "Layouts/StandardArtLeftLayout.h"
#include "../Services/PlaybackController.h"
#include "../Core/Input/InputManager.h"
#include "Theme/Theme.h"
#include <SDL.h>

namespace moosic
{

class UI
{
public:
    UI(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer, InputManager& input);

private:
    enum class LayoutMode
    {
        Standard,           
        SidebarLeft,        
        Compact,            
        MiniPlayer,         
        Theater,            
        StandardArtLeft     
    };

    LayoutMode m_layoutMode = LayoutMode::Standard;

    MainLayout m_standardLayout;
    SidebarLeftLayout m_sidebarLayout;
    CompactLayout m_compactLayout;
    MiniPlayerLayout m_miniPlayerLayout;
    TheaterLayout m_theaterLayout;
    StandardArtLeftLayout m_standardArtLeftLayout;

    PlaybackController& m_playbackController;
    MusicLibrary& m_library;

    void HandleLayoutSwitch(InputManager& input);
    void DrawCurrentLayout(SDL_Renderer* renderer);
};

} // namespace moosic