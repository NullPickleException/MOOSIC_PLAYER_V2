//==============================================================================
// ClassicBlueTheme.h
//==============================================================================
// Classic blue theme with 3D glossy effects - Dark dominant palette
// 3 base colors: Deep Blue (80%), Medium Blue (15%), Light Blue Accent (5%)
// Palette: #0D47A1, #1565C0, #1976D2, #1E88E5, #42A5F5
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicBlueTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 80% Dark, 15% Medium, 5% Light
        //==========================================================================

        // ── Deep Blue (80%) - main backgrounds (#0D47A1, rgb(13,71,161)) ──
        const ImVec4 DeepBlue = ImVec4(0.05f, 0.28f, 0.63f, 1.00f);       // #0D47A1
        const ImVec4 DeepBluePanel = ImVec4(0.07f, 0.30f, 0.65f, 1.00f);  // #124DA6
        const ImVec4 DeepBlueDefault = ImVec4(0.08f, 0.33f, 0.68f, 1.00f); // #1554AE
        const ImVec4 DeepBlueAlt = ImVec4(0.10f, 0.36f, 0.72f, 1.00f);    // #1A5CB8
        const ImVec4 DeepBlueSurface = ImVec4(0.12f, 0.40f, 0.75f, 1.00f); // #1E66C0
        const ImVec4 DeepBlueDarker = ImVec4(0.03f, 0.20f, 0.50f, 1.00f); // #083380

        // ── Medium Blue (15%) - surfaces (#1565C0, rgb(21,101,192)) ──────
        const ImVec4 BlueDark = ImVec4(0.08f, 0.40f, 0.75f, 1.00f);      // #1466C0
        const ImVec4 BlueMid = ImVec4(0.12f, 0.45f, 0.80f, 1.00f);       // #1F73CC
        const ImVec4 BlueLight = ImVec4(0.20f, 0.55f, 0.85f, 1.00f);     // #338CD9
        const ImVec4 BlueDarker = ImVec4(0.05f, 0.32f, 0.62f, 1.00f);    // #0D529E

        // ── Light Blue (5%) - accent (#1E88E5 / #42A5F5, rgb(30,136,229)) ──
        const ImVec4 Accent = ImVec4(0.12f, 0.53f, 0.90f, 1.00f);        // #1E88E5
        const ImVec4 AccentDark = ImVec4(0.08f, 0.40f, 0.75f, 1.00f);    // #1466C0
        const ImVec4 AccentDarker = ImVec4(0.05f, 0.30f, 0.60f, 1.00f);  // #0D4D99
        const ImVec4 AccentLight = ImVec4(0.26f, 0.65f, 0.96f, 1.00f);   // #42A5F5
        const ImVec4 AccentVeryLight = ImVec4(0.26f, 0.65f, 0.96f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 BlueGlow = ImVec4(0.12f, 0.45f, 0.80f, 0.25f);
        const ImVec4 BlueVeryLight = ImVec4(0.12f, 0.45f, 0.80f, 0.50f);
        const ImVec4 BlueSubtle = ImVec4(0.12f, 0.45f, 0.80f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.07f, 0.30f, 0.65f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright = ImVec4(0.95f, 0.97f, 1.00f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.50f, 0.75f, 0.95f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.30f, 0.50f, 0.80f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle = ImVec4(0.08f, 0.40f, 0.75f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        const ImVec4 GlossStrong = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        const ImVec4 BevelShadow = ImVec4(0.02f, 0.10f, 0.25f, 0.50f);
        const ImVec4 BevelBorder = ImVec4(0.05f, 0.30f, 0.60f, 0.65f);

        //==========================================================================
        // Title Bar - Gradient from dark to slightly lighter (top→bottom)
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.03f, 0.20f, 0.50f, 1.00f);
        t.TitleBar.BackgroundColorActive = ImVec4(0.03f, 0.20f, 0.50f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.03f, 0.20f, 0.50f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;
        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;
        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = BlueMid;
        t.TitleBar.ShowAccentLine = true;
        t.TitleBar.AccentLineColor = AccentLight;
        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        // Title bar with subtle gradient (darker at top, lighter at bottom)
        t.TitleBar.UseTitleBarGradient = true;
        t.TitleBar.TitleBarGradientTop = ImVec4(0.03f, 0.18f, 0.45f, 1.00f);
        t.TitleBar.TitleBarGradientBottom = ImVec4(0.07f, 0.28f, 0.60f, 1.00f);
        t.TitleBar.UseTitleBarGloss = true;
        t.TitleBar.TitleBarGlossIntensity = 0.35f;
        t.TitleBar.TitleBarGlossColor = GlossStrong;
        t.TitleBar.UseTitleBarBevel = true;
        t.TitleBar.TitleBarBevelThickness = 1.5f;
        t.TitleBar.TitleBarBevelLight = GlossStrong;
        t.TitleBar.TitleBarBevelDark = BevelShadow;

        //==========================================================================
        // Content Panel - Dark with subtle gradient
        //==========================================================================

        t.ContentPanel.TabActive = AccentLight;
        t.ContentPanel.TabInactive = DeepBlueDefault;
        t.ContentPanel.TabHovered = DeepBlueAlt;
        t.ContentPanel.TabRounding = 4.0f;
        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;
        t.ContentPanel.ButtonNormal = BlueDark;
        t.ContentPanel.ButtonHovered = BlueMid;
        t.ContentPanel.ButtonActive = AccentDark;
        t.ContentPanel.ButtonRounding = 2.0f;
        t.ContentPanel.BorderColor = BlueMid;
        t.ContentPanel.BorderThickness = 2.5f;
        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        t.ContentPanel.UseGlossyTabs = true;
        t.ContentPanel.TabGlossIntensity = 0.35f;
        t.ContentPanel.TabGlossHighlight = GlossWhite;
        t.ContentPanel.UseGradientTabs = true;
        t.ContentPanel.TabGradientTop = DeepBlueDefault;
        t.ContentPanel.TabGradientBottom = DeepBlueDarker;
        t.ContentPanel.UseTabBevel = true;
        t.ContentPanel.TabBevelThickness = 2.0f;
        t.ContentPanel.TabBevelLight = GlossStrong;
        t.ContentPanel.TabBevelDark = BevelShadow;
        t.ContentPanel.TabBevelBorderColor = BevelBorder;

        //==========================================================================
        // Window - Deep dark blues throughout
        //==========================================================================

        t.Window.WindowBg = DeepBluePanel;
        t.Window.ChildBg = DeepBlueDarker;
        t.Window.WindowBorder = BorderSubtle;
        t.Window.TitleBar = DeepBlueDefault;
        t.Window.TitleBarActive = DeepBlueAlt;
        t.Window.HeaderText = TextBright;
        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;
        t.Window.BrandText = AccentLight;

        t.Window.ButtonNormal = BlueDark;
        t.Window.ButtonHovered = BlueMid;
        t.Window.ButtonActive = AccentDark;
        t.Window.ButtonRounding = 8.0f;
        t.Window.UseWindowGradient = true;
        t.Window.WindowGradientTop = DeepBlueDefault;
        t.Window.WindowGradientBottom = DeepBlueDarker;
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
        t.Window.PlayingHighlight = BlueGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table - Dark rows with subtle alternation
        //==========================================================================

        t.TrackTable.HeaderBackground = BlueDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = DeepBlueSurface;
        t.TrackTable.HeaderActive = AccentLight;
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;
        t.TrackTable.RowDefault = DeepBlueDarker;
        t.TrackTable.RowDefaultAlt = DeepBlueDefault;
        t.TrackTable.RowHovered = BlueVeryLight;
        t.TrackTable.RowClicked = AccentDarker;
        t.TrackTable.RowSelected = BlueDark;
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
        t.TrackTable.ScrollbarBg = DeepBluePanel;
        t.TrackTable.ScrollbarGrab = BlueDark;
        t.TrackTable.ScrollbarGrabHovered = BlueMid;
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
        t.TrackTable.HeaderGradientTop = BlueMid;
        t.TrackTable.HeaderGradientBottom = BlueDark;
        t.TrackTable.UseGlossySelection = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer - Dark background with bright accents
        //==========================================================================

        t.Visualizer.BackgroundColor = DeepBlueDarker;
        t.Visualizer.WaveformColor = AccentLight;
        t.Visualizer.WaveformFillColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.15f);
        t.Visualizer.GridColor = ImVec4(BlueDark.x, BlueDark.y, BlueDark.z, 0.30f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = BlueDark;
        t.Visualizer.SpectrumColorMid = BlueMid;
        t.Visualizer.SpectrumColorHigh = AccentLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.60f, 0.85f, 1.00f, 1.00f);
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = BlueDark;
        t.Visualizer.HighFreqTint = AccentLight;
        t.Visualizer.FrequencyTintBlend = 0.30f;
        t.Visualizer.BarBrightnessMin = 0.55f;
        t.Visualizer.BarBrightnessMax = 1.30f;
        t.Visualizer.UseGlossyBars = true;
        t.Visualizer.BarGlossIntensity = 0.40f;
        t.Visualizer.BarGlossColor = GlossStrong;
        t.Visualizer.UseVisualizerGradient = true;
        t.Visualizer.VisualizerGradientTop = DeepBlueDefault;
        t.Visualizer.VisualizerGradientBottom = DeepBlueDarker;
        t.Visualizer.UseGlassEffect = true;
        t.Visualizer.GlassOpacity = 0.20f;
        t.Visualizer.UseGlossyWaveform = true;
        t.Visualizer.WaveformGlossIntensity = 0.30f;

        //==========================================================================
        // Album Art - Clean dark frame
        //==========================================================================

        t.AlbumArtBox.BorderColor = BorderSubtle;
        t.AlbumArtBox.BorderColorHovered = AccentLight;
        t.AlbumArtBox.BorderColorClicked = Accent;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;
        t.AlbumArtBox.BackgroundColor = DeepBlueDefault;
        t.AlbumArtBox.BackgroundColorHovered = DeepBlueAlt;
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
        t.AlbumArtBox.InnerShadowColor = ImVec4(0.02f, 0.10f, 0.25f, 0.40f);
        t.AlbumArtBox.InnerShadowSize = 5.0f;
        t.AlbumArtBox.UseReflection = true;
        t.AlbumArtBox.ReflectionHeight = 0.25f;
        t.AlbumArtBox.ReflectionOpacity = 0.15f;

        //==========================================================================
        // Lightbox - Deep dark overlay
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.03f, 0.12f, 0.25f, 0.95f);
        t.AlbumArtLightbox.BorderColor = BlueDark;
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
        t.AlbumArtLightbox.LightboxGradientTop = ImVec4(0.05f, 0.20f, 0.40f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom = ImVec4(0.02f, 0.08f, 0.18f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar - Dark theme consistent
        //==========================================================================

        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = BlueMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = AccentLight;
        t.SearchBar.rowHoverColor = DeepBlueAlt;
        t.SearchBar.separatorColor = BorderSubtle;
        t.SearchBar.inputBgColor = DeepBlueDefault;
        t.SearchBar.inputBorderColor = BlueMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;
        t.SearchBar.UseSearchGloss = true;
        t.SearchBar.SearchGlossIntensity = 0.30f;
        t.SearchBar.SearchGlossColor = ImVec4(GlossStrong.x, GlossStrong.y, GlossStrong.z, 0.2f);
        t.SearchBar.UseSearchGradient = true;
        t.SearchBar.SearchGradientTop = BlueMid;
        t.SearchBar.SearchGradientBottom = DeepBlueDefault;
        t.SearchBar.UseRoundedInput = true;
        t.SearchBar.InputRounding = 8.0f;
        t.SearchBar.UseGlossyDropdown = true;
        t.SearchBar.DropdownGlossIntensity = 0.25f;

        //==========================================================================
        // Player Bar - Dark with subtle gradient
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal = BlueDark;
        t.PlayerBar.ButtonHovered = BlueMid;
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
        t.PlayerBar.PlayerBarGradientTop = DeepBlueDefault;
        t.PlayerBar.PlayerBarGradientBottom = DeepBlueDarker;
        t.PlayerBar.PlayerBarGradientRounding = 8.0f;
        t.PlayerBar.PlayerBarOpacity = 0.95f;
        t.PlayerBar.UsePlayerBarBevel = true;
        t.PlayerBar.PlayerBarBevelThickness = 2.5f;
        t.PlayerBar.PlayerBarBevelLight = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient = true;
        t.PlayerBar.SliderTrackGradientTop = DeepBlueDefault;
        t.PlayerBar.SliderTrackGradientBottom = DeepBlueDarker;
        t.PlayerBar.UseSliderGrabGloss = true;
        t.PlayerBar.SliderGrabGlossIntensity = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel = true;
        t.PlayerBar.SliderGrabBevelThickness = 1.5f;
        t.PlayerBar.SliderGrabBevelLight = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor = BevelBorder;
        t.PlayerBar.UseProgressGradient = true;
        t.PlayerBar.ProgressTrackColor = DeepBlueDarker;
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
        // Popup Menu - Dark consistent
        //==========================================================================

        t.ContextMenu.BackgroundColor = SearchDropdownBg;
        t.ContextMenu.BorderColor = BlueMid;
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
        t.ContextMenu.MenuGradientTop = BlueMid;
        t.ContextMenu.MenuGradientBottom = DeepBlueDefault;
        t.ContextMenu.UseGlossySelection = true;
        t.ContextMenu.SelectionGlossIntensity = 0.35f;

        return t;
    }

} // namespace moosic