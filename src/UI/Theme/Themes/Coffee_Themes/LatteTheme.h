//==============================================================================
// LatteTheme.h
//==============================================================================
// Warm milk coffee theme using 80/15/5 rule:
// 80% Warm latte beige backgrounds (#E8DDD2, #EDE3D8, #F2E9DF, #EEE4DA, #E6D9CC)
// 15% Caramel surfaces (#C4A882, #D4BC9A, #DFC9AA)
// 5% Warm caramel accent (#B88450)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateLatteTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 80% - Warm latte beige backgrounds
        const ImVec4 LatteDeep = ImVec4(0.910f, 0.867f, 0.824f, 1.00f);    // #E8DDD2
        const ImVec4 LattePanel = ImVec4(0.929f, 0.890f, 0.847f, 1.00f);   // #EDE3D8
        const ImVec4 LatteDefault = ImVec4(0.949f, 0.914f, 0.875f, 1.00f); // #F2E9DF
        const ImVec4 LatteAlt = ImVec4(0.933f, 0.894f, 0.855f, 1.00f);     // #EEE4DA
        const ImVec4 LatteSurface = ImVec4(0.902f, 0.851f, 0.800f, 1.00f); // #E6D9CC

        const ImVec4 LatteGlow = ImVec4(0.910f, 0.867f, 0.824f, 0.20f);
        const ImVec4 LatteVeryLight = ImVec4(0.910f, 0.867f, 0.824f, 0.5f);
        const ImVec4 LatteSubtle = ImVec4(0.910f, 0.867f, 0.824f, 0.10f);

        // 15% - Caramel surfaces
        const ImVec4 CaramelDark = ImVec4(0.769f, 0.659f, 0.510f, 1.00f);   // #C4A882
        const ImVec4 CaramelMid = ImVec4(0.831f, 0.737f, 0.604f, 1.00f);    // #D4BC9A
        const ImVec4 CaramelLight = ImVec4(0.875f, 0.788f, 0.667f, 1.00f);  // #DFC9AA
        const ImVec4 CaramelDarker = ImVec4(0.659f, 0.557f, 0.420f, 1.00f); // Darker variant

        // 5% - Warm caramel accent
        const ImVec4 CaramelAccent = ImVec4(0.722f, 0.518f, 0.314f, 1.00f);     // #B88450
        const ImVec4 CaramelAccentDark = ImVec4(0.604f, 0.420f, 0.227f, 1.00f); // #9A6B3A
        const ImVec4 CaramelAccentDarker = ImVec4(0.478f, 0.322f, 0.188f, 1.00f);
        const ImVec4 CaramelAccentLight = ImVec4(0.784f, 0.604f, 0.416f, 1.00f); // #C89A6A
        const ImVec4 CaramelAccentVeryLight = ImVec4(0.784f, 0.604f, 0.416f, 0.5f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.961f, 0.929f, 0.898f, 1.00f);

        // Text
        const ImVec4 TextBright = ImVec4(0.239f, 0.169f, 0.102f, 1.00f); // #3D2B1A
        const ImVec4 TextMuted = ImVec4(0.478f, 0.396f, 0.314f, 1.00f);  // #7A6550
        const ImVec4 TextDim = ImVec4(0.659f, 0.565f, 0.471f, 1.00f);    // #A89078
        const ImVec4 TextWhite = ImVec4(1.000f, 0.984f, 0.969f, 1.00f);  // #FFFBF7

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.831f, 0.737f, 0.604f, 1.00f); // #D4BC9A

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.878f, 0.827f, 0.773f, 1.00f); // #E0D3C5 - Darker than LatteDeep
        t.TitleBar.BackgroundColorActive = ImVec4(0.878f, 0.827f, 0.773f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.878f, 0.827f, 0.773f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = CaramelDark;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = CaramelAccent;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;
        
        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = CaramelAccent;
        t.ContentPanel.TabInactive = LatteAlt;
        t.ContentPanel.TabHovered = LatteSurface;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = CaramelDark;
        t.ContentPanel.ButtonHovered = CaramelMid;
        t.ContentPanel.ButtonActive = CaramelAccentDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = CaramelDark;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = LattePanel;
        t.Window.ChildBg = LatteDeep;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = LatteDefault;
        t.Window.TitleBarActive = LatteAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = CaramelAccent;

        t.Window.ButtonNormal = CaramelDark;
        t.Window.ButtonHovered = CaramelMid;
        t.Window.ButtonActive = CaramelAccentDark;

        t.Window.ProgressBar = CaramelAccent;
        t.Window.PlayingHighlight = LatteGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = CaramelDark;
        t.TrackTable.HeaderTextColor = TextWhite;
        t.TrackTable.HeaderBorderColor = CaramelDarker;
        t.TrackTable.HeaderHovered = CaramelMid;
        t.TrackTable.HeaderActive = CaramelAccent;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextWhite;
        t.TrackTable.HeaderTextArtist = TextWhite;
        t.TrackTable.HeaderTextAlbum = TextWhite;
        t.TrackTable.HeaderTextExtension = TextWhite;
        t.TrackTable.HeaderTextDuration = TextWhite;

        // ── Row colors ──
        t.TrackTable.RowDefault = LatteDeep;
        t.TrackTable.RowDefaultAlt = LatteDefault;
        t.TrackTable.RowHovered = CaramelAccentVeryLight;
        t.TrackTable.RowClicked = CaramelAccentDarker;
        t.TrackTable.RowSelected = CaramelDark;
        t.TrackTable.RowPlaying = CaramelAccent;

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
        t.TrackTable.BorderColor = BorderSubtle;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = LattePanel;
        t.TrackTable.ScrollbarGrab = CaramelDark;
        t.TrackTable.ScrollbarGrabHovered = CaramelMid;
        t.TrackTable.ScrollbarGrabActive = CaramelAccent;
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

        t.Visualizer.BackgroundColor = LattePanel;
        t.Visualizer.WaveformColor = CaramelAccent;
        t.Visualizer.WaveformFillColor = ImVec4(CaramelAccent.x, CaramelAccent.y, CaramelAccent.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(CaramelDark.x, CaramelDark.y, CaramelDark.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (caramel warmth) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = CaramelAccentDark;
        t.Visualizer.SpectrumColorMid = CaramelAccent;
        t.Visualizer.SpectrumColorHigh = CaramelAccentLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.831f, 0.659f, 0.471f, 1.00f); // #D4A878
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = CaramelDark;
        t.Visualizer.HighFreqTint = CaramelAccent;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.50f;
        t.Visualizer.BarBrightnessMax = 1.10f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = CaramelAccent;
        t.AlbumArtBox.BorderColorClicked = CaramelAccentLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = LatteDefault;
        t.AlbumArtBox.BackgroundColorHovered = LatteAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.12f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(CaramelAccent.x, CaramelAccent.y, CaramelAccent.z, 0.06f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(CaramelAccent.x, CaramelAccent.y, CaramelAccent.z, 0.14f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.91f, 0.87f, 0.82f, 0.95f);
        t.AlbumArtLightbox.BorderColor = CaramelDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = CaramelAccent;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.18f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = CaramelDark;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = CaramelAccent;
        t.SearchBar.rowHoverColor = LatteAlt;
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = LatteDefault;
        t.SearchBar.inputBorderColor = CaramelDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = CaramelDark;
        t.PlayerBar.ButtonHovered = CaramelMid;
        t.PlayerBar.ButtonActive = CaramelAccentDark;

        t.PlayerBar.ButtonPrimary = CaramelDark;
        t.PlayerBar.ButtonPrimaryHovered = CaramelMid;
        t.PlayerBar.ButtonPrimaryActive = CaramelAccentDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = CaramelAccent;
        t.PlayerBar.SliderGrabActive = CaramelAccentLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = CaramelDark;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = CaramelAccent;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.18f);

        return t;
    }

} // namespace moosic