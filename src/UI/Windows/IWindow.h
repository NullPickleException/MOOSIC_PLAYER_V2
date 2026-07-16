//==============================================================================
// IWindow.h
//==============================================================================

#pragma once
#include <imgui.h>

namespace moosic
{

    // Forward declare Theme
    struct Theme;

    //==============================================================================
    // WindowTheme
    //==============================================================================
    struct WindowTheme
    {
        //--------------------------------------------------------------------------
        // Window Backgrounds
        //--------------------------------------------------------------------------

        ImVec4 WindowBg = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
        ImVec4 ChildBg = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
        ImVec4 WindowBorder = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);
        ImVec4 TitleBar = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
        ImVec4 TitleBarActive = ImVec4(0.20f, 0.20f, 0.22f, 1.00f);

        //--------------------------------------------------------------------------
        // Text Colors
        //--------------------------------------------------------------------------

        ImVec4 HeaderText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 TextPrimary = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        ImVec4 TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
        ImVec4 TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

        //--------------------------------------------------------------------------
        // Brand / Accent Text (for app name, headers, etc.)
        //--------------------------------------------------------------------------

        ImVec4 BrandText = ImVec4(0.459f, 0.671f, 0.851f, 1.00f);  // Blue accent

        //--------------------------------------------------------------------------
        // Button Colors
        //--------------------------------------------------------------------------

        ImVec4 ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        ImVec4 ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        ImVec4 ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

        // Changed from 4.0f to 0.0f (square buttons = basic)
        float ButtonRounding = 0.0f;

        //--------------------------------------------------------------------------
        // Misc Colors
        //--------------------------------------------------------------------------

        ImVec4 PlayingHighlight = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
        ImVec4 ProgressBar = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        ImVec4 SeparatorColor = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);

        //--------------------------------------------------------------------------
        // Spacing
        //--------------------------------------------------------------------------

        float HeaderSpacing = 4.0f;
    };

    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual void Draw() = 0;
        virtual void ApplyTheme(const WindowTheme &theme) = 0;
    };

} // namespace moosic