//==============================================================================
// AutumnWarmthTheme.h
//==============================================================================
// Autumn warmth - rich harvest golds, burnt oranges, and deep russet tones
// Palette: #8B3A0F (russet earth), #C44B1A (burnt sienna), #D4782F (harvest gold),
//          #E8A84C (golden maple), #F5D78A (autumn sunlight)
// 60% Rich earth tones and deep russet (#4A1C0A → #6B2F15)
// 25% Burnt sienna and harvest surfaces (#C44B1A, #D4782F)
// 10% Golden maple accent (#E8A84C)
// 5% Autumn sunlight text (#F5D78A)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateAutumnWarmthTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Autumn warmth, harvest golds and russet tones
        //==========================================================================

        // 60% - Rich earth tones and deep russet
        const ImVec4 RussetEarth    = ImVec4(0.290f, 0.110f, 0.039f, 1.00f);  // #4A1C0A - Deep russet earth
        const ImVec4 DarkBark       = ImVec4(0.420f, 0.184f, 0.082f, 1.00f);  // #6B2F15 - Dark bark
        const ImVec4 AutumnShadow   = ImVec4(0.545f, 0.227f, 0.059f, 1.00f);  // #8B3A0F - Autumn shadow (library bg)
        const ImVec4 RichSoil       = ImVec4(0.620f, 0.290f, 0.094f, 1.00f);  // #9E4A18 - Rich soil
        const ImVec4 SpiceBrown     = ImVec4(0.710f, 0.365f, 0.125f, 1.00f);  // #B55D20 - Spice brown

        const ImVec4 AutumnGlow       = ImVec4(0.910f, 0.659f, 0.306f, 0.15f); // Golden maple glow
        const ImVec4 AutumnVeryLight  = ImVec4(0.910f, 0.659f, 0.306f, 0.40f);
        const ImVec4 AutumnSubtle     = ImVec4(0.910f, 0.659f, 0.306f, 0.08f);

        // 25% - Burnt sienna and harvest surfaces
        const ImVec4 BurntSienna    = ImVec4(0.769f, 0.294f, 0.102f, 1.00f);  // #C44B1A - Burnt sienna
        const ImVec4 HarvestGold    = ImVec4(0.831f, 0.471f, 0.184f, 1.00f);  // #D4782F - Harvest gold
        const ImVec4 GoldenMaple    = ImVec4(0.910f, 0.659f, 0.306f, 1.00f);  // #E8A84C - Golden maple

        // 10% - Golden maple accent
        const ImVec4 Accent          = ImVec4(0.910f, 0.659f, 0.306f, 1.00f);  // #E8A84C - Golden maple
        const ImVec4 AccentDark      = ImVec4(0.831f, 0.471f, 0.184f, 1.00f);  // #D4782F - Harvest gold
        const ImVec4 AccentDarker    = ImVec4(0.769f, 0.294f, 0.102f, 1.00f);  // #C44B1A - Burnt sienna
        const ImVec4 AccentLight     = ImVec4(0.961f, 0.843f, 0.541f, 1.00f);  // #F5D78A - Autumn sunlight
        const ImVec4 AccentVeryLight = ImVec4(0.961f, 0.843f, 0.541f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.475f, 0.212f, 0.082f, 1.00f); // #793615

        // Text - Autumn sunlight and warm tones
        const ImVec4 TextBright  = ImVec4(0.961f, 0.843f, 0.541f, 1.00f);  // #F5D78A - Autumn sunlight
        const ImVec4 TextMuted   = ImVec4(0.875f, 0.710f, 0.475f, 1.00f);  // #DFB579 - Warm amber
        const ImVec4 TextDim     = ImVec4(0.690f, 0.490f, 0.318f, 1.00f);  // #B07D51 - Muted spice
        const ImVec4 TextWhite   = ImVec4(0.984f, 0.929f, 0.780f, 1.00f);  // #FBEDC7 - Cream light

        // Borders - Warm wood tones
        const ImVec4 BorderSubtle      = ImVec4(0.620f, 0.290f, 0.094f, 1.00f); // #9E4A18 - Rich soil border
        const ImVec4 BorderWindow      = ImVec4(0.769f, 0.294f, 0.102f, 1.00f); // #C44B1A - Burnt sienna border
        const ImVec4 BorderTitle       = ImVec4(0.910f, 0.659f, 0.306f, 1.00f); // #E8A84C - Golden border
        const ImVec4 BorderTitleBottom = ImVec4(0.290f, 0.110f, 0.039f, 1.00f); // #4A1C0A - Russet bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.200f, 0.075f, 0.027f, 1.00f);  // #331307
        const ImVec4 WindowSurround = ImVec4(0.153f, 0.059f, 0.020f, 1.00f);  // #270F05

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.110f, 0.039f, 0.012f, 1.00f); // #1C0A03
        t.TitleBar.BackgroundColorActive   = ImVec4(0.110f, 0.039f, 0.012f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.110f, 0.039f, 0.012f, 0.85f);
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
        t.ContentPanel.TabInactive         = AutumnShadow;
        t.ContentPanel.TabHovered          = RichSoil;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = BurntSienna;
        t.ContentPanel.ButtonHovered       = HarvestGold;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = AutumnShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = AutumnShadow;
        t.Window.TitleBarActive    = RichSoil;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = BurntSienna;
        t.Window.ButtonHovered     = HarvestGold;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = AutumnGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = BurntSienna;
        t.TrackTable.HeaderTextColor      = TextWhite;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = SpiceBrown;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextWhite;
        t.TrackTable.HeaderTextArtist     = TextWhite;
        t.TrackTable.HeaderTextAlbum      = TextWhite;
        t.TrackTable.HeaderTextExtension  = TextWhite;
        t.TrackTable.HeaderTextDuration   = TextWhite;

        t.TrackTable.RowDefault           = RussetEarth;
        t.TrackTable.RowDefaultAlt        = AutumnShadow;
        t.TrackTable.RowHovered           = AutumnVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = BurntSienna;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = DarkBark;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = DarkBark;
        t.TrackTable.ScrollbarGrab        = BurntSienna;
        t.TrackTable.ScrollbarGrabHovered = HarvestGold;
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

        t.Visualizer.BackgroundColor       = DarkBark;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(BurntSienna.x, BurntSienna.y, BurntSienna.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = BurntSienna;
        t.Visualizer.SpectrumColorMid      = HarvestGold;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.961f, 0.843f, 0.541f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = BurntSienna;
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
        t.AlbumArtBox.BackgroundColor         = AutumnShadow;
        t.AlbumArtBox.BackgroundColorHovered  = RichSoil;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.110f, 0.039f, 0.012f, 0.95f);
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
        t.SearchBar.rowHoverColor             = RichSoil;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = AutumnShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = BurntSienna;
        t.PlayerBar.ButtonHovered             = HarvestGold;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = BurntSienna;
        t.PlayerBar.ButtonPrimaryHovered      = HarvestGold;
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
        t.ContextMenu.HoverTextColor          = DarkBark;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic