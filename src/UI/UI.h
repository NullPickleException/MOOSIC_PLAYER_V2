//==============================================================================
// UI.h
//==============================================================================
// Main UI coordinator that manages layouts, themes, and input
//==============================================================================

#pragma once

#include "../Models/MusicLibrary.h"
#include "../Services/PlaybackController.h"
#include "../Core/Input/InputManager.h"

#include "Layouts/MainLayout.h"
#include "Layouts/SidebarLeftLayout.h"
#include "Layouts/CompactLayout.h"
#include "Layouts/MiniPlayerLayout.h"
#include "Layouts/TheaterLayout.h"
#include "Layouts/StandardArtLeftLayout.h"

#include "Theme/ThemeManager.h"

#include <SDL.h>

namespace moosic
{

// Forward declare
class WindowContentPanel;

//==============================================================================
// UI
//==============================================================================

class UI
{
public:
    UI(MusicLibrary& library, PlaybackController& playbackController);

    //--------------------------------------------------------------------------
    // Core
    //--------------------------------------------------------------------------

    void Draw(SDL_Renderer* renderer, InputManager& input);

    //--------------------------------------------------------------------------
    // Initialization - Call AFTER ImGui context is created
    //--------------------------------------------------------------------------

    void Initialize();

    //--------------------------------------------------------------------------
    // Theme
    //--------------------------------------------------------------------------

    void SetTheme(const Theme& theme);
    void SetTheme(const std::string& themeName);
    const Theme& GetTheme() const;
    ThemeManager& GetThemeManager();

private:
    //--------------------------------------------------------------------------
    // Layout Management
    //--------------------------------------------------------------------------

    enum class LayoutMode
    {
        Standard,
        SidebarLeft,
        Compact,
        MiniPlayer,
        Theater,
        StandardArtLeft
    };

    void HandleLayoutSwitch(InputManager& input);
    void DrawCurrentLayout(SDL_Renderer* renderer);
    void ApplyThemeToLayouts();
    void ApplyImGuiStyle(const Theme& theme);
    
    //--------------------------------------------------------------------------
    // Settings Window Connection
    //--------------------------------------------------------------------------

    void ConnectSettingsWindow(WindowContentPanel* contentPanel);
    void ConnectSettingsWindowForCurrentLayout();

    //--------------------------------------------------------------------------
    // Get Current Layout's Content Panel
    //--------------------------------------------------------------------------

    WindowContentPanel* GetCurrentContentPanel();

private:
    // Theme
    ThemeManager m_themeManager;

    // Layout
    LayoutMode m_layoutMode = LayoutMode::Standard;

    // Layouts
    MainLayout m_standardLayout;
    SidebarLeftLayout m_sidebarLayout;
    CompactLayout m_compactLayout;
    MiniPlayerLayout m_miniPlayerLayout;
    TheaterLayout m_theaterLayout;
    StandardArtLeftLayout m_standardArtLeftLayout;

    // Dependencies
    PlaybackController& m_playbackController;
    MusicLibrary& m_library;

    // State
    bool m_initialized = false;
};

} // namespace moosic