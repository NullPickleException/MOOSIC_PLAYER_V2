//==============================================================================
// AmberChapelTheme.h
//==============================================================================
// Antique amber chapel - opulent, candlelit, sacred warmth
// Palette: #0c0b09 (crypt darkness), #2b2216 (aged oak), #5c4526 (antique amber),
//          #b08a3c (candle flame gold), #f2e6c7 (beeswax candlelight)
// 55% Crypt darkness and aged oak (#0c0b09 → #2b2216)
// 25% Antique amber and candle gold surfaces (#5c4526, #b08a3c)
// 10% Candle flame gold accent (#b08a3c)
// 10% Beeswax candlelight text (#f2e6c7)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateAmberChapelTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Antique amber chapel, candlelit sanctuary
        //==========================================================================

        // 55% - Crypt darkness and aged oak
        const ImVec4 CryptDarkness   = ImVec4(0.047f, 0.043f, 0.035f, 1.00f);  // #0c0b09 - Crypt darkness
        const ImVec4 AgedOak         = ImVec4(0.169f, 0.133f, 0.086f, 1.00f);  // #2b2216 - Aged oak pews
        const ImVec4 ChapelShadow    = ImVec4(0.220f, 0.176f, 0.114f, 1.00f);  // #382d1d - Chapel in shadow (library bg)
        const ImVec4 AmberNiche      = ImVec4(0.275f, 0.220f, 0.145f, 1.00f);  // #463825 - Amber-lit niche
        const ImVec4 CandleWall      = ImVec4(0.329f, 0.263f, 0.173f, 1.00f);  // #54432c - Candlelit wall

        const ImVec4 AmberGlow       = ImVec4(0.690f, 0.541f, 0.235f, 0.20f); // Candle flame glow
        const ImVec4 AmberVeryLight  = ImVec4(0.690f, 0.541f, 0.235f, 0.50f);
        const ImVec4 AmberSubtle     = ImVec4(0.690f, 0.541f, 0.235f, 0.10f);

        // 25% - Antique amber and candle gold surfaces
        const ImVec4 AntiqueAmber   = ImVec4(0.361f, 0.271f, 0.149f, 1.00f);  // #5c4526 - Antique amber
        const ImVec4 CandleGold     = ImVec4(0.690f, 0.541f, 0.235f, 1.00f);  // #b08a3c - Candle flame gold
        const ImVec4 PolishedBrass  = ImVec4(0.753f, 0.604f, 0.294f, 1.00f);  // #c09a4b - Polished brass

        // 10% - Candle flame gold accent
        const ImVec4 Accent          = ImVec4(0.690f, 0.541f, 0.235f, 1.00f);  // #b08a3c - Candle flame gold
        const ImVec4 AccentDark      = ImVec4(0.361f, 0.271f, 0.149f, 1.00f);  // #5c4526 - Antique amber
        const ImVec4 AccentDarker    = ImVec4(0.275f, 0.220f, 0.145f, 1.00f);  // #463825 - Deep amber
        const ImVec4 AccentLight     = ImVec4(0.753f, 0.604f, 0.294f, 1.00f);  // #c09a4b - Polished brass
        const ImVec4 AccentVeryLight = ImVec4(0.753f, 0.604f, 0.294f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.192f, 0.153f, 0.098f, 1.00f); // #312719

        // Text - Beeswax candlelight on parchment
        const ImVec4 TextBright  = ImVec4(0.949f, 0.902f, 0.780f, 1.00f);  // #f2e6c7 - Beeswax candlelight
        const ImVec4 TextMuted   = ImVec4(0.710f, 0.663f, 0.553f, 1.00f);  // #b5a98d - Aged parchment
        const ImVec4 TextDim     = ImVec4(0.463f, 0.427f, 0.349f, 1.00f);  // #766d59 - Faded ink
        const ImVec4 TextWhite   = ImVec4(0.965f, 0.929f, 0.839f, 1.00f);  // #f6edd6 - Pure candle flame

        // Borders - Amber-tinted aged oak
        const ImVec4 BorderSubtle      = ImVec4(0.275f, 0.220f, 0.145f, 1.00f); // #463825 - Amber niche border
        const ImVec4 BorderWindow      = ImVec4(0.361f, 0.271f, 0.149f, 1.00f); // #5c4526 - Antique amber border
        const ImVec4 BorderTitle       = ImVec4(0.690f, 0.541f, 0.235f, 1.00f); // #b08a3c - Candle gold border
        const ImVec4 BorderTitleBottom = ImVec4(0.275f, 0.220f, 0.145f, 1.00f); // #463825 - Deep amber bottom

        // Player Bar & Window Surround - Deepest chapel crypt
        const ImVec4 PlayerBarBg    = ImVec4(0.035f, 0.031f, 0.024f, 1.00f);  // #090806
        const ImVec4 WindowSurround = ImVec4(0.027f, 0.024f, 0.020f, 1.00f);  // #070605

        //==========================================================================
        // Title Bar - Chapel spire
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.020f, 0.016f, 0.012f, 1.00f); // #050403
        t.TitleBar.BackgroundColorActive   = ImVec4(0.020f, 0.016f, 0.012f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.020f, 0.016f, 0.012f, 0.85f);
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
        t.ContentPanel.TabInactive         = ChapelShadow;
        t.ContentPanel.TabHovered          = AmberNiche;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = CryptDarkness;  // Dark text on gold tab
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = AntiqueAmber;
        t.ContentPanel.ButtonHovered       = CandleGold;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Amber-lit sanctuary
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = ChapelShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = ChapelShadow;
        t.Window.TitleBarActive    = AmberNiche;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = AntiqueAmber;
        t.Window.ButtonHovered     = CandleGold;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = AmberGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Oak pews in candlelight
        //==========================================================================

        t.TrackTable.HeaderBackground     = AntiqueAmber;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = CandleWall;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = CryptDarkness;
        t.TrackTable.RowDefaultAlt        = ChapelShadow;
        t.TrackTable.RowHovered           = AmberVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = AntiqueAmber;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = CryptDarkness;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = AgedOak;
        t.TrackTable.ScrollbarGrab        = AntiqueAmber;
        t.TrackTable.ScrollbarGrabHovered = CandleGold;
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
        // Visualizer - Candle flames flickering
        //==========================================================================

        t.Visualizer.BackgroundColor       = AgedOak;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(AntiqueAmber.x, AntiqueAmber.y, AntiqueAmber.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: antique amber → candle gold → polished brass → beeswax ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = AntiqueAmber;
        t.Visualizer.SpectrumColorMid      = CandleGold;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.949f, 0.902f, 0.780f, 1.00f); // #f2e6c7 - Beeswax peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = AntiqueAmber;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Gilded oak frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = ChapelShadow;
        t.AlbumArtBox.BackgroundColorHovered  = AmberNiche;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Sacred sanctuary
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.020f, 0.016f, 0.012f, 0.95f);
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
        // Search Bar - Illuminated manuscript
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = AmberNiche;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = ChapelShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Chapel floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = AntiqueAmber;
        t.PlayerBar.ButtonHovered             = CandleGold;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = AntiqueAmber;
        t.PlayerBar.ButtonPrimaryHovered      = CandleGold;
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
        // Popup Menu - Amber-lit chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = CryptDarkness;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic