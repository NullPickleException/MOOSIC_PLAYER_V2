//==============================================================================
// UI.cpp
//==============================================================================
// Implementation of main UI coordinator
//==============================================================================

#include "UI.h"
#include "Windows/WindowContentPanel.h"

namespace moosic
{

    //==============================================================================
    // ImGui Style Application
    //==============================================================================

    void UI::ApplyImGuiStyle(const Theme &theme)
    {
        if (!ImGui::GetCurrentContext())
            return;

        ImGuiStyle &style = ImGui::GetStyle();
        const auto &w = theme.Window;
        const auto &cp = theme.ContentPanel;

        style.Colors[ImGuiCol_WindowBg] = w.WindowBg;
        style.Colors[ImGuiCol_Border] = cp.BorderColor;
        style.Colors[ImGuiCol_TitleBg] = w.TitleBar;
        style.Colors[ImGuiCol_TitleBgActive] = w.TitleBarActive;
        style.Colors[ImGuiCol_TitleBgCollapsed] = w.TitleBar;
        style.Colors[ImGuiCol_ChildBg] = w.ChildBg;
        style.Colors[ImGuiCol_Text] = w.TextPrimary;
        style.Colors[ImGuiCol_TextDisabled] = w.TextDisabled;
        style.Colors[ImGuiCol_Button] = w.ButtonNormal;
        style.Colors[ImGuiCol_ButtonHovered] = w.ButtonHovered;
        style.Colors[ImGuiCol_ButtonActive] = w.ButtonActive;
        style.Colors[ImGuiCol_Separator] = w.SeparatorColor;
        style.Colors[ImGuiCol_SeparatorHovered] = w.SeparatorColor;
        style.Colors[ImGuiCol_SeparatorActive] = w.SeparatorColor;
        style.Colors[ImGuiCol_PlotHistogram] = w.ProgressBar;
        style.Colors[ImGuiCol_Header] = w.ButtonNormal;
        style.Colors[ImGuiCol_HeaderHovered] = w.ButtonHovered;
        style.Colors[ImGuiCol_HeaderActive] = w.ButtonActive;
        style.Colors[ImGuiCol_FrameBg] = w.ChildBg;
        style.Colors[ImGuiCol_FrameBgHovered] = w.ButtonHovered;
        style.Colors[ImGuiCol_FrameBgActive] = w.ButtonActive;
        style.Colors[ImGuiCol_PopupBg] = w.WindowBg;
        style.Colors[ImGuiCol_CheckMark] = w.ProgressBar;
        style.Colors[ImGuiCol_SliderGrab] = w.ProgressBar;
        style.Colors[ImGuiCol_SliderGrabActive] = w.ButtonActive;

        style.Colors[ImGuiCol_Tab] = cp.TabInactive;
        style.Colors[ImGuiCol_TabHovered] = cp.TabHovered;
        style.Colors[ImGuiCol_TabActive] = cp.TabActive;
        style.Colors[ImGuiCol_TabUnfocused] = cp.TabInactive;
        style.Colors[ImGuiCol_TabUnfocusedActive] = cp.TabActive;

        style.WindowRounding = 0.0f;
        style.ChildRounding = 4.0f;
        style.FrameRounding = w.ButtonRounding;
        style.GrabRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.TabRounding = cp.TabRounding;
        style.ScrollbarRounding = 4.0f;

        style.WindowBorderSize = cp.BorderThickness;
        style.ChildBorderSize = 0.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;

        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(6.0f, 4.0f);
        style.ItemSpacing = ImVec2(6.0f, 4.0f);
        style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);

        style.ScrollbarSize = 12.0f;
        style.GrabMinSize = 8.0f;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    }

    void UI::ConnectSettingsWindow(WindowContentPanel *contentPanel)
    {
        if (!contentPanel)
            return;

        auto &settingsWindow = contentPanel->GetSettingsWindow();

        settingsWindow.SetSettingsDataModel(&m_settingsData);
        settingsWindow.SetThemeManager(&m_themeManager);

        // Scan for available logos
        settingsWindow.ScanAvailableLogos();

        settingsWindow.OnThemeChanged([this]()
                                      { ApplyThemeToLayouts(); });

        settingsWindow.OnVisualizerModeChanged([this](int mode)
                                               {
        m_playbackController.SetVisualizerMode(mode);
        m_settingsData.SetVisualizerMode(mode); });

        // Logo change callback
        settingsWindow.OnLogoChanged([this](const std::string &path)
                                     {
        if (path.empty())
        {
            // Reload default logo
            std::vector<std::string> defaultPaths = {
                "assets/Logo_img/COW_IMAGE.png",
                "../assets/Logo_img/COW_IMAGE.png",
                "../../assets/Logo_img/COW_IMAGE.png"
            };
            for (const auto& p : defaultPaths)
            {
                if (m_titleBar.LoadLogo(p))
                    break;
            }
        }
        else
        {
            m_titleBar.LoadLogo(path);
        } });

        // Load saved logo on startup
        std::string savedLogo = m_settingsData.GetLogoPath();
        if (!savedLogo.empty())
        {
            m_titleBar.LoadLogo(savedLogo);
        }
    }

    WindowContentPanel *UI::GetCurrentContentPanel()
    {
        switch (m_layoutMode)
        {
        case LayoutMode::Standard:
            return m_standardLayout.GetContentPanel();
        case LayoutMode::SidebarLeft:
            return m_sidebarLayout.GetContentPanel();
        case LayoutMode::Compact:
            return m_compactLayout.GetContentPanel();
        case LayoutMode::MiniPlayer:
            return m_miniPlayerLayout.GetContentPanel();
        case LayoutMode::Theater:
            return m_theaterLayout.GetContentPanel();
        case LayoutMode::StandardArtLeft:
            return m_standardArtLeftLayout.GetContentPanel();
        default:
            return nullptr;
        }
    }

    void UI::ConnectSettingsWindowForCurrentLayout()
    {
        WindowContentPanel *contentPanel = GetCurrentContentPanel();
        if (contentPanel)
        {
            ConnectSettingsWindow(contentPanel);
        }
    }

    UI::UI(MusicLibrary &library, PlaybackController &playbackController)
        : m_library(library), m_playbackController(playbackController),
          m_libraryData(library),
          m_directoryData(library, &m_playlistData),
          m_playlistData(library),
          m_standardLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_sidebarLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_compactLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_miniPlayerLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_theaterLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_standardArtLeftLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController)
    {
    }

    void UI::Initialize(SDL_Window *window)
    {
        if (m_initialized)
            return;

        m_initialized = true;

        m_titleBar.Initialize(window);

        ConnectSettingsWindowForCurrentLayout();

        ApplyThemeToLayouts();
    }

    void UI::SetTheme(const Theme &theme)
    {
        m_themeManager.SetTheme(theme);
        m_settingsData.SetThemeName(m_themeManager.GetCurrentThemeName());
        ApplyThemeToLayouts();
    }

    void UI::SetTheme(const std::string &themeName)
    {
        if (m_themeManager.SetTheme(themeName))
        {
            m_settingsData.SetThemeName(themeName);
            ApplyThemeToLayouts();
        }
    }

    const Theme &UI::GetTheme() const
    {
        return m_themeManager.GetTheme();
    }

    ThemeManager &UI::GetThemeManager()
    {
        return m_themeManager;
    }

    void UI::ApplyThemeToLayouts()
    {
        const Theme &theme = m_themeManager.GetTheme();

        if (m_initialized)
        {
            ApplyImGuiStyle(theme);
        }

        m_titleBar.ApplyTheme(theme.TitleBar);

        m_standardLayout.ApplyTheme(theme);
        m_sidebarLayout.ApplyTheme(theme);
        m_compactLayout.ApplyTheme(theme);
        m_miniPlayerLayout.ApplyTheme(theme);
        m_theaterLayout.ApplyTheme(theme);
        m_standardArtLeftLayout.ApplyTheme(theme);
    }

    void UI::HandleLayoutSwitch(InputManager &input)
    {
        LayoutMode newMode = m_layoutMode;

        if (input.IsKeyPressed(SDLK_1))
            newMode = LayoutMode::Standard;
        if (input.IsKeyPressed(SDLK_2))
            newMode = LayoutMode::Compact;
        if (input.IsKeyPressed(SDLK_3))
            newMode = LayoutMode::StandardArtLeft;
        if (input.IsKeyPressed(SDLK_4))
            newMode = LayoutMode::SidebarLeft;
        if (input.IsKeyPressed(SDLK_5))
            newMode = LayoutMode::MiniPlayer;
        if (input.IsKeyPressed(SDLK_6))
            newMode = LayoutMode::Theater;

        if (newMode != m_layoutMode)
        {
            m_layoutMode = newMode;
            m_settingsData.SetLayoutMode(static_cast<int>(newMode));
            ConnectSettingsWindowForCurrentLayout();
        }
    }

    void UI::DrawCurrentLayout(SDL_Renderer *renderer)
    {
        switch (m_layoutMode)
        {
        case LayoutMode::Standard:
            m_standardLayout.Draw(renderer);
            break;
        case LayoutMode::SidebarLeft:
            m_sidebarLayout.Draw(renderer);
            break;
        case LayoutMode::Compact:
            m_compactLayout.Draw(renderer);
            break;
        case LayoutMode::MiniPlayer:
            m_miniPlayerLayout.Draw(renderer);
            break;
        case LayoutMode::Theater:
            m_theaterLayout.Draw(renderer);
            break;
        case LayoutMode::StandardArtLeft:
            m_standardArtLeftLayout.Draw(renderer);
            break;
        }
    }

    void UI::LoadSavedLogo(const std::string &path)
    {
        if (!path.empty())
        {
            m_titleBar.LoadLogo(path);
        }
    }

    void UI::Draw(SDL_Renderer *renderer, InputManager &input)
    {
        HandleLayoutSwitch(input);

        m_playbackController.Update();

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        float titleBarHeight = m_titleBar.GetTheme().Height;

        const float TITLEBAR_OVERLAP = 0.0f;

        ImVec2 originalPos = viewport->Pos;
        ImVec2 originalSize = viewport->Size;
        ImVec2 originalWorkPos = viewport->WorkPos;
        ImVec2 originalWorkSize = viewport->WorkSize;

        viewport->Pos = ImVec2(originalPos.x, originalPos.y + titleBarHeight - TITLEBAR_OVERLAP);
        viewport->Size = ImVec2(originalSize.x, originalSize.y - titleBarHeight + TITLEBAR_OVERLAP);
        viewport->WorkPos = viewport->Pos;
        viewport->WorkSize = viewport->Size;

        DrawCurrentLayout(renderer);

        viewport->Pos = originalPos;
        viewport->Size = originalSize;
        viewport->WorkPos = originalWorkPos;
        viewport->WorkSize = originalWorkSize;

        m_titleBar.Render();
    }

} // namespace moosic