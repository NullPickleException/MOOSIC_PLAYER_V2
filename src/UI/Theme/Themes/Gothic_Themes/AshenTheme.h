//==============================================================================
// AshenTheme.h
//==============================================================================
// Burned ruins, volcanic ash, smoke, and dying embers
// Palette: #222831 (cold ash), #393E46 (smoke stone), #948979 (warm ash),
//          #DFD0B8 (pale smoke)
// 60% Cold ash and smoke stone (#222831 → #393E46)
// 25% Warm ash and weathered stone surfaces (#393E46, #948979)
// 10% Warm ash accent (#948979)
// 5% Pale smoke text (#DFD0B8)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateAshenTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Burned ruins, cold ash, rising smoke
        //==========================================================================

        // 60% - Cold ash and smoke stone
        const ImVec4 ColdAsh        = ImVec4(0.133f, 0.157f, 0.192f, 1.00f);  // #222831 - Cold ash
        const ImVec4 SmokeStone     = ImVec4(0.224f, 0.243f, 0.275f, 1.00f);  // #393E46 - Smoke stone
        const ImVec4 AshField       = ImVec4(0.278f, 0.298f, 0.333f, 1.00f);  // #474C55 - Ash field (library bg)
        const ImVec4 AshDrift       = ImVec4(0.333f, 0.353f, 0.392f, 1.00f);  // #555A64 - Ash drift
        const ImVec4 SmokeLayer     = ImVec4(0.388f, 0.408f, 0.447f, 1.00f);  // #636872 - Smoke layer

        const ImVec4 AshenGlow       = ImVec4(0.580f, 0.537f, 0.475f, 0.15f); // Warm ash glow
        const ImVec4 AshenVeryLight  = ImVec4(0.580f, 0.537f, 0.475f, 0.40f);
        const ImVec4 AshenSubtle     = ImVec4(0.580f, 0.537f, 0.475f, 0.08f);

        // 25% - Warm ash and weathered stone surfaces
        const ImVec4 WeatheredStone = ImVec4(0.224f, 0.243f, 0.275f, 1.00f);  // #393E46 - Weathered stone
        const ImVec4 WarmAsh        = ImVec4(0.580f, 0.537f, 0.475f, 1.00f);  // #948979 - Warm ash
        const ImVec4 PaleAsh        = ImVec4(0.678f, 0.635f, 0.573f, 1.00f);  // #ADA292 - Pale ash

        // 10% - Warm ash accent
        const ImVec4 Accent          = ImVec4(0.580f, 0.537f, 0.475f, 1.00f);  // #948979 - Warm ash
        const ImVec4 AccentDark      = ImVec4(0.451f, 0.420f, 0.369f, 1.00f);  // #736B5E - Dark ash
        const ImVec4 AccentDarker    = ImVec4(0.333f, 0.310f, 0.271f, 1.00f);  // #554F45 - Deepest ash
        const ImVec4 AccentLight     = ImVec4(0.875f, 0.816f, 0.722f, 1.00f);  // #DFD0B8 - Pale smoke
        const ImVec4 AccentVeryLight = ImVec4(0.875f, 0.816f, 0.722f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.247f, 0.267f, 0.302f, 1.00f); // #3F444D

        // Text - Pale smoke through ruins
        const ImVec4 TextBright  = ImVec4(0.875f, 0.816f, 0.722f, 1.00f);  // #DFD0B8 - Pale smoke
        const ImVec4 TextMuted   = ImVec4(0.678f, 0.635f, 0.573f, 1.00f);  // #ADA292 - Distant smoke
        const ImVec4 TextDim     = ImVec4(0.482f, 0.451f, 0.404f, 1.00f);  // #7B7367 - Settled ash
        const ImVec4 TextWhite   = ImVec4(0.914f, 0.863f, 0.784f, 1.00f);  // #E9DCC8 - Pure smoke white

        // Borders - Ash-tinted stone
        const ImVec4 BorderSubtle      = ImVec4(0.333f, 0.353f, 0.392f, 1.00f); // #555A64 - Ash border
        const ImVec4 BorderWindow      = ImVec4(0.451f, 0.420f, 0.369f, 1.00f); // #736B5E - Dark ash border
        const ImVec4 BorderTitle       = ImVec4(0.580f, 0.537f, 0.475f, 1.00f); // #948979 - Warm ash border
        const ImVec4 BorderTitleBottom = ImVec4(0.333f, 0.310f, 0.271f, 1.00f); // #554F45 - Deep ash bottom

        // Player Bar & Window Surround - Deepest ash pit
        const ImVec4 PlayerBarBg    = ImVec4(0.094f, 0.110f, 0.137f, 1.00f);  // #181C23
        const ImVec4 WindowSurround = ImVec4(0.075f, 0.090f, 0.110f, 1.00f);  // #13171C

        //==========================================================================
        // Title Bar - Charred peak
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.059f, 0.071f, 0.086f, 1.00f); // #0F1216
        t.TitleBar.BackgroundColorActive   = ImVec4(0.059f, 0.071f, 0.086f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.059f, 0.071f, 0.086f, 0.85f);
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
        t.ContentPanel.TabInactive         = AshField;
        t.ContentPanel.TabHovered          = AshDrift;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = ColdAsh;  // Dark text on warm ash tab
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = WeatheredStone;
        t.ContentPanel.ButtonHovered       = WarmAsh;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Smoke-filled ruins
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = AshField;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = AshField;
        t.Window.TitleBarActive    = AshDrift;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = WeatheredStone;
        t.Window.ButtonHovered     = WarmAsh;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = AshenGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Charred remains
        //==========================================================================

        t.TrackTable.HeaderBackground     = WeatheredStone;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = SmokeLayer;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = ColdAsh;
        t.TrackTable.RowDefaultAlt        = AshField;
        t.TrackTable.RowHovered           = AshenVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = WeatheredStone;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = ColdAsh;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = SmokeStone;
        t.TrackTable.ScrollbarGrab        = WeatheredStone;
        t.TrackTable.ScrollbarGrabHovered = WarmAsh;
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
        // Visualizer - Smoke rising through ruins
        //==========================================================================

        t.Visualizer.BackgroundColor       = SmokeStone;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.08f);
        t.Visualizer.GridColor             = ImVec4(WeatheredStone.x, WeatheredStone.y, WeatheredStone.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: weathered stone → warm ash → pale ash → pale smoke ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = WeatheredStone;
        t.Visualizer.SpectrumColorMid      = WarmAsh;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.875f, 0.816f, 0.722f, 1.00f); // #DFD0B8 - Pale smoke peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = WeatheredStone;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.40f;
        t.Visualizer.BarBrightnessMax      = 1.15f;

        //==========================================================================
        // Album Art - Charred frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = AshField;
        t.AlbumArtBox.BackgroundColorHovered  = AshDrift;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.18f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Charred sanctuary
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.059f, 0.071f, 0.086f, 0.95f);
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
        // Search Bar - Ashen inscriptions
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = AshDrift;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = AshField;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Ash-covered ground
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = WeatheredStone;
        t.PlayerBar.ButtonHovered             = WarmAsh;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = WeatheredStone;
        t.PlayerBar.ButtonPrimaryHovered      = WarmAsh;
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
        // Popup Menu - Ashen chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = ColdAsh;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic