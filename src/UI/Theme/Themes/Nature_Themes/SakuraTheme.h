//==============================================================================
// SakuraTheme.h
//==============================================================================
// Cherry blossom - delicate pink petals, warm wood, spring romance
// Palette: #643843 (dark cherry bark), #99627A (mauve blossom), #C88EA7 (pink sakura),
//          #E7CBCB (pale petal)
// 60% Dark cherry bark (#643843 → #4D2B34)
// 25% Mauve blossom and pink sakura surfaces (#99627A, #C88EA7)
// 10% Pink sakura accent (#C88EA7)
// 5% Pale petal text (#E7CBCB)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateSakuraTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Cherry blossom, spring romance
        //==========================================================================

        // 60% - Dark cherry bark (darkened)
        const ImVec4 CherryBark     = ImVec4(0.302f, 0.220f, 0.263f, 1.00f);  // #4D3843 - Dark cherry bark
        const ImVec4 BarkShadow     = ImVec4(0.349f, 0.255f, 0.302f, 1.00f);  // #59414D - Bark shadow
        const ImVec4 PetalShade     = ImVec4(0.392f, 0.290f, 0.341f, 1.00f);  // #644A57 - Petal shade (library bg)
        const ImVec4 BranchWood     = ImVec4(0.435f, 0.325f, 0.380f, 1.00f);  // #6F5361 - Branch wood
        const ImVec4 BlossomShadow  = ImVec4(0.478f, 0.361f, 0.420f, 1.00f);  // #7A5C6B - Blossom shadow

        const ImVec4 SakuraGlow       = ImVec4(0.784f, 0.557f, 0.655f, 0.15f); // Pink sakura glow
        const ImVec4 SakuraVeryLight  = ImVec4(0.784f, 0.557f, 0.655f, 0.45f);
        const ImVec4 SakuraSubtle     = ImVec4(0.784f, 0.557f, 0.655f, 0.08f);

        // 25% - Mauve blossom and pink sakura surfaces
        const ImVec4 MauveBlossom   = ImVec4(0.600f, 0.384f, 0.478f, 1.00f);  // #99627A - Mauve blossom
        const ImVec4 PinkSakura     = ImVec4(0.784f, 0.557f, 0.655f, 1.00f);  // #C88EA7 - Pink sakura
        const ImVec4 LightPetal     = ImVec4(0.831f, 0.627f, 0.714f, 1.00f);  // #D4A0B6 - Light petal

        // 10% - Pink sakura accent
        const ImVec4 Accent          = ImVec4(0.784f, 0.557f, 0.655f, 1.00f);  // #C88EA7 - Pink sakura
        const ImVec4 AccentDark      = ImVec4(0.600f, 0.384f, 0.478f, 1.00f);  // #99627A - Mauve blossom
        const ImVec4 AccentDarker    = ImVec4(0.392f, 0.220f, 0.263f, 1.00f);  // #643843 - Cherry bark
        const ImVec4 AccentLight     = ImVec4(0.906f, 0.796f, 0.796f, 1.00f);  // #E7CBCB - Pale petal
        const ImVec4 AccentVeryLight = ImVec4(0.906f, 0.796f, 0.796f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.369f, 0.271f, 0.318f, 1.00f); // #5E4551

        // Text - Pale petals
        const ImVec4 TextBright  = ImVec4(0.906f, 0.796f, 0.796f, 1.00f);  // #E7CBCB - Pale petal
        const ImVec4 TextMuted   = ImVec4(0.718f, 0.624f, 0.635f, 1.00f);  // #B79FA2 - Faded petal
        const ImVec4 TextDim     = ImVec4(0.502f, 0.431f, 0.443f, 1.00f);  // #806E71 - Dried petal
        const ImVec4 TextWhite   = ImVec4(0.933f, 0.847f, 0.847f, 1.00f);  // #EED8D8 - Pure petal white

        // Borders - Sakura-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.435f, 0.325f, 0.380f, 1.00f); // #6F5361 - Branch border
        const ImVec4 BorderWindow      = ImVec4(0.392f, 0.220f, 0.263f, 1.00f); // #643843 - Cherry bark border
        const ImVec4 BorderTitle       = ImVec4(0.784f, 0.557f, 0.655f, 1.00f); // #C88EA7 - Pink sakura border
        const ImVec4 BorderTitleBottom = ImVec4(0.302f, 0.220f, 0.263f, 1.00f); // #4D3843 - Dark bark bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.212f, 0.153f, 0.184f, 1.00f);  // #36272F
        const ImVec4 WindowSurround = ImVec4(0.169f, 0.122f, 0.149f, 1.00f);  // #2B1F26

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.125f, 0.090f, 0.110f, 1.00f); // #20171C
        t.TitleBar.BackgroundColorActive   = ImVec4(0.125f, 0.090f, 0.110f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.125f, 0.090f, 0.110f, 0.85f);
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
        t.ContentPanel.TabInactive         = PetalShade;
        t.ContentPanel.TabHovered          = BranchWood;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = CherryBark;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = MauveBlossom;
        t.ContentPanel.ButtonHovered       = PinkSakura;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = PetalShade;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = PetalShade;
        t.Window.TitleBarActive    = BranchWood;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = MauveBlossom;
        t.Window.ButtonHovered     = PinkSakura;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = SakuraGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = MauveBlossom;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = BlossomShadow;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = CherryBark;
        t.TrackTable.RowDefaultAlt        = PetalShade;
        t.TrackTable.RowHovered           = SakuraVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = MauveBlossom;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = CherryBark;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = BarkShadow;
        t.TrackTable.ScrollbarGrab        = MauveBlossom;
        t.TrackTable.ScrollbarGrabHovered = PinkSakura;
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

        t.Visualizer.BackgroundColor       = BarkShadow;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(MauveBlossom.x, MauveBlossom.y, MauveBlossom.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = MauveBlossom;
        t.Visualizer.SpectrumColorMid      = PinkSakura;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.906f, 0.796f, 0.796f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = MauveBlossom;
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
        t.AlbumArtBox.BackgroundColor         = PetalShade;
        t.AlbumArtBox.BackgroundColorHovered  = BranchWood;
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

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.125f, 0.090f, 0.110f, 0.95f);
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

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = BranchWood;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = PetalShade;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = MauveBlossom;
        t.PlayerBar.ButtonHovered             = PinkSakura;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = MauveBlossom;
        t.PlayerBar.ButtonPrimaryHovered      = PinkSakura;
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
        t.ContextMenu.HoverTextColor          = CherryBark;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic