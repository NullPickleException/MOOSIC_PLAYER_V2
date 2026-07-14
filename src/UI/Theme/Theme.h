//==============================================================================
// Theme.h
//==============================================================================
// Theme presets for the entire application
// Each theme provides all style structs: PlayerBar, Window, ContentPanel, TrackTable
//==============================================================================

#pragma once

#include "../Widgets/PlayerBar/IPlayerBar.h"
#include "../Windows/IWindow.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/TrackTable.h"
#include "../Widgets/AlbumArtLightBox.h"
#include <string>

namespace moosic
{

//==============================================================================
// Forward declarations of theme structs (these must be defined BEFORE Theme)
//==============================================================================

// PlayerBarTheme - already defined in IPlayerBar.h
// WindowTheme - defined in IWindow.h
// ContentPanelTheme - defined in WindowContentPanel.h
// TrackTableStyle - defined in TrackTable.h
// AlbumArtLightBoxTheme - defined in AlbumArtLightBox.h

//==============================================================================
// Theme - bundles all style structs for one complete look
//==============================================================================

struct Theme
{
    std::string name;
    PlayerBarTheme playerBar;
    WindowTheme window;
    ContentPanelTheme contentPanel;
    TrackTableStyle trackTable;
};

//==============================================================================
// Dark Theme
//==============================================================================

inline Theme CreateDarkTheme()
{
    Theme t;
    t.name = "Dark";

    // PlayerBar
    t.playerBar.TextPrimary = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.playerBar.TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    t.playerBar.ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    t.playerBar.ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    t.playerBar.ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    t.playerBar.ButtonPrimary = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.playerBar.ButtonPrimaryHovered = ImVec4(0.36f, 0.69f, 1.00f, 1.00f);
    t.playerBar.ButtonPrimaryActive = ImVec4(0.16f, 0.49f, 0.88f, 1.00f);
    t.playerBar.SliderTrack = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    t.playerBar.SliderGrab = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.playerBar.SliderGrabActive = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.playerBar.ButtonRounding = 4.0f;
    t.playerBar.SliderRounding = 4.0f;
    t.playerBar.AlbumArtRounding = 4.0f;
    t.playerBar.AlbumArtSize = 60.0f;
    t.playerBar.NormalButtonExtraWidth = 15.0f;
    t.playerBar.PrimaryButtonExtraWidth = 22.0f;
    t.playerBar.ButtonHeightExtra = 3.0f;
    
    t.playerBar.Lightbox.BackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
    t.playerBar.Lightbox.BorderColor = ImVec4(0.3f, 0.3f, 0.3f, 1.0f);
    t.playerBar.Lightbox.CloseButtonColor = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
    t.playerBar.Lightbox.CloseButtonHovered = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    t.playerBar.Lightbox.TitleColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    t.playerBar.Lightbox.ArtistColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    t.playerBar.Lightbox.MaxWidth = 600.0f;
    t.playerBar.Lightbox.MaxHeight = 600.0f;
    t.playerBar.Lightbox.BorderRounding = 4.0f;
    t.playerBar.Lightbox.CloseButtonSize = 30.0f;
    t.playerBar.Lightbox.Padding = 20.0f;

    // Window
    t.window.HeaderText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.window.HeaderSpacing = 4.0f;
    t.window.ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    t.window.ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    t.window.ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    t.window.ButtonRounding = 4.0f;
    t.window.TextPrimary = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.window.TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    t.window.TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    t.window.PlayingHighlight = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
    t.window.ProgressBar = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.window.ChildBg = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    t.window.SeparatorColor = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);

    // ContentPanel
    t.contentPanel.TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.contentPanel.TabInactive = ImVec4(0.10f, 0.22f, 0.40f, 1.00f);
    t.contentPanel.TabHovered = ImVec4(0.18f, 0.40f, 0.70f, 1.00f);
    t.contentPanel.TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.contentPanel.TabTextInactive = ImVec4(0.60f, 0.65f, 0.75f, 1.00f);
    t.contentPanel.BorderColor = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.contentPanel.BorderThickness = 2.0f;
    t.contentPanel.TabSpacing = 2.0f;

    // TrackTable
    t.trackTable.HeaderBackground = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    t.trackTable.RowDefault = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    t.trackTable.RowDefaultAlt = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    t.trackTable.RowHovered = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);
    t.trackTable.RowClicked = ImVec4(0.30f, 0.30f, 0.50f, 0.80f);
    t.trackTable.RowSelected = ImVec4(0.00f, 0.00f, 0.90f, 0.90f);
    t.trackTable.RowPlaying = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
    t.trackTable.BorderColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    t.trackTable.TextColor = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.trackTable.TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    t.trackTable.TextSelected = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.trackTable.TitleWidth = 350.0f;
    t.trackTable.ArtistWidth = 180.0f;
    t.trackTable.AlbumWidth = 180.0f;
    t.trackTable.ExtensionWidth = 50.0f;
    t.trackTable.DurationWidth = 80.0f;
    t.trackTable.DefaultColumnWidth = 150.0f;
    t.trackTable.RowHeight = 18.0f;

    return t;
}

