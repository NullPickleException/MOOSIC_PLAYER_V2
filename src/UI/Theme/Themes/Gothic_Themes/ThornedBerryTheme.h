//==============================================================================
// ThornedBerryTheme.h
//==============================================================================
// Thorned berry - romantic, sharp, storybook gothic
// Palette: #0f0407 (blackberry thorn), #3a0f1c (dark berry), #6b1e33 (crushed berry),
//          #a93a55 (wild rose), #f3c9d3 (pale blossom)
// 55% Blackberry thorn and dark berry (#0f0407 → #3a0f1c)
// 25% Crushed berry and wild rose surfaces (#6b1e33, #a93a55)
// 10% Wild rose accent (#a93a55)
// 10% Pale blossom text (#f3c9d3)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateThornedBerryTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Thorned berry, sharp and romantic
        //==========================================================================

        // 55% - Blackberry thorn and dark berry
        const ImVec4 BlackberryThorn = ImVec4(0.059f, 0.016f, 0.027f, 1.00f);  // #0f0407 - Blackberry thorn
        const ImVec4 DarkBerry       = ImVec4(0.227f, 0.059f, 0.110f, 1.00f);  // #3a0f1c - Dark berry
        const ImVec4 BerryShadow     = ImVec4(0.290f, 0.078f, 0.141f, 1.00f);  // #4a1424 - Berry in shadow (library bg)
        const ImVec4 ThornStem       = ImVec4(0.353f, 0.098f, 0.173f, 1.00f);  // #5a192c - Thorn stem
        const ImVec4 BerryBush       = ImVec4(0.420f, 0.118f, 0.200f, 1.00f);  // #6b1e33 - Berry bush

        const ImVec4 BerryGlow       = ImVec4(0.663f, 0.227f, 0.333f, 0.20f); // Wild rose glow
        const ImVec4 BerryVeryLight  = ImVec4(0.663f, 0.227f, 0.333f, 0.50f);
        const ImVec4 BerrySubtle     = ImVec4(0.663f, 0.227f, 0.333f, 0.10f);

        // 25% - Crushed berry and wild rose surfaces
        const ImVec4 CrushedBerry   = ImVec4(0.420f, 0.118f, 0.200f, 1.00f);  // #6b1e33 - Crushed berry
        const ImVec4 WildRose       = ImVec4(0.663f, 0.227f, 0.333f, 1.00f);  // #a93a55 - Wild rose
        const ImVec4 RoseThorn      = ImVec4(0.749f, 0.294f, 0.404f, 1.00f);  // #bf4b67 - Rose thorn

        // 10% - Wild rose accent
        const ImVec4 Accent          = ImVec4(0.663f, 0.227f, 0.333f, 1.00f);  // #a93a55 - Wild rose
        const ImVec4 AccentDark      = ImVec4(0.420f, 0.118f, 0.200f, 1.00f);  // #6b1e33 - Crushed berry
        const ImVec4 AccentDarker    = ImVec4(0.290f, 0.078f, 0.141f, 1.00f);  // #4a1424 - Dark berry
        const ImVec4 AccentLight     = ImVec4(0.749f, 0.294f, 0.404f, 1.00f);  // #bf4b67 - Rose thorn
        const ImVec4 AccentVeryLight = ImVec4(0.749f, 0.294f, 0.404f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.259f, 0.067f, 0.122f, 1.00f); // #42111f

        // Text - Pale blossom petals
        const ImVec4 TextBright  = ImVec4(0.953f, 0.788f, 0.827f, 1.00f);  // #f3c9d3 - Pale blossom
        const ImVec4 TextMuted   = ImVec4(0.729f, 0.580f, 0.627f, 1.00f);  // #ba94a0 - Faded blossom
        const ImVec4 TextDim     = ImVec4(0.471f, 0.357f, 0.396f, 1.00f);  // #785b65 - Dried petal
        const ImVec4 TextWhite   = ImVec4(0.969f, 0.851f, 0.878f, 1.00f);  // #f7d9e0 - Pure blossom white

        // Borders - Berry-tinted thorns
        const ImVec4 BorderSubtle      = ImVec4(0.353f, 0.098f, 0.173f, 1.00f); // #5a192c - Thorn stem border
        const ImVec4 BorderWindow      = ImVec4(0.420f, 0.118f, 0.200f, 1.00f); // #6b1e33 - Crushed berry border
        const ImVec4 BorderTitle       = ImVec4(0.663f, 0.227f, 0.333f, 1.00f); // #a93a55 - Wild rose border
        const ImVec4 BorderTitleBottom = ImVec4(0.290f, 0.078f, 0.141f, 1.00f); // #4a1424 - Dark berry bottom

        // Player Bar & Window Surround - Deepest thorn thicket
        const ImVec4 PlayerBarBg    = ImVec4(0.043f, 0.012f, 0.020f, 1.00f);  // #0b0305
        const ImVec4 WindowSurround = ImVec4(0.031f, 0.008f, 0.016f, 1.00f);  // #080204

        //==========================================================================
        // Title Bar - Thorned crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.024f, 0.004f, 0.008f, 1.00f); // #060102
        t.TitleBar.BackgroundColorActive   = ImVec4(0.024f, 0.004f, 0.008f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.024f, 0.004f, 0.008f, 0.85f);
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
        t.ContentPanel.TabInactive         = BerryShadow;
        t.ContentPanel.TabHovered          = ThornStem;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = CrushedBerry;
        t.ContentPanel.ButtonHovered       = WildRose;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Thorn thicket frame
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = BerryShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = BerryShadow;
        t.Window.TitleBarActive    = ThornStem;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = CrushedBerry;
        t.Window.ButtonHovered     = WildRose;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = BerryGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Berry-laden shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = CrushedBerry;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = BerryBush;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = BlackberryThorn;
        t.TrackTable.RowDefaultAlt        = BerryShadow;
        t.TrackTable.RowHovered           = BerryVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = CrushedBerry;
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

        t.TrackTable.ScrollbarBg          = DarkBerry;
        t.TrackTable.ScrollbarGrab        = CrushedBerry;
        t.TrackTable.ScrollbarGrabHovered = WildRose;
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
        // Visualizer - Crushed berry pulse
        //==========================================================================

        t.Visualizer.BackgroundColor       = DarkBerry;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(CrushedBerry.x, CrushedBerry.y, CrushedBerry.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: dark berry → crushed berry → wild rose → pale blossom ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = CrushedBerry;
        t.Visualizer.SpectrumColorMid      = WildRose;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.953f, 0.788f, 0.827f, 1.00f); // #f3c9d3 - Blossom peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = CrushedBerry;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Thorned frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = BerryShadow;
        t.AlbumArtBox.BackgroundColorHovered  = ThornStem;
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
        // Lightbox - Berry thicket
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.024f, 0.004f, 0.008f, 0.95f);
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
        // Search Bar - Berry-stained pages
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = ThornStem;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = BerryShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Thorny ground
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = CrushedBerry;
        t.PlayerBar.ButtonHovered             = WildRose;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = CrushedBerry;
        t.PlayerBar.ButtonPrimaryHovered      = WildRose;
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
        // Popup Menu - Berry bramble
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