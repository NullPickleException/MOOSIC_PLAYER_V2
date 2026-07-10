#pragma once

#include "../Models/MusicLibrary.h"
#include "Layouts/MainLayout.h"
#include "../Services/PlaybackController.h"
#include <SDL.h>  // ADD THIS

namespace moosic
{

class UI
{
public:
    UI(MusicLibrary& library, PlaybackController& playbackController);  
    void Draw(SDL_Renderer* renderer);  

private:
    MainLayout m_mainLayout;
};

}