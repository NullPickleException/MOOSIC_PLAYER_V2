//==============================================================================
// XboxInspiredTheme.h
//==============================================================================
// Xbox inspired - deep black, signature jade green, dark charcoal
// Palette: #0A0A0A (Xbox black), #1A2A1A (dark green), #107C10 (Xbox green),
//          #5DC21E (bright jade)
// 60% Xbox black and dark green (#050505 → #1A2A1A)
// 25% Xbox green surfaces (#107C10, #5DC21E)
// 10% Xbox green accent (#107C10)
// 5% Pale green text (#D0FFD0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateXboxInspiredTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.020f, 0.020f, 0.020f, 1.00f);
    const ImVec4 DeepXbox    = ImVec4(0.063f, 0.102f, 0.063f, 1.00f);
    const ImVec4 XboxBg      = ImVec4(0.102f, 0.165f, 0.102f, 1.00f);
    const ImVec4 XboxAlt     = ImVec4(0.063f, 0.486f, 0.063f, 1.00f);
    const ImVec4 XboxSurf    = ImVec4(0.125f, 0.380f, 0.125f, 1.00f);
    const ImVec4 XboxGlow    = ImVec4(0.063f, 0.486f, 0.063f, 0.18f);
    const ImVec4 XboxVL      = ImVec4(0.063f, 0.486f, 0.063f, 0.45f);
    const ImVec4 XboxDark    = ImVec4(0.102f, 0.165f, 0.102f, 1.00f);
    const ImVec4 XboxMid     = ImVec4(0.125f, 0.380f, 0.125f, 1.00f);
    const ImVec4 XboxLit     = ImVec4(0.165f, 0.510f, 0.165f, 1.00f);
    const ImVec4 Accent      = ImVec4(0.063f, 0.486f, 0.063f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.043f, 0.349f, 0.043f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.027f, 0.251f, 0.027f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.365f, 0.761f, 0.118f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.082f, 0.141f, 0.082f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.816f, 1.000f, 0.816f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.580f, 0.761f, 0.580f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.373f, 0.518f, 0.373f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.878f, 1.000f, 0.878f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.102f, 0.165f, 0.102f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.043f, 0.349f, 0.043f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.063f, 0.486f, 0.063f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.027f, 0.251f, 0.027f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.012f, 0.012f, 0.012f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.004f, 0.004f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.004f, 0.004f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.004f, 0.004f, 0.004f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = XboxBg;
    t.ContentPanel.TabHovered = XboxAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = TextWhite; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = XboxDark; t.ContentPanel.ButtonHovered = XboxMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = XboxBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = XboxBg; t.Window.TitleBarActive = XboxAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = XboxDark;
    t.Window.ButtonHovered = XboxMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = XboxGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = XboxDark; t.TrackTable.HeaderTextColor = AccentLight;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = XboxSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = AccentLight;
    t.TrackTable.HeaderTextArtist = AccentLight; t.TrackTable.HeaderTextAlbum = AccentLight;
    t.TrackTable.HeaderTextExtension = AccentLight; t.TrackTable.HeaderTextDuration = AccentLight;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = XboxBg;
    t.TrackTable.RowHovered = XboxVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = XboxDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = TextWhite; t.TrackTable.TextPlaying = TextWhite;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepXbox; t.TrackTable.ScrollbarGrab = XboxDark;
    t.TrackTable.ScrollbarGrabHovered = XboxMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepXbox; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(XboxDark.x, XboxDark.y, XboxDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = XboxDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.816f, 1.000f, 0.816f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = XboxDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = XboxBg; t.AlbumArtBox.BackgroundColorHovered = XboxAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = TextWhite;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.004f, 0.004f, 0.004f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = XboxAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = XboxBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = XboxDark; t.PlayerBar.ButtonHovered = XboxMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = XboxDark;
    t.PlayerBar.ButtonPrimaryHovered = XboxMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
    t.PlayerBar.SliderTrack = BorderWin; t.PlayerBar.SliderGrab = Accent; t.PlayerBar.SliderGrabActive = AccentLight;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = SearchBg; t.ContextMenu.BorderColor = BorderWin;
    t.ContextMenu.TextColor = TextBright; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = Accent; t.ContextMenu.HoverTextColor = TextWhite;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic