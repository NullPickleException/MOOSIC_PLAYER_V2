//==============================================================================
// ClassicMintTheme.h
//==============================================================================
// Classic mint/fresh green theme with 3D glossy effects
// 3 base colors: Mint (60%), Soft Green (30%), Fresh Green Accent (10%)
// Palette: #E8F5E9, #C8E6C9, #A5D6A7, #81C784, #66BB6A
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicMintTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 60% Light, 30% Medium, 10% Accent
        //==========================================================================

        // ── Mint (60%) - main backgrounds (#E8F5E9, rgb(232,245,233)) ──
        const ImVec4 MintDeep    = ImVec4(0.88f, 0.94f, 0.89f, 1.00f);  // #E0F0E1
        const ImVec4 MintPanel   = ImVec4(0.90f, 0.95f, 0.91f, 1.00f);  // #E6F2E8
        const ImVec4 MintDefault = ImVec4(0.91f, 0.96f, 0.92f, 1.00f);  // #E8F5E9
        const ImVec4 MintAlt     = ImVec4(0.93f, 0.97f, 0.94f, 1.00f);  // #EDF7EE
        const ImVec4 MintSurface = ImVec4(0.95f, 0.98f, 0.95f, 1.00f);  // #F2FAF3

        // ── Soft Green (30%) - surfaces (#C8E6C9, rgb(200,230,201)) ──
        const ImVec4 GreenDark   = ImVec4(0.72f, 0.88f, 0.73f, 1.00f);  // #B8E0B9
        const ImVec4 GreenMid    = ImVec4(0.78f, 0.90f, 0.79f, 1.00f);  // #C8E6C9
        const ImVec4 GreenLight  = ImVec4(0.84f, 0.93f, 0.85f, 1.00f);  // #D6EDD7
        const ImVec4 GreenDarker = ImVec4(0.66f, 0.84f, 0.67f, 1.00f);  // #A8D7A9

        // ── Fresh Green (10%) - accent (#66BB6A, rgb(102,187,106)) ──
        const ImVec4 Accent          = ImVec4(0.40f, 0.73f, 0.42f, 1.00f);  // #66BB6A
        const ImVec4 AccentDark      = ImVec4(0.32f, 0.62f, 0.34f, 1.00f);  // #529E56
        const ImVec4 AccentDarker    = ImVec4(0.24f, 0.50f, 0.26f, 1.00f);  // #3D8041
        const ImVec4 AccentLight     = ImVec4(0.54f, 0.82f, 0.56f, 1.00f);  // #8AD18E
        const ImVec4 AccentVeryLight = ImVec4(0.54f, 0.82f, 0.56f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 MintGlow         = ImVec4(0.40f, 0.73f, 0.42f, 0.25f);
        const ImVec4 MintVeryLight    = ImVec4(0.40f, 0.73f, 0.42f, 0.50f);
        const ImVec4 MintSubtle       = ImVec4(0.40f, 0.73f, 0.42f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.90f, 0.95f, 0.91f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright      = ImVec4(0.20f, 0.40f, 0.20f, 1.00f);
        const ImVec4 TextMuted       = ImVec4(0.40f, 0.55f, 0.40f, 1.00f);
        const ImVec4 TextDim         = ImVec4(0.55f, 0.65f, 0.55f, 1.00f);
        const ImVec4 TextWhite       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle    = ImVec4(0.72f, 0.88f, 0.73f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite      = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 GlossStrong     = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 BevelShadow     = ImVec4(0.30f, 0.50f, 0.30f, 0.50f);
        const ImVec4 BevelBorder     = ImVec4(0.50f, 0.70f, 0.50f, 0.65f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor           = ImVec4(0.20f, 0.50f, 0.30f, 1.00f);
        t.TitleBar.BackgroundColorActive     = ImVec4(0.20f, 0.50f, 0.30f, 1.00f);
        t.TitleBar.BackgroundColorInactive   = ImVec4(0.20f, 0.50f, 0.30f, 0.85f);
        t.TitleBar.BackgroundOpacity         = 1.0f;
        t.TitleBar.ShowBottomBorder          = true;
        t.TitleBar.BottomBorderColor         = BorderSubtle;
        t.TitleBar.ShowWindowBorder          = true;
        t.TitleBar.WindowBorderColor         = GreenMid;
        t.TitleBar.ShowAccentLine            = true;
        t.TitleBar.AccentLineColor           = Accent;
        t.TitleBar.TitleTextColor            = TextWhite;
        t.TitleBar.TitleTextColorInactive    = TextDim;

        t.TitleBar.UseTitleBarGradient       = true;
        t.TitleBar.TitleBarGradientTop       = ImVec4(0.28f, 0.55f, 0.35f, 1.00f);
        t.TitleBar.TitleBarGradientBottom    = ImVec4(0.16f, 0.42f, 0.24f, 1.00f);
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
        t.ContentPanel.TabInactive           = MintDefault;
        t.ContentPanel.TabHovered            = MintAlt;
        t.ContentPanel.TabRounding           = 4.0f;
        t.ContentPanel.TabText               = TextWhite;
        t.ContentPanel.TabTextInactive       = TextMuted;
        t.ContentPanel.ButtonNormal          = GreenDark;
        t.ContentPanel.ButtonHovered         = GreenMid;
        t.ContentPanel.ButtonActive          = AccentDark;
        t.ContentPanel.ButtonRounding        = 2.0f;
        t.ContentPanel.BorderColor           = GreenMid;
        t.ContentPanel.BorderThickness       = 2.5f;
        t.ContentPanel.TabSpacing            = 4.0f;
        t.ContentPanel.HeaderSpacing         = 4.0f;

        t.ContentPanel.UseGlossyTabs         = true;
        t.ContentPanel.TabGlossIntensity     = 0.35f;
        t.ContentPanel.TabGlossHighlight     = GlossWhite;
        t.ContentPanel.UseGradientTabs       = true;
        t.ContentPanel.TabGradientTop        = MintDefault;
        t.ContentPanel.TabGradientBottom     = GreenDark;
        t.ContentPanel.UseTabBevel           = true;
        t.ContentPanel.TabBevelThickness     = 2.0f;
        t.ContentPanel.TabBevelLight         = GlossStrong;
        t.ContentPanel.TabBevelDark          = BevelShadow;
        t.ContentPanel.TabBevelBorderColor   = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                    = MintPanel;
        t.Window.ChildBg                     = MintDeep;
        t.Window.WindowBorder                = BorderSubtle;
        t.Window.TitleBar                    = MintDefault;
        t.Window.TitleBarActive              = MintAlt;
        t.Window.HeaderText                  = TextBright;
        t.Window.TextPrimary                 = TextBright;
        t.Window.TextSecondary               = TextMuted;
        t.Window.TextDisabled                = TextDim;
        t.Window.BrandText                   = Accent;

        t.Window.ButtonNormal                = GreenDark;
        t.Window.ButtonHovered               = GreenMid;
        t.Window.ButtonActive                = AccentDark;
        t.Window.ButtonRounding              = 8.0f;
        t.Window.UseWindowGradient           = true;
        t.Window.WindowGradientTop           = MintDefault;
        t.Window.WindowGradientBottom        = MintDeep;
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
        t.Window.PlayingHighlight            = MintGlow;
        t.Window.SeparatorColor              = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground        = GreenDark;
        t.TrackTable.HeaderTextColor         = TextWhite;
        t.TrackTable.HeaderBorderColor       = BorderSubtle;
        t.TrackTable.HeaderHovered           = MintSurface;
        t.TrackTable.HeaderActive            = Accent;
        t.TrackTable.HeaderTextTitle         = TextWhite;
        t.TrackTable.HeaderTextArtist        = TextWhite;
        t.TrackTable.HeaderTextAlbum         = TextWhite;
        t.TrackTable.HeaderTextExtension     = TextWhite;
        t.TrackTable.HeaderTextDuration      = TextWhite;
        t.TrackTable.RowDefault              = MintDeep;
        t.TrackTable.RowDefaultAlt           = MintDefault;
        t.TrackTable.RowHovered              = MintVeryLight;
        t.TrackTable.RowClicked              = AccentDarker;
        t.TrackTable.RowSelected             = GreenDark;
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
        t.TrackTable.ScrollbarBg             = MintPanel;
        t.TrackTable.ScrollbarGrab           = GreenDark;
        t.TrackTable.ScrollbarGrabHovered    = GreenMid;
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
        t.TrackTable.HeaderGradientTop       = GreenMid;
        t.TrackTable.HeaderGradientBottom    = GreenDark;
        t.TrackTable.UseGlossySelection      = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar     = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor         = MintDeep;
        t.Visualizer.WaveformColor           = Accent;
        t.Visualizer.WaveformFillColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.15f);
        t.Visualizer.GridColor               = ImVec4(GreenDark.x, GreenDark.y, GreenDark.z, 0.30f);
        t.Visualizer.BorderColor             = BorderSubtle;
        t.Visualizer.PlaceholderColor        = TextDim;
        t.Visualizer.UseColorRamp            = true;
        t.Visualizer.SpectrumColorLow        = GreenDark;
        t.Visualizer.SpectrumColorMid        = GreenMid;
        t.Visualizer.SpectrumColorHigh       = AccentLight;
        t.Visualizer.SpectrumColorPeak       = ImVec4(0.60f, 0.85f, 0.60f, 1.00f);
        t.Visualizer.ColorRampLowThreshold   = 0.0f;
        t.Visualizer.ColorRampMidThreshold   = 0.45f;
        t.Visualizer.ColorRampHighThreshold  = 0.80f;
        t.Visualizer.UseFrequencyTint        = true;
        t.Visualizer.LowFreqTint             = GreenDark;
        t.Visualizer.HighFreqTint            = Accent;
        t.Visualizer.FrequencyTintBlend      = 0.30f;
        t.Visualizer.BarBrightnessMin        = 0.55f;
        t.Visualizer.BarBrightnessMax        = 1.30f;
        t.Visualizer.UseGlossyBars           = true;
        t.Visualizer.BarGlossIntensity       = 0.40f;
        t.Visualizer.BarGlossColor           = GlossStrong;
        t.Visualizer.UseVisualizerGradient   = true;
        t.Visualizer.VisualizerGradientTop   = MintDefault;
        t.Visualizer.VisualizerGradientBottom = GreenDark;
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
        t.AlbumArtBox.BackgroundColor        = MintDefault;
        t.AlbumArtBox.BackgroundColorHovered = MintAlt;
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
        t.AlbumArtBox.InnerShadowColor       = ImVec4(0.30f, 0.50f, 0.30f, 0.40f);
        t.AlbumArtBox.InnerShadowSize        = 5.0f;
        t.AlbumArtBox.UseReflection          = true;
        t.AlbumArtBox.ReflectionHeight       = 0.25f;
        t.AlbumArtBox.ReflectionOpacity      = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor      = ImVec4(0.18f, 0.42f, 0.24f, 0.95f);
        t.AlbumArtLightbox.BorderColor          = GreenDark;
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
        t.AlbumArtLightbox.LightboxGradientTop     = ImVec4(0.22f, 0.48f, 0.28f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom  = ImVec4(0.14f, 0.36f, 0.18f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton    = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor              = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor          = SearchDropdownBg;
        t.SearchBar.borderColor              = GreenMid;
        t.SearchBar.textColor                = TextBright;
        t.SearchBar.highlightTextColor       = Accent;
        t.SearchBar.rowHoverColor            = MintAlt;
        t.SearchBar.separatorColor           = BorderSubtle;
        t.SearchBar.inputBgColor             = MintDefault;
        t.SearchBar.inputBorderColor         = GreenMid;
        t.SearchBar.inputTextColor           = TextBright;
        t.SearchBar.inputHintColor           = TextDim;
        t.SearchBar.UseSearchGloss           = true;
        t.SearchBar.SearchGlossIntensity     = 0.30f;
        t.SearchBar.SearchGlossColor         = GlossStrong;
        t.SearchBar.UseSearchGradient        = true;
        t.SearchBar.SearchGradientTop        = GreenMid;
        t.SearchBar.SearchGradientBottom     = MintDefault;
        t.SearchBar.UseRoundedInput          = true;
        t.SearchBar.InputRounding            = 8.0f;
        t.SearchBar.UseGlossyDropdown        = true;
        t.SearchBar.DropdownGlossIntensity   = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary                 = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary               = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal                = MintDeep;
        t.PlayerBar.ButtonHovered               = GreenMid;
        t.PlayerBar.ButtonActive                = AccentDark;
        t.PlayerBar.ButtonPrimary               = MintDeep;
        t.PlayerBar.ButtonPrimaryHovered        = GreenMid;
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
        t.PlayerBar.PlayerBarGradientTop        = MintDefault;
        t.PlayerBar.PlayerBarGradientBottom     = GreenDark;
        t.PlayerBar.PlayerBarGradientRounding   = 8.0f;
        t.PlayerBar.PlayerBarOpacity            = 0.95f;
        t.PlayerBar.UsePlayerBarBevel           = true;
        t.PlayerBar.PlayerBarBevelThickness     = 2.5f;
        t.PlayerBar.PlayerBarBevelLight         = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark          = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor   = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient      = true;
        t.PlayerBar.SliderTrackGradientTop      = MintDefault;
        t.PlayerBar.SliderTrackGradientBottom   = GreenDark;
        t.PlayerBar.UseSliderGrabGloss          = true;
        t.PlayerBar.SliderGrabGlossIntensity    = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight    = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel          = true;
        t.PlayerBar.SliderGrabBevelThickness    = 1.5f;
        t.PlayerBar.SliderGrabBevelLight        = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark         = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor  = BevelBorder;
        t.PlayerBar.UseProgressGradient         = true;
        t.PlayerBar.ProgressTrackColor          = MintDeep;
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
        t.ContextMenu.BorderColor               = GreenMid;
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
        t.ContextMenu.MenuGradientTop           = GreenMid;
        t.ContextMenu.MenuGradientBottom        = MintDefault;
        t.ContextMenu.UseGlossySelection        = true;
        t.ContextMenu.SelectionGlossIntensity   = 0.35f;

        return t;
    }

} // namespace moosic