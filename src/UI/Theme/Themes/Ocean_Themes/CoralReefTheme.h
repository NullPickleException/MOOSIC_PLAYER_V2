//==============================================================================
// CoralReefTheme.h
//==============================================================================
// Ocean-inspired theme with vibrant coral and teal accents
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCoralReefTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // Coral colors (warm, vibrant)
        const ImVec4 Coral = ImVec4(1.000f, 0.498f, 0.431f, 1.00f);         // 255,127,110
        const ImVec4 CoralDark = ImVec4(0.800f, 0.298f, 0.231f, 1.00f);     // 204,76,59
        const ImVec4 CoralDarker = ImVec4(0.600f, 0.198f, 0.131f, 1.00f);   // 153,50,33
        const ImVec4 CoralLight = ImVec4(1.000f, 0.698f, 0.631f, 1.00f);    // 255,178,161
        const ImVec4 CoralVeryLight = ImVec4(1.000f, 0.698f, 0.631f, 0.5f); // 255,178,161
        const ImVec4 CoralGlow = ImVec4(1.000f, 0.498f, 0.431f, 0.20f);
        const ImVec4 CoralSubtle = ImVec4(1.000f, 0.498f, 0.431f, 0.10f);

        // Teal/Ocean colors (cool, deep)
        const ImVec4 Teal = ImVec4(0.180f, 0.780f, 0.722f, 1.00f);         // 46,199,184
        const ImVec4 TealDark = ImVec4(0.120f, 0.580f, 0.522f, 1.00f);     // 31,148,133
        const ImVec4 TealDarker = ImVec4(0.080f, 0.420f, 0.380f, 1.00f);   // 20,107,97
        const ImVec4 TealLight = ImVec4(0.380f, 0.880f, 0.822f, 1.00f);    // 97,224,210
        const ImVec4 TealGlow = ImVec4(0.180f, 0.780f, 0.722f, 0.20f);

        // Deep ocean backgrounds
        const ImVec4 OceanDeep = ImVec4(0.020f, 0.180f, 0.220f, 1.00f);    // 5,46,56
        const ImVec4 OceanMid = ImVec4(0.040f, 0.220f, 0.260f, 1.00f);     // 10,56,66
        const ImVec4 OceanSurface = ImVec4(0.060f, 0.260f, 0.300f, 1.00f); // 15,66,77
        const ImVec4 OceanPanel = ImVec4(0.015f, 0.150f, 0.190f, 1.00f);   // 4,38,48

        // Text
        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = OceanDeep;
        t.TitleBar.BackgroundColorActive = OceanDeep;
        t.TitleBar.BackgroundColorInactive = ImVec4(OceanDeep.x, OceanDeep.y, OceanDeep.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = TealDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = CoralLight;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Coral;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Coral;
        t.ContentPanel.TabInactive = TealDarker;
        t.ContentPanel.TabHovered = TealDark;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = TealDark;
        t.ContentPanel.ButtonHovered = Coral;
        t.ContentPanel.ButtonActive = CoralDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = CoralLight;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = OceanPanel;
        t.Window.ChildBg = OceanDeep;
        t.Window.WindowBorder = TealDarker;

        t.Window.TitleBar = OceanMid;
        t.Window.TitleBarActive = OceanSurface;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Coral;

        t.Window.ButtonNormal = TealDark;
        t.Window.ButtonHovered = Coral;
        t.Window.ButtonActive = CoralDark;

        t.Window.ProgressBar = Coral;
        t.Window.PlayingHighlight = CoralGlow;
        t.Window.SeparatorColor = TealDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = TealDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = TealDarker;
        t.TrackTable.HeaderHovered = OceanSurface;
        t.TrackTable.HeaderActive = Coral;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = OceanDeep;
        t.TrackTable.RowDefaultAlt = OceanMid;
        t.TrackTable.RowHovered = CoralVeryLight;
        t.TrackTable.RowClicked = ImVec4(Coral.x, Coral.y, Coral.z, 0.35f);
        t.TrackTable.RowSelected = CoralLight;
        t.TrackTable.RowPlaying = Coral;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = TextBright;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextWhite;
        t.TrackTable.TextPlaying = TextWhite;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle = TextBright;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = TealDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(TealDarker.x, TealDarker.y, TealDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = OceanPanel;
        t.TrackTable.ScrollbarGrab = TealDark;
        t.TrackTable.ScrollbarGrabHovered = Teal;
        t.TrackTable.ScrollbarGrabActive = Coral;
        t.TrackTable.ScrollbarWidth = 8.0f;
        t.TrackTable.ScrollbarRounding = 4.0f;

        // ── Smoothing / Animation ──
        t.TrackTable.HoverFadeSpeed = 0.15f;
        t.TrackTable.SelectionFadeSpeed = 0.20f;
        t.TrackTable.ScrollSmoothing = 0.12f;

        // ── Misc ──
        t.TrackTable.TableRounding = 0.0f;
        t.TrackTable.MinColumnWidth = 30.0f;

        // ── Column widths ──
        t.TrackTable.TitleWidth = 350.0f;
        t.TrackTable.ArtistWidth = 180.0f;
        t.TrackTable.AlbumWidth = 180.0f;
        t.TrackTable.ExtensionWidth = 50.0f;
        t.TrackTable.DurationWidth = 80.0f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = OceanPanel;
        t.Visualizer.WaveformColor = Coral;
        t.Visualizer.WaveformFillColor = ImVec4(Coral.x, Coral.y, Coral.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(TealDark.x, TealDark.y, TealDark.z, 0.25f);
        t.Visualizer.BorderColor = TealDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Coral;
        t.Visualizer.SpectrumColorMid = CoralLight;
        t.Visualizer.SpectrumColorHigh = ImVec4(1.00f, 0.85f, 0.50f, 1.00f);
        t.Visualizer.SpectrumColorPeak = TextWhite;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.40f;
        t.Visualizer.ColorRampHighThreshold = 0.75f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = Teal;
        t.Visualizer.HighFreqTint = Coral;
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.50f;
        t.Visualizer.BarBrightnessMax = 1.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = TealDarker;
        t.AlbumArtBox.BorderColorHovered = Coral;
        t.AlbumArtBox.BorderColorClicked = CoralLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = OceanMid;
        t.AlbumArtBox.BackgroundColorHovered = OceanSurface;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Coral.x, Coral.y, Coral.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Coral.x, Coral.y, Coral.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.01f, 0.09f, 0.11f, 0.95f);
        t.AlbumArtLightbox.BorderColor = TealDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Coral;
        t.AlbumArtLightbox.TitleColor = TextBright;
        t.AlbumArtLightbox.ArtistColor = TextMuted;

        t.AlbumArtLightbox.MaxWidth = 400.0f;
        t.AlbumArtLightbox.MaxHeight = 400.0f;
        t.AlbumArtLightbox.BorderRounding = 4.0f;
        t.AlbumArtLightbox.BorderThickness = 1.0f;
        t.AlbumArtLightbox.CloseButtonSize = 24.0f;
        t.AlbumArtLightbox.Padding = 30.0f;
        t.AlbumArtLightbox.TitleSpacing = 12.0f;
        t.AlbumArtLightbox.ArtistSpacing = 8.0f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        // ── Dropdown Colors ──
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
        t.SearchBar.backgroundColor = OceanPanel;
        t.SearchBar.borderColor = TealDarker;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Coral;
        t.SearchBar.rowHoverColor = OceanSurface;
        t.SearchBar.separatorColor = TealDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = OceanMid;
        t.SearchBar.inputBorderColor = TealDarker;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Coral;
        t.PlayerBar.ButtonHovered = CoralLight;
        t.PlayerBar.ButtonActive = CoralDark;

        t.PlayerBar.ButtonPrimary = Coral;
        t.PlayerBar.ButtonPrimaryHovered = CoralLight;
        t.PlayerBar.ButtonPrimaryActive = CoralDark;

        t.PlayerBar.SliderTrack = TealDarker;
        t.PlayerBar.SliderGrab = Coral;
        t.PlayerBar.SliderGrabActive = CoralLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = OceanPanel;
        t.ContextMenu.BorderColor = CoralLight;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Coral;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = Teal;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        return t;
    }

} // namespace moosic