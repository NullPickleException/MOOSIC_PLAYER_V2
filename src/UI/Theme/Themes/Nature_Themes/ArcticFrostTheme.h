//==============================================================================
// ArcticFrostTheme.h
//==============================================================================
// Arctic frost - crisp frozen whites, pale ice blues, and crystalline light
// Palette: #00A9FF (glacial ice), #89CFF3 (frozen sky), #A0E9FF (ice crystal),
//          #CDF5FD (arctic mist)
// 60% Bright arctic sky and ice crystal surfaces (#89CFF3 → #A0E9FF)
// 25% Glacial ice and crystalline highlights (#00A9FF, #CDF5FD)
// 10% Deep ice accent (#0082C8)
// 5% Pure snow text (#FFFFFF)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateArcticFrostTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Arctic frost, bright and crystalline
        //==========================================================================

        // 60% - Bright arctic sky and ice crystal surfaces (light theme base)
        const ImVec4 ArcticSky      = ImVec4(0.537f, 0.812f, 0.953f, 1.00f);  // #89CFF3 - Frozen sky
        const ImVec4 IceCrystal     = ImVec4(0.627f, 0.914f, 1.000f, 1.00f);  // #A0E9FF - Ice crystal
        const ImVec4 FrostSurface   = ImVec4(0.725f, 0.941f, 1.000f, 1.00f);  // #B9F0FF - Frost surface (library bg)
        const ImVec4 GlacialMist    = ImVec4(0.804f, 0.961f, 0.992f, 1.00f);  // #CDF5FD - Arctic mist
        const ImVec4 SnowDrift      = ImVec4(0.878f, 0.980f, 0.996f, 1.00f);  // #E0FAFE - Snow drift

        const ImVec4 FrostGlow       = ImVec4(0.000f, 0.663f, 1.000f, 0.12f); // Glacial ice glow
        const ImVec4 FrostVeryLight  = ImVec4(0.000f, 0.663f, 1.000f, 0.40f);
        const ImVec4 FrostSubtle     = ImVec4(0.000f, 0.663f, 1.000f, 0.08f);

        // 25% - Glacial ice and crystalline highlights
        const ImVec4 GlacialIce     = ImVec4(0.000f, 0.663f, 1.000f, 1.00f);  // #00A9FF - Glacial ice
        const ImVec4 DeepIce        = ImVec4(0.000f, 0.510f, 0.784f, 1.00f);  // #0082C8 - Deep ice
        const ImVec4 FrozenLake     = ImVec4(0.380f, 0.741f, 0.937f, 1.00f);  // #61BDEF - Frozen lake

        // 10% - Deep ice accent
        const ImVec4 Accent          = ImVec4(0.000f, 0.663f, 1.000f, 1.00f);  // #00A9FF - Glacial ice
        const ImVec4 AccentDark      = ImVec4(0.000f, 0.510f, 0.784f, 1.00f);  // #0082C8 - Deep ice
        const ImVec4 AccentDarker    = ImVec4(0.000f, 0.361f, 0.561f, 1.00f);  // #005C8F - Deepest ice
        const ImVec4 AccentLight     = ImVec4(0.627f, 0.914f, 1.000f, 1.00f);  // #A0E9FF - Ice crystal
        const ImVec4 AccentVeryLight = ImVec4(0.627f, 0.914f, 1.000f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.804f, 0.961f, 0.992f, 1.00f); // #CDF5FD

        // Text - Crisp snow and deep ice
        const ImVec4 TextBright  = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);  // #FFFFFF - Pure snow
        const ImVec4 TextMuted   = ImVec4(0.000f, 0.361f, 0.561f, 1.00f);  // #005C8F - Deep ice text
        const ImVec4 TextDim     = ImVec4(0.000f, 0.510f, 0.784f, 1.00f);  // #0082C8 - Ice text
        const ImVec4 TextWhite   = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);  // #FFFFFF - Pure snow

        // Borders - Ice blue tones
        const ImVec4 BorderSubtle      = ImVec4(0.537f, 0.812f, 0.953f, 1.00f); // #89CFF3 - Frozen sky border
        const ImVec4 BorderWindow      = ImVec4(0.000f, 0.663f, 1.000f, 1.00f); // #00A9FF - Glacial ice border
        const ImVec4 BorderTitle       = ImVec4(0.000f, 0.510f, 0.784f, 1.00f); // #0082C8 - Deep ice border
        const ImVec4 BorderTitleBottom = ImVec4(0.000f, 0.361f, 0.561f, 1.00f); // #005C8F - Deepest ice bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.380f, 0.741f, 0.937f, 1.00f);  // #61BDEF
        const ImVec4 WindowSurround = ImVec4(0.537f, 0.812f, 0.953f, 1.00f);  // #89CFF3

        //==========================================================================
        // Title Bar - Deep crystalline ice
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.000f, 0.361f, 0.561f, 1.00f); // #005C8F
        t.TitleBar.BackgroundColorActive   = ImVec4(0.000f, 0.361f, 0.561f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.361f, 0.561f, 0.85f);
        t.TitleBar.BackgroundOpacity       = 1.0f;

        t.TitleBar.ShowBottomBorder        = true;
        t.TitleBar.BottomBorderColor       = BorderTitleBottom;
        t.TitleBar.ShowWindowBorder        = true;
        t.TitleBar.WindowBorderColor       = BorderTitle;
        t.TitleBar.ShowAccentLine          = true;
        t.TitleBar.AccentLineColor         = Accent;
        t.TitleBar.TitleTextColor          = TextBright;
        t.TitleBar.TitleTextColorInactive  = ImVec4(0.804f, 0.961f, 0.992f, 0.70f);

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive           = Accent;
        t.ContentPanel.TabInactive         = FrostSurface;
        t.ContentPanel.TabHovered          = IceCrystal;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = GlacialIce;
        t.ContentPanel.ButtonHovered       = FrozenLake;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Bright arctic
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = FrostSurface;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = FrostSurface;
        t.Window.TitleBarActive    = IceCrystal;
        t.Window.HeaderText        = TextMuted;
        t.Window.TextPrimary       = TextMuted;
        t.Window.TextSecondary     = TextDim;
        t.Window.TextDisabled      = ImVec4(0.537f, 0.812f, 0.953f, 0.50f);
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = GlacialIce;
        t.Window.ButtonHovered     = FrozenLake;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = FrostGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Crisp ice layers
        //==========================================================================

        t.TrackTable.HeaderBackground     = GlacialIce;
        t.TrackTable.HeaderTextColor      = TextWhite;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = FrozenLake;
        t.TrackTable.HeaderActive         = AccentDark;
        t.TrackTable.HeaderTextTitle      = TextWhite;
        t.TrackTable.HeaderTextArtist     = TextWhite;
        t.TrackTable.HeaderTextAlbum      = TextWhite;
        t.TrackTable.HeaderTextExtension  = TextWhite;
        t.TrackTable.HeaderTextDuration   = TextWhite;

        t.TrackTable.RowDefault           = ArcticSky;
        t.TrackTable.RowDefaultAlt        = FrostSurface;
        t.TrackTable.RowHovered           = FrostVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = GlacialIce;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextMuted;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = TextWhite;

        t.TrackTable.RowTextTitle         = TextMuted;
        t.TrackTable.RowTextArtist        = TextDim;
        t.TrackTable.RowTextAlbum         = TextDim;
        t.TrackTable.RowTextExtension     = ImVec4(0.537f, 0.812f, 0.953f, 0.70f);
        t.TrackTable.RowTextDuration      = TextDim;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = IceCrystal;
        t.TrackTable.ScrollbarGrab        = GlacialIce;
        t.TrackTable.ScrollbarGrabHovered = FrozenLake;
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
        // Visualizer - Northern lights
        //==========================================================================

        t.Visualizer.BackgroundColor       = IceCrystal;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.Visualizer.GridColor             = ImVec4(GlacialIce.x, GlacialIce.y, GlacialIce.z, 0.20f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = ArcticSky;
        t.Visualizer.SpectrumColorMid      = GlacialIce;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.804f, 0.961f, 0.992f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = ArcticSky;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.50f;
        t.Visualizer.BarBrightnessMax      = 1.30f;

        //==========================================================================
        // Album Art - Ice frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = FrostSurface;
        t.AlbumArtBox.BackgroundColorHovered  = IceCrystal;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.000f, 0.361f, 0.561f, 0.15f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.000f, 0.361f, 0.561f, 0.40f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.000f, 0.361f, 0.561f, 0.95f);
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
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.000f, 0.361f, 0.561f, 0.15f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextMuted;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = IceCrystal;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = FrostSurface;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextMuted;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Frozen depths
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextMuted;
        t.PlayerBar.TextSecondary             = TextDim;
        t.PlayerBar.ButtonNormal              = GlacialIce;
        t.PlayerBar.ButtonHovered             = FrozenLake;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = GlacialIce;
        t.PlayerBar.ButtonPrimaryHovered      = FrozenLake;
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
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextMuted;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = TextWhite;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.000f, 0.361f, 0.561f, 0.15f);

        return t;
    }

} // namespace moosic