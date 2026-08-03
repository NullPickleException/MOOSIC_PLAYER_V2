//==============================================================================
// AtariInspiredTheme.h
//==============================================================================
// Atari 2600 inspired - black console, wood grain, orange-red accents, silver
// Palette: #1A1A1A (console black), #8B6914 (wood grain), #FF4D00 (Atari orange-red),
//          #C0C0C0 (silver switches), #FFCC00 (cartridge yellow)
// 55% Black console body (#0A0A0A → #1A1A1A)
// 25% Wood grain and orange-red surfaces (#8B6914, #FF4D00)
// 15% Atari orange-red accent (#FF4D00)
// 5% Silver text (#C0C0C0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateAtariInspiredTheme() {
    Theme t;

    const ImVec4 Black       = ImVec4(0.039f, 0.039f, 0.039f, 1.00f);
    const ImVec4 DarkGray    = ImVec4(0.102f, 0.102f, 0.102f, 1.00f);
    const ImVec4 MidGray     = ImVec4(0.165f, 0.165f, 0.165f, 1.00f);
    const ImVec4 WoodGrain   = ImVec4(0.545f, 0.412f, 0.078f, 1.00f);
    const ImVec4 AtariOrange = ImVec4(1.000f, 0.302f, 0.000f, 1.00f);
    const ImVec4 Silver      = ImVec4(0.753f, 0.753f, 0.753f, 1.00f);
    const ImVec4 CartYellow  = ImVec4(1.000f, 0.800f, 0.000f, 1.00f);
    const ImVec4 OrangeGlow  = ImVec4(1.000f, 0.302f, 0.000f, 0.18f);
    const ImVec4 WoodVL      = ImVec4(0.545f, 0.412f, 0.078f, 0.45f);
    const ImVec4 OrangeVL    = ImVec4(1.000f, 0.302f, 0.000f, 0.50f);
    const ImVec4 WoodDark    = ImVec4(0.420f, 0.318f, 0.059f, 1.00f);
    const ImVec4 OrangeDark  = ImVec4(0.749f, 0.224f, 0.000f, 1.00f);
    const ImVec4 WoodLit     = ImVec4(0.682f, 0.518f, 0.133f, 1.00f);
    const ImVec4 OrangeLit   = ImVec4(1.000f, 0.502f, 0.149f, 1.00f);

    const ImVec4 Void        = Black;
    const ImVec4 Accent      = AtariOrange;
    const ImVec4 AccentDark  = OrangeDark;
    const ImVec4 AccentDarker= WoodDark;
    const ImVec4 AccentLight = CartYellow;
    const ImVec4 SearchBg    = DarkGray;
    const ImVec4 TextBright  = Silver;
    const ImVec4 TextMuted   = ImVec4(0.659f, 0.659f, 0.659f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.455f, 0.455f, 0.455f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.910f, 0.910f, 0.910f, 1.00f);
    const ImVec4 BorderSubtle= MidGray;
    const ImVec4 BorderWin   = AtariOrange;
    const ImVec4 BorderTitle = CartYellow;
    const ImVec4 BorderBot   = WoodGrain;
    const ImVec4 PlayerBg    = ImVec4(0.020f, 0.020f, 0.020f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.012f, 0.012f, 0.012f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.008f, 0.008f, 0.008f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = Silver; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = AtariOrange; t.ContentPanel.TabInactive = MidGray;
    t.ContentPanel.TabHovered = WoodGrain; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Black; t.ContentPanel.TabTextInactive = Silver;
    t.ContentPanel.ButtonNormal = WoodGrain; t.ContentPanel.ButtonHovered = WoodLit;
    t.ContentPanel.ButtonActive = AtariOrange; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = MidGray; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = MidGray; t.Window.TitleBarActive = WoodGrain;
    t.Window.HeaderText = Silver; t.Window.TextPrimary = Silver;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = AtariOrange; t.Window.ButtonNormal = WoodGrain;
    t.Window.ButtonHovered = WoodLit; t.Window.ButtonActive = AtariOrange;
    t.Window.ProgressBar = AtariOrange; t.Window.PlayingHighlight = OrangeGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = WoodGrain; t.TrackTable.HeaderTextColor = Black;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = WoodLit;
    t.TrackTable.HeaderActive = AtariOrange; t.TrackTable.HeaderTextTitle = Black;
    t.TrackTable.HeaderTextArtist = Black; t.TrackTable.HeaderTextAlbum = Black;
    t.TrackTable.HeaderTextExtension = Black; t.TrackTable.HeaderTextDuration = Black;
    t.TrackTable.RowDefault = Black; t.TrackTable.RowDefaultAlt = MidGray;
    t.TrackTable.RowHovered = OrangeVL; t.TrackTable.RowClicked = OrangeDark;
    t.TrackTable.RowSelected = WoodGrain; t.TrackTable.RowPlaying = AtariOrange;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = Silver; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Black; t.TrackTable.TextPlaying = Black;
    t.TrackTable.RowTextTitle = Silver; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DarkGray; t.TrackTable.ScrollbarGrab = WoodGrain;
    t.TrackTable.ScrollbarGrabHovered = WoodLit; t.TrackTable.ScrollbarGrabActive = AtariOrange;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DarkGray; t.Visualizer.WaveformColor = AtariOrange;
    t.Visualizer.WaveformFillColor = ImVec4(AtariOrange.x, AtariOrange.y, AtariOrange.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(WoodGrain.x, WoodGrain.y, WoodGrain.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true;
    t.Visualizer.SpectrumColorLow = WoodGrain;
    t.Visualizer.SpectrumColorMid = AtariOrange;
    t.Visualizer.SpectrumColorHigh = CartYellow;
    t.Visualizer.SpectrumColorPeak = Silver;
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = WoodGrain;
    t.Visualizer.HighFreqTint = AtariOrange; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = WoodGrain; t.AlbumArtBox.BorderColorHovered = AtariOrange;
    t.AlbumArtBox.BorderColorClicked = CartYellow; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = MidGray; t.AlbumArtBox.BackgroundColorHovered = WoodGrain;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(AtariOrange.x, AtariOrange.y, AtariOrange.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(AtariOrange.x, AtariOrange.y, AtariOrange.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Silver;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 0.95f);
    t.AlbumArtLightbox.BorderColor = CartYellow; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = AtariOrange; t.AlbumArtLightbox.TitleColor = Silver;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = AtariOrange; t.SearchBar.textColor = Silver;
    t.SearchBar.highlightTextColor = CartYellow; t.SearchBar.rowHoverColor = WoodGrain;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = MidGray;
    t.SearchBar.inputBorderColor = AtariOrange; t.SearchBar.inputTextColor = Silver;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = Silver; t.PlayerBar.TextSecondary = TextMuted;
    t.PlayerBar.ButtonNormal = WoodGrain; t.PlayerBar.ButtonHovered = WoodLit;
    t.PlayerBar.ButtonActive = AtariOrange;
    t.PlayerBar.ButtonPrimary = AtariOrange; t.PlayerBar.ButtonPrimaryHovered = OrangeLit;
    t.PlayerBar.ButtonPrimaryActive = CartYellow;
    t.PlayerBar.SliderTrack = WoodGrain; t.PlayerBar.SliderGrab = AtariOrange; t.PlayerBar.SliderGrabActive = CartYellow;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = DarkGray; t.ContextMenu.BorderColor = AtariOrange;
    t.ContextMenu.TextColor = Silver; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = WoodGrain; t.ContextMenu.HoverTextColor = Black;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic