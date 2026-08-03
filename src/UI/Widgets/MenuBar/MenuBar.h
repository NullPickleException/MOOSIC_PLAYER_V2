//==============================================================================
// UI/Widgets/MenuBar/MenuBar.h
//==============================================================================

#pragma once

#include <imgui.h>
#include <string>
#include <functional>

namespace moosic
{

struct MenuBarTheme
{
    ImVec4 BackgroundColor = ImVec4(0.15f, 0.15f, 0.17f, 1.0f);
    ImVec4 TextColor       = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
    ImVec4 TextHovered     = ImVec4(1.00f, 1.00f, 1.00f, 1.0f);

    // Top-level menu titles + dropdown rows
    ImVec4 HighlightColor       = ImVec4(0.26f, 0.59f, 0.98f, 0.80f); // Header / open
    ImVec4 HighlightHovered     = ImVec4(0.26f, 0.59f, 0.98f, 1.00f); // HeaderHovered
    ImVec4 HighlightActive      = ImVec4(0.20f, 0.50f, 0.90f, 1.00f); // HeaderActive

    ImVec4 PopupBackground = ImVec4(0.12f, 0.12f, 0.14f, 1.0f);
    ImVec4 BorderColor     = ImVec4(0.30f, 0.30f, 0.35f, 1.0f);

    float Height = 19.6f;
};

class MenuBar
{
public:
    MenuBar() = default;
    
    void ApplyTheme(const MenuBarTheme& theme) { m_theme = theme; }
    const MenuBarTheme& GetTheme() const { return m_theme; }
    float GetHeight() const;
    
    // Callbacks
    std::function<void()> OnFileOpen;
    std::function<void()> OnFileExit;
    std::function<void(int)> OnViewLayout;
    std::function<void()> OnPlaybackPlay;
    std::function<void()> OnPlaybackPause;
    std::function<void()> OnPlaybackStop;
    std::function<void()> OnNextTrack;
    std::function<void()> OnPreviousTrack;
    std::function<void()> OnHelpAbout;

    // Draw takes what it needs from UI
    void Draw(float titleBarHeight, float borderThickness, const ImVec4& borderColor, const ImVec4& bgColor);

private:
    MenuBarTheme m_theme;
};

} // namespace moosic