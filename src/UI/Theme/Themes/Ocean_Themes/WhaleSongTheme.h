//==============================================================================
// WhaleSongTheme.h
//==============================================================================
// Serene deep ocean theme with grey-blue, muted blue, and light blue-grey tones
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateWhaleSongTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // Dark Grey-Blue - #213448
        const ImVec4 GreyBlue = ImVec4(0.129f, 0.204f, 0.282f, 1.00f);         // 33,52,72
        const ImVec4 GreyBlueDark = ImVec4(0.098f, 0.153f, 0.212f, 1.00f);     // 25,39,54
        const ImVec4 GreyBlueDarker = ImVec4(0.065f, 0.102f, 0.141f, 1.00f);   // 17,26,36
        const ImVec4 GreyBlueLight = ImVec4(0.200f, 0.278f, 0.361f, 1.00f);    // 51,71,92
        const ImVec4 GreyBlueVeryLight = ImVec4(0.200f, 0.278f, 0.361f, 0.5f); // 51,71,92
        const ImVec4 GreyBlueGlow = ImVec4(0.129f, 0.204f, 0.282f, 0.20f);
        const ImVec4 GreyBlueSubtle = ImVec4(0.129f, 0.204f, 0.282f, 0.10f);

        // Muted Blue - #547792
        const ImVec4 MutedBlue = ImVec4(0.329f, 0.467f, 0.573f, 1.00f);         // 84,119,146
        const ImVec4 MutedBlueDark = ImVec4(0.247f, 0.353f, 0.431f, 1.00f);     // 63,90,110
        const ImVec4 MutedBlueDarker = ImVec4(0.165f, 0.239f, 0.290f, 1.00f);   // 42,61,74
        const ImVec4 MutedBlueLight = ImVec4(0.451f, 0.580f, 0.675f, 1.00f);    // 115,148,172
        const ImVec4 MutedBlueGlow = ImVec4(0.329f, 0.467f, 0.573f, 0.20f);

        // Light Blue-Grey - #94B4C1
        const ImVec4 LightBlue = ImVec4(0.580f, 0.706f, 0.757f, 1.00f);         // 148,180,193
        const ImVec4 LightBlueDark = ImVec4(0.463f, 0.565f, 0.606f, 1.00f);     // 118,144,155
        const ImVec4 LightBlueDarker = ImVec4(0.349f, 0.424f, 0.455f, 1.00f);   // 89,108,116
        const ImVec4 LightBlueLight = ImVec4(0.690f, 0.792f, 0.831f, 1.00f);    // 176,202,212

        // Deep ocean backgrounds (from GreyBlue family)
        const ImVec4 OceanDeep = ImVec4(0.059f, 0.090f, 0.125f, 1.00f);    // 15,23,32
        const ImVec4 OceanMid = ImVec4(0.078f, 0.114f, 0.157f, 1.00f);     // 20,29,40
        const ImVec4 OceanSurface = ImVec4(0.098f, 0.137f, 0.184f, 1.00f); // 25,35,47
        const ImVec4 OceanPanel = ImVec4(0.047f, 0.071f, 0.102f, 1.00f);   // 12,18,26

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
        t.TitleBar.BottomBorderColor = GreyBlueDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = MutedBlue;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = GreyBlue;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = MutedBlue;
        t.ContentPanel.TabInactive = GreyBlueDarker;
        t.ContentPanel.TabHovered = GreyBlue;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = GreyBlue;
        t.ContentPanel.ButtonHovered = MutedBlue;
        t.ContentPanel.ButtonActive = MutedBlueDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = MutedBlue;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = OceanPanel;
        t.Window.ChildBg = OceanDeep;
        t.Window.WindowBorder = GreyBlueDarker;

        t.Window.TitleBar = OceanMid;
        t.Window.TitleBarActive = OceanSurface;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = MutedBlue;

        t.Window.ButtonNormal = GreyBlue;
        t.Window.ButtonHovered = MutedBlue;
        t.Window.ButtonActive = MutedBlueDark;

        t.Window.ProgressBar = MutedBlue;
        t.Window.PlayingHighlight = GreyBlueGlow;
        t.Window.SeparatorColor = GreyBlueDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = GreyBlue;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = GreyBlueDarker;
        t.TrackTable.HeaderHovered = OceanSurface;
        t.TrackTable.HeaderActive = MutedBlue;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = OceanDeep;
        t.TrackTable.RowDefaultAlt = OceanMid;
        t.TrackTable.RowHovered = GreyBlueVeryLight;
        t.TrackTable.RowClicked = ImVec4(MutedBlue.x, MutedBlue.y, MutedBlue.z, 0.35f);
        t.TrackTable.RowSelected = MutedBlue;
        t.TrackTable.RowPlaying = LightBlue;

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
        t.TrackTable.BorderColor = GreyBlueDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(GreyBlueDarker.x, GreyBlueDarker.y, GreyBlueDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = OceanPanel;
        t.TrackTable.ScrollbarGrab = GreyBlue;
        t.TrackTable.ScrollbarGrabHovered = MutedBlue;
        t.TrackTable.ScrollbarGrabActive = LightBlue;
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
        t.Visualizer.WaveformColor = MutedBlue;
        t.Visualizer.WaveformFillColor = ImVec4(MutedBlue.x, MutedBlue.y, MutedBlue.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(GreyBlue.x, GreyBlue.y, GreyBlue.z, 0.25f);
        t.Visualizer.BorderColor = GreyBlueDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = GreyBlue;
        t.Visualizer.SpectrumColorMid = MutedBlue;
        t.Visualizer.SpectrumColorHigh = LightBlue;
        t.Visualizer.SpectrumColorPeak = LightBlueLight;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = GreyBlue;
        t.Visualizer.HighFreqTint = LightBlue;
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = GreyBlueDarker;
        t.AlbumArtBox.BorderColorHovered = MutedBlue;
        t.AlbumArtBox.BorderColorClicked = LightBlue;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = OceanMid;
        t.AlbumArtBox.BackgroundColorHovered = OceanSurface;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(MutedBlue.x, MutedBlue.y, MutedBlue.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(MutedBlue.x, MutedBlue.y, MutedBlue.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.03f, 0.05f, 0.07f, 0.95f);
        t.AlbumArtLightbox.BorderColor = GreyBlue;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = LightBlue;
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
        t.SearchBar.borderColor = GreyBlueDarker;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = MutedBlue;
        t.SearchBar.rowHoverColor = OceanSurface;
        t.SearchBar.separatorColor = GreyBlueDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = OceanMid;
        t.SearchBar.inputBorderColor = GreyBlueDarker;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = GreyBlue;
        t.PlayerBar.ButtonHovered = MutedBlue;
        t.PlayerBar.ButtonActive = MutedBlueDark;

        t.PlayerBar.ButtonPrimary = GreyBlue;
        t.PlayerBar.ButtonPrimaryHovered = MutedBlue;
        t.PlayerBar.ButtonPrimaryActive = MutedBlueDark;

        t.PlayerBar.SliderTrack = GreyBlueDarker;
        t.PlayerBar.SliderGrab = MutedBlue;
        t.PlayerBar.SliderGrabActive = LightBlue;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = OceanPanel;
        t.ContextMenu.BorderColor = MutedBlue;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = MutedBlue;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = GreyBlue;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        return t;
    }

} // namespace moosic