//==============================================================================
// UI.h
//==============================================================================
// Main UI controller - manages layouts, themes, fonts, menu bar, hotkeys
//==============================================================================

#pragma once

#include "../Models/MusicLibrary.h"
#include "../Services/PlaybackController.h"
#include "../Core/Input/InputManager.h"

#include "Data/LibraryDataModel.h"
#include "Data/DirectoryDataModel.h"
#include "Data/PlaylistDataModel.h"
#include "Data/SettingsDataModel.h"
#include "Data/LayoutStateDataModel.h"

#include "Layouts/MainLayout.h"
#include "Layouts/CompactLayout.h"
#include "Layouts/StandardArtLeftLayout.h"
#include "Layouts/SidebarLeftLayout.h"
#include "Layouts/MiniPlayerLayout.h"
#include "Layouts/TheaterLayout.h"

#include "Widgets/TitleBar/TitleBar.h"
#include "Widgets/MenuBar/MenuBar.h"

#include "Theme/ThemeManager.h"

#include <SDL.h>

namespace moosic
{
    class WindowContentPanel;

    class UI
    {
    public:
        //======================================================================
        // Construction / Initialization
        //======================================================================
        
        UI(MusicLibrary &library, PlaybackController &playbackController);
        void Initialize(SDL_Window *window);

        //======================================================================
        // Main Draw
        //======================================================================
        
        void Draw(SDL_Renderer *renderer, InputManager &input);

        //======================================================================
        // Theme Management
        //======================================================================
        
        void SetTheme(const Theme &theme);
        void SetTheme(const std::string &themeName);
        const Theme &GetTheme() const;
        ThemeManager &GetThemeManager();

        //======================================================================
        // Layout Access
        //======================================================================
        
        WindowContentPanel *GetCurrentContentPanel();

        //======================================================================
        // Data Model Access
        //======================================================================
        
        SettingsDataModel &GetSettingsDataModel() { return m_settingsData; }
        const SettingsDataModel &GetSettingsDataModel() const { return m_settingsData; }

        PlaylistDataModel &GetPlaylistDataModel() { return m_playlistData; }
        const PlaylistDataModel &GetPlaylistDataModel() const { return m_playlistData; }

        LayoutStateDataModel &GetLayoutState() { return m_layoutState; }
        const LayoutStateDataModel &GetLayoutState() const { return m_layoutState; }

        //======================================================================
        // Font & Logo
        //======================================================================
        
        void LoadSavedLogo(const std::string &path);
        void ApplyPendingFont();

        //======================================================================
        // Startup
        //======================================================================
        
        void ScanForNewFilesOnStartup() { m_directoryData.ScanForNewFiles(); }

    private:
        //======================================================================
        // Layout Mode
        //======================================================================
        
        enum class LayoutMode
        {
            Standard = 0,
            Compact = 1,
            StandardArtLeft = 2,
            SidebarLeft = 3,
            Theater = 4
        };

        //======================================================================
        // Layout Switching
        //======================================================================
        
        void HandleLayoutSwitch(InputManager &input);
        void DrawCurrentLayout(SDL_Renderer *renderer);

        //======================================================================
        // Theme Application
        //======================================================================
        
        void ApplyThemeToLayouts();
        void ApplyImGuiStyle(const Theme &theme);

        //======================================================================
        // Settings Window
        //======================================================================
        
        void ConnectSettingsWindow(WindowContentPanel *contentPanel);
        void ConnectSettingsWindowForCurrentLayout();

        //======================================================================
        // Font Management
        //======================================================================
        
        void LoadFont(const std::string &fontPath, float fontSize);

        //======================================================================
        // Menu Bar
        //======================================================================
        
        void DrawMenuBar();
        void SetupMenuBarCallbacks();

        //======================================================================
        // Menu Bar Actions - File
        //======================================================================
        
        void OnFileOpen();
        void OnFileExit();
        void OpenAndPlayTemporaryAudioFile(const std::filesystem::path &filePath);

        //======================================================================
        // Menu Bar Actions - View
        //======================================================================
        
        void OnViewLayout(LayoutMode mode);

        //======================================================================
        // Menu Bar Actions - Playback
        //======================================================================
        
        void OnPlaybackPlay();
        void OnPlaybackPause();
        void OnPlaybackStop();

        //======================================================================
        // Menu Bar Actions - Help
        //======================================================================
        
        void OnHelpAbout();
        void DrawAboutPopup();

        //======================================================================
        // Global Hotkeys
        //======================================================================
        
        void HandleGlobalHotkeys(InputManager &input);

        //======================================================================
        // Data Models
        //======================================================================
        
        LibraryDataModel m_libraryData;
        PlaylistDataModel m_playlistData;
        DirectoryDataModel m_directoryData;
        SettingsDataModel m_settingsData;
        LayoutStateDataModel m_layoutState;

        //======================================================================
        // Theme & Chrome
        //======================================================================
        
        ThemeManager m_themeManager;
        TitleBar m_titleBar;
        MenuBar m_menuBar;

        //======================================================================
        // Layout State
        //======================================================================
        
        LayoutMode m_layoutMode = LayoutMode::Standard;

        //======================================================================
        // Layout Instances
        //======================================================================
        
        MainLayout m_standardLayout;
        CompactLayout m_compactLayout;
        StandardArtLeftLayout m_standardArtLeftLayout;
        SidebarLeftLayout m_sidebarLayout;
        TheaterLayout m_theaterLayout;

        //======================================================================
        // Core References
        //======================================================================
        
        PlaybackController &m_playbackController;
        MusicLibrary &m_library;

        //======================================================================
        // Font State
        //======================================================================
        
        bool m_fontNeedsReload = false;
        std::string m_pendingFontPath;
        float m_pendingFontSize = 16.0f;

        //======================================================================
        // Initialization Flags
        //======================================================================
        
        bool m_initialized = false;
        bool m_menuCallbacksSet = false;

        //======================================================================
        // Hotkey State
        //======================================================================
        
        float m_lastVolumeBeforeMute = 0.8f;

        //======================================================================
        // Popup State
        //======================================================================
        
        bool m_showAboutPopup = false;
    };

} // namespace moosic