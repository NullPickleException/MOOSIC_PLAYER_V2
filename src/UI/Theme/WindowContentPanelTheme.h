//==============================================================================
// WindowContentPanelTheme.h
//==============================================================================
// Theme definition for the content panel (tabs, borders, etc.)
// Separated to avoid circular dependencies
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
    ImVec4 TabActive = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    ImVec4 TabInactive = ImVec4(0.10f, 0.22f, 0.40f, 1.00f);
    ImVec4 TabHovered = ImVec4(0.18f, 0.40f, 0.70f, 1.00f);
    ImVec4 TabText = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TabTextInactive = ImVec4(0.60f, 0.65f, 0.75f, 1.00f);
    ImVec4 BorderColor = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    float BorderThickness = 2.0f;
    float TabSpacing = 2.0f;
};

} // namespace moosic