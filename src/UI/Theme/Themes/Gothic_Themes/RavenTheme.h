//==============================================================================
// RavenTheme.h
//==============================================================================
// Raven feathers - midnight blue intelligence with violet iridescence
// Palette: #0C134F (midnight feather), #1D267D (deep indigo), #5C469C (violet sheen),
//          #D4ADFC (pale lavender light)
// 55% Midnight blue-black (#0C134F → #1D267D)
// 25% Deep indigo and violet surfaces (#1D267D, #5C469C)
// 10% Violet sheen accent (#5C469C)
// 10% Pale lavender text (#D4ADFC)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateRavenTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Raven feathers with violet iridescence
        //==========================================================================

        // 55% - Midnight blue-black
        const ImVec4 MidnightFeather = ImVec4(0.047f, 0.075f, 0.310f, 1.00f);  // #0C134F - Midnight feather
        const ImVec4 DeepIndigo      = ImVec4(0.114f, 0.149f, 0.490f, 1.00f);  // #1D267D - Deep indigo
        const ImVec4 IndigoShadow    = ImVec4(0.149f, 0.188f, 0.553f, 1.00f);  // #26308D - Indigo shadow (library bg)
        const ImVec4 WingFold        = ImVec4(0.188f, 0.231f, 0.608f, 1.00f);  // #303B9B - Folded wing
        const ImVec4 FeatherSheen    = ImVec4(0.227f, 0.275f, 0.612f, 1.00f);  // #3A469C - Feather sheen

        const ImVec4 RavenGlow       = ImVec4(0.361f, 0.275f, 0.612f, 0.20f); // Violet iridescence glow
        const ImVec4 RavenVeryLight  = ImVec4(0.361f, 0.275f, 0.612f, 0.50f);
        const ImVec4 RavenSubtle     = ImVec4(0.361f, 0.275f, 0.612f, 0.10f);

        // 25% - Deep indigo and violet surfaces
        const ImVec4 IndigoDark     = ImVec4(0.114f, 0.149f, 0.490f, 1.00f);  // #1D267D - Deep indigo
        const ImVec4 VioletSheen    = ImVec4(0.361f, 0.275f, 0.612f, 1.00f);  // #5C469C - Violet sheen
        const ImVec4 BrightViolet   = ImVec4(0.455f, 0.349f, 0.706f, 1.00f);  // #7459B4 - Bright violet

        // 10% - Violet sheen accent
        const ImVec4 Accent          = ImVec4(0.361f, 0.275f, 0.612f, 1.00f);  // #5C469C - Violet sheen
        const ImVec4 AccentDark      = ImVec4(0.227f, 0.188f, 0.490f, 1.00f);  // #3A307D - Dark violet
        const ImVec4 AccentDarker    = ImVec4(0.149f, 0.122f, 0.380f, 1.00f);  // #261F61 - Deepest violet
        const ImVec4 AccentLight     = ImVec4(0.831f, 0.678f, 0.988f, 1.00f);  // #D4ADFC - Pale lavender
        const ImVec4 AccentVeryLight = ImVec4(0.831f, 0.678f, 0.988f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.129f, 0.165f, 0.522f, 1.00f); // #212A85

        // Text - Pale lavender moonlight
        const ImVec4 TextBright  = ImVec4(0.831f, 0.678f, 0.988f, 1.00f);  // #D4ADFC - Pale lavender
        const ImVec4 TextMuted   = ImVec4(0.627f, 0.510f, 0.780f, 1.00f);  // #A082C7 - Muted violet
        const ImVec4 TextDim     = ImVec4(0.400f, 0.325f, 0.541f, 1.00f);  // #66538A - Dimmed purple
        const ImVec4 TextWhite   = ImVec4(0.902f, 0.788f, 0.996f, 1.00f);  // #E6C9FE - Pure moonlight

        // Borders - Violet-tinted midnight
        const ImVec4 BorderSubtle      = ImVec4(0.188f, 0.231f, 0.608f, 1.00f); // #303B9B - Indigo border
        const ImVec4 BorderWindow      = ImVec4(0.227f, 0.188f, 0.490f, 1.00f); // #3A307D - Dark violet border
        const ImVec4 BorderTitle       = ImVec4(0.361f, 0.275f, 0.612f, 1.00f); // #5C469C - Violet title border
        const ImVec4 BorderTitleBottom = ImVec4(0.149f, 0.122f, 0.380f, 1.00f); // #261F61 - Deep violet bottom

        // Player Bar & Window Surround - Deepest raven's nest
        const ImVec4 PlayerBarBg    = ImVec4(0.035f, 0.055f, 0.231f, 1.00f);  // #090E3B
        const ImVec4 WindowSurround = ImVec4(0.027f, 0.043f, 0.184f, 1.00f);  // #070B2F

        //==========================================================================
        // Title Bar - Raven's crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.020f, 0.031f, 0.133f, 1.00f); // #050822
        t.TitleBar.BackgroundColorActive   = ImVec4(0.020f, 0.031f, 0.133f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.020f, 0.031f, 0.133f, 0.85f);
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
        t.ContentPanel.TabInactive         = IndigoShadow;
        t.ContentPanel.TabHovered          = WingFold;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = IndigoDark;
        t.ContentPanel.ButtonHovered       = VioletSheen;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Violet-tinged raven's wing
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = IndigoShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = IndigoShadow;
        t.Window.TitleBarActive    = WingFold;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = IndigoDark;
        t.Window.ButtonHovered     = VioletSheen;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = RavenGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Feathered shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = IndigoDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = FeatherSheen;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = MidnightFeather;
        t.TrackTable.RowDefaultAlt        = IndigoShadow;
        t.TrackTable.RowHovered           = RavenVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = IndigoDark;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = MidnightFeather;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = MidnightFeather;
        t.TrackTable.ScrollbarGrab        = IndigoDark;
        t.TrackTable.ScrollbarGrabHovered = VioletSheen;
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
        // Visualizer - Violet iridescence on raven feathers
        //==========================================================================

        t.Visualizer.BackgroundColor       = MidnightFeather;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(IndigoDark.x, IndigoDark.y, IndigoDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: deep indigo → violet sheen → bright violet → pale lavender ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = IndigoDark;
        t.Visualizer.SpectrumColorMid      = VioletSheen;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.831f, 0.678f, 0.988f, 1.00f); // #D4ADFC - Lavender peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = IndigoDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Violet-tinged frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = IndigoShadow;
        t.AlbumArtBox.BackgroundColorHovered  = WingFold;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Raven's roost
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.020f, 0.031f, 0.133f, 0.95f);
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
        // Search Bar - Feathered pages
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = WingFold;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = IndigoShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Raven's perch
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = IndigoDark;
        t.PlayerBar.ButtonHovered             = VioletSheen;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = IndigoDark;
        t.PlayerBar.ButtonPrimaryHovered      = VioletSheen;
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
        // Popup Menu - Raven's counsel
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = MidnightFeather;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic