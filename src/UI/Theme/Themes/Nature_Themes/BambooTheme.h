//==============================================================================
// BambooTheme.h
//==============================================================================
// Bamboo grove - fresh shoots, filtered sunlight, peaceful green
// Palette: #84B179 (bamboo leaf), #A2CB8B (fresh shoot), #C7EABB (young bamboo),
//          #E8F5BD (pale sunlight)
// 60% Darkened bamboo forest (#2D3D28 → #3D5236)
// 25% Bamboo leaf and fresh shoot surfaces (#84B179, #A2CB8B)
// 10% Fresh shoot accent (#A2CB8B)
// 5% Pale sunlight text (#E8F5BD)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateBambooTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Bamboo grove, fresh and peaceful
        //==========================================================================

        // 60% - Darkened bamboo forest
        const ImVec4 BambooForest   = ImVec4(0.176f, 0.239f, 0.157f, 1.00f);  // #2D3D28 - Bamboo forest floor
        const ImVec4 BambooShade    = ImVec4(0.239f, 0.322f, 0.212f, 1.00f);  // #3D5236 - Bamboo shade
        const ImVec4 GroveShadow    = ImVec4(0.282f, 0.369f, 0.247f, 1.00f);  // #485E3F - Grove shadow (library bg)
        const ImVec4 BambooStalk    = ImVec4(0.325f, 0.416f, 0.282f, 1.00f);  // #536A48 - Bamboo stalk
        const ImVec4 SunlitGrove    = ImVec4(0.369f, 0.463f, 0.318f, 1.00f);  // #5E7651 - Sunlit grove

        const ImVec4 BambooGlow       = ImVec4(0.518f, 0.694f, 0.475f, 0.15f); // Bamboo leaf glow
        const ImVec4 BambooVeryLight  = ImVec4(0.518f, 0.694f, 0.475f, 0.45f);
        const ImVec4 BambooSubtle     = ImVec4(0.518f, 0.694f, 0.475f, 0.08f);

        // 25% - Bamboo leaf and fresh shoot surfaces
        const ImVec4 BambooLeaf     = ImVec4(0.518f, 0.694f, 0.475f, 1.00f);  // #84B179 - Bamboo leaf
        const ImVec4 FreshShoot     = ImVec4(0.635f, 0.796f, 0.545f, 1.00f);  // #A2CB8B - Fresh shoot
        const ImVec4 YoungBamboo    = ImVec4(0.780f, 0.918f, 0.733f, 1.00f);  // #C7EABB - Young bamboo

        // 10% - Fresh shoot accent
        const ImVec4 Accent          = ImVec4(0.635f, 0.796f, 0.545f, 1.00f);  // #A2CB8B - Fresh shoot
        const ImVec4 AccentDark      = ImVec4(0.518f, 0.694f, 0.475f, 1.00f);  // #84B179 - Bamboo leaf
        const ImVec4 AccentDarker    = ImVec4(0.369f, 0.518f, 0.349f, 1.00f);  // #5E8459 - Dark bamboo
        const ImVec4 AccentLight     = ImVec4(0.910f, 0.961f, 0.741f, 1.00f);  // #E8F5BD - Pale sunlight
        const ImVec4 AccentVeryLight = ImVec4(0.910f, 0.961f, 0.741f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.259f, 0.341f, 0.227f, 1.00f); // #42573A

        // Text - Pale sunlight through bamboo
        const ImVec4 TextBright  = ImVec4(0.910f, 0.961f, 0.741f, 1.00f);  // #E8F5BD - Pale sunlight
        const ImVec4 TextMuted   = ImVec4(0.780f, 0.918f, 0.733f, 1.00f);  // #C7EABB - Young bamboo
        const ImVec4 TextDim     = ImVec4(0.557f, 0.686f, 0.518f, 1.00f);  // #8EAF84 - Muted leaf
        const ImVec4 TextWhite   = ImVec4(0.937f, 0.976f, 0.812f, 1.00f);  // #EFF9CF - Bright sunlight

        // Borders - Bamboo-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.325f, 0.416f, 0.282f, 1.00f); // #536A48 - Stalk border
        const ImVec4 BorderWindow      = ImVec4(0.369f, 0.518f, 0.349f, 1.00f); // #5E8459 - Dark bamboo border
        const ImVec4 BorderTitle       = ImVec4(0.518f, 0.694f, 0.475f, 1.00f); // #84B179 - Bamboo leaf border
        const ImVec4 BorderTitleBottom = ImVec4(0.239f, 0.322f, 0.212f, 1.00f); // #3D5236 - Deep bamboo bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.125f, 0.173f, 0.114f, 1.00f);  // #202C1D
        const ImVec4 WindowSurround = ImVec4(0.098f, 0.137f, 0.090f, 1.00f);  // #192317

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.071f, 0.102f, 0.067f, 1.00f); // #121A11
        t.TitleBar.BackgroundColorActive   = ImVec4(0.071f, 0.102f, 0.067f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.071f, 0.102f, 0.067f, 0.85f);
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
        t.ContentPanel.TabInactive         = GroveShadow;
        t.ContentPanel.TabHovered          = BambooStalk;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = BambooForest;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = BambooLeaf;
        t.ContentPanel.ButtonHovered       = FreshShoot;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = GroveShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = GroveShadow;
        t.Window.TitleBarActive    = BambooStalk;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = BambooLeaf;
        t.Window.ButtonHovered     = FreshShoot;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = BambooGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = BambooLeaf;
        t.TrackTable.HeaderTextColor      = BambooForest;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = SunlitGrove;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = BambooForest;
        t.TrackTable.HeaderTextArtist     = BambooForest;
        t.TrackTable.HeaderTextAlbum      = BambooForest;
        t.TrackTable.HeaderTextExtension  = BambooForest;
        t.TrackTable.HeaderTextDuration   = BambooForest;

        t.TrackTable.RowDefault           = BambooForest;
        t.TrackTable.RowDefaultAlt        = GroveShadow;
        t.TrackTable.RowHovered           = BambooVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = BambooLeaf;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = BambooForest;
        t.TrackTable.TextPlaying          = BambooForest;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = BambooShade;
        t.TrackTable.ScrollbarGrab        = BambooLeaf;
        t.TrackTable.ScrollbarGrabHovered = FreshShoot;
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

        t.Visualizer.BackgroundColor       = BambooShade;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(BambooLeaf.x, BambooLeaf.y, BambooLeaf.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = BambooLeaf;
        t.Visualizer.SpectrumColorMid      = FreshShoot;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.910f, 0.961f, 0.741f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = BambooLeaf;
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
        t.AlbumArtBox.BackgroundColor         = GroveShadow;
        t.AlbumArtBox.BackgroundColorHovered  = BambooStalk;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.071f, 0.102f, 0.067f, 0.95f);
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
        t.SearchBar.rowHoverColor             = BambooStalk;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = GroveShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = BambooLeaf;
        t.PlayerBar.ButtonHovered             = FreshShoot;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = BambooLeaf;
        t.PlayerBar.ButtonPrimaryHovered      = FreshShoot;
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
        t.ContextMenu.HoverTextColor          = BambooForest;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic