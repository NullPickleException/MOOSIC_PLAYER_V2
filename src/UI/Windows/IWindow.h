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
    ImVec4 HeaderText = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    float HeaderSpacing = 4.0f;
    
    ImVec4 ButtonNormal = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    ImVec4 ButtonHovered = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
    ImVec4 ButtonActive = ImVec4(0.45f, 0.45f, 0.45f, 1.0f);
    float ButtonRounding = 4.0f;
    
    ImVec4 TextPrimary = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    ImVec4 TextSecondary = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
    ImVec4 TextDisabled = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    
    ImVec4 PlayingHighlight = ImVec4(0.00f, 0.70f, 0.00f, 0.80f);
    ImVec4 ProgressBar = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    ImVec4 ChildBg = ImVec4(0.12f, 0.12f, 0.14f, 1.00f);
    ImVec4 SeparatorColor = ImVec4(0.25f, 0.25f, 0.27f, 1.00f);
};

class IWindow
{
public:
    virtual ~IWindow() = default;
    virtual void Draw() = 0;
    virtual void ApplyTheme(const Theme& theme) {}  // Forward declared Theme
};

} // namespace moosic