//==============================================================================
// Application.cpp
//==============================================================================

#include "Application.h"
#include "UI/Windows/WindowContentPanel.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

namespace moosic
{

    std::filesystem::path Application::GetExecutableDir()
    {
        char buffer[4096];

#ifdef _WIN32
        GetModuleFileNameA(NULL, buffer, sizeof(buffer));
#elif defined(__APPLE__)
        uint32_t size = sizeof(buffer);
        if (_NSGetExecutablePath(buffer, &size) != 0)
            return std::filesystem::current_path();
#else
        ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
        if (count != -1)
            buffer[count] = '\0';
        else
            return std::filesystem::current_path();
#endif

        return std::filesystem::path(buffer).parent_path();
    }

    Application::Application()
        : m_playbackController(m_library),
          m_ui(m_library, m_playbackController),
          m_savingSystem(GetExecutableDir() / "moosic_state.json")
    {
    }

    Application::~Application()
    {
        Shutdown();
    }

    int Application::Run()
    {
        if (!init())
            return 1;

        while (!m_input.ShouldQuit())
        {
            m_input.Reset();

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);

                if (event.type == SDL_WINDOWEVENT &&
                    (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                     event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED))
                {
                    ImGuiIO &io = ImGui::GetIO();
                    io.DisplaySize = ImVec2(
                        static_cast<float>(event.window.data1),
                        static_cast<float>(event.window.data2));
                }

                m_input.ProcessEvent(event);
            }

            Update();
            Render();
        }

        return 0;
    }

    bool Application::init()
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "SDL could not initialize!\n"
                      << SDL_GetError() << std::endl;
            return false;
        }

        m_window = SDL_CreateWindow(
            "MOOSIC PLAYER",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS);

        if (!m_window)
        {
            std::cerr << "Failed to create window.\n"
                      << SDL_GetError() << std::endl;
            return false;
        }

        SDL_SetWindowMinimumSize(m_window, 590, 440);

        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);

        m_renderer = SDL_CreateRenderer(
            m_window, -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (!m_renderer)
        {
            std::cerr << "Failed to create renderer.\n"
                      << SDL_GetError() << std::endl;
            return false;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.DisplaySize = ImVec2(static_cast<float>(width), static_cast<float>(height));

        ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
        ImGui_ImplSDLRenderer2_Init(m_renderer);

        m_ui.Initialize(m_window);
        LoadState();

        std::cout << "Window initialized: " << width << "x" << height << "\n";
        return true;
    }

    void Application::Shutdown()
    {
        SaveState();

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        if (m_renderer)
            SDL_DestroyRenderer(m_renderer);
        if (m_window)
            SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Application::Update()
    {
        static auto lastAutoSave = std::chrono::steady_clock::now();
        auto now = std::chrono::steady_clock::now();

        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastAutoSave).count() >= 30)
        {
            SaveState();
            lastAutoSave = now;
        }
    }

    void Application::Render()
    {
        SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
        SDL_RenderClear(m_renderer);

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        m_ui.Draw(m_renderer, m_input);

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
        SDL_RenderPresent(m_renderer);
    }

    //==========================================================================
    // Save/Load - Thin wrappers, all work delegated to SavingSystem
    //==========================================================================

    void Application::SaveState()
    {
        auto *contentPanel = m_ui.GetCurrentContentPanel();
        if (!contentPanel)
            return;

        m_savingSystem.Save(
            m_library,
            contentPanel->GetPlaylistData(),
            m_playbackController,
            m_ui.GetSettingsDataModel());
    }

    void Application::LoadState()
    {
        auto *contentPanel = m_ui.GetCurrentContentPanel();
        if (!contentPanel)
            return;

        if (m_savingSystem.Load(
                m_library,
                contentPanel->GetPlaylistData(),
                m_playbackController,
                m_ui.GetSettingsDataModel()))
        {
            contentPanel->GetLibraryData().Refresh();

            // Apply loaded settings
            const auto &settings = m_ui.GetSettingsDataModel();
            m_ui.SetTheme(settings.GetThemeName());
            m_playbackController.SetVisualizerMode(settings.GetVisualizerMode());
        }

        m_playbackController.Pause();
    }

} // namespace moosic