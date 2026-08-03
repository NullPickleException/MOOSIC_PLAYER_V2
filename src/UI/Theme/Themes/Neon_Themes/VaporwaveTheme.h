//==============================================================================
// VaporwaveTheme.h
//==============================================================================
// Vaporwave - pink/cyan duotone on deep purple void
// 60% Deep purple void (#140F23 → #1C1835)
// 25% Dark violet surfaces (#3D2050, #5C3090)
// 10% Pink/cyan duotone accents (#FF64C8, #64C8FF)
// 5% Pale pink glow text (#FFE0FF)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateVaporwaveTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.078f, 0.059f, 0.137f, 1.00f);
    const ImVec4 DeepVapor   = ImVec4(0.110f, 0.094f, 0.208f, 1.00f);
    const ImVec4 VaporBg     = ImVec4(0.149f, 0.125f, 0.267f, 1.00f);
    const ImVec4 VaporAlt    = ImVec4(0.239f, 0.125f, 0.314f, 1.00f);
    const ImVec4 VaporSurf   = ImVec4(0.361f, 0.188f, 0.565f, 1.00f);
    const ImVec4 NeonGlow    = ImVec4(1.000f, 0.392f, 0.784f, 0.20f);
    const ImVec4 NeonVL      = ImVec4(0.392f, 0.784f, 1.000f, 0.40f);
    const ImVec4 VaporDark   = ImVec4(0.239f, 0.125f, 0.314f, 1.00f);
    const ImVec4 VaporMid    = ImVec4(0.361f, 0.188f, 0.565f, 1.00f);
    const ImVec4 VaporLit    = ImVec4(0.482f, 0.251f, 0.690f, 1.00f);
    const ImVec4 Accent      = ImVec4(1.000f, 0.392f, 0.784f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.392f, 0.784f, 1.000f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.608f, 0.220f, 0.690f, 1.00f);
    const ImVec4 AccentLight = ImVec4(1.000f, 0.600f, 0.890f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.129f, 0.106f, 0.231f, 1.00f);
    const ImVec4 TextBright  = ImVec4(1.000f, 0.878f, 1.000f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.788f, 0.627f, 0.812f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.518f, 0.388f, 0.553f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(1.000f, 0.922f, 1.000f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.239f, 0.125f, 0.314f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.392f, 0.784f, 1.000f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(1.000f, 0.392f, 0.784f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.608f, 0.220f, 0.690f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.055f, 0.039f, 0.098f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.043f, 0.031f, 0.078f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.031f, 0.020f, 0.059f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.031f, 0.020f, 0.059f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.031f, 0.020f, 0.059f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = VaporBg;
    t.ContentPanel.TabHovered = VaporAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = VaporDark; t.ContentPanel.ButtonHovered = VaporMid;
    t.ContentPanel.ButtonActive = AccentDarker; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = VaporBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = VaporBg; t.Window.TitleBarActive = VaporAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = VaporDark;
    t.Window.ButtonHovered = VaporMid; t.Window.ButtonActive = AccentDarker;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = NeonGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = VaporDark; t.TrackTable.HeaderTextColor = AccentDark;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = VaporSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = AccentDark;
    t.TrackTable.HeaderTextArtist = AccentDark; t.TrackTable.HeaderTextAlbum = AccentDark;
    t.TrackTable.HeaderTextExtension = AccentDark; t.TrackTable.HeaderTextDuration = AccentDark;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = VaporBg;
    t.TrackTable.RowHovered = NeonVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = VaporDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepVapor; t.TrackTable.ScrollbarGrab = VaporDark;
    t.TrackTable.ScrollbarGrabHovered = VaporMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepVapor; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(VaporDark.x, VaporDark.y, VaporDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = AccentDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(1.000f, 0.878f, 1.000f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = VaporDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = VaporBg; t.AlbumArtBox.BackgroundColorHovered = VaporAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(AccentDark.x, AccentDark.y, AccentDark.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.031f, 0.020f, 0.059f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = VaporAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = VaporBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = VaporDark; t.PlayerBar.ButtonHovered = VaporMid;
    t.PlayerBar.ButtonActive = AccentDarker; t.PlayerBar.ButtonPrimary = VaporDark;
    t.PlayerBar.ButtonPrimaryHovered = VaporMid; t.PlayerBar.ButtonPrimaryActive = AccentDarker;
    t.PlayerBar.SliderTrack = BorderWin; t.PlayerBar.SliderGrab = Accent; t.PlayerBar.SliderGrabActive = AccentLight;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = SearchBg; t.ContextMenu.BorderColor = BorderWin;
    t.ContextMenu.TextColor = TextBright; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = Accent; t.ContextMenu.HoverTextColor = Void;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

    return t;
}
} // namespace moosic