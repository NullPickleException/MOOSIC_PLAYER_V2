//==============================================================================
// CursedEmeraldTheme.h
//==============================================================================
// Cursed emerald - mysterious, jewel-toned, fresh-dark
// 55% Deep emerald-black (#060907 → #0e1f17)
// 25% Dark teal-cyan surfaces (#124136, #1f7a63)
// 10% Emerald glow accent (#1f7a63)
// 10% Pale mint text (#d5efe6)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCursedEmeraldTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Cursed emerald jewel
        //==========================================================================

        // 55% - Deep emerald-black
        const ImVec4 AbyssGreen    = ImVec4(0.024f, 0.027f, 0.027f, 1.00f);  // #060907 - The emerald void
        const ImVec4 DarkJade      = ImVec4(0.055f, 0.122f, 0.090f, 1.00f);  // #0e1f17 - Dark jade shadow
        const ImVec4 EmeraldShadow = ImVec4(0.071f, 0.157f, 0.118f, 1.00f);  // #12281e - Emerald in shadow (library bg)
        const ImVec4 DeepTeal      = ImVec4(0.098f, 0.200f, 0.153f, 1.00f);  // #193327 - Deep teal stone
        const ImVec4 MossStone     = ImVec4(0.125f, 0.239f, 0.184f, 1.00f);  // #203d2f - Ancient moss-covered stone

        const ImVec4 EmeraldGlow       = ImVec4(0.122f, 0.478f, 0.388f, 0.20f); // Cursed emerald glow
        const ImVec4 EmeraldVeryLight  = ImVec4(0.122f, 0.478f, 0.388f, 0.50f);
        const ImVec4 EmeraldSubtle     = ImVec4(0.122f, 0.478f, 0.388f, 0.10f);

        // 25% - Dark teal-cyan surfaces
        const ImVec4 TealDark      = ImVec4(0.071f, 0.255f, 0.212f, 1.00f);  // #124136 - Dark teal
        const ImVec4 EmeraldLit    = ImVec4(0.122f, 0.478f, 0.388f, 1.00f);  // #1f7a63 - Lit emerald
        const ImVec4 TealBright    = ImVec4(0.176f, 0.557f, 0.467f, 1.00f);  // #2d8e77 - Bright teal

        // 10% - Emerald glow accent
        const ImVec4 Accent          = ImVec4(0.122f, 0.478f, 0.388f, 1.00f);  // #1f7a63 - Cursed emerald
        const ImVec4 AccentDark      = ImVec4(0.090f, 0.357f, 0.290f, 1.00f);  // #175b4a - Deep emerald
        const ImVec4 AccentDarker    = ImVec4(0.063f, 0.239f, 0.192f, 1.00f);  // #103d31 - Darkest emerald
        const ImVec4 AccentLight     = ImVec4(0.176f, 0.557f, 0.467f, 1.00f);  // #2d8e77 - Bright emerald
        const ImVec4 AccentVeryLight = ImVec4(0.176f, 0.557f, 0.467f, 0.50f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.059f, 0.133f, 0.102f, 1.00f); // #0f221a

        // Text - Pale mint ethereal
        const ImVec4 TextBright  = ImVec4(0.835f, 0.937f, 0.906f, 1.00f);  // #d5efe6 - Pale mint light
        const ImVec4 TextMuted   = ImVec4(0.627f, 0.745f, 0.710f, 1.00f);  // #a0beb5 - Muted mint
        const ImVec4 TextDim     = ImVec4(0.384f, 0.482f, 0.455f, 1.00f);  // #627b74 - Dimmed jade
        const ImVec4 TextWhite   = ImVec4(0.886f, 0.965f, 0.941f, 1.00f);  // #e2f6f0 - Pure mint white

        // Borders - Emerald-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.098f, 0.200f, 0.153f, 1.00f); // #193327 - Deep teal border
        const ImVec4 BorderWindow      = ImVec4(0.071f, 0.255f, 0.212f, 1.00f); // #124136 - Dark teal window border
        const ImVec4 BorderTitle       = ImVec4(0.122f, 0.478f, 0.388f, 1.00f); // #1f7a63 - Emerald title border
        const ImVec4 BorderTitleBottom = ImVec4(0.063f, 0.239f, 0.192f, 1.00f); // #103d31 - Deep emerald bottom

        // Player Bar & Window Surround - Deepest cursed vault
        const ImVec4 PlayerBarBg    = ImVec4(0.016f, 0.020f, 0.020f, 1.00f);  // #040505
        const ImVec4 WindowSurround = ImVec4(0.012f, 0.016f, 0.016f, 1.00f);  // #030404

        //==========================================================================
        // Title Bar - Cursed crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.008f, 0.012f, 0.012f, 1.00f); // #020303
        t.TitleBar.BackgroundColorActive   = ImVec4(0.008f, 0.012f, 0.012f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.008f, 0.012f, 0.012f, 0.85f);
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
        t.ContentPanel.TabInactive         = EmeraldShadow;
        t.ContentPanel.TabHovered          = DeepTeal;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = TealDark;
        t.ContentPanel.ButtonHovered       = EmeraldLit;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Emerald vault
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = EmeraldShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = EmeraldShadow;
        t.Window.TitleBarActive    = DeepTeal;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = TealDark;
        t.Window.ButtonHovered     = EmeraldLit;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = EmeraldGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Cursed library shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = TealDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = MossStone;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = AbyssGreen;
        t.TrackTable.RowDefaultAlt        = EmeraldShadow;
        t.TrackTable.RowHovered           = EmeraldVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = TealDark;
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

        t.TrackTable.ScrollbarBg          = DarkJade;
        t.TrackTable.ScrollbarGrab        = TealDark;
        t.TrackTable.ScrollbarGrabHovered = EmeraldLit;
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
        // Visualizer - Cursed emerald energy
        //==========================================================================

        t.Visualizer.BackgroundColor       = DarkJade;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(TealDark.x, TealDark.y, TealDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: dark teal → emerald → bright teal → pale mint ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = TealDark;
        t.Visualizer.SpectrumColorMid      = Accent;
        t.Visualizer.SpectrumColorHigh     = AccentLight;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.835f, 0.937f, 0.906f, 1.00f); // #d5efe6 - Mint peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = TealDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Emerald-veined frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = EmeraldShadow;
        t.AlbumArtBox.BackgroundColorHovered  = DeepTeal;
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
        // Lightbox - Cursed vault
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.008f, 0.012f, 0.012f, 0.95f);
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
        // Search Bar - Ancient emerald grimoire
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = DeepTeal;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = EmeraldShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Cursed emerald floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = TealDark;
        t.PlayerBar.ButtonHovered             = EmeraldLit;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = TealDark;
        t.PlayerBar.ButtonPrimaryHovered      = EmeraldLit;
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
        // Popup Menu - Emerald chamber
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