//==============================================================================
// Theme.h
//==============================================================================
// Master theme structure that aggregates all sub-themes
//==============================================================================

#pragma once

#include "../Windows/IWindow.h"
#include "WindowContentPanelTheme.h"
#include "../Widgets/PlayerBar/IPlayerBar.h"
#include "../Widgets/TrackTable.h"
#include "../Widgets/WaveVisualizer.h"
#include "../Widgets/AlbumArtBox.h"
#include "../Widgets/AlbumArtLightBox.h"
#include "../Widgets/TitleBar/TitleBar.h"


namespace moosic
{

    //==============================================================================
    // Theme
    //==============================================================================

    struct Theme
    {

        //--------------------------------------------------------------------------
        // Windows
        //--------------------------------------------------------------------------

        WindowTheme Window;
        WindowContentPanelTheme ContentPanel;

        //--------------------------------------------------------------------------
        // Standalone Widgets
        //--------------------------------------------------------------------------

        TitleBarTheme TitleBar;
        TrackTableStyle TrackTable;
        WaveVisualizerStyle Visualizer;
        AlbumArtBoxTheme AlbumArtBox;
        LightboxTheme AlbumArtLightbox;

        //--------------------------------------------------------------------------
        // Composite Widgets
        //--------------------------------------------------------------------------

        PlayerBarTheme PlayerBar;

        //--------------------------------------------------------------------------
        // Future Widgets
        //--------------------------------------------------------------------------

        // SearchBarTheme SearchBar;
        // PlaylistTheme Playlist;
        // QueueTheme Queue;
        // SpectrumTheme Spectrum;
        // LyricsTheme Lyrics;
        // NotificationTheme Notifications;

        //--------------------------------------------------------------------------
        // Layouts
        //--------------------------------------------------------------------------

        // MainLayoutTheme MainLayout;
        // SidebarLayoutTheme SidebarLayout;
        // TheaterLayoutTheme TheaterLayout;
    };

    //==============================================================================
    // Factory Functions
    //==============================================================================

    Theme CreateDarkTheme();
    Theme CreateLightTheme();
    Theme CreateDraculaTheme();
    Theme CreateNordTheme();
    Theme CreateGruvboxTheme();
    Theme CreateCatppuccinTheme();
    Theme CreateSolarizedDarkTheme();
    Theme CreateSolarizedLightTheme();

} // namespace moosic