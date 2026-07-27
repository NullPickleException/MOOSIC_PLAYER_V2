//==============================================================================
// CoffeeTheme.h
//==============================================================================
// Warm medium roast coffee theme using 60/30/10 rule:
// 60% Rich brown backgrounds (#1E1814, #231D18, #28211C, #2D2620, #332B24)
// 30% Warm tan surfaces (#5C4A3A, #7A6450, #8B7560)
// 10% Golden amber accent (#C8925A)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateCoffeeTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        // 60% - Rich brown backgrounds
        const ImVec4 CoffeeDeep = ImVec4(0.118f, 0.094f, 0.078f, 1.00f);    // #1E1814
        const ImVec4 CoffeePanel = ImVec4(0.137f, 0.114f, 0.094f, 1.00f);   // #231D18
        const ImVec4 CoffeeDefault = ImVec4(0.157f, 0.129f, 0.110f, 1.00f); // #28211C
        const ImVec4 CoffeeAlt = ImVec4(0.176f, 0.149f, 0.125f, 1.00f);     // #2D2620
        const ImVec4 CoffeeSurface = ImVec4(0.200f, 0.169f, 0.141f, 1.00f); // #332B24

        const ImVec4 CoffeeGlow = ImVec4(0.157f, 0.129f, 0.110f, 0.20f);
        const ImVec4 CoffeeVeryLight = ImVec4(0.157f, 0.129f, 0.110f, 0.5f);
        const ImVec4 CoffeeSubtle = ImVec4(0.157f, 0.129f, 0.110f, 0.10f);

        // 30% - Warm tan surfaces
        const ImVec4 TanDark = ImVec4(0.361f, 0.290f, 0.227f, 1.00f);   // #5C4A3A
        const ImVec4 TanMid = ImVec4(0.478f, 0.392f, 0.314f, 1.00f);    // #7A6450
        const ImVec4 TanLight = ImVec4(0.545f, 0.459f, 0.376f, 1.00f);  // #8B7560
        const ImVec4 TanDarker = ImVec4(0.271f, 0.220f, 0.173f, 1.00f); // Darker variant

        // 10% - Golden amber accent
        const ImVec4 Amber = ImVec4(0.784f, 0.573f, 0.353f, 1.00f);       // #C8925A
        const ImVec4 AmberDark = ImVec4(0.651f, 0.459f, 0.247f, 1.00f);   // #A6753F
        const ImVec4 AmberDarker = ImVec4(0.478f, 0.337f, 0.188f, 1.00f); // #7A5630
        const ImVec4 AmberLight = ImVec4(0.831f, 0.659f, 0.447f, 1.00f);  // #D4A872
        const ImVec4 AmberVeryLight = ImVec4(0.831f, 0.659f, 0.447f, 0.5f);

        // Search dropdown - lighter tint of CoffeeDefault
        const ImVec4 SearchDropdownBg = ImVec4(0.196f, 0.165f, 0.141f, 1.00f);

        // Text
        const ImVec4 TextBright = ImVec4(0.941f, 0.922f, 0.902f, 1.00f); // #F0EBE6
        const ImVec4 TextMuted = ImVec4(0.722f, 0.663f, 0.604f, 1.00f);  // #B8A99A
        const ImVec4 TextDim = ImVec4(0.478f, 0.431f, 0.384f, 1.00f);    // #7A6E62
        const ImVec4 TextWhite = ImVec4(0.980f, 0.969f, 0.957f, 1.00f);  // #FAF7F4

        // Borders
        const ImVec4 BorderSubtle = ImVec4(0.239f, 0.200f, 0.169f, 1.00f); // #3D332B

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.078f, 0.059f, 0.047f, 1.00f); // #140F0C - Darker than CoffeeDeep
        t.TitleBar.BackgroundColorActive = ImVec4(0.078f, 0.059f, 0.047f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.078f, 0.059f, 0.047f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;

        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;

        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = TanMid;

        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Amber;

        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Amber;
        t.ContentPanel.TabInactive = CoffeeDefault;
        t.ContentPanel.TabHovered = CoffeeAlt;
        t.ContentPanel.TabRounding = 4.0f;

        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;

        t.ContentPanel.ButtonNormal = TanDark;
        t.ContentPanel.ButtonHovered = TanMid;
        t.ContentPanel.ButtonActive = AmberDark;
        t.ContentPanel.ButtonRounding = 2.0f;

        t.ContentPanel.BorderColor = TanMid;

        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = CoffeePanel;
        t.Window.ChildBg = CoffeeDeep;
        t.Window.WindowBorder = BorderSubtle;

        t.Window.TitleBar = CoffeeDefault;
        t.Window.TitleBarActive = CoffeeAlt;

        t.Window.HeaderText = TextBright;

        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;

        t.Window.BrandText = Amber;

        t.Window.ButtonNormal = TanDark;
        t.Window.ButtonHovered = TanMid;
        t.Window.ButtonActive = AmberDark;

        t.Window.ProgressBar = Amber;
        t.Window.PlayingHighlight = CoffeeGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground = TanDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = CoffeeSurface;
        t.TrackTable.HeaderActive = Amber;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault = CoffeeDeep;
        t.TrackTable.RowDefaultAlt = CoffeeDefault;
        t.TrackTable.RowHovered = CoffeeVeryLight;
        t.TrackTable.RowClicked = AmberDarker;
        t.TrackTable.RowSelected = TanDark;
        t.TrackTable.RowPlaying = Amber;

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
        t.TrackTable.ScrollbarBg = CoffeePanel;
        t.TrackTable.ScrollbarGrab = TanDark;
        t.TrackTable.ScrollbarGrabHovered = TanMid;
        t.TrackTable.ScrollbarGrabActive = Amber;
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

        t.Visualizer.BackgroundColor = CoffeePanel;
        t.Visualizer.WaveformColor = Amber;
        t.Visualizer.WaveformFillColor = ImVec4(Amber.x, Amber.y, Amber.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(TanDark.x, TanDark.y, TanDark.z, 0.25f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;

        // ── Color ramp (warm amber to golden cream) ──
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = AmberDark;
        t.Visualizer.SpectrumColorMid = Amber;
        t.Visualizer.SpectrumColorHigh = AmberLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.910f, 0.796f, 0.627f, 1.00f); // #E8CBA0
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.50f;
        t.Visualizer.ColorRampHighThreshold = 0.82f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = TanDark;
        t.Visualizer.HighFreqTint = Amber;
        t.Visualizer.FrequencyTintBlend = 0.30f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin = 0.45f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = Amber;
        t.AlbumArtBox.BorderColorClicked = AmberLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;

        t.AlbumArtBox.BackgroundColor = CoffeeDefault;
        t.AlbumArtBox.BackgroundColorHovered = CoffeeAlt;

        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Amber.x, Amber.y, Amber.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Amber.x, Amber.y, Amber.z, 0.18f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.06f, 0.05f, 0.04f, 0.95f);
        t.AlbumArtLightbox.BorderColor = TanDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Amber;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = TanMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Amber;
        t.SearchBar.rowHoverColor = CoffeeAlt;
        t.SearchBar.separatorColor = BorderSubtle;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = CoffeeDefault;
        t.SearchBar.inputBorderColor = TanMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal = TanDark;
        t.PlayerBar.ButtonHovered = TanMid;
        t.PlayerBar.ButtonActive = AmberDark;

        t.PlayerBar.ButtonPrimary = TanDark;
        t.PlayerBar.ButtonPrimaryHovered = TanMid;
        t.PlayerBar.ButtonPrimaryActive = AmberDark;

        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = Amber;
        t.PlayerBar.SliderGrabActive = AmberLight;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = TanMid;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Amber;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);

        return t;
    }

} // namespace moosic