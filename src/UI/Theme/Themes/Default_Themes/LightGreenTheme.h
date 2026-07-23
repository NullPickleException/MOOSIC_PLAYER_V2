//==============================================================================
// LightGreenTheme.h
//==============================================================================
// Warm, eye-friendly light theme with green accent
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateLightGreenTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (Warm, Eye-Friendly)
        //==========================================================================

        const ImVec4 Green = ImVec4(0.271f, 0.702f, 0.443f, 1.00f);      // 69,179,113
        const ImVec4 GreenDark = ImVec4(0.200f, 0.529f, 0.333f, 1.00f);  // 51,135,85
        const ImVec4 GreenLight = ImVec4(0.400f, 0.800f, 0.549f, 1.00f); // 102,204,140
        const ImVec4 GreenGlow = ImVec4(0.271f, 0.702f, 0.443f, 0.10f);
        const ImVec4 GreenSubtle = ImVec4(0.271f, 0.702f, 0.443f, 0.06f);

        // Warm greys — with slight brown undertones, not cold grey
        const ImVec4 Grey = ImVec4(0.627f, 0.604f, 0.569f, 1.00f);       // 160,154,145 — warm stone
        const ImVec4 GreyDark = ImVec4(0.537f, 0.514f, 0.478f, 1.00f);   // 137,131,122
        const ImVec4 GreyDarker = ImVec4(0.820f, 0.808f, 0.788f, 1.00f); // 209,206,201 — warm border
        const ImVec4 GreyLight = ImVec4(0.910f, 0.898f, 0.878f, 1.00f);  // 232,229,224 — warm light

        // Warm backgrounds — creamy, not sterile white
        const ImVec4 LightBg = ImVec4(0.957f, 0.949f, 0.937f, 1.00f);      // 244,242,239 — warm cream
        const ImVec4 LightBgAlt = ImVec4(0.937f, 0.925f, 0.910f, 1.00f);   // 239,236,232 — slightly darker cream
        const ImVec4 LightBgHi = ImVec4(0.890f, 0.886f, 0.878f, 1.00f);    // 227,226,224 — hover highlight
        const ImVec4 LightBgPanel = ImVec4(0.969f, 0.961f, 0.949f, 1.00f); // 247,245,242 — panel white

        // Text — soft dark brown-grey, not pure black
        const ImVec4 TextDark = ImVec4(0.235f, 0.216f, 0.196f, 1.00f);  // 60,55,50 — warm dark
        const ImVec4 TextMuted = ImVec4(0.447f, 0.424f, 0.396f, 1.00f); // 114,108,101 — warm medium
        const ImVec4 TextDim = ImVec4(0.608f, 0.584f, 0.557f, 1.00f);   // 155,149,142 — warm light
        const ImVec4 TextWhite = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = Grey;
        t.TitleBar.BackgroundColorActive = GreyLight;
        t.TitleBar.BackgroundColorInactive = ImVec4(LightBg.x, LightBg.y, LightBg.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = GreyDarker;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Green;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Green;

        t.TitleBar.TitleTextColor = TextDark;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Green;
        t.ContentPanel.TabInactive = GreyLight;
        t.ContentPanel.TabHovered = LightBgHi;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = GreyLight;
        t.ContentPanel.ButtonHovered = LightBgHi;
        t.ContentPanel.ButtonActive = GreyDarker;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = GreenLight;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = LightBgPanel;
        t.Window.ChildBg = LightBg;
        t.Window.WindowBorder = GreyDarker;

        t.Window.TitleBar = LightBgAlt;
        t.Window.TitleBarActive = LightBgAlt;

        t.Window.HeaderText = TextDark;

        t.Window.TextPrimary = TextDark;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Green;

        t.Window.ButtonNormal = GreyLight;
        t.Window.ButtonHovered = LightBgHi;
        t.Window.ButtonActive = GreyDarker;

        t.Window.ProgressBar = Green;
        t.Window.PlayingHighlight = GreenGlow;
        t.Window.SeparatorColor = GreyDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = LightBgAlt;
        t.TrackTable.HeaderTextColor = TextMuted;
        t.TrackTable.HeaderBorderColor = GreyDarker;
        t.TrackTable.HeaderHovered = LightBgHi;
        t.TrackTable.HeaderActive = Green;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextMuted;
        t.TrackTable.HeaderTextArtist = TextMuted;
        t.TrackTable.HeaderTextAlbum = TextMuted;
        t.TrackTable.HeaderTextExtension = TextMuted;
        t.TrackTable.HeaderTextDuration = TextMuted;

        // ── Row colors ──
        t.TrackTable.RowDefault = LightBgPanel;
        t.TrackTable.RowDefaultAlt = LightBg;
        t.TrackTable.RowHovered = ImVec4(Green.x, Green.y, Green.z, 0.20f);
        t.TrackTable.RowClicked = ImVec4(Green.x, Green.y, Green.z, 0.35f);
        t.TrackTable.RowSelected = GreenLight;
        t.TrackTable.RowPlaying = GreenLight;

        // ── Row layout ──
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor = TextDark;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextWhite;
        t.TrackTable.TextPlaying = TextDark;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle = TextDark;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;

        // ── Border & Separator ──
        t.TrackTable.BorderColor = GreyDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.50f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = LightBg;
        t.TrackTable.ScrollbarGrab = GreyDarker;
        t.TrackTable.ScrollbarGrabHovered = Grey;
        t.TrackTable.ScrollbarGrabActive = Green;
        t.TrackTable.ScrollbarWidth = 8.0f;
        t.TrackTable.ScrollbarRounding = 4.0f;

        // ── Smoothing / Animation ──
        t.TrackTable.HoverFadeSpeed = 0.18f;
        t.TrackTable.SelectionFadeSpeed = 0.22f;
        t.TrackTable.ScrollSmoothing = 0.14f;

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

        t.Visualizer.BackgroundColor = LightBg;
        t.Visualizer.WaveformColor = Green;
        t.Visualizer.WaveformFillColor = ImVec4(Green.x, Green.y, Green.z, 0.06f);
        t.Visualizer.GridColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.40f);
        t.Visualizer.BorderColor = GreyDarker;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp — warm greens ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = ImVec4(0.380f, 0.620f, 0.420f, 1.00f);
        t.Visualizer.SpectrumColorMid = Green;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.10f, 0.60f, 0.25f, 1.00f); // Deep rich green at peaks
        t.Visualizer.SpectrumColorPeak = ImVec4(0.15f, 0.35f, 0.15f, 1.00f); // Dark peak dots for light bg
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.40f;
        t.Visualizer.ColorRampHighThreshold = 0.75f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = false;
        t.Visualizer.LowFreqTint = ImVec4(0.91f, 0.58f, 0.35f, 1.0f);
        t.Visualizer.HighFreqTint = ImVec4(0.35f, 0.58f, 0.84f, 1.0f);
        t.Visualizer.FrequencyTintBlend = 0.25f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.60f; // Quieter bars still visible
        t.Visualizer.BarBrightnessMax = 1.20f; // Peaks glow beyond 1.0

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = GreyDarker;
        t.AlbumArtBox.BorderColorHovered = Green;
        t.AlbumArtBox.BorderColorClicked = GreenLight;
        t.AlbumArtBox.BorderThickness = 1.5f;
        t.AlbumArtBox.BorderThicknessHovered = 2.5f;
        t.AlbumArtBox.BorderRounding = 4.0f;

        t.AlbumArtBox.BackgroundColor = LightBgAlt;
        t.AlbumArtBox.BackgroundColorHovered = LightBgHi;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.24f, 0.22f, 0.20f, 0.08f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Green.x, Green.y, Green.z, 0.05f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Green.x, Green.y, Green.z, 0.12f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.18f, 0.16f, 0.14f, 0.45f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.969f, 0.961f, 0.949f, 0.94f);
        t.AlbumArtLightbox.BorderColor = GreyDarker;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Green;
        t.AlbumArtLightbox.TitleColor = TextDark;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.15f);
        t.SearchBar.backgroundColor = LightBgPanel;
        t.SearchBar.borderColor = GreyDarker;
        t.SearchBar.textColor = TextDark;
        t.SearchBar.highlightTextColor = Green;
        t.SearchBar.rowHoverColor = LightBgHi;
        t.SearchBar.separatorColor = GreyDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = LightBg;
        t.SearchBar.inputBorderColor = GreyDarker;
        t.SearchBar.inputTextColor = TextDark;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = GreyLight;
        t.PlayerBar.ButtonHovered = Green;
        t.PlayerBar.ButtonActive = GreenDark;

        t.PlayerBar.ButtonPrimary = Green;
        t.PlayerBar.ButtonPrimaryHovered = GreenLight;
        t.PlayerBar.ButtonPrimaryActive = GreenDark;

        t.PlayerBar.SliderTrack = GreyDarker;
        t.PlayerBar.SliderGrab = Green;
        t.PlayerBar.SliderGrabActive = GreenLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = LightBgPanel;
        t.ContextMenu.BorderColor = Green;
        t.ContextMenu.TextColor = TextDark;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Green;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = GreyLight;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.15f);

        return t;
    }

} // namespace moosic