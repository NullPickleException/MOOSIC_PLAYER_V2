//==============================================================================
// UI.cpp
//==============================================================================

#include "UI.h"
#include "Windows/WindowContentPanel.h"
#include "../Services/FileDialog.h"
#include "../Services/Metadata/MetadataReader.h"

#include <imgui_impl_sdlrenderer2.h>
#include <nfd.h>

#include <iostream>
#include <algorithm>

namespace moosic
{

    //==============================================================================
    // Constructor
    //==============================================================================

    UI::UI(MusicLibrary &library, PlaybackController &playbackController)
        : m_library(library), m_playbackController(playbackController),
          m_libraryData(library), m_directoryData(library, &m_playlistData), m_playlistData(library),
          m_standardLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_compactLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_standardArtLeftLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_sidebarLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController),
          m_theaterLayout(m_libraryData, m_directoryData, m_playlistData, m_layoutState, library, playbackController)
    {
    }

    //==============================================================================
    // Initialization
    //==============================================================================

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

    //==============================================================================
    // Main Draw
    //==============================================================================

    void UI::Draw(SDL_Renderer *renderer, InputManager &input)
    {
        HandleLayoutSwitch(input);
        HandleGlobalHotkeys(input);
        m_playbackController.Update();

        ImGuiViewport *viewport = ImGui::GetMainViewport();
        const float titleBarHeight = m_titleBar.GetTheme().Height;
        const float borderThickness = m_themeManager.GetTheme().ContentPanel.BorderThickness;

        m_menuBar.Draw(titleBarHeight, borderThickness,
                       m_themeManager.GetTheme().ContentPanel.BorderColor,
                       m_themeManager.GetTheme().Window.TitleBar);

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
        case LayoutMode::Theater:
            m_theaterLayout.Draw(renderer);
            break;
        }
    }

    //==============================================================================
    // Theme Management
    //==============================================================================

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

        MenuBarTheme menuTheme;
        menuTheme.BackgroundColor = theme.Window.TitleBar;
        menuTheme.TextColor = theme.Window.TextPrimary;
        menuTheme.TextHovered = theme.Window.TextPrimary;
        menuTheme.HighlightColor = theme.Window.ButtonHovered;
        menuTheme.HighlightHovered = theme.Window.ButtonActive;
        menuTheme.HighlightActive = theme.Window.ButtonActive;
        menuTheme.PopupBackground = theme.Window.WindowBg;
        menuTheme.BorderColor = theme.ContentPanel.BorderColor;

        m_menuBar.ApplyTheme(menuTheme);

        m_standardLayout.ApplyTheme(theme);
        m_compactLayout.ApplyTheme(theme);
        m_standardArtLeftLayout.ApplyTheme(theme);
        m_sidebarLayout.ApplyTheme(theme);
        m_theaterLayout.ApplyTheme(theme);
    }

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

    //==============================================================================
    // Font Management
    //==============================================================================

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

    //==============================================================================
    // Logo
    //==============================================================================

    void UI::LoadSavedLogo(const std::string &path)
    {
        if (!path.empty())
            m_titleBar.LoadLogo(path);
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
            newMode = LayoutMode::Theater;

        if (newMode != m_layoutMode)
        {
            m_layoutMode = newMode;
            m_layoutState.SetCurrentLayout(static_cast<LayoutStateDataModel::Layout>(static_cast<int>(newMode)));
            m_settingsData.SetLayoutMode(static_cast<int>(newMode));

            if (auto *panel = m_standardLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_compactLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_standardArtLeftLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_sidebarLayout.GetContentPanel())
                panel->InvalidateTabSelection();
            if (auto *panel = m_theaterLayout.GetContentPanel())
                panel->InvalidateTabSelection();

            ConnectSettingsWindowForCurrentLayout();
        }
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
        case LayoutMode::Theater:
            return m_theaterLayout.GetContentPanel();
        default:
            return nullptr;
        }
    }

    //==============================================================================
    // Settings Window Connection
    //==============================================================================

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

    void UI::ConnectSettingsWindowForCurrentLayout()
    {
        WindowContentPanel *contentPanel = GetCurrentContentPanel();
        if (contentPanel)
            ConnectSettingsWindow(contentPanel);
    }

    //==============================================================================
    // Global Hotkeys
    //==============================================================================
    void UI::HandleGlobalHotkeys(InputManager &input)
    {
        ImGuiIO &io = ImGui::GetIO();

        // Media keys (from AirPods, keyboard media buttons, etc.) - always process these
        // regardless of ImGui focus
        if (input.IsMediaKeyPressed(HotkeyAction::PlayPause))
        {
            m_playbackController.TogglePlayPause();
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::NextTrack))
        {
            m_playbackController.Next();
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::PreviousTrack))
        {
            m_playbackController.Previous();
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::Stop))
        {
            m_playbackController.Stop();
            return;
        }

        // File Open - Ctrl+O
        if (!io.WantTextInput && input.IsKeyPressed(SDLK_o) &&
            (input.IsKeyDown(SDLK_LCTRL) || input.IsKeyDown(SDLK_RCTRL)))
        {
            OnFileOpen();
            return;
        }

        // Play/Pause - Space (only when NOT typing in an input field)
        if (!io.WantTextInput && input.IsHotkeyPressed(HotkeyAction::PlayPause))
            m_playbackController.TogglePlayPause();

        // Next Track - Ctrl+Right
        if (input.IsHotkeyPressed(HotkeyAction::NextTrack))
            m_playbackController.Next();

        // Previous Track - Ctrl+Left
        if (input.IsHotkeyPressed(HotkeyAction::PreviousTrack))
            m_playbackController.Previous();

        // Stop - Ctrl+S
        if (input.IsHotkeyPressed(HotkeyAction::Stop))
            m_playbackController.Stop();

        // Volume Up - Ctrl+Up
        if (input.IsHotkeyPressed(HotkeyAction::VolumeUp))
        {
            float vol = m_playbackController.GetVolume() + 0.05f;
            if (vol > 1.0f)
                vol = 1.0f;
            m_playbackController.SetVolume(vol);
        }

        // Volume Down - Ctrl+Down
        if (input.IsHotkeyPressed(HotkeyAction::VolumeDown))
        {
            float vol = m_playbackController.GetVolume() - 0.05f;
            if (vol < 0.0f)
                vol = 0.0f;
            m_playbackController.SetVolume(vol);
        }

        // Mute Toggle - Ctrl+M
        if (input.IsHotkeyPressed(HotkeyAction::MuteToggle))
        {
            float currentVol = m_playbackController.GetVolume();
            if (currentVol > 0.0f)
            {
                m_lastVolumeBeforeMute = currentVol;
                m_playbackController.SetVolume(0.0f);
            }
            else
            {
                m_playbackController.SetVolume(m_lastVolumeBeforeMute);
            }
        }

        // Seek Forward 5s - Right arrow (no Ctrl)
        if (input.IsHotkeyPressed(HotkeyAction::SeekForward))
        {
            float pos = m_playbackController.GetCurrentPosition();
            float dur = m_playbackController.GetCurrentDuration();
            if (dur > 0.0f)
                m_playbackController.SeekTo((std::min)(pos + 5.0f, dur));
        }

        // Seek Backward 5s - Left arrow (no Ctrl)
        if (input.IsHotkeyPressed(HotkeyAction::SeekBackward))
        {
            float pos = m_playbackController.GetCurrentPosition();
            m_playbackController.SeekTo((std::max)(pos - 5.0f, 0.0f));
        }
    }

    //==============================================================================
    // Menu Bar Setup
    //==============================================================================

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
        { OnViewLayout(static_cast<LayoutMode>(mode)); };
        m_menuBar.OnPlaybackPlay = [this]()
        { m_playbackController.TogglePlayPause(); };
        m_menuBar.OnPlaybackPause = [this]()
        { OnPlaybackPause(); };
        m_menuBar.OnPlaybackStop = [this]()
        { OnPlaybackStop(); };
        m_menuBar.OnNextTrack = [this]()
        { m_playbackController.Next(); };
        m_menuBar.OnPreviousTrack = [this]()
        { m_playbackController.Previous(); };
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

    //==============================================================================
    // Menu Bar Actions - File
    //==============================================================================

    void UI::OnFileOpen()
    {
        auto path = OpenAudioFileDialog();
        if (path.has_value())
            OpenAndPlayTemporaryAudioFile(path.value());
    }

    void UI::OpenAndPlayTemporaryAudioFile(const std::filesystem::path &filePath)
    {
        if (filePath.empty() || !std::filesystem::exists(filePath))
        {
            std::cerr << "[UI] File does not exist: " << filePath << std::endl;
            return;
        }

        std::cout << "[UI] Opening temporary audio file: " << filePath << std::endl;

        MetadataReader reader;
        MusicTrack track = reader.ReadMetadataForSingleTrack(filePath);

        if (track.GetTitle().empty() || track.GetTitle() == "Unknown Track")
        {
            std::string filename = filePath.filename().string();
            size_t dotPos = filename.find_last_of('.');
            if (dotPos != std::string::npos)
                filename = filename.substr(0, dotPos);
            track.SetTitle(filename);
        }

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

        std::cout << "[UI] Temporary track: " << track.GetTitle()
                  << " - " << track.GetArtist()
                  << " (" << track.GetDuration() << "s)" << std::endl;

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

    //==============================================================================
    // Menu Bar Actions - View
    //==============================================================================

    void UI::OnViewLayout(LayoutMode mode)
    {
        if (mode == m_layoutMode)
            return;

        m_layoutMode = mode;
        m_layoutState.SetCurrentLayout(static_cast<LayoutStateDataModel::Layout>(static_cast<int>(mode)));
        m_settingsData.SetLayoutMode(static_cast<int>(mode));

        if (auto *panel = m_standardLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_compactLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_standardArtLeftLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_sidebarLayout.GetContentPanel())
            panel->InvalidateTabSelection();
        if (auto *panel = m_theaterLayout.GetContentPanel())
            panel->InvalidateTabSelection();

        ConnectSettingsWindowForCurrentLayout();
    }

    //==============================================================================
    // Menu Bar Actions - Playback
    //==============================================================================

    void UI::OnPlaybackPlay() { m_playbackController.Play(); }
    void UI::OnPlaybackPause() { m_playbackController.Pause(); }
    void UI::OnPlaybackStop() { m_playbackController.Stop(); }

    //==============================================================================
    // Menu Bar Actions - Help
    //==============================================================================

    void UI::OnHelpAbout()
    {
        ImGui::OpenPopup("About Moosic");
    }

} // namespace moosic