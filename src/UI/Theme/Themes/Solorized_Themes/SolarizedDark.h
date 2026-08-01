//==============================================================================
// SolarizedDark.h
//==============================================================================
// Dark solarized theme based on Ethan Schoonover's precision color scheme
// 60% Base03/Base02 backgrounds (#002B36, #073642)
// 30% Base01/Base00 content surfaces (#586E75, #657B83)
// 10% Cyan/Blue accents (#2AA198, #268BD2)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateSolarizedDarkTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Dark backgrounds
        const ImVec4 Base03 = ImVec4(0.000f, 0.169f, 0.212f, 1.00f);   // #002B36 - Deepest bg
        const ImVec4 Base02 = ImVec4(0.027f, 0.212f, 0.259f, 1.00f);   // #073642 - Dark bg

        // 30% - Content surfaces
        const ImVec4 Base01 = ImVec4(0.345f, 0.431f, 0.459f, 1.00f);   // #586E75 - Comments
        const ImVec4 Base00 = ImVec4(0.396f, 0.482f, 0.514f, 1.00f);   // #657B83 - Content

        const ImVec4 Base02Glow = ImVec4(0.027f, 0.212f, 0.259f, 0.20f);
        const ImVec4 Base02VeryLight = ImVec4(0.027f, 0.212f, 0.259f, 0.50f);
        const ImVec4 Base02Subtle = ImVec4(0.027f, 0.212f, 0.259f, 0.10f);

        // 10% - Accent colors
        const ImVec4 Cyan = ImVec4(0.165f, 0.631f, 0.596f, 1.00f);     // #2AA198 - Primary accent
        const ImVec4 Blue = ImVec4(0.149f, 0.545f, 0.824f, 1.00f);     // #268BD2 - Secondary accent
        const ImVec4 Violet = ImVec4(0.424f, 0.443f, 0.769f, 1.00f);   // #6C71C4 - Accent variant
        const ImVec4 Magenta = ImVec4(0.827f, 0.212f, 0.510f, 1.00f);  // #D33682 - Accent highlight
        const ImVec4 CyanDark = ImVec4(0.114f, 0.490f, 0.463f, 1.00f); // Darker cyan
        const ImVec4 CyanLight = ImVec4(0.216f, 0.733f, 0.694f, 1.00f);
        const ImVec4 CyanVeryLight = ImVec4(0.216f, 0.733f, 0.694f, 0.50f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.043f, 0.235f, 0.286f, 1.00f); // #0A3A47

        // Text
        const ImVec4 Base0 = ImVec4(0.514f, 0.580f, 0.588f, 1.00f);    // #839496 - Primary text
        const ImVec4 Base1 = ImVec4(0.576f, 0.631f, 0.631f, 1.00f);    // #93A1A1 - Bright text
        const ImVec4 Base2 = ImVec4(0.933f, 0.910f, 0.835f, 1.00f);    // #EEE8D5 - Lightest
        const ImVec4 Base3 = ImVec4(0.992f, 0.965f, 0.890f, 1.00f);    // #FDF6E3 - White
        const ImVec4 Yellow = ImVec4(0.710f, 0.537f, 0.000f, 1.00f);   // #B58900 - Emphasis

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.180f, 0.325f, 0.365f, 1.00f); // #2E535D

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.000f, 0.129f, 0.161f, 1.00f); // #002129 - Darker Base03
        t.TitleBar.BackgroundColorActive = ImVec4(0.000f, 0.129f, 0.161f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.129f, 0.161f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Base01;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Cyan;

        t.TitleBar.TitleTextColor = Base1;
        t.TitleBar.TitleTextColorInactive = Base01;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Cyan;
        t.ContentPanel.TabInactive = Base02;
        t.ContentPanel.TabHovered = ImVec4(0.055f, 0.251f, 0.302f, 1.00f); // Slightly lighter Base02
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = Base2;
        t.ContentPanel.TabTextInactive = Base01;

        t.ContentPanel.ButtonNormal = Base01;
        t.ContentPanel.ButtonHovered = Base00;
        t.ContentPanel.ButtonActive = CyanDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = Base00;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = Base02;
        t.Window.ChildBg = Base03;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = Base02;
        t.Window.TitleBarActive = ImVec4(0.039f, 0.235f, 0.286f, 1.00f); // Slightly lighter

        t.Window.HeaderText = Base1;

        t.Window.TextPrimary = Base0;
        t.Window.TextSecondary = Base01;
        t.Window.TextDisabled = ImVec4(0.255f, 0.345f, 0.373f, 1.00f); // Muted

        t.Window.BrandText = Cyan;

        t.Window.ButtonNormal = Base01;
        t.Window.ButtonHovered = Base00;
        t.Window.ButtonActive = CyanDark;

        t.Window.ProgressBar = Cyan;
        t.Window.PlayingHighlight = Base02Glow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = Base01;
        t.TrackTable.HeaderTextColor = Base1;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = Base00;
        t.TrackTable.HeaderActive = Cyan;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = Base1;
        t.TrackTable.HeaderTextArtist = Base1;
        t.TrackTable.HeaderTextAlbum = Base1;
        t.TrackTable.HeaderTextExtension = Base1;
        t.TrackTable.HeaderTextDuration = Base1;

        // ── Row colors ──
        t.TrackTable.RowDefault = Base03;
        t.TrackTable.RowDefaultAlt = Base02;
        t.TrackTable.RowHovered = Base02VeryLight;
        t.TrackTable.RowClicked = ImVec4(0.067f, 0.322f, 0.369f, 1.00f); // #11525E
        t.TrackTable.RowSelected = Base01;
        t.TrackTable.RowPlaying = Cyan;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = Base0;
        t.TrackTable.TextDim = Base01;
        t.TrackTable.TextSelected = Base2;
        t.TrackTable.TextPlaying = Base3;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle = Base0;
        t.TrackTable.RowTextArtist = Base01;
        t.TrackTable.RowTextAlbum = Base01;
        t.TrackTable.RowTextExtension = ImVec4(0.255f, 0.345f, 0.373f, 1.00f); // Muted
        t.TrackTable.RowTextDuration = Base01;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = BorderSubtle;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = Base02;
        t.TrackTable.ScrollbarGrab = Base01;
        t.TrackTable.ScrollbarGrabHovered = Base00;
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

        t.Visualizer.BackgroundColor = Base02;
        t.Visualizer.WaveformColor = Cyan;
        t.Visualizer.WaveformFillColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(Base01.x, Base01.y, Base01.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = Base01;

        // ── Color ramp (cyan to blue to violet) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Blue;
        t.Visualizer.SpectrumColorMid = Cyan;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.388f, 0.608f, 0.741f, 1.00f); // Lighter cyan
        t.Visualizer.SpectrumColorPeak = ImVec4(0.545f, 0.706f, 0.804f, 1.00f); // Light blue-cyan
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = Blue;
        t.Visualizer.HighFreqTint = Cyan;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Cyan;
        t.AlbumArtBox.BorderColorClicked = CyanLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = Base02;
        t.AlbumArtBox.BackgroundColorHovered = ImVec4(0.039f, 0.235f, 0.286f, 1.00f);

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        t.AlbumArtBox.PlaceholderTextColor = Base01;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = Base2;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.000f, 0.129f, 0.161f, 0.95f);
        t.AlbumArtLightbox.BorderColor = Base01;
        t.AlbumArtLightbox.CloseButtonColor = Base01;
        t.AlbumArtLightbox.CloseButtonHovered = Cyan;
        t.AlbumArtLightbox.TitleColor = Base1;
        t.AlbumArtLightbox.ArtistColor = Base01;

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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = Base00;
        t.SearchBar.textColor = Base0;
        t.SearchBar.highlightTextColor = Cyan;
        t.SearchBar.rowHoverColor = ImVec4(0.055f, 0.251f, 0.302f, 1.00f);
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = Base02;
        t.SearchBar.inputBorderColor = Base00;
        t.SearchBar.inputTextColor = Base0;
        t.SearchBar.inputHintColor = Base01;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Base01;
        t.PlayerBar.ButtonHovered = Base00;
        t.PlayerBar.ButtonActive = CyanDark;

        t.PlayerBar.ButtonPrimary = Base01;
        t.PlayerBar.ButtonPrimaryHovered = Base00;
        t.PlayerBar.ButtonPrimaryActive = CyanDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = Cyan;
        t.PlayerBar.SliderGrabActive = CyanLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = Base00;
        t.ContextMenu.TextColor = Base0;
        t.ContextMenu.TextDisabledColor = ImVec4(0.255f, 0.345f, 0.373f, 1.00f);
        t.ContextMenu.HoverColor = Cyan;
        t.ContextMenu.HoverTextColor = Base3;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic