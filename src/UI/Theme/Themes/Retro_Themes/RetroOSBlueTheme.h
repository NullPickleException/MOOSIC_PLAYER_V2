//==============================================================================
// ClassicBlueTheme.h
//==============================================================================
// Classic blue - vintage OS blue, white text, gray accents
// Palette: #0000AA (classic OS blue), #1A1A6E (dark blue border), #3D3DB8 (highlight),
//          #C8C8FF (light blue text)
// 60% Deep classic blue (#000050 → #0000AA)
// 25% Blue surfaces (#1A1A6E, #3D3DB8)
// 10% Bright blue accent (#3D3DB8)
// 5% Light blue text (#C8C8FF)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateRetroOSBlueTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.000f, 0.000f, 0.314f, 1.00f);
    const ImVec4 DeepBlue    = ImVec4(0.102f, 0.102f, 0.431f, 1.00f);
    const ImVec4 BlueBg      = ImVec4(0.000f, 0.000f, 0.667f, 1.00f);
    const ImVec4 BlueAlt     = ImVec4(0.239f, 0.239f, 0.722f, 1.00f);
    const ImVec4 BlueSurf    = ImVec4(0.322f, 0.322f, 0.784f, 1.00f);
    const ImVec4 BlueGlow    = ImVec4(0.239f, 0.239f, 0.722f, 0.18f);
    const ImVec4 BlueVL      = ImVec4(0.239f, 0.239f, 0.722f, 0.45f);
    const ImVec4 BlueDark    = ImVec4(0.000f, 0.000f, 0.667f, 1.00f);
    const ImVec4 BlueMid     = ImVec4(0.239f, 0.239f, 0.722f, 1.00f);
    const ImVec4 BlueLit     = ImVec4(0.322f, 0.322f, 0.784f, 1.00f);
    const ImVec4 Accent      = ImVec4(0.239f, 0.239f, 0.722f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.102f, 0.102f, 0.431f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.000f, 0.000f, 0.314f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.784f, 0.784f, 1.000f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.000f, 0.000f, 0.561f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.784f, 0.784f, 1.000f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.580f, 0.580f, 0.812f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.373f, 0.373f, 0.553f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.847f, 0.847f, 1.000f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.102f, 0.102f, 0.431f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.580f, 0.580f, 0.812f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.784f, 0.784f, 1.000f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.000f, 0.000f, 0.314f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.000f, 0.000f, 0.220f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.000f, 0.000f, 0.176f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.000f, 0.000f, 0.137f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.000f, 0.000f, 0.137f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.000f, 0.000f, 0.137f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextWhite; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = AccentLight; t.ContentPanel.TabInactive = BlueBg;
    t.ContentPanel.TabHovered = BlueAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = BlueDark; t.ContentPanel.ButtonHovered = BlueMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = BlueBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = BlueBg; t.Window.TitleBarActive = BlueAlt;
    t.Window.HeaderText = TextWhite; t.Window.TextPrimary = TextWhite;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = AccentLight; t.Window.ButtonNormal = BlueDark;
    t.Window.ButtonHovered = BlueMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = AccentLight; t.Window.PlayingHighlight = BlueGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = BlueDark; t.TrackTable.HeaderTextColor = TextWhite;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = BlueSurf;
    t.TrackTable.HeaderActive = AccentLight; t.TrackTable.HeaderTextTitle = TextWhite;
    t.TrackTable.HeaderTextArtist = TextWhite; t.TrackTable.HeaderTextAlbum = TextWhite;
    t.TrackTable.HeaderTextExtension = TextWhite; t.TrackTable.HeaderTextDuration = TextWhite;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = BlueBg;
    t.TrackTable.RowHovered = BlueVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = BlueDark; t.TrackTable.RowPlaying = AccentLight;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextWhite; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = TextWhite; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextWhite; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepBlue; t.TrackTable.ScrollbarGrab = BlueDark;
    t.TrackTable.ScrollbarGrabHovered = BlueMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepBlue; t.Visualizer.WaveformColor = AccentLight;
    t.Visualizer.WaveformFillColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(BlueDark.x, BlueDark.y, BlueDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = BlueDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.784f, 0.784f, 1.000f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = BlueDark;
    t.Visualizer.HighFreqTint = AccentLight; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.20f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = AccentLight;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = BlueBg; t.AlbumArtBox.BackgroundColorHovered = BlueAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(AccentLight.x, AccentLight.y, AccentLight.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = TextWhite;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.000f, 0.000f, 0.137f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = AccentLight; t.AlbumArtLightbox.TitleColor = TextWhite;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextWhite;
    t.SearchBar.highlightTextColor = AccentLight; t.SearchBar.rowHoverColor = BlueAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = BlueBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextWhite;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = TextWhite; t.PlayerBar.TextSecondary = TextMuted;
    t.PlayerBar.ButtonNormal = BlueDark; t.PlayerBar.ButtonHovered = BlueMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = BlueDark;
    t.PlayerBar.ButtonPrimaryHovered = BlueMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
    t.PlayerBar.SliderTrack = BorderWin; t.PlayerBar.SliderGrab = AccentLight; t.PlayerBar.SliderGrabActive = TextWhite;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = SearchBg; t.ContextMenu.BorderColor = BorderWin;
    t.ContextMenu.TextColor = TextWhite; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = AccentLight; t.ContextMenu.HoverTextColor = Void;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

    return t;
}
} // namespace moosic