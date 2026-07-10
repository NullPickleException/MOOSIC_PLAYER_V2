#pragma once

#include "UI/UI.h"
#include "Core/Input/InputManager.h"
#include "../Models/MusicLibrary.h"
#include "Services/PlaybackController.h"

#include <SDL.h>

namespace moosic
{
    class Application
    {
    public:
        Application();
        ~Application();
        int Run();

    private:
        bool init();
        void Shutdown();
        void Update();
        void Render();

    private:
        SDL_Window* m_window = nullptr;
        SDL_Renderer* m_renderer = nullptr;
        
        InputManager m_input;
        MusicLibrary m_library;
        PlaybackController m_playbackController;  
        UI m_ui;
    };
}