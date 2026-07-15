//==============================================================================
// LightTheme.h
//==============================================================================
// VS Code Light style with classic ImGui button styling
//==============================================================================

#pragma once

#include "../Theme.h"

namespace moosic
{

//==============================================================================
// Light Theme - VS Code Light with Classic ImGui Buttons
//==============================================================================

inline Theme CreateLightTheme()
{
    Theme t;

    //--------------------------------------------------------------------------
    // ContentPanelTheme - VS Code Light
    //--------------------------------------------------------------------------

    t.ContentPanel.TabActive = ImVec4(0.00f, 0.48f, 0.80f, 1.00f);
    t.ContentPanel.TabInactive = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.ContentPanel.TabHovered = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
    t.ContentPanel.TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    t.ContentPanel.TabTextInactive = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    t.ContentPanel.BorderColor = ImVec4(0.00f, 0.48f, 0.80f, 1.00f);
    t.ContentPanel.BorderThickness = 2.0f;
    t.ContentPanel.TabSpacing = 2.0f;

    //--------------------------------------------------------------------------
    // WindowTheme - VS Code Light
    //--------------------------------------------------------------------------

    // Window Backgrounds
    t.Window.WindowBg = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);
    t.Window.ChildBg = ImVec4(0.965f, 0.965f, 0.965f, 1.00f);
    t.Window.WindowBorder = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    t.Window.TitleBar = ImVec4(0.945f, 0.945f, 0.945f, 1.00f);
    t.Window.TitleBarActive = ImVec4(0.945f, 0.945f, 0.945f, 1.00f);

    // Text Colors
    t.Window.HeaderText = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.Window.TextPrimary = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    t.Window.TextSecondary = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    t.Window.TextDisabled = ImVec4(0.65f, 0.65f, 0.65f, 1.00f);

    // Classic ImGui Button Colors (rounded but classic looking)
    t.Window.ButtonNormal = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    t.Window.ButtonHovered = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    t.Window.ButtonActive = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
    t.Window.ButtonRounding = 4.0f;

    // Misc Colors
    t.Window.ProgressBar = ImVec4(0.00f, 0.48f, 0.80f, 1.00f);
    t.Window.PlayingHighlight = ImVec4(0.00f, 0.48f, 0.80f, 0.25f);
    t.Window.SeparatorColor = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.Window.HeaderSpacing = 4.0f;

    //--------------------------------------------------------------------------
    // TrackTableStyle - VS Code Light
    //--------------------------------------------------------------------------

    t.TrackTable.HeaderBackground = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.TrackTable.RowDefault = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
    t.TrackTable.RowDefaultAlt = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    t.TrackTable.RowHovered = ImVec4(0.88f, 0.88f, 0.88f, 1.00f);
    t.TrackTable.RowClicked = ImVec4(0.00f, 0.48f, 0.80f, 0.20f);
    t.TrackTable.RowSelected = ImVec4(0.00f, 0.48f, 0.80f, 0.15f);
    t.TrackTable.RowPlaying = ImVec4(0.00f, 0.48f, 0.80f, 0.12f);
    t.TrackTable.BorderColor = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.TrackTable.TextColor = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.TrackTable.TextDisabled = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
    t.TrackTable.TextSelected = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    
    // Column widths - keep defaults
    t.TrackTable.TitleWidth = 300.0f;
    t.TrackTable.ArtistWidth = 200.0f;
    t.TrackTable.AlbumWidth = 200.0f;
    t.TrackTable.ExtensionWidth = 60.0f;
    t.TrackTable.DurationWidth = 80.0f;
    t.TrackTable.DefaultColumnWidth = 150.0f;
    t.TrackTable.RowHeight = 12.0f;

    //--------------------------------------------------------------------------
    // WaveVisualizerStyle - VS Code Light
    //--------------------------------------------------------------------------

