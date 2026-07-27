//==============================================================================
// CoffeeCreamTheme.h
//==============================================================================
// Light warm latte theme using 60/30/10 rule:
// 60% Cream backgrounds (#F5F0EB, #F8F4F0, #FCFAF7, #F6F1EC, #EDE6DF)
// 30% Warm beige surfaces (#C4B09E, #D4C5B5, #E0D3C5)
// 10% Rich brown accent (#A6753F)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCoffeeCreamTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Cream backgrounds
        const ImVec4 CreamDeep = ImVec4(0.961f, 0.941f, 0.922f, 1.00f);    // #F5F0EB
        const ImVec4 CreamPanel = ImVec4(0.973f, 0.957f, 0.941f, 1.00f);   // #F8F4F0
        const ImVec4 CreamDefault = ImVec4(0.988f, 0.980f, 0.969f, 1.00f); // #FCFAF7
        const ImVec4 CreamAlt = ImVec4(0.965f, 0.945f, 0.925f, 1.00f);     // #F6F1EC
        const ImVec4 CreamSurface = ImVec4(0.929f, 0.902f, 0.875f, 1.00f); // #EDE6DF

        const ImVec4 CreamGlow = ImVec4(0.961f, 0.941f, 0.922f, 0.20f);
        const ImVec4 CreamVeryLight = ImVec4(0.961f, 0.941f, 0.922f, 0.5f);
        const ImVec4 CreamSubtle = ImVec4(0.961f, 0.941f, 0.922f, 0.10f);

        // 30% - Warm beige surfaces
        const ImVec4 BeigeDark = ImVec4(0.769f, 0.690f, 0.620f, 1.00f);   // #C4B09E
        const ImVec4 BeigeMid = ImVec4(0.831f, 0.773f, 0.710f, 1.00f);    // #D4C5B5
        const ImVec4 BeigeLight = ImVec4(0.878f, 0.827f, 0.773f, 1.00f);  // #E0D3C5
        const ImVec4 BeigeDarker = ImVec4(0.647f, 0.576f, 0.514f, 1.00f); // Darker variant

        // 10% - Rich brown accent
        const ImVec4 Brown = ImVec4(0.651f, 0.459f, 0.247f, 1.00f);       // #A6753F
        const ImVec4 BrownDark = ImVec4(0.545f, 0.369f, 0.188f, 1.00f);   // #8B5E30
        const ImVec4 BrownDarker = ImVec4(0.439f, 0.290f, 0.145f, 1.00f); // #704A25
        const ImVec4 BrownLight = ImVec4(0.769f, 0.584f, 0.416f, 1.00f);  // #C4956A
        const ImVec4 BrownVeryLight = ImVec4(0.769f, 0.584f, 0.416f, 0.5f);

        // Search dropdown - lighter tint
        const ImVec4 SearchDropdownBg = ImVec4(1.000f, 0.992f, 0.984f, 1.00f);

        // Text
        const ImVec4 TextBright = ImVec4(0.176f, 0.141f, 0.125f, 1.00f); // #2D2420
        const ImVec4 TextMuted = ImVec4(0.420f, 0.365f, 0.322f, 1.00f);  // #6B5D52
        const ImVec4 TextDim = ImVec4(0.608f, 0.557f, 0.510f, 1.00f);    // #9B8E82
        const ImVec4 TextWhite = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);  // #FFFFFF

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.831f, 0.773f, 0.710f, 1.00f); // #D4C5B5

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.929f, 0.902f, 0.875f, 1.00f); // #EDE6DF - Darker than CreamDeep
        t.TitleBar.BackgroundColorActive = ImVec4(0.929f, 0.902f, 0.875f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.929f, 0.902f, 0.875f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BeigeMid;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = BeigeDark;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Brown;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Brown;
        t.ContentPanel.TabInactive = CreamAlt;
        t.ContentPanel.TabHovered = CreamSurface;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = BeigeDark;
        t.ContentPanel.ButtonHovered = BeigeMid;
        t.ContentPanel.ButtonActive = BrownDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = BeigeDark;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = CreamPanel;
        t.Window.ChildBg = CreamDeep;
        t.Window.WindowBorder = BeigeMid;

        t.Window.TitleBar = CreamDefault;
        t.Window.TitleBarActive = CreamAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Brown;

        t.Window.ButtonNormal = BeigeDark;
        t.Window.ButtonHovered = BeigeMid;
        t.Window.ButtonActive = BrownDark;

        t.Window.ProgressBar = Brown;
        t.Window.PlayingHighlight = CreamGlow;
        t.Window.SeparatorColor = BeigeMid;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = BeigeDark;
        t.TrackTable.HeaderTextColor = TextWhite;
        t.TrackTable.HeaderBorderColor = BeigeMid;
        t.TrackTable.HeaderHovered = CreamSurface;
        t.TrackTable.HeaderActive = Brown;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextWhite;
        t.TrackTable.HeaderTextArtist = TextWhite;
        t.TrackTable.HeaderTextAlbum = TextWhite;
        t.TrackTable.HeaderTextExtension = TextWhite;
        t.TrackTable.HeaderTextDuration = TextWhite;

        // ── Row colors ──
        t.TrackTable.RowDefault = CreamDeep;
        t.TrackTable.RowDefaultAlt = CreamDefault;
        t.TrackTable.RowHovered = BrownVeryLight;
        t.TrackTable.RowClicked = BrownDarker;
        t.TrackTable.RowSelected = BeigeDark;
        t.TrackTable.RowPlaying = Brown;

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
        t.TrackTable.BorderColor = BeigeMid;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(BeigeMid.x, BeigeMid.y, BeigeMid.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg = CreamPanel;
        t.TrackTable.ScrollbarGrab = BeigeDark;
        t.TrackTable.ScrollbarGrabHovered = BeigeMid;
        t.TrackTable.ScrollbarGrabActive = Brown;
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

        t.Visualizer.BackgroundColor = CreamPanel;
        t.Visualizer.WaveformColor = Brown;
        t.Visualizer.WaveformFillColor = ImVec4(Brown.x, Brown.y, Brown.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(BeigeDark.x, BeigeDark.y, BeigeDark.z, 0.25f);
        t.Visualizer.BorderColor = BeigeMid;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (brown to golden cream) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = BrownDark;
        t.Visualizer.SpectrumColorMid = Brown;
        t.Visualizer.SpectrumColorHigh = BrownLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.831f, 0.722f, 0.604f, 1.00f); // #D4B89A
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = BeigeDarker;
        t.Visualizer.HighFreqTint = Brown;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.50f;
        t.Visualizer.BarBrightnessMax = 1.15f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BeigeMid;
        t.AlbumArtBox.BorderColorHovered = Brown;
        t.AlbumArtBox.BorderColorClicked = BrownLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = CreamDefault;
        t.AlbumArtBox.BackgroundColorHovered = CreamAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.15f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Brown.x, Brown.y, Brown.z, 0.06f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Brown.x, Brown.y, Brown.z, 0.14f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.96f, 0.94f, 0.92f, 0.95f);
        t.AlbumArtLightbox.BorderColor = BeigeDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Brown;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.20f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = BeigeDark;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Brown;
        t.SearchBar.rowHoverColor = CreamAlt;
        t.SearchBar.separatorColor = BeigeMid;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = CreamDefault;
        t.SearchBar.inputBorderColor = BeigeDark;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = BeigeDark;
        t.PlayerBar.ButtonHovered = BeigeMid;
        t.PlayerBar.ButtonActive = BrownDark;

        t.PlayerBar.ButtonPrimary = BeigeDark;
        t.PlayerBar.ButtonPrimaryHovered = BeigeMid;
        t.PlayerBar.ButtonPrimaryActive = BrownDark;

        t.PlayerBar.SliderTrack = BeigeMid;
        t.PlayerBar.SliderGrab = Brown;
        t.PlayerBar.SliderGrabActive = BrownLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = BeigeDark;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Brown;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BeigeMid;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.20f);

        return t;
    }

} // namespace moosic