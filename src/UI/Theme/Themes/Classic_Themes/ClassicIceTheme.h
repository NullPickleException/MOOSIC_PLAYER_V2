//==============================================================================
// ClassicIceTheme.h
//==============================================================================
// Clean ice blue theme with 3D glossy effects
// 3 base colors: White Ice, Sky Blue, Bright Cyan
// Palette: #89CFF3, #A0E9FF, #CDF5FD, rgb(0,169,255), rgb(137,207,243)
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicIceTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 3 distinct ice tones
        //==========================================================================

        // ── White Ice (60%) - main backgrounds (#CDF5FD) ──────────────
        const ImVec4 WhiteIceDeep    = ImVec4(0.76f, 0.94f, 0.98f, 1.00f);  // #C2F0FA
        const ImVec4 WhiteIcePanel   = ImVec4(0.80f, 0.96f, 0.99f, 1.00f);  // #CCF5FC
        const ImVec4 WhiteIceDefault = ImVec4(0.84f, 0.97f, 0.99f, 1.00f);  // #D6F7FD
        const ImVec4 WhiteIceAlt     = ImVec4(0.88f, 0.98f, 1.00f, 1.00f);  // #E0FAFF
        const ImVec4 WhiteIceSurface = ImVec4(0.92f, 0.99f, 1.00f, 1.00f);  // #EBFCFF

        // ── Sky Blue (30%) - surfaces (#89CFF3, rgb(137,207,243)) ────
        const ImVec4 SkyBlueDark     = ImVec4(0.42f, 0.76f, 0.91f, 1.00f);  // #6BC2E8
        const ImVec4 SkyBlueMid      = ImVec4(0.54f, 0.81f, 0.95f, 1.00f);  // #89CFF3
        const ImVec4 SkyBlueLight    = ImVec4(0.63f, 0.88f, 0.98f, 1.00f);  // #A0E9FF
        const ImVec4 SkyBlueDarker   = ImVec4(0.32f, 0.66f, 0.85f, 1.00f);  // #52A8D9

        // ── Bright Cyan (10%) - accent (rgb(0,169,255)) ──────────────
        const ImVec4 Accent          = ImVec4(0.00f, 0.66f, 1.00f, 1.00f);  // #00A9FF
        const ImVec4 AccentDark      = ImVec4(0.00f, 0.52f, 0.85f, 1.00f);  // #0085D9
        const ImVec4 AccentDarker    = ImVec4(0.00f, 0.38f, 0.68f, 1.00f);  // #0061AD
        const ImVec4 AccentLight     = ImVec4(0.30f, 0.78f, 1.00f, 1.00f);  // #4DC7FF
        const ImVec4 AccentVeryLight = ImVec4(0.30f, 0.78f, 1.00f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 IceGlow         = ImVec4(0.00f, 0.66f, 1.00f, 0.25f);
        const ImVec4 IceVeryLight    = ImVec4(0.00f, 0.66f, 1.00f, 0.50f);
        const ImVec4 IceSubtle       = ImVec4(0.00f, 0.66f, 1.00f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.82f, 0.96f, 0.99f, 1.00f);

        // ── Text (Dark Blue tones for readability on light bg) ──────
        const ImVec4 TextDark        = ImVec4(0.05f, 0.15f, 0.35f, 1.00f);  // #0D2659 - Primary dark text
        const ImVec4 TextDarkMuted   = ImVec4(0.10f, 0.25f, 0.50f, 1.00f);  // #1A4080 - Secondary text
        const ImVec4 TextDarkDim     = ImVec4(0.20f, 0.40f, 0.65f, 1.00f);  // #3366A6 - Dimmed text
        const ImVec4 TextWhite       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);  // #FFFFFF - Text on dark bg
        const ImVec4 TextBright      = ImVec4(0.90f, 0.95f, 1.00f, 1.00f);  // #E6F2FF - Light text

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle    = ImVec4(0.35f, 0.72f, 0.92f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite      = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 GlossStrong     = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 BevelShadow     = ImVec4(0.00f, 0.35f, 0.60f, 0.50f);
        const ImVec4 BevelBorder     = ImVec4(0.10f, 0.50f, 0.80f, 0.65f);

        //==========================================================================
        // Title Bar (keeps white text on blue gradient background)
        //==========================================================================

        t.TitleBar.BackgroundColor           = ImVec4(0.20f, 0.55f, 0.80f, 1.00f);
        t.TitleBar.BackgroundColorActive     = ImVec4(0.20f, 0.55f, 0.80f, 1.00f);
        t.TitleBar.BackgroundColorInactive   = ImVec4(0.20f, 0.55f, 0.80f, 0.85f);
        t.TitleBar.BackgroundOpacity         = 1.0f;
        t.TitleBar.ShowBottomBorder          = true;
        t.TitleBar.BottomBorderColor         = BorderSubtle;
        t.TitleBar.ShowWindowBorder          = true;
        t.TitleBar.WindowBorderColor         = SkyBlueMid;
        t.TitleBar.ShowAccentLine            = true;
        t.TitleBar.AccentLineColor           = Accent;
        t.TitleBar.TitleTextColor            = TextWhite;          // White on dark blue title bar
        t.TitleBar.TitleTextColorInactive    = TextBright;         // Light on inactive

        // Title bar classic effects
        t.TitleBar.UseTitleBarGradient       = true;
        t.TitleBar.TitleBarGradientTop       = ImVec4(0.30f, 0.62f, 0.88f, 1.00f);
        t.TitleBar.TitleBarGradientBottom    = ImVec4(0.15f, 0.45f, 0.72f, 1.00f);
        t.TitleBar.UseTitleBarGloss          = true;
        t.TitleBar.TitleBarGlossIntensity    = 0.40f;
        t.TitleBar.TitleBarGlossColor        = GlossStrong;
        t.TitleBar.UseTitleBarBevel          = true;
        t.TitleBar.TitleBarBevelThickness    = 1.5f;
        t.TitleBar.TitleBarBevelLight        = GlossStrong;
        t.TitleBar.TitleBarBevelDark         = BevelShadow;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive             = Accent;
        t.ContentPanel.TabInactive           = WhiteIceDefault;
        t.ContentPanel.TabHovered            = WhiteIceAlt;
        t.ContentPanel.TabRounding           = 4.0f;
        t.ContentPanel.TabText               = TextWhite;          // White on accent tabs
        t.ContentPanel.TabTextInactive       = TextDark;           // Dark on light inactive tabs
        t.ContentPanel.ButtonNormal          = SkyBlueDark;
        t.ContentPanel.ButtonHovered         = SkyBlueMid;
        t.ContentPanel.ButtonActive          = AccentDark;
        t.ContentPanel.ButtonRounding        = 2.0f;
        t.ContentPanel.BorderColor           = SkyBlueMid;
        t.ContentPanel.BorderThickness       = 2.5f;
        t.ContentPanel.TabSpacing            = 4.0f;
        t.ContentPanel.HeaderSpacing         = 4.0f;

        t.ContentPanel.UseGlossyTabs         = true;
        t.ContentPanel.TabGlossIntensity     = 0.35f;
        t.ContentPanel.TabGlossHighlight     = GlossWhite;
        t.ContentPanel.UseGradientTabs       = true;
        t.ContentPanel.TabGradientTop        = WhiteIceDefault;
        t.ContentPanel.TabGradientBottom     = SkyBlueDark;
        t.ContentPanel.UseTabBevel           = true;
        t.ContentPanel.TabBevelThickness     = 2.0f;
        t.ContentPanel.TabBevelLight         = GlossStrong;
        t.ContentPanel.TabBevelDark          = BevelShadow;
        t.ContentPanel.TabBevelBorderColor   = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                    = WhiteIcePanel;
        t.Window.ChildBg                     = WhiteIceDeep;
        t.Window.WindowBorder                = BorderSubtle;
        t.Window.TitleBar                    = WhiteIceDefault;
        t.Window.TitleBarActive              = WhiteIceAlt;
        t.Window.HeaderText                  = TextDark;           // Dark text on light header
        t.Window.TextPrimary                 = TextDark;           // Dark primary text
        t.Window.TextSecondary               = TextDarkMuted;      // Muted dark text
        t.Window.TextDisabled                = TextDarkDim;        // Dimmed dark text
        t.Window.BrandText                   = Accent;             // Accent remains bright

        t.Window.ButtonNormal                = SkyBlueDark;
        t.Window.ButtonHovered               = SkyBlueMid;
        t.Window.ButtonActive                = AccentDark;
        t.Window.ButtonRounding              = 8.0f;
        t.Window.UseWindowGradient           = true;
        t.Window.WindowGradientTop           = WhiteIceDefault;
        t.Window.WindowGradientBottom        = WhiteIceDeep;
        t.Window.WindowOpacity               = 0.95f;
        t.Window.UseButtonGloss              = true;
        t.Window.ButtonGlossIntensity        = 0.50f;
        t.Window.ButtonGlossHighlight        = GlossStrong;
        t.Window.UseButtonBevel              = true;
        t.Window.ButtonBevelThickness        = 2.0f;
        t.Window.ButtonBevelLight            = GlossStrong;
        t.Window.ButtonBevelDark             = BevelShadow;
        t.Window.ChildBgOpacity              = 0.95f;
        t.Window.ProgressBar                 = Accent;
        t.Window.PlayingHighlight            = IceGlow;
        t.Window.SeparatorColor              = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground        = SkyBlueDark;
        t.TrackTable.HeaderTextColor         = TextWhite;          // White on colored header
        t.TrackTable.HeaderBorderColor       = BorderSubtle;
        t.TrackTable.HeaderHovered           = WhiteIceSurface;
        t.TrackTable.HeaderActive            = Accent;
        t.TrackTable.HeaderTextTitle         = TextWhite;
        t.TrackTable.HeaderTextArtist        = TextWhite;
        t.TrackTable.HeaderTextAlbum         = TextWhite;
        t.TrackTable.HeaderTextExtension     = TextWhite;
        t.TrackTable.HeaderTextDuration      = TextWhite;
        t.TrackTable.RowDefault              = WhiteIceDeep;
        t.TrackTable.RowDefaultAlt           = WhiteIceDefault;
        t.TrackTable.RowHovered              = IceVeryLight;
        t.TrackTable.RowClicked              = AccentDarker;
        t.TrackTable.RowSelected             = SkyBlueDark;
        t.TrackTable.RowPlaying              = Accent;
        t.TrackTable.RowHeight               = 18.0f;
        t.TrackTable.RowPaddingX             = 4.0f;
        t.TrackTable.RowPaddingY             = 2.0f;
        t.TrackTable.TextColor               = TextDark;           // Dark text on light rows
        t.TrackTable.TextDim                 = TextDarkDim;
        t.TrackTable.TextSelected            = TextWhite;          // White on selected (colored bg)
        t.TrackTable.TextPlaying             = TextWhite;          // White on playing (accent bg)
        t.TrackTable.RowTextTitle            = TextDark;
        t.TrackTable.RowTextArtist           = TextDarkMuted;
        t.TrackTable.RowTextAlbum            = TextDarkMuted;
        t.TrackTable.RowTextExtension        = TextDarkDim;
        t.TrackTable.RowTextDuration         = TextDarkMuted;
        t.TrackTable.BorderColor             = BorderSubtle;
        t.TrackTable.BorderThickness         = 1.0f;
        t.TrackTable.ShowRowSeparators       = true;
        t.TrackTable.RowSeparatorColor       = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
        t.TrackTable.ScrollbarBg             = WhiteIcePanel;
        t.TrackTable.ScrollbarGrab           = SkyBlueDark;
        t.TrackTable.ScrollbarGrabHovered    = SkyBlueMid;
        t.TrackTable.ScrollbarGrabActive     = Accent;
        t.TrackTable.ScrollbarWidth          = 8.0f;
        t.TrackTable.ScrollbarRounding       = 4.0f;
        t.TrackTable.HoverFadeSpeed          = 0.15f;
        t.TrackTable.SelectionFadeSpeed      = 0.20f;
        t.TrackTable.ScrollSmoothing         = 0.12f;
        t.TrackTable.TableRounding           = 0.0f;
        t.TrackTable.MinColumnWidth          = 30.0f;
        t.TrackTable.TitleWidth              = 350.0f;
        t.TrackTable.ArtistWidth             = 180.0f;
        t.TrackTable.AlbumWidth              = 180.0f;
        t.TrackTable.ExtensionWidth          = 50.0f;
        t.TrackTable.DurationWidth           = 80.0f;

        t.TrackTable.UseGlossyHeader         = true;
        t.TrackTable.HeaderGlossIntensity    = 0.40f;
        t.TrackTable.HeaderGlossColor        = GlossStrong;
        t.TrackTable.UseHeaderGradient       = true;
        t.TrackTable.HeaderGradientTop       = SkyBlueMid;
        t.TrackTable.HeaderGradientBottom    = SkyBlueDark;
        t.TrackTable.UseGlossySelection      = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar     = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor         = WhiteIceDeep;
        t.Visualizer.WaveformColor           = Accent;
        t.Visualizer.WaveformFillColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.15f);
        t.Visualizer.GridColor               = ImVec4(SkyBlueDark.x, SkyBlueDark.y, SkyBlueDark.z, 0.30f);
        t.Visualizer.BorderColor             = BorderSubtle;
        t.Visualizer.PlaceholderColor        = TextDarkDim;
        t.Visualizer.UseColorRamp            = true;
        t.Visualizer.SpectrumColorLow        = AccentDark;
        t.Visualizer.SpectrumColorMid        = Accent;
        t.Visualizer.SpectrumColorHigh       = AccentLight;
        t.Visualizer.SpectrumColorPeak       = ImVec4(0.70f, 0.92f, 1.00f, 1.00f);
        t.Visualizer.ColorRampLowThreshold   = 0.0f;
        t.Visualizer.ColorRampMidThreshold   = 0.45f;
        t.Visualizer.ColorRampHighThreshold  = 0.80f;
        t.Visualizer.UseFrequencyTint        = true;
        t.Visualizer.LowFreqTint             = SkyBlueDark;
        t.Visualizer.HighFreqTint            = Accent;
        t.Visualizer.FrequencyTintBlend      = 0.30f;
        t.Visualizer.BarBrightnessMin        = 0.55f;
        t.Visualizer.BarBrightnessMax        = 1.30f;
        t.Visualizer.UseGlossyBars           = true;
        t.Visualizer.BarGlossIntensity       = 0.40f;
        t.Visualizer.BarGlossColor           = GlossStrong;
        t.Visualizer.UseVisualizerGradient   = true;
        t.Visualizer.VisualizerGradientTop   = WhiteIceDefault;
        t.Visualizer.VisualizerGradientBottom = SkyBlueDark;
        t.Visualizer.UseGlassEffect          = true;
        t.Visualizer.GlassOpacity            = 0.20f;
        t.Visualizer.UseGlossyWaveform       = true;
        t.Visualizer.WaveformGlossIntensity  = 0.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor            = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered     = Accent;
        t.AlbumArtBox.BorderColorClicked     = AccentLight;
        t.AlbumArtBox.BorderThickness        = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding         = 3.0f;
        t.AlbumArtBox.BackgroundColor        = WhiteIceDefault;
        t.AlbumArtBox.BackgroundColorHovered = WhiteIceAlt;
        t.AlbumArtBox.ShowShadow             = true;
        t.AlbumArtBox.ShadowColor            = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor   = TextDarkDim;
        t.AlbumArtBox.ShowHoverOverlay       = true;
        t.AlbumArtBox.HoverOverlayColor      = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor      = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover  = true;
        t.AlbumArtBox.PlayButtonColor        = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.UseGlossyOverlay       = true;
        t.AlbumArtBox.GlossyIntensity        = 0.35f;
        t.AlbumArtBox.GlossyHighlightColor   = GlossStrong;
        t.AlbumArtBox.UseInnerShadow         = true;
        t.AlbumArtBox.InnerShadowColor       = ImVec4(0.00f, 0.30f, 0.55f, 0.40f);
        t.AlbumArtBox.InnerShadowSize        = 5.0f;
        t.AlbumArtBox.UseReflection          = true;
        t.AlbumArtBox.ReflectionHeight       = 0.25f;
        t.AlbumArtBox.ReflectionOpacity      = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor      = ImVec4(0.10f, 0.40f, 0.62f, 0.95f);
        t.AlbumArtLightbox.BorderColor          = SkyBlueDark;
        t.AlbumArtLightbox.CloseButtonColor     = TextBright;         // Light on dark overlay
        t.AlbumArtLightbox.CloseButtonHovered   = Accent;
        t.AlbumArtLightbox.TitleColor           = TextWhite;          // White on dark overlay
        t.AlbumArtLightbox.ArtistColor          = TextBright;         // Light on dark overlay
        t.AlbumArtLightbox.MaxWidth             = 400.0f;
        t.AlbumArtLightbox.MaxHeight            = 400.0f;
        t.AlbumArtLightbox.BorderRounding       = 4.0f;
        t.AlbumArtLightbox.BorderThickness      = 1.0f;
        t.AlbumArtLightbox.CloseButtonSize      = 24.0f;
        t.AlbumArtLightbox.Padding              = 30.0f;
        t.AlbumArtLightbox.TitleSpacing         = 12.0f;
        t.AlbumArtLightbox.ArtistSpacing        = 8.0f;
        t.AlbumArtLightbox.UseLightboxGloss        = true;
        t.AlbumArtLightbox.LightboxGlossIntensity  = 0.30f;
        t.AlbumArtLightbox.LightboxGlossColor      = GlossStrong;
        t.AlbumArtLightbox.UseLightboxGradient     = true;
        t.AlbumArtLightbox.LightboxGradientTop     = ImVec4(0.18f, 0.48f, 0.68f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom  = ImVec4(0.08f, 0.30f, 0.50f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton    = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor              = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor          = SearchDropdownBg;
        t.SearchBar.borderColor              = SkyBlueMid;
        t.SearchBar.textColor                = TextDark;           // Dark text in search
        t.SearchBar.highlightTextColor       = Accent;
        t.SearchBar.rowHoverColor            = WhiteIceAlt;
        t.SearchBar.separatorColor           = BorderSubtle;
        t.SearchBar.inputBgColor             = WhiteIceDefault;
        t.SearchBar.inputBorderColor         = SkyBlueMid;
        t.SearchBar.inputTextColor           = TextDark;           // Dark text in input
        t.SearchBar.inputHintColor           = TextDarkDim;
        t.SearchBar.UseSearchGloss           = true;
        t.SearchBar.SearchGlossIntensity     = 0.30f;
        t.SearchBar.SearchGlossColor         = GlossStrong;
        t.SearchBar.UseSearchGradient        = true;
        t.SearchBar.SearchGradientTop        = SkyBlueMid;
        t.SearchBar.SearchGradientBottom     = WhiteIceDefault;
        t.SearchBar.UseRoundedInput          = true;
        t.SearchBar.InputRounding            = 8.0f;
        t.SearchBar.UseGlossyDropdown        = true;
        t.SearchBar.DropdownGlossIntensity   = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary                 = TextDark;        // Dark text on light player bar
        t.PlayerBar.TextSecondary               = TextDarkMuted;
        t.PlayerBar.ButtonNormal                = WhiteIceDeep;
        t.PlayerBar.ButtonHovered               = SkyBlueMid;
        t.PlayerBar.ButtonActive                = AccentDark;
        t.PlayerBar.ButtonPrimary               = WhiteIceDeep;
        t.PlayerBar.ButtonPrimaryHovered        = SkyBlueMid;
        t.PlayerBar.ButtonPrimaryActive         = AccentDark;
        t.PlayerBar.SliderTrack                 = BorderSubtle;
        t.PlayerBar.SliderGrab                  = Accent;
        t.PlayerBar.SliderGrabActive            = AccentLight;
        t.PlayerBar.ButtonRounding              = 8.0f;
        t.PlayerBar.SliderRounding              = 4.0f;
        t.PlayerBar.UseButtonGloss              = true;
        t.PlayerBar.ButtonGlossIntensity        = 1.60f;
        t.PlayerBar.ButtonGlossHighlight        = GlossStrong;
        t.PlayerBar.UseButtonBevel              = true;
        t.PlayerBar.ButtonBevelThickness        = 1.4f;
        t.PlayerBar.ButtonBevelLight            = GlossStrong;
        t.PlayerBar.ButtonBevelDark             = BevelShadow;
        t.PlayerBar.ButtonBevelBorderColor      = BevelBorder;
        t.PlayerBar.UsePlayerBarGradient        = true;
        t.PlayerBar.PlayerBarGradientTop        = WhiteIceDefault;
        t.PlayerBar.PlayerBarGradientBottom     = SkyBlueDark;
        t.PlayerBar.PlayerBarGradientRounding   = 8.0f;
        t.PlayerBar.PlayerBarOpacity            = 0.95f;
        t.PlayerBar.UsePlayerBarBevel           = true;
        t.PlayerBar.PlayerBarBevelThickness     = 2.5f;
        t.PlayerBar.PlayerBarBevelLight         = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark          = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor   = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient      = true;
        t.PlayerBar.SliderTrackGradientTop      = WhiteIceDefault;
        t.PlayerBar.SliderTrackGradientBottom   = SkyBlueDark;
        t.PlayerBar.UseSliderGrabGloss          = true;
        t.PlayerBar.SliderGrabGlossIntensity    = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight    = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel          = true;
        t.PlayerBar.SliderGrabBevelThickness    = 1.5f;
        t.PlayerBar.SliderGrabBevelLight        = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark         = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor  = BevelBorder;
        t.PlayerBar.UseProgressGradient         = true;
        t.PlayerBar.ProgressTrackColor          = WhiteIceDeep;
        t.PlayerBar.ProgressFillColor           = Accent;
        t.PlayerBar.ProgressFillTop             = AccentLight;
        t.PlayerBar.ProgressFillBottom          = AccentDark;
        t.PlayerBar.ProgressHeight              = 10.0f;
        t.PlayerBar.ProgressRounding            = 5.0f;
        t.PlayerBar.ShowProgressGloss           = true;
        t.PlayerBar.ProgressGlossOpacity        = 0.35f;
        t.PlayerBar.Lightbox                    = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox                 = t.AlbumArtBox;
        t.PlayerBar.Visualizer                  = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor           = SearchDropdownBg;
        t.ContextMenu.BorderColor               = SkyBlueMid;
        t.ContextMenu.TextColor                 = TextDark;        // Dark text in menu
        t.ContextMenu.TextDisabledColor         = TextDarkDim;
        t.ContextMenu.HoverColor                = Accent;
        t.ContextMenu.HoverTextColor            = TextWhite;       // White on accent hover
        t.ContextMenu.SeparatorColor            = BorderSubtle;
        t.ContextMenu.ShadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.ContextMenu.UseMenuGloss              = true;
        t.ContextMenu.MenuGlossIntensity        = 0.30f;
        t.ContextMenu.MenuGlossColor            = GlossStrong;
        t.ContextMenu.UseMenuGradient           = true;
        t.ContextMenu.MenuGradientTop           = SkyBlueMid;
        t.ContextMenu.MenuGradientBottom        = WhiteIceDefault;
        t.ContextMenu.UseGlossySelection        = true;
        t.ContextMenu.SelectionGlossIntensity   = 0.35f;

        return t;
    }

} // namespace moosic