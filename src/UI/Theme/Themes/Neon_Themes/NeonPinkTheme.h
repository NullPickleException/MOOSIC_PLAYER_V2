//==============================================================================
// NeonPinkTheme.h
//==============================================================================
// Neon pink - electric hot pink glow on dark void
// 60% Deep pink-black (#140710 → #2A1030)
// 25% Dark magenta surfaces (#6B1A52, #942870)
// 10% Neon pink accent (#FF1493)
// 5% Pale pink glow text (#FFDDF0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateNeonPinkTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.078f, 0.027f, 0.063f, 1.00f);
    const ImVec4 DeepPink    = ImVec4(0.165f, 0.063f, 0.188f, 1.00f);
    const ImVec4 PinkBg      = ImVec4(0.216f, 0.086f, 0.247f, 1.00f);
    const ImVec4 PinkAlt     = ImVec4(0.267f, 0.110f, 0.306f, 1.00f);
    const ImVec4 PinkSurf    = ImVec4(0.318f, 0.133f, 0.365f, 1.00f);
    const ImVec4 NeonGlow    = ImVec4(1.000f, 0.078f, 0.576f, 0.20f);
    const ImVec4 NeonVL      = ImVec4(1.000f, 0.078f, 0.576f, 0.50f);
    const ImVec4 MagentaDark = ImVec4(0.420f, 0.102f, 0.322f, 1.00f);
    const ImVec4 MagentaMid  = ImVec4(0.580f, 0.157f, 0.439f, 1.00f);
    const ImVec4 MagentaLit  = ImVec4(0.710f, 0.212f, 0.557f, 1.00f);
    const ImVec4 Accent      = ImVec4(1.000f, 0.078f, 0.576f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.808f, 0.059f, 0.459f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.608f, 0.039f, 0.349f, 1.00f);
    const ImVec4 AccentLight = ImVec4(1.000f, 0.298f, 0.710f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.188f, 0.075f, 0.216f, 1.00f);
    const ImVec4 TextBright  = ImVec4(1.000f, 0.867f, 0.941f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.788f, 0.608f, 0.682f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.518f, 0.373f, 0.435f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(1.000f, 0.910f, 0.965f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.267f, 0.110f, 0.306f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.608f, 0.039f, 0.349f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(1.000f, 0.078f, 0.576f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.408f, 0.020f, 0.239f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.055f, 0.020f, 0.043f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.043f, 0.016f, 0.035f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.031f, 0.008f, 0.027f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.031f, 0.008f, 0.027f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.031f, 0.008f, 0.027f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = PinkBg;
    t.ContentPanel.TabHovered = PinkAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = TextWhite; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = MagentaDark; t.ContentPanel.ButtonHovered = MagentaMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = PinkBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = PinkBg; t.Window.TitleBarActive = PinkAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = MagentaDark;
    t.Window.ButtonHovered = MagentaMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = NeonGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = MagentaDark; t.TrackTable.HeaderTextColor = TextBright;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = PinkSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = TextBright;
    t.TrackTable.HeaderTextArtist = TextBright; t.TrackTable.HeaderTextAlbum = TextBright;
    t.TrackTable.HeaderTextExtension = TextBright; t.TrackTable.HeaderTextDuration = TextBright;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = PinkBg;
    t.TrackTable.RowHovered = NeonVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = MagentaDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = TextWhite; t.TrackTable.TextPlaying = TextWhite;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepPink; t.TrackTable.ScrollbarGrab = MagentaDark;
    t.TrackTable.ScrollbarGrabHovered = MagentaMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepPink; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(MagentaDark.x, MagentaDark.y, MagentaDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = MagentaDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(1.000f, 0.867f, 0.941f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = MagentaDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = PinkBg; t.AlbumArtBox.BackgroundColorHovered = PinkAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = TextWhite;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.031f, 0.008f, 0.027f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = PinkAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = PinkBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = MagentaDark; t.PlayerBar.ButtonHovered = MagentaMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = MagentaDark;
    t.PlayerBar.ButtonPrimaryHovered = MagentaMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
    t.PlayerBar.SliderTrack = BorderWin; t.PlayerBar.SliderGrab = Accent; t.PlayerBar.SliderGrabActive = AccentLight;
    t.PlayerBar.UsePlayerBarGradient = true; t.PlayerBar.PlayerBarGradientTop = PlayerBg;
    t.PlayerBar.PlayerBarGradientBottom = PlayerBg; t.PlayerBar.PlayerBarOpacity = 1.0f;
    t.PlayerBar.Lightbox = t.AlbumArtLightbox; t.PlayerBar.AlbumArtBox = t.AlbumArtBox; t.PlayerBar.Visualizer = t.Visualizer;

    t.ContextMenu.BackgroundColor = SearchBg; t.ContextMenu.BorderColor = BorderWin;
    t.ContextMenu.TextColor = TextBright; t.ContextMenu.TextDisabledColor = TextDim;
    t.ContextMenu.HoverColor = Accent; t.ContextMenu.HoverTextColor = TextWhite;
    t.ContextMenu.SeparatorColor = BorderSubtle; t.ContextMenu.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);

    return t;
}
} // namespace moosic