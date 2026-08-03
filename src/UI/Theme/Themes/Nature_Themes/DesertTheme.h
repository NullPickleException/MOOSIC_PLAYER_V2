//==============================================================================
// DesertTheme.h
//==============================================================================
// Warm desert sands - sun-bleached earth, warm dunes, pale sky
// Palette: #F6F0F0 (desert sky), #F2E2B1 (sunlit sand), #D5C7A3 (warm dune),
//          #BDB395 (weathered stone)
// 60% Darkened sand and weathered stone (#8A7D6A → #A89880)
// 25% Warm dune and sunlit sand surfaces (#D5C7A3, #F2E2B1)
// 10% Sunlit sand accent (#F2E2B1)
// 5% Desert sky text (#F6F0F0)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateDesertTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Desert sands, warm and timeless
        //==========================================================================

        // 60% - Darkened sand and weathered stone
        const ImVec4 DeepSand       = ImVec4(0.541f, 0.490f, 0.416f, 1.00f);  // #8A7D6A - Deep sand
        const ImVec4 WeatheredStone = ImVec4(0.659f, 0.627f, 0.584f, 1.00f);  // #A89880 - Weathered stone
        const ImVec4 DuneShadow     = ImVec4(0.702f, 0.671f, 0.627f, 1.00f);  // #B3ABA0 - Dune shadow (library bg)
        const ImVec4 SandDrift      = ImVec4(0.741f, 0.702f, 0.639f, 1.00f);  // #BDB395 - Sand drift
        const ImVec4 WarmDune       = ImVec4(0.835f, 0.780f, 0.639f, 1.00f);  // #D5C7A3 - Warm dune

        const ImVec4 DesertGlow       = ImVec4(0.949f, 0.886f, 0.694f, 0.15f); // Sunlit sand glow
        const ImVec4 DesertVeryLight  = ImVec4(0.949f, 0.886f, 0.694f, 0.45f);
        const ImVec4 DesertSubtle     = ImVec4(0.949f, 0.886f, 0.694f, 0.08f);

        // 25% - Warm dune and sunlit sand surfaces
        const ImVec4 SandStone      = ImVec4(0.741f, 0.702f, 0.639f, 1.00f);  // #BDB395 - Sand stone
        const ImVec4 SunlitSand     = ImVec4(0.949f, 0.886f, 0.694f, 1.00f);  // #F2E2B1 - Sunlit sand
        const ImVec4 BrightDune     = ImVec4(0.957f, 0.902f, 0.737f, 1.00f);  // #F4E6BC - Bright dune

        // 10% - Sunlit sand accent
        const ImVec4 Accent          = ImVec4(0.949f, 0.886f, 0.694f, 1.00f);  // #F2E2B1 - Sunlit sand
        const ImVec4 AccentDark      = ImVec4(0.835f, 0.780f, 0.639f, 1.00f);  // #D5C7A3 - Warm dune
        const ImVec4 AccentDarker    = ImVec4(0.741f, 0.702f, 0.639f, 1.00f);  // #BDB395 - Sand stone
        const ImVec4 AccentLight     = ImVec4(0.965f, 0.941f, 0.941f, 1.00f);  // #F6F0F0 - Desert sky
        const ImVec4 AccentVeryLight = ImVec4(0.965f, 0.941f, 0.941f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.682f, 0.651f, 0.608f, 1.00f); // #AEA69B

        // Text - Desert sky and deep earth
        const ImVec4 TextBright  = ImVec4(0.965f, 0.941f, 0.941f, 1.00f);  // #F6F0F0 - Desert sky
        const ImVec4 TextMuted   = ImVec4(0.835f, 0.780f, 0.639f, 1.00f);  // #D5C7A3 - Warm sand
        const ImVec4 TextDim     = ImVec4(0.659f, 0.627f, 0.584f, 1.00f);  // #A89880 - Weathered stone
        const ImVec4 TextWhite   = ImVec4(0.976f, 0.957f, 0.957f, 1.00f);  // #F9F4F4 - Pure sky

        // Borders - Sand-tinted stone
        const ImVec4 BorderSubtle      = ImVec4(0.741f, 0.702f, 0.639f, 1.00f); // #BDB395 - Sand border
        const ImVec4 BorderWindow      = ImVec4(0.659f, 0.627f, 0.584f, 1.00f); // #A89880 - Stone border
        const ImVec4 BorderTitle       = ImVec4(0.949f, 0.886f, 0.694f, 1.00f); // #F2E2B1 - Sunlit border
        const ImVec4 BorderTitleBottom = ImVec4(0.541f, 0.490f, 0.416f, 1.00f); // #8A7D6A - Deep sand bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.400f, 0.361f, 0.306f, 1.00f);  // #665C4E
        const ImVec4 WindowSurround = ImVec4(0.322f, 0.290f, 0.247f, 1.00f);  // #524A3F

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.243f, 0.220f, 0.188f, 1.00f); // #3E3830
        t.TitleBar.BackgroundColorActive   = ImVec4(0.243f, 0.220f, 0.188f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.243f, 0.220f, 0.188f, 0.85f);
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
        t.ContentPanel.TabInactive         = DuneShadow;
        t.ContentPanel.TabHovered          = SandDrift;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = DeepSand;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = SandStone;
        t.ContentPanel.ButtonHovered       = SunlitSand;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = DuneShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = DuneShadow;
        t.Window.TitleBarActive    = SandDrift;
        t.Window.HeaderText        = DeepSand;
        t.Window.TextPrimary       = DeepSand;
        t.Window.TextSecondary     = TextDim;
        t.Window.TextDisabled      = TextMuted;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = SandStone;
        t.Window.ButtonHovered     = SunlitSand;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = DesertGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = SandStone;
        t.TrackTable.HeaderTextColor      = DeepSand;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = WarmDune;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = DeepSand;
        t.TrackTable.HeaderTextArtist     = DeepSand;
        t.TrackTable.HeaderTextAlbum      = DeepSand;
        t.TrackTable.HeaderTextExtension  = DeepSand;
        t.TrackTable.HeaderTextDuration   = DeepSand;

        t.TrackTable.RowDefault           = DeepSand;
        t.TrackTable.RowDefaultAlt        = DuneShadow;
        t.TrackTable.RowHovered           = DesertVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = SandStone;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = DeepSand;
        t.TrackTable.TextPlaying          = DeepSand;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = WeatheredStone;
        t.TrackTable.ScrollbarGrab        = SandStone;
        t.TrackTable.ScrollbarGrabHovered = SunlitSand;
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

        t.Visualizer.BackgroundColor       = WeatheredStone;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(SandStone.x, SandStone.y, SandStone.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = SandStone;
        t.Visualizer.SpectrumColorMid      = SunlitSand;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.965f, 0.941f, 0.941f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = SandStone;
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
        t.AlbumArtBox.BackgroundColor         = DuneShadow;
        t.AlbumArtBox.BackgroundColorHovered  = SandDrift;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.20f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.243f, 0.220f, 0.188f, 0.95f);
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

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = SandDrift;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = DuneShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = SandStone;
        t.PlayerBar.ButtonHovered             = SunlitSand;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = SandStone;
        t.PlayerBar.ButtonPrimaryHovered      = SunlitSand;
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
        t.ContextMenu.HoverTextColor          = DeepSand;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic