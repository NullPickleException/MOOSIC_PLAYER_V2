//==============================================================================
// MossTheme.h
//==============================================================================
// Vibrant moss - lush, earthy, organic growth
// Palette: #6CA651 (living moss), #BBCB2E (chartreuse growth), #839705 (olive earth),
//          #6B7445 (dried moss)
// 60% Darkened mossy earth (#1A1F0E → #2B3318)
// 25% Living moss and chartreuse surfaces (#6CA651, #BBCB2E)
// 10% Chartreuse growth accent (#BBCB2E)
// 5% Pale green text
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateMossTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Vibrant moss, lush and organic
        //==========================================================================

        // 60% - Darkened mossy earth
        const ImVec4 MossEarth      = ImVec4(0.102f, 0.122f, 0.055f, 1.00f);  // #1A1F0E - Dark mossy earth
        const ImVec4 MossBed        = ImVec4(0.169f, 0.200f, 0.094f, 1.00f);  // #2B3318 - Moss bed
        const ImVec4 MossShadow     = ImVec4(0.212f, 0.247f, 0.122f, 1.00f);  // #363F1F - Moss in shadow (library bg)
        const ImVec4 MossPatch      = ImVec4(0.255f, 0.294f, 0.149f, 1.00f);  // #414B26 - Moss patch
        const ImVec4 MossCarpet     = ImVec4(0.298f, 0.341f, 0.176f, 1.00f);  // #4C572D - Moss carpet

        const ImVec4 MossGlow       = ImVec4(0.733f, 0.796f, 0.180f, 0.15f); // Chartreuse glow
        const ImVec4 MossVeryLight  = ImVec4(0.733f, 0.796f, 0.180f, 0.45f);
        const ImVec4 MossSubtle     = ImVec4(0.733f, 0.796f, 0.180f, 0.08f);

        // 25% - Living moss and chartreuse surfaces
        const ImVec4 LivingMoss     = ImVec4(0.424f, 0.651f, 0.318f, 1.00f);  // #6CA651 - Living moss
        const ImVec4 Chartreuse     = ImVec4(0.733f, 0.796f, 0.180f, 1.00f);  // #BBCB2E - Chartreuse growth
        const ImVec4 OliveEarth     = ImVec4(0.514f, 0.592f, 0.020f, 1.00f);  // #839705 - Olive earth

        // 10% - Chartreuse growth accent
        const ImVec4 Accent          = ImVec4(0.733f, 0.796f, 0.180f, 1.00f);  // #BBCB2E - Chartreuse
        const ImVec4 AccentDark      = ImVec4(0.514f, 0.592f, 0.020f, 1.00f);  // #839705 - Olive earth
        const ImVec4 AccentDarker    = ImVec4(0.420f, 0.455f, 0.271f, 1.00f);  // #6B7445 - Dried moss
        const ImVec4 AccentLight     = ImVec4(0.804f, 0.851f, 0.306f, 1.00f);  // #CDD94E - Bright chartreuse
        const ImVec4 AccentVeryLight = ImVec4(0.804f, 0.851f, 0.306f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.192f, 0.224f, 0.106f, 1.00f); // #31391B

        // Text - Pale green growth
        const ImVec4 TextBright  = ImVec4(0.878f, 0.925f, 0.741f, 1.00f);  // #E0ECBD - Pale green
        const ImVec4 TextMuted   = ImVec4(0.686f, 0.741f, 0.557f, 1.00f);  // #AFBD8E - Muted moss
        const ImVec4 TextDim     = ImVec4(0.471f, 0.514f, 0.380f, 1.00f);  // #788361 - Dark moss
        const ImVec4 TextWhite   = ImVec4(0.918f, 0.949f, 0.812f, 1.00f);  // #EAF2CF - Bright growth

        // Borders - Moss-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.255f, 0.294f, 0.149f, 1.00f); // #414B26 - Moss border
        const ImVec4 BorderWindow      = ImVec4(0.420f, 0.455f, 0.271f, 1.00f); // #6B7445 - Dried moss border
        const ImVec4 BorderTitle       = ImVec4(0.424f, 0.651f, 0.318f, 1.00f); // #6CA651 - Living moss border
        const ImVec4 BorderTitleBottom = ImVec4(0.298f, 0.341f, 0.176f, 1.00f); // #4C572D - Deep moss bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.075f, 0.090f, 0.039f, 1.00f);  // #13170A
        const ImVec4 WindowSurround = ImVec4(0.059f, 0.071f, 0.031f, 1.00f);  // #0F1208

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.043f, 0.051f, 0.020f, 1.00f); // #0B0D05
        t.TitleBar.BackgroundColorActive   = ImVec4(0.043f, 0.051f, 0.020f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.043f, 0.051f, 0.020f, 0.85f);
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
        t.ContentPanel.TabInactive         = MossShadow;
        t.ContentPanel.TabHovered          = MossPatch;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = MossEarth;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = LivingMoss;
        t.ContentPanel.ButtonHovered       = Chartreuse;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = MossShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = MossShadow;
        t.Window.TitleBarActive    = MossPatch;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = LivingMoss;
        t.Window.ButtonHovered     = Chartreuse;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = MossGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = LivingMoss;
        t.TrackTable.HeaderTextColor      = MossEarth;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = MossCarpet;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = MossEarth;
        t.TrackTable.HeaderTextArtist     = MossEarth;
        t.TrackTable.HeaderTextAlbum      = MossEarth;
        t.TrackTable.HeaderTextExtension  = MossEarth;
        t.TrackTable.HeaderTextDuration   = MossEarth;

        t.TrackTable.RowDefault           = MossEarth;
        t.TrackTable.RowDefaultAlt        = MossShadow;
        t.TrackTable.RowHovered           = MossVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = LivingMoss;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = MossEarth;
        t.TrackTable.TextPlaying          = MossEarth;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = MossBed;
        t.TrackTable.ScrollbarGrab        = LivingMoss;
        t.TrackTable.ScrollbarGrabHovered = Chartreuse;
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

        t.Visualizer.BackgroundColor       = MossBed;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(LivingMoss.x, LivingMoss.y, LivingMoss.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = LivingMoss;
        t.Visualizer.SpectrumColorMid      = Chartreuse;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.878f, 0.925f, 0.741f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = LivingMoss;
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
        t.AlbumArtBox.BackgroundColor         = MossShadow;
        t.AlbumArtBox.BackgroundColorHovered  = MossPatch;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.043f, 0.051f, 0.020f, 0.95f);
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
        t.SearchBar.rowHoverColor             = MossPatch;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = MossShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = LivingMoss;
        t.PlayerBar.ButtonHovered             = Chartreuse;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = LivingMoss;
        t.PlayerBar.ButtonPrimaryHovered      = Chartreuse;
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
        t.ContextMenu.HoverTextColor          = MossEarth;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic