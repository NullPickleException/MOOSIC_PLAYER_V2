//==============================================================================
// NeonLimeTheme.h
//==============================================================================
// Neon lime - electric green glow on dark void
// 60% Deep lime-black (#081005 → #1A2A0F)
// 25% Dark green surfaces (#3D6B1A, #529428)
// 10% Neon lime accent (#8CFF00)
// 5% Pale lime glow text (#E5FFCC)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateNeonLimeTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.031f, 0.063f, 0.020f, 1.00f);
    const ImVec4 DeepLime    = ImVec4(0.102f, 0.165f, 0.059f, 1.00f);
    const ImVec4 LimeBg      = ImVec4(0.133f, 0.216f, 0.078f, 1.00f);
    const ImVec4 LimeAlt     = ImVec4(0.165f, 0.267f, 0.098f, 1.00f);
    const ImVec4 LimeSurf    = ImVec4(0.196f, 0.318f, 0.118f, 1.00f);
    const ImVec4 NeonGlow    = ImVec4(0.549f, 1.000f, 0.000f, 0.20f);
    const ImVec4 NeonVL      = ImVec4(0.549f, 1.000f, 0.000f, 0.50f);
    const ImVec4 GreenDark   = ImVec4(0.239f, 0.420f, 0.102f, 1.00f);
    const ImVec4 GreenMid    = ImVec4(0.322f, 0.580f, 0.157f, 1.00f);
    const ImVec4 GreenLit    = ImVec4(0.404f, 0.710f, 0.212f, 1.00f);
    const ImVec4 Accent      = ImVec4(0.549f, 1.000f, 0.000f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.420f, 0.808f, 0.000f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.318f, 0.608f, 0.000f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.710f, 1.000f, 0.298f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.118f, 0.192f, 0.067f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.898f, 1.000f, 0.800f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.678f, 0.812f, 0.557f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.439f, 0.553f, 0.349f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.937f, 1.000f, 0.863f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.165f, 0.267f, 0.098f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.318f, 0.608f, 0.000f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.549f, 1.000f, 0.000f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.220f, 0.424f, 0.000f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.020f, 0.043f, 0.012f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.016f, 0.035f, 0.008f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.008f, 0.024f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.008f, 0.024f, 0.004f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.008f, 0.024f, 0.004f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = LimeBg;
    t.ContentPanel.TabHovered = LimeAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = GreenDark; t.ContentPanel.ButtonHovered = GreenMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = LimeBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = LimeBg; t.Window.TitleBarActive = LimeAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = GreenDark;
    t.Window.ButtonHovered = GreenMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = NeonGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = GreenDark; t.TrackTable.HeaderTextColor = Void;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = LimeSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = Void;
    t.TrackTable.HeaderTextArtist = Void; t.TrackTable.HeaderTextAlbum = Void;
    t.TrackTable.HeaderTextExtension = Void; t.TrackTable.HeaderTextDuration = Void;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = LimeBg;
    t.TrackTable.RowHovered = NeonVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = GreenDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepLime; t.TrackTable.ScrollbarGrab = GreenDark;
    t.TrackTable.ScrollbarGrabHovered = GreenMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepLime; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(GreenDark.x, GreenDark.y, GreenDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = GreenDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.898f, 1.000f, 0.800f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = GreenDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = LimeBg; t.AlbumArtBox.BackgroundColorHovered = LimeAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.008f, 0.024f, 0.004f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = LimeAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = LimeBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = GreenDark; t.PlayerBar.ButtonHovered = GreenMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = GreenDark;
    t.PlayerBar.ButtonPrimaryHovered = GreenMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
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