//==============================================================================
// Commodore64InspiredTheme.h
//==============================================================================
// Commodore 64 inspired - full C64 branding: red, blue, yellow, black, white
// Palette: #B22222 (Deep Red), #0055A4 (Bright Blue), #FFCC00 (Golden Yellow),
//          #000000 (Black), #F5F5F5 (White/Off-White)
// 55% Black (#000000 → #1A1A1A)
// 25% Deep Red and Bright Blue surfaces (#B22222, #0055A4)
// 15% Golden Yellow accent (#FFCC00)
// 5% White text (#F5F5F5)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateCommodore64InspiredTheme() {
    Theme t;

    const ImVec4 Black       = ImVec4(0.000f, 0.000f, 0.000f, 1.00f);
    const ImVec4 DarkGray    = ImVec4(0.102f, 0.102f, 0.102f, 1.00f);
    const ImVec4 MidGray     = ImVec4(0.165f, 0.165f, 0.165f, 1.00f);
    const ImVec4 DeepRed     = ImVec4(0.698f, 0.133f, 0.133f, 1.00f);
    const ImVec4 BrightBlue  = ImVec4(0.000f, 0.333f, 0.643f, 1.00f);
    const ImVec4 GoldenYellow= ImVec4(1.000f, 0.800f, 0.000f, 1.00f);
    const ImVec4 White       = ImVec4(0.961f, 0.961f, 0.961f, 1.00f);
    const ImVec4 OffWhite    = ImVec4(0.910f, 0.910f, 0.910f, 1.00f);
    const ImVec4 RedGlow     = ImVec4(0.698f, 0.133f, 0.133f, 0.18f);
    const ImVec4 BlueGlow    = ImVec4(0.000f, 0.333f, 0.643f, 0.45f);
    const ImVec4 YellowGlow  = ImVec4(1.000f, 0.800f, 0.000f, 0.50f);
    const ImVec4 RedDark     = ImVec4(0.502f, 0.090f, 0.090f, 1.00f);
    const ImVec4 BlueDark    = ImVec4(0.000f, 0.239f, 0.478f, 1.00f);
    const ImVec4 RedLit      = ImVec4(0.808f, 0.239f, 0.239f, 1.00f);
    const ImVec4 BlueLit     = ImVec4(0.188f, 0.502f, 0.808f, 1.00f);
    const ImVec4 YellowDark  = ImVec4(0.749f, 0.600f, 0.000f, 1.00f);
    const ImVec4 YellowLit   = ImVec4(1.000f, 0.882f, 0.298f, 1.00f);

    const ImVec4 Void        = Black;
    const ImVec4 Accent      = GoldenYellow;
    const ImVec4 AccentDark  = YellowDark;
    const ImVec4 AccentDarker= DeepRed;
    const ImVec4 AccentLight = YellowLit;
    const ImVec4 SearchBg    = DarkGray;
    const ImVec4 TextBright  = White;
    const ImVec4 TextMuted   = OffWhite;
    const ImVec4 TextDim     = ImVec4(0.580f, 0.580f, 0.580f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.976f, 0.976f, 0.976f, 1.00f);
    const ImVec4 BorderSubtle= MidGray;
    const ImVec4 BorderWin   = DeepRed;
    const ImVec4 BorderTitle = GoldenYellow;
    const ImVec4 BorderBot   = BrightBlue;
    const ImVec4 PlayerBg    = ImVec4(0.020f, 0.020f, 0.020f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.012f, 0.012f, 0.012f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.008f, 0.008f, 0.008f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.008f, 0.008f, 0.008f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = GoldenYellow;
    t.TitleBar.TitleTextColor = White; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = GoldenYellow; t.ContentPanel.TabInactive = MidGray;
    t.ContentPanel.TabHovered = DeepRed; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Black; t.ContentPanel.TabTextInactive = White;
    t.ContentPanel.ButtonNormal = BrightBlue; t.ContentPanel.ButtonHovered = BlueLit;
    t.ContentPanel.ButtonActive = DeepRed; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = MidGray; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = MidGray; t.Window.TitleBarActive = DeepRed;
    t.Window.HeaderText = White; t.Window.TextPrimary = White;
    t.Window.TextSecondary = OffWhite; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = GoldenYellow; t.Window.ButtonNormal = BrightBlue;
    t.Window.ButtonHovered = BlueLit; t.Window.ButtonActive = DeepRed;
    t.Window.ProgressBar = GoldenYellow; t.Window.PlayingHighlight = YellowGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = BrightBlue; t.TrackTable.HeaderTextColor = White;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = BlueLit;
    t.TrackTable.HeaderActive = GoldenYellow; t.TrackTable.HeaderTextTitle = White;
    t.TrackTable.HeaderTextArtist = White; t.TrackTable.HeaderTextAlbum = White;
    t.TrackTable.HeaderTextExtension = White; t.TrackTable.HeaderTextDuration = White;
    t.TrackTable.RowDefault = Black; t.TrackTable.RowDefaultAlt = MidGray;
    t.TrackTable.RowHovered = BlueGlow; t.TrackTable.RowClicked = RedDark;
    t.TrackTable.RowSelected = BrightBlue; t.TrackTable.RowPlaying = GoldenYellow;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = White; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = White; t.TrackTable.TextPlaying = Black;
    t.TrackTable.RowTextTitle = White; t.TrackTable.RowTextArtist = OffWhite;
    t.TrackTable.RowTextAlbum = OffWhite; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = OffWhite; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DarkGray; t.TrackTable.ScrollbarGrab = BrightBlue;
    t.TrackTable.ScrollbarGrabHovered = BlueLit; t.TrackTable.ScrollbarGrabActive = GoldenYellow;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DarkGray; t.Visualizer.WaveformColor = GoldenYellow;
    t.Visualizer.WaveformFillColor = ImVec4(GoldenYellow.x, GoldenYellow.y, GoldenYellow.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(BrightBlue.x, BrightBlue.y, BrightBlue.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true;
    t.Visualizer.SpectrumColorLow = BrightBlue;
    t.Visualizer.SpectrumColorMid = DeepRed;
    t.Visualizer.SpectrumColorHigh = GoldenYellow;
    t.Visualizer.SpectrumColorPeak = White;
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = BrightBlue;
    t.Visualizer.HighFreqTint = GoldenYellow; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BrightBlue; t.AlbumArtBox.BorderColorHovered = GoldenYellow;
    t.AlbumArtBox.BorderColorClicked = DeepRed; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = MidGray; t.AlbumArtBox.BackgroundColorHovered = DeepRed;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(GoldenYellow.x, GoldenYellow.y, GoldenYellow.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(DeepRed.x, DeepRed.y, DeepRed.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = White;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.008f, 0.008f, 0.008f, 0.95f);
    t.AlbumArtLightbox.BorderColor = GoldenYellow; t.AlbumArtLightbox.CloseButtonColor = OffWhite;
    t.AlbumArtLightbox.CloseButtonHovered = DeepRed; t.AlbumArtLightbox.TitleColor = White;
    t.AlbumArtLightbox.ArtistColor = OffWhite; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BrightBlue; t.SearchBar.textColor = White;
    t.SearchBar.highlightTextColor = GoldenYellow; t.SearchBar.rowHoverColor = DeepRed;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = MidGray;
    t.SearchBar.inputBorderColor = BrightBlue; t.SearchBar.inputTextColor = White;
    t.SearchBar.inputHintColor = TextDim;

    // Multi-color Player Bar buttons
    t.PlayerBar.TextPrimary = White; t.PlayerBar.TextSecondary = OffWhite;
    t.PlayerBar.ButtonNormal = BrightBlue; t.PlayerBar.ButtonHovered = BlueLit;
    t.PlayerBar.ButtonActive = DeepRed;
    t.PlayerBar.ButtonPrimary = DeepRed; t.PlayerBar.ButtonPrimaryHovered = RedLit;
    t.PlayerBar.ButtonPrimaryActive = GoldenYellow;
    t.PlayerBar.SliderTrack = BrightBlue; t.PlayerBar.SliderGrab = GoldenYellow; t.PlayerBar.SliderGrabActive = DeepRed;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = DarkGray; t.ContextMenu.BorderColor = GoldenYellow;
    t.ContextMenu.TextColor = White; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = DeepRed; t.ContextMenu.HoverTextColor = White;
    t.ContextMenu.SeparatorColor = BrightBlue; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    return t;
}
} // namespace moosic