//==============================================================================
// UI.h
//==============================================================================
// Main UI coordinator that manages layouts, themes, and input
//==============================================================================

#pragma once

#include "../Models/MusicLibrary.h"
#include "../Services/PlaybackController.h"
#include "../Core/Input/InputManager.h"

#include "Data/LibraryDataModel.h"
#include "Data/DirectoryDataModel.h"
#include "Data/PlaylistDataModel.h"
#include "Data/SettingsDataModel.h"  // NEW: Settings data model

#include "Layouts/MainLayout.h"
#include "Layouts/SidebarLeftLayout.h"
#include "Layouts/CompactLayout.h"
#include "Layouts/MiniPlayerLayout.h"
#include "Layouts/TheaterLayout.h"
#include "Layouts/StandardArtLeftLayout.h"

#include "Widgets/TitleBar/TitleBar.h"

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
        UI(MusicLibrary &library, PlaybackController &playbackController);

        //--------------------------------------------------------------------------
        // Core
        //--------------------------------------------------------------------------

        void Draw(SDL_Renderer *renderer, InputManager &input);

        //--------------------------------------------------------------------------
        // Initialization - Call AFTER ImGui context is created
        //--------------------------------------------------------------------------

        void Initialize(SDL_Window *window);

        //--------------------------------------------------------------------------
        // Theme
        //--------------------------------------------------------------------------

        void SetTheme(const Theme &theme);
        void SetTheme(const std::string &themeName);
        const Theme &GetTheme() const;
        ThemeManager &GetThemeManager();

        //--------------------------------------------------------------------------
        // Get Current Layout's Content Panel
        //--------------------------------------------------------------------------

        WindowContentPanel *GetCurrentContentPanel();
        
        //--------------------------------------------------------------------------
        // Settings Data Model Access (shared state)
        //--------------------------------------------------------------------------
        
        SettingsDataModel& GetSettingsDataModel() { return m_settingsData; }
        const SettingsDataModel& GetSettingsDataModel() const { return m_settingsData; }

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

        void HandleLayoutSwitch(InputManager &input);
        void DrawCurrentLayout(SDL_Renderer *renderer);
        void ApplyThemeToLayouts();
        void ApplyImGuiStyle(const Theme &theme);

        //--------------------------------------------------------------------------
        // Settings Window Connection
        //--------------------------------------------------------------------------

        void ConnectSettingsWindow(WindowContentPanel *contentPanel);
        void ConnectSettingsWindowForCurrentLayout();

    private:
        // Shared data models - created once, shared by all layouts
        LibraryDataModel m_libraryData;
        DirectoryDataModel m_directoryData;
        PlaylistDataModel m_playlistData;
        SettingsDataModel m_settingsData;  // NEW: Shared settings state

        // Theme
        ThemeManager m_themeManager;

        // Title Bar
        TitleBar m_titleBar;

        // Layout
        LayoutMode m_layoutMode = LayoutMode::Standard;

        // Layouts - all share the same data models
        MainLayout m_standardLayout;
        SidebarLeftLayout m_sidebarLayout;
        CompactLayout m_compactLayout;
        MiniPlayerLayout m_miniPlayerLayout;
        TheaterLayout m_theaterLayout;
        StandardArtLeftLayout m_standardArtLeftLayout;

        // Dependencies
        PlaybackController &m_playbackController;
        MusicLibrary &m_library;

        // State
        bool m_initialized = false;
    };

} // namespace moosic