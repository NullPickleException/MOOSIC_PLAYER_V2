//==============================================================================
// NightCreaturesTheme.h
//==============================================================================
// Night creatures - nocturnal, mysterious, deep sea predator
// Palette: #121358 (abyssal blue), #232F72 (midnight depths), #2F578A (bioluminescent blue),
//          #36ADA3 (creature eyes teal)
// 55% Abyssal blue and midnight depths (#121358 → #232F72)
// 25% Bioluminescent blue surfaces (#2F578A, #3A6D9E)
// 10% Creature eyes teal accent (#36ADA3)
// 10% Pale bioluminescent text
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateNightCreaturesTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Night creatures of the deep
        //==========================================================================

        // 55% - Abyssal blue and midnight depths
        const ImVec4 AbyssalBlue      = ImVec4(0.071f, 0.075f, 0.345f, 1.00f);  // #121358 - Abyssal blue
        const ImVec4 MidnightDepths   = ImVec4(0.137f, 0.184f, 0.447f, 1.00f);  // #232F72 - Midnight depths
        const ImVec4 DeepWater        = ImVec4(0.176f, 0.231f, 0.506f, 1.00f);  // #2D3B81 - Deep water (library bg)
        const ImVec4 PredatorShadow   = ImVec4(0.216f, 0.278f, 0.561f, 1.00f);  // #37478F - Predator in shadow
        const ImVec4 OceanHunt        = ImVec4(0.259f, 0.329f, 0.588f, 1.00f);  // #425496 - Ocean hunt

        const ImVec4 CreatureGlow       = ImVec4(0.212f, 0.678f, 0.639f, 0.20f); // Bioluminescent glow
        const ImVec4 CreatureVeryLight  = ImVec4(0.212f, 0.678f, 0.639f, 0.50f);
        const ImVec4 CreatureSubtle     = ImVec4(0.212f, 0.678f, 0.639f, 0.10f);

        // 25% - Bioluminescent blue surfaces
        const ImVec4 BiolumeBlue    = ImVec4(0.184f, 0.341f, 0.541f, 1.00f);  // #2F578A - Bioluminescent blue
        const ImVec4 DeepTeal       = ImVec4(0.228f, 0.427f, 0.620f, 1.00f);  // #3A6D9E - Deep teal
        const ImVec4 HuntingGlow    = ImVec4(0.271f, 0.502f, 0.682f, 1.00f);  // #4580AE - Hunting glow

        // 10% - Creature eyes teal accent
        const ImVec4 Accent          = ImVec4(0.212f, 0.678f, 0.639f, 1.00f);  // #36ADA3 - Creature eyes
        const ImVec4 AccentDark      = ImVec4(0.165f, 0.525f, 0.494f, 1.00f);  // #2A867E - Dark teal
        const ImVec4 AccentDarker    = ImVec4(0.125f, 0.396f, 0.373f, 1.00f);  // #20655F - Deepest teal
        const ImVec4 AccentLight     = ImVec4(0.314f, 0.780f, 0.741f, 1.00f);  // #50C7BD - Bright creature eyes
        const ImVec4 AccentVeryLight = ImVec4(0.314f, 0.780f, 0.741f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.153f, 0.208f, 0.471f, 1.00f); // #273578

        // Text - Pale bioluminescent glow
        const ImVec4 TextBright  = ImVec4(0.831f, 0.910f, 0.929f, 1.00f);  // #D4E8ED - Pale bioluminescence
        const ImVec4 TextMuted   = ImVec4(0.627f, 0.722f, 0.769f, 1.00f);  // #A0B8C4 - Muted glow
        const ImVec4 TextDim     = ImVec4(0.400f, 0.482f, 0.541f, 1.00f);  // #667B8A - Fading light
        const ImVec4 TextWhite   = ImVec4(0.902f, 0.949f, 0.961f, 1.00f);  // #E6F2F5 - Pure bioluminescence

        // Borders - Bioluminescent-tinted
        const ImVec4 BorderSubtle      = ImVec4(0.216f, 0.278f, 0.561f, 1.00f); // #37478F - Deep water border
        const ImVec4 BorderWindow      = ImVec4(0.184f, 0.341f, 0.541f, 1.00f); // #2F578A - Biolume blue border
        const ImVec4 BorderTitle       = ImVec4(0.212f, 0.678f, 0.639f, 1.00f); // #36ADA3 - Creature eyes border
        const ImVec4 BorderTitleBottom = ImVec4(0.125f, 0.396f, 0.373f, 1.00f); // #20655F - Deep teal bottom

        // Player Bar & Window Surround - Deepest abyss
        const ImVec4 PlayerBarBg    = ImVec4(0.051f, 0.055f, 0.255f, 1.00f);  // #0D0E41
        const ImVec4 WindowSurround = ImVec4(0.039f, 0.043f, 0.204f, 1.00f);  // #0A0B34

        //==========================================================================
        // Title Bar - Abyssal crown
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.027f, 0.031f, 0.149f, 1.00f); // #070826
        t.TitleBar.BackgroundColorActive   = ImVec4(0.027f, 0.031f, 0.149f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.027f, 0.031f, 0.149f, 0.85f);
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
        t.ContentPanel.TabInactive         = DeepWater;
        t.ContentPanel.TabHovered          = PredatorShadow;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = AbyssalBlue;  // Dark text on teal tab
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = BiolumeBlue;
        t.ContentPanel.ButtonHovered       = DeepTeal;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window - Deep sea predator's lair
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = DeepWater;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = DeepWater;
        t.Window.TitleBarActive    = PredatorShadow;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = BiolumeBlue;
        t.Window.ButtonHovered     = DeepTeal;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = CreatureGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table - Predator's hunting ground
        //==========================================================================

        t.TrackTable.HeaderBackground     = BiolumeBlue;
        t.TrackTable.HeaderTextColor      = TextBright;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = OceanHunt;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = TextBright;
        t.TrackTable.HeaderTextArtist     = TextBright;
        t.TrackTable.HeaderTextAlbum      = TextBright;
        t.TrackTable.HeaderTextExtension  = TextBright;
        t.TrackTable.HeaderTextDuration   = TextBright;

        t.TrackTable.RowDefault           = AbyssalBlue;
        t.TrackTable.RowDefaultAlt        = DeepWater;
        t.TrackTable.RowHovered           = CreatureVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = BiolumeBlue;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = TextWhite;
        t.TrackTable.TextPlaying          = AbyssalBlue;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = MidnightDepths;
        t.TrackTable.ScrollbarGrab        = BiolumeBlue;
        t.TrackTable.ScrollbarGrabHovered = DeepTeal;
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
        // Visualizer - Bioluminescent creature pulses
        //==========================================================================

        t.Visualizer.BackgroundColor       = MidnightDepths;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(BiolumeBlue.x, BiolumeBlue.y, BiolumeBlue.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp: biolume blue → deep teal → creature eyes → pale glow ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = BiolumeBlue;
        t.Visualizer.SpectrumColorMid      = DeepTeal;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.831f, 0.910f, 0.929f, 1.00f); // #D4E8ED - Biolume peak
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = BiolumeBlue;
        t.Visualizer.HighFreqTint          = Accent;
        t.Visualizer.FrequencyTintBlend    = 0.30f;

        t.Visualizer.BarBrightnessMin      = 0.45f;
        t.Visualizer.BarBrightnessMax      = 1.20f;

        //==========================================================================
        // Album Art - Bioluminescent frame
        //==========================================================================

        t.AlbumArtBox.BorderColor             = BorderWindow;
        t.AlbumArtBox.BorderColorHovered      = Accent;
        t.AlbumArtBox.BorderColorClicked      = AccentLight;
        t.AlbumArtBox.BorderThickness         = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered  = 3.0f;
        t.AlbumArtBox.BorderRounding          = 3.0f;
        t.AlbumArtBox.BackgroundColor         = DeepWater;
        t.AlbumArtBox.BackgroundColorHovered  = PredatorShadow;
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
        // Lightbox - Deepest trench
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.027f, 0.031f, 0.149f, 0.95f);
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
        // Search Bar - Predator's tracking
        //==========================================================================

        t.SearchBar.shadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor           = SearchDropdownBg;
        t.SearchBar.borderColor               = BorderWindow;
        t.SearchBar.textColor                 = TextBright;
        t.SearchBar.highlightTextColor        = Accent;
        t.SearchBar.rowHoverColor             = PredatorShadow;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = DeepWater;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar - Ocean floor
        //==========================================================================

        t.PlayerBar.TextPrimary               = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary             = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal              = BiolumeBlue;
        t.PlayerBar.ButtonHovered             = DeepTeal;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = BiolumeBlue;
        t.PlayerBar.ButtonPrimaryHovered      = DeepTeal;
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
        // Popup Menu - Predator's lair
        //==========================================================================

        t.ContextMenu.BackgroundColor         = SearchDropdownBg;
        t.ContextMenu.BorderColor             = BorderWindow;
        t.ContextMenu.TextColor               = TextBright;
        t.ContextMenu.TextDisabledColor       = TextDim;
        t.ContextMenu.HoverColor              = Accent;
        t.ContextMenu.HoverTextColor          = AbyssalBlue;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic