//==============================================================================
// GlacierFrostTheme.h
//==============================================================================
// Glacier frost - icy blue, frozen crystal, arctic light
// Palette: #00A9FF (glacial ice), #89CFF3 (frozen sky), #A0E9FF (ice crystal),
//          #CDF5FD (arctic mist)
// 60% Darkened glacial depths (#003D5C → #005C80)
// 25% Frozen sky and ice crystal surfaces (#89CFF3, #A0E9FF)
// 10% Glacial ice accent (#00A9FF)
// 5% Arctic mist text (#CDF5FD)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateGlacierFrostTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Glacier frost, arctic and crystalline
        //==========================================================================

        // 60% - Darkened glacial depths
        const ImVec4 GlacialDeep    = ImVec4(0.000f, 0.239f, 0.361f, 1.00f);  // #003D5C - Glacial depths
        const ImVec4 DeepIce        = ImVec4(0.000f, 0.361f, 0.502f, 1.00f);  // #005C80 - Deep ice
        const ImVec4 IceShadow      = ImVec4(0.000f, 0.435f, 0.584f, 1.00f);  // #006F95 - Ice shadow (library bg)
        const ImVec4 FrozenDepths   = ImVec4(0.000f, 0.510f, 0.667f, 1.00f);  // #0082AA - Frozen depths
        const ImVec4 GlacialWall    = ImVec4(0.000f, 0.584f, 0.749f, 1.00f);  // #0095BF - Glacial wall

        const ImVec4 GlacierGlow       = ImVec4(0.000f, 0.663f, 1.000f, 0.15f); // Glacial ice glow
        const ImVec4 GlacierVeryLight  = ImVec4(0.000f, 0.663f, 1.000f, 0.40f);
        const ImVec4 GlacierSubtle     = ImVec4(0.000f, 0.663f, 1.000f, 0.08f);

        // 25% - Frozen sky and ice crystal surfaces
        const ImVec4 FrozenSky      = ImVec4(0.537f, 0.812f, 0.953f, 1.00f);  // #89CFF3 - Frozen sky
        const ImVec4 IceCrystal     = ImVec4(0.627f, 0.914f, 1.000f, 1.00f);  // #A0E9FF - Ice crystal
        const ImVec4 ArcticMist     = ImVec4(0.804f, 0.961f, 0.992f, 1.00f);  // #CDF5FD - Arctic mist

        // 10% - Glacial ice accent
        const ImVec4 Accent          = ImVec4(0.000f, 0.663f, 1.000f, 1.00f);  // #00A9FF - Glacial ice
        const ImVec4 AccentDark      = ImVec4(0.000f, 0.510f, 0.784f, 1.00f);  // #0082C8 - Dark ice
        const ImVec4 AccentDarker    = ImVec4(0.000f, 0.361f, 0.561f, 1.00f);  // #005C8F - Deep ice
        const ImVec4 AccentLight     = ImVec4(0.627f, 0.914f, 1.000f, 1.00f);  // #A0E9FF - Ice crystal
        const ImVec4 AccentVeryLight = ImVec4(0.627f, 0.914f, 1.000f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.000f, 0.400f, 0.541f, 1.00f); // #00668A

        // Text - Arctic mist and pale ice
        const ImVec4 TextBright  = ImVec4(0.804f, 0.961f, 0.992f, 1.00f);  // #CDF5FD - Arctic mist
        const ImVec4 TextMuted   = ImVec4(0.627f, 0.831f, 0.902f, 1.00f);  // #A0D4E6 - Pale ice
        const ImVec4 TextDim     = ImVec4(0.424f, 0.604f, 0.710f, 1.00f);  // #6C9AB5 - Deep frost
        const ImVec4 TextWhite   = ImVec4(0.878f, 0.976f, 0.996f, 1.00f);  // #E0F9FE - Pure arctic light

        // Borders - Ice-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.000f, 0.510f, 0.667f, 1.00f); // #0082AA - Ice border
        const ImVec4 BorderWindow      = ImVec4(0.000f, 0.361f, 0.561f, 1.00f); // #005C8F - Deep ice border
        const ImVec4 BorderTitle       = ImVec4(0.000f, 0.663f, 1.000f, 1.00f); // #00A9FF - Glacial border
        const ImVec4 BorderTitleBottom = ImVec4(0.000f, 0.239f, 0.361f, 1.00f); // #003D5C - Deepest ice bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.000f, 0.169f, 0.259f, 1.00f);  // #002B42
        const ImVec4 WindowSurround = ImVec4(0.000f, 0.133f, 0.204f, 1.00f);  // #002234

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.000f, 0.098f, 0.149f, 1.00f); // #001926
        t.TitleBar.BackgroundColorActive   = ImVec4(0.000f, 0.098f, 0.149f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.098f, 0.149f, 0.85f);
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
        t.ContentPanel.TabInactive         = IceShadow;
        t.ContentPanel.TabHovered          = FrozenDepths;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = FrozenSky;
        t.ContentPanel.ButtonHovered       = IceCrystal;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = IceShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = IceShadow;
        t.Window.TitleBarActive    = FrozenDepths;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = FrozenSky;
        t.Window.ButtonHovered     = IceCrystal;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = GlacierGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = FrozenSky;
        t.TrackTable.HeaderTextColor      = GlacialDeep;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = GlacialWall;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = GlacialDeep;
        t.TrackTable.HeaderTextArtist     = GlacialDeep;
        t.TrackTable.HeaderTextAlbum      = GlacialDeep;
        t.TrackTable.HeaderTextExtension  = GlacialDeep;
        t.TrackTable.HeaderTextDuration   = GlacialDeep;

        t.TrackTable.RowDefault           = GlacialDeep;
        t.TrackTable.RowDefaultAlt        = IceShadow;
        t.TrackTable.RowHovered           = GlacierVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = FrozenSky;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = GlacialDeep;
        t.TrackTable.TextPlaying          = TextWhite;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = DeepIce;
        t.TrackTable.ScrollbarGrab        = FrozenSky;
        t.TrackTable.ScrollbarGrabHovered = IceCrystal;
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
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor       = DeepIce;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(FrozenSky.x, FrozenSky.y, FrozenSky.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = FrozenSky;
        t.Visualizer.SpectrumColorMid      = IceCrystal;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.804f, 0.961f, 0.992f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = FrozenSky;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.40f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = IceShadow;
        t.AlbumArtBox.BackgroundColorHovered  = FrozenDepths;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.20f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.000f, 0.098f, 0.149f, 0.95f);
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

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = FrozenDepths;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = IceShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = FrozenSky;
        t.PlayerBar.ButtonHovered             = IceCrystal;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = FrozenSky;
        t.PlayerBar.ButtonPrimaryHovered      = IceCrystal;
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
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = GlacialDeep;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic