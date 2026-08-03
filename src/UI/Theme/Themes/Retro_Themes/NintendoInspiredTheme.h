//==============================================================================
// NintendoInspiredTheme.h
//==============================================================================
// NES inspired - two-tone gray, black stripe, red accents, NES blue buttons
// Palette: #1A1A1A (black), #404040 (dark gray), #C0C0C0 (light gray),
//          #C80000 (NES red stripe), #0000CC (NES blue buttons)
// 55% Two-tone gray and black (#000000 → #404040)
// 25% NES red and blue surfaces (#C80000, #0000CC)
// 10% NES red stripe accent (#C80000)
// 10% Light gray text (#C0C0C0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateNintendoInspiredTheme() {
    Theme t;

    const ImVec4 Black       = ImVec4(0.039f, 0.039f, 0.039f, 1.00f);
    const ImVec4 DarkGray    = ImVec4(0.251f, 0.251f, 0.251f, 1.00f);
    const ImVec4 MidGray     = ImVec4(0.165f, 0.165f, 0.165f, 1.00f);
    const ImVec4 LightGray   = ImVec4(0.753f, 0.753f, 0.753f, 1.00f);
    const ImVec4 NESRed      = ImVec4(0.784f, 0.000f, 0.000f, 1.00f);
    const ImVec4 NESBlue     = ImVec4(0.000f, 0.000f, 0.800f, 1.00f);
    const ImVec4 White       = ImVec4(0.910f, 0.910f, 0.910f, 1.00f);
    const ImVec4 RedGlow     = ImVec4(0.784f, 0.000f, 0.000f, 0.18f);
    const ImVec4 RedVL       = ImVec4(0.784f, 0.000f, 0.000f, 0.50f);
    const ImVec4 BlueGlow    = ImVec4(0.000f, 0.000f, 0.800f, 0.45f);
    const ImVec4 RedDark     = ImVec4(0.580f, 0.000f, 0.000f, 1.00f);
    const ImVec4 BlueDark    = ImVec4(0.000f, 0.000f, 0.549f, 1.00f);
    const ImVec4 RedLit      = ImVec4(0.902f, 0.149f, 0.149f, 1.00f);
    const ImVec4 BlueLit     = ImVec4(0.188f, 0.188f, 0.878f, 1.00f);

    const ImVec4 Void        = Black;
    const ImVec4 Accent      = NESRed;
    const ImVec4 AccentDark  = RedDark;
    const ImVec4 AccentDarker= MidGray;
    const ImVec4 AccentLight = LightGray;
    const ImVec4 SearchBg    = ImVec4(0.102f, 0.102f, 0.102f, 1.00f);
    const ImVec4 TextBright  = LightGray;
    const ImVec4 TextMuted   = ImVec4(0.580f, 0.580f, 0.580f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.388f, 0.388f, 0.388f, 1.00f);
    const ImVec4 TextWhite   = White;
    const ImVec4 BorderSubtle= DarkGray;
    const ImVec4 BorderWin   = NESRed;
    const ImVec4 BorderTitle = LightGray;
    const ImVec4 BorderBot   = Black;
    const ImVec4 PlayerBg    = ImVec4(0.020f, 0.020f, 0.020f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.012f, 0.012f, 0.012f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.008f, 0.008f, 0.008f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = NESRed;
    t.TitleBar.TitleTextColor = LightGray; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = NESRed; t.ContentPanel.TabInactive = MidGray;
    t.ContentPanel.TabHovered = DarkGray; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = White; t.ContentPanel.TabTextInactive = LightGray;
    t.ContentPanel.ButtonNormal = DarkGray; t.ContentPanel.ButtonHovered = NESBlue;
    t.ContentPanel.ButtonActive = NESRed; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = MidGray; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = MidGray; t.Window.TitleBarActive = DarkGray;
    t.Window.HeaderText = LightGray; t.Window.TextPrimary = LightGray;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = NESRed; t.Window.ButtonNormal = DarkGray;
    t.Window.ButtonHovered = NESBlue; t.Window.ButtonActive = NESRed;
    t.Window.ProgressBar = NESRed; t.Window.PlayingHighlight = RedGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = DarkGray; t.TrackTable.HeaderTextColor = LightGray;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = NESBlue;
    t.TrackTable.HeaderActive = NESRed; t.TrackTable.HeaderTextTitle = LightGray;
    t.TrackTable.HeaderTextArtist = LightGray; t.TrackTable.HeaderTextAlbum = LightGray;
    t.TrackTable.HeaderTextExtension = LightGray; t.TrackTable.HeaderTextDuration = LightGray;
    t.TrackTable.RowDefault = Black; t.TrackTable.RowDefaultAlt = MidGray;
    t.TrackTable.RowHovered = RedVL; t.TrackTable.RowClicked = RedDark;
    t.TrackTable.RowSelected = DarkGray; t.TrackTable.RowPlaying = NESRed;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = LightGray; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = White; t.TrackTable.TextPlaying = White;
    t.TrackTable.RowTextTitle = LightGray; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = MidGray; t.TrackTable.ScrollbarGrab = DarkGray;
    t.TrackTable.ScrollbarGrabHovered = NESBlue; t.TrackTable.ScrollbarGrabActive = NESRed;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = Black; t.Visualizer.WaveformColor = NESRed;
    t.Visualizer.WaveformFillColor = ImVec4(NESRed.x, NESRed.y, NESRed.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(DarkGray.x, DarkGray.y, DarkGray.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true;
    t.Visualizer.SpectrumColorLow = DarkGray;
    t.Visualizer.SpectrumColorMid = NESRed;
    t.Visualizer.SpectrumColorHigh = NESBlue;
    t.Visualizer.SpectrumColorPeak = LightGray;
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = DarkGray;
    t.Visualizer.HighFreqTint = NESRed; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = DarkGray; t.AlbumArtBox.BorderColorHovered = NESRed;
    t.AlbumArtBox.BorderColorClicked = NESBlue; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = MidGray; t.AlbumArtBox.BackgroundColorHovered = DarkGray;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(NESRed.x, NESRed.y, NESRed.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(NESRed.x, NESRed.y, NESRed.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = White;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 0.95f);
    t.AlbumArtLightbox.BorderColor = LightGray; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = NESRed; t.AlbumArtLightbox.TitleColor = LightGray;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = DarkGray; t.SearchBar.textColor = LightGray;
    t.SearchBar.highlightTextColor = NESRed; t.SearchBar.rowHoverColor = DarkGray;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = MidGray;
    t.SearchBar.inputBorderColor = DarkGray; t.SearchBar.inputTextColor = LightGray;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = LightGray; t.PlayerBar.TextSecondary = TextMuted;
    t.PlayerBar.ButtonNormal = DarkGray; t.PlayerBar.ButtonHovered = NESBlue;
    t.PlayerBar.ButtonActive = NESRed;
    t.PlayerBar.ButtonPrimary = NESRed; t.PlayerBar.ButtonPrimaryHovered = RedLit;
    t.PlayerBar.ButtonPrimaryActive = NESBlue;
    t.PlayerBar.SliderTrack = DarkGray; t.PlayerBar.SliderGrab = NESRed; t.PlayerBar.SliderGrabActive = NESBlue;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = MidGray; t.ContextMenu.BorderColor = DarkGray;
    t.ContextMenu.TextColor = LightGray; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = NESRed; t.ContextMenu.HoverTextColor = White;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic