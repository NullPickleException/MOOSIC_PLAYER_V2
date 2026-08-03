//==============================================================================
// TronTheme.h
//==============================================================================
// Tron - electric blue glow lines on pure black grid
// 60% Pure black (#000510 → #0A1020)
// 25% Dark blue surfaces (#103050, #184870)
// 10% Electric blue accent (#00A8FF)
// 5% Pale blue glow text (#DDF0FF)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateTronTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.000f, 0.020f, 0.063f, 1.00f);
    const ImVec4 DeepTron    = ImVec4(0.039f, 0.063f, 0.125f, 1.00f);
    const ImVec4 TronBg      = ImVec4(0.063f, 0.102f, 0.188f, 1.00f);
    const ImVec4 TronAlt     = ImVec4(0.063f, 0.188f, 0.314f, 1.00f);
    const ImVec4 TronSurf    = ImVec4(0.094f, 0.282f, 0.439f, 1.00f);
    const ImVec4 NeonGlow    = ImVec4(0.000f, 0.659f, 1.000f, 0.20f);
    const ImVec4 NeonVL      = ImVec4(0.000f, 0.659f, 1.000f, 0.50f);
    const ImVec4 TronDark    = ImVec4(0.063f, 0.188f, 0.314f, 1.00f);
    const ImVec4 TronMid     = ImVec4(0.094f, 0.282f, 0.439f, 1.00f);
    const ImVec4 TronLit     = ImVec4(0.125f, 0.373f, 0.565f, 1.00f);
    const ImVec4 Accent      = ImVec4(0.000f, 0.659f, 1.000f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.000f, 0.502f, 0.808f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.000f, 0.373f, 0.608f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.298f, 0.812f, 1.000f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.047f, 0.082f, 0.161f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.867f, 0.941f, 1.000f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.627f, 0.722f, 0.812f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.388f, 0.482f, 0.580f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.910f, 0.965f, 1.000f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.063f, 0.188f, 0.314f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.000f, 0.502f, 0.808f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.000f, 0.659f, 1.000f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.000f, 0.373f, 0.608f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.000f, 0.012f, 0.043f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.000f, 0.008f, 0.035f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.000f, 0.004f, 0.024f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.000f, 0.004f, 0.024f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.004f, 0.024f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = TronBg;
    t.ContentPanel.TabHovered = TronAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = TronDark; t.ContentPanel.ButtonHovered = TronMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = TronBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = TronBg; t.Window.TitleBarActive = TronAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = TronDark;
    t.Window.ButtonHovered = TronMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = NeonGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = TronDark; t.TrackTable.HeaderTextColor = Accent;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = TronSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = Accent;
    t.TrackTable.HeaderTextArtist = Accent; t.TrackTable.HeaderTextAlbum = Accent;
    t.TrackTable.HeaderTextExtension = Accent; t.TrackTable.HeaderTextDuration = Accent;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = TronBg;
    t.TrackTable.RowHovered = NeonVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = TronDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepTron; t.TrackTable.ScrollbarGrab = TronDark;
    t.TrackTable.ScrollbarGrabHovered = TronMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepTron; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(TronDark.x, TronDark.y, TronDark.z, 0.30f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = TronDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.867f, 0.941f, 1.000f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = TronDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.30f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = TronBg; t.AlbumArtBox.BackgroundColorHovered = TronAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.000f, 0.004f, 0.024f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = TronAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = TronBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = TronDark; t.PlayerBar.ButtonHovered = TronMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = TronDark;
    t.PlayerBar.ButtonPrimaryHovered = TronMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
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