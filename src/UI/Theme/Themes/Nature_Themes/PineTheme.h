//==============================================================================
// PineTheme.h
//==============================================================================
// Pine forest - evergreen, bark, filtered mountain light
// Palette: #2C3930 (pine needle), #3F4F44 (evergreen trunk), #A27B5C (pine bark),
//          #DCD7C9 (mountain mist)
// 60% Pine needle and evergreen (#2C3930 → #3F4F44)
// 25% Pine bark and warm wood surfaces (#A27B5C, #B89472)
// 10% Pine bark accent (#A27B5C)
// 5% Mountain mist text (#DCD7C9)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreatePineTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Pine forest, mountain evergreen
        //==========================================================================

        // 60% - Pine needle and evergreen
        const ImVec4 PineNeedle     = ImVec4(0.173f, 0.224f, 0.188f, 1.00f);  // #2C3930 - Pine needle floor
        const ImVec4 Evergreen      = ImVec4(0.247f, 0.310f, 0.267f, 1.00f);  // #3F4F44 - Evergreen trunk
        const ImVec4 ForestShade    = ImVec4(0.286f, 0.353f, 0.306f, 1.00f);  // #495A4E - Forest shade (library bg)
        const ImVec4 PineBough      = ImVec4(0.325f, 0.396f, 0.345f, 1.00f);  // #536558 - Pine bough
        const ImVec4 MistyPine      = ImVec4(0.365f, 0.439f, 0.384f, 1.00f);  // #5D7062 - Misty pine

        const ImVec4 PineGlow       = ImVec4(0.635f, 0.482f, 0.361f, 0.15f); // Bark glow
        const ImVec4 PineVeryLight  = ImVec4(0.635f, 0.482f, 0.361f, 0.45f);
        const ImVec4 PineSubtle     = ImVec4(0.635f, 0.482f, 0.361f, 0.08f);

        // 25% - Pine bark and warm wood surfaces
        const ImVec4 PineBark       = ImVec4(0.635f, 0.482f, 0.361f, 1.00f);  // #A27B5C - Pine bark
        const ImVec4 WarmWood       = ImVec4(0.722f, 0.580f, 0.447f, 1.00f);  // #B89472 - Warm wood
        const ImVec4 MountainMist   = ImVec4(0.863f, 0.843f, 0.788f, 1.00f);  // #DCD7C9 - Mountain mist

        // 10% - Pine bark accent
        const ImVec4 Accent          = ImVec4(0.635f, 0.482f, 0.361f, 1.00f);  // #A27B5C - Pine bark
        const ImVec4 AccentDark      = ImVec4(0.502f, 0.373f, 0.278f, 1.00f);  // #805F47 - Dark bark
        const ImVec4 AccentDarker    = ImVec4(0.373f, 0.275f, 0.204f, 1.00f);  // #5F4634 - Deepest bark
        const ImVec4 AccentLight     = ImVec4(0.863f, 0.843f, 0.788f, 1.00f);  // #DCD7C9 - Mountain mist
        const ImVec4 AccentVeryLight = ImVec4(0.863f, 0.843f, 0.788f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.263f, 0.322f, 0.278f, 1.00f); // #435247

        // Text - Mountain mist through pines
        const ImVec4 TextBright  = ImVec4(0.863f, 0.843f, 0.788f, 1.00f);  // #DCD7C9 - Mountain mist
        const ImVec4 TextMuted   = ImVec4(0.682f, 0.663f, 0.616f, 1.00f);  // #AEA99D - Distant mist
        const ImVec4 TextDim     = ImVec4(0.482f, 0.463f, 0.427f, 1.00f);  // #7B766D - Forest shadow
        const ImVec4 TextWhite   = ImVec4(0.906f, 0.890f, 0.843f, 1.00f);  // #E7E3D7 - Bright mist

        // Borders - Bark-tinted pine
        const ImVec4 BorderSubtle      = ImVec4(0.325f, 0.396f, 0.345f, 1.00f); // #536558 - Pine border
        const ImVec4 BorderWindow      = ImVec4(0.502f, 0.373f, 0.278f, 1.00f); // #805F47 - Bark border
        const ImVec4 BorderTitle       = ImVec4(0.635f, 0.482f, 0.361f, 1.00f); // #A27B5C - Warm bark border
        const ImVec4 BorderTitleBottom = ImVec4(0.373f, 0.275f, 0.204f, 1.00f); // #5F4634 - Deep bark bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.122f, 0.157f, 0.133f, 1.00f);  // #1F2822
        const ImVec4 WindowSurround = ImVec4(0.094f, 0.125f, 0.106f, 1.00f);  // #18201B

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.067f, 0.090f, 0.075f, 1.00f); // #111713
        t.TitleBar.BackgroundColorActive   = ImVec4(0.067f, 0.090f, 0.075f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.067f, 0.090f, 0.075f, 0.85f);
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
        t.ContentPanel.TabInactive         = ForestShade;
        t.ContentPanel.TabHovered          = PineBough;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = PineNeedle;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = PineBark;
        t.ContentPanel.ButtonHovered       = WarmWood;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = ForestShade;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = ForestShade;
        t.Window.TitleBarActive    = PineBough;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = PineBark;
        t.Window.ButtonHovered     = WarmWood;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = PineGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = PineBark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = MistyPine;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = PineNeedle;
        t.TrackTable.RowDefaultAlt        = ForestShade;
        t.TrackTable.RowHovered           = PineVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = PineBark;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = PineNeedle;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = Evergreen;
        t.TrackTable.ScrollbarGrab        = PineBark;
        t.TrackTable.ScrollbarGrabHovered = WarmWood;
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

        t.Visualizer.BackgroundColor       = Evergreen;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(PineBark.x, PineBark.y, PineBark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = PineBark;
        t.Visualizer.SpectrumColorMid      = WarmWood;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.863f, 0.843f, 0.788f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = PineBark;
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
        t.AlbumArtBox.BackgroundColor         = ForestShade;
        t.AlbumArtBox.BackgroundColorHovered  = PineBough;
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
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.067f, 0.090f, 0.075f, 0.95f);
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
        t.SearchBar.rowHoverColor             = PineBough;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = ForestShade;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = PineBark;
        t.PlayerBar.ButtonHovered             = WarmWood;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = PineBark;
        t.PlayerBar.ButtonPrimaryHovered      = WarmWood;
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
        t.ContextMenu.HoverTextColor          = PineNeedle;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic