//==============================================================================
// TitleBar.h
//==============================================================================
// Custom title bar with minimize/maximize/close + comprehensive theming
//==============================================================================

#pragma once

#include <SDL.h>
#include <imgui.h>
#include <string>
#include <functional>

namespace moosic
{

//==============================================================================
// TitleBarTheme
//==============================================================================

struct TitleBarTheme
{
    //--------------------------------------------------------------------------
    // Background
    //--------------------------------------------------------------------------

    ImVec4 BackgroundColor         = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);   // Default dark
    ImVec4 BackgroundColorActive   = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);   // When window is focused
    ImVec4 BackgroundColorInactive = ImVec4(0.15f, 0.15f, 0.15f, 0.85f);   // When window is unfocused
    float  BackgroundOpacity       = 1.0f;                                   // Overall opacity

    //--------------------------------------------------------------------------
    // Bottom Border
    //--------------------------------------------------------------------------

    bool   ShowBottomBorder        = true;
    ImVec4 BottomBorderColor       = ImVec4(1.0f, 1.0f, 1.0f, 0.12f);
    float  BottomBorderThickness   = 1.0f;

    //--------------------------------------------------------------------------
    // Top Accent Line (optional colored line at very top)
    //--------------------------------------------------------------------------

    bool   ShowAccentLine          = false;
    ImVec4 AccentLineColor         = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);
    float  AccentLineThickness     = 2.0f;

    //--------------------------------------------------------------------------
    // Title Text
    //--------------------------------------------------------------------------

    ImVec4 TitleTextColor          = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 TitleTextColorInactive  = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
    float  TitleFontScale          = 1.0f;
    float  TitleOffsetX            = 12.0f;    // Offset from left edge (or logo)
    std::string TitleText          = "MOOSIC PLAYER";

    //--------------------------------------------------------------------------
    // Logo
    //--------------------------------------------------------------------------

    bool   ShowLogo                = false;
    std::string LogoPath           = "";
    float  LogoSize                = 24.0f;    // Height of logo
    float  LogoPaddingLeft         = 10.0f;
    float  LogoPaddingRight        = 8.0f;

    //--------------------------------------------------------------------------
    // Window Control Buttons (Minimize, Maximize, Close)
    //--------------------------------------------------------------------------

    float  ButtonWidth             = 46.0f;
    float  ButtonIconSize          = 1.5f;     // Thickness of icon lines

    // Minimize
    ImVec4 MinimizeButtonColor     = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 MinimizeButtonHoverBg   = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

    // Maximize / Restore
    ImVec4 MaximizeButtonColor     = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 MaximizeButtonHoverBg   = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

    // Close
    ImVec4 CloseButtonColor        = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 CloseButtonHoverBg      = ImVec4(0.86f, 0.20f, 0.20f, 0.78f);   // Red hover

    //--------------------------------------------------------------------------
    // Custom Action Buttons (optional, left of window controls)
    //--------------------------------------------------------------------------

    bool   ShowCustomButtons       = false;
    ImVec4 CustomButtonColor       = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
    ImVec4 CustomButtonHoverBg     = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

    //--------------------------------------------------------------------------
    // Sizing
    //--------------------------------------------------------------------------

    float  Height                  = 35.0f;
    float  ResizeBorderWidth       = 8.0f;     // Width of invisible resize handles at edges
};

//==============================================================================
// TitleBar
//==============================================================================

class TitleBar
{
public:
    TitleBar();
    ~TitleBar();

    //--------------------------------------------------------------------------
    // Initialization — call once with SDL_Window
    //--------------------------------------------------------------------------

    void Initialize(SDL_Window* window);

    //--------------------------------------------------------------------------
    // Theme
    //--------------------------------------------------------------------------

    void ApplyTheme(const TitleBarTheme& theme) { m_theme = theme; }
    const TitleBarTheme& GetTheme() const { return m_theme; }

    //--------------------------------------------------------------------------
    // Logo
    //--------------------------------------------------------------------------

    bool LoadLogo(const std::string& path);
    void ClearLogo();

    //--------------------------------------------------------------------------
    // Title
    //--------------------------------------------------------------------------

    void SetTitle(const std::string& title) { m_theme.TitleText = title; }

    //--------------------------------------------------------------------------
    // Custom buttons
    //--------------------------------------------------------------------------

    using CustomButtonCallback = std::function<void(int buttonIndex)>;
    void SetCustomButtons(const std::vector<std::string>& labels, CustomButtonCallback callback);

    //--------------------------------------------------------------------------
    // Render — call at the START of your ImGui frame
    //--------------------------------------------------------------------------

    void Render();

    //--------------------------------------------------------------------------
    // State
    //--------------------------------------------------------------------------

    bool IsMaximized() const;
    bool IsWindowFocused() const { return m_isFocused; }

private:
    void DrawBackground();
    void DrawAccentLine();
    void DrawLogo();
    void DrawTitleText();
    void DrawCustomButtons();
    void DrawWindowControls();
    void DrawBottomBorder();

    void DrawMinimizeButton(float& xPos);
    void DrawMaximizeButton(float& xPos);
    void DrawCloseButton(float& xPos);

    // SDL Hit testing for resize
    static SDL_HitTestResult HitTestCallback(SDL_Window*, const SDL_Point*, void* data);
    SDL_HitTestResult HitTest(const SDL_Point* area);

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    TitleBarTheme m_theme;

    // Logo
    SDL_Texture* m_logoTexture = nullptr;
    int m_logoWidth = 0;
    int m_logoHeight = 0;

    // State
    bool m_isMaximized = false;
    bool m_isFocused = true;

    // Custom buttons
    std::vector<std::string> m_customButtonLabels;
    CustomButtonCallback m_customButtonCallback;
};

} // namespace moosic