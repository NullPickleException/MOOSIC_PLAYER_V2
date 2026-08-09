//==============================================================================
// UI.h (REVISED with Hotkeys)
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
        UI(MusicLibrary &library, PlaybackController &playbackController);

        void Draw(SDL_Renderer *renderer, InputManager &input);
        void Initialize(SDL_Window *window);

        void SetTheme(const Theme &theme);
        void SetTheme(const std::string &themeName);
        const Theme &GetTheme() const;
        ThemeManager &GetThemeManager();

        WindowContentPanel *GetCurrentContentPanel();

        SettingsDataModel &GetSettingsDataModel() { return m_settingsData; }
        const SettingsDataModel &GetSettingsDataModel() const { return m_settingsData; }
        
        PlaylistDataModel &GetPlaylistDataModel() { return m_playlistData; }
        const PlaylistDataModel &GetPlaylistDataModel() const { return m_playlistData; }
        
        LayoutStateDataModel &GetLayoutState() { return m_layoutState; }
        const LayoutStateDataModel &GetLayoutState() const { return m_layoutState; }
        
        void LoadSavedLogo(const std::string &path);
        void ApplyPendingFont();

        void ScanForNewFilesOnStartup() { m_directoryData.ScanForNewFiles(); }

    private:
        enum class LayoutMode
        {
            Standard = 0, Compact = 1, StandardArtLeft = 2,
            SidebarLeft = 3, Theater = 4
        };

        void HandleLayoutSwitch(InputManager &input);
        void DrawCurrentLayout(SDL_Renderer *renderer);
        void ApplyThemeToLayouts();
        void ApplyImGuiStyle(const Theme &theme);
        void ConnectSettingsWindow(WindowContentPanel *contentPanel);
        void ConnectSettingsWindowForCurrentLayout();
        void LoadFont(const std::string &fontPath, float fontSize);

        // Menu bar
        void DrawMenuBar();
        void SetupMenuBarCallbacks();
        void OnFileOpen();
        void OnFileExit();
        void OnViewLayout(LayoutMode mode);
        void OnPlaybackPlay();
        void OnPlaybackPause();
        void OnPlaybackStop();
        void OnHelpAbout();
        void OpenAndPlayTemporaryAudioFile(const std::filesystem::path& filePath);

        void HandleGlobalHotkeys(InputManager &input);

        LibraryDataModel m_libraryData;
        PlaylistDataModel m_playlistData;
        DirectoryDataModel m_directoryData;
        SettingsDataModel m_settingsData;
        LayoutStateDataModel m_layoutState;

        ThemeManager m_themeManager;
        TitleBar m_titleBar;
        MenuBar m_menuBar;
        LayoutMode m_layoutMode = LayoutMode::Standard;

        MainLayout m_standardLayout;
        CompactLayout m_compactLayout;
        StandardArtLeftLayout m_standardArtLeftLayout;
        SidebarLeftLayout m_sidebarLayout;
        TheaterLayout m_theaterLayout;

        PlaybackController &m_playbackController;
        MusicLibrary &m_library;

        bool m_fontNeedsReload = false;
        std::string m_pendingFontPath;
        float m_pendingFontSize = 16.0f;
        bool m_initialized = false;
        bool m_menuCallbacksSet = false;

        // ──── NEW: Volume state for mute toggle ────
        float m_lastVolumeBeforeMute = 0.8f;
    };

} // namespace moosic