//==============================================================================
// CrimsonNightTheme.h
//==============================================================================
// Gothic vampire castle theme with candlelight and dark velvet tones
// 60% Deep crimson-black backgrounds (#120A0C → #352327)
// 30% Dried blood surfaces (#5C3038, #74414B, #8F5562)
// 10% Crimson accent (#C1273D)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCrimsonNightTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - Gothic vampire castle
        //==========================================================================

        //==============================================================================
        // Crimson Night Theme Palette (Revised)
        // Inspired by original CrimsonNight UITheme
        //
        // 60% - Black Crimson backgrounds
        // 30% - Dark Wine / Blood surfaces
        // 10% - Bright Crimson accents
        //==============================================================================

        //==========================================================================
        // 60% - Backgrounds
        //==========================================================================

        // Almost black with crimson tint
        const ImVec4 CrimsonDeep = ImVec4(0.098f, 0.020f, 0.039f, 1.00f); // #19050A

        // Main panel
        const ImVec4 CrimsonPanel = ImVec4(0.118f, 0.039f, 0.059f, 1.00f); // #1E0A0F

        // Window background
        const ImVec4 CrimsonDefault = ImVec4(0.137f, 0.039f, 0.078f, 1.00f); // #230A14

        // Alternate rows
        const ImVec4 CrimsonAlt = ImVec4(0.165f, 0.055f, 0.094f, 1.00f); // #2A0E18

        // Elevated controls
        const ImVec4 CrimsonSurface = ImVec4(0.192f, 0.071f, 0.110f, 1.00f); // #31121C

        const ImVec4 CrimsonGlow = ImVec4(1.000f, 0.235f, 0.353f, 0.20f);
        const ImVec4 CrimsonVeryLight = ImVec4(1.000f, 0.235f, 0.353f, 0.50f);
        const ImVec4 CrimsonSubtle = ImVec4(1.000f, 0.235f, 0.353f, 0.10f);

        //==========================================================================
        // 30% - Blood surfaces
        //==========================================================================

        const ImVec4 BloodDark = ImVec4(0.471f, 0.118f, 0.157f, 1.00f);   // #781E28
        const ImVec4 BloodMid = ImVec4(0.588f, 0.157f, 0.216f, 1.00f);    // #962837
        const ImVec4 BloodLight = ImVec4(0.706f, 0.216f, 0.294f, 1.00f);  // #B4374B
        const ImVec4 BloodDarker = ImVec4(0.314f, 0.078f, 0.110f, 1.00f); // #50141C

        //==========================================================================
        // 10% - Crimson Accent
        //==========================================================================

        const ImVec4 Accent = ImVec4(1.000f, 0.235f, 0.353f, 1.00f);       // #FF3C5A
        const ImVec4 AccentDark = ImVec4(0.784f, 0.196f, 0.275f, 1.00f);   // #C83246
        const ImVec4 AccentDarker = ImVec4(0.588f, 0.118f, 0.176f, 1.00f); // #961E2D
        const ImVec4 AccentLight = ImVec4(1.000f, 0.396f, 0.490f, 1.00f);  // #FF657D
        const ImVec4 AccentVeryLight = ImVec4(1.000f, 0.396f, 0.490f, 0.50f);

        //==========================================================================
        // Search dropdown
        //==========================================================================

        const ImVec4 SearchDropdownBg = ImVec4(0.157f, 0.043f, 0.067f, 1.00f); // #280B11

        //==========================================================================
        // Text
        //==========================================================================

        // Pale pink parchment
        const ImVec4 TextBright = ImVec4(1.000f, 0.784f, 0.784f, 1.00f); // #FFC8C8
        const ImVec4 TextMuted = ImVec4(0.784f, 0.588f, 0.588f, 1.00f);  // #C89696
        const ImVec4 TextDim = ImVec4(0.514f, 0.365f, 0.365f, 1.00f);    // #835D5D
        const ImVec4 TextWhite = ImVec4(1.000f, 0.922f, 0.922f, 1.00f);  // #FFEBEB

        //==========================================================================
        // Borders
        //==========================================================================

        const ImVec4 BorderSubtle = ImVec4(0.471f, 0.118f, 0.157f, 1.00f); // #781E28

        //==========================================================================
        // Title Bar - Darker gothic header
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.047f, 0.024f, 0.031f, 1.00f); // #0C0608
        t.TitleBar.BackgroundColorActive = ImVec4(0.047f, 0.024f, 0.031f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.047f, 0.024f, 0.031f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = BloodDark;

        t.TitleBar.ShowAccentLine = true;
        t.TitleBar.AccentLineColor = Accent;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Accent;
        t.ContentPanel.TabInactive = CrimsonDefault;
        t.ContentPanel.TabHovered = CrimsonAlt;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = BloodDark;
        t.ContentPanel.ButtonHovered = BloodMid;
        t.ContentPanel.ButtonActive = AccentDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = BloodMid;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = CrimsonPanel;
        t.Window.ChildBg = CrimsonDeep;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = CrimsonDefault;
        t.Window.TitleBarActive = CrimsonAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Accent;

        t.Window.ButtonNormal = BloodDark;
        t.Window.ButtonHovered = BloodMid;
        t.Window.ButtonActive = AccentDark;

        t.Window.ProgressBar = Accent;
        t.Window.PlayingHighlight = CrimsonGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = BloodDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = CrimsonSurface;
        t.TrackTable.HeaderActive = Accent;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = CrimsonDeep;
        t.TrackTable.RowDefaultAlt = CrimsonDefault;
        t.TrackTable.RowHovered = CrimsonVeryLight;
        t.TrackTable.RowClicked = AccentDarker;
        t.TrackTable.RowSelected = BloodDark;
        t.TrackTable.RowPlaying = Accent;

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
        t.TrackTable.ScrollbarBg = CrimsonPanel;
        t.TrackTable.ScrollbarGrab = BloodDark;
        t.TrackTable.ScrollbarGrabHovered = BloodMid;
        t.TrackTable.ScrollbarGrabActive = Accent;
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

        t.Visualizer.BackgroundColor = CrimsonPanel;
        t.Visualizer.WaveformColor = Accent;
        t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(BloodDark.x, BloodDark.y, BloodDark.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp: dark crimson → blood red → bright crimson ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = AccentDark;
        t.Visualizer.SpectrumColorMid = Accent;
        t.Visualizer.SpectrumColorHigh = AccentLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.918f, 0.416f, 0.486f, 1.00f); // #EA6A7C
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = BloodDark;
        t.Visualizer.HighFreqTint = Accent;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Accent;
        t.AlbumArtBox.BorderColorClicked = AccentLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = CrimsonDefault;
        t.AlbumArtBox.BackgroundColorHovered = CrimsonAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.20f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.031f, 0.016f, 0.020f, 0.95f); // #080405
        t.AlbumArtLightbox.BorderColor = BloodDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Accent;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = BloodMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Accent;
        t.SearchBar.rowHoverColor = CrimsonAlt;
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = CrimsonDefault;
        t.SearchBar.inputBorderColor = BloodMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = BloodDark;
        t.PlayerBar.ButtonHovered = BloodMid;
        t.PlayerBar.ButtonActive = AccentDark;

        t.PlayerBar.ButtonPrimary = BloodDark;
        t.PlayerBar.ButtonPrimaryHovered = BloodMid;
        t.PlayerBar.ButtonPrimaryActive = AccentDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = Accent;
        t.PlayerBar.SliderGrabActive = AccentLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = BloodMid;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Accent;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic