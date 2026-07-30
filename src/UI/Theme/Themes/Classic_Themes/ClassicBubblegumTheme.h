//==============================================================================
// ClassicBubblegumTheme.h
//==============================================================================
// Classic bubblegum/retro candy theme with 3D glossy effects
// Nostalgic palette inspired by 90s bubblegum aesthetic
// Palette: #D65A8F, #E977A6, #F995BB, #FDB7D2, #FFE4F0, #5EA9E8, #84C7F5, #B7E8FF, #FF3F91, #5A213C
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicBubblegumTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 80% Pink, 15% Blue, 5% Accent
        //==========================================================================

        // ── Bubblegum Pink (80%) - main backgrounds ──────────────────
        const ImVec4 GumDeep    = ImVec4(0.84f, 0.35f, 0.56f, 1.00f);  // #D65A8F
        const ImVec4 GumPanel   = ImVec4(0.91f, 0.47f, 0.65f, 1.00f);  // #E977A6
        const ImVec4 GumDefault = ImVec4(0.98f, 0.58f, 0.73f, 1.00f);  // #F995BB
        const ImVec4 GumAlt     = ImVec4(0.99f, 0.72f, 0.82f, 1.00f);  // #FDB7D2
        const ImVec4 GumSurface = ImVec4(1.00f, 0.89f, 0.94f, 1.00f);  // #FFE4F0

        // ── Candy Blue (15%) - surfaces (glossy toy plastic) ──────────
        const ImVec4 BlueDark   = ImVec4(0.37f, 0.66f, 0.91f, 1.00f);  // #5EA9E8
        const ImVec4 BlueMid    = ImVec4(0.52f, 0.78f, 0.96f, 1.00f);  // #84C7F5
        const ImVec4 BlueLight  = ImVec4(0.72f, 0.91f, 1.00f, 1.00f);  // #B7E8FF

        // ── Hot Pink Accent (5%) - accent (#FF3F91) ────────────────────
        const ImVec4 Accent          = ImVec4(1.00f, 0.25f, 0.57f, 1.00f);  // #FF3F91
        const ImVec4 AccentDark      = ImVec4(0.85f, 0.18f, 0.47f, 1.00f);  // #D92F78
        const ImVec4 AccentDarker    = ImVec4(0.70f, 0.12f, 0.38f, 1.00f);  // #B31F61
        const ImVec4 AccentLight     = ImVec4(1.00f, 0.50f, 0.72f, 1.00f);  // #FF7FB8
        const ImVec4 AccentVeryLight = ImVec4(1.00f, 0.50f, 0.72f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 GumGlow         = ImVec4(1.00f, 0.25f, 0.57f, 0.25f);
        const ImVec4 GumVeryLight    = ImVec4(1.00f, 0.25f, 0.57f, 0.50f);
        const ImVec4 GumSubtle       = ImVec4(1.00f, 0.25f, 0.57f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.91f, 0.47f, 0.65f, 1.00f);

        // ── Text (Dark Burgundy - classic software) ──────────────────
        const ImVec4 TextPrimary     = ImVec4(0.35f, 0.13f, 0.24f, 1.00f);  // #5A213C
        const ImVec4 TextSecondary   = ImVec4(0.51f, 0.29f, 0.39f, 1.00f);  // #814A63
        const ImVec4 TextDisabled    = ImVec4(0.69f, 0.48f, 0.58f, 1.00f);  // #B07A95
        const ImVec4 TextWhite       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders (Thin glossy blue - Windows XP style) ──────────
        const ImVec4 BorderSubtle    = ImVec4(0.56f, 0.79f, 0.95f, 1.00f);  // #8EC9F2

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite      = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
        const ImVec4 GlossStrong     = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
        const ImVec4 BevelShadow     = ImVec4(0.48f, 0.22f, 0.33f, 0.35f);  // #7A3753
        const ImVec4 BevelBorder     = ImVec4(0.48f, 0.22f, 0.33f, 0.35f);

        //==========================================================================
        // Title Bar - Gradient from Blue to Pink (glossy toy plastic)
        //==========================================================================

        t.TitleBar.BackgroundColor           = ImVec4(0.37f, 0.66f, 0.91f, 1.00f);
        t.TitleBar.BackgroundColorActive     = ImVec4(0.37f, 0.66f, 0.91f, 1.00f);
        t.TitleBar.BackgroundColorInactive   = ImVec4(0.37f, 0.66f, 0.91f, 0.85f);
        t.TitleBar.BackgroundOpacity         = 1.0f;
        t.TitleBar.ShowBottomBorder          = true;
        t.TitleBar.BottomBorderColor         = BorderSubtle;
        t.TitleBar.ShowWindowBorder          = true;
        t.TitleBar.WindowBorderColor         = BlueMid;
        t.TitleBar.ShowAccentLine            = true;
        t.TitleBar.AccentLineColor           = AccentLight;
        t.TitleBar.TitleTextColor            = TextWhite;
        t.TitleBar.TitleTextColorInactive    = TextDisabled;

        // Gradient: Top = Candy Blue, Bottom = Bubblegum Pink
        t.TitleBar.UseTitleBarGradient       = true;
        t.TitleBar.TitleBarGradientTop       = ImVec4(0.52f, 0.78f, 0.96f, 1.00f);  // #84C7F5
        t.TitleBar.TitleBarGradientBottom    = ImVec4(0.84f, 0.35f, 0.56f, 1.00f);  // #D65A8F
        t.TitleBar.UseTitleBarGloss          = true;
        t.TitleBar.TitleBarGlossIntensity    = 0.45f;
        t.TitleBar.TitleBarGlossColor        = GlossStrong;
        t.TitleBar.UseTitleBarBevel          = true;
        t.TitleBar.TitleBarBevelThickness    = 1.5f;
        t.TitleBar.TitleBarBevelLight        = GlossStrong;
        t.TitleBar.TitleBarBevelDark         = BevelShadow;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive             = AccentLight;
        t.ContentPanel.TabInactive           = GumDefault;
        t.ContentPanel.TabHovered            = GumAlt;
        t.ContentPanel.TabRounding           = 6.0f;
        t.ContentPanel.TabText               = TextWhite;
        t.ContentPanel.TabTextInactive       = TextSecondary;
        t.ContentPanel.ButtonNormal          = BlueDark;
        t.ContentPanel.ButtonHovered         = BlueMid;
        t.ContentPanel.ButtonActive          = AccentDark;
        t.ContentPanel.ButtonRounding        = 8.0f;
        t.ContentPanel.BorderColor           = BorderSubtle;
        t.ContentPanel.BorderThickness       = 2.5f;
        t.ContentPanel.TabSpacing            = 4.0f;
        t.ContentPanel.HeaderSpacing         = 4.0f;

        t.ContentPanel.UseGlossyTabs         = true;
        t.ContentPanel.TabGlossIntensity     = 0.40f;
        t.ContentPanel.TabGlossHighlight     = GlossWhite;
        t.ContentPanel.UseGradientTabs       = true;
        t.ContentPanel.TabGradientTop        = GumDefault;
        t.ContentPanel.TabGradientBottom     = GumDeep;
        t.ContentPanel.UseTabBevel           = true;
        t.ContentPanel.TabBevelThickness     = 2.0f;
        t.ContentPanel.TabBevelLight         = GlossStrong;
        t.ContentPanel.TabBevelDark          = BevelShadow;
        t.ContentPanel.TabBevelBorderColor   = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                    = GumPanel;
        t.Window.ChildBg                     = GumDeep;
        t.Window.WindowBorder                = BorderSubtle;
        t.Window.TitleBar                    = GumDefault;
        t.Window.TitleBarActive              = GumAlt;
        t.Window.HeaderText                  = TextPrimary;
        t.Window.TextPrimary                 = TextPrimary;
        t.Window.TextSecondary               = TextSecondary;
        t.Window.TextDisabled                = TextDisabled;
        t.Window.BrandText                   = AccentLight;

        t.Window.ButtonNormal                = BlueDark;
        t.Window.ButtonHovered               = BlueMid;
        t.Window.ButtonActive                = AccentDark;
        t.Window.ButtonRounding              = 12.0f;
        t.Window.UseWindowGradient           = true;
        t.Window.WindowGradientTop           = GumDefault;
        t.Window.WindowGradientBottom        = GumDeep;
        t.Window.WindowOpacity               = 0.95f;
        t.Window.UseButtonGloss              = true;
        t.Window.ButtonGlossIntensity        = 0.60f;
        t.Window.ButtonGlossHighlight        = GlossStrong;
        t.Window.UseButtonBevel              = true;
        t.Window.ButtonBevelThickness        = 2.0f;
        t.Window.ButtonBevelLight            = GlossStrong;
        t.Window.ButtonBevelDark             = BevelShadow;
        t.Window.ChildBgOpacity              = 0.95f;
        t.Window.ProgressBar                 = AccentLight;
        t.Window.PlayingHighlight            = GumGlow;
        t.Window.SeparatorColor              = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground        = BlueDark;
        t.TrackTable.HeaderTextColor         = TextWhite;
        t.TrackTable.HeaderBorderColor       = BorderSubtle;
        t.TrackTable.HeaderHovered           = GumSurface;
        t.TrackTable.HeaderActive            = AccentLight;
        t.TrackTable.HeaderTextTitle         = TextWhite;
        t.TrackTable.HeaderTextArtist        = TextWhite;
        t.TrackTable.HeaderTextAlbum         = TextWhite;
        t.TrackTable.HeaderTextExtension     = TextWhite;
        t.TrackTable.HeaderTextDuration      = TextWhite;
        t.TrackTable.RowDefault              = GumDeep;
        t.TrackTable.RowDefaultAlt           = GumDefault;
        t.TrackTable.RowHovered              = GumVeryLight;
        t.TrackTable.RowClicked              = AccentDarker;
        t.TrackTable.RowSelected             = BlueDark;
        t.TrackTable.RowPlaying              = AccentLight;
        t.TrackTable.RowHeight               = 18.0f;
        t.TrackTable.RowPaddingX             = 4.0f;
        t.TrackTable.RowPaddingY             = 2.0f;
        t.TrackTable.TextColor               = TextPrimary;
        t.TrackTable.TextDim                 = TextDisabled;
        t.TrackTable.TextSelected            = TextWhite;
        t.TrackTable.TextPlaying             = TextWhite;
        t.TrackTable.RowTextTitle            = TextPrimary;
        t.TrackTable.RowTextArtist           = TextSecondary;
        t.TrackTable.RowTextAlbum            = TextSecondary;
        t.TrackTable.RowTextExtension        = TextDisabled;
        t.TrackTable.RowTextDuration         = TextSecondary;
        t.TrackTable.BorderColor             = BorderSubtle;
        t.TrackTable.BorderThickness         = 1.0f;
        t.TrackTable.ShowRowSeparators       = true;
        t.TrackTable.RowSeparatorColor       = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
        t.TrackTable.ScrollbarBg             = GumPanel;
        t.TrackTable.ScrollbarGrab           = BlueDark;
        t.TrackTable.ScrollbarGrabHovered    = BlueMid;
        t.TrackTable.ScrollbarGrabActive     = AccentLight;
        t.TrackTable.ScrollbarWidth          = 10.0f;
        t.TrackTable.ScrollbarRounding       = 8.0f;
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
        t.TrackTable.HeaderGlossIntensity    = 0.45f;
        t.TrackTable.HeaderGlossColor        = GlossStrong;
        t.TrackTable.UseHeaderGradient       = true;
        t.TrackTable.HeaderGradientTop       = BlueMid;
        t.TrackTable.HeaderGradientBottom    = BlueDark;
        t.TrackTable.UseGlossySelection      = true;
        t.TrackTable.SelectionGlossIntensity = 0.35f;
        t.TrackTable.UseRoundedScrollbar     = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.30f;

        //==========================================================================
        // Visualizer - Candy colored spectrum (Pink → Blue → Hot Pink)
        //==========================================================================

        t.Visualizer.BackgroundColor         = GumDeep;
        t.Visualizer.WaveformColor           = AccentLight;
        t.Visualizer.WaveformFillColor       = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.15f);
        t.Visualizer.GridColor               = ImVec4(BlueDark.x, BlueDark.y, BlueDark.z, 0.30f);
        t.Visualizer.BorderColor             = BorderSubtle;
        t.Visualizer.PlaceholderColor        = TextDisabled;
        t.Visualizer.UseColorRamp            = true;
        // Spectrum: Pink → Blue → Hot Pink (candy colors)
        t.Visualizer.SpectrumColorLow        = ImVec4(0.84f, 0.35f, 0.56f, 1.00f);  // #D65A8F
        t.Visualizer.SpectrumColorMid        = ImVec4(0.52f, 0.78f, 0.96f, 1.00f);  // #84C7F5
        t.Visualizer.SpectrumColorHigh       = ImVec4(1.00f, 0.25f, 0.57f, 1.00f);  // #FF3F91
        t.Visualizer.SpectrumColorPeak       = ImVec4(1.00f, 0.85f, 0.92f, 1.00f);  // #FFD9EB
        t.Visualizer.ColorRampLowThreshold   = 0.0f;
        t.Visualizer.ColorRampMidThreshold   = 0.45f;
        t.Visualizer.ColorRampHighThreshold  = 0.80f;
        t.Visualizer.UseFrequencyTint        = true;
        t.Visualizer.LowFreqTint             = ImVec4(0.84f, 0.35f, 0.56f, 1.00f);  // Pink for bass
        t.Visualizer.HighFreqTint            = ImVec4(1.00f, 0.25f, 0.57f, 1.00f);  // Hot Pink for treble
        t.Visualizer.FrequencyTintBlend      = 0.35f;
        t.Visualizer.BarBrightnessMin        = 0.60f;
        t.Visualizer.BarBrightnessMax        = 1.40f;
        t.Visualizer.UseGlossyBars           = true;
        t.Visualizer.BarGlossIntensity       = 0.50f;
        t.Visualizer.BarGlossColor           = GlossStrong;
        t.Visualizer.UseVisualizerGradient   = true;
        t.Visualizer.VisualizerGradientTop   = GumDefault;
        t.Visualizer.VisualizerGradientBottom = GumDeep;
        t.Visualizer.UseGlassEffect          = true;
        t.Visualizer.GlassOpacity            = 0.25f;
        t.Visualizer.UseGlossyWaveform       = true;
        t.Visualizer.WaveformGlossIntensity  = 0.35f;

        //==========================================================================
        // Album Art - Candy wrapper frame
        //==========================================================================

        t.AlbumArtBox.BorderColor            = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered     = AccentLight;
        t.AlbumArtBox.BorderColorClicked     = Accent;
        t.AlbumArtBox.BorderThickness        = 3.0f;
        t.AlbumArtBox.BorderThicknessHovered = 4.0f;
        t.AlbumArtBox.BorderRounding         = 6.0f;
        t.AlbumArtBox.BackgroundColor        = GumDefault;
        t.AlbumArtBox.BackgroundColorHovered = GumAlt;
        t.AlbumArtBox.ShowShadow             = true;
        t.AlbumArtBox.ShadowColor            = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor   = TextDisabled;
        t.AlbumArtBox.ShowHoverOverlay       = true;
        t.AlbumArtBox.HoverOverlayColor      = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.15f);
        t.AlbumArtBox.ClickOverlayColor      = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.25f);
        t.AlbumArtBox.ShowPlayButtonOnHover  = true;
        t.AlbumArtBox.PlayButtonColor        = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.UseGlossyOverlay       = true;
        t.AlbumArtBox.GlossyIntensity        = 0.40f;
        t.AlbumArtBox.GlossyHighlightColor   = GlossStrong;
        t.AlbumArtBox.UseInnerShadow         = true;
        t.AlbumArtBox.InnerShadowColor       = ImVec4(0.48f, 0.22f, 0.33f, 0.35f);
        t.AlbumArtBox.InnerShadowSize        = 5.0f;
        t.AlbumArtBox.UseReflection          = true;
        t.AlbumArtBox.ReflectionHeight       = 0.25f;
        t.AlbumArtBox.ReflectionOpacity      = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor      = ImVec4(0.35f, 0.13f, 0.24f, 0.95f);
        t.AlbumArtLightbox.BorderColor          = BlueDark;
        t.AlbumArtLightbox.CloseButtonColor     = TextSecondary;
        t.AlbumArtLightbox.CloseButtonHovered   = AccentLight;
        t.AlbumArtLightbox.TitleColor           = TextWhite;
        t.AlbumArtLightbox.ArtistColor          = TextSecondary;
        t.AlbumArtLightbox.MaxWidth             = 400.0f;
        t.AlbumArtLightbox.MaxHeight            = 400.0f;
        t.AlbumArtLightbox.BorderRounding       = 8.0f;
        t.AlbumArtLightbox.BorderThickness      = 1.0f;
        t.AlbumArtLightbox.CloseButtonSize      = 24.0f;
        t.AlbumArtLightbox.Padding              = 30.0f;
        t.AlbumArtLightbox.TitleSpacing         = 12.0f;
        t.AlbumArtLightbox.ArtistSpacing        = 8.0f;
        t.AlbumArtLightbox.UseLightboxGloss        = true;
        t.AlbumArtLightbox.LightboxGlossIntensity  = 0.35f;
        t.AlbumArtLightbox.LightboxGlossColor      = GlossStrong;
        t.AlbumArtLightbox.UseLightboxGradient     = true;
        t.AlbumArtLightbox.LightboxGradientTop     = ImVec4(0.40f, 0.18f, 0.28f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom  = ImVec4(0.28f, 0.10f, 0.20f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton    = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.45f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor              = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor          = SearchDropdownBg;
        t.SearchBar.borderColor              = BlueMid;
        t.SearchBar.textColor                = TextPrimary;
        t.SearchBar.highlightTextColor       = AccentLight;
        t.SearchBar.rowHoverColor            = GumAlt;
        t.SearchBar.separatorColor           = BorderSubtle;
        t.SearchBar.inputBgColor             = GumDefault;
        t.SearchBar.inputBorderColor         = BlueMid;
        t.SearchBar.inputTextColor           = TextPrimary;
        t.SearchBar.inputHintColor           = TextDisabled;
        t.SearchBar.UseSearchGloss           = true;
        t.SearchBar.SearchGlossIntensity     = 0.35f;
        t.SearchBar.SearchGlossColor         = GlossStrong;
        t.SearchBar.UseSearchGradient        = true;
        t.SearchBar.SearchGradientTop        = BlueMid;
        t.SearchBar.SearchGradientBottom     = GumDefault;
        t.SearchBar.UseRoundedInput          = true;
        t.SearchBar.InputRounding            = 12.0f;
        t.SearchBar.UseGlossyDropdown        = true;
        t.SearchBar.DropdownGlossIntensity   = 0.30f;

        //==========================================================================
        // Player Bar - Candy shop counter
        //==========================================================================

        t.PlayerBar.TextPrimary                 = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary               = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal                = GumDeep;
        t.PlayerBar.ButtonHovered               = BlueMid;
        t.PlayerBar.ButtonActive                = AccentDark;
        t.PlayerBar.ButtonPrimary               = GumDeep;
        t.PlayerBar.ButtonPrimaryHovered        = BlueMid;
        t.PlayerBar.ButtonPrimaryActive         = AccentDark;
        t.PlayerBar.SliderTrack                 = BorderSubtle;
        t.PlayerBar.SliderGrab                  = AccentLight;
        t.PlayerBar.SliderGrabActive            = Accent;
        t.PlayerBar.ButtonRounding              = 12.0f;
        t.PlayerBar.SliderRounding              = 8.0f;
        t.PlayerBar.UseButtonGloss              = true;
        t.PlayerBar.ButtonGlossIntensity        = 1.80f;
        t.PlayerBar.ButtonGlossHighlight        = GlossStrong;
        t.PlayerBar.UseButtonBevel              = true;
        t.PlayerBar.ButtonBevelThickness        = 1.4f;
        t.PlayerBar.ButtonBevelLight            = GlossStrong;
        t.PlayerBar.ButtonBevelDark             = BevelShadow;
        t.PlayerBar.ButtonBevelBorderColor      = BevelBorder;
        t.PlayerBar.UsePlayerBarGradient        = true;
        t.PlayerBar.PlayerBarGradientTop        = GumDefault;
        t.PlayerBar.PlayerBarGradientBottom     = GumDeep;
        t.PlayerBar.PlayerBarGradientRounding   = 12.0f;
        t.PlayerBar.PlayerBarOpacity            = 0.95f;
        t.PlayerBar.UsePlayerBarBevel           = true;
        t.PlayerBar.PlayerBarBevelThickness     = 2.5f;
        t.PlayerBar.PlayerBarBevelLight         = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark          = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor   = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient      = true;
        t.PlayerBar.SliderTrackGradientTop      = GumDefault;
        t.PlayerBar.SliderTrackGradientBottom   = GumDeep;
        t.PlayerBar.UseSliderGrabGloss          = true;
        t.PlayerBar.SliderGrabGlossIntensity    = 0.50f;
        t.PlayerBar.SliderGrabGlossHighlight    = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel          = true;
        t.PlayerBar.SliderGrabBevelThickness    = 1.5f;
        t.PlayerBar.SliderGrabBevelLight        = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark         = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor  = BevelBorder;
        t.PlayerBar.UseProgressGradient         = true;
        t.PlayerBar.ProgressTrackColor          = GumDeep;
        t.PlayerBar.ProgressFillColor           = AccentLight;
        t.PlayerBar.ProgressFillTop             = Accent;
        t.PlayerBar.ProgressFillBottom          = AccentDark;
        t.PlayerBar.ProgressHeight              = 12.0f;
        t.PlayerBar.ProgressRounding            = 8.0f;
        t.PlayerBar.ShowProgressGloss           = true;
        t.PlayerBar.ProgressGlossOpacity        = 0.40f;
        t.PlayerBar.Lightbox                    = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox                 = t.AlbumArtBox;
        t.PlayerBar.Visualizer                  = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor           = SearchDropdownBg;
        t.ContextMenu.BorderColor               = BlueMid;
        t.ContextMenu.TextColor                 = TextPrimary;
        t.ContextMenu.TextDisabledColor         = TextDisabled;
        t.ContextMenu.HoverColor                = AccentLight;
        t.ContextMenu.HoverTextColor            = TextWhite;
        t.ContextMenu.SeparatorColor            = BorderSubtle;
        t.ContextMenu.ShadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.ContextMenu.UseMenuGloss              = true;
        t.ContextMenu.MenuGlossIntensity        = 0.35f;
        t.ContextMenu.MenuGlossColor            = GlossStrong;
        t.ContextMenu.UseMenuGradient           = true;
        t.ContextMenu.MenuGradientTop           = BlueMid;
        t.ContextMenu.MenuGradientBottom        = GumDefault;
        t.ContextMenu.UseGlossySelection        = true;
        t.ContextMenu.SelectionGlossIntensity   = 0.40f;

        return t;
    }

} // namespace moosic