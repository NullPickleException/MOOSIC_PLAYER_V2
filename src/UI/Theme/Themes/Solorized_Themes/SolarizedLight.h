//==============================================================================
// SolarizedLight.h
//==============================================================================
// Light solarized theme based on Ethan Schoonover's precision color scheme
// 60% Base3/Base2 backgrounds (#FDF6E3, #EEE8D5)
// 30% Base1/Base0 content surfaces (#93A1A1, #839496)
// 10% Cyan/Blue accents (#2AA198, #268BD2)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateSolarizedLightTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Light backgrounds
        const ImVec4 Base3 = ImVec4(0.992f, 0.965f, 0.890f, 1.00f);    // #FDF6E3 - Lightest bg
        const ImVec4 Base2 = ImVec4(0.933f, 0.910f, 0.835f, 1.00f);    // #EEE8D5 - Light bg

        // 30% - Content surfaces
        const ImVec4 Base1 = ImVec4(0.576f, 0.631f, 0.631f, 1.00f);    // #93A1A1 - Light text/surfaces
        const ImVec4 Base0 = ImVec4(0.514f, 0.580f, 0.588f, 1.00f);    // #839496 - Content

        const ImVec4 Base2Glow = ImVec4(0.933f, 0.910f, 0.835f, 0.20f);
        const ImVec4 Base2VeryLight = ImVec4(0.933f, 0.910f, 0.835f, 0.50f);
        const ImVec4 Base2Subtle = ImVec4(0.933f, 0.910f, 0.835f, 0.10f);

        // 10% - Accent colors
        const ImVec4 Cyan = ImVec4(0.165f, 0.631f, 0.596f, 1.00f);     // #2AA198 - Primary accent
        const ImVec4 Blue = ImVec4(0.149f, 0.545f, 0.824f, 1.00f);     // #268BD2 - Secondary accent
        const ImVec4 Violet = ImVec4(0.424f, 0.443f, 0.769f, 1.00f);   // #6C71C4 - Accent variant
        const ImVec4 Magenta = ImVec4(0.827f, 0.212f, 0.510f, 1.00f);  // #D33682 - Accent highlight
        const ImVec4 CyanDark = ImVec4(0.114f, 0.490f, 0.463f, 1.00f); // Darker cyan
        const ImVec4 CyanLight = ImVec4(0.216f, 0.733f, 0.694f, 1.00f);
        const ImVec4 CyanVeryLight = ImVec4(0.165f, 0.631f, 0.596f, 0.30f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.973f, 0.945f, 0.871f, 1.00f); // Tinted Base3

        // Text
        const ImVec4 Base03 = ImVec4(0.000f, 0.169f, 0.212f, 1.00f);   // #002B36 - Darkest text
        const ImVec4 Base02 = ImVec4(0.027f, 0.212f, 0.259f, 1.00f);   // #073642 - Dark text
        const ImVec4 Base01 = ImVec4(0.345f, 0.431f, 0.459f, 1.00f);   // #586E75 - Secondary text
        const ImVec4 Yellow = ImVec4(0.710f, 0.537f, 0.000f, 1.00f);   // #B58900 - Emphasis

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.824f, 0.804f, 0.749f, 1.00f); // #D2CDBF
        const ImVec4 BorderStrong = ImVec4(0.733f, 0.714f, 0.667f, 1.00f); // #BBB6AA

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.929f, 0.906f, 0.831f, 1.00f); // #EDE7D4 - Slightly darker Base2
        t.TitleBar.BackgroundColorActive = ImVec4(0.929f, 0.906f, 0.831f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.929f, 0.906f, 0.831f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Base01;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Cyan;

        t.TitleBar.TitleTextColor = Base02;
        t.TitleBar.TitleTextColorInactive = Base01;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Cyan;
        t.ContentPanel.TabInactive = Base2;
        t.ContentPanel.TabHovered = ImVec4(0.902f, 0.882f, 0.812f, 1.00f); // Slightly darker Base2
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = Base03;
        t.ContentPanel.TabTextInactive = Base01;

        t.ContentPanel.ButtonNormal = Base1;
        t.ContentPanel.ButtonHovered = Base0;
        t.ContentPanel.ButtonActive = CyanDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = Base0;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = Base2;
        t.Window.ChildBg = Base3;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = Base2;
        t.Window.TitleBarActive = ImVec4(0.910f, 0.890f, 0.820f, 1.00f);

        t.Window.HeaderText = Base02;

        t.Window.TextPrimary = Base02;
        t.Window.TextSecondary = Base01;
        t.Window.TextDisabled = ImVec4(0.576f, 0.631f, 0.631f, 1.00f); // Base1

        t.Window.BrandText = Cyan;

        t.Window.ButtonNormal = Base1;
        t.Window.ButtonHovered = Base0;
        t.Window.ButtonActive = CyanDark;

        t.Window.ProgressBar = Cyan;
        t.Window.PlayingHighlight = Base2Glow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = Base1;
        t.TrackTable.HeaderTextColor = Base3;
        t.TrackTable.HeaderBorderColor = BorderStrong;
        t.TrackTable.HeaderHovered = Base0;
        t.TrackTable.HeaderActive = Cyan;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = Base3;
        t.TrackTable.HeaderTextArtist = Base3;
        t.TrackTable.HeaderTextAlbum = Base3;
        t.TrackTable.HeaderTextExtension = Base3;
        t.TrackTable.HeaderTextDuration = Base3;

        // ── Row colors ──
        t.TrackTable.RowDefault = Base3;
        t.TrackTable.RowDefaultAlt = Base2;
        t.TrackTable.RowHovered = ImVec4(0.902f, 0.882f, 0.812f, 0.50f);
        t.TrackTable.RowClicked = ImVec4(0.165f, 0.631f, 0.596f, 0.15f);
        t.TrackTable.RowSelected = Base1;
        t.TrackTable.RowPlaying = Cyan;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = Base02;
        t.TrackTable.TextDim = Base01;
        t.TrackTable.TextSelected = Base3;
        t.TrackTable.TextPlaying = Base3;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle = Base02;
        t.TrackTable.RowTextArtist = Base01;
        t.TrackTable.RowTextAlbum = Base01;
        t.TrackTable.RowTextExtension = Base1;
        t.TrackTable.RowTextDuration = Base01;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = BorderSubtle;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.60f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = Base2;
        t.TrackTable.ScrollbarGrab = Base1;
        t.TrackTable.ScrollbarGrabHovered = Base0;
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

        t.Visualizer.BackgroundColor = Base2;
        t.Visualizer.WaveformColor = Cyan;
        t.Visualizer.WaveformFillColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.08f);
        t.Visualizer.GridColor = ImVec4(Base1.x, Base1.y, Base1.z, 0.20f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = Base1;

        // ── Color ramp (blue to cyan to teal) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Blue;
        t.Visualizer.SpectrumColorMid = Cyan;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.388f, 0.608f, 0.741f, 1.00f);
        t.Visualizer.SpectrumColorPeak = ImVec4(0.545f, 0.706f, 0.804f, 1.00f);
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = Blue;
        t.Visualizer.HighFreqTint = Cyan;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.60f;
        t.Visualizer.BarBrightnessMax = 1.15f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Cyan;
        t.AlbumArtBox.BorderColorClicked = CyanLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = Base2;
        t.AlbumArtBox.BackgroundColorHovered = ImVec4(0.910f, 0.890f, 0.820f, 1.00f);

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.15f);

        t.AlbumArtBox.PlaceholderTextColor = Base1;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Cyan.x, Cyan.y, Cyan.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = Base3;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.929f, 0.906f, 0.831f, 0.95f);
        t.AlbumArtLightbox.BorderColor = Base0;
        t.AlbumArtLightbox.CloseButtonColor = Base01;
        t.AlbumArtLightbox.CloseButtonHovered = Cyan;
        t.AlbumArtLightbox.TitleColor = Base02;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.12f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = Base0;
        t.SearchBar.textColor = Base02;
        t.SearchBar.highlightTextColor = Cyan;
        t.SearchBar.rowHoverColor = ImVec4(0.902f, 0.882f, 0.812f, 1.00f);
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = Base2;
        t.SearchBar.inputBorderColor = Base0;
        t.SearchBar.inputTextColor = Base02;
        t.SearchBar.inputHintColor = Base01;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Base1;
        t.PlayerBar.ButtonHovered = Base0;
        t.PlayerBar.ButtonActive = CyanDark;

        t.PlayerBar.ButtonPrimary = Base1;
        t.PlayerBar.ButtonPrimaryHovered = Base0;
        t.PlayerBar.ButtonPrimaryActive = CyanDark;

        t.PlayerBar.SliderTrack = BorderStrong;
        t.PlayerBar.SliderGrab = Cyan;
        t.PlayerBar.SliderGrabActive = CyanLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = Base0;
        t.ContextMenu.TextColor = Base02;
        t.ContextMenu.TextDisabledColor = Base1;
        t.ContextMenu.HoverColor = Cyan;
        t.ContextMenu.HoverTextColor = Base3;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.12f);

        return t;
    }

} // namespace moosic