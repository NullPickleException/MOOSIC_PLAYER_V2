//==============================================================================
// LagoonTheme.h
//==============================================================================
// Tropical lagoon theme with warm turquoise and sandy tones
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateLagoonTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // Turquoise (warm lagoon water)
        const ImVec4 Turquoise = ImVec4(0.200f, 0.780f, 0.690f, 1.00f);         // 51,199,176
        const ImVec4 TurquoiseDark = ImVec4(0.150f, 0.585f, 0.518f, 1.00f);     // 38,149,132
        const ImVec4 TurquoiseDarker = ImVec4(0.100f, 0.390f, 0.345f, 1.00f);   // 26,99,88
        const ImVec4 TurquoiseLight = ImVec4(0.400f, 0.880f, 0.820f, 1.00f);    // 102,224,209
        const ImVec4 TurquoiseVeryLight = ImVec4(0.400f, 0.880f, 0.820f, 0.5f); // 102,224,209
        const ImVec4 TurquoiseGlow = ImVec4(0.200f, 0.780f, 0.690f, 0.20f);
        const ImVec4 TurquoiseSubtle = ImVec4(0.200f, 0.780f, 0.690f, 0.10f);

        // Sandy/Golden tones (warm beach)
        const ImVec4 Sand = ImVec4(0.890f, 0.722f, 0.529f, 1.00f);         // 227,184,135
        const ImVec4 SandDark = ImVec4(0.710f, 0.576f, 0.420f, 1.00f);     // 181,147,107
        const ImVec4 SandDarker = ImVec4(0.533f, 0.431f, 0.314f, 1.00f);   // 136,110,80
        const ImVec4 SandLight = ImVec4(0.945f, 0.831f, 0.698f, 1.00f);    // 241,212,178
        const ImVec4 SandGlow = ImVec4(0.890f, 0.722f, 0.529f, 0.20f);

        // Lagoon backgrounds (warm, shallow water feel)
        const ImVec4 LagoonDeep = ImVec4(0.078f, 0.220f, 0.200f, 1.00f);   // 20,56,51
        const ImVec4 LagoonMid = ImVec4(0.098f, 0.263f, 0.239f, 1.00f);    // 25,67,61
        const ImVec4 LagoonSurface = ImVec4(0.118f, 0.306f, 0.278f, 1.00f);// 30,78,71
        const ImVec4 LagoonPanel = ImVec4(0.063f, 0.184f, 0.169f, 1.00f);  // 16,47,43

        // Text
        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = LagoonDeep;
        t.TitleBar.BackgroundColorActive = LagoonDeep;
        t.TitleBar.BackgroundColorInactive = ImVec4(LagoonDeep.x, LagoonDeep.y, LagoonDeep.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = SandDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Turquoise;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Sand;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Turquoise;
        t.ContentPanel.TabInactive = TurquoiseDarker;
        t.ContentPanel.TabHovered = TurquoiseDark;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = TurquoiseDark;
        t.ContentPanel.ButtonHovered = Sand;
        t.ContentPanel.ButtonActive = SandDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = Turquoise;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = LagoonPanel;
        t.Window.ChildBg = LagoonDeep;
        t.Window.WindowBorder = TurquoiseDarker;

        t.Window.TitleBar = LagoonMid;
        t.Window.TitleBarActive = LagoonSurface;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Turquoise;

        t.Window.ButtonNormal = TurquoiseDark;
        t.Window.ButtonHovered = Sand;
        t.Window.ButtonActive = SandDark;

        t.Window.ProgressBar = Turquoise;
        t.Window.PlayingHighlight = TurquoiseGlow;
        t.Window.SeparatorColor = TurquoiseDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = TurquoiseDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = TurquoiseDarker;
        t.TrackTable.HeaderHovered = LagoonSurface;
        t.TrackTable.HeaderActive = Sand;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = LagoonDeep;
        t.TrackTable.RowDefaultAlt = LagoonMid;
        t.TrackTable.RowHovered = TurquoiseVeryLight;
        t.TrackTable.RowClicked = ImVec4(Turquoise.x, Turquoise.y, Turquoise.z, 0.35f);
        t.TrackTable.RowSelected = TurquoiseLight;
        t.TrackTable.RowPlaying = Turquoise;

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
        t.TrackTable.BorderColor = TurquoiseDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(TurquoiseDarker.x, TurquoiseDarker.y, TurquoiseDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = LagoonPanel;
        t.TrackTable.ScrollbarGrab = TurquoiseDark;
        t.TrackTable.ScrollbarGrabHovered = Turquoise;
        t.TrackTable.ScrollbarGrabActive = Sand;
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

        t.Visualizer.BackgroundColor = LagoonPanel;
        t.Visualizer.WaveformColor = Turquoise;
        t.Visualizer.WaveformFillColor = ImVec4(Turquoise.x, Turquoise.y, Turquoise.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(TurquoiseDark.x, TurquoiseDark.y, TurquoiseDark.z, 0.25f);
        t.Visualizer.BorderColor = TurquoiseDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Turquoise;
        t.Visualizer.SpectrumColorMid = Sand;
        t.Visualizer.SpectrumColorHigh = SandLight;
        t.Visualizer.SpectrumColorPeak = TextWhite;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = Turquoise;
        t.Visualizer.HighFreqTint = Sand;
        t.Visualizer.FrequencyTintBlend = 0.3f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.25f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = TurquoiseDarker;
        t.AlbumArtBox.BorderColorHovered = Sand;
        t.AlbumArtBox.BorderColorClicked = SandLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = LagoonMid;
        t.AlbumArtBox.BackgroundColorHovered = LagoonSurface;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Turquoise.x, Turquoise.y, Turquoise.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Turquoise.x, Turquoise.y, Turquoise.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.04f, 0.11f, 0.10f, 0.95f);
        t.AlbumArtLightbox.BorderColor = TurquoiseDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Sand;
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
        t.SearchBar.backgroundColor = LagoonPanel;
        t.SearchBar.borderColor = TurquoiseDarker;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Sand;
        t.SearchBar.rowHoverColor = LagoonSurface;
        t.SearchBar.separatorColor = TurquoiseDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = LagoonMid;
        t.SearchBar.inputBorderColor = TurquoiseDarker;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = Turquoise;
        t.PlayerBar.ButtonHovered = TurquoiseLight;
        t.PlayerBar.ButtonActive = TurquoiseDark;

        t.PlayerBar.ButtonPrimary = Turquoise;
        t.PlayerBar.ButtonPrimaryHovered = TurquoiseLight;
        t.PlayerBar.ButtonPrimaryActive = TurquoiseDark;

        t.PlayerBar.SliderTrack = TurquoiseDarker;
        t.PlayerBar.SliderGrab = Turquoise;
        t.PlayerBar.SliderGrabActive = Sand;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = LagoonPanel;
        t.ContextMenu.BorderColor = Turquoise;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Sand;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = TurquoiseDark;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        return t;
    }

} // namespace moosic