//==============================================================================
// DeepBlueTheme.h
//==============================================================================
// Deep ocean blue theme
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateDeepBlueTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // Key blue: rgb(52, 105, 154)
        const ImVec4 KeyBlue = ImVec4(0.204f, 0.412f, 0.604f, 1.00f);         // 52,105,154
        const ImVec4 KeyBlueDark = ImVec4(0.153f, 0.309f, 0.453f, 1.00f);     // 39,79,116
        const ImVec4 KeyBlueDarker = ImVec4(0.102f, 0.206f, 0.302f, 1.00f);   // 26,53,77
        const ImVec4 KeyBlueLight = ImVec4(0.314f, 0.588f, 0.824f, 1.00f);    // 80,150,210
        const ImVec4 KeyBlueVeryLight = ImVec4(0.314f, 0.588f, 0.824f, 0.5f); // 80,150,210
        const ImVec4 KeyBlueGlow = ImVec4(0.204f, 0.412f, 0.604f, 0.20f);
        const ImVec4 KeyBlueSubtle = ImVec4(0.204f, 0.412f, 0.604f, 0.10f);

        // Cyan accent
        const ImVec4 Cyan = ImVec4(0.000f, 0.706f, 0.784f, 1.00f);         // 0,180,200
        const ImVec4 CyanDark = ImVec4(0.000f, 0.529f, 0.588f, 1.00f);     // 0,135,150
        const ImVec4 CyanDarker = ImVec4(0.000f, 0.353f, 0.392f, 1.00f);   // 0,90,100
        const ImVec4 CyanLight = ImVec4(0.200f, 0.824f, 0.882f, 1.00f);    // 51,210,225
        const ImVec4 CyanGlow = ImVec4(0.000f, 0.706f, 0.784f, 0.20f);

        // Deep ocean backgrounds
        const ImVec4 OceanDeep = ImVec4(0.051f, 0.102f, 0.200f, 1.00f);    // 13,26,51
        const ImVec4 OceanMid = ImVec4(0.086f, 0.184f, 0.329f, 1.00f);     // 22,47,84
        const ImVec4 OceanSurface = ImVec4(0.122f, 0.267f, 0.459f, 1.00f); // 31,68,117
        const ImVec4 OceanPanel = ImVec4(0.039f, 0.078f, 0.161f, 1.00f);   // 10,20,41

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
        t.TitleBar.BottomBorderColor = CyanDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = KeyBlue;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Cyan;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Cyan;
        t.ContentPanel.TabInactive = CyanDarker;
        t.ContentPanel.TabHovered = CyanDark;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = CyanDark;
        t.ContentPanel.ButtonHovered = Cyan;
        t.ContentPanel.ButtonActive = CyanDarker;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = KeyBlue;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = OceanPanel;
        t.Window.ChildBg = OceanDeep;
        t.Window.WindowBorder = CyanDarker;

        t.Window.TitleBar = OceanMid;
        t.Window.TitleBarActive = OceanSurface;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Cyan;

        t.Window.ButtonNormal = CyanDark;
        t.Window.ButtonHovered = Cyan;
        t.Window.ButtonActive = CyanDarker;

        t.Window.ProgressBar = Cyan;
        t.Window.PlayingHighlight = KeyBlueGlow;
        t.Window.SeparatorColor = CyanDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = KeyBlueDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = CyanDarker;
        t.TrackTable.HeaderHovered = OceanSurface;
        t.TrackTable.HeaderActive = Cyan;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = OceanDeep;
        t.TrackTable.RowDefaultAlt = OceanMid;
        t.TrackTable.RowHovered = KeyBlueVeryLight;
        t.TrackTable.RowClicked = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.35f);
        t.TrackTable.RowSelected = KeyBlueLight;
        t.TrackTable.RowPlaying = Cyan;

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
        t.TrackTable.BorderColor = CyanDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(CyanDarker.x, CyanDarker.y, CyanDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = OceanPanel;
        t.TrackTable.ScrollbarGrab = KeyBlueDark;
        t.TrackTable.ScrollbarGrabHovered = KeyBlue;
        t.TrackTable.ScrollbarGrabActive = Cyan;
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
        t.Visualizer.WaveformColor = Cyan;
        t.Visualizer.WaveformFillColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(KeyBlueDark.x, KeyBlueDark.y, KeyBlueDark.z, 0.25f);
        t.Visualizer.BorderColor = CyanDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = KeyBlue;
        t.Visualizer.SpectrumColorMid = Cyan;
        t.Visualizer.SpectrumColorHigh = CyanLight;
        t.Visualizer.SpectrumColorPeak = TextWhite;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = KeyBlue;
        t.Visualizer.HighFreqTint = Cyan;
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.40f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = CyanDarker;
        t.AlbumArtBox.BorderColorHovered = Cyan;
        t.AlbumArtBox.BorderColorClicked = CyanLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = OceanMid;
        t.AlbumArtBox.BackgroundColorHovered = OceanSurface;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.03f, 0.05f, 0.10f, 0.95f);
        t.AlbumArtLightbox.BorderColor = KeyBlueDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Cyan;
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
        t.SearchBar.borderColor = CyanDarker;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Cyan;
        t.SearchBar.rowHoverColor = OceanSurface;
        t.SearchBar.separatorColor = CyanDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = OceanMid;
        t.SearchBar.inputBorderColor = CyanDarker;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Cyan;
        t.PlayerBar.ButtonHovered = CyanLight;
        t.PlayerBar.ButtonActive = CyanDark;

        t.PlayerBar.ButtonPrimary = Cyan;
        t.PlayerBar.ButtonPrimaryHovered = CyanLight;
        t.PlayerBar.ButtonPrimaryActive = CyanDark;

        t.PlayerBar.SliderTrack = CyanDarker;
        t.PlayerBar.SliderGrab = Cyan;
        t.PlayerBar.SliderGrabActive = CyanLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = OceanPanel;
        t.ContextMenu.BorderColor = KeyBlue;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Cyan;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = CyanDark;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        return t;
    }

} // namespace moosic