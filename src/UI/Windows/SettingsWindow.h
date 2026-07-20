//==============================================================================
// SettingsWindow.h
//==============================================================================
// Settings window with theme selection, visualizer mode, and other preferences
//==============================================================================

#pragma once

#include "IWindow.h"
#include "../Theme/ThemeManager.h"
#include <vector>
#include <string>
#include <functional>

namespace moosic
{

//==============================================================================
// SettingsWindow
//==============================================================================

class SettingsWindow : public IWindow
{
public:
    SettingsWindow();

    void Draw() override;
    void ApplyTheme(const WindowTheme& theme) override;

    //--------------------------------------------------------------------------
    // Theme Manager
    //--------------------------------------------------------------------------

    void SetThemeManager(ThemeManager* manager);

    //--------------------------------------------------------------------------
    // Theme Change Callback - No parameter needed, ThemeManager owns the theme
    //--------------------------------------------------------------------------

    using ThemeChangeCallback = std::function<void()>;
    void OnThemeChanged(ThemeChangeCallback callback);

    //--------------------------------------------------------------------------
    // Visualizer Mode Callback - Called when user changes visualization type
    //--------------------------------------------------------------------------

    using VisualizerModeCallback = std::function<void(int mode)>;
    void OnVisualizerModeChanged(VisualizerModeCallback callback);

private:
    //--------------------------------------------------------------------------
    // Drawing Sections
    //--------------------------------------------------------------------------

    void DrawAppearanceSection();
    void DrawThemeSelector();
    void DrawVisualizerModeSelector();
    void DrawGeneralSection();
    void DrawAudioSection();

    //--------------------------------------------------------------------------
    // Theme Management
    //--------------------------------------------------------------------------

    void ApplySelectedTheme(int index);

private:
    WindowTheme m_theme;
    ThemeManager* m_themeManager = nullptr;
    int m_selectedThemeIndex = 0;
    ThemeChangeCallback m_onThemeChanged;

    //--------------------------------------------------------------------------
    // Visualizer Mode
    //--------------------------------------------------------------------------

    int m_visualizerMode = 0; // 0=Spectrum, 1=Oscilloscope
    VisualizerModeCallback m_onVisualizerModeChanged;
};

} // namespace moosic