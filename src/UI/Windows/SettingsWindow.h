//==============================================================================
// SettingsWindow.h
//==============================================================================

#pragma once

#include "IWindow.h"
#include "../Data/SettingsDataModel.h"
#include "../Theme/ThemeManager.h"
#include <vector>
#include <string>
#include <functional>

namespace moosic
{

class SettingsWindow : public IWindow
{
public:
    SettingsWindow();

    void Draw() override;
    void ApplyTheme(const WindowTheme& theme) override;

    void SetSettingsDataModel(SettingsDataModel* model);
    SettingsDataModel* GetSettingsDataModel() const { return m_settingsModel; }

    void SetThemeManager(ThemeManager* manager);

    using ThemeChangeCallback = std::function<void()>;
    void OnThemeChanged(ThemeChangeCallback callback);

    using VisualizerModeCallback = std::function<void(int mode)>;
    void OnVisualizerModeChanged(VisualizerModeCallback callback);

    using LogoChangeCallback = std::function<void(const std::string& path)>;
    void OnLogoChanged(LogoChangeCallback callback);

    // Call this once to scan available logos
    void ScanAvailableLogos();

private:
    void DrawAppearanceSection();
    void DrawThemeSelector();
    void DrawVisualizerModeSelector();
    void DrawLogoSelector();
    void DrawGeneralSection();
    void DrawAudioSection();

    void ApplySelectedTheme(int index);
    void ApplySelectedLogo(int index);

private:
    WindowTheme m_theme;
    SettingsDataModel* m_settingsModel = nullptr;
    ThemeManager* m_themeManager = nullptr;
    int m_selectedThemeIndex = 0;
    ThemeChangeCallback m_onThemeChanged;
    
    int m_visualizerMode = 0;
    VisualizerModeCallback m_onVisualizerModeChanged;

    // Logo state
    struct LogoInfo
    {
        std::string name;       // Display name (filename without extension)
        std::string path;       // Full path
    };
    std::vector<LogoInfo> m_availableLogos;
    int m_selectedLogoIndex = 0;
    LogoChangeCallback m_onLogoChanged;
};

} // namespace moosic