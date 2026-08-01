//==============================================================================
// CathedralTheme.h
//==============================================================================
// Gothic stone cathedral with stained glass and cold candlelight
// Palette: #0b0b0f (stone black), #2a2438 (amethyst shadow), #5a1f2b (blood ruby),
//          #a28b6e (aged brass), #e7e1d6 (parchment candlelight)
// 60% Cold stone near-black (#0b0b0f → #1e1a26)
// 30% Amethyst shadow and aged brass surfaces (#2a2438, #3d3548, #5a1f2b)
// 10% Aged brass accent (#a28b6e)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCathedralTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Gothic cathedral stone, brass & stained glass
        //==========================================================================

        // 60% - Cold stone near-black
        const ImVec4 CryptDeep     = ImVec4(0.043f, 0.043f, 0.059f, 1.00f);  // #0b0b0f - Deepest crypt
        const ImVec4 StoneWall     = ImVec4(0.067f, 0.067f, 0.086f, 1.00f);  // #111116 - Cold stone wall
        const ImVec4 NaveShadow    = ImVec4(0.118f, 0.102f, 0.149f, 1.00f);  // #1e1a26 - Nave in shadow (library bg)
        const ImVec4 ArchStone     = ImVec4(0.165f, 0.141f, 0.220f, 1.00f);  // #2a2438 - Gothic arch stone
        const ImVec4 ChoirStone    = ImVec4(0.204f, 0.176f, 0.255f, 1.00f);  // #342d41 - Choir loft stone

        const ImVec4 CathedralGlow       = ImVec4(0.635f, 0.545f, 0.431f, 0.20f); // Brass candle glow
        const ImVec4 CathedralVeryLight  = ImVec4(0.635f, 0.545f, 0.431f, 0.50f);
        const ImVec4 CathedralSubtle     = ImVec4(0.635f, 0.545f, 0.431f, 0.10f);

        // 30% - Amethyst shadow, blood ruby, and aged brass surfaces
        const ImVec4 AmethystDark = ImVec4(0.165f, 0.141f, 0.220f, 1.00f);  // #2a2438 - Amethyst shadow
        const ImVec4 BloodRuby    = ImVec4(0.353f, 0.122f, 0.169f, 1.00f);  // #5a1f2b - Blood ruby
        const ImVec4 StoneLit     = ImVec4(0.239f, 0.208f, 0.282f, 1.00f);  // #3d3548 - Lit stone

        // 10% - Aged brass accent
        const ImVec4 Accent          = ImVec4(0.635f, 0.545f, 0.431f, 1.00f);  // #a28b6e - Aged brass
        const ImVec4 AccentDark      = ImVec4(0.510f, 0.435f, 0.341f, 1.00f);  // #826f57 - Dark brass
        const ImVec4 AccentDarker    = ImVec4(0.384f, 0.325f, 0.251f, 1.00f);  // #625340 - Tarnished brass
        const ImVec4 AccentLight     = ImVec4(0.741f, 0.647f, 0.529f, 1.00f);  // #bda587 - Polished brass
        const ImVec4 AccentVeryLight = ImVec4(0.741f, 0.647f, 0.529f, 0.50f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.102f, 0.090f, 0.129f, 1.00f); // #1a1721

        // Text - Warm parchment candlelight
        const ImVec4 TextBright  = ImVec4(0.906f, 0.882f, 0.839f, 1.00f);  // #e7e1d6 - Parchment candlelight
        const ImVec4 TextMuted   = ImVec4(0.698f, 0.675f, 0.627f, 1.00f);  // #b2aca0 - Fading candlelight
        const ImVec4 TextDim     = ImVec4(0.463f, 0.439f, 0.404f, 1.00f);  // #767067 - Shadowed inscription
        const ImVec4 TextWhite   = ImVec4(0.937f, 0.918f, 0.878f, 1.00f);  // #efeae0 - Pure candle flame

        // Borders - Blood ruby and aged brass
        const ImVec4 BorderSubtle      = ImVec4(0.204f, 0.176f, 0.255f, 1.00f); // #342d41 - Amethyst iron
        const ImVec4 BorderWindow      = ImVec4(0.353f, 0.122f, 0.169f, 1.00f); // #5a1f2b - Blood ruby border
        const ImVec4 BorderTitle       = ImVec4(0.635f, 0.545f, 0.431f, 1.00f); // #a28b6e - Aged brass border
        const ImVec4 BorderTitleBottom = ImVec4(0.384f, 0.325f, 0.251f, 1.00f); // #625340 - Dark brass bottom

        // Player Bar & Window Surround - Darkest cathedral corners
        const ImVec4 PlayerBarBg    = ImVec4(0.031f, 0.031f, 0.043f, 1.00f);  // #08080b
        const ImVec4 WindowSurround = ImVec4(0.024f, 0.024f, 0.035f, 1.00f);  // #060609

        //==========================================================================
        // Title Bar - Cathedral spire peak
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.016f, 0.016f, 0.024f, 1.00f); // #040406
        t.TitleBar.BackgroundColorActive   = ImVec4(0.016f, 0.016f, 0.024f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.016f, 0.016f, 0.024f, 0.85f);
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
        t.ContentPanel.TabInactive         = NaveShadow;
        t.ContentPanel.TabHovered          = ArchStone;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = CryptDeep;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = BloodRuby;
        t.ContentPanel.ButtonHovered       = AmethystDark;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Blood ruby and brass frame the stone library
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = NaveShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = NaveShadow;
        t.Window.TitleBarActive    = ArchStone;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = BloodRuby;
        t.Window.ButtonHovered     = AmethystDark;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = CathedralGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = BloodRuby;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = ChoirStone;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = CryptDeep;
        t.TrackTable.RowDefaultAlt        = NaveShadow;
        t.TrackTable.RowHovered           = CathedralVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = BloodRuby;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = CryptDeep;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = StoneWall;
        t.TrackTable.ScrollbarGrab        = BloodRuby;
        t.TrackTable.ScrollbarGrabHovered = AmethystDark;
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
        // Visualizer - Candlelight through stained glass
        //==========================================================================

        t.Visualizer.BackgroundColor       = StoneWall;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(BloodRuby.x, BloodRuby.y, BloodRuby.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: blood ruby → amethyst → aged brass → parchment ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = BloodRuby;
        t.Visualizer.SpectrumColorMid      = AmethystDark;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.906f, 0.882f, 0.839f, 1.00f); // #e7e1d6 - Candlelight peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = BloodRuby;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Brass frame with blood ruby glow
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = NaveShadow;
        t.AlbumArtBox.BackgroundColorHovered  = ArchStone;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(BloodRuby.x, BloodRuby.y, BloodRuby.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Darkest cathedral sanctuary
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.016f, 0.016f, 0.024f, 0.95f);
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
        t.SearchBar.rowHoverColor             = ArchStone;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = NaveShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Cathedral floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = BloodRuby;
        t.PlayerBar.ButtonHovered             = AmethystDark;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = BloodRuby;
        t.PlayerBar.ButtonPrimaryHovered      = AmethystDark;
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
        t.ContextMenu.HoverTextColor          = CryptDeep;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic