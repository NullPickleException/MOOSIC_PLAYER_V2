//==============================================================================
// TitleBar.h
//==============================================================================
#pragma once

#include <SDL.h>
#include <imgui.h>
#include <string>
#include <functional>
#include <vector>

namespace moosic
{

    struct TitleBarTheme
    {
        // ── Background ──
        ImVec4 BackgroundColor = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        ImVec4 BackgroundColorActive = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        ImVec4 BackgroundColorInactive = ImVec4(0.15f, 0.15f, 0.15f, 0.85f);
        float BackgroundOpacity = 1.0f;

        // ── Bottom Border ──
        bool ShowBottomBorder = true;
        ImVec4 BottomBorderColor = ImVec4(1.0f, 1.0f, 1.0f, 0.12f);
        float BottomBorderThickness = 1.0f;

        // ── Window Border ──
        bool ShowWindowBorder = true;
        ImVec4 WindowBorderColor = ImVec4(0.459f, 0.671f, 0.851f, 0.60f);
        float WindowBorderThickness = 1.0f;
        float WindowBorderRounding = 0.0f;

        // ── Accent Line ──
        bool ShowAccentLine = false;
        ImVec4 AccentLineColor = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);
        float AccentLineThickness = 2.0f;

        // ── Title Text ──
        ImVec4 TitleTextColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 TitleTextColorInactive = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
        float TitleOffsetX = 12.0f;
        std::string TitleText = "MOOSIC PLAYER";

        // ── Logo ──
        bool ShowLogo = true;
        float LogoSize = 24.0f;
        float LogoPaddingLeft = 10.0f;
        float LogoPaddingRight = 8.0f;
        float LogoScale = 1.00f; 

        // ── Window Buttons ──
        float ButtonWidth = 46.0f;
        float ButtonIconSize = 1.5f;

        ImVec4 MinimizeButtonColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 MinimizeButtonHoverBg = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

        ImVec4 MaximizeButtonColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 MaximizeButtonHoverBg = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

        ImVec4 CloseButtonColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 CloseButtonHoverBg = ImVec4(0.86f, 0.20f, 0.20f, 0.78f);

        bool ShowCustomButtons = false;
        ImVec4 CustomButtonColor = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
        ImVec4 CustomButtonHoverBg = ImVec4(1.0f, 1.0f, 1.0f, 0.16f);

        // ── Layout ──
        float Height = 40.0f;
        float ResizeBorderWidth = 8.0f;

        int MinWindowWidth = 590;
        int MinWindowHeight = 440;

        //--------------------------------------------------------------------------
        // Classic 2000s Title Bar Effects (default: off)
        //--------------------------------------------------------------------------
        bool UseTitleBarGradient = false;
        ImVec4 TitleBarGradientTop = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        ImVec4 TitleBarGradientBottom = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);

        bool UseTitleBarGloss = false;
        float TitleBarGlossIntensity = 0.0f;
        ImVec4 TitleBarGlossColor = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);

        bool UseTitleBarBevel = false;
        float TitleBarBevelThickness = 0.0f;
        ImVec4 TitleBarBevelLight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
        ImVec4 TitleBarBevelDark = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    };

    class TitleBar
    {
    public:
        TitleBar();
        ~TitleBar();

        void Initialize(SDL_Window *window);
        void ApplyTheme(const TitleBarTheme &theme) { m_theme = theme; }
        const TitleBarTheme &GetTheme() const { return m_theme; }

        bool LoadLogo(const std::string &path);
        void ClearLogo();
        void SetTitle(const std::string &title) { m_theme.TitleText = title; }

        using CustomButtonCallback = std::function<void(int buttonIndex)>;
        void SetCustomButtons(const std::vector<std::string> &labels, CustomButtonCallback callback);

        void Render();
        bool IsMaximized() const { return m_isMaximized; }

    private:
        static SDL_HitTestResult HitTestCallback(SDL_Window *, const SDL_Point *, void *data);
        SDL_HitTestResult HitTest(const SDL_Point *area);

        SDL_Window *m_window = nullptr;
        SDL_Renderer *m_renderer = nullptr;
        TitleBarTheme m_theme;

        SDL_Texture *m_logoTexture = nullptr;
        int m_logoWidth = 0;
        int m_logoHeight = 0;

        bool m_isMaximized = false;
        bool m_isFocused = true;

        std::vector<std::string> m_customButtonLabels;
        CustomButtonCallback m_customButtonCallback;
    };

} // namespace moosic