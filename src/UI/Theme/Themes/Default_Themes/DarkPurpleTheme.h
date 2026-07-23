//==============================================================================
// DarkPurpleTheme.h
//==============================================================================
// Dark theme with purple accent
//==============================================================================

#pragma once

#include "../../Theme.h"

namespace moosic
{

    inline Theme CreateDarkPurpleTheme()
    {
        Theme t;

        //==========================================================================
        // Base palette (RGB → normalized)
        //==========================================================================

        const ImVec4 Purple = ImVec4(0.557f, 0.380f, 0.749f, 1.00f);       // 142,97,191
        const ImVec4 PurpleDark = ImVec4(0.420f, 0.286f, 0.565f, 1.00f);   // 107,73,144
        const ImVec4 PurpleDarker = ImVec4(0.314f, 0.216f, 0.424f, 1.00f); // 80,55,108
        const ImVec4 PurpleLight = ImVec4(0.675f, 0.518f, 0.839f, 1.00f);  // 172,132,214
        const ImVec4 PurpleVeryLight = ImVec4(0.675f, 0.518f, 0.839f, 0.5f);
        const ImVec4 PurpleGlow = ImVec4(0.557f, 0.380f, 0.749f, 0.20f);
        const ImVec4 PurpleSubtle = ImVec4(0.557f, 0.380f, 0.749f, 0.10f);

        const ImVec4 Grey = ImVec4(0.380f, 0.427f, 0.471f, 1.00f);
        const ImVec4 GreyDark = ImVec4(0.280f, 0.327f, 0.371f, 1.00f);
        const ImVec4 GreyDarker = ImVec4(0.200f, 0.247f, 0.291f, 1.00f);
         const ImVec4 GreyLight = ImVec4(0.910f, 0.898f, 0.878f, 1.00f);

        const ImVec4 DarkBg = ImVec4(0.149f, 0.161f, 0.173f, 1.00f);
        const ImVec4 DarkBgAlt = ImVec4(0.176f, 0.192f, 0.204f, 1.00f);
        const ImVec4 DarkBgHi = ImVec4(0.216f, 0.235f, 0.251f, 1.00f);
        const ImVec4 DarkBgPanel = ImVec4(0.122f, 0.133f, 0.145f, 1.00f);

        const ImVec4 TextBright = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        const ImVec4 TextMuted = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
        const ImVec4 TextDim = ImVec4(0.42f, 0.42f, 0.42f, 1.00f);
        const ImVec4 TextWhite = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Title Bar
        //==========================================================================

        t.TitleBar.BackgroundColor = DarkBg;
        t.TitleBar.BackgroundColorActive = DarkBg;
        t.TitleBar.BackgroundColorInactive = ImVec4(DarkBg.x, DarkBg.y, DarkBg.z, 0.85f);
        t.TitleBar.BackgroundOpacity = 1.0f;
        t.TitleBar.ShowBottomBorder = true;
        t.TitleBar.BottomBorderColor = GreyDarker;
        t.TitleBar.ShowWindowBorder = true;
        t.TitleBar.WindowBorderColor = PurpleLight;
        t.TitleBar.ShowAccentLine = false;
        t.TitleBar.AccentLineColor = Purple;
        t.TitleBar.TitleTextColor = TextBright;
        t.TitleBar.TitleTextColorInactive = TextDim;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = Purple;
        t.ContentPanel.TabInactive = GreyDarker;
        t.ContentPanel.TabHovered = GreyDark;
        t.ContentPanel.TabRounding = 4.0f;
        t.ContentPanel.TabText = TextWhite;
        t.ContentPanel.TabTextInactive = TextMuted;
        t.ContentPanel.ButtonNormal = GreyDark;
        t.ContentPanel.ButtonHovered = Purple;
        t.ContentPanel.ButtonActive = PurpleDark;
        t.ContentPanel.ButtonRounding = 2.0f;
        t.ContentPanel.BorderColor = PurpleLight;
        t.ContentPanel.TabSpacing = 4.0f;
        t.ContentPanel.HeaderSpacing = 4.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = DarkBgPanel;
        t.Window.ChildBg = DarkBg;
        t.Window.WindowBorder = GreyDarker;
        t.Window.TitleBar = DarkBgAlt;
        t.Window.TitleBarActive = DarkBgHi;
        t.Window.HeaderText = TextBright;
        t.Window.TextPrimary = TextBright;
        t.Window.TextSecondary = TextMuted;
        t.Window.TextDisabled = TextDim;
        t.Window.BrandText = Purple;
        t.Window.ButtonNormal = GreyDark;
        t.Window.ButtonHovered = Purple;
        t.Window.ButtonActive = PurpleDark;
        t.Window.ProgressBar = Purple;
        t.Window.PlayingHighlight = PurpleGlow;
        t.Window.SeparatorColor = GreyDarker;

        //==========================================================================
        // Track Table
        //==========================================================================

        t.TrackTable.HeaderBackground = GreyDark;
        t.TrackTable.HeaderTextColor = TextBright;
        t.TrackTable.HeaderBorderColor = GreyDarker;
        t.TrackTable.HeaderHovered = DarkBgHi;
        t.TrackTable.HeaderActive = Purple;
        t.TrackTable.HeaderTextTitle = TextBright;
        t.TrackTable.HeaderTextArtist = TextBright;
        t.TrackTable.HeaderTextAlbum = TextBright;
        t.TrackTable.HeaderTextExtension = TextBright;
        t.TrackTable.HeaderTextDuration = TextBright;
        t.TrackTable.RowDefault = DarkBg;
        t.TrackTable.RowDefaultAlt = DarkBgAlt;
        t.TrackTable.RowHovered = ImVec4(Purple.x, Purple.y, Purple.z, 0.25f);
        t.TrackTable.RowClicked = ImVec4(Purple.x, Purple.y, Purple.z, 0.45f);
        t.TrackTable.RowSelected = PurpleLight;
        t.TrackTable.RowPlaying = Purple;
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
        t.TrackTable.BorderColor = GreyDarker;
        t.TrackTable.BorderThickness = 1.0f;
        t.TrackTable.ShowRowSeparators = true;
        t.TrackTable.RowSeparatorColor = ImVec4(GreyDarker.x, GreyDarker.y, GreyDarker.z, 0.40f);
        t.TrackTable.ScrollbarBg = DarkBgPanel;
        t.TrackTable.ScrollbarGrab = GreyDark;
        t.TrackTable.ScrollbarGrabHovered = Grey;
        t.TrackTable.ScrollbarGrabActive = Purple;
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

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = DarkBgPanel;
        t.Visualizer.WaveformColor = Purple;
        t.Visualizer.WaveformFillColor = ImVec4(Purple.x, Purple.y, Purple.z, 0.10f);
        t.Visualizer.GridColor = ImVec4(GreyDark.x, GreyDark.y, GreyDark.z, 0.25f);
        t.Visualizer.BorderColor = GreyDarker;
        t.Visualizer.PlaceholderColor = TextDim;
        t.Visualizer.UseColorRamp = true;
        t.Visualizer.SpectrumColorLow = Purple;
        t.Visualizer.SpectrumColorMid = PurpleLight;
        t.Visualizer.SpectrumColorHigh = ImVec4(0.75f, 0.55f, 1.00f, 1.00f);
        t.Visualizer.SpectrumColorPeak = TextWhite;
        t.Visualizer.ColorRampLowThreshold = 0.0f;
        t.Visualizer.ColorRampMidThreshold = 0.40f;
        t.Visualizer.ColorRampHighThreshold = 0.75f;
        t.Visualizer.UseFrequencyTint = false;
        t.Visualizer.LowFreqTint = ImVec4(1.0f, 0.65f, 0.3f, 1.0f);
        t.Visualizer.HighFreqTint = ImVec4(0.3f, 0.65f, 1.0f, 1.0f);
        t.Visualizer.FrequencyTintBlend = 0.3f;
        t.Visualizer.BarBrightnessMin = 0.50f;
        t.Visualizer.BarBrightnessMax = 1.30f;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = GreyDarker;
        t.AlbumArtBox.BorderColorHovered = Purple;
        t.AlbumArtBox.BorderColorClicked = PurpleLight;
        t.AlbumArtBox.BorderThickness = 2.5f;
        t.AlbumArtBox.BorderThicknessHovered = 3.0f;
        t.AlbumArtBox.BorderRounding = 3.0f;
        t.AlbumArtBox.BackgroundColor = DarkBgAlt;
        t.AlbumArtBox.BackgroundColorHovered = DarkBgHi;
        t.AlbumArtBox.ShowShadow = true;
        t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.40f);
        t.AlbumArtBox.PlaceholderTextColor = TextDim;
        t.AlbumArtBox.ShowHoverOverlay = true;
        t.AlbumArtBox.HoverOverlayColor = ImVec4(Purple.x, Purple.y, Purple.z, 0.08f);
        t.AlbumArtBox.ClickOverlayColor = ImVec4(Purple.x, Purple.y, Purple.z, 0.18f);
        t.AlbumArtBox.ShowPlayButtonOnHover = true;
        t.AlbumArtBox.PlayButtonColor = TextWhite;
        t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.05f, 0.05f, 0.06f, 0.95f);
        t.AlbumArtLightbox.BorderColor = GreyDark;
        t.AlbumArtLightbox.CloseButtonColor = TextMuted;
        t.AlbumArtLightbox.CloseButtonHovered = Purple;
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

        //==========================================================================
        // Search Bar
        //==========================================================================

        // ── Dropdown Colors ──
        t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);
        t.SearchBar.backgroundColor = DarkBgPanel;
        t.SearchBar.borderColor = GreyDarker;
        t.SearchBar.textColor = TextBright;
        t.SearchBar.highlightTextColor = Purple;
        t.SearchBar.rowHoverColor = DarkBgHi;
        t.SearchBar.separatorColor = GreyDarker;

        // ── Input Colors ──
        t.SearchBar.inputBgColor = DarkBgAlt;
        t.SearchBar.inputBorderColor = GreyDarker;
        t.SearchBar.inputTextColor = TextBright;
        t.SearchBar.inputHintColor = TextDim;

        //==========================================================================
        // Player Bar
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;
        t.PlayerBar.ButtonNormal = Purple;
        t.PlayerBar.ButtonHovered = PurpleLight;
        t.PlayerBar.ButtonActive = PurpleDark;
        t.PlayerBar.ButtonPrimary = Purple;
        t.PlayerBar.ButtonPrimaryHovered = PurpleLight;
        t.PlayerBar.ButtonPrimaryActive = PurpleDark;
        t.PlayerBar.SliderTrack = GreyDarker;
        t.PlayerBar.SliderGrab = Purple;
        t.PlayerBar.SliderGrabActive = PurpleLight;
        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        //==========================================================================
        // Popup Menu
        //==========================================================================

        t.ContextMenu.BackgroundColor = DarkBgPanel;
        t.ContextMenu.BorderColor = PurpleLight;
        t.ContextMenu.TextColor = TextBright;
        t.ContextMenu.TextDisabledColor = TextDim;
        t.ContextMenu.HoverColor = Purple;
        t.ContextMenu.HoverTextColor = TextWhite;
        t.ContextMenu.SeparatorColor = Grey;
        t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.35f);

        return t;
    }

} // namespace moosic