//==============================================================================
// ForestTheme.h
//==============================================================================
// Deep forest - ancient trees, filtered sunlight, mossy earth
// Palette: #18230F (deep forest floor), #27391C (canopy shadow), #255F38 (emerald moss),
//          #1F7D53 (sunlit clearing)
// 60% Deep forest floor and canopy shadow (#18230F → #27391C)
// 25% Emerald moss and forest surfaces (#255F38, #3A7A4D)
// 10% Sunlit clearing accent (#1F7D53)
// 5% Pale green text
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateForestTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Deep forest, ancient and verdant
        //==========================================================================

        // 60% - Deep forest floor and canopy shadow
        const ImVec4 ForestFloor    = ImVec4(0.094f, 0.137f, 0.059f, 1.00f);  // #18230F - Deep forest floor
        const ImVec4 CanopyShadow   = ImVec4(0.153f, 0.224f, 0.110f, 1.00f);  // #27391C - Canopy shadow
        const ImVec4 Understory     = ImVec4(0.192f, 0.275f, 0.141f, 1.00f);  // #314624 - Understory (library bg)
        const ImVec4 MossyTrunk     = ImVec4(0.231f, 0.325f, 0.176f, 1.00f);  // #3B532D - Mossy trunk
        const ImVec4 FernGlade      = ImVec4(0.271f, 0.373f, 0.212f, 1.00f);  // #455F36 - Fern glade

        const ImVec4 ForestGlow       = ImVec4(0.122f, 0.490f, 0.325f, 0.15f); // Sunlit moss glow
        const ImVec4 ForestVeryLight  = ImVec4(0.122f, 0.490f, 0.325f, 0.45f);
        const ImVec4 ForestSubtle     = ImVec4(0.122f, 0.490f, 0.325f, 0.08f);

        // 25% - Emerald moss and forest surfaces
        const ImVec4 EmeraldMoss    = ImVec4(0.145f, 0.373f, 0.220f, 1.00f);  // #255F38 - Emerald moss
        const ImVec4 ForestGreen    = ImVec4(0.228f, 0.478f, 0.302f, 1.00f);  // #3A7A4D - Forest green
        const ImVec4 SunlitLeaf     = ImVec4(0.122f, 0.490f, 0.325f, 1.00f);  // #1F7D53 - Sunlit leaf

        // 10% - Sunlit clearing accent
        const ImVec4 Accent          = ImVec4(0.122f, 0.490f, 0.325f, 1.00f);  // #1F7D53 - Sunlit clearing
        const ImVec4 AccentDark      = ImVec4(0.145f, 0.373f, 0.220f, 1.00f);  // #255F38 - Emerald moss
        const ImVec4 AccentDarker    = ImVec4(0.106f, 0.275f, 0.161f, 1.00f);  // #1B4629 - Deep moss
        const ImVec4 AccentLight     = ImVec4(0.224f, 0.596f, 0.404f, 1.00f);  // #399867 - Bright leaf
        const ImVec4 AccentVeryLight = ImVec4(0.224f, 0.596f, 0.404f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.173f, 0.251f, 0.125f, 1.00f); // #2C4020

        // Text - Pale green sunlight through leaves
        const ImVec4 TextBright  = ImVec4(0.780f, 0.918f, 0.749f, 1.00f);  // #C7EABF - Sunlit leaf
        const ImVec4 TextMuted   = ImVec4(0.608f, 0.729f, 0.584f, 1.00f);  // #9BBA95 - Muted forest light
        const ImVec4 TextDim     = ImVec4(0.404f, 0.502f, 0.388f, 1.00f);  // #678063 - Deep shade
        const ImVec4 TextWhite   = ImVec4(0.847f, 0.949f, 0.824f, 1.00f);  // #D8F2D2 - Bright sunbeam

        // Borders - Moss-tinted bark
        const ImVec4 BorderSubtle      = ImVec4(0.231f, 0.325f, 0.176f, 1.00f); // #3B532D - Mossy bark border
        const ImVec4 BorderWindow      = ImVec4(0.145f, 0.373f, 0.220f, 1.00f); // #255F38 - Emerald moss border
        const ImVec4 BorderTitle       = ImVec4(0.122f, 0.490f, 0.325f, 1.00f); // #1F7D53 - Sunlit border
        const ImVec4 BorderTitleBottom = ImVec4(0.106f, 0.275f, 0.161f, 1.00f); // #1B4629 - Deep moss bottom

        // Player Bar & Window Surround - Deepest forest earth
        const ImVec4 PlayerBarBg    = ImVec4(0.067f, 0.098f, 0.043f, 1.00f);  // #11190B
        const ImVec4 WindowSurround = ImVec4(0.051f, 0.075f, 0.031f, 1.00f);  // #0D1308

        //==========================================================================
        // Title Bar - Highest canopy
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.035f, 0.051f, 0.020f, 1.00f); // #090D05
        t.TitleBar.BackgroundColorActive   = ImVec4(0.035f, 0.051f, 0.020f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.035f, 0.051f, 0.020f, 0.85f);
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
        t.ContentPanel.TabInactive         = Understory;
        t.ContentPanel.TabHovered          = MossyTrunk;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = ForestFloor;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = EmeraldMoss;
        t.ContentPanel.ButtonHovered       = ForestGreen;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Forest glade
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = Understory;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = Understory;
        t.Window.TitleBarActive    = MossyTrunk;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = EmeraldMoss;
        t.Window.ButtonHovered     = ForestGreen;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = ForestGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Forest path
        //==========================================================================

        t.TrackTable.HeaderBackground     = EmeraldMoss;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = FernGlade;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = ForestFloor;
        t.TrackTable.RowDefaultAlt        = Understory;
        t.TrackTable.RowHovered           = ForestVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = EmeraldMoss;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = ForestFloor;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = CanopyShadow;
        t.TrackTable.ScrollbarGrab        = EmeraldMoss;
        t.TrackTable.ScrollbarGrabHovered = ForestGreen;
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
        // Visualizer - Sunlight through leaves
        //==========================================================================

        t.Visualizer.BackgroundColor       = CanopyShadow;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(EmeraldMoss.x, EmeraldMoss.y, EmeraldMoss.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = EmeraldMoss;
        t.Visualizer.SpectrumColorMid      = ForestGreen;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.780f, 0.918f, 0.749f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = EmeraldMoss;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.40f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Bark frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = Understory;
        t.AlbumArtBox.BackgroundColorHovered  = MossyTrunk;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.20f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Deepest forest
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.035f, 0.051f, 0.020f, 0.95f);
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

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = MossyTrunk;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = Understory;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Forest floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = EmeraldMoss;
        t.PlayerBar.ButtonHovered             = ForestGreen;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = EmeraldMoss;
        t.PlayerBar.ButtonPrimaryHovered      = ForestGreen;
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
        t.ContextMenu.HoverTextColor          = ForestFloor;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic