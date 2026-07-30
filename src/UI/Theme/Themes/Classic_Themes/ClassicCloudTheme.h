//==============================================================================
// ClassicCloudTheme.h
//==============================================================================
// Classic cloud/soft gray theme with 3D glossy effects
// 3 base colors: Cloud Gray (60%), Medium Gray (30%), Steel Blue Accent (10%)
// Palette: #ECEFF1, #B0BEC5, #90A4AE, #78909C, #607D8B
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicCloudTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 60% Light, 30% Medium, 10% Accent
        //==========================================================================

        // ── Cloud Gray (60%) - main backgrounds (#ECEFF1, rgb(236,239,241)) ──
        const ImVec4 CloudDeep    = ImVec4(0.88f, 0.90f, 0.92f, 1.00f);  // #E0E6E8
        const ImVec4 CloudPanel   = ImVec4(0.90f, 0.92f, 0.94f, 1.00f);  // #E8EBED
        const ImVec4 CloudDefault = ImVec4(0.93f, 0.94f, 0.95f, 1.00f);  // #ECEFF1
        const ImVec4 CloudAlt     = ImVec4(0.95f, 0.96f, 0.97f, 1.00f);  // #F2F4F6
        const ImVec4 CloudSurface = ImVec4(0.97f, 0.98f, 0.98f, 1.00f);  // #F7F8FA

        // ── Medium Gray (30%) - surfaces (#B0BEC5, rgb(176,190,197)) ──
        const ImVec4 GrayDark   = ImVec4(0.60f, 0.70f, 0.75f, 1.00f);  // #99B3B8
        const ImVec4 GrayMid    = ImVec4(0.69f, 0.75f, 0.77f, 1.00f);  // #B0BEC5
        const ImVec4 GrayLight  = ImVec4(0.78f, 0.82f, 0.84f, 1.00f);  // #C7D1D6
        const ImVec4 GrayDarker = ImVec4(0.52f, 0.62f, 0.68f, 1.00f);  // #859EA6

        // ── Steel Blue (10%) - accent (#607D8B, rgb(96,125,139)) ──────────
        const ImVec4 Accent          = ImVec4(0.38f, 0.49f, 0.55f, 1.00f);  // #607D8B
        const ImVec4 AccentDark      = ImVec4(0.30f, 0.40f, 0.45f, 1.00f);  // #4D6670
        const ImVec4 AccentDarker    = ImVec4(0.22f, 0.30f, 0.35f, 1.00f);  // #384D55
        const ImVec4 AccentLight     = ImVec4(0.50f, 0.60f, 0.65f, 1.00f);  // #8099A6
        const ImVec4 AccentVeryLight = ImVec4(0.50f, 0.60f, 0.65f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 CloudGlow         = ImVec4(0.38f, 0.49f, 0.55f, 0.25f);
        const ImVec4 CloudVeryLight    = ImVec4(0.38f, 0.49f, 0.55f, 0.50f);
        const ImVec4 CloudSubtle       = ImVec4(0.38f, 0.49f, 0.55f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.90f, 0.92f, 0.94f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright      = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
        const ImVec4 TextMuted       = ImVec4(0.40f, 0.48f, 0.52f, 1.00f);
        const ImVec4 TextDim         = ImVec4(0.55f, 0.62f, 0.65f, 1.00f);
        const ImVec4 TextWhite       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle    = ImVec4(0.60f, 0.70f, 0.75f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite      = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 GlossStrong     = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 BevelShadow     = ImVec4(0.25f, 0.30f, 0.35f, 0.50f);
        const ImVec4 BevelBorder     = ImVec4(0.45f, 0.50f, 0.55f, 0.65f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor           = ImVec4(0.25f, 0.30f, 0.35f, 1.00f);
        t.TitleBar.BackgroundColorActive     = ImVec4(0.25f, 0.30f, 0.35f, 1.00f);
        t.TitleBar.BackgroundColorInactive   = ImVec4(0.25f, 0.30f, 0.35f, 0.85f);
        t.TitleBar.BackgroundOpacity         = 1.0f;
        t.TitleBar.ShowBottomBorder          = true;
        t.TitleBar.BottomBorderColor         = BorderSubtle;
        t.TitleBar.ShowWindowBorder          = true;
        t.TitleBar.WindowBorderColor         = GrayMid;
        t.TitleBar.ShowAccentLine            = true;
        t.TitleBar.AccentLineColor           = Accent;
        t.TitleBar.TitleTextColor            = TextWhite;
        t.TitleBar.TitleTextColorInactive    = TextDim;

        t.TitleBar.UseTitleBarGradient       = true;
        t.TitleBar.TitleBarGradientTop       = ImVec4(0.30f, 0.35f, 0.40f, 1.00f);
        t.TitleBar.TitleBarGradientBottom    = ImVec4(0.20f, 0.25f, 0.30f, 1.00f);
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
        t.ContentPanel.TabInactive           = CloudDefault;
        t.ContentPanel.TabHovered            = CloudAlt;
        t.ContentPanel.TabRounding           = 4.0f;
        t.ContentPanel.TabText               = TextWhite;
        t.ContentPanel.TabTextInactive       = TextMuted;
        t.ContentPanel.ButtonNormal          = GrayDark;
        t.ContentPanel.ButtonHovered         = GrayMid;
        t.ContentPanel.ButtonActive          = AccentDark;
        t.ContentPanel.ButtonRounding        = 2.0f;
        t.ContentPanel.BorderColor           = GrayMid;
        t.ContentPanel.BorderThickness       = 2.5f;
        t.ContentPanel.TabSpacing            = 4.0f;
        t.ContentPanel.HeaderSpacing         = 4.0f;

        t.ContentPanel.UseGlossyTabs         = true;
        t.ContentPanel.TabGlossIntensity     = 0.35f;
        t.ContentPanel.TabGlossHighlight     = GlossWhite;
        t.ContentPanel.UseGradientTabs       = true;
        t.ContentPanel.TabGradientTop        = CloudDefault;
        t.ContentPanel.TabGradientBottom     = GrayDark;
        t.ContentPanel.UseTabBevel           = true;
        t.ContentPanel.TabBevelThickness     = 2.0f;
        t.ContentPanel.TabBevelLight         = GlossStrong;
        t.ContentPanel.TabBevelDark          = BevelShadow;
        t.ContentPanel.TabBevelBorderColor   = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                    = CloudPanel;
        t.Window.ChildBg                     = CloudDeep;
        t.Window.WindowBorder                = BorderSubtle;
        t.Window.TitleBar                    = CloudDefault;
        t.Window.TitleBarActive              = CloudAlt;
        t.Window.HeaderText                  = TextBright;
        t.Window.TextPrimary                 = TextBright;
        t.Window.TextSecondary               = TextMuted;
        t.Window.TextDisabled                = TextDim;
        t.Window.BrandText                   = Accent;

        t.Window.ButtonNormal                = GrayDark;
        t.Window.ButtonHovered               = GrayMid;
        t.Window.ButtonActive                = AccentDark;
        t.Window.ButtonRounding              = 8.0f;
        t.Window.UseWindowGradient           = true;
        t.Window.WindowGradientTop           = CloudDefault;
        t.Window.WindowGradientBottom        = CloudDeep;
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
        t.Window.PlayingHighlight            = CloudGlow;
        t.Window.SeparatorColor              = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground        = GrayDark;
        t.TrackTable.HeaderTextColor         = TextWhite;
        t.TrackTable.HeaderBorderColor       = BorderSubtle;
        t.TrackTable.HeaderHovered           = CloudSurface;
        t.TrackTable.HeaderActive            = Accent;
        t.TrackTable.HeaderTextTitle         = TextWhite;
        t.TrackTable.HeaderTextArtist        = TextWhite;
        t.TrackTable.HeaderTextAlbum         = TextWhite;
        t.TrackTable.HeaderTextExtension     = TextWhite;
        t.TrackTable.HeaderTextDuration      = TextWhite;
        t.TrackTable.RowDefault              = CloudDeep;
        t.TrackTable.RowDefaultAlt           = CloudDefault;
        t.TrackTable.RowHovered              = CloudVeryLight;
        t.TrackTable.RowClicked              = AccentDarker;
        t.TrackTable.RowSelected             = GrayDark;
        t.TrackTable.RowPlaying              = Accent;
        t.TrackTable.RowHeight               = 18.0f;
        t.TrackTable.RowPaddingX             = 4.0f;
        t.TrackTable.RowPaddingY             = 2.0f;
        t.TrackTable.TextColor               = TextBright;
        t.TrackTable.TextDim                 = TextDim;
        t.TrackTable.TextSelected            = TextWhite;
        t.TrackTable.TextPlaying             = TextWhite;
        t.TrackTable.RowTextTitle            = TextBright;
        t.TrackTable.RowTextArtist           = TextMuted;
        t.TrackTable.RowTextAlbum            = TextMuted;
        t.TrackTable.RowTextExtension        = TextDim;
        t.TrackTable.RowTextDuration         = TextMuted;
        t.TrackTable.BorderColor             = BorderSubtle;
        t.TrackTable.BorderThickness         = 1.0f;
        t.TrackTable.ShowRowSeparators       = true;
        t.TrackTable.RowSeparatorColor       = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
        t.TrackTable.ScrollbarBg             = CloudPanel;
        t.TrackTable.ScrollbarGrab           = GrayDark;
        t.TrackTable.ScrollbarGrabHovered    = GrayMid;
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
        t.TrackTable.HeaderGradientTop       = GrayMid;
        t.TrackTable.HeaderGradientBottom    = GrayDark;
        t.TrackTable.UseGlossySelection      = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar     = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor         = CloudDeep;
        t.Visualizer.WaveformColor           = Accent;
        t.Visualizer.WaveformFillColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.15f);
        t.Visualizer.GridColor               = ImVec4(GrayDark.x, GrayDark.y, GrayDark.z, 0.30f);
        t.Visualizer.BorderColor             = BorderSubtle;
        t.Visualizer.PlaceholderColor        = TextDim;
        t.Visualizer.UseColorRamp            = true;
        t.Visualizer.SpectrumColorLow        = GrayDark;
        t.Visualizer.SpectrumColorMid        = GrayMid;
        t.Visualizer.SpectrumColorHigh       = AccentLight;
        t.Visualizer.SpectrumColorPeak       = ImVec4(0.50f, 0.60f, 0.65f, 1.00f);
        t.Visualizer.ColorRampLowThreshold   = 0.0f;
        t.Visualizer.ColorRampMidThreshold   = 0.45f;
        t.Visualizer.ColorRampHighThreshold  = 0.80f;
        t.Visualizer.UseFrequencyTint        = true;
        t.Visualizer.LowFreqTint             = GrayDark;
        t.Visualizer.HighFreqTint            = Accent;
        t.Visualizer.FrequencyTintBlend      = 0.30f;
        t.Visualizer.BarBrightnessMin        = 0.55f;
        t.Visualizer.BarBrightnessMax        = 1.30f;
        t.Visualizer.UseGlossyBars           = true;
        t.Visualizer.BarGlossIntensity       = 0.40f;
        t.Visualizer.BarGlossColor           = GlossStrong;
        t.Visualizer.UseVisualizerGradient   = true;
        t.Visualizer.VisualizerGradientTop   = CloudDefault;
        t.Visualizer.VisualizerGradientBottom = GrayDark;
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
        t.AlbumArtBox.BackgroundColor        = CloudDefault;
        t.AlbumArtBox.BackgroundColorHovered = CloudAlt;
        t.AlbumArtBox.ShowShadow             = true;
        t.AlbumArtBox.ShadowColor            = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor   = TextDim;
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
        t.AlbumArtBox.InnerShadowColor       = ImVec4(0.25f, 0.30f, 0.35f, 0.40f);
        t.AlbumArtBox.InnerShadowSize        = 5.0f;
        t.AlbumArtBox.UseReflection          = true;
        t.AlbumArtBox.ReflectionHeight       = 0.25f;
        t.AlbumArtBox.ReflectionOpacity      = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor      = ImVec4(0.20f, 0.25f, 0.30f, 0.95f);
        t.AlbumArtLightbox.BorderColor          = GrayDark;
        t.AlbumArtLightbox.CloseButtonColor     = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered   = Accent;
        t.AlbumArtLightbox.TitleColor           = TextWhite;
        t.AlbumArtLightbox.ArtistColor          = TextMuted;
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
        t.AlbumArtLightbox.LightboxGradientTop     = ImVec4(0.24f, 0.28f, 0.34f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom  = ImVec4(0.16f, 0.20f, 0.25f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton    = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor              = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor          = SearchDropdownBg;
        t.SearchBar.borderColor              = GrayMid;
        t.SearchBar.textColor                = TextBright;
        t.SearchBar.highlightTextColor       = Accent;
        t.SearchBar.rowHoverColor            = CloudAlt;
        t.SearchBar.separatorColor           = BorderSubtle;
        t.SearchBar.inputBgColor             = CloudDefault;
        t.SearchBar.inputBorderColor         = GrayMid;
        t.SearchBar.inputTextColor           = TextBright;
        t.SearchBar.inputHintColor           = TextDim;
        t.SearchBar.UseSearchGloss           = true;
        t.SearchBar.SearchGlossIntensity     = 0.30f;
        t.SearchBar.SearchGlossColor         = GlossStrong;
        t.SearchBar.UseSearchGradient        = true;
        t.SearchBar.SearchGradientTop        = GrayMid;
        t.SearchBar.SearchGradientBottom     = CloudDefault;
        t.SearchBar.UseRoundedInput          = true;
        t.SearchBar.InputRounding            = 8.0f;
        t.SearchBar.UseGlossyDropdown        = true;
        t.SearchBar.DropdownGlossIntensity   = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary                 = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary               = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal                = CloudDeep;
        t.PlayerBar.ButtonHovered               = GrayMid;
        t.PlayerBar.ButtonActive                = AccentDark;
        t.PlayerBar.ButtonPrimary               = CloudDeep;
        t.PlayerBar.ButtonPrimaryHovered        = GrayMid;
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
        t.PlayerBar.PlayerBarGradientTop        = CloudDefault;
        t.PlayerBar.PlayerBarGradientBottom     = GrayDark;
        t.PlayerBar.PlayerBarGradientRounding   = 8.0f;
        t.PlayerBar.PlayerBarOpacity            = 0.95f;
        t.PlayerBar.UsePlayerBarBevel           = true;
        t.PlayerBar.PlayerBarBevelThickness     = 2.5f;
        t.PlayerBar.PlayerBarBevelLight         = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark          = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor   = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient      = true;
        t.PlayerBar.SliderTrackGradientTop      = CloudDefault;
        t.PlayerBar.SliderTrackGradientBottom   = GrayDark;
        t.PlayerBar.UseSliderGrabGloss          = true;
        t.PlayerBar.SliderGrabGlossIntensity    = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight    = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel          = true;
        t.PlayerBar.SliderGrabBevelThickness    = 1.5f;
        t.PlayerBar.SliderGrabBevelLight        = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark         = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor  = BevelBorder;
        t.PlayerBar.UseProgressGradient         = true;
        t.PlayerBar.ProgressTrackColor          = CloudDeep;
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
        t.ContextMenu.BorderColor               = GrayMid;
        t.ContextMenu.TextColor                 = TextBright;
        t.ContextMenu.TextDisabledColor         = TextDim;
        t.ContextMenu.HoverColor                = Accent;
        t.ContextMenu.HoverTextColor            = TextWhite;
        t.ContextMenu.SeparatorColor            = BorderSubtle;
        t.ContextMenu.ShadowColor               = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.ContextMenu.UseMenuGloss              = true;
        t.ContextMenu.MenuGlossIntensity        = 0.30f;
        t.ContextMenu.MenuGlossColor            = GlossStrong;
        t.ContextMenu.UseMenuGradient           = true;
        t.ContextMenu.MenuGradientTop           = GrayMid;
        t.ContextMenu.MenuGradientBottom        = CloudDefault;
        t.ContextMenu.UseGlossySelection        = true;
        t.ContextMenu.SelectionGlossIntensity   = 0.35f;

        return t;
    }

} // namespace moosic