    t.Visualizer.BackgroundColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    t.Visualizer.WaveformColor = ImVec4(0.00f, 0.48f, 0.80f, 1.00f);
    t.Visualizer.WaveformFillColor = ImVec4(0.00f, 0.48f, 0.80f, 0.10f);
    t.Visualizer.SpectrumColor = ImVec4(0.00f, 0.48f, 0.80f, 1.00f);
    t.Visualizer.SpectrumColorHigh = ImVec4(0.20f, 0.60f, 1.00f, 1.00f);
    t.Visualizer.GridColor = ImVec4(0.80f, 0.80f, 0.80f, 0.40f);
    t.Visualizer.BorderColor = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.Visualizer.PlaceholderColor = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    
    // Keep default sizing
    t.Visualizer.BoxWidth = 137.0f;
    t.Visualizer.BoxHeight = 45.0f;
    t.Visualizer.BorderRounding = 3.0f;
    t.Visualizer.BorderThickness = 3.0f;
    t.Visualizer.OffsetX = 0.0f;
    t.Visualizer.OffsetY = 0.0f;
    t.Visualizer.OscilloscopeScaleX = 1.0f;
    t.Visualizer.OscilloscopeScaleY = 1.0f;
    t.Visualizer.SpectrumScaleX = 1.0f;
    t.Visualizer.SpectrumScaleY = 1.0f;
    t.Visualizer.SpectrumBands = 16;
    t.Visualizer.BarWidth = 3.2f;
    t.Visualizer.BarGap = 5.0f;
    t.Visualizer.BarBottomPadding = 3.0f;
    t.Visualizer.BarTopPadding = 2.0f;
    t.Visualizer.BarTopRounding = 2.0f;
    t.Visualizer.RoundBarTops = true;
    t.Visualizer.WaveformSamples = 128;
    t.Visualizer.WaveformLineWidth = 1.5f;
    t.Visualizer.EnableWaveformFill = true;
    t.Visualizer.SpectrumSensitivity = 2.0f;
    t.Visualizer.SpectrumDecay = 0.7f;
    t.Visualizer.Smoothing = 0.6f;
    t.Visualizer.ScaleMultiplier = 3.3f;
    t.Visualizer.VolumeAffectsScale = false;
    t.Visualizer.ClampToBounds = true;
    t.Visualizer.Mode = VisualizerMode::Oscilloscope;
    t.Visualizer.ShowGrid = false;
    t.Visualizer.GridLinesHorizontal = 2;
    t.Visualizer.GridLinesVertical = 4;
    t.Visualizer.ShowPeaks = false;

    //--------------------------------------------------------------------------
    // AlbumArtBoxTheme - VS Code Light
    //--------------------------------------------------------------------------

    t.AlbumArtBox.BorderColor = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.AlbumArtBox.BorderThickness = 2.0f;
    t.AlbumArtBox.BorderRounding = 6.0f;
    t.AlbumArtBox.BackgroundColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    t.AlbumArtBox.ShowShadow = true;
    t.AlbumArtBox.ShadowColor = ImVec4(0.30f, 0.30f, 0.30f, 0.15f);
    t.AlbumArtBox.ShadowOffsetX = 2.0f;
    t.AlbumArtBox.ShadowOffsetY = 2.0f;
    t.AlbumArtBox.ShadowBlur = 4.0f;
    t.AlbumArtBox.PlaceholderTextColor = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    t.AlbumArtBox.PlaceholderText = "No Art";

    //--------------------------------------------------------------------------
    // LightboxTheme - VS Code Light
    //--------------------------------------------------------------------------

    t.AlbumArtLightbox.BackgroundColor = ImVec4(1.00f, 1.00f, 1.00f, 0.92f);
    t.AlbumArtLightbox.BorderColor = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
    t.AlbumArtLightbox.CloseButtonColor = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
    t.AlbumArtLightbox.CloseButtonHovered = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    t.AlbumArtLightbox.TitleColor = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.AlbumArtLightbox.ArtistColor = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    t.AlbumArtLightbox.MaxWidth = 600.0f;
    t.AlbumArtLightbox.MaxHeight = 600.0f;
    t.AlbumArtLightbox.BorderRounding = 12.0f;
    t.AlbumArtLightbox.CloseButtonSize = 30.0f;
    t.AlbumArtLightbox.Padding = 20.0f;

    //--------------------------------------------------------------------------
    // PlayerBarTheme - Classic ImGui Light
    //--------------------------------------------------------------------------

    t.PlayerBar.TextPrimary = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    t.PlayerBar.TextSecondary = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    t.PlayerBar.ButtonNormal = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    t.PlayerBar.ButtonHovered = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
    t.PlayerBar.ButtonActive = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
    t.PlayerBar.ButtonPrimary = ImVec4(0.00f, 0.60f, 0.80f, 1.00f);
    t.PlayerBar.ButtonPrimaryHovered = ImVec4(0.10f, 0.70f, 0.90f, 1.00f);
    t.PlayerBar.ButtonPrimaryActive = ImVec4(0.00f, 0.50f, 0.70f, 1.00f);
    t.PlayerBar.SliderTrack = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    t.PlayerBar.SliderGrab = ImVec4(0.00f, 0.60f, 0.80f, 1.00f);
    t.PlayerBar.SliderGrabActive = ImVec4(0.10f, 0.70f, 0.90f, 1.00f);
    t.PlayerBar.ButtonRounding = 4.0f;
    t.PlayerBar.SliderRounding = 4.0f;
    t.PlayerBar.AlbumArtRounding = 4.0f;
    t.PlayerBar.AlbumArtSize = 60.0f;
    t.PlayerBar.NormalButtonExtraWidth = 15.0f;
    t.PlayerBar.PrimaryButtonExtraWidth = 22.0f;
    t.PlayerBar.ButtonHeightExtra = 3.0f;

    // Child widget themes (forwarded from above)
    t.PlayerBar.Lightbox = t.AlbumArtLightbox;
    t.PlayerBar.AlbumArtBox = t.AlbumArtBox;
    t.PlayerBar.Visualizer = t.Visualizer;

    return t;
}

} // namespace moosic