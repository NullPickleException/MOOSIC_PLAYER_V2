//==============================================================================
// SeafoamTheme.h
//==============================================================================
// Bright coastal theme using 60/30/10 rule:
// 60% Deep Teal Ocean (#1A2E2C, #1F3633, #243E3A)
// 30% Bright Seafoam Cyan-Green (#7EC8B8, #94D4C7, #B8E5DA)
// 10% Warm Gold (#C8A96B)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateSeafoamTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Deep Teal Ocean backgrounds
        const ImVec4 OceanDark = ImVec4(0.102f, 0.180f, 0.173f, 1.00f);     // #1A2E2C - 26,46,44
        const ImVec4 OceanMid = ImVec4(0.122f, 0.212f, 0.200f, 1.00f);      // #1F3633 - 31,54,51
        const ImVec4 OceanLight = ImVec4(0.141f, 0.243f, 0.227f, 1.00f);    // #243E3A - 36,62,58
        const ImVec4 OceanPanel = ImVec4(0.082f, 0.149f, 0.141f, 1.00f);    // Darker panel
        const ImVec4 OceanDeep = ImVec4(0.063f, 0.118f, 0.110f, 1.00f);     // Deepest bg
        
        const ImVec4 OceanGlow = ImVec4(0.122f, 0.212f, 0.200f, 0.20f);
        const ImVec4 OceanVeryLight = ImVec4(0.122f, 0.212f, 0.200f, 0.5f);
        const ImVec4 OceanSubtle = ImVec4(0.122f, 0.212f, 0.200f, 0.10f);

        // 30% - Bright Seafoam Cyan-Green
        const ImVec4 SeafoamDarker = ImVec4(0.380f, 0.667f, 0.604f, 1.00f);  // #61AA9A
        const ImVec4 SeafoamDark = ImVec4(0.494f, 0.784f, 0.722f, 1.00f);    // #7EC8B8 - 126,200,184
        const ImVec4 Seafoam = ImVec4(0.580f, 0.831f, 0.780f, 1.00f);       // #94D4C7 - 148,212,199
        const ImVec4 SeafoamLight = ImVec4(0.722f, 0.898f, 0.855f, 1.00f);  // #B8E5DA - 184,229,218
        const ImVec4 SeafoamVeryLight = ImVec4(0.580f, 0.831f, 0.780f, 0.5f);

        // 10% - Warm Gold accent
        const ImVec4 Gold = ImVec4(0.784f, 0.663f, 0.420f, 1.00f);         // #C8A96B - 200,169,107
        const ImVec4 GoldDark = ImVec4(0.627f, 0.529f, 0.333f, 1.00f);     // Darker gold
        const ImVec4 GoldDarker = ImVec4(0.471f, 0.396f, 0.247f, 1.00f);   // Even darker
        const ImVec4 GoldLight = ImVec4(0.859f, 0.765f, 0.569f, 1.00f);    // Lighter gold

        // Search dropdown - lighter tint of OceanMid (60% family)
        const ImVec4 SearchDropdownBg = ImVec4(0.165f, 0.263f, 0.247f, 1.00f);  // Tinted lighter

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
        t.TitleBar.BottomBorderColor = OceanDark;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = SeafoamDark;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Gold;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Seafoam;
        t.ContentPanel.TabInactive = OceanDark;
        t.ContentPanel.TabHovered = OceanLight;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = OceanLight;
        t.ContentPanel.ButtonHovered = SeafoamDark;
        t.ContentPanel.ButtonActive = SeafoamDarker;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = SeafoamDark;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = OceanPanel;
        t.Window.ChildBg = OceanDeep;
        t.Window.WindowBorder = OceanDark;

        t.Window.TitleBar = OceanDark;
        t.Window.TitleBarActive = OceanMid;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Seafoam;

        t.Window.ButtonNormal = OceanLight;
        t.Window.ButtonHovered = SeafoamDark;
        t.Window.ButtonActive = SeafoamDarker;

        t.Window.ProgressBar = Seafoam;
        t.Window.PlayingHighlight = OceanGlow;
        t.Window.SeparatorColor = OceanDark;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = OceanMid;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = OceanDark;
        t.TrackTable.HeaderHovered = OceanLight;
        t.TrackTable.HeaderActive = Seafoam;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = OceanDeep;
        t.TrackTable.RowDefaultAlt = OceanDark;
        t.TrackTable.RowHovered = OceanVeryLight;
        t.TrackTable.RowClicked = ImVec4(SeafoamDark.x, SeafoamDark.y, SeafoamDark.z, 0.35f);
        t.TrackTable.RowSelected = Seafoam;
        t.TrackTable.RowPlaying = Gold;

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
        t.TrackTable.BorderColor = OceanDark;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(OceanDark.x, OceanDark.y, OceanDark.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = OceanPanel;
        t.TrackTable.ScrollbarGrab = OceanLight;
        t.TrackTable.ScrollbarGrabHovered = SeafoamDark;
        t.TrackTable.ScrollbarGrabActive = Seafoam;
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
        t.Visualizer.WaveformColor = Seafoam;
        t.Visualizer.WaveformFillColor = ImVec4(Seafoam.x, Seafoam.y, Seafoam.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(OceanMid.x, OceanMid.y, OceanMid.z, 0.25f);
        t.Visualizer.BorderColor = OceanDark;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (bright seafoam to golden sunlight) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = SeafoamDarker;
        t.Visualizer.SpectrumColorMid = Seafoam;
        t.Visualizer.SpectrumColorHigh = Gold;
        t.Visualizer.SpectrumColorPeak = GoldLight;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint (cyan-green to warm gold) ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = SeafoamDarker;
        t.Visualizer.HighFreqTint = Gold;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.25f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = OceanDark;
        t.AlbumArtBox.BorderColorHovered = Seafoam;
        t.AlbumArtBox.BorderColorClicked = SeafoamLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = OceanDark;
        t.AlbumArtBox.BackgroundColorHovered = OceanMid;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Seafoam.x, Seafoam.y, Seafoam.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Seafoam.x, Seafoam.y, Seafoam.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.04f, 0.09f, 0.09f, 0.95f);
        t.AlbumArtLightbox.BorderColor = OceanMid;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Seafoam;
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

        // ── Dropdown Colors (lighter tint of OceanMid) ──
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = SeafoamDark;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Seafoam;
        t.SearchBar.rowHoverColor = OceanLight;
        t.SearchBar.separatorColor = OceanMid;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = OceanDark;
        t.SearchBar.inputBorderColor = SeafoamDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = OceanLight;
        t.PlayerBar.ButtonHovered = Seafoam;
        t.PlayerBar.ButtonActive = SeafoamDark;

        t.PlayerBar.ButtonPrimary = OceanLight;
        t.PlayerBar.ButtonPrimaryHovered = Seafoam;
        t.PlayerBar.ButtonPrimaryActive = SeafoamDark;

        t.PlayerBar.SliderTrack = OceanDark;
        t.PlayerBar.SliderGrab = Seafoam;
        t.PlayerBar.SliderGrabActive = SeafoamLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = SeafoamDark;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Seafoam;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = OceanMid;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        return t;
    }

} // namespace moosic