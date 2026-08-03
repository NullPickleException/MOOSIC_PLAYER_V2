//==============================================================================
// GameboyInspiredTheme.h
//==============================================================================
// Gameboy inspired - olive green, darker LCD green, pale phosphor
// Palette: #1A2A0A (dark olive), #2D4A10 (Gameboy green), #4A7A18 (bright olive),
//          #8BC834 (LCD lime)
// 60% Dark olive green (#0A1400 → #2D4A10)
// 25% Gameboy green surfaces (#4A7A18, #8BC834)
// 10% LCD lime accent (#8BC834)
// 5% Pale green text (#D0F0C0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateGameboyInspiredTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.039f, 0.078f, 0.020f, 1.00f);
    const ImVec4 DeepGB      = ImVec4(0.102f, 0.165f, 0.039f, 1.00f);
    const ImVec4 GBBg        = ImVec4(0.176f, 0.290f, 0.063f, 1.00f);
    const ImVec4 GBAlt       = ImVec4(0.290f, 0.478f, 0.094f, 1.00f);
    const ImVec4 GBSurf      = ImVec4(0.420f, 0.620f, 0.157f, 1.00f);
    const ImVec4 GBGlow      = ImVec4(0.545f, 0.784f, 0.204f, 0.18f);
    const ImVec4 GBVL        = ImVec4(0.545f, 0.784f, 0.204f, 0.45f);
    const ImVec4 GBDark      = ImVec4(0.176f, 0.290f, 0.063f, 1.00f);
    const ImVec4 GBMid       = ImVec4(0.290f, 0.478f, 0.094f, 1.00f);
    const ImVec4 GBLit       = ImVec4(0.420f, 0.620f, 0.157f, 1.00f);
    const ImVec4 Accent      = ImVec4(0.545f, 0.784f, 0.204f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.420f, 0.620f, 0.157f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.290f, 0.478f, 0.094f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.710f, 0.890f, 0.404f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.141f, 0.247f, 0.051f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.816f, 0.941f, 0.753f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.580f, 0.722f, 0.467f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.373f, 0.502f, 0.278f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.878f, 0.965f, 0.831f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.176f, 0.290f, 0.063f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.420f, 0.620f, 0.157f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.545f, 0.784f, 0.204f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.290f, 0.478f, 0.094f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.027f, 0.055f, 0.012f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.020f, 0.043f, 0.008f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.016f, 0.031f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.016f, 0.031f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.016f, 0.031f, 0.004f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = GBBg;
    t.ContentPanel.TabHovered = GBAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = GBDark; t.ContentPanel.ButtonHovered = GBMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = GBBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = GBBg; t.Window.TitleBarActive = GBAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = GBDark;
    t.Window.ButtonHovered = GBMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = GBGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = GBDark; t.TrackTable.HeaderTextColor = AccentLight;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = GBSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = AccentLight;
    t.TrackTable.HeaderTextArtist = AccentLight; t.TrackTable.HeaderTextAlbum = AccentLight;
    t.TrackTable.HeaderTextExtension = AccentLight; t.TrackTable.HeaderTextDuration = AccentLight;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = GBBg;
    t.TrackTable.RowHovered = GBVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = GBDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepGB; t.TrackTable.ScrollbarGrab = GBDark;
    t.TrackTable.ScrollbarGrabHovered = GBMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepGB; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(GBDark.x, GBDark.y, GBDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = GBDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.816f, 0.941f, 0.753f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = GBDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = GBBg; t.AlbumArtBox.BackgroundColorHovered = GBAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.016f, 0.031f, 0.004f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = GBAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = GBBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = GBDark; t.PlayerBar.ButtonHovered = GBMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = GBDark;
    t.PlayerBar.ButtonPrimaryHovered = GBMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
    t.PlayerBar.SliderTrack = BorderWin; t.PlayerBar.SliderGrab = Accent; t.PlayerBar.SliderGrabActive = AccentLight;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = SearchBg; t.ContextMenu.BorderColor = BorderWin;
    t.ContextMenu.TextColor = TextBright; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = Accent; t.ContextMenu.HoverTextColor = Void;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic