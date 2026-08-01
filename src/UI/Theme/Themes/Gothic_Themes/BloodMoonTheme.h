//==============================================================================
// BloodMoonTheme.h
//==============================================================================
// Moonlit forest with deep red glow - cold silver moonlight meets fresh blood
// 60% Near-black with subtle blood-wine undertone (#110A0A → #362424)
// 30% Rich blood-washed surfaces (#503131, #684040, #845353)
// 10% Luminous blood-moon crimson (#E53935)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateBloodMoonTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - Moonlit forest & blood glow
        //==========================================================================

        // 60% - Near-black with subtle blood-wine undertone (darkened for contrast)
        const ImVec4 MoonDeep     = ImVec4(0.043f, 0.024f, 0.024f, 1.00f);  // #0B0606 - Moonless forest floor
        const ImVec4 MoonPanel    = ImVec4(0.067f, 0.039f, 0.039f, 1.00f);  // #110A0A - Shadowed bark
        const ImVec4 MoonDefault  = ImVec4(0.098f, 0.067f, 0.067f, 1.00f);  // #191111 - Deep forest shadow (library bg)
        const ImVec4 MoonAlt      = ImVec4(0.133f, 0.090f, 0.090f, 1.00f);  // #221717 - Moonlit clearing edge
        const ImVec4 MoonSurface  = ImVec4(0.173f, 0.114f, 0.114f, 1.00f);  // #2C1D1D - Moonlit ground

        const ImVec4 MoonGlow       = ImVec4(0.898f, 0.224f, 0.208f, 0.20f); // Blood moon glow
        const ImVec4 MoonVeryLight  = ImVec4(0.898f, 0.224f, 0.208f, 0.50f);
        const ImVec4 MoonSubtle     = ImVec4(0.898f, 0.224f, 0.208f, 0.10f);

        // 30% - Rich blood-washed surfaces
        const ImVec4 BloodWashDark   = ImVec4(0.314f, 0.192f, 0.192f, 1.00f);  // #503131
        const ImVec4 BloodWashMid    = ImVec4(0.408f, 0.251f, 0.251f, 1.00f);  // #684040
        const ImVec4 BloodWashLight  = ImVec4(0.518f, 0.325f, 0.325f, 1.00f);  // #845353

        // 10% - Luminous blood-moon crimson
        const ImVec4 Accent          = ImVec4(0.898f, 0.224f, 0.208f, 1.00f);  // #E53935
        const ImVec4 AccentDark      = ImVec4(0.718f, 0.165f, 0.153f, 1.00f);
        const ImVec4 AccentDarker    = ImVec4(0.541f, 0.118f, 0.106f, 1.00f);
        const ImVec4 AccentLight     = ImVec4(0.941f, 0.337f, 0.318f, 1.00f);
        const ImVec4 AccentVeryLight = ImVec4(0.941f, 0.337f, 0.318f, 0.50f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.114f, 0.078f, 0.078f, 1.00f); // #1D1414

        // Text - cold silver moonlight tinted warm by blood
        const ImVec4 TextBright  = ImVec4(0.961f, 0.945f, 0.941f, 1.00f);  // #F5F1F0
        const ImVec4 TextMuted   = ImVec4(0.733f, 0.663f, 0.659f, 1.00f);  // #BBA9A8
        const ImVec4 TextDim     = ImVec4(0.455f, 0.404f, 0.400f, 1.00f);  // #746766
        const ImVec4 TextWhite   = ImVec4(0.976f, 0.965f, 0.961f, 1.00f);

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.239f, 0.157f, 0.157f, 1.00f); // #3D2828

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.035f, 0.016f, 0.016f, 1.00f);  // #090404
        const ImVec4 WindowSurround = ImVec4(0.027f, 0.012f, 0.012f, 1.00f);  // #070303

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.020f, 0.008f, 0.008f, 1.00f); // #050202
        t.TitleBar.BackgroundColorActive   = ImVec4(0.020f, 0.008f, 0.008f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.020f, 0.008f, 0.008f, 0.85f);
        t.TitleBar.BackgroundOpacity       = 1.0f;

        t.TitleBar.ShowBottomBorder        = true;
        t.TitleBar.BottomBorderColor       = BorderSubtle;
        t.TitleBar.ShowWindowBorder        = true;
        t.TitleBar.WindowBorderColor       = BloodWashDark;
        t.TitleBar.ShowAccentLine          = true;
        t.TitleBar.AccentLineColor         = Accent;
        t.TitleBar.TitleTextColor          = TextBright;
        t.TitleBar.TitleTextColorInactive  = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive           = Accent;
        t.ContentPanel.TabInactive         = MoonDefault;
        t.ContentPanel.TabHovered          = MoonAlt;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = BloodWashDark;
        t.ContentPanel.ButtonHovered       = BloodWashMid;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BloodWashMid;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = MoonDefault;
        t.Window.WindowBorder      = BorderSubtle;
        t.Window.TitleBar          = MoonDefault;
        t.Window.TitleBarActive    = MoonAlt;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = BloodWashDark;
        t.Window.ButtonHovered     = BloodWashMid;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = MoonGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = BloodWashDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderSubtle;
        t.TrackTable.HeaderHovered        = MoonSurface;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = MoonDeep;
        t.TrackTable.RowDefaultAlt        = MoonDefault;
        t.TrackTable.RowHovered           = MoonVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = BloodWashDark;
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

        t.TrackTable.BorderColor          = BorderSubtle;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = MoonPanel;
        t.TrackTable.ScrollbarGrab        = BloodWashDark;
        t.TrackTable.ScrollbarGrabHovered = BloodWashMid;
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

        t.Visualizer.BackgroundColor       = MoonPanel;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(BloodWashDark.x, BloodWashDark.y, BloodWashDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderSubtle;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = AccentDark;
        t.Visualizer.SpectrumColorMid      = Accent;
        t.Visualizer.SpectrumColorHigh     = AccentLight;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.976f, 0.478f, 0.459f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = BloodWashDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = MoonDefault;
        t.AlbumArtBox.BackgroundColorHovered  = MoonAlt;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.020f, 0.008f, 0.008f, 0.95f);
        t.AlbumArtLightbox.BorderColor        = BloodWashDark;
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
        t.SearchBar.borderColor               = BloodWashMid;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = MoonAlt;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = MoonDefault;
        t.SearchBar.inputBorderColor          = BloodWashMid;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = BloodWashDark;
        t.PlayerBar.ButtonHovered             = BloodWashMid;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = BloodWashDark;
        t.PlayerBar.ButtonPrimaryHovered      = BloodWashMid;
        t.PlayerBar.ButtonPrimaryActive       = AccentDark;
        t.PlayerBar.SliderTrack               = BorderSubtle;
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
        t.ContextMenu.BorderColor             = BloodWashMid;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = TextWhite;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic