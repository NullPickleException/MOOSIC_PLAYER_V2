//==============================================================================
// CoffeeBlackTheme.h
//==============================================================================
// Dark intense espresso theme using 60/30/10 rule:
// 60% Near-black brown backgrounds (#0F0C0A, #141110, #1A1614, #1F1B18, #24201D)
// 30% Dark brown surfaces (#3D3028, #524335, #615040)
// 10% Warm bronze accent (#B88450)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCoffeeBlackTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Near-black brown backgrounds
        const ImVec4 EspressoDeep = ImVec4(0.059f, 0.047f, 0.039f, 1.00f);    // #0F0C0A
        const ImVec4 EspressoPanel = ImVec4(0.078f, 0.067f, 0.063f, 1.00f);   // #141110
        const ImVec4 EspressoDefault = ImVec4(0.102f, 0.086f, 0.078f, 1.00f); // #1A1614
        const ImVec4 EspressoAlt = ImVec4(0.122f, 0.106f, 0.094f, 1.00f);     // #1F1B18
        const ImVec4 EspressoSurface = ImVec4(0.141f, 0.125f, 0.114f, 1.00f); // #24201D

        const ImVec4 EspressoGlow = ImVec4(0.102f, 0.086f, 0.078f, 0.20f);
        const ImVec4 EspressoVeryLight = ImVec4(0.102f, 0.086f, 0.078f, 0.5f);
        const ImVec4 EspressoSubtle = ImVec4(0.102f, 0.086f, 0.078f, 0.10f);

        // 30% - Dark brown surfaces
        const ImVec4 DarkBrown = ImVec4(0.239f, 0.188f, 0.157f, 1.00f);      // #3D3028
        const ImVec4 DarkBrownMid = ImVec4(0.322f, 0.263f, 0.208f, 1.00f);   // #524335
        const ImVec4 DarkBrownLight = ImVec4(0.380f, 0.314f, 0.251f, 1.00f); // #615040
        const ImVec4 DarkBrownDarker = ImVec4(0.180f, 0.141f, 0.118f, 1.00f);

        // 10% - Warm bronze accent
        const ImVec4 Bronze = ImVec4(0.722f, 0.518f, 0.314f, 1.00f);       // #B88450
        const ImVec4 BronzeDark = ImVec4(0.588f, 0.416f, 0.227f, 1.00f);   // #966A3A
        const ImVec4 BronzeDarker = ImVec4(0.439f, 0.314f, 0.157f, 1.00f); // #705028
        const ImVec4 BronzeLight = ImVec4(0.784f, 0.604f, 0.416f, 1.00f);  // #C89A6A
        const ImVec4 BronzeVeryLight = ImVec4(0.784f, 0.604f, 0.416f, 0.5f);

        // Search dropdown - lighter tint
        const ImVec4 SearchDropdownBg = ImVec4(0.137f, 0.118f, 0.102f, 1.00f);

        // Text
        const ImVec4 TextBright = ImVec4(0.929f, 0.910f, 0.890f, 1.00f); // #EDE8E3
        const ImVec4 TextMuted = ImVec4(0.659f, 0.596f, 0.533f, 1.00f);  // #A89888
        const ImVec4 TextDim = ImVec4(0.420f, 0.369f, 0.322f, 1.00f);    // #6B5E52
        const ImVec4 TextWhite = ImVec4(0.961f, 0.941f, 0.922f, 1.00f);  // #F5F0EB

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.176f, 0.149f, 0.125f, 1.00f); // #2D2620

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.039f, 0.031f, 0.024f, 1.00f); // #0A0806 - Darker than EspressoDeep
        t.TitleBar.BackgroundColorActive = ImVec4(0.039f, 0.031f, 0.024f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.039f, 0.031f, 0.024f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = DarkBrownMid;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Bronze;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Bronze;
        t.ContentPanel.TabInactive = EspressoDefault;
        t.ContentPanel.TabHovered = EspressoAlt;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = DarkBrown;
        t.ContentPanel.ButtonHovered = DarkBrownMid;
        t.ContentPanel.ButtonActive = BronzeDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = DarkBrownMid;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = EspressoPanel;
        t.Window.ChildBg = EspressoDeep;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = EspressoDefault;
        t.Window.TitleBarActive = EspressoAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Bronze;

        t.Window.ButtonNormal = DarkBrown;
        t.Window.ButtonHovered = DarkBrownMid;
        t.Window.ButtonActive = BronzeDark;

        t.Window.ProgressBar = Bronze;
        t.Window.PlayingHighlight = EspressoGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = DarkBrown;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = EspressoSurface;
        t.TrackTable.HeaderActive = Bronze;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = EspressoDeep;
        t.TrackTable.RowDefaultAlt = EspressoDefault;
        t.TrackTable.RowHovered = EspressoVeryLight;
        t.TrackTable.RowClicked = BronzeDarker;
        t.TrackTable.RowSelected = DarkBrown;
        t.TrackTable.RowPlaying = Bronze;

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
        t.TrackTable.ScrollbarBg = EspressoPanel;
        t.TrackTable.ScrollbarGrab = DarkBrown;
        t.TrackTable.ScrollbarGrabHovered = DarkBrownMid;
        t.TrackTable.ScrollbarGrabActive = Bronze;
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

        t.Visualizer.BackgroundColor = EspressoPanel;
        t.Visualizer.WaveformColor = Bronze;
        t.Visualizer.WaveformFillColor = ImVec4(Bronze.x, Bronze.y, Bronze.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(DarkBrown.x, DarkBrown.y, DarkBrown.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (dark bronze to warm gold) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = BronzeDark;
        t.Visualizer.SpectrumColorMid = Bronze;
        t.Visualizer.SpectrumColorHigh = BronzeLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.831f, 0.659f, 0.471f, 1.00f); // #D4A878
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = DarkBrownDarker;
        t.Visualizer.HighFreqTint = Bronze;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.40f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Bronze;
        t.AlbumArtBox.BorderColorClicked = BronzeLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = EspressoDefault;
        t.AlbumArtBox.BackgroundColorHovered = EspressoAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Bronze.x, Bronze.y, Bronze.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Bronze.x, Bronze.y, Bronze.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.60f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.04f, 0.03f, 0.02f, 0.95f);
        t.AlbumArtLightbox.BorderColor = DarkBrown;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Bronze;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = DarkBrownMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Bronze;
        t.SearchBar.rowHoverColor = EspressoAlt;
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = EspressoDefault;
        t.SearchBar.inputBorderColor = DarkBrownMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = DarkBrown;
        t.PlayerBar.ButtonHovered = DarkBrownMid;
        t.PlayerBar.ButtonActive = BronzeDark;

        t.PlayerBar.ButtonPrimary = DarkBrown;
        t.PlayerBar.ButtonPrimaryHovered = DarkBrownMid;
        t.PlayerBar.ButtonPrimaryActive = BronzeDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = Bronze;
        t.PlayerBar.SliderGrabActive = BronzeLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = DarkBrownMid;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Bronze;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        return t;
    }

} // namespace moosic