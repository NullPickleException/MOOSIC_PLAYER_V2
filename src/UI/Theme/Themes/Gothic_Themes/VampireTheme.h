//==============================================================================
// VampireTheme.h
//==============================================================================
// Crypt noir - secretive, modern vampire, cold stone and dried blood
// Palette: #0B0C10 (crypt darkness), #1C1A1F (stone shadow), #2E232A (aged wine),
//          #5B1B2B (dried blood), #B9A6A0 (pale skin)
// 55% Crypt darkness and stone shadows (#0B0C10 → #1C1A1F)
// 25% Aged wine and dried blood surfaces (#2E232A, #5B1B2B)
// 10% Dried blood accent (#5B1B2B)
// 10% Pale skin text (#B9A6A0)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateVampireTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Crypt noir vampire
        //==========================================================================

        // 55% - Crypt darkness and stone shadows
        const ImVec4 CryptDarkness  = ImVec4(0.043f, 0.047f, 0.063f, 1.00f);  // #0B0C10 - Crypt darkness
        const ImVec4 StoneShadow    = ImVec4(0.110f, 0.102f, 0.122f, 1.00f);  // #1C1A1F - Stone shadow
        const ImVec4 ColdStone      = ImVec4(0.141f, 0.133f, 0.153f, 1.00f);  // #242227 - Cold stone (library bg)
        const ImVec4 AgedWine       = ImVec4(0.180f, 0.137f, 0.165f, 1.00f);  // #2E232A - Aged wine stain
        const ImVec4 CryptWall      = ImVec4(0.220f, 0.173f, 0.200f, 1.00f);  // #382C33 - Crypt wall

        const ImVec4 VampireGlow       = ImVec4(0.357f, 0.106f, 0.169f, 0.20f); // Dried blood glow
        const ImVec4 VampireVeryLight  = ImVec4(0.357f, 0.106f, 0.169f, 0.50f);
        const ImVec4 VampireSubtle     = ImVec4(0.357f, 0.106f, 0.169f, 0.10f);

        // 25% - Aged wine and dried blood surfaces
        const ImVec4 WineDark      = ImVec4(0.180f, 0.137f, 0.165f, 1.00f);  // #2E232A - Aged wine
        const ImVec4 DriedBlood    = ImVec4(0.357f, 0.106f, 0.169f, 1.00f);  // #5B1B2B - Dried blood
        const ImVec4 BloodStain    = ImVec4(0.455f, 0.137f, 0.216f, 1.00f);  // #742337 - Fresh blood stain

        // 10% - Dried blood accent
        const ImVec4 Accent          = ImVec4(0.357f, 0.106f, 0.169f, 1.00f);  // #5B1B2B - Dried blood
        const ImVec4 AccentDark      = ImVec4(0.267f, 0.078f, 0.125f, 1.00f);  // #441420 - Dark blood
        const ImVec4 AccentDarker    = ImVec4(0.196f, 0.055f, 0.090f, 1.00f);  // #320E17 - Old blood
        const ImVec4 AccentLight     = ImVec4(0.455f, 0.137f, 0.216f, 1.00f);  // #742337 - Fresh blood
        const ImVec4 AccentVeryLight = ImVec4(0.455f, 0.137f, 0.216f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.122f, 0.114f, 0.133f, 1.00f); // #1F1D22

        // Text - Pale skin tones
        const ImVec4 TextBright  = ImVec4(0.725f, 0.651f, 0.627f, 1.00f);  // #B9A6A0 - Pale skin
        const ImVec4 TextMuted   = ImVec4(0.580f, 0.518f, 0.498f, 1.00f);  // #94847F - Shadowed skin
        const ImVec4 TextDim     = ImVec4(0.392f, 0.349f, 0.333f, 1.00f);  // #645955 - Faded vein
        const ImVec4 TextWhite   = ImVec4(0.804f, 0.741f, 0.722f, 1.00f);  // #CDBDB8 - Moonlit skin

        // Borders - Cold stone with blood tint
        const ImVec4 BorderSubtle      = ImVec4(0.180f, 0.137f, 0.165f, 1.00f); // #2E232A - Wine-tinted stone
        const ImVec4 BorderWindow      = ImVec4(0.267f, 0.078f, 0.125f, 1.00f); // #441420 - Dark blood border
        const ImVec4 BorderTitle       = ImVec4(0.357f, 0.106f, 0.169f, 1.00f); // #5B1B2B - Dried blood border
        const ImVec4 BorderTitleBottom = ImVec4(0.196f, 0.055f, 0.090f, 1.00f); // #320E17 - Old blood bottom

        // Player Bar & Window Surround - Deepest crypt
        const ImVec4 PlayerBarBg    = ImVec4(0.031f, 0.035f, 0.047f, 1.00f);  // #08090C
        const ImVec4 WindowSurround = ImVec4(0.024f, 0.027f, 0.035f, 1.00f);  // #060709

        //==========================================================================
        // Title Bar - Crypt entrance
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.016f, 0.020f, 0.027f, 1.00f); // #040507
        t.TitleBar.BackgroundColorActive   = ImVec4(0.016f, 0.020f, 0.027f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.016f, 0.020f, 0.027f, 0.85f);
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
        t.ContentPanel.TabInactive         = ColdStone;
        t.ContentPanel.TabHovered          = AgedWine;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = WineDark;
        t.ContentPanel.ButtonHovered       = DriedBlood;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Cold stone chamber
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = ColdStone;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = ColdStone;
        t.Window.TitleBarActive    = AgedWine;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = WineDark;
        t.Window.ButtonHovered     = DriedBlood;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = VampireGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Crypt shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = WineDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = CryptWall;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = CryptDarkness;
        t.TrackTable.RowDefaultAlt        = ColdStone;
        t.TrackTable.RowHovered           = VampireVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = WineDark;
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

        t.TrackTable.ScrollbarBg          = StoneShadow;
        t.TrackTable.ScrollbarGrab        = WineDark;
        t.TrackTable.ScrollbarGrabHovered = DriedBlood;
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
        // Visualizer - Blood pulse in darkness
        //==========================================================================

        t.Visualizer.BackgroundColor       = StoneShadow;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(WineDark.x, WineDark.y, WineDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: aged wine → dried blood → fresh blood → pale skin ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = WineDark;
        t.Visualizer.SpectrumColorMid      = DriedBlood;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.725f, 0.651f, 0.627f, 1.00f); // #B9A6A0 - Pale skin peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = WineDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Cold stone frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = ColdStone;
        t.AlbumArtBox.BackgroundColorHovered  = AgedWine;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Deepest crypt
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.016f, 0.020f, 0.027f, 0.95f);
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
        // Search Bar - Ancient grimoire
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = AgedWine;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = ColdStone;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Crypt floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = WineDark;
        t.PlayerBar.ButtonHovered             = DriedBlood;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = WineDark;
        t.PlayerBar.ButtonPrimaryHovered      = DriedBlood;
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
        // Popup Menu - Crypt chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = TextWhite;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic