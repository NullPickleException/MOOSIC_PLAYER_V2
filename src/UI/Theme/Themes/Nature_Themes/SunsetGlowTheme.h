//==============================================================================
// SunsetGlowTheme.h
//==============================================================================
// Sunset glow - warm coral, dusty rose, amber, and deep purple twilight
// Palette: #6B2D5B (twilight purple), #C4546B (dusk rose), #E8845C (sunset coral),
//          #F0A868 (golden amber), #FAD4A0 (evening glow)
// 60% Deep twilight purple and dusk shadows (#4A1E3F → #6B2D5B)
// 25% Dusk rose and sunset coral surfaces (#C4546B, #E8845C)
// 10% Golden amber accent (#F0A868)
// 5% Evening glow text (#FAD4A0)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateSunsetGlowTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Sunset glow, warm and atmospheric
        //==========================================================================

        // 60% - Deep twilight purple and dusk shadows
        const ImVec4 TwilightDeep   = ImVec4(0.290f, 0.118f, 0.247f, 1.00f);  // #4A1E3F - Twilight deep
        const ImVec4 DuskShadow     = ImVec4(0.420f, 0.176f, 0.357f, 1.00f);  // #6B2D5B - Dusk shadow
        const ImVec4 SunsetShadow   = ImVec4(0.510f, 0.235f, 0.396f, 1.00f);  // #823C65 - Sunset shadow (library bg)
        const ImVec4 PurpleHaze     = ImVec4(0.580f, 0.275f, 0.424f, 1.00f);  // #94466C - Purple haze
        const ImVec4 MauveMist      = ImVec4(0.651f, 0.318f, 0.451f, 1.00f);  // #A65173 - Mauve mist

        const ImVec4 SunsetGlow       = ImVec4(0.941f, 0.659f, 0.408f, 0.15f); // Golden amber glow
        const ImVec4 SunsetVeryLight  = ImVec4(0.941f, 0.659f, 0.408f, 0.42f);
        const ImVec4 SunsetSubtle     = ImVec4(0.941f, 0.659f, 0.408f, 0.08f);

        // 25% - Dusk rose and sunset coral surfaces
        const ImVec4 DuskRose       = ImVec4(0.769f, 0.329f, 0.420f, 1.00f);  // #C4546B - Dusk rose
        const ImVec4 SunsetCoral    = ImVec4(0.910f, 0.518f, 0.361f, 1.00f);  // #E8845C - Sunset coral
        const ImVec4 GoldenAmber    = ImVec4(0.941f, 0.659f, 0.408f, 1.00f);  // #F0A868 - Golden amber

        // 10% - Golden amber accent
        const ImVec4 Accent          = ImVec4(0.941f, 0.659f, 0.408f, 1.00f);  // #F0A868 - Golden amber
        const ImVec4 AccentDark      = ImVec4(0.910f, 0.518f, 0.361f, 1.00f);  // #E8845C - Sunset coral
        const ImVec4 AccentDarker    = ImVec4(0.769f, 0.329f, 0.420f, 1.00f);  // #C4546B - Dusk rose
        const ImVec4 AccentLight     = ImVec4(0.980f, 0.831f, 0.627f, 1.00f);  // #FAD4A0 - Evening glow
        const ImVec4 AccentVeryLight = ImVec4(0.980f, 0.831f, 0.627f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.459f, 0.212f, 0.373f, 1.00f); // #75365F

        // Text - Evening glow and warm tones
        const ImVec4 TextBright  = ImVec4(0.980f, 0.831f, 0.627f, 1.00f);  // #FAD4A0 - Evening glow
        const ImVec4 TextMuted   = ImVec4(0.910f, 0.714f, 0.557f, 1.00f);  // #E8B68E - Soft peach
        const ImVec4 TextDim     = ImVec4(0.710f, 0.478f, 0.420f, 1.00f);  // #B57A6B - Dusty rose dim
        const ImVec4 TextWhite   = ImVec4(0.992f, 0.914f, 0.812f, 1.00f);  // #FDE9CF - Warm cream

        // Borders - Twilight rose tones
        const ImVec4 BorderSubtle      = ImVec4(0.580f, 0.275f, 0.424f, 1.00f); // #94466C - Purple haze border
        const ImVec4 BorderWindow      = ImVec4(0.769f, 0.329f, 0.420f, 1.00f); // #C4546B - Dusk rose border
        const ImVec4 BorderTitle       = ImVec4(0.941f, 0.659f, 0.408f, 1.00f); // #F0A868 - Golden amber border
        const ImVec4 BorderTitleBottom = ImVec4(0.290f, 0.118f, 0.247f, 1.00f); // #4A1E3F - Twilight bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.212f, 0.086f, 0.180f, 1.00f);  // #36162E
        const ImVec4 WindowSurround = ImVec4(0.165f, 0.067f, 0.141f, 1.00f);  // #2A1124

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.118f, 0.047f, 0.102f, 1.00f); // #1E0C1A
        t.TitleBar.BackgroundColorActive   = ImVec4(0.118f, 0.047f, 0.102f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.118f, 0.047f, 0.102f, 0.85f);
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
        t.ContentPanel.TabInactive         = SunsetShadow;
        t.ContentPanel.TabHovered          = PurpleHaze;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = DuskRose;
        t.ContentPanel.ButtonHovered       = SunsetCoral;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = SunsetShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = SunsetShadow;
        t.Window.TitleBarActive    = PurpleHaze;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = DuskRose;
        t.Window.ButtonHovered     = SunsetCoral;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = SunsetGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = DuskRose;
        t.TrackTable.HeaderTextColor      = TextWhite;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = MauveMist;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextWhite;
        t.TrackTable.HeaderTextArtist     = TextWhite;
        t.TrackTable.HeaderTextAlbum      = TextWhite;
        t.TrackTable.HeaderTextExtension  = TextWhite;
        t.TrackTable.HeaderTextDuration   = TextWhite;

        t.TrackTable.RowDefault           = TwilightDeep;
        t.TrackTable.RowDefaultAlt        = SunsetShadow;
        t.TrackTable.RowHovered           = SunsetVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = DuskRose;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = DuskShadow;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = DuskShadow;
        t.TrackTable.ScrollbarGrab        = DuskRose;
        t.TrackTable.ScrollbarGrabHovered = SunsetCoral;
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

        t.Visualizer.BackgroundColor       = DuskShadow;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(DuskRose.x, DuskRose.y, DuskRose.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = DuskRose;
        t.Visualizer.SpectrumColorMid      = SunsetCoral;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.980f, 0.831f, 0.627f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = DuskRose;
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
        t.AlbumArtBox.BackgroundColor         = SunsetShadow;
        t.AlbumArtBox.BackgroundColorHovered  = PurpleHaze;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.118f, 0.047f, 0.102f, 0.95f);
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
        t.SearchBar.rowHoverColor             = PurpleHaze;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = SunsetShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = DuskRose;
        t.PlayerBar.ButtonHovered             = SunsetCoral;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = DuskRose;
        t.PlayerBar.ButtonPrimaryHovered      = SunsetCoral;
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
        t.ContextMenu.HoverTextColor          = DuskShadow;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic