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
#include "Data/SettingsDataModel.h"

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
        void LoadSavedLogo(const std::string &path);

        void ApplyPendingFont();

    private:
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
        void ConnectSettingsWindow(WindowContentPanel *contentPanel);
        void ConnectSettingsWindowForCurrentLayout();

        void LoadFont(const std::string &fontPath, float fontSize);

    private:
        // Shared data models - ORDER MATTERS for initialization
        LibraryDataModel m_libraryData;
        PlaylistDataModel m_playlistData;   // MUST be before m_directoryData
        DirectoryDataModel m_directoryData; // Takes pointer to m_playlistData
        SettingsDataModel m_settingsData;

        ThemeManager m_themeManager;
        TitleBar m_titleBar;
        LayoutMode m_layoutMode = LayoutMode::Standard;

        MainLayout m_standardLayout;
        SidebarLeftLayout m_sidebarLayout;
        CompactLayout m_compactLayout;
        MiniPlayerLayout m_miniPlayerLayout;
        TheaterLayout m_theaterLayout;
        StandardArtLeftLayout m_standardArtLeftLayout;

        PlaybackController &m_playbackController;
        MusicLibrary &m_library;

        // Font reload state
        bool m_fontNeedsReload = false;
        std::string m_pendingFontPath;
        float m_pendingFontSize = 16.0f;

        bool m_initialized = false;
    };

} // namespace moosic