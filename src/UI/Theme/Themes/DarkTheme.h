//==============================================================================
// DarkTheme.h
//==============================================================================
// Modern Dark Theme - VS Code Dark+ with UITheme::Dark() button & row colors
//==============================================================================

#pragma once

#include "../Theme.h"

namespace moosic
{

    inline Theme CreateDarkTheme()
    {
        Theme t;

        //==========================================================================
        // Content Panel
        //==========================================================================

        t.ContentPanel.TabActive = ImVec4(0.16f, 0.47f, 0.84f, 1.00f);
        t.ContentPanel.TabInactive = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        t.ContentPanel.TabHovered = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);

        t.ContentPanel.TabText = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        t.ContentPanel.TabTextInactive = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);

        t.ContentPanel.BorderColor = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        t.ContentPanel.BorderThickness = 1.0f;

        //==========================================================================
        // Window
        //==========================================================================

        t.Window.WindowBg = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
        t.Window.ChildBg = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

        t.Window.WindowBorder = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);

        t.Window.TitleBar = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        t.Window.TitleBarActive = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

        t.Window.HeaderText = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);

        t.Window.TextPrimary = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        t.Window.TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
        t.Window.TextDisabled = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);

        // Window buttons - UITheme::Dark() extracted: button.normal = palette.bgAccent = RGB(50,50,50)
        t.Window.ButtonNormal = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);
        // button.hover = palette.accent * 1.15 = RGB(138, 195, 255)
        t.Window.ButtonHovered = ImVec4(0.541f, 0.765f, 1.000f, 1.00f);
        // button.active = palette.accent * 0.75 = RGB(90, 128, 191)
        t.Window.ButtonActive = ImVec4(0.353f, 0.500f, 0.750f, 1.00f);

        t.Window.ButtonRounding = 3.0f;

        t.Window.ProgressBar = ImVec4(0.471f, 0.667f, 1.000f, 1.00f);

        t.Window.PlayingHighlight = ImVec4(0.471f, 0.667f, 1.000f, 0.18f);

        t.Window.SeparatorColor = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);

        //==========================================================================
        // Track Table - Nice Blue Highlighting (matches button accent)
        //==========================================================================

        t.TrackTable.HeaderBackground = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);

        t.TrackTable.RowDefault = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
        t.TrackTable.RowDefaultAlt = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

        // Row hover - subtle blue tint
        t.TrackTable.RowHovered = ImVec4(0.20f, 0.25f, 0.35f, 1.00f);

        // Row clicked - stronger blue accent
        t.TrackTable.RowClicked = ImVec4(0.353f, 0.500f, 0.750f, 0.35f);

        // Row selected - prominent blue highlight (matches primary button)
        t.TrackTable.RowSelected = ImVec4(0.471f, 0.667f, 1.000f, 0.28f);

        // Row playing - softer glowing blue (distinguishable from selected)
        t.TrackTable.RowPlaying = ImVec4(0.1f, 0.40f, 1.00f, 0.50f);

        t.TrackTable.BorderColor = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);

        t.TrackTable.TextColor = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
        t.TrackTable.TextDisabled = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
        t.TrackTable.TextSelected = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);

        //==========================================================================
        // Visualizer
        //==========================================================================

        t.Visualizer.BackgroundColor = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

        t.Visualizer.WaveformColor = ImVec4(0.471f, 0.667f, 1.000f, 1.00f);

        t.Visualizer.WaveformFillColor = ImVec4(0.471f, 0.667f, 1.000f, 0.12f);

        t.Visualizer.SpectrumColor = ImVec4(0.471f, 0.667f, 1.000f, 1.00f);

        t.Visualizer.SpectrumColorHigh = ImVec4(0.541f, 0.765f, 1.000f, 1.00f);

        t.Visualizer.GridColor = ImVec4(0.22f, 0.22f, 0.22f, 0.30f);

        t.Visualizer.BorderColor = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);

        t.Visualizer.PlaceholderColor = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

        t.Visualizer.BorderRounding = 3.0f;
        t.Visualizer.BorderThickness = 1.0f;

        t.Visualizer.RoundBarTops = true;
        t.Visualizer.EnableWaveformFill = true;
        t.Visualizer.ClampToBounds = true;
        t.Visualizer.Mode = VisualizerMode::Oscilloscope;
        t.Visualizer.ShowGrid = false;
        t.Visualizer.ShowPeaks = false;

        //==========================================================================
        // Album Art
        //==========================================================================

        t.AlbumArtBox.BorderColor = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        t.AlbumArtBox.BorderThickness = 1.0f;
        t.AlbumArtBox.BorderRounding = 4.0f;

        t.AlbumArtBox.BackgroundColor = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

        t.AlbumArtBox.ShowShadow = false;

        t.AlbumArtBox.ShadowColor = ImVec4(0, 0, 0, 0);
        t.AlbumArtBox.ShadowOffsetX = 0;
        t.AlbumArtBox.ShadowOffsetY = 0;
        t.AlbumArtBox.ShadowBlur = 0;

        t.AlbumArtBox.PlaceholderTextColor = ImVec4(0.55f, 0.55f, 0.55f, 1.0f);
        t.AlbumArtBox.PlaceholderText = "No Art";

        //==========================================================================
        // Lightbox
        //==========================================================================

        t.AlbumArtLightbox.BackgroundColor = ImVec4(0.08f, 0.08f, 0.08f, 0.95f);

        t.AlbumArtLightbox.BorderColor = ImVec4(0.26f, 0.26f, 0.26f, 1.0f);

        t.AlbumArtLightbox.CloseButtonColor = ImVec4(0.90f, 0.90f, 0.90f, 0.80f);

        t.AlbumArtLightbox.CloseButtonHovered = ImVec4(1, 1, 1, 1);

        t.AlbumArtLightbox.TitleColor = ImVec4(0.95f, 0.95f, 0.95f, 1);

        t.AlbumArtLightbox.ArtistColor = ImVec4(0.70f, 0.70f, 0.70f, 1);

        t.AlbumArtLightbox.BorderRounding = 8.0f;

        //==========================================================================
        // Player Bar - UITheme::Dark() extracted button colors
        //==========================================================================

        t.PlayerBar.TextPrimary = t.Window.TextPrimary;
        t.PlayerBar.TextSecondary = t.Window.TextSecondary;

        // button.normal = palette.bgAccent = RGB(50, 50, 50)
        t.PlayerBar.ButtonNormal = ImVec4(0.196f, 0.196f, 0.196f, 1.00f);
        // button.hover = palette.accent * 1.15 = RGB(138, 195, 255)
        t.PlayerBar.ButtonHovered = ImVec4(0.541f, 0.765f, 1.000f, 1.00f);
        // button.active = palette.accent * 0.75 = RGB(90, 128, 191)
        t.PlayerBar.ButtonActive = ImVec4(0.353f, 0.500f, 0.750f, 1.00f);

        // Primary = palette.accent = RGB(120, 170, 255)
        t.PlayerBar.ButtonPrimary = ImVec4(0.471f, 0.667f, 1.000f, 1.00f);
        // Primary hovered = palette.accent * 1.15 = RGB(138, 195, 255)
        t.PlayerBar.ButtonPrimaryHovered = ImVec4(0.541f, 0.765f, 1.000f, 1.00f);
        // Primary active = palette.accent * 0.75 = RGB(90, 128, 191)
        t.PlayerBar.ButtonPrimaryActive = ImVec4(0.353f, 0.500f, 0.750f, 1.00f);

        // Slider track = palette.border = RGB(70, 70, 70)
        t.PlayerBar.SliderTrack = ImVec4(0.275f, 0.275f, 0.275f, 1.00f);

        // Slider grab = palette.accent = RGB(120, 170, 255)
        t.PlayerBar.SliderGrab = ImVec4(0.471f, 0.667f, 1.000f, 1.00f);

        // Slider grab active = palette.accent * 1.15 = RGB(138, 195, 255)
        t.PlayerBar.SliderGrabActive = ImVec4(0.541f, 0.765f, 1.000f, 1.00f);

        // Sizing
        t.PlayerBar.ButtonRounding = 3.0f;
        t.PlayerBar.SliderRounding = 3.0f;
        t.PlayerBar.AlbumArtRounding = 4.0f;

        t.PlayerBar.NormalButtonExtraWidth = 15.0f;
        t.PlayerBar.PrimaryButtonExtraWidth = 22.0f;
        t.PlayerBar.ButtonHeightExtra = 3.0f;
        t.PlayerBar.AlbumArtSize = 60.0f;

        t.PlayerBar.Lightbox = t.AlbumArtLightbox;
        t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
        t.PlayerBar.Visualizer = t.Visualizer;

        return t;
    }

} // namespace moosic