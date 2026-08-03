//==============================================================================
// OliveTheme.h
//==============================================================================
// Olive grove - Mediterranean earth, silver-green leaves, warm stone
// Palette: #5F6F52 (olive leaf), #A9B388 (silver sage), #FEFAE0 (warm parchment),
//          #B99470 (terra cotta)
// 60% Darkened olive grove (#3D4A35 → #4F5E44)
// 25% Olive leaf and silver sage surfaces (#5F6F52, #A9B388)
// 10% Silver sage accent (#A9B388)
// 5% Warm parchment text (#FEFAE0)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateOliveTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Mediterranean olive grove
        //==========================================================================

        // 60% - Darkened olive grove
        const ImVec4 OliveGrove     = ImVec4(0.239f, 0.290f, 0.208f, 1.00f);  // #3D4A35 - Olive grove earth
        const ImVec4 GroveShadow    = ImVec4(0.310f, 0.369f, 0.267f, 1.00f);  // #4F5E44 - Grove shadow
        const ImVec4 OliveShade     = ImVec4(0.349f, 0.412f, 0.302f, 1.00f);  // #59694D - Olive shade (library bg)
        const ImVec4 SilverLeaf     = ImVec4(0.388f, 0.455f, 0.337f, 1.00f);  // #637456 - Silver leaf
        const ImVec4 TerraCotta     = ImVec4(0.725f, 0.580f, 0.439f, 1.00f);  // #B99470 - Terra cotta earth

        const ImVec4 OliveGlow       = ImVec4(0.663f, 0.702f, 0.533f, 0.15f); // Silver sage glow
        const ImVec4 OliveVeryLight  = ImVec4(0.663f, 0.702f, 0.533f, 0.45f);
        const ImVec4 OliveSubtle     = ImVec4(0.663f, 0.702f, 0.533f, 0.08f);

        // 25% - Olive leaf and silver sage surfaces
        const ImVec4 OliveLeaf      = ImVec4(0.373f, 0.435f, 0.322f, 1.00f);  // #5F6F52 - Olive leaf
        const ImVec4 SilverSage     = ImVec4(0.663f, 0.702f, 0.533f, 1.00f);  // #A9B388 - Silver sage
        const ImVec4 WarmParchment  = ImVec4(0.996f, 0.980f, 0.878f, 1.00f);  // #FEFAE0 - Warm parchment

        // 10% - Silver sage accent
        const ImVec4 Accent          = ImVec4(0.663f, 0.702f, 0.533f, 1.00f);  // #A9B388 - Silver sage
        const ImVec4 AccentDark      = ImVec4(0.373f, 0.435f, 0.322f, 1.00f);  // #5F6F52 - Olive leaf
        const ImVec4 AccentDarker    = ImVec4(0.310f, 0.369f, 0.267f, 1.00f);  // #4F5E44 - Dark olive
        const ImVec4 AccentLight     = ImVec4(0.996f, 0.980f, 0.878f, 1.00f);  // #FEFAE0 - Warm parchment
        const ImVec4 AccentVeryLight = ImVec4(0.996f, 0.980f, 0.878f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.329f, 0.388f, 0.282f, 1.00f); // #546348

        // Text - Warm parchment and olive tones
        const ImVec4 TextBright  = ImVec4(0.996f, 0.980f, 0.878f, 1.00f);  // #FEFAE0 - Warm parchment
        const ImVec4 TextMuted   = ImVec4(0.725f, 0.580f, 0.439f, 1.00f);  // #B99470 - Terra cotta
        const ImVec4 TextDim     = ImVec4(0.502f, 0.553f, 0.435f, 1.00f);  // #808D6F - Muted olive
        const ImVec4 TextWhite   = ImVec4(1.000f, 0.988f, 0.914f, 1.00f);  // #FFFCE9 - Pure parchment

        // Borders - Olive and terra cotta
        const ImVec4 BorderSubtle      = ImVec4(0.388f, 0.455f, 0.337f, 1.00f); // #637456 - Silver leaf border
        const ImVec4 BorderWindow      = ImVec4(0.373f, 0.435f, 0.322f, 1.00f); // #5F6F52 - Olive leaf border
        const ImVec4 BorderTitle       = ImVec4(0.663f, 0.702f, 0.533f, 1.00f); // #A9B388 - Silver sage border
        const ImVec4 BorderTitleBottom = ImVec4(0.310f, 0.369f, 0.267f, 1.00f); // #4F5E44 - Dark olive bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.176f, 0.216f, 0.153f, 1.00f);  // #2D3727
        const ImVec4 WindowSurround = ImVec4(0.141f, 0.173f, 0.122f, 1.00f);  // #242C1F

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.106f, 0.129f, 0.090f, 1.00f); // #1B2117
        t.TitleBar.BackgroundColorActive   = ImVec4(0.106f, 0.129f, 0.090f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.106f, 0.129f, 0.090f, 0.85f);
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
        t.ContentPanel.TabInactive         = OliveShade;
        t.ContentPanel.TabHovered          = SilverLeaf;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = OliveGrove;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = OliveLeaf;
        t.ContentPanel.ButtonHovered       = SilverSage;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = OliveShade;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = OliveShade;
        t.Window.TitleBarActive    = SilverLeaf;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = OliveLeaf;
        t.Window.ButtonHovered     = SilverSage;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = OliveGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = OliveLeaf;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = TerraCotta;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = OliveGrove;
        t.TrackTable.RowDefaultAlt        = OliveShade;
        t.TrackTable.RowHovered           = OliveVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = OliveLeaf;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = OliveGrove;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = GroveShadow;
        t.TrackTable.ScrollbarGrab        = OliveLeaf;
        t.TrackTable.ScrollbarGrabHovered = SilverSage;
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

        t.Visualizer.BackgroundColor       = GroveShadow;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(OliveLeaf.x, OliveLeaf.y, OliveLeaf.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = OliveLeaf;
        t.Visualizer.SpectrumColorMid      = SilverSage;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.996f, 0.980f, 0.878f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = OliveLeaf;
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
        t.AlbumArtBox.BackgroundColor         = OliveShade;
        t.AlbumArtBox.BackgroundColorHovered  = SilverLeaf;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.106f, 0.129f, 0.090f, 0.95f);
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
        t.SearchBar.rowHoverColor             = SilverLeaf;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = OliveShade;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = OliveLeaf;
        t.PlayerBar.ButtonHovered             = SilverSage;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = OliveLeaf;
        t.PlayerBar.ButtonPrimaryHovered      = SilverSage;
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
        t.ContextMenu.HoverTextColor          = OliveGrove;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic