//==============================================================================
// WindowContentPanelTheme.h
//==============================================================================

#pragma once

#include <imgui.h>

namespace moosic
{

struct WindowContentPanelTheme
{
    //--------------------------------------------------------------------------
    // Tab Colors
    //--------------------------------------------------------------------------

    ImVec4 TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    ImVec4 TabInactive = ImVec4(0.10f, 0.22f, 0.40f, 1.00f);
    ImVec4 TabHovered = ImVec4(0.18f, 0.40f, 0.70f, 1.00f);
    
    float TabRounding = 4.0f;

    //--------------------------------------------------------------------------
    // Tab Text Colors
    //--------------------------------------------------------------------------

    ImVec4 TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TabTextInactive = ImVec4(0.60f, 0.65f, 0.75f, 1.00f);

    //--------------------------------------------------------------------------
    // Button Colors
    //--------------------------------------------------------------------------

    ImVec4 ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    ImVec4 ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    ImVec4 ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    
    float ButtonRounding = 2.0f;

    //--------------------------------------------------------------------------
    // Border Colors
    //--------------------------------------------------------------------------

    ImVec4 BorderColor = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
    float BorderThickness = 2.0f;

    //--------------------------------------------------------------------------
    // Spacing
    //--------------------------------------------------------------------------

    float TabSpacing = 4.0f;
    float HeaderSpacing = 4.0f;

    //--------------------------------------------------------------------------
    // Classic 2000s Tab Effects (default: off)
    //--------------------------------------------------------------------------
    
    bool UseGlossyTabs = false;
    float TabGlossIntensity = 0.0f;
    ImVec4 TabGlossHighlight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    
    bool UseGradientTabs = false;
    ImVec4 TabGradientTop = ImVec4(0.3f, 0.3f, 0.3f, 1.00f);
    ImVec4 TabGradientBottom = ImVec4(0.1f, 0.1f, 0.1f, 1.00f);
    
    bool UseTabBevel = false;
    float TabBevelThickness = 0.0f;
    ImVec4 TabBevelLight = ImVec4(1.0f, 1.0f, 1.0f, 0.0f);
    ImVec4 TabBevelDark = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    ImVec4 TabBevelBorderColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
};

} // namespace moosic