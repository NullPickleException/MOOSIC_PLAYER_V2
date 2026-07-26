//==============================================================================
// PearlTheme.h
//==============================================================================
// Elegant iridescent theme using 60/30/10 rule:
// 60% Deep Abyss (#1A1D24, #1F232B, #242933)
// 30% Pearl White (#E8E2E0, #F0EBE9, #F5F2F0)
// 10% Rose Gold (#C4919D)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreatePearlTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Deep Abyss backgrounds (dark oyster interior)
        const ImVec4 AbyssDark = ImVec4(0.102f, 0.114f, 0.141f, 1.00f);     // #1A1D24 - 26,29,36
        const ImVec4 AbyssMid = ImVec4(0.122f, 0.137f, 0.169f, 1.00f);      // #1F232B - 31,35,43
        const ImVec4 AbyssLight = ImVec4(0.141f, 0.161f, 0.200f, 1.00f);    // #242933 - 36,41,51
        const ImVec4 AbyssPanel = ImVec4(0.082f, 0.094f, 0.118f, 1.00f);    // Darker panel
        const ImVec4 AbyssDeep = ImVec4(0.065f, 0.075f, 0.094f, 1.00f);     // Deepest bg
        
        const ImVec4 AbyssGlow = ImVec4(0.122f, 0.137f, 0.169f, 0.20f);
        const ImVec4 AbyssVeryLight = ImVec4(0.122f, 0.137f, 0.169f, 0.5f);
        const ImVec4 AbyssSubtle = ImVec4(0.122f, 0.137f, 0.169f, 0.10f);

        // 30% - Pearl White (iridescent cream with subtle warmth)
        const ImVec4 PearlDarker = ImVec4(0.757f, 0.741f, 0.733f, 1.00f);   // #C1BDBA
        const ImVec4 PearlDark = ImVec4(0.843f, 0.827f, 0.820f, 1.00f);     // #D7D3D1
        const ImVec4 Pearl = ImVec4(0.910f, 0.886f, 0.878f, 1.00f);         // #E8E2E0 - 232,226,224
        const ImVec4 PearlMid = ImVec4(0.941f, 0.922f, 0.914f, 1.00f);      // #F0EBE9 - 240,235,233
        const ImVec4 PearlLight = ImVec4(0.961f, 0.949f, 0.941f, 1.00f);    // #F5F2F0 - 245,242,240
        const ImVec4 PearlVeryLight = ImVec4(0.910f, 0.886f, 0.878f, 0.5f);

        // 10% - Rose Gold accent (iridescent shimmer)
        const ImVec4 RoseGold = ImVec4(0.769f, 0.569f, 0.616f, 1.00f);      // #C4919D - 196,145,157
        const ImVec4 RoseGoldDark = ImVec4(0.616f, 0.455f, 0.494f, 1.00f);  // Darker
        const ImVec4 RoseGoldDarker = ImVec4(0.463f, 0.341f, 0.373f, 1.00f);// Even darker
        const ImVec4 RoseGoldLight = ImVec4(0.847f, 0.682f, 0.722f, 1.00f); // Lighter

        // Search dropdown - lighter tint of AbyssMid (60% family)
        const ImVec4 SearchDropdownBg = ImVec4(0.161f, 0.180f, 0.216f, 1.00f);  // Tinted lighter

        // Text
        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        const ImVec4 TextDark = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = AbyssDeep;
        t.TitleBar.BackgroundColorActive = AbyssDeep;
        t.TitleBar.BackgroundColorInactive = ImVec4(AbyssDeep.x, AbyssDeep.y, AbyssDeep.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = AbyssDark;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = PearlDark;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = RoseGold;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Pearl;
        t.ContentPanel.TabInactive = AbyssDark;
        t.ContentPanel.TabHovered = AbyssLight;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextDark;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = AbyssLight;
        t.ContentPanel.ButtonHovered = PearlDark;
        t.ContentPanel.ButtonActive = PearlDarker;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = PearlDark;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = AbyssPanel;
        t.Window.ChildBg = AbyssDeep;
        t.Window.WindowBorder = AbyssDark;

        t.Window.TitleBar = AbyssDark;
        t.Window.TitleBarActive = AbyssMid;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Pearl;

        t.Window.ButtonNormal = AbyssLight;
        t.Window.ButtonHovered = PearlDark;
        t.Window.ButtonActive = PearlDarker;

        t.Window.ProgressBar = RoseGold;
        t.Window.PlayingHighlight = AbyssGlow;
        t.Window.SeparatorColor = AbyssDark;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = AbyssMid;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = AbyssDark;
        t.TrackTable.HeaderHovered = AbyssLight;
        t.TrackTable.HeaderActive = Pearl;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = AbyssDeep;
        t.TrackTable.RowDefaultAlt = AbyssDark;
        t.TrackTable.RowHovered = AbyssVeryLight;
        t.TrackTable.RowClicked = ImVec4(PearlDark.x, PearlDark.y, PearlDark.z, 0.35f);
        t.TrackTable.RowSelected = Pearl;
        t.TrackTable.RowPlaying = RoseGold;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = TextBright;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextDark;
        t.TrackTable.TextPlaying = TextWhite;
        t.TrackTable.TextPlaying = TextBright;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle = TextBright;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = AbyssDark;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(AbyssDark.x, AbyssDark.y, AbyssDark.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = AbyssPanel;
        t.TrackTable.ScrollbarGrab = AbyssLight;
        t.TrackTable.ScrollbarGrabHovered = PearlDark;
        t.TrackTable.ScrollbarGrabActive = Pearl;
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

        t.Visualizer.BackgroundColor = AbyssPanel;
        t.Visualizer.WaveformColor = Pearl;
        t.Visualizer.WaveformFillColor = ImVec4(Pearl.x, Pearl.y, Pearl.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(AbyssMid.x, AbyssMid.y, AbyssMid.z, 0.25f);
        t.Visualizer.BorderColor = AbyssDark;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (abyss to iridescent pearl shimmer) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = PearlDarker;
        t.Visualizer.SpectrumColorMid = Pearl;
        t.Visualizer.SpectrumColorHigh = RoseGold;
        t.Visualizer.SpectrumColorPeak = RoseGoldLight;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint (pearl white to rose gold shimmer) ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = PearlDarker;
        t.Visualizer.HighFreqTint = RoseGold;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = AbyssDark;
        t.AlbumArtBox.BorderColorHovered = Pearl;
        t.AlbumArtBox.BorderColorClicked = RoseGold;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = AbyssDark;
        t.AlbumArtBox.BackgroundColorHovered = AbyssMid;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Pearl.x, Pearl.y, Pearl.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(RoseGold.x, RoseGold.y, RoseGold.z, 0.15f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextBright;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.04f, 0.06f, 0.07f, 0.95f);
        t.AlbumArtLightbox.BorderColor = AbyssMid;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = RoseGold;
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

        // ── Dropdown Colors (lighter tint of AbyssMid) ──
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = PearlDark;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = RoseGold;
        t.SearchBar.rowHoverColor = AbyssLight;
        t.SearchBar.separatorColor = AbyssMid;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = AbyssDark;
        t.SearchBar.inputBorderColor = PearlDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = AbyssLight;
        t.PlayerBar.ButtonHovered = Pearl;
        t.PlayerBar.ButtonActive = PearlDark;

        t.PlayerBar.ButtonPrimary = AbyssLight;
        t.PlayerBar.ButtonPrimaryHovered = Pearl;
        t.PlayerBar.ButtonPrimaryActive = PearlDark;

        t.PlayerBar.SliderTrack = AbyssDark;
        t.PlayerBar.SliderGrab = Pearl;
        t.PlayerBar.SliderGrabActive = RoseGold;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = PearlDark;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = RoseGold;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = AbyssMid;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic