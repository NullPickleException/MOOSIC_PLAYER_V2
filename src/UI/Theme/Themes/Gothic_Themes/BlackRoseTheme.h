//==============================================================================
// BlackRoseTheme.h
//==============================================================================
// Dark romance - midnight blue velvet with bleeding crimson rose
// Palette: #111F35 (midnight velvet), #8A244B (dried rose), #D02752 (bleeding crimson),
//          #F63049 (fresh blood rose)
// 55% Midnight blue-black (#111F35 → #1a2a45)
// 25% Dried rose and bleeding crimson surfaces (#8A244B, #D02752)
// 10% Fresh blood rose accent (#F63049)
// 10% Pale rose text
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateBlackRoseTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Midnight velvet with bleeding rose
        //==========================================================================

        // 55% - Midnight blue-black velvet
        const ImVec4 MidnightVelvet  = ImVec4(0.067f, 0.122f, 0.208f, 1.00f);  // #111F35 - Midnight velvet
        const ImVec4 VelvetShadow   = ImVec4(0.102f, 0.165f, 0.271f, 1.00f);  // #1a2a45 - Velvet in shadow (library bg)
        const ImVec4 VelvetFold     = ImVec4(0.137f, 0.208f, 0.322f, 1.00f);  // #233552 - Folded velvet
        const ImVec4 VelvetLight    = ImVec4(0.173f, 0.251f, 0.373f, 1.00f);  // #2c405f - Velvet catching light
        const ImVec4 VelvetSurface  = ImVec4(0.208f, 0.294f, 0.424f, 1.00f);  // #354b6c - Velvet surface

        const ImVec4 RoseGlow       = ImVec4(0.965f, 0.188f, 0.286f, 0.20f); // Fresh blood rose glow
        const ImVec4 RoseVeryLight  = ImVec4(0.965f, 0.188f, 0.286f, 0.50f);
        const ImVec4 RoseSubtle     = ImVec4(0.965f, 0.188f, 0.286f, 0.10f);

        // 25% - Dried rose and bleeding crimson surfaces
        const ImVec4 DriedRose      = ImVec4(0.541f, 0.141f, 0.294f, 1.00f);  // #8A244B - Dried rose
        const ImVec4 BleedingRose   = ImVec4(0.816f, 0.153f, 0.322f, 1.00f);  // #D02752 - Bleeding crimson
        const ImVec4 CrimsonBloom   = ImVec4(0.886f, 0.173f, 0.353f, 1.00f);  // #e22c5a - Crimson bloom

        // 10% - Fresh blood rose accent
        const ImVec4 Accent          = ImVec4(0.965f, 0.188f, 0.286f, 1.00f);  // #F63049 - Fresh blood rose
        const ImVec4 AccentDark      = ImVec4(0.816f, 0.153f, 0.322f, 1.00f);  // #D02752 - Bleeding crimson
        const ImVec4 AccentDarker    = ImVec4(0.541f, 0.141f, 0.294f, 1.00f);  // #8A244B - Dried rose
        const ImVec4 AccentLight     = ImVec4(0.976f, 0.302f, 0.396f, 1.00f);  // #f94d65 - Bright rose bloom
        const ImVec4 AccentVeryLight = ImVec4(0.976f, 0.302f, 0.396f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.086f, 0.141f, 0.231f, 1.00f); // #16243b

        // Text - Pale rose-tinted parchment on midnight velvet
        const ImVec4 TextBright  = ImVec4(0.965f, 0.945f, 0.957f, 1.00f);  // #f6f1f4 - Pale rose petal
        const ImVec4 TextMuted   = ImVec4(0.784f, 0.706f, 0.749f, 1.00f);  // #c8b4bf - Faded rose
        const ImVec4 TextDim     = ImVec4(0.490f, 0.416f, 0.455f, 1.00f);  // #7d6a74 - Dried petal
        const ImVec4 TextWhite   = ImVec4(0.980f, 0.969f, 0.976f, 1.00f);  // #faf7f9 - Pure white rose

        // Borders - Crimson-tinted midnight
        const ImVec4 BorderSubtle      = ImVec4(0.173f, 0.208f, 0.322f, 1.00f); // #2c3552 - Midnight blue border
        const ImVec4 BorderWindow      = ImVec4(0.541f, 0.141f, 0.294f, 1.00f); // #8A244B - Dried rose border
        const ImVec4 BorderTitle       = ImVec4(0.816f, 0.153f, 0.322f, 1.00f); // #D02752 - Bleeding crimson border
        const ImVec4 BorderTitleBottom = ImVec4(0.369f, 0.098f, 0.208f, 1.00f); // #5e1935 - Deepest rose bottom

        // Player Bar & Window Surround - Deepest midnight
        const ImVec4 PlayerBarBg    = ImVec4(0.047f, 0.086f, 0.149f, 1.00f);  // #0c1626
        const ImVec4 WindowSurround = ImVec4(0.035f, 0.067f, 0.114f, 1.00f);  // #09111d

        //==========================================================================
        // Title Bar - Midnight crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.027f, 0.051f, 0.090f, 1.00f); // #070d17
        t.TitleBar.BackgroundColorActive   = ImVec4(0.027f, 0.051f, 0.090f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.027f, 0.051f, 0.090f, 0.85f);
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
        t.ContentPanel.TabInactive         = VelvetShadow;
        t.ContentPanel.TabHovered          = VelvetFold;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = DriedRose;
        t.ContentPanel.ButtonHovered       = BleedingRose;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Midnight velvet frame
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = VelvetShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = VelvetShadow;
        t.Window.TitleBarActive    = VelvetFold;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = DriedRose;
        t.Window.ButtonHovered     = BleedingRose;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = RoseGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Velvet-lined shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = DriedRose;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = VelvetSurface;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = MidnightVelvet;
        t.TrackTable.RowDefaultAlt        = VelvetShadow;
        t.TrackTable.RowHovered           = RoseVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = DriedRose;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
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

        t.TrackTable.ScrollbarBg          = MidnightVelvet;
        t.TrackTable.ScrollbarGrab        = DriedRose;
        t.TrackTable.ScrollbarGrabHovered = BleedingRose;
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
        // Visualizer - Bleeding rose energy
        //==========================================================================

        t.Visualizer.BackgroundColor       = MidnightVelvet;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(DriedRose.x, DriedRose.y, DriedRose.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: dried rose → bleeding crimson → fresh blood → bright bloom ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = DriedRose;
        t.Visualizer.SpectrumColorMid      = BleedingRose;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.988f, 0.455f, 0.537f, 1.00f); // #fc7489 - Rose petal peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = DriedRose;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Rose-thorned frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = VelvetShadow;
        t.AlbumArtBox.BackgroundColorHovered  = VelvetFold;
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
        // Lightbox - Velvet chamber
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.027f, 0.051f, 0.090f, 0.95f);
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
        // Search Bar - Rose-scented grimoire
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = VelvetFold;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = VelvetShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Velvet-lined floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = DriedRose;
        t.PlayerBar.ButtonHovered             = BleedingRose;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = DriedRose;
        t.PlayerBar.ButtonPrimaryHovered      = BleedingRose;
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
        // Popup Menu - Rose chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = TextWhite;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic