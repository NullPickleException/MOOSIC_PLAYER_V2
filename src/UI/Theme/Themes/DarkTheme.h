#pragma once

#include "../Theme.h"

namespace moosic
{

    inline Theme CreateDarkTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================
        // Blue:   117, 171, 217  →  0.459f, 0.671f, 0.851f
        // Grey:    97, 109, 120  →  0.380f, 0.427f, 0.471f
        // Dark:    52,  56,  59  →  0.204f, 0.220f, 0.231f

        const ImVec4 Blue = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);         // 117,171,217
        const ImVec4 BlueDark = ImVec4(0.329f, 0.541f, 0.721f, 1.00f);     // ~84,138,184
        const ImVec4 BlueDarker = ImVec4(0.247f, 0.420f, 0.580f, 1.00f);   // ~63,107,148
        const ImVec4 BlueLight = ImVec4(0.529f, 0.741f, 0.921f, 1.00f);    // ~135,189,235
        const ImVec4 BlueVeryLight = ImVec4(0.529f, 0.741f, 0.921f, 0.5f); // ~135,189,235
        const ImVec4 BlueGlow = ImVec4(0.459f, 0.671f, 0.851f, 0.20f);
        const ImVec4 BlueSubtle = ImVec4(0.459f, 0.671f, 0.851f, 0.10f);

        const ImVec4 Grey = ImVec4(0.380f, 0.427f, 0.471f, 1.00f);       // 97,109,120
        const ImVec4 GreyDark = ImVec4(0.280f, 0.327f, 0.371f, 1.00f);   // ~71,83,95
        const ImVec4 GreyDarker = ImVec4(0.200f, 0.247f, 0.291f, 1.00f); // ~51,63,74
        const ImVec4 GreyLight = ImVec4(0.480f, 0.527f, 0.571f, 1.00f);  // ~122,134,146

        // Darker backgrounds
        const ImVec4 DarkBg = ImVec4(0.149f, 0.161f, 0.173f, 1.00f);      // ~38,41,44
        const ImVec4 DarkBgAlt = ImVec4(0.176f, 0.192f, 0.204f, 1.00f);   // ~45,49,52
        const ImVec4 DarkBgHi = ImVec4(0.216f, 0.235f, 0.251f, 1.00f);    // ~55,60,64
        const ImVec4 DarkBgPanel = ImVec4(0.122f, 0.133f, 0.145f, 1.00f); // ~31,34,37

        // Text
        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

          //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Blue;
        t.ContentPanel.TabInactive = GreyDarker;
        t.ContentPanel.TabHovered = GreyDark;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = GreyDark;
        t.ContentPanel.ButtonHovered = Blue;
        t.ContentPanel.ButtonActive = BlueDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = GreyDarker;
        t.ContentPanel.BorderThickness = 2.0f;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = DarkBgPanel;
        t.Window.ChildBg = DarkBg;
        t.Window.WindowBorder = GreyDarker;

        t.Window.TitleBar = DarkBgAlt;
        t.Window.TitleBarActive = DarkBgHi;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Blue;

        t.Window.ButtonNormal = GreyDark;
        t.Window.ButtonHovered = Blue;
        t.Window.ButtonActive = BlueDark;

        t.Window.ProgressBar = Blue;
        t.Window.PlayingHighlight = BlueGlow;
        t.Window.SeparatorColor = GreyDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = GreyDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = GreyDarker;
        t.TrackTable.HeaderHovered = DarkBgHi;
        t.TrackTable.HeaderActive = Blue;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = DarkBg;
        t.TrackTable.RowDefaultAlt = DarkBgAlt;
        t.TrackTable.RowHovered = BlueVeryLight;
        t.TrackTable.RowClicked = ImVec4(Blue.x, Blue.y, Blue.z, 0.35f);
        t.TrackTable.RowSelected = BlueLight;
        t.TrackTable.RowPlaying = Blue;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = TextBright;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextWhite;
        t.TrackTable.TextPlaying = TextWhite;

        // ── Row text per column (hierarchy: Title bright, Artist/Album muted, Extension/Duration dim) ──
        t.TrackTable.RowTextTitle = TextBright;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = GreyDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = DarkBgPanel;
        t.TrackTable.ScrollbarGrab = GreyDark;
        t.TrackTable.ScrollbarGrabHovered = Grey;
        t.TrackTable.ScrollbarGrabActive = Blue;
        t.TrackTable.ScrollbarWidth = 8.0f;
        t.TrackTable.ScrollbarRounding = 4.0f;

        // ── Smoothing / Animation ──
        t.TrackTable.HoverFadeSpeed = 0.15f;
        t.TrackTable.SelectionFadeSpeed = 0.20f;
        t.TrackTable.ScrollSmoothing = 0.12f;

        // ── Misc ──
        t.TrackTable.TableRounding = 0.0f;
        t.TrackTable.MinColumnWidth = 30.0f;

        // ── Column widths (not theme, set in constructor, but included for completeness) ──
        t.TrackTable.TitleWidth = 350.0f;
        t.TrackTable.ArtistWidth = 180.0f;
        t.TrackTable.AlbumWidth = 180.0f;
        t.TrackTable.ExtensionWidth = 50.0f;
        t.TrackTable.DurationWidth = 80.0f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = DarkBgPanel;
        t.Visualizer.WaveformColor = Blue;
        t.Visualizer.WaveformFillColor = ImVec4(Blue.x, Blue.y, Blue.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(GreyDark.x, GreyDark.y, GreyDark.z, 0.25f);
        t.Visualizer.BorderColor = GreyDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Blue;
        t.Visualizer.SpectrumColorMid = BlueLight;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.75f, 0.85f, 1.00f, 1.00f);
        t.Visualizer.SpectrumColorPeak = TextWhite;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = false;
        t.Visualizer.LowFreqTint = ImVec4(1.0f, 0.65f, 0.3f, 1.0f);
        t.Visualizer.HighFreqTint = ImVec4(0.3f, 0.65f, 1.0f, 1.0f);
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.4f;
        t.Visualizer.BarBrightnessMax = 1.0f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = GreyDarker;
        t.AlbumArtBox.BorderColorHovered = Blue;
        t.AlbumArtBox.BorderColorClicked = BlueLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = DarkBgAlt;
        t.AlbumArtBox.BackgroundColorHovered = DarkBgHi;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Blue.x, Blue.y, Blue.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Blue.x, Blue.y, Blue.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.05f, 0.05f, 0.06f, 0.95f);
        t.AlbumArtLightbox.BorderColor = GreyDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Blue;
        t.AlbumArtLightbox.TitleColor = TextBright;
        t.AlbumArtLightbox.ArtistColor = TextMuted;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Blue;
        t.PlayerBar.ButtonHovered = BlueLight;
        t.PlayerBar.ButtonActive = BlueDark;

        t.PlayerBar.ButtonPrimary = Blue;
        t.PlayerBar.ButtonPrimaryHovered = BlueLight;
        t.PlayerBar.ButtonPrimaryActive = BlueDark;

        t.PlayerBar.SliderTrack = GreyDarker;
        t.PlayerBar.SliderGrab = Blue;
        t.PlayerBar.SliderGrabActive = BlueLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        return t;
    }

} // namespace moosic