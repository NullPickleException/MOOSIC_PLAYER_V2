//==============================================================================
// CyberpunkTheme.h
//==============================================================================
// Cyberpunk - multi-neon yellow/cyan/magenta on deep void
// 60% Deep purple-black (#0A0A14 → #1A1A2E)
// 25% Dark cyber surfaces (#2D2050, #3D2870)
// 10% Multi-neon accents (#FFFF00 yellow, #00FFFF cyan, #FF00AA magenta)
// 5% Pale neon text (#F0F0FF)
//==============================================================================

#pragma once
#include "../../Theme.h"

namespace moosic {

inline Theme CreateCyberpunkTheme() {
    Theme t;

    const ImVec4 Void        = ImVec4(0.039f, 0.039f, 0.078f, 1.00f);
    const ImVec4 DeepCyber   = ImVec4(0.102f, 0.102f, 0.180f, 1.00f);
    const ImVec4 CyberBg     = ImVec4(0.141f, 0.141f, 0.235f, 1.00f);
    const ImVec4 CyberAlt    = ImVec4(0.176f, 0.125f, 0.314f, 1.00f);
    const ImVec4 CyberSurf   = ImVec4(0.239f, 0.157f, 0.439f, 1.00f);
    const ImVec4 NeonGlow    = ImVec4(1.000f, 1.000f, 0.000f, 0.20f);
    const ImVec4 NeonVL      = ImVec4(0.000f, 1.000f, 1.000f, 0.40f);
    const ImVec4 CyberDark   = ImVec4(0.176f, 0.125f, 0.314f, 1.00f);
    const ImVec4 CyberMid    = ImVec4(0.239f, 0.157f, 0.439f, 1.00f);
    const ImVec4 CyberLit    = ImVec4(0.302f, 0.188f, 0.533f, 1.00f);
    const ImVec4 Accent      = ImVec4(1.000f, 1.000f, 0.000f, 1.00f);
    const ImVec4 AccentDark  = ImVec4(0.808f, 0.808f, 0.000f, 1.00f);
    const ImVec4 AccentDarker= ImVec4(0.608f, 0.608f, 0.000f, 1.00f);
    const ImVec4 AccentLight = ImVec4(0.400f, 1.000f, 1.000f, 1.00f);
    const ImVec4 SearchBg    = ImVec4(0.122f, 0.122f, 0.208f, 1.00f);
    const ImVec4 TextBright  = ImVec4(0.941f, 0.941f, 1.000f, 1.00f);
    const ImVec4 TextMuted   = ImVec4(0.682f, 0.682f, 0.788f, 1.00f);
    const ImVec4 TextDim     = ImVec4(0.435f, 0.435f, 0.518f, 1.00f);
    const ImVec4 TextWhite   = ImVec4(0.973f, 0.973f, 1.000f, 1.00f);
    const ImVec4 BorderSubtle= ImVec4(0.239f, 0.157f, 0.439f, 1.00f);
    const ImVec4 BorderWin   = ImVec4(1.000f, 0.000f, 0.667f, 1.00f);
    const ImVec4 BorderTitle = ImVec4(0.000f, 1.000f, 1.000f, 1.00f);
    const ImVec4 BorderBot   = ImVec4(0.608f, 0.000f, 0.408f, 1.00f);
    const ImVec4 PlayerBg    = ImVec4(0.027f, 0.027f, 0.055f, 1.00f);
    const ImVec4 WinSurround = ImVec4(0.020f, 0.020f, 0.043f, 1.00f);

    t.TitleBar.BackgroundColor = ImVec4(0.016f, 0.016f, 0.031f, 1.00f);
    t.TitleBar.BackgroundColorActive = ImVec4(0.016f, 0.016f, 0.031f, 1.00f);
    t.TitleBar.BackgroundColorInactive = ImVec4(0.016f, 0.016f, 0.031f, 0.85f);
    t.TitleBar.BackgroundOpacity = 1.0f;
    t.TitleBar.ShowBottomBorder = true; t.TitleBar.BottomBorderColor = BorderBot;
    t.TitleBar.ShowWindowBorder = true; t.TitleBar.WindowBorderColor = BorderTitle;
    t.TitleBar.ShowAccentLine = true; t.TitleBar.AccentLineColor = Accent;
    t.TitleBar.TitleTextColor = TextBright; t.TitleBar.TitleTextColorInactive = TextDim;

    t.ContentPanel.TabActive = Accent; t.ContentPanel.TabInactive = CyberBg;
    t.ContentPanel.TabHovered = CyberAlt; t.ContentPanel.TabRounding = 4.0f;
    t.ContentPanel.TabText = Void; t.ContentPanel.TabTextInactive = TextMuted;
    t.ContentPanel.ButtonNormal = CyberDark; t.ContentPanel.ButtonHovered = CyberMid;
    t.ContentPanel.ButtonActive = AccentDark; t.ContentPanel.ButtonRounding = 2.0f;
    t.ContentPanel.BorderColor = BorderWin; t.ContentPanel.TabSpacing = 4.0f; t.ContentPanel.HeaderSpacing = 4.0f;

    t.Window.WindowBg = WinSurround; t.Window.ChildBg = CyberBg; t.Window.WindowBorder = BorderWin;
    t.Window.TitleBar = CyberBg; t.Window.TitleBarActive = CyberAlt;
    t.Window.HeaderText = TextBright; t.Window.TextPrimary = TextBright;
    t.Window.TextSecondary = TextMuted; t.Window.TextDisabled = TextDim;
    t.Window.BrandText = Accent; t.Window.ButtonNormal = CyberDark;
    t.Window.ButtonHovered = CyberMid; t.Window.ButtonActive = AccentDark;
    t.Window.ProgressBar = Accent; t.Window.PlayingHighlight = NeonGlow; t.Window.SeparatorColor = BorderSubtle;

    t.TrackTable.HeaderBackground = CyberDark; t.TrackTable.HeaderTextColor = Accent;
    t.TrackTable.HeaderBorderColor = BorderWin; t.TrackTable.HeaderHovered = CyberSurf;
    t.TrackTable.HeaderActive = Accent; t.TrackTable.HeaderTextTitle = Accent;
    t.TrackTable.HeaderTextArtist = Accent; t.TrackTable.HeaderTextAlbum = Accent;
    t.TrackTable.HeaderTextExtension = Accent; t.TrackTable.HeaderTextDuration = Accent;
    t.TrackTable.RowDefault = Void; t.TrackTable.RowDefaultAlt = CyberBg;
    t.TrackTable.RowHovered = NeonVL; t.TrackTable.RowClicked = AccentDarker;
    t.TrackTable.RowSelected = CyberDark; t.TrackTable.RowPlaying = Accent;
    t.TrackTable.RowHeight = 18.0f; t.TrackTable.RowPaddingX = 4.0f; t.TrackTable.RowPaddingY = 2.0f;
    t.TrackTable.TextColor = TextBright; t.TrackTable.TextDim = TextDim;
    t.TrackTable.TextSelected = Void; t.TrackTable.TextPlaying = Void;
    t.TrackTable.RowTextTitle = TextBright; t.TrackTable.RowTextArtist = TextMuted;
    t.TrackTable.RowTextAlbum = TextMuted; t.TrackTable.RowTextExtension = TextDim;
    t.TrackTable.RowTextDuration = TextMuted; t.TrackTable.BorderColor = BorderWin;
    t.TrackTable.BorderThickness = 1.0f; t.TrackTable.ShowRowSeparators = true;
    t.TrackTable.RowSeparatorColor = ImVec4(BorderSubtle.x, BorderSubtle.y, BorderSubtle.z, 0.40f);
    t.TrackTable.ScrollbarBg = DeepCyber; t.TrackTable.ScrollbarGrab = CyberDark;
    t.TrackTable.ScrollbarGrabHovered = CyberMid; t.TrackTable.ScrollbarGrabActive = Accent;
    t.TrackTable.ScrollbarWidth = 8.0f; t.TrackTable.ScrollbarRounding = 4.0f;
    t.TrackTable.HoverFadeSpeed = 0.15f; t.TrackTable.SelectionFadeSpeed = 0.20f; t.TrackTable.ScrollSmoothing = 0.12f;
    t.TrackTable.TableRounding = 0.0f; t.TrackTable.MinColumnWidth = 30.0f;
    t.TrackTable.TitleWidth = 350.0f; t.TrackTable.ArtistWidth = 180.0f; t.TrackTable.AlbumWidth = 180.0f;
    t.TrackTable.ExtensionWidth = 50.0f; t.TrackTable.DurationWidth = 80.0f;

    t.Visualizer.BackgroundColor = DeepCyber; t.Visualizer.WaveformColor = Accent;
    t.Visualizer.WaveformFillColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.10f);
    t.Visualizer.GridColor = ImVec4(CyberDark.x, CyberDark.y, CyberDark.z, 0.25f);
    t.Visualizer.BorderColor = BorderWin; t.Visualizer.PlaceholderColor = TextDim;
    t.Visualizer.UseColorRamp = true; t.Visualizer.SpectrumColorLow = CyberDark;
    t.Visualizer.SpectrumColorMid = Accent; t.Visualizer.SpectrumColorHigh = AccentLight;
    t.Visualizer.SpectrumColorPeak = ImVec4(0.941f, 0.941f, 1.000f, 1.00f);
    t.Visualizer.ColorRampLowThreshold = 0.0f; t.Visualizer.ColorRampMidThreshold = 0.50f; t.Visualizer.ColorRampHighThreshold = 0.82f;
    t.Visualizer.UseFrequencyTint = true; t.Visualizer.LowFreqTint = CyberDark;
    t.Visualizer.HighFreqTint = Accent; t.Visualizer.FrequencyTintBlend = 0.30f;
    t.Visualizer.BarBrightnessMin = 0.45f; t.Visualizer.BarBrightnessMax = 1.25f;

