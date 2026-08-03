//==============================================================================
// UI.cpp
//==============================================================================

#include "UI.h"
#include "Windows/WindowContentPanel.h"
#include "../Services/FileDialog.h"

#include <imgui_impl_sdlrenderer2.h>
#include <nfd.h>

#include <iostream>
#include <algorithm>

namespace moosic
{

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
        settingsWindow.ScanAvailableLogos();
        settingsWindow.OnThemeChanged([this]()
                                      { ApplyThemeToLayouts(); });
        settingsWindow.OnVisualizerModeChanged([this](int mode)
                                               {
            m_playbackController.SetVisualizerMode(mode);
            m_settingsData.SetVisualizerMode(mode); });
        settingsWindow.OnLogoChanged([this](const std::string &path)
                                     {
            if (path.empty()) {
                std::vector<std::string> defaultPaths = {
                    "assets/Logo_img/COW_IMAGE.png", "../assets/Logo_img/COW_IMAGE.png", "../../assets/Logo_img/COW_IMAGE.png"};
                for (const auto& p : defaultPaths) { if (m_titleBar.LoadLogo(p)) break; }
            } else { m_titleBar.LoadLogo(path); } });
        std::string savedLogo = m_settingsData.GetLogoPath();
        if (!savedLogo.empty())
            m_titleBar.LoadLogo(savedLogo);
        settingsWindow.ScanAvailableFonts();
        settingsWindow.OnFontChanged([this](const std::string &path, float size)
                                     { LoadFont(path, size); });
        std::string savedFont = m_settingsData.GetFontPath();
        float savedFontSize = m_settingsData.GetFontSize();
        if (savedFontSize < 12.0f)
            savedFontSize = 16.0f;
        LoadFont(savedFont, savedFontSize);
    }

    WindowContentPanel *UI::GetCurrentContentPanel()
    {
        switch (m_layoutMode)
        {
        case LayoutMode::Standard:
            return m_standardLayout.GetContentPanel();
        case LayoutMode::Compact:
            return m_compactLayout.GetContentPanel();
        case LayoutMode::StandardArtLeft:
            return m_standardArtLeftLayout.GetContentPanel();
        case LayoutMode::SidebarLeft:
            return m_sidebarLayout.GetContentPanel();
        case LayoutMode::MiniPlayer:
            return m_miniPlayerLayout.GetContentPanel();
        case LayoutMode::Theater:
            return m_theaterLayout.GetContentPanel();
        default:
            return nullptr;
        }
    }

    void UI::ConnectSettingsWindowForCurrentLayout()
    {
        WindowContentPanel *contentPanel = GetCurrentContentPanel();
        if (contentPanel)
            ConnectSettingsWindow(contentPanel);
    }

    UI::UI(MusicLibrary &library, PlaybackController &playbackController)
        : m_library(library), m_playbackController(playbackController),
          m_libraryData(library), m_directoryData(library, &m_playlistData), m_playlistData(library),
          m_standardLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_compactLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_standardArtLeftLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_sidebarLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_miniPlayerLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_theaterLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController)
    {
    }

    void UI::Initialize(SDL_Window *window)
    {
        if (m_initialized)
            return;
        m_initialized = true;
        m_titleBar.Initialize(window);
        SetupMenuBarCallbacks();
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

    const Theme &UI::GetTheme() const { return m_themeManager.GetTheme(); }
    ThemeManager &UI::GetThemeManager() { return m_themeManager; }

    void UI::ApplyThemeToLayouts()
    {
        const Theme &theme = m_themeManager.GetTheme();
        if (m_initialized)
            ApplyImGuiStyle(theme);
        m_titleBar.ApplyTheme(theme.TitleBar);

        // Apply menu bar theme
        MenuBarTheme menuTheme;
        menuTheme.BackgroundColor = theme.Window.TitleBar;
        menuTheme.TextColor = theme.Window.TextPrimary;
        menuTheme.TextHovered = theme.Window.TextPrimary;
        menuTheme.HighlightColor = theme.Window.ButtonHovered;
        menuTheme.HighlightHovered = theme.Window.ButtonActive;
        menuTheme.HighlightActive = theme.Window.ButtonActive;
        menuTheme.PopupBackground = theme.Window.WindowBg;
        menuTheme.BorderColor = theme.ContentPanel.BorderColor;
        menuTheme.Height = 19.6f;
        m_menuBar.ApplyTheme(menuTheme);

        m_standardLayout.ApplyTheme(theme);
        m_compactLayout.ApplyTheme(theme);
        m_standardArtLeftLayout.ApplyTheme(theme);
        m_sidebarLayout.ApplyTheme(theme);
        m_miniPlayerLayout.ApplyTheme(theme);
        m_theaterLayout.ApplyTheme(theme);
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

            m_layoutState.SetCurrentLayout(
                static_cast<LayoutStateDataModel::Layout>(static_cast<int>(newMode)));
            m_settingsData.SetLayoutMode(static_cast<int>(newMode));

            if (auto *panel = m_standardLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_compactLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_standardArtLeftLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_sidebarLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_miniPlayerLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_theaterLayout.GetContentPanel())
                panel->InvalidateTabSelection();

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
        case LayoutMode::Compact:
            m_compactLayout.Draw(renderer);
            break;
        case LayoutMode::StandardArtLeft:
            m_standardArtLeftLayout.Draw(renderer);
            break;
        case LayoutMode::SidebarLeft:
            m_sidebarLayout.Draw(renderer);
            break;
        case LayoutMode::MiniPlayer:
            m_miniPlayerLayout.Draw(renderer);
            break;
        case LayoutMode::Theater:
            m_theaterLayout.Draw(renderer);
            break;
        }
    }

    void UI::LoadSavedLogo(const std::string &path)
    {
        if (!path.empty())
            m_titleBar.LoadLogo(path);
    }

    void UI::Draw(SDL_Renderer *renderer, InputManager &input)
    {
        HandleLayoutSwitch(input);
        m_playbackController.Update();

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        const float titleBarHeight = m_titleBar.GetTheme().Height;
        const float borderThickness = m_themeManager.GetTheme().ContentPanel.BorderThickness;

        // ── Menu bar draws itself ──
        m_menuBar.Draw(titleBarHeight, borderThickness,
                       m_themeManager.GetTheme().ContentPanel.BorderColor,
                       m_themeManager.GetTheme().Window.TitleBar);

        // ── Main content window: starts after menu bar ──
        const float menuBarHeight = m_menuBar.GetHeight();
        const float topChrome = titleBarHeight + menuBarHeight + borderThickness;

        const ImVec2 originalPos = viewport->Pos;
        const ImVec2 originalSize = viewport->Size;
        const ImVec2 originalWorkPos = viewport->WorkPos;
        const ImVec2 originalWorkSize = viewport->WorkSize;

        viewport->Pos = ImVec2(originalPos.x, originalPos.y + topChrome);
        viewport->Size = ImVec2(originalSize.x, originalSize.y - topChrome);
        viewport->WorkPos = viewport->Pos;
        viewport->WorkSize = viewport->Size;

        DrawCurrentLayout(renderer);

        viewport->Pos = originalPos;
        viewport->Size = originalSize;
        viewport->WorkPos = originalWorkPos;
        viewport->WorkSize = originalWorkSize;

        m_titleBar.Render();
    }

    void UI::LoadFont(const std::string &fontPath, float fontSize)
    {
        m_pendingFontPath = fontPath;
        m_pendingFontSize = fontSize;
        m_fontNeedsReload = true;
    }

    void UI::ApplyPendingFont()
    {
        if (!m_fontNeedsReload)
            return;
        m_fontNeedsReload = false;
        ImGuiStyle savedStyle = ImGui::GetStyle();
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->Clear();
        ImFontConfig config;
        config.OversampleH = 1;
        config.OversampleV = 1;
        config.PixelSnapH = true;
        config.FontDataOwnedByAtlas = false;
        if (m_pendingFontPath.empty())
            io.Fonts->AddFontDefault(&config);
        else
        {
            ImFont *font = io.Fonts->AddFontFromFileTTF(m_pendingFontPath.c_str(), m_pendingFontSize, &config);
            if (!font)
            {
                std::cout << "[UI] Failed to load font, using default\n";
                io.Fonts->AddFontDefault(&config);
            }
        }
        io.Fonts->Build();
        ImGui_ImplSDLRenderer2_DestroyDeviceObjects();
        ImGui_ImplSDLRenderer2_CreateDeviceObjects();
        ImGui::GetStyle() = savedStyle;
    }

    //==========================================================================
    // Menu Bar
    //==========================================================================

    void UI::SetupMenuBarCallbacks()
    {
        if (m_menuCallbacksSet)
            return;
        m_menuCallbacksSet = true;

        m_menuBar.OnFileOpen = [this]()
        { OnFileOpen(); };
        m_menuBar.OnFileExit = [this]()
        { OnFileExit(); };
        m_menuBar.OnViewLayout = [this](int mode)
        {
            OnViewLayout(static_cast<LayoutMode>(mode));
        };
        m_menuBar.OnPlaybackPlay = [this]()
        { OnPlaybackPlay(); };
        m_menuBar.OnPlaybackPause = [this]()
        { OnPlaybackPause(); };
        m_menuBar.OnPlaybackStop = [this]()
        { OnPlaybackStop(); };
        m_menuBar.OnHelpAbout = [this]()
        { OnHelpAbout(); };
    }

    void UI::DrawMenuBar()
    {
        SetupMenuBarCallbacks();
        m_menuBar.Draw(
            m_titleBar.GetTheme().Height,
            m_themeManager.GetTheme().ContentPanel.BorderThickness,
            m_themeManager.GetTheme().ContentPanel.BorderColor,
            m_themeManager.GetTheme().Window.TitleBar);
    }
    //==========================================================================
    // Menu Bar Actions - File
    //==========================================================================

    void UI::OnFileOpen()
    {
        auto path = OpenAudioFileDialog();
        if (path.has_value())
        {
            OpenAndPlayTemporaryAudioFile(path.value());
        }
    }

    void UI::OpenAndPlayTemporaryAudioFile(const std::filesystem::path &filePath)
    {
        if (filePath.empty() || !std::filesystem::exists(filePath))
        {
            std::cerr << "[UI] File does not exist: " << filePath << std::endl;
            return;
        }

        std::cout << "[UI] Opening temporary audio file: " << filePath << std::endl;

        // Read metadata (but don't add to library)
        MetadataReader reader;
        MusicTrack track = reader.ReadMetadataForSingleTrack(filePath);

        // Use filename as title if metadata is missing
        if (track.GetTitle().empty() || track.GetTitle() == "Unknown Track")
        {
            std::string filename = filePath.filename().string();
            size_t dotPos = filename.find_last_of('.');
            if (dotPos != std::string::npos)
                filename = filename.substr(0, dotPos);
            track.SetTitle(filename);
        }

        // ====== FIX: Get actual duration using BASS ======
        unsigned int duration = reader.GetDurationWithBASS(filePath);
        if (duration > 0)
        {
            track.SetDuration(duration);
            std::cout << "[UI] Duration from BASS: " << duration << "s" << std::endl;
        }
        else
        {
            std::cout << "[UI] Warning: Could not get duration from BASS" << std::endl;
        }
        // ================================================

        std::cout << "[UI] Temporary track: " << track.GetTitle()
                  << " - " << track.GetArtist()
                  << " (" << track.GetDuration() << "s)" << std::endl;

        // Let PlaybackController take full ownership of the track
        m_playbackController.SetTemporaryTrack(std::move(track));
        m_playbackController.Play();

        std::cout << "[UI] Now playing (temporary): "
                  << m_playbackController.GetCurrentTrack()->GetTitle()
                  << " (" << m_playbackController.GetCurrentTrack()->GetDuration() << "s)" << std::endl;
    }

    void UI::OnFileExit()
    {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    //==========================================================================
    // Menu Bar Actions - View
    //==========================================================================

    void UI::OnViewLayout(LayoutMode mode)
    {
        if (mode == m_layoutMode)
            return;

        m_layoutMode = mode;
        m_layoutState.SetCurrentLayout(
            static_cast<LayoutStateDataModel::Layout>(static_cast<int>(mode)));
        m_settingsData.SetLayoutMode(static_cast<int>(mode));

        if (auto *panel = m_standardLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_compactLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_standardArtLeftLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_sidebarLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_miniPlayerLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_theaterLayout.GetContentPanel())
            panel->InvalidateTabSelection();

        ConnectSettingsWindowForCurrentLayout();
    }

    //==========================================================================
    // Menu Bar Actions - Playback
    //==========================================================================

    void UI::OnPlaybackPlay()
    {
        m_playbackController.Play();
    }

    void UI::OnPlaybackPause()
    {
        m_playbackController.Pause();
    }

    void UI::OnPlaybackStop()
    {
        m_playbackController.Stop();
    }

    //==========================================================================
    // Menu Bar Actions - Help
    //==========================================================================

    void UI::OnHelpAbout()
    {
        ImGui::OpenPopup("About Moosic");
    }

} // namespace moosic