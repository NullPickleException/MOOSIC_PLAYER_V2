//==============================================================================
// CanyonTheme.h
//==============================================================================
// Red rock canyon - sandstone cliffs, desert sunset, warm earth
// Palette: #973131 (canyon rust), #E0A75E (sandstone glow), #F9D689 (golden hour),
//          #F5E7B2 (pale canyon light)
// 60% Darkened canyon rust (#973131 → #6B2222)
// 25% Sandstone glow and golden surfaces (#E0A75E, #F9D689)
// 10% Golden hour accent (#F9D689)
// 5% Pale canyon light text (#F5E7B2)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCanyonTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette - Red rock canyon at golden hour
        //==========================================================================

        // 60% - Darkened canyon rust
        const ImVec4 CanyonRust     = ImVec4(0.420f, 0.192f, 0.192f, 1.00f);  // #6B3131 - Dark canyon rust
        const ImVec4 DeepCanyon     = ImVec4(0.490f, 0.224f, 0.224f, 1.00f);  // #7D3939 - Deep canyon
        const ImVec4 CanyonShadow   = ImVec4(0.541f, 0.247f, 0.247f, 1.00f);  // #8A3F3F - Canyon shadow (library bg)
        const ImVec4 RockWall       = ImVec4(0.592f, 0.271f, 0.271f, 1.00f);  // #974545 - Rock wall
        const ImVec4 SandstoneCliff = ImVec4(0.635f, 0.294f, 0.294f, 1.00f);  // #A24B4B - Sandstone cliff

        const ImVec4 CanyonGlow       = ImVec4(0.878f, 0.655f, 0.369f, 0.15f); // Sandstone glow
        const ImVec4 CanyonVeryLight  = ImVec4(0.878f, 0.655f, 0.369f, 0.45f);
        const ImVec4 CanyonSubtle     = ImVec4(0.878f, 0.655f, 0.369f, 0.08f);

        // 25% - Sandstone glow and golden surfaces
        const ImVec4 SandstoneGlow  = ImVec4(0.878f, 0.655f, 0.369f, 1.00f);  // #E0A75E - Sandstone glow
        const ImVec4 GoldenHour     = ImVec4(0.976f, 0.839f, 0.537f, 1.00f);  // #F9D689 - Golden hour
        const ImVec4 PaleLight      = ImVec4(0.961f, 0.906f, 0.698f, 1.00f);  // #F5E7B2 - Pale canyon light

        // 10% - Golden hour accent
        const ImVec4 Accent          = ImVec4(0.976f, 0.839f, 0.537f, 1.00f);  // #F9D689 - Golden hour
        const ImVec4 AccentDark      = ImVec4(0.878f, 0.655f, 0.369f, 1.00f);  // #E0A75E - Sandstone glow
        const ImVec4 AccentDarker    = ImVec4(0.592f, 0.192f, 0.192f, 1.00f);  // #973131 - Canyon rust
        const ImVec4 AccentLight     = ImVec4(0.961f, 0.906f, 0.698f, 1.00f);  // #F5E7B2 - Pale light
        const ImVec4 AccentVeryLight = ImVec4(0.961f, 0.906f, 0.698f, 0.40f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.510f, 0.231f, 0.231f, 1.00f); // #823B3B

        // Text - Pale canyon light and warm sand
        const ImVec4 TextBright  = ImVec4(0.961f, 0.906f, 0.698f, 1.00f);  // #F5E7B2 - Pale canyon light
        const ImVec4 TextMuted   = ImVec4(0.878f, 0.655f, 0.369f, 1.00f);  // #E0A75E - Sandstone
        const ImVec4 TextDim     = ImVec4(0.682f, 0.475f, 0.318f, 1.00f);  // #AE7951 - Faded rock
        const ImVec4 TextWhite   = ImVec4(0.976f, 0.937f, 0.776f, 1.00f);  // #F9EFC6 - Bright canyon light

        // Borders - Rust-tinted sandstone
        const ImVec4 BorderSubtle      = ImVec4(0.592f, 0.271f, 0.271f, 1.00f); // #974545 - Rock border
        const ImVec4 BorderWindow      = ImVec4(0.592f, 0.192f, 0.192f, 1.00f); // #973131 - Canyon rust border
        const ImVec4 BorderTitle       = ImVec4(0.878f, 0.655f, 0.369f, 1.00f); // #E0A75E - Sandstone border
        const ImVec4 BorderTitleBottom = ImVec4(0.420f, 0.192f, 0.192f, 1.00f); // #6B3131 - Deep rust bottom

        // Player Bar & Window Surround
        const ImVec4 PlayerBarBg    = ImVec4(0.302f, 0.137f, 0.137f, 1.00f);  // #4D2323
        const ImVec4 WindowSurround = ImVec4(0.243f, 0.110f, 0.110f, 1.00f);  // #3E1C1C

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = ImVec4(0.184f, 0.082f, 0.082f, 1.00f); // #2F1515
        t.TitleBar.BackgroundColorActive   = ImVec4(0.184f, 0.082f, 0.082f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.184f, 0.082f, 0.082f, 0.85f);
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
        t.ContentPanel.TabInactive         = CanyonShadow;
        t.ContentPanel.TabHovered          = RockWall;
        t.ContentPanel.TabRounding         = 4.0f;
        t.ContentPanel.TabText             = CanyonRust;
        t.ContentPanel.TabTextInactive     = TextMuted;
        t.ContentPanel.ButtonNormal        = SandstoneGlow;
        t.ContentPanel.ButtonHovered       = GoldenHour;
        t.ContentPanel.ButtonActive        = AccentDark;
        t.ContentPanel.ButtonRounding      = 2.0f;
        t.ContentPanel.BorderColor         = BorderWindow;
        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg          = WindowSurround;
        t.Window.ChildBg           = CanyonShadow;
        t.Window.WindowBorder      = BorderWindow;
        t.Window.TitleBar          = CanyonShadow;
        t.Window.TitleBarActive    = RockWall;
        t.Window.HeaderText        = TextBright;
        t.Window.TextPrimary       = TextBright;
        t.Window.TextSecondary     = TextMuted;
        t.Window.TextDisabled      = TextDim;
        t.Window.BrandText         = Accent;
        t.Window.ButtonNormal      = SandstoneGlow;
        t.Window.ButtonHovered     = GoldenHour;
        t.Window.ButtonActive      = AccentDark;
        t.Window.ProgressBar       = Accent;
        t.Window.PlayingHighlight  = CanyonGlow;
        t.Window.SeparatorColor    = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground     = SandstoneGlow;
        t.TrackTable.HeaderTextColor      = CanyonRust;
        t.TrackTable.HeaderBorderColor    = BorderWindow;
        t.TrackTable.HeaderHovered        = SandstoneCliff;
        t.TrackTable.HeaderActive         = Accent;
        t.TrackTable.HeaderTextTitle      = CanyonRust;
        t.TrackTable.HeaderTextArtist     = CanyonRust;
        t.TrackTable.HeaderTextAlbum      = CanyonRust;
        t.TrackTable.HeaderTextExtension  = CanyonRust;
        t.TrackTable.HeaderTextDuration   = CanyonRust;

        t.TrackTable.RowDefault           = CanyonRust;
        t.TrackTable.RowDefaultAlt        = CanyonShadow;
        t.TrackTable.RowHovered           = CanyonVeryLight;
        t.TrackTable.RowClicked           = AccentDarker;
        t.TrackTable.RowSelected          = SandstoneGlow;
        t.TrackTable.RowPlaying           = Accent;

        t.TrackTable.RowHeight            = 18.0f;
        t.TrackTable.RowPaddingX          = 4.0f;
        t.TrackTable.RowPaddingY          = 2.0f;

        t.TrackTable.TextColor            = TextBright;
        t.TrackTable.TextDim              = TextDim;
        t.TrackTable.TextSelected         = CanyonRust;
        t.TrackTable.TextPlaying          = CanyonRust;

        t.TrackTable.RowTextTitle         = TextBright;
        t.TrackTable.RowTextArtist        = TextMuted;
        t.TrackTable.RowTextAlbum         = TextMuted;
        t.TrackTable.RowTextExtension     = TextDim;
        t.TrackTable.RowTextDuration      = TextMuted;

        t.TrackTable.BorderColor          = BorderWindow;
        t.TrackTable.BorderThickness      = 1.0f;
        t.TrackTable.ShowRowSeparators    = true;
        t.TrackTable.RowSeparatorColor    = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        t.TrackTable.ScrollbarBg          = DeepCanyon;
        t.TrackTable.ScrollbarGrab        = SandstoneGlow;
        t.TrackTable.ScrollbarGrabHovered = GoldenHour;
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

        t.Visualizer.BackgroundColor       = DeepCanyon;
        t.Visualizer.WaveformColor         = Accent;
        t.Visualizer.WaveformFillColor     = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor             = ImVec4(SandstoneGlow.x, SandstoneGlow.y, SandstoneGlow.z, 0.25f);
        t.Visualizer.BorderColor           = BorderWindow;
        t.Visualizer.PlaceholderColor      = TextDim;

        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = SandstoneGlow;
        t.Visualizer.SpectrumColorMid      = GoldenHour;
        t.Visualizer.SpectrumColorHigh     = Accent;
        t.Visualizer.SpectrumColorPeak     = ImVec4(0.961f, 0.906f, 0.698f, 1.00f);
        t.Visualizer.ColorRampLowThreshold  = 0.0f;
        t.Visualizer.ColorRampMidThreshold  = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = SandstoneGlow;
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
        t.AlbumArtBox.BackgroundColor         = CanyonShadow;
        t.AlbumArtBox.BackgroundColorHovered  = RockWall;
        t.AlbumArtBox.ShowShadow              = true;
        t.AlbumArtBox.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.AlbumArtBox.PlaceholderTextColor    = TextDim;
        t.AlbumArtBox.ShowHoverOverlay        = true;
        t.AlbumArtBox.HoverOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.20f);
        t.AlbumArtBox.ShowPlayButtonOnHover   = true;
        t.AlbumArtBox.PlayButtonColor         = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor    = ImVec4(0.184f, 0.082f, 0.082f, 0.95f);
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
        t.SearchBar.rowHoverColor             = RockWall;
        t.SearchBar.separatorColor            = BorderSubtle;
        t.SearchBar.inputBgColor              = CanyonShadow;
        t.SearchBar.inputBorderColor          = BorderWindow;
        t.SearchBar.inputTextColor            = TextBright;
        t.SearchBar.inputHintColor            = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary               = TextBright;
        t.PlayerBar.TextSecondary             = TextMuted;
        t.PlayerBar.ButtonNormal              = SandstoneGlow;
        t.PlayerBar.ButtonHovered             = GoldenHour;
        t.PlayerBar.ButtonActive              = AccentDark;
        t.PlayerBar.ButtonPrimary             = SandstoneGlow;
        t.PlayerBar.ButtonPrimaryHovered      = GoldenHour;
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
        t.ContextMenu.HoverTextColor          = CanyonRust;
        t.ContextMenu.SeparatorColor          = BorderSubtle;
        t.ContextMenu.ShadowColor             = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic