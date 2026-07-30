//==============================================================================
// ClassicRubyTheme.h
//==============================================================================
// Classic ruby/deep red theme with 3D glossy effects
// 3 base colors: Deep Ruby (80%), Medium Ruby (15%), Pink Accent (5%)
// Palette: #880E4F, #AD1457, #C2185B, #D81B60, #FF4081
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicRubyTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 80% Dark, 15% Medium, 5% Light
        //==========================================================================

        // ── Deep Ruby (80%) - main backgrounds (#880E4F, rgb(136,14,79)) ──
        const ImVec4 RubyDeep = ImVec4(0.40f, 0.05f, 0.25f, 1.00f);       // #660D3D
        const ImVec4 RubyPanel = ImVec4(0.45f, 0.06f, 0.28f, 1.00f);      // #730F47
        const ImVec4 RubyDefault = ImVec4(0.50f, 0.07f, 0.31f, 1.00f);    // #801250
        const ImVec4 RubyAlt = ImVec4(0.55f, 0.08f, 0.34f, 1.00f);        // #8D145A
        const ImVec4 RubySurface = ImVec4(0.60f, 0.09f, 0.37f, 1.00f);    // #9A1763
        const ImVec4 RubyDarker = ImVec4(0.33f, 0.03f, 0.20f, 1.00f);     // #540833

        // ── Medium Ruby (15%) - surfaces (#AD1457, rgb(173,20,87)) ──────
        const ImVec4 RubyDark = ImVec4(0.58f, 0.08f, 0.34f, 1.00f);      // #941457
        const ImVec4 RubyMid = ImVec4(0.65f, 0.10f, 0.38f, 1.00f);       // #A61A61
        const ImVec4 RubyLight = ImVec4(0.72f, 0.14f, 0.42f, 1.00f);     // #B8246B
        const ImVec4 RubyDarkerMid = ImVec4(0.50f, 0.06f, 0.28f, 1.00f); // #800F47

        // ── Pink (5%) - accent (#FF4081, rgb(255,64,129)) ──────────────
        const ImVec4 Accent = ImVec4(1.00f, 0.25f, 0.50f, 1.00f);        // #FF4081
        const ImVec4 AccentDark = ImVec4(0.80f, 0.15f, 0.40f, 1.00f);    // #CC2666
        const ImVec4 AccentDarker = ImVec4(0.60f, 0.10f, 0.30f, 1.00f);  // #991A4D
        const ImVec4 AccentLight = ImVec4(1.00f, 0.45f, 0.65f, 1.00f);   // #FF73A6
        const ImVec4 AccentVeryLight = ImVec4(1.00f, 0.45f, 0.65f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 RubyGlow = ImVec4(0.65f, 0.10f, 0.38f, 0.25f);
        const ImVec4 RubyVeryLight = ImVec4(0.65f, 0.10f, 0.38f, 0.50f);
        const ImVec4 RubySubtle = ImVec4(0.65f, 0.10f, 0.38f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.45f, 0.06f, 0.28f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright = ImVec4(1.00f, 0.90f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.80f, 0.50f, 0.65f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.60f, 0.35f, 0.50f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle = ImVec4(0.58f, 0.08f, 0.34f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        const ImVec4 GlossStrong = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        const ImVec4 BevelShadow = ImVec4(0.25f, 0.02f, 0.15f, 0.50f);
        const ImVec4 BevelBorder = ImVec4(0.45f, 0.05f, 0.25f, 0.65f);

        //==========================================================================
        // Title Bar - Gradient from dark to slightly lighter (top→bottom)
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.33f, 0.03f, 0.20f, 1.00f);
        t.TitleBar.BackgroundColorActive = ImVec4(0.33f, 0.03f, 0.20f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.33f, 0.03f, 0.20f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;
        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;
        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = RubyMid;
        t.TitleBar.ShowAccentLine = true;
        t.TitleBar.AccentLineColor = AccentLight;
        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        t.TitleBar.UseTitleBarGradient = true;
        t.TitleBar.TitleBarGradientTop = ImVec4(0.30f, 0.02f, 0.18f, 1.00f);
        t.TitleBar.TitleBarGradientBottom = ImVec4(0.40f, 0.05f, 0.25f, 1.00f);
        t.TitleBar.UseTitleBarGloss = true;
        t.TitleBar.TitleBarGlossIntensity = 0.35f;
        t.TitleBar.TitleBarGlossColor = GlossStrong;
        t.TitleBar.UseTitleBarBevel = true;
        t.TitleBar.TitleBarBevelThickness = 1.5f;
        t.TitleBar.TitleBarBevelLight = GlossStrong;
        t.TitleBar.TitleBarBevelDark = BevelShadow;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = AccentLight;
        t.ContentPanel.TabInactive = RubyDefault;
        t.ContentPanel.TabHovered = RubyAlt;
        t.ContentPanel.TabRounding = 4.0f;
        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;
        t.ContentPanel.ButtonNormal = RubyDark;
        t.ContentPanel.ButtonHovered = RubyMid;
        t.ContentPanel.ButtonActive = AccentDark;
        t.ContentPanel.ButtonRounding = 2.0f;
        t.ContentPanel.BorderColor = RubyMid;
        t.ContentPanel.BorderThickness = 2.5f;
        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        t.ContentPanel.UseGlossyTabs = true;
        t.ContentPanel.TabGlossIntensity = 0.35f;
        t.ContentPanel.TabGlossHighlight = GlossWhite;
        t.ContentPanel.UseGradientTabs = true;
        t.ContentPanel.TabGradientTop = RubyDefault;
        t.ContentPanel.TabGradientBottom = RubyDarker;
        t.ContentPanel.UseTabBevel = true;
        t.ContentPanel.TabBevelThickness = 2.0f;
        t.ContentPanel.TabBevelLight = GlossStrong;
        t.ContentPanel.TabBevelDark = BevelShadow;
        t.ContentPanel.TabBevelBorderColor = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = RubyPanel;
        t.Window.ChildBg = RubyDarker;
        t.Window.WindowBorder = BorderSubtle;
        t.Window.TitleBar = RubyDefault;
        t.Window.TitleBarActive = RubyAlt;
        t.Window.HeaderText = TextBright;
        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;
        t.Window.BrandText = AccentLight;

        t.Window.ButtonNormal = RubyDark;
        t.Window.ButtonHovered = RubyMid;
        t.Window.ButtonActive = AccentDark;
        t.Window.ButtonRounding = 8.0f;
        t.Window.UseWindowGradient = true;
        t.Window.WindowGradientTop = RubyDefault;
        t.Window.WindowGradientBottom = RubyDarker;
        t.Window.WindowOpacity = 0.95f;
        t.Window.UseButtonGloss = true;
        t.Window.ButtonGlossIntensity = 0.50f;
        t.Window.ButtonGlossHighlight = GlossStrong;
        t.Window.UseButtonBevel = true;
        t.Window.ButtonBevelThickness = 2.0f;
        t.Window.ButtonBevelLight = GlossStrong;
        t.Window.ButtonBevelDark = BevelShadow;
        t.Window.ChildBgOpacity = 0.95f;
        t.Window.ProgressBar = AccentLight;
        t.Window.PlayingHighlight = RubyGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground = RubyDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = RubySurface;
        t.TrackTable.HeaderActive = AccentLight;
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;
        t.TrackTable.RowDefault = RubyDarker;
        t.TrackTable.RowDefaultAlt = RubyDefault;
        t.TrackTable.RowHovered = RubyVeryLight;
        t.TrackTable.RowClicked = AccentDarker;
        t.TrackTable.RowSelected = RubyDark;
        t.TrackTable.RowPlaying = AccentLight;
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;
        t.TrackTable.TextColor = TextBright;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextWhite;
        t.TrackTable.TextPlaying = TextWhite;
        t.TrackTable.RowTextTitle = TextBright;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;
        t.TrackTable.BorderColor = BorderSubtle;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.30f);
        t.TrackTable.ScrollbarBg = RubyPanel;
        t.TrackTable.ScrollbarGrab = RubyDark;
        t.TrackTable.ScrollbarGrabHovered = RubyMid;
        t.TrackTable.ScrollbarGrabActive = AccentLight;
        t.TrackTable.ScrollbarWidth = 8.0f;
        t.TrackTable.ScrollbarRounding = 4.0f;
        t.TrackTable.HoverFadeSpeed = 0.15f;
        t.TrackTable.SelectionFadeSpeed = 0.20f;
        t.TrackTable.ScrollSmoothing = 0.12f;
        t.TrackTable.TableRounding = 0.0f;
        t.TrackTable.MinColumnWidth = 30.0f;
        t.TrackTable.TitleWidth = 350.0f;
        t.TrackTable.ArtistWidth = 180.0f;
        t.TrackTable.AlbumWidth = 180.0f;
        t.TrackTable.ExtensionWidth = 50.0f;
        t.TrackTable.DurationWidth = 80.0f;

        t.TrackTable.UseGlossyHeader = true;
        t.TrackTable.HeaderGlossIntensity = 0.40f;
        t.TrackTable.HeaderGlossColor = GlossStrong;
        t.TrackTable.UseHeaderGradient = true;
        t.TrackTable.HeaderGradientTop = RubyMid;
        t.TrackTable.HeaderGradientBottom = RubyDark;
        t.TrackTable.UseGlossySelection = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = RubyDarker;
        t.Visualizer.WaveformColor = AccentLight;
        t.Visualizer.WaveformFillColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.15f);
        t.Visualizer.GridColor = ImVec4(RubyDark.x, RubyDark.y, RubyDark.z, 0.30f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = RubyDark;
        t.Visualizer.SpectrumColorMid = RubyMid;
        t.Visualizer.SpectrumColorHigh = AccentLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(1.00f, 0.50f, 0.70f, 1.00f);
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = RubyDark;
        t.Visualizer.HighFreqTint = AccentLight;
        t.Visualizer.FrequencyTintBlend = 0.30f;
        t.Visualizer.BarBrightnessMin = 0.55f;
        t.Visualizer.BarBrightnessMax = 1.30f;
        t.Visualizer.UseGlossyBars = true;
        t.Visualizer.BarGlossIntensity = 0.40f;
        t.Visualizer.BarGlossColor = GlossStrong;
        t.Visualizer.UseVisualizerGradient = true;
        t.Visualizer.VisualizerGradientTop = RubyDefault;
        t.Visualizer.VisualizerGradientBottom = RubyDarker;
        t.Visualizer.UseGlassEffect = true;
        t.Visualizer.GlassOpacity = 0.20f;
        t.Visualizer.UseGlossyWaveform = true;
        t.Visualizer.WaveformGlossIntensity = 0.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = AccentLight;
        t.AlbumArtBox.BorderColorClicked = Accent;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;
        t.AlbumArtBox.BackgroundColor = RubyDefault;
        t.AlbumArtBox.BackgroundColorHovered = RubyAlt;
        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.AlbumArtBox.PlaceholderTextColor = TextDim;
        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.12f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.22f);
        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
        t.AlbumArtBox.UseGlossyOverlay = true;
        t.AlbumArtBox.GlossyIntensity = 0.35f;
        t.AlbumArtBox.GlossyHighlightColor = GlossStrong;
        t.AlbumArtBox.UseInnerShadow = true;
        t.AlbumArtBox.InnerShadowColor = ImVec4(0.25f, 0.02f, 0.15f, 0.40f);
        t.AlbumArtBox.InnerShadowSize = 5.0f;
        t.AlbumArtBox.UseReflection = true;
        t.AlbumArtBox.ReflectionHeight = 0.25f;
        t.AlbumArtBox.ReflectionOpacity = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.30f, 0.03f, 0.18f, 0.95f);
        t.AlbumArtLightbox.BorderColor = RubyDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = AccentLight;
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
        t.AlbumArtLightbox.UseLightboxGloss = true;
        t.AlbumArtLightbox.LightboxGlossIntensity = 0.30f;
        t.AlbumArtLightbox.LightboxGlossColor = GlossStrong;
        t.AlbumArtLightbox.UseLightboxGradient = true;
        t.AlbumArtLightbox.LightboxGradientTop = ImVec4(0.35f, 0.04f, 0.22f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom = ImVec4(0.22f, 0.02f, 0.14f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = RubyMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = AccentLight;
        t.SearchBar.rowHoverColor = RubyAlt;
        t.SearchBar.separatorColor = BorderSubtle;
        t.SearchBar.inputBgColor = RubyDefault;
        t.SearchBar.inputBorderColor = RubyMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;
        t.SearchBar.UseSearchGloss = true;
        t.SearchBar.SearchGlossIntensity = 0.30f;
        t.SearchBar.SearchGlossColor = ImVec4(GlossStrong.x, GlossStrong.y, GlossStrong.z, 0.2f);
        t.SearchBar.UseSearchGradient = true;
        t.SearchBar.SearchGradientTop = RubyMid;
        t.SearchBar.SearchGradientBottom = RubyDefault;
        t.SearchBar.UseRoundedInput = true;
        t.SearchBar.InputRounding = 8.0f;
        t.SearchBar.UseGlossyDropdown = true;
        t.SearchBar.DropdownGlossIntensity = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal = RubyDark;
        t.PlayerBar.ButtonHovered = RubyMid;
        t.PlayerBar.ButtonActive = AccentDark;
        t.PlayerBar.ButtonPrimary = AccentLight;
        t.PlayerBar.ButtonPrimaryHovered = Accent;
        t.PlayerBar.ButtonPrimaryActive = AccentDark;
        t.PlayerBar.SliderTrack = BorderSubtle;
        t.PlayerBar.SliderGrab = AccentLight;
        t.PlayerBar.SliderGrabActive = Accent;
        t.PlayerBar.ButtonRounding = 8.0f;
        t.PlayerBar.SliderRounding = 4.0f;
        t.PlayerBar.UseButtonGloss = true;
        t.PlayerBar.ButtonGlossIntensity = 0.50f;
        t.PlayerBar.ButtonGlossHighlight = GlossStrong;
        t.PlayerBar.UseButtonBevel = true;
        t.PlayerBar.ButtonBevelThickness = 2.0f;
        t.PlayerBar.ButtonBevelLight = GlossStrong;
        t.PlayerBar.ButtonBevelDark = BevelShadow;
        t.PlayerBar.ButtonBevelBorderColor = BevelBorder;
        t.PlayerBar.UsePlayerBarGradient = true;
        t.PlayerBar.PlayerBarGradientTop = RubyDefault;
        t.PlayerBar.PlayerBarGradientBottom = RubyDarker;
        t.PlayerBar.PlayerBarGradientRounding = 8.0f;
        t.PlayerBar.PlayerBarOpacity = 0.95f;
        t.PlayerBar.UsePlayerBarBevel = true;
        t.PlayerBar.PlayerBarBevelThickness = 2.5f;
        t.PlayerBar.PlayerBarBevelLight = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient = true;
        t.PlayerBar.SliderTrackGradientTop = RubyDefault;
        t.PlayerBar.SliderTrackGradientBottom = RubyDarker;
        t.PlayerBar.UseSliderGrabGloss = true;
        t.PlayerBar.SliderGrabGlossIntensity = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel = true;
        t.PlayerBar.SliderGrabBevelThickness = 1.5f;
        t.PlayerBar.SliderGrabBevelLight = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor = BevelBorder;
        t.PlayerBar.UseProgressGradient = true;
        t.PlayerBar.ProgressTrackColor = RubyDarker;
        t.PlayerBar.ProgressFillColor = AccentLight;
        t.PlayerBar.ProgressFillTop = Accent;
        t.PlayerBar.ProgressFillBottom = AccentDark;
        t.PlayerBar.ProgressHeight = 10.0f;
        t.PlayerBar.ProgressRounding = 5.0f;
        t.PlayerBar.ShowProgressGloss = true;
        t.PlayerBar.ProgressGlossOpacity = 0.35f;
        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = RubyMid;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = AccentLight;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = BorderSubtle;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.ContextMenu.UseMenuGloss = true;
        t.ContextMenu.MenuGlossIntensity = 0.30f;
        t.ContextMenu.MenuGlossColor = GlossStrong;
        t.ContextMenu.UseMenuGradient = true;
        t.ContextMenu.MenuGradientTop = RubyMid;
        t.ContextMenu.MenuGradientBottom = RubyDefault;
        t.ContextMenu.UseGlossySelection = true;
        t.ContextMenu.SelectionGlossIntensity = 0.35f;

        return t;
    }

} // namespace moosic