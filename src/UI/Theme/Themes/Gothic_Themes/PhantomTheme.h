//==============================================================================
// PhantomTheme.h
//==============================================================================
// Ghostly apparition - cold spectral blues and pale ectoplasmic light
// Palette: #9FB3DF (ghostly blue), #9EC6F3 (spectral sky), #BDDDE4 (pale mist),
//          #FFF1D5 (ectoplasmic glow)
// 60% Darkened ghostly blue-black (#0D1118 → #1A2435)
// 25% Spectral blue and pale mist surfaces (#4A6080, #6B8AB0, #9FB3DF)
// 10% Ghostly blue accent (#9FB3DF)
// 5% Ectoplasmic glow text (#FFF1D5)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreatePhantomTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Ghostly apparition, spectral and cold
        //==========================================================================

        // 60% - Darkened ghostly blue-black
        const ImVec4 PhantomDeep     = ImVec4(0.051f, 0.067f, 0.094f, 1.00f);  // #0D1118 - Haunted cellar
        const ImVec4 PhantomMist     = ImVec4(0.102f, 0.141f, 0.208f, 1.00f);  // #1A2435 - Ground fog
        const ImVec4 PhantomHall     = ImVec4(0.141f, 0.184f, 0.263f, 1.00f);  // #242F43 - Empty hallway (library bg)
        const ImVec4 PhantomRoom     = ImVec4(0.180f, 0.227f, 0.314f, 1.00f);  // #2E3A50 - Fading apparition
        const ImVec4 PhantomLight    = ImVec4(0.220f, 0.271f, 0.365f, 1.00f);  // #38455D - Spectral glow on wall

        const ImVec4 PhantomGlow       = ImVec4(0.624f, 0.702f, 0.875f, 0.15f); // Ghostly blue glow
        const ImVec4 PhantomVeryLight  = ImVec4(0.624f, 0.702f, 0.875f, 0.45f);
        const ImVec4 PhantomSubtle     = ImVec4(0.624f, 0.702f, 0.875f, 0.08f);

        // 25% - Spectral blue and pale mist surfaces (darkened)
        const ImVec4 SpectralDark   = ImVec4(0.290f, 0.376f, 0.502f, 1.00f);  // #4A6080 - Dark spectral blue
        const ImVec4 SpectralMid    = ImVec4(0.420f, 0.541f, 0.690f, 1.00f);  // #6B8AB0 - Spectral mist
        const ImVec4 SpectralLit    = ImVec4(0.624f, 0.702f, 0.875f, 1.00f);  // #9FB3DF - Ghostly blue

        // 10% - Ghostly blue accent
        const ImVec4 Accent          = ImVec4(0.624f, 0.702f, 0.875f, 1.00f);  // #9FB3DF - Ghostly apparition
        const ImVec4 AccentDark      = ImVec4(0.420f, 0.541f, 0.690f, 1.00f);  // #6B8AB0 - Fading spirit
        const ImVec4 AccentDarker    = ImVec4(0.290f, 0.376f, 0.502f, 1.00f);  // #4A6080 - Distant phantom
        const ImVec4 AccentLight     = ImVec4(0.741f, 0.867f, 0.894f, 1.00f);  // #BDDDE4 - Pale mist
        const ImVec4 AccentVeryLight = ImVec4(0.741f, 0.867f, 0.894f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.122f, 0.161f, 0.231f, 1.00f); // #1F293B

        // Text - Ectoplasmic glow
        const ImVec4 TextBright  = ImVec4(1.000f, 0.945f, 0.835f, 1.00f);  // #FFF1D5 - Ectoplasmic glow
        const ImVec4 TextMuted   = ImVec4(0.741f, 0.867f, 0.894f, 1.00f);  // #BDDDE4 - Pale mist
        const ImVec4 TextDim     = ImVec4(0.482f, 0.580f, 0.690f, 1.00f);  // #7B94B0 - Fading ectoplasm
        const ImVec4 TextWhite   = ImVec4(1.000f, 0.965f, 0.890f, 1.00f);  // #FFF6E3 - Pure spirit light

        // Borders - Spectral blue-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.290f, 0.376f, 0.502f, 1.00f); // #4A6080 - Spectral border
        const ImVec4 BorderWindow      = ImVec4(0.420f, 0.541f, 0.690f, 1.00f); // #6B8AB0 - Spirit window border
        const ImVec4 BorderTitle       = ImVec4(0.624f, 0.702f, 0.875f, 1.00f); // #9FB3DF - Ghostly title border
        const ImVec4 BorderTitleBottom = ImVec4(0.290f, 0.376f, 0.502f, 1.00f); // #4A6080 - Deep spirit bottom

        // Player Bar & Window Surround - Deepest haunted cellar
        const ImVec4 PlayerBarBg    = ImVec4(0.039f, 0.051f, 0.071f, 1.00f);  // #0A0D12
        const ImVec4 WindowSurround = ImVec4(0.031f, 0.039f, 0.055f, 1.00f);  // #080A0E

        //==========================================================================
        // Title Bar - Haunted manor peak
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.024f, 0.031f, 0.043f, 1.00f); // #06080B
        t.TitleBar.BackgroundColorActive   = ImVec4(0.024f, 0.031f, 0.043f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.024f, 0.031f, 0.043f, 0.85f);
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
        t.ContentPanel.TabInactive         = PhantomHall;
        t.ContentPanel.TabHovered          = PhantomRoom;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = PhantomDeep;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = SpectralDark;
        t.ContentPanel.ButtonHovered       = SpectralMid;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Haunted mirror frame
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = PhantomHall;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = PhantomHall;
        t.Window.TitleBarActive    = PhantomRoom;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = SpectralDark;
        t.Window.ButtonHovered     = SpectralMid;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = PhantomGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Ghostly apparitions
        //==========================================================================

        t.TrackTable.HeaderBackground     = SpectralDark;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = PhantomLight;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = PhantomDeep;
        t.TrackTable.RowDefaultAlt        = PhantomHall;
        t.TrackTable.RowHovered           = PhantomVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = SpectralDark;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = PhantomDeep;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = PhantomMist;
        t.TrackTable.ScrollbarGrab        = SpectralDark;
        t.TrackTable.ScrollbarGrabHovered = SpectralMid;
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
        // Visualizer - Spectral energy manifestation
        //==========================================================================

        t.Visualizer.BackgroundColor       = PhantomMist;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.08f);
        t.Visualizer.GridColor             = ImVec4(SpectralDark.x, SpectralDark.y, SpectralDark.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: dark spectral → ghostly blue → pale mist → ectoplasm ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = SpectralDark;
        t.Visualizer.SpectrumColorMid      = Accent;
        t.Visualizer.SpectrumColorHigh     = AccentLight;
        t.Visualizer.SpectrumColorPeak     = ImVec4(1.000f, 0.945f, 0.835f, 1.00f); // #FFF1D5 - Ectoplasm peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = SpectralDark;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.40f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Tarnished silver frame with ghostly glow
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = PhantomHall;
        t.AlbumArtBox.BackgroundColorHovered  = PhantomRoom;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.18f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox - Haunted sanctuary
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.024f, 0.031f, 0.043f, 0.95f);
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
        // Search Bar - Ghostly whispers
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = PhantomRoom;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = PhantomHall;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Cold cellar floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = SpectralDark;
        t.PlayerBar.ButtonHovered             = SpectralMid;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = SpectralDark;
        t.PlayerBar.ButtonPrimaryHovered      = SpectralMid;
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
        // Popup Menu - Ghostly chamber
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = PhantomDeep;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic