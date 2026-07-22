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

        //--------------------------------------------------------------------------
        // Window Colors
        //--------------------------------------------------------------------------
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

        // Tab Colors
        style.Colors[ImGuiCol_Tab] = cp.TabInactive;
        style.Colors[ImGuiCol_TabHovered] = cp.TabHovered;
        style.Colors[ImGuiCol_TabActive] = cp.TabActive;
        style.Colors[ImGuiCol_TabUnfocused] = cp.TabInactive;
        style.Colors[ImGuiCol_TabUnfocusedActive] = cp.TabActive;

        //--------------------------------------------------------------------------
        // Style Properties - Main Window Rounding (Top flat, Bottom rounded)
        //--------------------------------------------------------------------------
        style.WindowRounding = 6.0f; // Top corners flat (connects to title bar)
        style.ChildRounding = 4.0f;
        style.FrameRounding = w.ButtonRounding;
        style.GrabRounding = 4.0f;
        style.PopupRounding = 4.0f;
        style.TabRounding = cp.TabRounding;
        style.ScrollbarRounding = 4.0f;

        // Main window borders
        style.WindowBorderSize = cp.BorderThickness;
        style.ChildBorderSize = 0.0f;
        style.PopupBorderSize = 1.0f;
        style.FrameBorderSize = 0.0f;
        style.TabBorderSize = 0.0f;

        // Padding & Spacing
        style.WindowPadding = ImVec2(8.0f, 8.0f);
        style.FramePadding = ImVec2(6.0f, 4.0f);
        style.ItemSpacing = ImVec2(6.0f, 4.0f);
        style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);

        style.ScrollbarSize = 12.0f;
        style.GrabMinSize = 8.0f;
        style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
    }

    //==============================================================================
    // Settings Window Connection
    //==============================================================================

    void UI::ConnectSettingsWindow(WindowContentPanel *contentPanel)
    {
        if (!contentPanel)
            return;

        auto &settingsWindow = contentPanel->GetSettingsWindow();

        // Set the shared settings data model
        settingsWindow.SetSettingsDataModel(&m_settingsData);
        
        // Theme manager
        settingsWindow.SetThemeManager(&m_themeManager);
        settingsWindow.OnThemeChanged(
            [this]()
            {
                ApplyThemeToLayouts();
            });

        // Visualizer mode callback - propagates directly to PlaybackController
        // IPlayerBar reads this value in UpdatePlaybackState() automatically
        settingsWindow.OnVisualizerModeChanged(
            [this](int mode)
            {
                m_settingsData.SetVisualizerMode(mode);
                m_playbackController.SetVisualizerMode(mode);
            });
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

    //==============================================================================
    // Constructor
    //==============================================================================

    UI::UI(MusicLibrary &library, PlaybackController &playbackController)
        : m_library(library), m_playbackController(playbackController),
          m_libraryData(library),
          m_directoryData(library),
          m_playlistData(library),
          // SettingsDataModel is default-initialized with "Dark" theme, spectrum mode, standard layout
          m_standardLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_sidebarLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_compactLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_miniPlayerLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_theaterLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController),
          m_standardArtLeftLayout(m_libraryData, m_directoryData, m_playlistData, library, playbackController)
    {
        // All layouts share the SAME data models!
        // State persists across layout switches automatically.
    }

    //==============================================================================
    // Initialization
    //==============================================================================

    void UI::Initialize(SDL_Window *window)
    {
        if (m_initialized)
            return;

        m_initialized = true;

        // Initialize title bar
        m_titleBar.Initialize(window);

        // Connect settings window for the current layout
        ConnectSettingsWindowForCurrentLayout();

        // Apply the initial theme
        ApplyThemeToLayouts();
    }

    //==============================================================================
    // Theme
    //==============================================================================

    void UI::SetTheme(const Theme &theme)
    {
        m_themeManager.SetTheme(theme);
        // When setting a raw Theme object, we update the data model with the 
        // current theme name from the manager (which tracks it internally)
        m_settingsData.SetThemeName(m_themeManager.GetCurrentThemeName());
        ApplyThemeToLayouts();
    }

    void UI::SetTheme(const std::string &themeName)
    {
        if (m_themeManager.SetTheme(themeName))
        {
            m_settingsData.SetThemeName(themeName);  // Sync to data model
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

    //==============================================================================
    // Layout Switching
    //==============================================================================

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
            m_settingsData.SetLayoutMode(static_cast<int>(newMode));  // Sync to data model
            // Reconnect settings window for the new layout
            ConnectSettingsWindowForCurrentLayout();
        }
    }

    //==============================================================================
    // Drawing
    //==============================================================================

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

    void UI::Draw(SDL_Renderer *renderer, InputManager &input)
    {
        HandleLayoutSwitch(input);

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        float titleBarHeight = m_titleBar.GetTheme().Height;

        // Small overlap to eliminate the gap between title bar and content
        // Caused by window rounding and title bar bottom border
        const float TITLEBAR_OVERLAP = 0.0f;

        // Save original viewport state
        ImVec2 originalPos = viewport->Pos;
        ImVec2 originalSize = viewport->Size;
        ImVec2 originalWorkPos = viewport->WorkPos;
        ImVec2 originalWorkSize = viewport->WorkSize;

        // Shift the entire drawable area down so layouts can't draw over title bar
        viewport->Pos = ImVec2(originalPos.x, originalPos.y + titleBarHeight - TITLEBAR_OVERLAP);
        viewport->Size = ImVec2(originalSize.x, originalSize.y - titleBarHeight + TITLEBAR_OVERLAP);
        viewport->WorkPos = viewport->Pos;
        viewport->WorkSize = viewport->Size;

        // Draw layouts (now forced below title bar area)
        DrawCurrentLayout(renderer);

        // Restore full viewport for title bar rendering
        viewport->Pos = originalPos;
        viewport->Size = originalSize;
        viewport->WorkPos = originalWorkPos;
        viewport->WorkSize = originalWorkSize;

        // Draw title bar LAST - it renders at the original full viewport position on top of everything
        m_titleBar.Render();
    }

} // namespace moosic