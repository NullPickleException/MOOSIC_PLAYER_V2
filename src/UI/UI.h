#pragma once

#include "../Models/MusicLibrary.h"
#include "Layouts/MainLayout.h"
#include "../Services/PlaybackController.h"  // ADD THIS

namespace moosic
{

class UI
{
public:
    UI(MusicLibrary& library, PlaybackController& playbackController);  
    void Draw();

private:
    MainLayout m_mainLayout;
};

}