    t.AlbumArtBox.BorderColor = BorderWin; t.AlbumArtBox.BorderColorHovered = Accent;
    t.AlbumArtBox.BorderColorClicked = AccentLight; t.AlbumArtBox.BorderThickness = 2.5f;
    t.AlbumArtBox.BorderThicknessHovered = 3.0f; t.AlbumArtBox.BorderRounding = 3.0f;
    t.AlbumArtBox.BackgroundColor = CyberBg; t.AlbumArtBox.BackgroundColorHovered = CyberAlt;
    t.AlbumArtBox.ShowShadow = true; t.AlbumArtBox.ShadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f);
    t.AlbumArtBox.PlaceholderTextColor = TextDim; t.AlbumArtBox.ShowHoverOverlay = true;
    t.AlbumArtBox.HoverOverlayColor = ImVec4(Accent.x, Accent.y, Accent.z, 0.12f);
    t.AlbumArtBox.ClickOverlayColor = ImVec4(1.000f, 0.000f, 0.667f, 0.22f);
    t.AlbumArtBox.ShowPlayButtonOnHover = true; t.AlbumArtBox.PlayButtonColor = Void;
    t.AlbumArtBox.PlayButtonBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.55f);

    t.AlbumArtLightbox.BackgroundColor = ImVec4(0.016f, 0.016f, 0.031f, 0.95f);
    t.AlbumArtLightbox.BorderColor = BorderTitle; t.AlbumArtLightbox.CloseButtonColor = TextMuted;
    t.AlbumArtLightbox.CloseButtonHovered = Accent; t.AlbumArtLightbox.TitleColor = TextBright;
    t.AlbumArtLightbox.ArtistColor = TextMuted; t.AlbumArtLightbox.MaxWidth = 400.0f;
    t.AlbumArtLightbox.MaxHeight = 400.0f; t.AlbumArtLightbox.BorderRounding = 4.0f;
    t.AlbumArtLightbox.BorderThickness = 1.0f; t.AlbumArtLightbox.CloseButtonSize = 24.0f;
    t.AlbumArtLightbox.Padding = 30.0f; t.AlbumArtLightbox.TitleSpacing = 12.0f; t.AlbumArtLightbox.ArtistSpacing = 8.0f;

    t.SearchBar.shadowColor = ImVec4(0.0f, 0.0f, 0.0f, 0.50f); t.SearchBar.backgroundColor = SearchBg;
    t.SearchBar.borderColor = BorderWin; t.SearchBar.textColor = TextBright;
    t.SearchBar.highlightTextColor = Accent; t.SearchBar.rowHoverColor = CyberAlt;
    t.SearchBar.separatorColor = BorderSubtle; t.SearchBar.inputBgColor = CyberBg;
    t.SearchBar.inputBorderColor = BorderWin; t.SearchBar.inputTextColor = TextBright;
    t.SearchBar.inputHintColor = TextDim;

    t.PlayerBar.TextPrimary = t.Window.TextPrimary; t.PlayerBar.TextSecondary = t.Window.TextSecondary;
    t.PlayerBar.ButtonNormal = CyberDark; t.PlayerBar.ButtonHovered = CyberMid;
    t.PlayerBar.ButtonActive = AccentDark; t.PlayerBar.ButtonPrimary = CyberDark;
    t.PlayerBar.ButtonPrimaryHovered = CyberMid; t.PlayerBar.ButtonPrimaryActive = AccentDark;
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