//==============================================================================
// LightPinkTheme.h
//==============================================================================
// Warm, eye-friendly light theme with pink accent
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateLightPinkTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (Warm, Eye-Friendly)
        //==========================================================================

        const ImVec4 Pink = ImVec4(0.878f, 0.349f, 0.612f, 1.00f);      // 224,89,156
        const ImVec4 PinkDark = ImVec4(0.659f, 0.263f, 0.459f, 1.00f);  // 168,67,117
        const ImVec4 PinkLight = ImVec4(0.937f, 0.510f, 0.710f, 1.00f); // 239,130,181
        const ImVec4 PinkGlow = ImVec4(0.878f, 0.349f, 0.612f, 0.10f);
        const ImVec4 PinkSubtle = ImVec4(0.878f, 0.349f, 0.612f, 0.06f);

        const ImVec4 Grey = ImVec4(0.627f, 0.604f, 0.569f, 1.00f);
        const ImVec4 GreyDark = ImVec4(0.537f, 0.514f, 0.478f, 1.00f);
        const ImVec4 GreyDarker = ImVec4(0.820f, 0.808f, 0.788f, 1.00f);
        const ImVec4 GreyLight = ImVec4(0.910f, 0.898f, 0.878f, 1.00f);

        const ImVec4 LightBg = ImVec4(0.957f, 0.949f, 0.937f, 1.00f);
        const ImVec4 LightBgAlt = ImVec4(0.937f, 0.925f, 0.910f, 1.00f);
        const ImVec4 LightBgHi = ImVec4(0.890f, 0.886f, 0.878f, 1.00f);
        const ImVec4 LightBgPanel = ImVec4(0.969f, 0.961f, 0.949f, 1.00f);

        const ImVec4 TextDark = ImVec4(0.235f, 0.216f, 0.196f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.447f, 0.424f, 0.396f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.608f, 0.584f, 0.557f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = Grey;
        t.TitleBar.BackgroundColorActive = GreyLight;
        t.TitleBar.BackgroundColorInactive = ImVec4(LightBg.x, LightBg.y, LightBg.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;
        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = GreyDarker;
        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = Pink;
        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Pink;
        t.TitleBar.TitleTextColor = TextDark;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Pink;
        t.ContentPanel.TabInactive = GreyLight;
        t.ContentPanel.TabHovered = LightBgHi;
        t.ContentPanel.TabRounding = 4.0f;
        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;
        t.ContentPanel.ButtonNormal = GreyLight;
        t.ContentPanel.ButtonHovered = LightBgHi;
        t.ContentPanel.ButtonActive = GreyDarker;
        t.ContentPanel.ButtonRounding = 2.0f;
        t.ContentPanel.BorderColor = PinkLight;
        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = LightBgPanel;
        t.Window.ChildBg = LightBg;
        t.Window.WindowBorder = GreyDarker;
        t.Window.TitleBar = LightBgAlt;
        t.Window.TitleBarActive = LightBgAlt;
        t.Window.HeaderText = TextDark;
        t.Window.TextPrimary = TextDark;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;
        t.Window.BrandText = Pink;
        t.Window.ButtonNormal = GreyLight;
        t.Window.ButtonHovered = LightBgHi;
        t.Window.ButtonActive = GreyDarker;
        t.Window.ProgressBar = Pink;
        t.Window.PlayingHighlight = PinkGlow;
        t.Window.SeparatorColor = GreyDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground = LightBgAlt;
        t.TrackTable.HeaderTextColor = TextMuted;
        t.TrackTable.HeaderBorderColor = GreyDarker;
        t.TrackTable.HeaderHovered = LightBgHi;
        t.TrackTable.HeaderActive = Pink;
        t.TrackTable.HeaderTextTitle = TextMuted;
        t.TrackTable.HeaderTextArtist = TextMuted;
        t.TrackTable.HeaderTextAlbum = TextMuted;
        t.TrackTable.HeaderTextExtension = TextMuted;
        t.TrackTable.HeaderTextDuration = TextMuted;
        t.TrackTable.RowDefault = LightBgPanel;
        t.TrackTable.RowDefaultAlt = LightBg;
        t.TrackTable.RowHovered = ImVec4(Pink.x, Pink.y, Pink.z, 0.20f);
        t.TrackTable.RowClicked = ImVec4(Pink.x, Pink.y, Pink.z, 0.35f);
        t.TrackTable.RowSelected = PinkLight;
        t.TrackTable.RowPlaying = PinkLight;
        t.TrackTable.RowHeight = 18.0f;
        t.TrackTable.RowPaddingX = 4.0f;
        t.TrackTable.RowPaddingY = 2.0f;
        t.TrackTable.TextColor = TextDark;
        t.TrackTable.TextDim = TextDim;
        t.TrackTable.TextSelected = TextWhite;
        t.TrackTable.TextPlaying = TextDark;
        t.TrackTable.RowTextTitle = TextDark;
        t.TrackTable.RowTextArtist = TextMuted;
        t.TrackTable.RowTextAlbum = TextMuted;
        t.TrackTable.RowTextExtension = TextDim;
        t.TrackTable.RowTextDuration = TextMuted;
        t.TrackTable.BorderColor = GreyDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.50f);
        t.TrackTable.ScrollbarBg = LightBg;
        t.TrackTable.ScrollbarGrab = GreyDarker;
        t.TrackTable.ScrollbarGrabHovered = Grey;
        t.TrackTable.ScrollbarGrabActive = Pink;
        t.TrackTable.ScrollbarWidth = 8.0f;
        t.TrackTable.ScrollbarRounding = 4.0f;
        t.TrackTable.HoverFadeSpeed = 0.18f;
        t.TrackTable.SelectionFadeSpeed = 0.22f;
        t.TrackTable.ScrollSmoothing = 0.14f;
        t.TrackTable.TableRounding = 0.0f;
        t.TrackTable.MinColumnWidth = 30.0f;
        t.TrackTable.TitleWidth = 350.0f;
        t.TrackTable.ArtistWidth = 180.0f;
        t.TrackTable.AlbumWidth = 180.0f;
        t.TrackTable.ExtensionWidth = 50.0f;
        t.TrackTable.DurationWidth = 80.0f;

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = LightBg;
        t.Visualizer.WaveformColor = Pink;
        t.Visualizer.WaveformFillColor = ImVec4(Pink.x, Pink.y, Pink.z, 0.06f);
        t.Visualizer.GridColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.40f);
        t.Visualizer.BorderColor = GreyDarker;
        t.Visualizer.PlaceholderColor = TextDim;
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = ImVec4(0.800f, 0.480f, 0.620f, 1.00f);
        t.Visualizer.SpectrumColorMid = Pink;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.650f, 0.200f, 0.400f, 1.00f);
        t.Visualizer.SpectrumColorPeak = ImVec4(0.353f, 0.337f, 0.306f, 1.00f);
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.40f;
        t.Visualizer.ColorRampHighThreshold = 0.75f;
        t.Visualizer.UseFrequencyTint = false;
        t.Visualizer.LowFreqTint = ImVec4(0.91f, 0.58f, 0.35f, 1.0f);
        t.Visualizer.HighFreqTint = ImVec4(0.35f, 0.58f, 0.84f, 1.0f);
        t.Visualizer.FrequencyTintBlend = 0.25f;
        t.Visualizer.BarBrightnessMin = 0.60f;
        t.Visualizer.BarBrightnessMax = 1.20f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = GreyDarker;
        t.AlbumArtBox.BorderColorHovered = Pink;
        t.AlbumArtBox.BorderColorClicked = PinkLight;
        t.AlbumArtBox.BorderThickness = 1.5f;
        t.AlbumArtBox.BorderThicknessHovered = 2.5f;
        t.AlbumArtBox.BorderRounding = 4.0f;
        t.AlbumArtBox.BackgroundColor = LightBgAlt;
        t.AlbumArtBox.BackgroundColorHovered = LightBgHi;
        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.24f, 0.22f, 0.20f, 0.08f);
        t.AlbumArtBox.PlaceholderTextColor = TextDim;
        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Pink.x, Pink.y, Pink.z, 0.05f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Pink.x, Pink.y, Pink.z, 0.12f);
        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.18f, 0.16f, 0.14f, 0.45f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.969f, 0.961f, 0.949f, 0.94f);
        t.AlbumArtLightbox.BorderColor = GreyDarker;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Pink;
        t.AlbumArtLightbox.TitleColor = TextDark;
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
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.15f);
        t.SearchBar.backgroundColor = LightBgPanel;
        t.SearchBar.borderColor = GreyDarker;
        t.SearchBar.textColor = TextDark;
        t.SearchBar.highlightTextColor = Pink;
        t.SearchBar.rowHoverColor = LightBgHi;
        t.SearchBar.separatorColor = GreyDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = LightBg;
        t.SearchBar.inputBorderColor = GreyDarker;
        t.SearchBar.inputTextColor = TextDark;
        t.SearchBar.inputHintColor = TextDim;

      

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal = GreyLight;
        t.PlayerBar.ButtonHovered = Pink;
        t.PlayerBar.ButtonActive = PinkDark;
        t.PlayerBar.ButtonPrimary = Pink;
        t.PlayerBar.ButtonPrimaryHovered = PinkLight;
        t.PlayerBar.ButtonPrimaryActive = PinkDark;
        t.PlayerBar.SliderTrack = GreyDarker;
        t.PlayerBar.SliderGrab = Pink;
        t.PlayerBar.SliderGrabActive = PinkLight;
        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        return t;
    }

} // namespace moosic