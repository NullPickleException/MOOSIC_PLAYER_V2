//==============================================================================
// WindowContentPanelTheme.h
//==============================================================================
// Theme definition for the content panel (tabs, borders, etc.)
// Now used by ImGui TabBar styling via UI::ApplyImGuiStyle
//==============================================================================

#pragma once

#include <imgui.h>

namespace moosic
{

//==============================================================================
// WindowContentPanelTheme
//==============================================================================

struct WindowContentPanelTheme
{
    //--------------------------------------------------------------------------
    // Tab Colors (applied to ImGuiCol_Tab, ImGuiCol_TabActive, etc.)
    //--------------------------------------------------------------------------

    ImVec4 TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);      // Selected tab
    ImVec4 TabInactive = ImVec4(0.10f, 0.22f, 0.40f, 1.00f);    // Unselected tab
    ImVec4 TabHovered = ImVec4(0.18f, 0.40f, 0.70f, 1.00f);     // Hover on any tab
    
    float TabRounding = 4.0f;                                     // Tab corner rounding

    //--------------------------------------------------------------------------
    // Tab Text Colors
    //--------------------------------------------------------------------------

    ImVec4 TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TabTextInactive = ImVec4(0.60f, 0.65f, 0.75f, 1.00f);

    //--------------------------------------------------------------------------
    // Button Colors (matching WindowTheme/IWindow)
    //--------------------------------------------------------------------------

    ImVec4 ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    ImVec4 ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    ImVec4 ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
    
    float ButtonRounding = 2.0f;

    //--------------------------------------------------------------------------
    // Border Colors (matching WindowTheme/IWindow)
    //--------------------------------------------------------------------------

    ImVec4 BorderColor = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
    float BorderThickness = 2.0f;

    //--------------------------------------------------------------------------
    // Spacing
    //--------------------------------------------------------------------------

    float TabSpacing = 4.0f;
    float HeaderSpacing = 4.0f;
};

} // namespace moosic