//==============================================================================
// StormTheme.h
//==============================================================================
// Dramatic ocean storm theme – deep navy abyss, rain-soaked blue-greys,
// and electric cyan lightning flashes. Built with analogous cool palette
// + high-contrast electric accents for dramatic hierarchy.
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateStormTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        // Analogous cool spectrum: deep navy → storm blue → cyan lightning
        //==========================================================================

        // Abyss Navy – ocean depths
        const ImVec4 Abyss         = ImVec4(0.035f, 0.055f, 0.090f, 1.00f); //  9, 14, 23
        const ImVec4 AbyssDark     = ImVec4(0.022f, 0.035f, 0.060f, 1.00f); //  6,  9, 15
        const ImVec4 AbyssMid      = ImVec4(0.055f, 0.080f, 0.125f, 1.00f); // 14, 20, 32
        const ImVec4 AbyssSurface  = ImVec4(0.075f, 0.110f, 0.165f, 1.00f); // 19, 28, 42
        const ImVec4 AbyssPanel    = ImVec4(0.028f, 0.042f, 0.070f, 1.00f); //  7, 11, 18

        // Storm Blue – heavy rain clouds
        const ImVec4 Storm         = ImVec4(0.145f, 0.210f, 0.310f, 1.00f); // 37, 54, 79
        const ImVec4 StormDark     = ImVec4(0.100f, 0.150f, 0.225f, 1.00f); // 26, 38, 57
        const ImVec4 StormDarker   = ImVec4(0.070f, 0.105f, 0.160f, 1.00f); // 18, 27, 41
        const ImVec4 StormLight    = ImVec4(0.220f, 0.300f, 0.420f, 1.00f); // 56, 77,107
        const ImVec4 StormGlow     = ImVec4(0.145f, 0.210f, 0.310f, 0.22f);
        const ImVec4 StormSubtle   = ImVec4(0.145f, 0.210f, 0.310f, 0.12f);

        // Rain Grey-Blue – mist & rain bands
        const ImVec4 Rain          = ImVec4(0.320f, 0.390f, 0.480f, 1.00f); // 82, 99,122
        const ImVec4 RainDark      = ImVec4(0.230f, 0.285f, 0.360f, 1.00f); // 59, 73, 92
        const ImVec4 RainDarker    = ImVec4(0.155f, 0.195f, 0.255f, 1.00f); // 40, 50, 65
        const ImVec4 RainLight     = ImVec4(0.430f, 0.500f, 0.590f, 1.00f); //110,128,150
        const ImVec4 RainGlow      = ImVec4(0.320f, 0.390f, 0.480f, 0.20f);

        // Lightning Cyan – electric flash
        const ImVec4 Lightning     = ImVec4(0.380f, 0.760f, 0.960f, 1.00f); // 97,194,245
        const ImVec4 LightningDark = ImVec4(0.250f, 0.560f, 0.760f, 1.00f); // 64,143,194
        const ImVec4 LightningDeep = ImVec4(0.160f, 0.400f, 0.580f, 1.00f); // 41,102,148
        const ImVec4 LightningBright = ImVec4(0.580f, 0.880f, 1.000f, 1.00f); //148,224,255

        // Text (cool neutrals for legibility on dark navy)
        const ImVec4 TextBright    = ImVec4(0.94f, 0.96f, 0.98f, 1.00f);
        const ImVec4 TextMuted     = ImVec4(0.58f, 0.64f, 0.72f, 1.00f);
        const ImVec4 TextDim       = ImVec4(0.38f, 0.43f, 0.50f, 1.00f);
        const ImVec4 TextWhite     = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor         = Abyss;
        t.TitleBar.BackgroundColorActive   = Abyss;
        t.TitleBar.BackgroundColorInactive = ImVec4(Abyss.x, Abyss.y, Abyss.z, 0.85f);
        t.TitleBar.BackgroundOpacity       = 1.0f;

        t.TitleBar.ShowBottomBorder        = true;
        t.TitleBar.BottomBorderColor       = StormDarker;

        t.TitleBar.ShowWindowBorder        = true;
        t.TitleBar.WindowBorderColor       = RainDark;

        t.TitleBar.ShowAccentLine          = false;
        t.TitleBar.AccentLineColor         = Storm;

        t.TitleBar.TitleTextColor          = TextBright;
        t.TitleBar.TitleTextColorInactive  = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive           = Rain;
        t.ContentPanel.TabInactive         = StormDarker;
        t.ContentPanel.TabHovered          = Storm;
        t.ContentPanel.TabRounding         = 4.0f;

        t.ContentPanel.TabText             = TextWhite;
        t.ContentPanel.TabTextInactive     = TextMuted;

        t.ContentPanel.ButtonNormal        = Storm;
        t.ContentPanel.ButtonHovered       = Rain;
        t.ContentPanel.ButtonActive        = RainDark;
        t.ContentPanel.ButtonRounding      = 2.0f;

        t.ContentPanel.BorderColor         = RainDark;

        t.ContentPanel.TabSpacing          = 4.0f;
        t.ContentPanel.HeaderSpacing       = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                  = AbyssPanel;
        t.Window.ChildBg                   = Abyss;
        t.Window.WindowBorder              = StormDarker;

        t.Window.TitleBar                  = AbyssMid;
        t.Window.TitleBarActive            = AbyssSurface;

        t.Window.HeaderText                = TextBright;

        t.Window.TextPrimary               = TextBright;
        t.Window.TextSecondary             = TextMuted;
        t.Window.TextDisabled              = TextDim;

        t.Window.BrandText                 = RainLight;

        t.Window.ButtonNormal              = Storm;
        t.Window.ButtonHovered             = Rain;
        t.Window.ButtonActive              = RainDark;

        t.Window.ProgressBar               = Lightning;
        t.Window.PlayingHighlight          = StormGlow;
        t.Window.SeparatorColor            = StormDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        // ── Header ──
        t.TrackTable.HeaderBackground      = Storm;
        t.TrackTable.HeaderTextColor       = TextBright;
        t.TrackTable.HeaderBorderColor     = StormDarker;
        t.TrackTable.HeaderHovered         = AbyssSurface;
        t.TrackTable.HeaderActive          = Rain;

        // ── Header text per column ──
        t.TrackTable.HeaderTextTitle       = TextBright;
        t.TrackTable.HeaderTextArtist      = TextBright;
        t.TrackTable.HeaderTextAlbum       = TextBright;
        t.TrackTable.HeaderTextExtension   = TextBright;
        t.TrackTable.HeaderTextDuration    = TextBright;

        // ── Row colors ──
        t.TrackTable.RowDefault            = Abyss;
        t.TrackTable.RowDefaultAlt         = AbyssMid;
        t.TrackTable.RowHovered            = ImVec4(Storm.x, Storm.y, Storm.z, 0.45f);
        t.TrackTable.RowClicked            = ImVec4(Rain.x, Rain.y, Rain.z, 0.35f);
        t.TrackTable.RowSelected           = Rain;
        t.TrackTable.RowPlaying            = Lightning;

        // ── Row layout ──
        t.TrackTable.RowHeight             = 18.0f;
        t.TrackTable.RowPaddingX           = 4.0f;
        t.TrackTable.RowPaddingY           = 2.0f;

        // ── Text colors ──
        t.TrackTable.TextColor             = TextBright;
        t.TrackTable.TextDim               = TextDim;
        t.TrackTable.TextSelected          = TextWhite;
        t.TrackTable.TextPlaying           = TextWhite;

        // ── Row text per column ──
        t.TrackTable.RowTextTitle          = TextBright;
        t.TrackTable.RowTextArtist         = TextMuted;
        t.TrackTable.RowTextAlbum          = TextMuted;
        t.TrackTable.RowTextExtension      = TextDim;
        t.TrackTable.RowTextDuration       = TextMuted;

        // ── Border & Separator ──
        t.TrackTable.BorderColor           = StormDarker;
        t.TrackTable.BorderThickness       = 1.0f;
        t.TrackTable.ShowRowSeparators     = true;
        t.TrackTable.RowSeparatorColor     = ImVec4(StormDarker.x, StormDarker.y, StormDarker.z, 0.40f);

        // ── Scrollbar ──
        t.TrackTable.ScrollbarBg           = AbyssPanel;
        t.TrackTable.ScrollbarGrab         = Storm;
        t.TrackTable.ScrollbarGrabHovered  = Rain;
        t.TrackTable.ScrollbarGrabActive   = Lightning;
        t.TrackTable.ScrollbarWidth        = 8.0f;
        t.TrackTable.ScrollbarRounding     = 4.0f;

        // ── Smoothing / Animation ──
        t.TrackTable.HoverFadeSpeed        = 0.15f;
        t.TrackTable.SelectionFadeSpeed    = 0.20f;
        t.TrackTable.ScrollSmoothing       = 0.12f;

        // ── Misc ──
        t.TrackTable.TableRounding         = 0.0f;
        t.TrackTable.MinColumnWidth        = 30.0f;

        // ── Column widths ──
        t.TrackTable.TitleWidth            = 350.0f;
        t.TrackTable.ArtistWidth           = 180.0f;
        t.TrackTable.AlbumWidth            = 180.0f;
        t.TrackTable.ExtensionWidth        = 50.0f;
        t.TrackTable.DurationWidth         = 80.0f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor       = AbyssPanel;
        t.Visualizer.WaveformColor         = Rain;
        t.Visualizer.WaveformFillColor     = ImVec4(Rain.x, Rain.y, Rain.z, 0.12f);
        t.Visualizer.GridColor             = ImVec4(Storm.x, Storm.y, Storm.z, 0.28f);
        t.Visualizer.BorderColor           = StormDarker;
        t.Visualizer.PlaceholderColor      = TextDim;

        // ── Color ramp (deep → mid → lightning flash) ──
        t.Visualizer.UseColorRamp          = true;
        t.Visualizer.SpectrumColorLow      = StormDark;
        t.Visualizer.SpectrumColorMid      = Rain;
        t.Visualizer.SpectrumColorHigh     = Lightning;
        t.Visualizer.SpectrumColorPeak     = LightningBright;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.42f;
        t.Visualizer.ColorRampHighThreshold= 0.78f;

        // ── Frequency tint ──
        t.Visualizer.UseFrequencyTint      = true;
        t.Visualizer.LowFreqTint           = Storm;
        t.Visualizer.HighFreqTint          = Lightning;
        t.Visualizer.FrequencyTintBlend    = 0.32f;

        // ── Brightness ──
        t.Visualizer.BarBrightnessMin      = 0.38f;
        t.Visualizer.BarBrightnessMax      = 1.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor          = StormDarker;
        t.AlbumArtBox.BorderColorHovered   = Rain;
        t.AlbumArtBox.BorderColorClicked   = Lightning;
        t.AlbumArtBox.BorderThickness      = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding       = 3.0f;

        t.AlbumArtBox.BackgroundColor      = AbyssMid;
        t.AlbumArtBox.BackgroundColorHovered = AbyssSurface;

        t.AlbumArtBox.ShowShadow           = true;
        t.AlbumArtBox.ShadowColor          = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        t.AlbumArtBox.PlaceholderTextColor = TextDim;

        t.AlbumArtBox.ShowHoverOverlay     = true;
        t.AlbumArtBox.HoverOverlayColor    = ImVec4(Rain.x, Rain.y, Rain.z, 0.10f);
        t.AlbumArtBox.ClickOverlayColor    = ImVec4(Rain.x, Rain.y, Rain.z, 0.20f);

        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor      = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.02f, 0.03f, 0.05f, 0.96f);
        t.AlbumArtLightbox.BorderColor     = Storm;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Lightning;
        t.AlbumArtLightbox.TitleColor      = TextBright;
        t.AlbumArtLightbox.ArtistColor     = TextMuted;

        t.AlbumArtLightbox.MaxWidth        = 400.0f;
        t.AlbumArtLightbox.MaxHeight       = 400.0f;
        t.AlbumArtLightbox.BorderRounding  = 4.0f;
        t.AlbumArtLightbox.BorderThickness = 1.0f;
        t.AlbumArtLightbox.CloseButtonSize = 24.0f;
        t.AlbumArtLightbox.Padding         = 30.0f;
        t.AlbumArtLightbox.TitleSpacing    = 12.0f;
        t.AlbumArtLightbox.ArtistSpacing   = 8.0f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        // ── Dropdown Colors ──
        t.SearchBar.shadowColor            = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor        = AbyssPanel;
        t.SearchBar.borderColor            = StormDarker;
        t.SearchBar.textColor              = TextBright;
        t.SearchBar.highlightTextColor     = Lightning;
        t.SearchBar.rowHoverColor          = AbyssSurface;
        t.SearchBar.separatorColor         = StormDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor           = AbyssMid;
        t.SearchBar.inputBorderColor       = StormDarker;
        t.SearchBar.inputTextColor         = TextBright;
        t.SearchBar.inputHintColor         = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary            = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary          = t.Window.TextSecondary;

        t.PlayerBar.ButtonNormal           = Storm;
        t.PlayerBar.ButtonHovered          = Rain;
        t.PlayerBar.ButtonActive           = RainDark;

        t.PlayerBar.ButtonPrimary          = Storm;
        t.PlayerBar.ButtonPrimaryHovered   = Rain;
        t.PlayerBar.ButtonPrimaryActive    = RainDark;

        t.PlayerBar.SliderTrack            = StormDarker;
        t.PlayerBar.SliderGrab             = Rain;
        t.PlayerBar.SliderGrabActive       = Lightning;

        t.PlayerBar.Lightbox               = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox            = t.AlbumArtBox;
        t.PlayerBar.Visualizer             = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor      = AbyssPanel;
        t.ContextMenu.BorderColor          = RainDark;
        t.ContextMenu.TextColor            = TextBright;
        t.ContextMenu.TextDisabledColor    = TextDim;
        t.ContextMenu.HoverColor           = Lightning;
        t.ContextMenu.HoverTextColor       = TextWhite;
        t.ContextMenu.SeparatorColor       = Storm;
        t.ContextMenu.ShadowColor          = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

        return t;
    }

} // namespace moosic