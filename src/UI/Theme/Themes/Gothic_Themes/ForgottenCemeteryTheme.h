//==============================================================================
// ForgottenCemeteryTheme.h
//==============================================================================
// Forgotten cemetery - moss-covered stones, weathered marble, overgrown paths
// Palette: #273338 (weathered slate), #2B5748 (moss-covered stone), #618764 (aged moss),
//          #9CB080 (pale lichen)
// 60% Weathered slate and dark granite (#273338 → #2B5748)
// 25% Moss-covered stone and aged moss surfaces (#2B5748, #618764)
// 10% Aged moss accent (#618764)
// 5% Pale lichen text (#9CB080)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateForgottenCemeteryTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Forgotten cemetery, gothic decay
        //==========================================================================

        // 60% - Weathered slate and dark granite (darkened for gothic depth)
        const ImVec4 WeatheredSlate  = ImVec4(0.120f, 0.153f, 0.169f, 1.00f);  // #1F272B - Darker weathered slate
        const ImVec4 DarkGranite     = ImVec4(0.133f, 0.263f, 0.216f, 1.00f);  // #224337 - Dark granite tombstone
        const ImVec4 TombstoneShadow = ImVec4(0.165f, 0.306f, 0.251f, 1.00f);  // #2A4E40 - Tombstone in shadow (library bg)
        const ImVec4 MossyStone      = ImVec4(0.196f, 0.349f, 0.286f, 1.00f);  // #325949 - Mossy stone
        const ImVec4 LichenCovered   = ImVec4(0.227f, 0.384f, 0.318f, 1.00f);  // #3A6251 - Lichen-covered marble

        const ImVec4 CemeteryGlow       = ImVec4(0.380f, 0.529f, 0.392f, 0.18f); // Moss glow (subtle)
        const ImVec4 CemeteryVeryLight  = ImVec4(0.380f, 0.529f, 0.392f, 0.45f);
        const ImVec4 CemeterySubtle     = ImVec4(0.380f, 0.529f, 0.392f, 0.08f);

        // 25% - Moss-covered stone and aged moss surfaces
        const ImVec4 MossCovered    = ImVec4(0.169f, 0.341f, 0.282f, 1.00f);  // #2B5748 - Moss-covered stone
        const ImVec4 AgedMoss       = ImVec4(0.380f, 0.529f, 0.392f, 1.00f);  // #618764 - Aged moss
        const ImVec4 FreshLichen    = ImVec4(0.455f, 0.600f, 0.459f, 1.00f);  // #749975 - Fresh lichen

        // 10% - Aged moss accent
        const ImVec4 Accent          = ImVec4(0.380f, 0.529f, 0.392f, 1.00f);  // #618764 - Aged moss
        const ImVec4 AccentDark      = ImVec4(0.247f, 0.439f, 0.361f, 1.00f);  // #3F705C - Dark moss
        const ImVec4 AccentDarker    = ImVec4(0.169f, 0.341f, 0.282f, 1.00f);  // #2B5748 - Deepest moss
        const ImVec4 AccentLight     = ImVec4(0.612f, 0.690f, 0.502f, 1.00f);  // #9CB080 - Pale lichen
        const ImVec4 AccentVeryLight = ImVec4(0.612f, 0.690f, 0.502f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.149f, 0.282f, 0.235f, 1.00f); // #26483C

        // 5% - Pale lichen text on weathered stone
        const ImVec4 TextBright  = ImVec4(0.612f, 0.690f, 0.502f, 1.00f);  // #9CB080 - Pale lichen
        const ImVec4 TextMuted   = ImVec4(0.482f, 0.553f, 0.424f, 1.00f);  // #7B8D6C - Faded lichen
        const ImVec4 TextDim     = ImVec4(0.333f, 0.396f, 0.322f, 1.00f);  // #556552 - Weathered inscription
        const ImVec4 TextWhite   = ImVec4(0.698f, 0.769f, 0.592f, 1.00f);  // #B2C497 - Sunlit lichen

        // Borders - Gothic iron and moss-tinted stone
        const ImVec4 BorderSubtle      = ImVec4(0.196f, 0.349f, 0.286f, 1.00f); // #325949 - Mossy stone border
        const ImVec4 BorderWindow      = ImVec4(0.169f, 0.341f, 0.282f, 1.00f); // #2B5748 - Moss-covered border
        const ImVec4 BorderTitle       = ImVec4(0.380f, 0.529f, 0.392f, 1.00f); // #618764 - Aged moss border
        const ImVec4 BorderTitleBottom = ImVec4(0.106f, 0.216f, 0.180f, 1.00f); // #1B372E - Deep gothic moss bottom

        // Player Bar & Window Surround - Deepest cemetery earth
        const ImVec4 PlayerBarBg    = ImVec4(0.082f, 0.106f, 0.114f, 1.00f);  // #151B1D
        const ImVec4 WindowSurround = ImVec4(0.063f, 0.082f, 0.090f, 1.00f);  // #101517

        //==========================================================================
        // Title Bar - Gothic tombstone peak
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.047f, 0.063f, 0.071f, 1.00f); // #0C1012
        t.TitleBar.BackgroundColorActive   = ImVec4(0.047f, 0.063f, 0.071f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.047f, 0.063f, 0.071f, 0.85f);
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
        t.ContentPanel.TabInactive         = TombstoneShadow;
        t.ContentPanel.TabHovered          = MossyStone;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = WeatheredSlate;  // Dark text on moss tab
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = MossCovered;
        t.ContentPanel.ButtonHovered       = AgedMoss;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Gothic cemetery gates
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = TombstoneShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = TombstoneShadow;
        t.Window.TitleBarActive    = MossyStone;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = MossCovered;
        t.Window.ButtonHovered     = AgedMoss;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = CemeteryGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Rows of gothic tombstones
        //==========================================================================

        t.TrackTable.HeaderBackground     = MossCovered;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = LichenCovered;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = WeatheredSlate;
        t.TrackTable.RowDefaultAlt        = TombstoneShadow;
        t.TrackTable.RowHovered           = CemeteryVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = MossCovered;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = WeatheredSlate;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = DarkGranite;
        t.TrackTable.ScrollbarGrab        = MossCovered;
        t.TrackTable.ScrollbarGrabHovered = AgedMoss;
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
        // Visualizer - Gothic mist rising through tombstones
        //==========================================================================

        t.Visualizer.BackgroundColor       = DarkGranite;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.08f);
        t.Visualizer.GridColor             = ImVec4(MossCovered.x, MossCovered.y, MossCovered.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Gothic color ramp: dark granite → moss-covered → aged moss → pale lichen ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = MossCovered;
        t.Visualizer.SpectrumColorMid      = AgedMoss;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.612f, 0.690f, 0.502f, 1.00f); // #9CB080 - Lichen peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = MossCovered;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.40f;
        t.Visualizer.BarBrightnessMax      = 1.15f;

        //==========================================================================
        // Album Art - Gothic moss-covered iron frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = TombstoneShadow;
        t.AlbumArtBox.BackgroundColorHovered  = MossyStone;
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
        // Lightbox - Oldest gothic mausoleum
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.047f, 0.063f, 0.071f, 0.95f);
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
        // Search Bar - Weathered gothic inscriptions
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = MossyStone;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = TombstoneShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Gothic cemetery earth
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = MossCovered;
        t.PlayerBar.ButtonHovered             = AgedMoss;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = MossCovered;
        t.PlayerBar.ButtonPrimaryHovered      = AgedMoss;
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
        // Popup Menu - Overgrown gothic crypt
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = WeatheredSlate;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic