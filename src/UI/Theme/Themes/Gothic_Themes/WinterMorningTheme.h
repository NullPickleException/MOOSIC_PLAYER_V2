//==============================================================================
// WinterMorningTheme.h
//==============================================================================
// Quiet winter morning - cold, solemn, gentle dawn light with blue shift
// Palette: #0a0e18 (night sky), #1b2736 (frozen lake), #3c4e64 (hoarfrost),
//          #8b9eb8 (morning mist), #edf1f8 (pale winter sun)
// 55% Deep winter night transitioning to dawn (#0a0e18 → #1b2736)
// 25% Hoarfrost and icy stone surfaces (#3c4e64, #556880, #8b9eb8)
// 10% Morning mist accent (#8b9eb8)
// 10% Pale winter sun text (#edf1f8)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateWinterMorningTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Quiet winter morning with blue shift
        //==========================================================================

        // 55% - Deep winter night transitioning to dawn (blue-shifted)
        const ImVec4 NightSky      = ImVec4(0.039f, 0.055f, 0.094f, 1.00f);  // #0a0e18 - Pre-dawn sky with blue
        const ImVec4 FrozenLake    = ImVec4(0.106f, 0.153f, 0.212f, 1.00f);  // #1b2736 - Frozen lake surface
        const ImVec4 DawnShadow    = ImVec4(0.137f, 0.188f, 0.255f, 1.00f);  // #233041 - Dawn shadows (library bg)
        const ImVec4 MorningStone  = ImVec4(0.169f, 0.224f, 0.294f, 1.00f);  // #2b394b - Morning-lit stone
        const ImVec4 PaleSky       = ImVec4(0.200f, 0.259f, 0.333f, 1.00f);  // #334255 - Pale winter sky

        const ImVec4 WinterGlow       = ImVec4(0.545f, 0.620f, 0.722f, 0.15f); // Soft blue morning glow
        const ImVec4 WinterVeryLight  = ImVec4(0.545f, 0.620f, 0.722f, 0.40f);
        const ImVec4 WinterSubtle     = ImVec4(0.545f, 0.620f, 0.722f, 0.08f);

        // 25% - Hoarfrost and icy stone surfaces (blue-shifted)
        const ImVec4 Hoarfrost     = ImVec4(0.235f, 0.306f, 0.392f, 1.00f);  // #3c4e64 - Hoarfrost on stone
        const ImVec4 IcyStone      = ImVec4(0.333f, 0.408f, 0.502f, 1.00f);  // #556880 - Icy stone
        const ImVec4 FrostedGlass  = ImVec4(0.545f, 0.620f, 0.722f, 1.00f);  // #8b9eb8 - Frosted morning glass

        // 10% - Morning mist accent (blue-shifted)
        const ImVec4 Accent          = ImVec4(0.545f, 0.620f, 0.722f, 1.00f);  // #8b9eb8 - Morning mist
        const ImVec4 AccentDark      = ImVec4(0.435f, 0.498f, 0.580f, 1.00f);  // #6f7f94 - Deep mist
        const ImVec4 AccentDarker    = ImVec4(0.333f, 0.384f, 0.451f, 1.00f);  // #556273 - Storm cloud
        const ImVec4 AccentLight     = ImVec4(0.682f, 0.749f, 0.835f, 1.00f);  // #aebfd5 - Bright morning mist
        const ImVec4 AccentVeryLight = ImVec4(0.682f, 0.749f, 0.835f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.118f, 0.165f, 0.224f, 1.00f); // #1e2a39

        // Text - Pale winter sun (slightly blue-tinted white)
        const ImVec4 TextBright  = ImVec4(0.929f, 0.945f, 0.973f, 1.00f);  // #edf1f8 - Pale winter sun
        const ImVec4 TextMuted   = ImVec4(0.682f, 0.718f, 0.765f, 1.00f);  // #aeb7c3 - Morning haze
        const ImVec4 TextDim     = ImVec4(0.435f, 0.471f, 0.518f, 1.00f);  // #6f7884 - Distant fog
        const ImVec4 TextWhite   = ImVec4(0.949f, 0.961f, 0.980f, 1.00f);  // #f2f5fa - Pure morning light

        // Borders - Icy silver-blue
        const ImVec4 BorderSubtle      = ImVec4(0.235f, 0.306f, 0.392f, 1.00f); // #3c4e64 - Hoarfrost border
        const ImVec4 BorderWindow      = ImVec4(0.333f, 0.408f, 0.502f, 1.00f); // #556880 - Icy stone border
        const ImVec4 BorderTitle       = ImVec4(0.545f, 0.620f, 0.722f, 1.00f); // #8b9eb8 - Morning mist border
        const ImVec4 BorderTitleBottom = ImVec4(0.333f, 0.384f, 0.451f, 1.00f); // #556273 - Storm cloud bottom

        // Player Bar & Window Surround - Deepest winter pre-dawn
        const ImVec4 PlayerBarBg    = ImVec4(0.027f, 0.039f, 0.067f, 1.00f);  // #070a11
        const ImVec4 WindowSurround = ImVec4(0.020f, 0.031f, 0.051f, 1.00f);  // #05080d

        //==========================================================================
        // Title Bar - Pre-dawn sky
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.012f, 0.020f, 0.035f, 1.00f); // #030509
        t.TitleBar.BackgroundColorActive   = ImVec4(0.012f, 0.020f, 0.035f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.012f, 0.020f, 0.035f, 0.85f);
        t.TitleBar.BackgroundOpacity       = 1.0f;

        t.TitleBar.ShowBottomBorder        = true;
        t.TitleBar.BottomBorderColor       = BorderTitleBottom;
        t.TitleBar.ShowWindowBorder        = true;
        t.TitleBar.WindowBorderColor       = BorderTitle;
        t.TitleBar.ShowAccentLine          = true;
        t.TitleBar.AccentLineColor         = Accent;
        t.TitleBar.TitleTextColor          = TextBright;
        t.TitleBar.TitleTextColorInactive  = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive           = Accent;
        t.ContentPanel.TabInactive         = DawnShadow;
        t.ContentPanel.TabHovered          = MorningStone;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = NightSky;  // Dark text on mist tab
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = Hoarfrost;
        t.ContentPanel.ButtonHovered       = IcyStone;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Frozen morning light
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = DawnShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = DawnShadow;
        t.Window.TitleBarActive    = MorningStone;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = Hoarfrost;
        t.Window.ButtonHovered     = IcyStone;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = WinterGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Frozen lake surface
        //==========================================================================

        t.TrackTable.HeaderBackground     = Hoarfrost;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = PaleSky;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = NightSky;
        t.TrackTable.RowDefaultAlt        = DawnShadow;
        t.TrackTable.RowHovered           = WinterVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = Hoarfrost;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = NightSky;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = FrozenLake;
        t.TrackTable.ScrollbarGrab        = Hoarfrost;
        t.TrackTable.ScrollbarGrabHovered = IcyStone;
        t.TrackTable.ScrollbarGrabActive  = Accent;
        t.TrackTable.ScrollbarWidth       = 8.0f;
        t.TrackTable.ScrollbarRounding    = 4.0f;

        t.TrackTable.HoverFadeSpeed       = 0.15f;
        t.TrackTable.SelectionFadeSpeed   = 0.20f;
        t.TrackTable.ScrollSmoothing      = 0.12f;
        t.TrackTable.TableRounding        = 0.0f;
        t.TrackTable.MinColumnWidth       = 30.0f;

        t.TrackTable.TitleWidth           = 350.0f;
        t.TrackTable.ArtistWidth          = 180.0f;
        t.TrackTable.AlbumWidth           = 180.0f;
        t.TrackTable.ExtensionWidth       = 50.0f;
        t.TrackTable.DurationWidth        = 80.0f;

        //==========================================================================
        // Visualizer - Morning light through ice
        //==========================================================================

        t.Visualizer.BackgroundColor       = FrozenLake;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.08f);
        t.Visualizer.GridColor             = ImVec4(Hoarfrost.x, Hoarfrost.y, Hoarfrost.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: hoarfrost → icy stone → morning mist → pale sun ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = Hoarfrost;
        t.Visualizer.SpectrumColorMid      = IcyStone;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.929f, 0.945f, 0.973f, 1.00f); // #edf1f8 - Winter sun peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = Hoarfrost;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.15f;

        //==========================================================================
        // Album Art - Frosted frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = DawnShadow;
        t.AlbumArtBox.BackgroundColorHovered  = MorningStone;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.18f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        //==========================================================================
        // Lightbox - Winter dawn
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.012f, 0.020f, 0.035f, 0.95f);
        t.AlbumArtLightbox.BorderColor        = BorderTitle;
        t.AlbumArtLightbox.CloseButtonColor   = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Accent;
        t.AlbumArtLightbox.TitleColor         = TextBright;
        t.AlbumArtLightbox.ArtistColor        = TextMuted;
        t.AlbumArtLightbox.MaxWidth           = 400.0f;
        t.AlbumArtLightbox.MaxHeight          = 400.0f;
        t.AlbumArtLightbox.BorderRounding     = 4.0f;
        t.AlbumArtLightbox.BorderThickness    = 1.0f;
        t.AlbumArtLightbox.CloseButtonSize    = 24.0f;
        t.AlbumArtLightbox.Padding            = 30.0f;
        t.AlbumArtLightbox.TitleSpacing       = 12.0f;
        t.AlbumArtLightbox.ArtistSpacing      = 8.0f;

        //==========================================================================
        // Search Bar - Frosted glass
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = MorningStone;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = DawnShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Frozen ground
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = Hoarfrost;
        t.PlayerBar.ButtonHovered             = IcyStone;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = Hoarfrost;
        t.PlayerBar.ButtonPrimaryHovered      = IcyStone;
        t.PlayerBar.ButtonPrimaryActive       = AccentDark;
        t.PlayerBar.SliderTrack               = BorderWindow;
        t.PlayerBar.SliderGrab                = Accent;
        t.PlayerBar.SliderGrabActive          = AccentLight;

        t.PlayerBar.UsePlayerBarGradient      = true;
        t.PlayerBar.PlayerBarGradientTop      = PlayerBarBg;
        t.PlayerBar.PlayerBarGradientBottom   = PlayerBarBg;
        t.PlayerBar.PlayerBarOpacity          = 1.0f;

        t.PlayerBar.Lightbox                  = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox               = t.AlbumArtBox;
        t.PlayerBar.Visualizer                = t.Visualizer;

        //==========================================================================
        // Popup Menu - Frosted chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = NightSky;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic