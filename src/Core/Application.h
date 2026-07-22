//==============================================================================
// Application.h
//==============================================================================

#pragma once

#include "UI/UI.h"
#include "Core/Input/InputManager.h"
#include "../Models/MusicLibrary.h"
#include "Services/PlaybackController.h"
#include "Services/SavingSystem.h"

#include <SDL.h>
#include <nlohmann/json.hpp>

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
        void SaveState();
        void LoadState();
        std::filesystem::path GetExecutableDir();

    private:
        SDL_Window *m_window = nullptr;
        SDL_Renderer *m_renderer = nullptr;

        InputManager m_input;
        MusicLibrary m_library;
        PlaybackController m_playbackController;
        UI m_ui;
        SavingSystem m_savingSystem;
    };

} // namespace moosic