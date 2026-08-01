//==============================================================================
// ObsidianTheme.h
//==============================================================================
// Obsidian amethyst - arcane, luxe, night-sky
// Palette: #0a0710 (obsidian void), #241338 (deep amethyst), #4b1f6f (royal purple),
//          #7c49b9 (amethyst glow), #e9ddff (pale lavender light)
// 55% Obsidian black and deep amethyst (#0a0710 → #241338)
// 25% Royal purple surfaces (#4b1f6f, #5e2d85, #7c49b9)
// 10% Amethyst glow accent (#7c49b9)
// 10% Pale lavender text (#e9ddff)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateObsidianTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Obsidian amethyst, arcane night-sky
        //==========================================================================

        // 55% - Obsidian black and deep amethyst
        const ImVec4 ObsidianVoid   = ImVec4(0.039f, 0.027f, 0.063f, 1.00f);  // #0a0710 - Obsidian void
        const ImVec4 DeepAmethyst   = ImVec4(0.141f, 0.075f, 0.220f, 1.00f);  // #241338 - Deep amethyst crystal
        const ImVec4 AmethystShadow = ImVec4(0.184f, 0.102f, 0.278f, 1.00f);  // #2f1a47 - Amethyst in shadow (library bg)
        const ImVec4 RoyalPurple    = ImVec4(0.294f, 0.122f, 0.435f, 1.00f);  // #4b1f6f - Royal purple
        const ImVec4 PurpleVein     = ImVec4(0.369f, 0.176f, 0.522f, 1.00f);  // #5e2d85 - Purple crystal vein

        const ImVec4 AmethystGlow       = ImVec4(0.486f, 0.286f, 0.725f, 0.20f); // Amethyst glow
        const ImVec4 AmethystVeryLight  = ImVec4(0.486f, 0.286f, 0.725f, 0.50f);
        const ImVec4 AmethystSubtle     = ImVec4(0.486f, 0.286f, 0.725f, 0.10f);

        // 25% - Royal purple surfaces
        const ImVec4 RoyalDark     = ImVec4(0.294f, 0.122f, 0.435f, 1.00f);  // #4b1f6f - Royal purple
        const ImVec4 AmethystLit   = ImVec4(0.486f, 0.286f, 0.725f, 1.00f);  // #7c49b9 - Lit amethyst
        const ImVec4 CrystalBright = ImVec4(0.604f, 0.400f, 0.812f, 1.00f);  // #9a66cf - Bright crystal

        // 10% - Amethyst glow accent
        const ImVec4 Accent          = ImVec4(0.486f, 0.286f, 0.725f, 1.00f);  // #7c49b9 - Amethyst glow
        const ImVec4 AccentDark      = ImVec4(0.369f, 0.176f, 0.522f, 1.00f);  // #5e2d85 - Deep amethyst
        const ImVec4 AccentDarker    = ImVec4(0.294f, 0.122f, 0.435f, 1.00f);  // #4b1f6f - Darkest royal
        const ImVec4 AccentLight     = ImVec4(0.604f, 0.400f, 0.812f, 1.00f);  // #9a66cf - Bright amethyst
        const ImVec4 AccentVeryLight = ImVec4(0.604f, 0.400f, 0.812f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.161f, 0.090f, 0.243f, 1.00f); // #29173e

        // Text - Pale lavender starlight
        const ImVec4 TextBright  = ImVec4(0.914f, 0.867f, 1.000f, 1.00f);  // #e9ddff - Pale lavender light
        const ImVec4 TextMuted   = ImVec4(0.682f, 0.620f, 0.788f, 1.00f);  // #ae9ec9 - Muted amethyst
        const ImVec4 TextDim     = ImVec4(0.424f, 0.373f, 0.510f, 1.00f);  // #6c5f82 - Dimmed purple
        const ImVec4 TextWhite   = ImVec4(0.941f, 0.906f, 1.000f, 1.00f);  // #f0e7ff - Pure starlight

        // Borders - Amethyst-tinted obsidian
        const ImVec4 BorderSubtle      = ImVec4(0.220f, 0.098f, 0.329f, 1.00f); // #381954 - Deep purple border
        const ImVec4 BorderWindow      = ImVec4(0.294f, 0.122f, 0.435f, 1.00f); // #4b1f6f - Royal purple border
        const ImVec4 BorderTitle       = ImVec4(0.486f, 0.286f, 0.725f, 1.00f); // #7c49b9 - Amethyst title border
        const ImVec4 BorderTitleBottom = ImVec4(0.220f, 0.098f, 0.329f, 1.00f); // #381954 - Deep purple bottom

        // Player Bar & Window Surround - Deepest obsidian void
        const ImVec4 PlayerBarBg    = ImVec4(0.027f, 0.020f, 0.043f, 1.00f);  // #07050b
        const ImVec4 WindowSurround = ImVec4(0.020f, 0.016f, 0.035f, 1.00f);  // #050409

        //==========================================================================
        // Title Bar - Obsidian crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.012f, 0.008f, 0.020f, 1.00f); // #030205
        t.TitleBar.BackgroundColorActive   = ImVec4(0.012f, 0.008f, 0.020f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.012f, 0.008f, 0.020f, 0.85f);
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
        t.ContentPanel.TabInactive         = AmethystShadow;
        t.ContentPanel.TabHovered          = RoyalPurple;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = RoyalDark;
        t.ContentPanel.ButtonHovered       = AmethystLit;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Amethyst crystal vault
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = AmethystShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = AmethystShadow;
        t.Window.TitleBarActive    = RoyalPurple;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = RoyalDark;
        t.Window.ButtonHovered     = AmethystLit;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = AmethystGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Crystal library shelves
        //==========================================================================

        t.TrackTable.HeaderBackground     = RoyalDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = PurpleVein;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = ObsidianVoid;
        t.TrackTable.RowDefaultAlt        = AmethystShadow;
        t.TrackTable.RowHovered           = AmethystVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = RoyalDark;
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

        t.TrackTable.ScrollbarBg          = DeepAmethyst;
        t.TrackTable.ScrollbarGrab        = RoyalDark;
        t.TrackTable.ScrollbarGrabHovered = AmethystLit;
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
        // Visualizer - Amethyst crystal energy
        //==========================================================================

        t.Visualizer.BackgroundColor       = DeepAmethyst;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(RoyalDark.x, RoyalDark.y, RoyalDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: royal purple → amethyst → bright crystal → pale lavender ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = RoyalDark;
        t.Visualizer.SpectrumColorMid      = Accent;
        t.Visualizer.SpectrumColorHigh     = AccentLight;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.914f, 0.867f, 1.000f, 1.00f); // #e9ddff - Lavender peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = RoyalDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Amethyst-veined obsidian frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = AmethystShadow;
        t.AlbumArtBox.BackgroundColorHovered  = RoyalPurple;
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
        // Lightbox - Obsidian sanctuary
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.012f, 0.008f, 0.020f, 0.95f);
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
        // Search Bar - Arcane grimoire
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = RoyalPurple;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = AmethystShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Obsidian floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = RoyalDark;
        t.PlayerBar.ButtonHovered             = AmethystLit;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = RoyalDark;
        t.PlayerBar.ButtonPrimaryHovered      = AmethystLit;
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
        // Popup Menu - Amethyst chamber
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