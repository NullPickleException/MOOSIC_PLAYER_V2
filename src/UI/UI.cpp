//==============================================================================
// UI.cpp
//==============================================================================
// Main UI controller implementation
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

    // ---- Data-layer ticks (always run, independent of tab/layout) ----
    m_directoryData.Update();

    if (m_libraryData.NeedsRefresh())
        m_libraryData.Refresh();

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    const float titleBarHeight = m_titleBar.GetTheme().Height;
    const float borderThickness = m_themeManager.GetTheme().ContentPanel.BorderThickness;

    // Draw menu bar
    m_menuBar.Draw(titleBarHeight, borderThickness,
                   m_themeManager.GetTheme().ContentPanel.BorderColor,
                   m_themeManager.GetTheme().Window.TitleBar);

    const float menuBarHeight = m_menuBar.GetHeight();
    const float topChrome = titleBarHeight + menuBarHeight + borderThickness;

    // Save original viewport
    const ImVec2 originalPos = viewport->Pos;
    const ImVec2 originalSize = viewport->Size;
    const ImVec2 originalWorkPos = viewport->WorkPos;
    const ImVec2 originalWorkSize = viewport->WorkSize;

    // Adjust viewport to exclude title bar and menu bar
    viewport->Pos = ImVec2(originalPos.x, originalPos.y + topChrome);
    viewport->Size = ImVec2(originalSize.x, originalSize.y - topChrome);
    viewport->WorkPos = viewport->Pos;
    viewport->WorkSize = viewport->Size;

    // Draw current layout content
    DrawCurrentLayout(renderer);

    // Restore viewport BEFORE drawing popups so they render on the full screen
    viewport->Pos = originalPos;
    viewport->Size = originalSize;
    viewport->WorkPos = originalWorkPos;
    viewport->WorkSize = originalWorkSize;

    // Draw popups (must be after viewport restore)
    DrawAboutPopup();

    // Draw title bar last (always on top)
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

        // Colors
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

        // Sizing
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

        //====================================================================
        // Media keys (headphones / AirPods / keyboard media row)
        // Debounced to prevent double-tap issues
        //====================================================================
        static Uint32 lastMediaActionTime = 0;
        const Uint32 now = SDL_GetTicks();
        const Uint32 MEDIA_DEBOUNCE_MS = 350;

        if (input.IsMediaKeyPressed(HotkeyAction::PlayPause))
        {
            if (now - lastMediaActionTime > MEDIA_DEBOUNCE_MS)
            {
                m_playbackController.TogglePlayPause();
                lastMediaActionTime = now;
            }
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::NextTrack))
        {
            if (now - lastMediaActionTime > MEDIA_DEBOUNCE_MS)
            {
                m_playbackController.Next();
                lastMediaActionTime = now;
            }
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::PreviousTrack))
        {
            if (now - lastMediaActionTime > MEDIA_DEBOUNCE_MS)
            {
                m_playbackController.Previous();
                lastMediaActionTime = now;
            }
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::Stop))
        {
            if (now - lastMediaActionTime > MEDIA_DEBOUNCE_MS)
            {
                m_playbackController.Stop();
                lastMediaActionTime = now;
            }
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::MuteToggle))
        {
            if (now - lastMediaActionTime > MEDIA_DEBOUNCE_MS)
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
                lastMediaActionTime = now;
            }
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::VolumeUp))
        {
            float vol = m_playbackController.GetVolume() + 0.05f;
            if (vol > 1.0f)
                vol = 1.0f;
            m_playbackController.SetVolume(vol);
            return;
        }
        if (input.IsMediaKeyPressed(HotkeyAction::VolumeDown))
        {
            float vol = m_playbackController.GetVolume() - 0.05f;
            if (vol < 0.0f)
                vol = 0.0f;
            m_playbackController.SetVolume(vol);
            return;
        }

        //====================================================================
        // Keyboard shortcuts (blocked while typing in text fields)
        //====================================================================
        if (!io.WantTextInput && input.IsKeyPressed(SDLK_o) &&
            (input.IsKeyDown(SDLK_LCTRL) || input.IsKeyDown(SDLK_RCTRL)))
        {
            OnFileOpen();
            return;
        }

        if (!io.WantTextInput && input.IsHotkeyPressed(HotkeyAction::PlayPause))
            m_playbackController.TogglePlayPause();

        if (input.IsHotkeyPressed(HotkeyAction::NextTrack))
            m_playbackController.Next();

        if (input.IsHotkeyPressed(HotkeyAction::PreviousTrack))
            m_playbackController.Previous();

        if (input.IsHotkeyPressed(HotkeyAction::Stop))
            m_playbackController.Stop();

        if (input.IsHotkeyPressed(HotkeyAction::VolumeUp))
        {
            float vol = m_playbackController.GetVolume() + 0.05f;
            if (vol > 1.0f)
                vol = 1.0f;
            m_playbackController.SetVolume(vol);
        }

        if (input.IsHotkeyPressed(HotkeyAction::VolumeDown))
        {
            float vol = m_playbackController.GetVolume() - 0.05f;
            if (vol < 0.0f)
                vol = 0.0f;
            m_playbackController.SetVolume(vol);
        }

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

        if (input.IsHotkeyPressed(HotkeyAction::SeekForward))
        {
            float pos = m_playbackController.GetCurrentPosition();
            float dur = m_playbackController.GetCurrentDuration();
            if (dur > 0.0f)
                m_playbackController.SeekTo((std::min)(pos + 5.0f, dur));
        }

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
        m_showAboutPopup = true;
    }

    void UI::DrawAboutPopup()
    {
        // Open the popup if requested this frame
        if (m_showAboutPopup)
        {
            ImGui::OpenPopup("About Moosic");
            m_showAboutPopup = false;
        }

        // -------------------------------------------------------------------------
        // Popup configuration - responsive to window size
        // -------------------------------------------------------------------------

        ImVec2 viewportSize = ImGui::GetMainViewport()->Size;

        // Calculate popup size as percentage of viewport
        // Min size: 400x380, Max size: 600x500
        float popupWidth = std::clamp(viewportSize.x * 0.35f, 470.0f, 600.0f);
        float popupHeight = std::clamp(viewportSize.y * 0.55f, 445.0f, 500.0f);
        ImVec2 popupSize(popupWidth, popupHeight);

        ImGui::SetNextWindowSize(popupSize, ImGuiCond_Always);

        // Center the popup on screen
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal(
                "About Moosic",
                nullptr,
                ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoSavedSettings))
        {
            // ---------------------------------------------------------------------
            // Header
            // ---------------------------------------------------------------------

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + popupHeight * 0.025f);

            const char *title = "MOOSIC";
            const char *version = "Version 2.0.0";

            float titleWidth = ImGui::CalcTextSize(title).x;
            ImGui::SetCursorPosX((popupSize.x - titleWidth) * 0.5f);
            ImGui::TextColored(ImVec4(0.30f, 0.70f, 1.00f, 1.0f), "%s", title);

            float versionWidth = ImGui::CalcTextSize(version).x;
            ImGui::SetCursorPosX((popupSize.x - versionWidth) * 0.5f);
            ImGui::TextDisabled("%s", version);

            ImGui::Spacing();
            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // Divider
            // ---------------------------------------------------------------------

            const float paddingX = popupWidth * 0.05f;
            ImGui::SetCursorPosX(paddingX);
            ImGui::Separator();

            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // About MOOSIC
            // ---------------------------------------------------------------------

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::TextColored(ImVec4(0.85f, 0.85f, 0.90f, 1.0f), "About MOOSIC");

            ImGui::Spacing();

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::PushTextWrapPos(popupSize.x - paddingX - 6.0f);
            ImGui::TextWrapped(
                "MOOSIC is a free, open-source, cross-platform music player "
                "made for desktop. Built with C++ and focuses on a lightweight "
                "desktop experience, local music playback, customizable themes, "
                "and a clean library management workflow.");
            ImGui::PopTextWrapPos();

            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // GitHub (selectable text)
            // ---------------------------------------------------------------------

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::TextColored(ImVec4(0.85f, 0.85f, 0.90f, 1.0f), "Source Code");

            ImGui::Spacing();

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::Text("GitHub: ");

            ImGui::SameLine(0.0f, 0.0f);

            // Selectable link text
            const char *githubUrl = "github.com/NullPickleException/MOOSIC_PLAYER_V2";
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.75f, 1.00f, 1.0f));
            ImGui::TextUnformatted(githubUrl);

            // Store the position and size for hit testing
            ImVec2 githubMin = ImGui::GetItemRectMin();
            ImVec2 githubMax = ImGui::GetItemRectMax();

            // Make it selectable - draw invisible selectable over it
            ImGui::SetCursorScreenPos(githubMin);
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.26f, 0.59f, 0.98f, 0.3f));
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.26f, 0.59f, 0.98f, 0.5f));
            bool githubClicked = ImGui::Selectable("##GitHubLink", false, 0, ImVec2(githubMax.x - githubMin.x, githubMax.y - githubMin.y));
            ImGui::PopStyleColor(4);

            if (githubClicked)
            {
#ifdef _WIN32
                ShellExecuteA(NULL, "open", "https://github.com/NullPickleException/MOOSIC_PLAYER_V2", NULL, NULL, SW_SHOWNORMAL);
#elif defined(__APPLE__)
                system("open https://github.com/NullPickleException/MOOSIC_PLAYER_V2");
#else
                system("xdg-open https://github.com/NullPickleException/MOOSIC_PLAYER_V2");
#endif
            }

            if (ImGui::IsItemHovered())
            {
                ImGui::SetTooltip("Click to open in browser");
            }

            ImGui::Spacing();
            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // Artwork Credit
            // ---------------------------------------------------------------------

            ImGui::SetCursorPosX(paddingX);
            ImGui::Separator();

            ImGui::Spacing();

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::TextColored(ImVec4(0.85f, 0.85f, 0.90f, 1.0f), "Artwork & Icon Design");

            ImGui::Spacing();

            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::PushTextWrapPos(popupSize.x - paddingX - 6.0f);
            ImGui::TextWrapped(
                "Pixel art and cow artwork used throughout MOOSIC "
                "were created by my friend, whose work helped give "
                "the project its visual identity.");
            ImGui::PopTextWrapPos();

            ImGui::Spacing();

            // Artist name
            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::Text("Artist: ");

            ImGui::SameLine(0.0f, 0.0f);

            const char *artistName = "Friend's Name";
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.85f, 0.90f, 1.0f));
            ImGui::TextUnformatted(artistName);
            ImGui::PopStyleColor();

            ImGui::Spacing();

            // ArtStation link
            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::TextDisabled("ArtStation:");

            ImGui::SameLine(0.0f, 8.0f);

            const char *artStationLink = "[ArtStation link]";
            ImVec2 artStationMin = ImGui::GetCursorScreenPos();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.75f, 1.00f, 1.0f));
            ImGui::TextUnformatted(artStationLink);
            ImGui::PopStyleColor();
            ImVec2 artStationMax = ImGui::GetItemRectMax();

            // Make it clickable
            ImGui::SetCursorScreenPos(artStationMin);
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.26f, 0.59f, 0.98f, 0.3f));
            bool artStationClicked = ImGui::Selectable("##ArtStationLink", false, 0, ImVec2(artStationMax.x - artStationMin.x, artStationMax.y - artStationMin.y));
            ImGui::PopStyleColor(2);

            if (artStationClicked)
            {
                // Handle ArtStation click
            }

            // Pinterest link
            ImGui::SetCursorPosX(paddingX + 6.0f);
            ImGui::TextDisabled("Pinterest:");

            ImGui::SameLine(0.0f, 14.0f);

            const char *pinterestLink = "[Pinterest link]";
            ImVec2 pinterestMin = ImGui::GetCursorScreenPos();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.40f, 0.75f, 1.00f, 1.0f));
            ImGui::TextUnformatted(pinterestLink);
            ImGui::PopStyleColor();
            ImVec2 pinterestMax = ImGui::GetItemRectMax();

            // Make it clickable
            ImGui::SetCursorScreenPos(pinterestMin);
            ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.26f, 0.59f, 0.98f, 0.3f));
            bool pinterestClicked = ImGui::Selectable("##PinterestLink", false, 0, ImVec2(pinterestMax.x - pinterestMin.x, pinterestMax.y - pinterestMin.y));
            ImGui::PopStyleColor(2);

            if (pinterestClicked)
            {
                // Handle Pinterest click
            }

            ImGui::Spacing();
            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // Footer
            // ---------------------------------------------------------------------

            ImGui::SetCursorPosX(paddingX);
            ImGui::Separator();

            ImGui::Spacing();

            const char *footer = "Thank You for Choosing MOOSIC, Enjoy.";
            float footerWidth = ImGui::CalcTextSize(footer).x;
            ImGui::SetCursorPosX((popupSize.x - footerWidth) * 0.5f);
            ImGui::TextDisabled("%s", footer);

            ImGui::Spacing();

            // ---------------------------------------------------------------------
            // Close button
            // ---------------------------------------------------------------------

            // Scale button size with popup
            float buttonWidth = std::clamp(popupWidth * 0.25f, 100.0f, 140.0f);
            float buttonHeight = std::clamp(popupHeight * 0.07f, 28.0f, 36.0f);
            ImGui::SetCursorPosX((popupSize.x - buttonWidth) * 0.5f);

            if (ImGui::Button("OK", ImVec2(buttonWidth, buttonHeight)))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + popupHeight * 0.01f);

            ImGui::EndPopup();
        }
    }

} // namespace moosic