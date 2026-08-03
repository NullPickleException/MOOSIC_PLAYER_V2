//==============================================================================
// DOSTheme.h
//==============================================================================
// DOS - authentic black screen, white/gray text, nothing else
// Palette: #000000 (true DOS black), #2A2A2A (dark gray border), #C0C0C0 (light gray text),
//          #FFFFFF (white text), #808080 (dim text)
// 70% True DOS black (#000000 → #0A0A0A)
// 20% Dark gray surfaces (#1A1A1A, #2A2A2A)
// 5% Light gray accent (#C0C0C0)
// 5% White text (#FFFFFF)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateDOSTheme() {
    Theme t;

    const ImVec4 Black       = ImVec4(0.000f, 0.000f, 0.000f, 1.00f);
    const ImVec4 NearBlack   = ImVec4(0.039f, 0.039f, 0.039f, 1.00f);
    const ImVec4 DarkGray    = ImVec4(0.102f, 0.102f, 0.102f, 1.00f);
    const ImVec4 MidGray     = ImVec4(0.165f, 0.165f, 0.165f, 1.00f);
    const ImVec4 LightGray   = ImVec4(0.753f, 0.753f, 0.753f, 1.00f);
    const ImVec4 White       = ImVec4(1.000f, 1.000f, 1.000f, 1.00f);
    const ImVec4 OffWhite    = ImVec4(0.910f, 0.910f, 0.910f, 1.00f);
    const ImVec4 WhiteGlow   = ImVec4(1.000f, 1.000f, 1.000f, 0.12f);
    const ImVec4 WhiteVL     = ImVec4(1.000f, 1.000f, 1.000f, 0.40f);

    const ImVec4 Void        = Black;
    const ImVec4 Accent      = LightGray;
    const ImVec4 AccentDark  = MidGray;
    const ImVec4 AccentDarker= DarkGray;
    const ImVec4 AccentLight = White;
    const ImVec4 SearchBg    = DarkGray;
    const ImVec4 TextBright  = White;
    const ImVec4 TextMuted   = LightGray;
    const ImVec4 TextDim     = MidGray;
    const ImVec4 TextWhite   = White;
    const ImVec4 BorderSubtle= DarkGray;
    const ImVec4 BorderWin   = LightGray;
    const ImVec4 BorderTitle = White;
    const ImVec4 BorderBot   = DarkGray;
    const ImVec4 PlayerBg    = Black;
    const ImVec4 WinSurround = Black;

    t.TitleBar.BackgroundColor = Black;
    t.TitleBar.BackgroundColorActive = Black;
    t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.000f, 0.000f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = LightGray;
    t.TitleBar.TitleTextColor = White; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = LightGray; t.ContentPanel.TabInactive = NearBlack;
    t.ContentPanel.TabHovered = DarkGray; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Black; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = DarkGray; t.ContentPanel.ButtonHovered = MidGray;
    t.ContentPanel.ButtonActive = LightGray; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = LightGray; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = Black; t.Window.ChildBg = NearBlack; t.Window.WindowBorder = LightGray;
    t.Window.TitleBar = NearBlack; t.Window.TitleBarActive = DarkGray;
    t.Window.HeaderText = White; t.Window.TextPrimary = White;
    t.Window.TextSecondary = LightGray; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = White; t.Window.ButtonNormal = DarkGray;
    t.Window.ButtonHovered = MidGray; t.Window.ButtonActive = LightGray;
    t.Window.ProgressBar = White; t.Window.PlayingHighlight = WhiteGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = DarkGray; t.TrackTable.HeaderTextColor = White;
    t.TrackTable.HeaderBorderColor = LightGray; t.TrackTable.HeaderHovered = MidGray;
    t.TrackTable.HeaderActive = LightGray; t.TrackTable.HeaderTextTitle = White;
    t.TrackTable.HeaderTextArtist = White; t.TrackTable.HeaderTextAlbum = White;
    t.TrackTable.HeaderTextExtension = White; t.TrackTable.HeaderTextDuration = White;
    t.TrackTable.RowDefault = Black; t.TrackTable.RowDefaultAlt = NearBlack;
    t.TrackTable.RowHovered = WhiteVL; t.TrackTable.RowClicked = MidGray;
    t.TrackTable.RowSelected = DarkGray; t.TrackTable.RowPlaying = LightGray;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = White; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Black; t.TrackTable.TextPlaying = Black;
    t.TrackTable.RowTextTitle = White; t.TrackTable.RowTextArtist = LightGray;
    t.TrackTable.RowTextAlbum = LightGray; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = LightGray; t.TrackTable.BorderColor = LightGray;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(DarkGray.x, DarkGray.y, DarkGray.z, 0.40f);
    t.TrackTable.ScrollbarBg = NearBlack; t.TrackTable.ScrollbarGrab = DarkGray;
    t.TrackTable.ScrollbarGrabHovered = MidGray; t.TrackTable.ScrollbarGrabActive = LightGray;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = Black; t.Visualizer.WaveformColor = White;
    t.Visualizer.WaveformFillColor = ImVec4(1.000f, 1.000f, 1.000f, 0.08f);
    t.Visualizer.GridColor = ImVec4(DarkGray.x, DarkGray.y, DarkGray.z, 0.20f);
    t.Visualizer.BorderColor = LightGray; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true;
    t.Visualizer.SpectrumColorLow = DarkGray;
    t.Visualizer.SpectrumColorMid = LightGray;
    t.Visualizer.SpectrumColorHigh = OffWhite;
    t.Visualizer.SpectrumColorPeak = White;
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = DarkGray;
    t.Visualizer.HighFreqTint = LightGray; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.35f; t.Visualizer.BarBrightnessMax = 1.15f;

    t.AlbumArtBox.BorderColor = DarkGray; t.AlbumArtBox.BorderColorHovered = LightGray;
    t.AlbumArtBox.BorderColorClicked = White; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = NearBlack; t.AlbumArtBox.BackgroundColorHovered = DarkGray;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(1.000f, 1.000f, 1.000f, 0.10f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(1.000f, 1.000f, 1.000f, 0.18f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = White;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = Black;
    t.AlbumArtLightbox.BorderColor = White; t.AlbumArtLightbox.CloseButtonColor = LightGray;
    t.AlbumArtLightbox.CloseButtonHovered = White; t.AlbumArtLightbox.TitleColor = White;
    t.AlbumArtLightbox.ArtistColor = LightGray; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = DarkGray;
    t.SearchBar.borderColor = LightGray; t.SearchBar.textColor = White;
    t.SearchBar.highlightTextColor = White; t.SearchBar.rowHoverColor = MidGray;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = NearBlack;
    t.SearchBar.inputBorderColor = LightGray; t.SearchBar.inputTextColor = White;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = White; t.PlayerBar.TextSecondary = LightGray;
    t.PlayerBar.ButtonNormal = DarkGray; t.PlayerBar.ButtonHovered = MidGray;
    t.PlayerBar.ButtonActive = LightGray;
    t.PlayerBar.ButtonPrimary = LightGray; t.PlayerBar.ButtonPrimaryHovered = OffWhite;
    t.PlayerBar.ButtonPrimaryActive = White;
    t.PlayerBar.SliderTrack = DarkGray; t.PlayerBar.SliderGrab = LightGray; t.PlayerBar.SliderGrabActive = White;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = NearBlack; t.ContextMenu.BorderColor = LightGray;
    t.ContextMenu.TextColor = White; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = LightGray; t.ContextMenu.HoverTextColor = Black;
    t.ContextMenu.SeparatorColor = DarkGray; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic