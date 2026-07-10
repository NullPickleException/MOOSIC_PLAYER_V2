#include "Application.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <iostream>

namespace moosic
{

    Application::Application()
        : m_playbackController(m_library),
          m_ui(m_library, m_playbackController)
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

                // Handle window resize events
                if (event.type == SDL_WINDOWEVENT)
                {
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                        event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        // Update ImGui display size
                        ImGuiIO &io = ImGui::GetIO();
                        io.DisplaySize = ImVec2(
                            static_cast<float>(event.window.data1),
                            static_cast<float>(event.window.data2));

                        std::cout << "Window resized to: "
                                  << event.window.data1 << "x"
                                  << event.window.data2 << "\n";
                    }
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

        // Create window with RESIZABLE flag
        m_window = SDL_CreateWindow(
            "MOOSIC PLAYER",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1200,
            800,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if (!m_window)
        {
            std::cerr << "Failed to create window.\n"
                      << SDL_GetError() << std::endl;
            return false;
        }

        // Get actual window size (may differ from requested)
        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);

        m_renderer = SDL_CreateRenderer(
            m_window,
            -1,
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
        io.DisplaySize = ImVec2(
            static_cast<float>(width),
            static_cast<float>(height));

        // Optional: Set initial style
        ImGui::StyleColorsDark();

        // Setup ImGui for SDL
        ImGui_ImplSDL2_InitForSDLRenderer(m_window, m_renderer);
        ImGui_ImplSDLRenderer2_Init(m_renderer);

        std::cout << "Window initialized: " << width << "x" << height << "\n";
        std::cout << "Window is resizable - drag edges to resize!\n";

        return true;
    }

    void Application::Shutdown()
    {
        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        if (m_renderer)
        {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }

        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }

        SDL_Quit();
    }

    void Application::Update()
    {
        // Update application state
    }

    void Application::Render()
    {
        // Clear with dark background
        SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255);
        SDL_RenderClear(m_renderer);

        // Start ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // Draw UI
        m_ui.Draw();

        // Render ImGui
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);

        // Present
        SDL_RenderPresent(m_renderer);
    }

}