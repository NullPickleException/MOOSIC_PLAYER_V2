//==============================================================================
// ClassicVioletTheme.h
//==============================================================================
// Classic violet/deep purple theme with 3D glossy effects
// 3 base colors: Deep Violet (60%), Medium Violet (30%), Purple Accent (10%)
// Palette: #1A0033, #2D004D, #4A0066, #6A1B9A, #9C27B0
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateClassicVioletTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized) - 60% Dark, 30% Medium, 10% Light
        //==========================================================================

        // ── Deep Violet (60%) - main backgrounds (#1A0033, rgb(26,0,51)) ──
        const ImVec4 VioletDeep = ImVec4(0.10f, 0.00f, 0.20f, 1.00f);       // #1A0033
        const ImVec4 VioletPanel = ImVec4(0.12f, 0.00f, 0.24f, 1.00f);      // #1F003D
        const ImVec4 VioletDefault = ImVec4(0.14f, 0.00f, 0.28f, 1.00f);    // #240047
        const ImVec4 VioletAlt = ImVec4(0.16f, 0.00f, 0.32f, 1.00f);        // #290052
        const ImVec4 VioletSurface = ImVec4(0.18f, 0.00f, 0.36f, 1.00f);    // #2E005C
        const ImVec4 VioletDarker = ImVec4(0.08f, 0.00f, 0.16f, 1.00f);     // #140029

        // ── Medium Violet (30%) - surfaces (#2D004D, rgb(45,0,77)) ──────
        const ImVec4 VioletDark = ImVec4(0.18f, 0.00f, 0.30f, 1.00f);      // #2E004D
        const ImVec4 VioletMid = ImVec4(0.22f, 0.00f, 0.36f, 1.00f);       // #38005C
        const ImVec4 VioletLight = ImVec4(0.26f, 0.02f, 0.42f, 1.00f);     // #42056B
        const ImVec4 VioletDarkerMid = ImVec4(0.15f, 0.00f, 0.25f, 1.00f); // #260040

        // ── Purple (10%) - accent (#6A1B9A, rgb(106,27,154)) ──────────────
        const ImVec4 Accent = ImVec4(0.42f, 0.11f, 0.60f, 1.00f);          // #6B1A99
        const ImVec4 AccentDark = ImVec4(0.34f, 0.08f, 0.50f, 1.00f);      // #571480
        const ImVec4 AccentDarker = ImVec4(0.26f, 0.05f, 0.40f, 1.00f);    // #420D66
        const ImVec4 AccentLight = ImVec4(0.55f, 0.20f, 0.75f, 1.00f);     // #8C33BF
        const ImVec4 AccentVeryLight = ImVec4(0.55f, 0.20f, 0.75f, 0.50f);

        // ── Utility ──────────────────────────────────────────────────
        const ImVec4 VioletGlow = ImVec4(0.22f, 0.00f, 0.36f, 0.25f);
        const ImVec4 VioletVeryLight = ImVec4(0.22f, 0.00f, 0.36f, 0.50f);
        const ImVec4 VioletSubtle = ImVec4(0.22f, 0.00f, 0.36f, 0.10f);
        const ImVec4 SearchDropdownBg = ImVec4(0.12f, 0.00f, 0.24f, 1.00f);

        // ── Text ─────────────────────────────────────────────────────
        const ImVec4 TextBright = ImVec4(0.95f, 0.90f, 1.00f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.70f, 0.50f, 0.85f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.50f, 0.30f, 0.65f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        // ── Borders ───────────────────────────────────────────────────
        const ImVec4 BorderSubtle = ImVec4(0.22f, 0.00f, 0.36f, 1.00f);

        // ── Gloss for 3D ─────────────────────────────────────────────
        const ImVec4 GlossWhite = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
        const ImVec4 GlossStrong = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        const ImVec4 BevelShadow = ImVec4(0.08f, 0.00f, 0.16f, 0.55f);
        const ImVec4 BevelBorder = ImVec4(0.16f, 0.00f, 0.28f, 0.65f);

        //==========================================================================
        // Title Bar - Deep violet gradient
        //==========================================================================

        t.TitleBar.BackgroundColor = ImVec4(0.08f, 0.00f, 0.16f, 1.00f);
        t.TitleBar.BackgroundColorActive = ImVec4(0.08f, 0.00f, 0.16f, 1.00f);
        t.TitleBar.BackgroundColorInactive = ImVec4(0.08f, 0.00f, 0.16f, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;
        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = BorderSubtle;
        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = VioletMid;
        t.TitleBar.ShowAccentLine = true;
        t.TitleBar.AccentLineColor = AccentLight;
        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        t.TitleBar.UseTitleBarGradient = true;
        t.TitleBar.TitleBarGradientTop = ImVec4(0.06f, 0.00f, 0.14f, 1.00f);
        t.TitleBar.TitleBarGradientBottom = ImVec4(0.10f, 0.00f, 0.20f, 1.00f);
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
        t.ContentPanel.TabInactive = VioletDefault;
        t.ContentPanel.TabHovered = VioletAlt;
        t.ContentPanel.TabRounding = 4.0f;
        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;
        t.ContentPanel.ButtonNormal = VioletDark;
        t.ContentPanel.ButtonHovered = VioletMid;
        t.ContentPanel.ButtonActive = AccentDark;
        t.ContentPanel.ButtonRounding = 2.0f;
        t.ContentPanel.BorderColor = VioletMid;
        t.ContentPanel.BorderThickness = 2.5f;
        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        t.ContentPanel.UseGlossyTabs = true;
        t.ContentPanel.TabGlossIntensity = 0.35f;
        t.ContentPanel.TabGlossHighlight = GlossWhite;
        t.ContentPanel.UseGradientTabs = true;
        t.ContentPanel.TabGradientTop = VioletDefault;
        t.ContentPanel.TabGradientBottom = VioletDarker;
        t.ContentPanel.UseTabBevel = true;
        t.ContentPanel.TabBevelThickness = 2.0f;
        t.ContentPanel.TabBevelLight = GlossStrong;
        t.ContentPanel.TabBevelDark = BevelShadow;
        t.ContentPanel.TabBevelBorderColor = BevelBorder;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = VioletPanel;
        t.Window.ChildBg = VioletDarker;
        t.Window.WindowBorder = BorderSubtle;
        t.Window.TitleBar = VioletDefault;
        t.Window.TitleBarActive = VioletAlt;
        t.Window.HeaderText = TextBright;
        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;
        t.Window.BrandText = AccentLight;

        t.Window.ButtonNormal = VioletDark;
        t.Window.ButtonHovered = VioletMid;
        t.Window.ButtonActive = AccentDark;
        t.Window.ButtonRounding = 8.0f;
        t.Window.UseWindowGradient = true;
        t.Window.WindowGradientTop = VioletDefault;
        t.Window.WindowGradientBottom = VioletDarker;
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
        t.Window.PlayingHighlight = VioletGlow;
        t.Window.SeparatorColor = BorderSubtle;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground = VioletDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = BorderSubtle;
        t.TrackTable.HeaderHovered = VioletSurface;
        t.TrackTable.HeaderActive = AccentLight;
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;
        t.TrackTable.RowDefault = VioletDarker;
        t.TrackTable.RowDefaultAlt = VioletDefault;
        t.TrackTable.RowHovered = VioletVeryLight;
        t.TrackTable.RowClicked = AccentDarker;
        t.TrackTable.RowSelected = VioletDark;
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
        t.TrackTable.ScrollbarBg = VioletPanel;
        t.TrackTable.ScrollbarGrab = VioletDark;
        t.TrackTable.ScrollbarGrabHovered = VioletMid;
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
        t.TrackTable.HeaderGradientTop = VioletMid;
        t.TrackTable.HeaderGradientBottom = VioletDark;
        t.TrackTable.UseGlossySelection = true;
        t.TrackTable.SelectionGlossIntensity = 0.30f;
        t.TrackTable.UseRoundedScrollbar = true;
        t.TrackTable.ScrollbarGlossIntensity = 0.25f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = VioletDarker;
        t.Visualizer.WaveformColor = AccentLight;
        t.Visualizer.WaveformFillColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.15f);
        t.Visualizer.GridColor = ImVec4(VioletDark.x, VioletDark.y, VioletDark.z, 0.30f);
        t.Visualizer.BorderColor = BorderSubtle;
        t.Visualizer.PlaceholderColor = TextDim;
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = VioletDark;
        t.Visualizer.SpectrumColorMid = VioletMid;
        t.Visualizer.SpectrumColorHigh = AccentLight;
        t.Visualizer.SpectrumColorPeak = ImVec4(0.75f, 0.40f, 0.90f, 1.00f);
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.45f;
        t.Visualizer.ColorRampHighThreshold = 0.80f;
        t.Visualizer.UseFrequencyTint = true;
        t.Visualizer.LowFreqTint = VioletDark;
        t.Visualizer.HighFreqTint = AccentLight;
        t.Visualizer.FrequencyTintBlend = 0.30f;
        t.Visualizer.BarBrightnessMin = 0.55f;
        t.Visualizer.BarBrightnessMax = 1.30f;
        t.Visualizer.UseGlossyBars = true;
        t.Visualizer.BarGlossIntensity = 0.40f;
        t.Visualizer.BarGlossColor = GlossStrong;
        t.Visualizer.UseVisualizerGradient = true;
        t.Visualizer.VisualizerGradientTop = VioletDefault;
        t.Visualizer.VisualizerGradientBottom = VioletDarker;
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
        t.AlbumArtBox.BackgroundColor = VioletDefault;
        t.AlbumArtBox.BackgroundColorHovered = VioletAlt;
        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
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
        t.AlbumArtBox.InnerShadowColor = ImVec4(0.08f, 0.00f, 0.16f, 0.45f);
        t.AlbumArtBox.InnerShadowSize = 5.0f;
        t.AlbumArtBox.UseReflection = true;
        t.AlbumArtBox.ReflectionHeight = 0.25f;
        t.AlbumArtBox.ReflectionOpacity = 0.15f;

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.08f, 0.00f, 0.16f, 0.95f);
        t.AlbumArtLightbox.BorderColor = VioletDark;
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
        t.AlbumArtLightbox.LightboxGradientTop = ImVec4(0.10f, 0.00f, 0.20f, 0.95f);
        t.AlbumArtLightbox.LightboxGradientBottom = ImVec4(0.06f, 0.00f, 0.12f, 0.95f);
        t.AlbumArtLightbox.UseGlossyCloseButton = true;
        t.AlbumArtLightbox.CloseButtonGlossIntensity = 0.40f;

        //==========================================================================
        // Search Bar
        //==========================================================================

        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.45f);
        t.SearchBar.backgroundColor = SearchDropdownBg;
        t.SearchBar.borderColor = VioletMid;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = AccentLight;
        t.SearchBar.rowHoverColor = VioletAlt;
        t.SearchBar.separatorColor = BorderSubtle;
        t.SearchBar.inputBgColor = VioletDefault;
        t.SearchBar.inputBorderColor = VioletMid;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;
        t.SearchBar.UseSearchGloss = true;
        t.SearchBar.SearchGlossIntensity = 0.30f;
        t.SearchBar.SearchGlossColor = ImVec4(GlossStrong.x, GlossStrong.y, GlossStrong.z, 0.2f);
        t.SearchBar.UseSearchGradient = true;
        t.SearchBar.SearchGradientTop = VioletMid;
        t.SearchBar.SearchGradientBottom = VioletDefault;
        t.SearchBar.UseRoundedInput = true;
        t.SearchBar.InputRounding = 8.0f;
        t.SearchBar.UseGlossyDropdown = true;
        t.SearchBar.DropdownGlossIntensity = 0.25f;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal = VioletDark;
        t.PlayerBar.ButtonHovered = VioletMid;
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
        t.PlayerBar.PlayerBarGradientTop = VioletDefault;
        t.PlayerBar.PlayerBarGradientBottom = VioletDarker;
        t.PlayerBar.PlayerBarGradientRounding = 8.0f;
        t.PlayerBar.PlayerBarOpacity = 0.95f;
        t.PlayerBar.UsePlayerBarBevel = true;
        t.PlayerBar.PlayerBarBevelThickness = 2.5f;
        t.PlayerBar.PlayerBarBevelLight = GlossStrong;
        t.PlayerBar.PlayerBarBevelDark = BevelShadow;
        t.PlayerBar.PlayerBarBevelBorderColor = BevelBorder;
        t.PlayerBar.UseSliderTrackGradient = true;
        t.PlayerBar.SliderTrackGradientTop = VioletDefault;
        t.PlayerBar.SliderTrackGradientBottom = VioletDarker;
        t.PlayerBar.UseSliderGrabGloss = true;
        t.PlayerBar.SliderGrabGlossIntensity = 0.40f;
        t.PlayerBar.SliderGrabGlossHighlight = GlossStrong;
        t.PlayerBar.UseSliderGrabBevel = true;
        t.PlayerBar.SliderGrabBevelThickness = 1.5f;
        t.PlayerBar.SliderGrabBevelLight = GlossStrong;
        t.PlayerBar.SliderGrabBevelDark = BevelShadow;
        t.PlayerBar.SliderGrabBevelBorderColor = BevelBorder;
        t.PlayerBar.UseProgressGradient = true;
        t.PlayerBar.ProgressTrackColor = VioletDarker;
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
        t.ContextMenu.BorderColor = VioletMid;
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
        t.ContextMenu.MenuGradientTop = VioletMid;
        t.ContextMenu.MenuGradientBottom = VioletDefault;
        t.ContextMenu.UseGlossySelection = true;
        t.ContextMenu.SelectionGlossIntensity = 0.35f;

        return t;
    }

} // namespace moosic