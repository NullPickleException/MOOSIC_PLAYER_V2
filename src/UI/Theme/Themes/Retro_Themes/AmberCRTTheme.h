//==============================================================================
// AmberCRTTheme.h
//==============================================================================
// Amber CRT - warm phosphor glow on dark screen
// 60% Deep screen black (#0A0800 → #1A1400)
// 25% Dark amber surfaces (#3D2800, #5C3800)
// 10% Amber phosphor accent (#FFB000)
// 5% Pale amber text (#FFE8C0)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateAmberCRTTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.039f, 0.031f, 0.000f, 1.00f);
    const ImVec4 DeepAmber   = ImVec4(0.102f, 0.078f, 0.000f, 1.00f);
    const ImVec4 AmberBg     = ImVec4(0.141f, 0.106f, 0.000f, 1.00f);
    const ImVec4 AmberAlt    = ImVec4(0.239f, 0.157f, 0.000f, 1.00f);
    const ImVec4 AmberSurf   = ImVec4(0.361f, 0.220f, 0.000f, 1.00f);
    const ImVec4 CRTGlow     = ImVec4(1.000f, 0.690f, 0.000f, 0.18f);
    const ImVec4 CRTVL       = ImVec4(1.000f, 0.690f, 0.000f, 0.50f);
    const ImVec4 AmberDark   = ImVec4(0.239f, 0.157f, 0.000f, 1.00f);
    const ImVec4 AmberMid    = ImVec4(0.361f, 0.220f, 0.000f, 1.00f);
    const ImVec4 AmberLit    = ImVec4(0.482f, 0.302f, 0.000f, 1.00f);
    const ImVec4 Accent      = ImVec4(1.000f, 0.690f, 0.000f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.710f, 0.490f, 0.000f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.502f, 0.349f, 0.000f, 1.00f);
    const ImVec4 AccentLight = ImVec4(1.000f, 0.812f, 0.298f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.122f, 0.090f, 0.000f, 1.00f);
    const ImVec4 TextBright  = ImVec4(1.000f, 0.910f, 0.753f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.812f, 0.663f, 0.388f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.553f, 0.439f, 0.220f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(1.000f, 0.941f, 0.831f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.239f, 0.157f, 0.000f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(0.502f, 0.349f, 0.000f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(1.000f, 0.690f, 0.000f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.357f, 0.247f, 0.000f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.027f, 0.020f, 0.000f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.020f, 0.016f, 0.000f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.016f, 0.012f, 0.000f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.016f, 0.012f, 0.000f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.016f, 0.012f, 0.000f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = AmberBg;
    t.ContentPanel.TabHovered = AmberAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = AmberDark; t.ContentPanel.ButtonHovered = AmberMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = AmberBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = AmberBg; t.Window.TitleBarActive = AmberAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = AmberDark;
    t.Window.ButtonHovered = AmberMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = CRTGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = AmberDark; t.TrackTable.HeaderTextColor = Void;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = AmberSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = Void;
    t.TrackTable.HeaderTextArtist = Void; t.TrackTable.HeaderTextAlbum = Void;
    t.TrackTable.HeaderTextExtension = Void; t.TrackTable.HeaderTextDuration = Void;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = AmberBg;
    t.TrackTable.RowHovered = CRTVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = AmberDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepAmber; t.TrackTable.ScrollbarGrab = AmberDark;
    t.TrackTable.ScrollbarGrabHovered = AmberMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepAmber; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(AmberDark.x, AmberDark.y, AmberDark.z, 0.30f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = AmberDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(1.000f, 0.910f, 0.753f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = AmberDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = AmberBg; t.AlbumArtBox.BackgroundColorHovered = AmberAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.016f, 0.012f, 0.000f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = AmberAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = AmberBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = AmberDark; t.PlayerBar.ButtonHovered = AmberMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = AmberDark;
    t.PlayerBar.ButtonPrimaryHovered = AmberMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
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