//==============================================================================
// Light Theme
//==============================================================================

inline Theme CreateLightTheme()
{
    Theme t;
    t.name = "Light";

    // PlayerBar
    t.playerBar.TextPrimary = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.playerBar.TextSecondary = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    t.playerBar.ButtonNormal = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.playerBar.ButtonHovered = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    t.playerBar.ButtonActive = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    t.playerBar.ButtonPrimary = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.playerBar.ButtonPrimaryHovered = ImVec4(0.36f, 0.69f, 1.00f, 1.00f);
    t.playerBar.ButtonPrimaryActive = ImVec4(0.16f, 0.49f, 0.88f, 1.00f);
    t.playerBar.SliderTrack = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
    t.playerBar.SliderGrab = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    t.playerBar.SliderGrabActive = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    t.playerBar.ButtonRounding = 4.0f;
    t.playerBar.SliderRounding = 4.0f;
    t.playerBar.AlbumArtRounding = 4.0f;
    t.playerBar.AlbumArtSize = 60.0f;
    t.playerBar.NormalButtonExtraWidth = 15.0f;
    t.playerBar.PrimaryButtonExtraWidth = 22.0f;
    t.playerBar.ButtonHeightExtra = 3.0f;
    
    t.playerBar.Lightbox.BackgroundColor = ImVec4(1.0f, 1.0f, 1.0f, 0.90f);
    t.playerBar.Lightbox.BorderColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    t.playerBar.Lightbox.CloseButtonColor = ImVec4(0.2f, 0.2f, 0.2f, 0.8f);
    t.playerBar.Lightbox.CloseButtonHovered = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    t.playerBar.Lightbox.TitleColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
    t.playerBar.Lightbox.ArtistColor = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
    t.playerBar.Lightbox.MaxWidth = 600.0f;
    t.playerBar.Lightbox.MaxHeight = 600.0f;
    t.playerBar.Lightbox.BorderRounding = 4.0f;
    t.playerBar.Lightbox.CloseButtonSize = 30.0f;
    t.playerBar.Lightbox.Padding = 20.0f;

    // Window
    t.window.HeaderText = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.window.HeaderSpacing = 4.0f;
    t.window.ButtonNormal = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.window.ButtonHovered = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    t.window.ButtonActive = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);
    t.window.ButtonRounding = 4.0f;
    t.window.TextPrimary = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.window.TextSecondary = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    t.window.TextDisabled = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    t.window.PlayingHighlight = ImVec4(0.00f, 0.60f, 0.00f, 0.80f);
    t.window.ProgressBar = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.window.ChildBg = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    t.window.SeparatorColor = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);

    // ContentPanel
    t.contentPanel.TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.contentPanel.TabInactive = ImVec4(0.80f, 0.85f, 0.92f, 1.00f);
    t.contentPanel.TabHovered = ImVec4(0.65f, 0.72f, 0.85f, 1.00f);
    t.contentPanel.TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.contentPanel.TabTextInactive = ImVec4(0.30f, 0.35f, 0.45f, 1.00f);
    t.contentPanel.BorderColor = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    t.contentPanel.BorderThickness = 2.0f;
    t.contentPanel.TabSpacing = 2.0f;

    // TrackTable
    t.trackTable.HeaderBackground = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    t.trackTable.RowDefault = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    t.trackTable.RowDefaultAlt = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    t.trackTable.RowHovered = ImVec4(0.80f, 0.85f, 0.92f, 1.00f);
    t.trackTable.RowClicked = ImVec4(0.70f, 0.75f, 0.85f, 0.80f);
    t.trackTable.RowSelected = ImVec4(0.26f, 0.59f, 0.98f, 0.50f);
    t.trackTable.RowPlaying = ImVec4(0.00f, 0.60f, 0.00f, 0.50f);
    t.trackTable.BorderColor = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    t.trackTable.TextColor = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.trackTable.TextDisabled = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
    t.trackTable.TextSelected = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.trackTable.TitleWidth = 350.0f;
    t.trackTable.ArtistWidth = 180.0f;
    t.trackTable.AlbumWidth = 180.0f;
    t.trackTable.ExtensionWidth = 50.0f;
    t.trackTable.DurationWidth = 80.0f;
    t.trackTable.DefaultColumnWidth = 150.0f;
    t.trackTable.RowHeight = 18.0f;

    return t;
}

} // namespace moosic