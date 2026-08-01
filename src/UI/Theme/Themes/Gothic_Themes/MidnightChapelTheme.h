//==============================================================================
// MidnightChapelTheme.h
//==============================================================================
// Blue gothic church at midnight - rain on stained glass, sapphire moonlight
// 60% Deep midnight blue (#0D1018 → #30384A)
// 30% Slate blue stone and rain-washed surfaces (#46526A, #5C6985, #7887A5)
// 10% Sapphire moonlight accent (#6F5AFF)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateMidnightChapelTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Midnight chapel with sapphire stained glass
        //==========================================================================

        // 60% - Deep midnight blue
        const ImVec4 ChapelDeep     = ImVec4(0.051f, 0.063f, 0.094f, 1.00f);  // #0D1018 - Chapel crypt
        const ImVec4 ChapelWall     = ImVec4(0.078f, 0.098f, 0.137f, 1.00f);  // #141923 - Stone wall in darkness
        const ImVec4 ChapelNave     = ImVec4(0.110f, 0.133f, 0.188f, 1.00f);  // #1C2230 - Nave shadow (library bg)
        const ImVec4 ChapelArch     = ImVec4(0.145f, 0.173f, 0.235f, 1.00f);  // #252C3C - Gothic arch
        const ImVec4 ChapelChoir    = ImVec4(0.188f, 0.220f, 0.290f, 1.00f);  // #30384A - Moonlit choir

        const ImVec4 ChapelGlow       = ImVec4(0.435f, 0.353f, 1.000f, 0.20f); // Sapphire glass glow
        const ImVec4 ChapelVeryLight  = ImVec4(0.435f, 0.353f, 1.000f, 0.50f);
        const ImVec4 ChapelSubtle     = ImVec4(0.435f, 0.353f, 1.000f, 0.10f);

        // 30% - Slate blue stone and rain-washed surfaces
        const ImVec4 SlateDark    = ImVec4(0.275f, 0.322f, 0.416f, 1.00f);  // #46526A - Rain-darkened slate
        const ImVec4 SlateMid     = ImVec4(0.361f, 0.412f, 0.522f, 1.00f);  // #5C6985 - Wet stone
        const ImVec4 SlateLit     = ImVec4(0.471f, 0.529f, 0.647f, 1.00f);  // #7887A5 - Moonlit stone

        // 10% - Sapphire moonlight accent
        const ImVec4 Accent          = ImVec4(0.435f, 0.353f, 1.000f, 1.00f);  // #6F5AFF - Sapphire stained glass
        const ImVec4 AccentDark      = ImVec4(0.349f, 0.271f, 0.808f, 1.00f);  // #5945CE - Deep sapphire
        const ImVec4 AccentDarker    = ImVec4(0.263f, 0.192f, 0.608f, 1.00f);  // #43319B - Shadowed glass
        const ImVec4 AccentLight     = ImVec4(0.561f, 0.490f, 1.000f, 1.00f);  // #8F7DFF - Bright moonlight through glass
        const ImVec4 AccentVeryLight = ImVec4(0.561f, 0.490f, 1.000f, 0.50f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.094f, 0.114f, 0.161f, 1.00f); // #181D29

        // Text - Cool moonlight through rain
        const ImVec4 TextBright  = ImVec4(0.933f, 0.945f, 0.969f, 1.00f);  // #EEF1F7 - Moonlight on stone
        const ImVec4 TextMuted   = ImVec4(0.718f, 0.753f, 0.812f, 1.00f);  // #B7C0CF - Rain-blurred light
        const ImVec4 TextDim     = ImVec4(0.439f, 0.478f, 0.549f, 1.00f);  // #707A8C - Shadowed corner
        const ImVec4 TextWhite   = ImVec4(0.957f, 0.965f, 0.980f, 1.00f);  // #F4F6FA - Pure moonbeam

        // Borders - Sapphire-tinted stone
        const ImVec4 BorderSubtle      = ImVec4(0.220f, 0.259f, 0.337f, 1.00f); // #384256
        const ImVec4 BorderWindow      = ImVec4(0.349f, 0.271f, 0.808f, 1.00f); // #5945CE - Sapphire window border
        const ImVec4 BorderTitle       = ImVec4(0.435f, 0.353f, 1.000f, 1.00f); // #6F5AFF - Bright title border
        const ImVec4 BorderTitleBottom = ImVec4(0.263f, 0.192f, 0.608f, 1.00f); // #43319B - Deep bottom border

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.035f, 0.047f, 0.071f, 1.00f);  // #090C12
        const ImVec4 WindowSurround = ImVec4(0.027f, 0.035f, 0.055f, 1.00f);  // #07090E

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.020f, 0.027f, 0.043f, 1.00f); // #05070B
        t.TitleBar.BackgroundColorActive   = ImVec4(0.020f, 0.027f, 0.043f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.020f, 0.027f, 0.043f, 0.85f);
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
        t.ContentPanel.TabInactive         = ChapelNave;
        t.ContentPanel.TabHovered          = ChapelArch;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = SlateDark;
        t.ContentPanel.ButtonHovered       = SlateMid;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = ChapelNave;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = ChapelNave;
        t.Window.TitleBarActive    = ChapelArch;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = SlateDark;
        t.Window.ButtonHovered     = SlateMid;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = ChapelGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = SlateDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = ChapelChoir;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = ChapelDeep;
        t.TrackTable.RowDefaultAlt        = ChapelNave;
        t.TrackTable.RowHovered           = ChapelVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = SlateDark;
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

        t.TrackTable.ScrollbarBg          = ChapelWall;
        t.TrackTable.ScrollbarGrab        = SlateDark;
        t.TrackTable.ScrollbarGrabHovered = SlateMid;
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

        t.Visualizer.BackgroundColor       = ChapelWall;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(SlateDark.x, SlateDark.y, SlateDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = SlateMid;
        t.Visualizer.SpectrumColorMid      = Accent;
        t.Visualizer.SpectrumColorHigh     = AccentLight;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.706f, 0.651f, 1.000f, 1.00f); // #B4A6FF
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = SlateDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
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
        t.AlbumArtBox.BackgroundColor         = ChapelNave;
        t.AlbumArtBox.BackgroundColorHovered  = ChapelArch;
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
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.020f, 0.027f, 0.043f, 0.95f);
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
        t.SearchBar.rowHoverColor             = ChapelArch;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = ChapelNave;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = SlateDark;
        t.PlayerBar.ButtonHovered             = SlateMid;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = SlateDark;
        t.PlayerBar.ButtonPrimaryHovered      = SlateMid;
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
        t.ContextMenu.HoverTextColor          = TextWhite;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic