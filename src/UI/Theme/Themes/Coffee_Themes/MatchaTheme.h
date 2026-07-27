//==============================================================================
// MatchaTheme.h
//==============================================================================
// Calm Japanese-inspired matcha theme using 80/15/5 rule:
// 80% Sage green backgrounds (#1B231C, #1F2821, #232D25, #28322A, #2D3730)
// 15% Ceramic cream surfaces (#E8E0D5, #F0EAE0, #F5F0E8)
// 5% Matcha green accent (#7A9B6E)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateMatchaTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 80% - Sage green backgrounds
        const ImVec4 SageDeep = ImVec4(0.106f, 0.137f, 0.110f, 1.00f);    // #1B231C
        const ImVec4 SagePanel = ImVec4(0.122f, 0.157f, 0.129f, 1.00f);   // #1F2821
        const ImVec4 SageDefault = ImVec4(0.137f, 0.176f, 0.145f, 1.00f); // #232D25
        const ImVec4 SageAlt = ImVec4(0.157f, 0.196f, 0.165f, 1.00f);     // #28322A
        const ImVec4 SageSurface = ImVec4(0.176f, 0.216f, 0.188f, 1.00f); // #2D3730

        const ImVec4 SageGlow = ImVec4(0.137f, 0.176f, 0.145f, 0.20f);
        const ImVec4 SageVeryLight = ImVec4(0.137f, 0.176f, 0.145f, 0.5f);
        const ImVec4 SageSubtle = ImVec4(0.137f, 0.176f, 0.145f, 0.10f);

        // 15% - Ceramic cream surfaces
        const ImVec4 CeramicDark = ImVec4(0.910f, 0.878f, 0.835f, 1.00f);   // #E8E0D5
        const ImVec4 CeramicMid = ImVec4(0.941f, 0.918f, 0.878f, 1.00f);    // #F0EAE0
        const ImVec4 CeramicLight = ImVec4(0.961f, 0.941f, 0.910f, 1.00f);  // #F5F0E8
        const ImVec4 CeramicDarker = ImVec4(0.820f, 0.788f, 0.745f, 1.00f); // Darker variant

        // 5% - Matcha green accent
        const ImVec4 Matcha = ImVec4(0.478f, 0.608f, 0.431f, 1.00f);       // #7A9B6E
        const ImVec4 MatchaDark = ImVec4(0.373f, 0.490f, 0.333f, 1.00f);   // #5F7D55
        const ImVec4 MatchaDarker = ImVec4(0.275f, 0.373f, 0.247f, 1.00f); // #465F3F
        const ImVec4 MatchaLight = ImVec4(0.588f, 0.702f, 0.545f, 1.00f);  // #96B38B
        const ImVec4 MatchaVeryLight = ImVec4(0.588f, 0.702f, 0.545f, 0.5f);

        // Search dropdown
        const ImVec4 SearchDropdownBg = ImVec4(0.165f, 0.208f, 0.176f, 1.00f);

        // Text
        const ImVec4 TextBright = ImVec4(0.929f, 0.941f, 0.910f, 1.00f); // #EDF0E8
        const ImVec4 TextMuted = ImVec4(0.690f, 0.729f, 0.659f, 1.00f);  // #B0BAA8
        const ImVec4 TextDim = ImVec4(0.420f, 0.459f, 0.396f, 1.00f);    // #6B7565
        const ImVec4 TextWhite = ImVec4(0.961f, 0.969f, 0.949f, 1.00f);  // #F5F7F2
        const ImVec4 TextDark = ImVec4(0.106f, 0.137f, 0.110f, 1.00f);   // #1B231C

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.227f, 0.271f, 0.235f, 1.00f); // #3A453C
        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.078f, 0.102f, 0.082f, 1.00f); // #141A15 - Darker than SageDeep
        t.TitleBar.BackgroundColorActive = ImVec4(0.078f, 0.102f, 0.082f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.078f, 0.102f, 0.082f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Matcha;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Matcha;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Matcha;
        t.ContentPanel.TabInactive = SageDefault;
        t.ContentPanel.TabHovered = SageAlt;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = CeramicDark;
        t.ContentPanel.ButtonHovered = CeramicMid;
        t.ContentPanel.ButtonActive = MatchaDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = Matcha;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = SagePanel;
        t.Window.ChildBg = SageDeep;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = SageDefault;
        t.Window.TitleBarActive = SageAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Matcha;

        t.Window.ButtonNormal = CeramicDark;
        t.Window.ButtonHovered = CeramicMid;
        t.Window.ButtonActive = MatchaDark;

        t.Window.ProgressBar = Matcha;
        t.Window.PlayingHighlight = SageGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = CeramicDark;
        t.TrackTable.HeaderTextColor = TextDark;
        t.TrackTable.HeaderBorderColor = CeramicDarker;
        t.TrackTable.HeaderHovered = CeramicMid;
        t.TrackTable.HeaderActive = Matcha;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextDark;
        t.TrackTable.HeaderTextArtist = TextDark;
        t.TrackTable.HeaderTextAlbum = TextDark;
        t.TrackTable.HeaderTextExtension = TextDark;
        t.TrackTable.HeaderTextDuration = TextDark;

        // ── Row colors ──
        t.TrackTable.RowDefault = SageDeep;
        t.TrackTable.RowDefaultAlt = SageDefault;
        t.TrackTable.RowHovered = MatchaVeryLight;
        t.TrackTable.RowClicked = MatchaDarker;
        t.TrackTable.RowSelected = CeramicDark;
        t.TrackTable.RowPlaying = Matcha;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = TextBright;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextDark;
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
        t.TrackTable.ScrollbarBg = SagePanel;
        t.TrackTable.ScrollbarGrab = CeramicDark;
        t.TrackTable.ScrollbarGrabHovered = CeramicMid;
        t.TrackTable.ScrollbarGrabActive = Matcha;
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

        t.Visualizer.BackgroundColor = SagePanel;
        t.Visualizer.WaveformColor = Matcha;
        t.Visualizer.WaveformFillColor = ImVec4(Matcha.x, Matcha.y, Matcha.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (matcha bloom) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = MatchaDark;
        t.Visualizer.SpectrumColorMid = Matcha;
        t.Visualizer.SpectrumColorHigh = MatchaLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.710f, 0.788f, 0.659f, 1.00f); // #B5C9A8
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = MatchaDark;
        t.Visualizer.HighFreqTint = MatchaLight;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.15f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Matcha;
        t.AlbumArtBox.BorderColorClicked = MatchaLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = SageDefault;
        t.AlbumArtBox.BackgroundColorHovered = SageAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Matcha.x, Matcha.y, Matcha.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Matcha.x, Matcha.y, Matcha.z, 0.16f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.06f, 0.08f, 0.07f, 0.95f);
        t.AlbumArtLightbox.BorderColor = MatchaDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Matcha;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = Matcha;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Matcha;
        t.SearchBar.rowHoverColor = SageAlt;
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = SageDefault;
        t.SearchBar.inputBorderColor = MatchaDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = CeramicDark;
        t.PlayerBar.ButtonHovered = CeramicMid;
        t.PlayerBar.ButtonActive = MatchaDark;

        t.PlayerBar.ButtonPrimary = CeramicDark;
        t.PlayerBar.ButtonPrimaryHovered = CeramicMid;
        t.PlayerBar.ButtonPrimaryActive = MatchaDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = Matcha;
        t.PlayerBar.SliderGrabActive = MatchaLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = Matcha;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Matcha;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        return t;
    }

} // namespace moosic