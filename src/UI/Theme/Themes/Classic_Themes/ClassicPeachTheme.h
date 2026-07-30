//==============================================================================
// ClassicPeachTheme.h
//==============================================================================
// Classic peach/warm orange-pink theme with 3D glossy effects
// 3 base colors: Peach (60%), Soft Peach (30%), Coral Accent (10%)
// Palette: #FBE9E7, #FFCCBC, #FFAB91, #FF8A65, #FF7043
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicPeachTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 60% Light, 30% Medium, 10% Accent
        //==========================================================================

        // ── Peach (60%) - main backgrounds (#FBE9E7, rgb(251,233,231)) ──
        const ImVec4 PeachDeep    = ImVec4(0.94f, 0.88f, 0.86f, 1.00f);  // #F0E0DE
        const ImVec4 PeachPanel   = ImVec4(0.96f, 0.90f, 0.88f, 1.00f);  // #F5E6E0
        const ImVec4 PeachDefault = ImVec4(0.98f, 0.92f, 0.90f, 1.00f);  // #FBE9E7
        const ImVec4 PeachAlt     = ImVec4(0.99f, 0.94f, 0.92f, 1.00f);  // #FCF0EE
        const ImVec4 PeachSurface = ImVec4(1.00f, 0.96f, 0.94f, 1.00f);  // #FFF5F0

        // ── Soft Peach (30%) - surfaces (#FFCCBC, rgb(255,204,188)) ──
        const ImVec4 CoralDark   = ImVec4(0.92f, 0.74f, 0.68f, 1.00f);  // #EBBDAD
        const ImVec4 CoralMid    = ImVec4(0.96f, 0.80f, 0.74f, 1.00f);  // #F5CCBC
        const ImVec4 CoralLight  = ImVec4(0.98f, 0.86f, 0.80f, 1.00f);  // #FADBCD
        const ImVec4 CoralDarker = ImVec4(0.86f, 0.68f, 0.60f, 1.00f);  // #DCAE99

        // ── Coral (10%) - accent (#FF7043, rgb(255,112,67)) ──────────
        const ImVec4 Accent          = ImVec4(1.00f, 0.44f, 0.26f, 1.00f);  // #FF7043
        const ImVec4 AccentDark      = ImVec4(0.85f, 0.35f, 0.20f, 1.00f);  // #D95933
        const ImVec4 AccentDarker    = ImVec4(0.68f, 0.26f, 0.14f, 1.00f);  // #AE4224
        const ImVec4 AccentLight     = ImVec4(1.00f, 0.56f, 0.42f, 1.00f);  // #FF8F6B
        const ImVec4 AccentVeryLight = ImVec4(1.00f, 0.56f, 0.42f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 PeachGlow         = ImVec4(1.00f, 0.44f, 0.26f, 0.25f);
        const ImVec4 PeachVeryLight    = ImVec4(1.00f, 0.44f, 0.26f, 0.50f);
        const ImVec4 PeachSubtle       = ImVec4(1.00f, 0.44f, 0.26f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.96f, 0.90f, 0.88f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright      = ImVec4(0.35f, 0.15f, 0.10f, 1.00f);
        const ImVec4 TextMuted       = ImVec4(0.55f, 0.35f, 0.25f, 1.00f);
        const ImVec4 TextDim         = ImVec4(0.70f, 0.50f, 0.40f, 1.00f);
        const ImVec4 TextWhite       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle    = ImVec4(0.92f, 0.74f, 0.68f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite      = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 GlossStrong     = ImVec4(1.00f, 1.00f, 1.00f, 0.20f);
        const ImVec4 BevelShadow     = ImVec4(0.50f, 0.30f, 0.20f, 0.50f);
        const ImVec4 BevelBorder     = ImVec4(0.70f, 0.50f, 0.40f, 0.65f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor           = ImVec4(0.70f, 0.28f, 0.18f, 1.00f);
        t.TitleBar.BackgroundColorActive     = ImVec4(0.70f, 0.28f, 0.18f, 1.00f);
        t.TitleBar.BackgroundColorInactive   = ImVec4(0.70f, 0.28f, 0.18f, 0.85f);
        t.TitleBar.BackgroundOpacity         = 1.0f;
        t.TitleBar.ShowBottomBorder          = true;
        t.TitleBar.BottomBorderColor         = BorderSubtle;
        t.TitleBar.ShowWindowBorder          = true;
        t.TitleBar.WindowBorderColor         = CoralMid;
        t.TitleBar.ShowAccentLine            = true;
        t.TitleBar.AccentLineColor           = Accent;
        t.TitleBar.TitleTextColor            = TextWhite;
        t.TitleBar.TitleTextColorInactive    = TextDim;

        t.TitleBar.UseTitleBarGradient       = true;
        t.TitleBar.TitleBarGradientTop       = ImVec4(0.76f, 0.32f, 0.22f, 1.00f);
        t.TitleBar.TitleBarGradientBottom    = ImVec4(0.60f, 0.22f, 0.14f, 1.00f);
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
        t.ContentPanel.TabInactive           = PeachDefault;
        t.ContentPanel.TabHovered            = PeachAlt;
        t.ContentPanel.TabRounding           = 4.0f;
        t.ContentPanel.TabText               = TextWhite;
        t.ContentPanel.TabTextInactive       = TextMuted;
        t.ContentPanel.ButtonNormal          = CoralDark;
        t.ContentPanel.ButtonHovered         = CoralMid;
        t.ContentPanel.ButtonActive          = AccentDark;
        t.ContentPanel.ButtonRounding        = 2.0f;
        t.ContentPanel.BorderColor           = CoralMid;
        t.ContentPanel.BorderThickness       = 2.5f;
        t.ContentPanel.TabSpacing            = 4.0f;
        t.ContentPanel.HeaderSpacing         = 4.0f;

        t.ContentPanel.UseGlossyTabs         = true;
        t.ContentPanel.TabGlossIntensity     = 0.35f;
        t.ContentPanel.TabGlossHighlight     = GlossWhite;
        t.ContentPanel.UseGradientTabs       = true;
        t.ContentPanel.TabGradientTop        = PeachDefault;
        t.ContentPanel.TabGradientBottom     = CoralDark;
        t.ContentPanel.UseTabBevel           = true;
        t.ContentPanel.TabBevelThickness     = 2.0f;
        t.ContentPanel.TabBevelLight         = GlossStrong;
        t.ContentPanel.TabBevelDark          = BevelShadow;
        t.ContentPanel.TabBevelBorderColor   = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg                    = PeachPanel;
        t.Window.ChildBg                     = PeachDeep;
        t.Window.WindowBorder                = BorderSubtle;
        t.Window.TitleBar                    = PeachDefault;
        t.Window.TitleBarActive              = PeachAlt;
        t.Window.HeaderText                  = TextBright;
        t.Window.TextPrimary                 = TextBright;
        t.Window.TextSecondary               = TextMuted;
        t.Window.TextDisabled                = TextDim;
        t.Window.BrandText                   = Accent;

        t.Window.ButtonNormal                = CoralDark;
        t.Window.ButtonHovered               = CoralMid;
        t.Window.ButtonActive                = AccentDark;
        t.Window.ButtonRounding              = 8.0f;
        t.Window.UseWindowGradient           = true;
        t.Window.WindowGradientTop           = PeachDefault;
        t.Window.WindowGradientBottom        = PeachDeep;
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
        t.Window.PlayingHighlight            = PeachGlow;
        t.Window.SeparatorColor              = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground        = CoralDark;
        t.TrackTable.HeaderTextColor         = TextWhite;
        t.TrackTable.HeaderBorderColor       = BorderSubtle;
        t.TrackTable.HeaderHovered           = PeachSurface;
        t.TrackTable.HeaderActive            = Accent;
        t.TrackTable.HeaderTextTitle         = TextWhite;
        t.TrackTable.HeaderTextArtist        = TextWhite;
        t.TrackTable.HeaderTextAlbum         = TextWhite;
        t.TrackTable.HeaderTextExtension     = TextWhite;
        t.TrackTable.HeaderTextDuration      = TextWhite;
        t.TrackTable.RowDefault              = PeachDeep;
        t.TrackTable.RowDefaultAlt           = PeachDefault;
        t.TrackTable.RowHovered              = PeachVeryLight;
        t.TrackTable.RowClicked              = AccentDarker;
        t.TrackTable.RowSelected             = CoralDark;
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
        t.TrackTable.ScrollbarBg             = PeachPanel;
        t.TrackTable.ScrollbarGrab           = CoralDark;
        t.TrackTable.ScrollbarGrabHovered    = CoralMid;
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
        t.TrackTable.HeaderGradientTop       = CoralMid;
        t.TrackTable.HeaderGradientBottom    = CoralDark;
        t.TrackTable.UseGlossySelection      = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar     = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor         = PeachDeep;
        t.Visualizer.WaveformColor           = Accent;
        t.Visualizer.WaveformFillColor       = ImVec4(Accent.x, Accent.y, Accent.z, 0.15f);
        t.Visualizer.GridColor               = ImVec4(CoralDark.x, CoralDark.y, CoralDark.z, 0.30f);
        t.Visualizer.BorderColor             = BorderSubtle;
        t.Visualizer.PlaceholderColor        = TextDim;
        t.Visualizer.UseColorRamp            = true;
        t.Visualizer.SpectrumColorLow        = CoralDark;
        t.Visualizer.SpectrumColorMid        = CoralMid;
        t.Visualizer.SpectrumColorHigh       = AccentLight;
        t.Visualizer.SpectrumColorPeak       = ImVec4(1.00f, 0.60f, 0.40f, 1.00f);
        t.Visualizer.ColorRampLowThreshold   = 0.0f;
        t.Visualizer.ColorRampMidThreshold   = 0.45f;
        t.Visualizer.ColorRampHighThreshold  = 0.80f;
        t.Visualizer.UseFrequencyTint        = true;
        t.Visualizer.LowFreqTint             = CoralDark;
        t.Visualizer.HighFreqTint            = Accent;
        t.Visualizer.FrequencyTintBlend      = 0.30f;
        t.Visualizer.BarBrightnessMin        = 0.55f;
        t.Visualizer.BarBrightnessMax        = 1.30f;
        t.Visualizer.UseGlossyBars           = true;
        t.Visualizer.BarGlossIntensity       = 0.40f;
        t.Visualizer.BarGlossColor           = GlossStrong;
        t.Visualizer.UseVisualizerGradient   = true;
        t.Visualizer.VisualizerGradientTop   = PeachDefault;
        t.Visualizer.VisualizerGradientBottom = CoralDark;
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
        t.AlbumArtBox.BackgroundColor        = PeachDefault;
        t.AlbumArtBox.BackgroundColorHovered = PeachAlt;
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
        t.AlbumArtBox.InnerShadowColor       = ImVec4(0.50f, 0.30f, 0.20f, 0.40f);
        t.AlbumArtBox.InnerShadowSize        = 5.0f;
        t.AlbumArtBox.UseReflection          = true;
        t.AlbumArtBox.ReflectionHeight       = 0.25f;
        t.AlbumArtBox.ReflectionOpacity      = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor      = ImVec4(0.60f, 0.22f, 0.14f, 0.95f);
        t.AlbumArtLightbox.BorderColor          = CoralDark;
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
        t.AlbumArtLightbox.LightboxGradientTop     = ImVec4(0.64f, 0.26f, 0.18f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom  = ImVec4(0.50f, 0.18f, 0.10f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton    = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor              = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor          = SearchDropdownBg;
        t.SearchBar.borderColor              = CoralMid;
        t.SearchBar.textColor                = TextBright;
        t.SearchBar.highlightTextColor       = Accent;
        t.SearchBar.rowHoverColor            = PeachAlt;
        t.SearchBar.separatorColor           = BorderSubtle;
        t.SearchBar.inputBgColor             = PeachDefault;
        t.SearchBar.inputBorderColor         = CoralMid;
        t.SearchBar.inputTextColor           = TextBright;
        t.SearchBar.inputHintColor           = TextDim;
        t.SearchBar.UseSearchGloss           = true;
        t.SearchBar.SearchGlossIntensity     = 0.30f;
        t.SearchBar.SearchGlossColor         = GlossStrong;
        t.SearchBar.UseSearchGradient        = true;
        t.SearchBar.SearchGradientTop        = CoralMid;
        t.SearchBar.SearchGradientBottom     = PeachDefault;
        t.SearchBar.UseRoundedInput          = true;
        t.SearchBar.InputRounding            = 8.0f;
        t.SearchBar.UseGlossyDropdown        = true;
        t.SearchBar.DropdownGlossIntensity   = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary                 = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary               = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal                = PeachDeep;
        t.PlayerBar.ButtonHovered               = CoralMid;
        t.PlayerBar.ButtonActive                = AccentDark;
        t.PlayerBar.ButtonPrimary               = PeachDeep;
        t.PlayerBar.ButtonPrimaryHovered        = CoralMid;
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
        t.PlayerBar.PlayerBarGradientTop        = PeachDefault;
        t.PlayerBar.PlayerBarGradientBottom     = CoralDark;
        t.PlayerBar.PlayerBarGradientRounding   = 8.0f;
        t.PlayerBar.PlayerBarOpacity            = 0.95f;
        t.PlayerBar.UsePlayerBarBevel           = true;
        t.PlayerBar.PlayerBarBevelThickness     = 2.5f;
        t.PlayerBar.PlayerBarBevelLight         = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark          = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor   = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient      = true;
        t.PlayerBar.SliderTrackGradientTop      = PeachDefault;
        t.PlayerBar.SliderTrackGradientBottom   = CoralDark;
        t.PlayerBar.UseSliderGrabGloss          = true;
        t.PlayerBar.SliderGrabGlossIntensity    = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight    = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel          = true;
        t.PlayerBar.SliderGrabBevelThickness    = 1.5f;
        t.PlayerBar.SliderGrabBevelLight        = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark         = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor  = BevelBorder;
        t.PlayerBar.UseProgressGradient         = true;
        t.PlayerBar.ProgressTrackColor          = PeachDeep;
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
        t.ContextMenu.BorderColor               = CoralMid;
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
        t.ContextMenu.MenuGradientTop           = CoralMid;
        t.ContextMenu.MenuGradientBottom        = PeachDefault;
        t.ContextMenu.UseGlossySelection        = true;
        t.ContextMenu.SelectionGlossIntensity   = 0.35f;

        return t;
    }

} // namespace moosic