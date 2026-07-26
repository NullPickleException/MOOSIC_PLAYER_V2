//==============================================================================
// TsunamiTheme.h
//==============================================================================
// Powerful ocean theme with deep teal and seafoam accents
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateTsunamiTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // Deep Teal - tsunami depths
        const ImVec4 DeepTeal = ImVec4(0.071f, 0.282f, 0.294f, 1.00f);         // 18,72,75
        const ImVec4 DeepTealDark = ImVec4(0.055f, 0.212f, 0.220f, 1.00f);     // 14,54,56
        const ImVec4 DeepTealDarker = ImVec4(0.035f, 0.141f, 0.149f, 1.00f);   // 9,36,38
        const ImVec4 DeepTealLight = ImVec4(0.129f, 0.400f, 0.416f, 1.00f);    // 33,102,106
        const ImVec4 DeepTealVeryLight = ImVec4(0.129f, 0.400f, 0.416f, 0.5f); // 33,102,106
        const ImVec4 DeepTealGlow = ImVec4(0.071f, 0.282f, 0.294f, 0.20f);
        const ImVec4 DeepTealSubtle = ImVec4(0.071f, 0.282f, 0.294f, 0.10f);

        // Seafoam Green - crashing wave crest
        const ImVec4 Seafoam = ImVec4(0.388f, 0.761f, 0.698f, 1.00f);         // 99,194,178
        const ImVec4 SeafoamDark = ImVec4(0.290f, 0.573f, 0.525f, 1.00f);     // 74,146,134
        const ImVec4 SeafoamDarker = ImVec4(0.196f, 0.384f, 0.353f, 1.00f);   // 50,98,90
        const ImVec4 SeafoamLight = ImVec4(0.518f, 0.847f, 0.800f, 1.00f);    // 132,216,204
        const ImVec4 SeafoamGlow = ImVec4(0.388f, 0.761f, 0.698f, 0.20f);

        // White Foam - spray at the peak
        const ImVec4 Foam = ImVec4(0.820f, 0.918f, 0.902f, 1.00f);         // 209,234,230
        const ImVec4 FoamDark = ImVec4(0.655f, 0.737f, 0.722f, 1.00f);     // 167,188,184
        const ImVec4 FoamDarker = ImVec4(0.494f, 0.553f, 0.545f, 1.00f);   // 126,141,139
        const ImVec4 FoamLight = ImVec4(0.902f, 0.957f, 0.945f, 1.00f);    // 230,244,241

        // Tsunami backgrounds
        const ImVec4 TsunamiDeep = ImVec4(0.047f, 0.165f, 0.173f, 1.00f);    // 12,42,44
        const ImVec4 TsunamiMid = ImVec4(0.059f, 0.200f, 0.208f, 1.00f);     // 15,51,53
        const ImVec4 TsunamiSurface = ImVec4(0.071f, 0.235f, 0.243f, 1.00f); // 18,60,62
        const ImVec4 TsunamiPanel = ImVec4(0.039f, 0.137f, 0.145f, 1.00f);   // 10,35,37

        // Search dropdown - lighter tint of DeepTeal base (color theory: analogous lighter)
        const ImVec4 SearchDropdownBg = ImVec4(0.110f, 0.341f, 0.353f, 1.00f);  // 28,87,90

        // Text
        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = TsunamiDeep;
        t.TitleBar.BackgroundColorActive = TsunamiDeep;
        t.TitleBar.BackgroundColorInactive = ImVec4(TsunamiDeep.x, TsunamiDeep.y, TsunamiDeep.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = DeepTealDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = SeafoamDark;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = DeepTeal;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Seafoam;
        t.ContentPanel.TabInactive = DeepTealDarker;
        t.ContentPanel.TabHovered = DeepTeal;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = DeepTeal;
        t.ContentPanel.ButtonHovered = Seafoam;
        t.ContentPanel.ButtonActive = SeafoamDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = SeafoamDark;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = TsunamiPanel;
        t.Window.ChildBg = TsunamiDeep;
        t.Window.WindowBorder = DeepTealDarker;

        t.Window.TitleBar = TsunamiMid;
        t.Window.TitleBarActive = TsunamiSurface;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Seafoam;

        t.Window.ButtonNormal = DeepTeal;
        t.Window.ButtonHovered = Seafoam;
        t.Window.ButtonActive = SeafoamDark;

        t.Window.ProgressBar = Seafoam;
        t.Window.PlayingHighlight = DeepTealGlow;
        t.Window.SeparatorColor = DeepTealDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = DeepTeal;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = DeepTealDarker;
        t.TrackTable.HeaderHovered = TsunamiSurface;
        t.TrackTable.HeaderActive = Seafoam;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = TsunamiDeep;
        t.TrackTable.RowDefaultAlt = TsunamiMid;
        t.TrackTable.RowHovered = DeepTealVeryLight;
        t.TrackTable.RowClicked = ImVec4(Seafoam.x, Seafoam.y, Seafoam.z, 0.35f);
        t.TrackTable.RowSelected = Seafoam;
        t.TrackTable.RowPlaying = Foam;

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
        t.TrackTable.BorderColor = DeepTealDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(DeepTealDarker.x, DeepTealDarker.y, DeepTealDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = TsunamiPanel;
        t.TrackTable.ScrollbarGrab = DeepTeal;
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

        t.Visualizer.BackgroundColor = TsunamiPanel;
        t.Visualizer.WaveformColor = Seafoam;
        t.Visualizer.WaveformFillColor = ImVec4(Seafoam.x, Seafoam.y, Seafoam.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(DeepTeal.x, DeepTeal.y, DeepTeal.z, 0.25f);
        t.Visualizer.BorderColor = DeepTealDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = DeepTeal;
        t.Visualizer.SpectrumColorMid = Seafoam;
        t.Visualizer.SpectrumColorHigh = Foam;
        t.Visualizer.SpectrumColorPeak = FoamLight;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = DeepTeal;
        t.Visualizer.HighFreqTint = Foam;
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = DeepTealDarker;
        t.AlbumArtBox.BorderColorHovered = Seafoam;
        t.AlbumArtBox.BorderColorClicked = Foam;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = TsunamiMid;
        t.AlbumArtBox.BackgroundColorHovered = TsunamiSurface;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

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

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.024f, 0.082f, 0.086f, 0.95f);
        t.AlbumArtLightbox.BorderColor = DeepTeal;
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

        // ── Dropdown Colors (lighter tint of base DeepTeal for contrast) ──
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = SeafoamDark;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Seafoam;
        t.SearchBar.rowHoverColor = DeepTealLight;
        t.SearchBar.separatorColor = DeepTeal;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = TsunamiMid;
        t.SearchBar.inputBorderColor = SeafoamDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = DeepTeal;
        t.PlayerBar.ButtonHovered = Seafoam;
        t.PlayerBar.ButtonActive = SeafoamDark;

        t.PlayerBar.ButtonPrimary = DeepTeal;
        t.PlayerBar.ButtonPrimaryHovered = Seafoam;
        t.PlayerBar.ButtonPrimaryActive = SeafoamDark;

        t.PlayerBar.SliderTrack = DeepTealDarker;
        t.PlayerBar.SliderGrab = Seafoam;
        t.PlayerBar.SliderGrabActive = Foam;

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
        t.ContextMenu.SeparatorColor = DeepTeal;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic