//==============================================================================
// SettingsWindow.cpp
//==============================================================================

#include "SettingsWindow.h"
#include <imgui.h>
#include <filesystem>
#include <iostream>

namespace moosic
{

SettingsWindow::SettingsWindow()
{
}

void SettingsWindow::ApplyTheme(const WindowTheme& theme)
{
    m_theme = theme;
}

void SettingsWindow::SetSettingsDataModel(SettingsDataModel* model)
{
    m_settingsModel = model;
    if (m_settingsModel)
    {
        m_visualizerMode = m_settingsModel->GetVisualizerMode();
        
        // Find the saved logo in the list
        std::string savedPath = m_settingsModel->GetLogoPath();
        if (!savedPath.empty())
        {
            for (size_t i = 0; i < m_availableLogos.size(); ++i)
            {
                if (m_availableLogos[i].path == savedPath)
                {
                    m_selectedLogoIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void SettingsWindow::SetThemeManager(ThemeManager* manager)
{
    m_themeManager = manager;
    if (m_themeManager)
    {
        m_selectedThemeIndex = m_themeManager->GetCurrentThemeIndex();
        if (m_selectedThemeIndex < 0) m_selectedThemeIndex = 0;
    }
}

void SettingsWindow::OnThemeChanged(ThemeChangeCallback callback)
{
    m_onThemeChanged = callback;
}

void SettingsWindow::OnVisualizerModeChanged(VisualizerModeCallback callback)
{
    m_onVisualizerModeChanged = callback;
}

void SettingsWindow::OnLogoChanged(LogoChangeCallback callback)
{
    m_onLogoChanged = callback;
}

// Scan assets/Logo_img folder for .png files
void SettingsWindow::ScanAvailableLogos()
{
    m_availableLogos.clear();
    m_selectedLogoIndex = 0;

    std::vector<std::string> searchPaths = {
        "assets/Logo_img",
        "../assets/Logo_img",
        "../../assets/Logo_img"
    };

    for (const auto& searchPath : searchPaths)
    {
        if (!std::filesystem::exists(searchPath))
            continue;

        for (const auto& entry : std::filesystem::directory_iterator(searchPath))
        {
            if (!entry.is_regular_file())
                continue;

            std::string ext = entry.path().extension().string();
            // Convert to lowercase for comparison
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            
            if (ext == ".png")
            {
                LogoInfo info;
                info.path = entry.path().string();
                info.name = entry.path().stem().string();  // filename without extension
                m_availableLogos.push_back(info);
            }
        }

        if (!m_availableLogos.empty())
        {
            std::cout << "[SettingsWindow] Found " << m_availableLogos.size() 
                      << " logos in: " << searchPath << "\n";
            break;
        }
    }

    // If a logo was previously saved, find its index
    if (m_settingsModel)
    {
        std::string savedPath = m_settingsModel->GetLogoPath();
        if (!savedPath.empty())
        {
            for (size_t i = 0; i < m_availableLogos.size(); ++i)
            {
                if (m_availableLogos[i].path == savedPath ||
                    m_availableLogos[i].name == savedPath)
                {
                    m_selectedLogoIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void SettingsWindow::Draw()
{
    if (m_settingsModel)
    {
        m_visualizerMode = m_settingsModel->GetVisualizerMode();
        
        if (m_themeManager)
        {
            m_selectedThemeIndex = m_themeManager->GetCurrentThemeIndex();
            if (m_selectedThemeIndex < 0) m_selectedThemeIndex = 0;
        }
    }
    
    ImGui::Text("Settings");
    ImGui::Separator();

    if (ImGui::BeginTabBar("SettingsTabs"))
    {
        if (ImGui::BeginTabItem("Appearance"))
        {
            DrawAppearanceSection();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("General"))
        {
            DrawGeneralSection();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Audio"))
        {
            DrawAudioSection();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void SettingsWindow::DrawAppearanceSection()
{
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Theme");
    ImGui::Separator();
    ImGui::Spacing();
    DrawThemeSelector();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Visualization");
    ImGui::Separator();
    ImGui::Spacing();
    DrawVisualizerModeSelector();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Logo");
    ImGui::Separator();
    ImGui::Spacing();
    DrawLogoSelector();

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Font");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextDisabled("Font settings coming soon...");
}

void SettingsWindow::DrawLogoSelector()
{
    ImGui::TextColored(m_theme.TextPrimary, "Title Bar Logo:");

    if (m_availableLogos.empty())
    {
        ImGui::TextDisabled("No logos found in assets/Logo_img/");
        ImGui::TextDisabled("Place .png files in the Logo_img folder");
        return;
    }

    // Get current logo name for display
    std::string currentLogoName = "Default";
    if (m_selectedLogoIndex >= 0 && m_selectedLogoIndex < static_cast<int>(m_availableLogos.size()))
        currentLogoName = m_availableLogos[m_selectedLogoIndex].name;

    // Combo box for logo selection (just like theme selector)
    if (ImGui::BeginCombo("##LogoSelector", currentLogoName.c_str()))
    {
        for (int i = 0; i < static_cast<int>(m_availableLogos.size()); ++i)
        {
            bool isSelected = (i == m_selectedLogoIndex);
            
            if (ImGui::Selectable(m_availableLogos[i].name.c_str(), isSelected))
            {
                ApplySelectedLogo(i);
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    
    // Reset to default button
    if (ImGui::Button("Reset to Default"))
    {
        ApplySelectedLogo(-1);  // -1 = default
    }
    
    ImGui::SameLine();
    ImGui::TextColored(m_theme.TextDisabled, "Default: COW_IMAGE.png");
}

void SettingsWindow::ApplySelectedLogo(int index)
{
    m_selectedLogoIndex = index;
    
    std::string logoPath;
    if (index >= 0 && index < static_cast<int>(m_availableLogos.size()))
        logoPath = m_availableLogos[index].path;
    // else empty = use default
    
    // Save to settings data model
    if (m_settingsModel)
        m_settingsModel->SetLogoPath(logoPath);
    
    // Notify callback to reload the logo
    if (m_onLogoChanged)
        m_onLogoChanged(logoPath);
}

void SettingsWindow::DrawThemeSelector()
{
    if (!m_themeManager)
    {
        ImGui::TextDisabled("Theme manager not available");
        return;
    }

    const auto& themes = m_themeManager->GetAvailableThemes();

    if (themes.empty())
    {
        ImGui::TextDisabled("No themes available");
        return;
    }

    ImGui::TextColored(m_theme.TextPrimary, "Select Theme:");

    std::string currentThemeName = m_themeManager->GetCurrentThemeName();
    
    if (ImGui::BeginCombo("##ThemeSelector", currentThemeName.c_str()))
    {
        for (int i = 0; i < static_cast<int>(themes.size()); ++i)
        {
            bool isSelected = (themes[i].Name == currentThemeName);
            
            if (ImGui::Selectable(themes[i].Name.c_str(), isSelected))
                ApplySelectedTheme(i);

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Preview:");
    ImGui::Spacing();

    const Theme& selectedTheme = m_themeManager->GetTheme();
    
    float previewSize = 20.0f;
    float spacing = 4.0f;
    
    ImVec4 colors[] = {
        selectedTheme.Window.TextPrimary,
        selectedTheme.Window.TextSecondary,
        selectedTheme.Window.ButtonNormal,
        selectedTheme.Window.ButtonHovered,
        selectedTheme.Window.ChildBg,
        selectedTheme.Window.SeparatorColor
    };

    const char* labels[] = {
        "Text", "Text Sec", "Button", "Button Hover", "Background", "Separator"
    };

    for (int i = 0; i < 6; ++i)
    {
        ImGui::ColorButton(labels[i], colors[i], ImGuiColorEditFlags_NoTooltip, 
                          ImVec2(previewSize, previewSize));
        if (i < 5) ImGui::SameLine(0, spacing);
        else ImGui::Spacing();
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Current: %s", 
                       m_themeManager->GetCurrentThemeName().c_str());
}

void SettingsWindow::DrawVisualizerModeSelector()
{
    ImGui::TextColored(m_theme.TextPrimary, "Visualization Mode:");

    const char* modes[] = { "Spectrum", "Oscilloscope" };
    
    if (ImGui::BeginCombo("##VisualizerMode", modes[m_visualizerMode]))
    {
        for (int i = 0; i < 2; ++i)
        {
            bool isSelected = (i == m_visualizerMode);
            
            if (ImGui::Selectable(modes[i], isSelected))
            {
                m_visualizerMode = i;
                
                if (m_settingsModel)
                    m_settingsModel->SetVisualizerMode(i);
                
                if (m_onVisualizerModeChanged)
                    m_onVisualizerModeChanged(i);
            }

            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Current: %s", modes[m_visualizerMode]);
}

void SettingsWindow::ApplySelectedTheme(int index)
{
    if (!m_themeManager)
        return;

    const auto& themes = m_themeManager->GetAvailableThemes();
    if (index < 0 || index >= static_cast<int>(themes.size()))
        return;

    m_themeManager->SetThemeByIndex(index);
    
    if (m_settingsModel)
        m_settingsModel->SetThemeName(themes[index].Name);

    if (m_onThemeChanged)
        m_onThemeChanged();
}

void SettingsWindow::DrawGeneralSection()
{
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "General Settings");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextDisabled("General settings coming soon...");
}

void SettingsWindow::DrawAudioSection()
{
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextSecondary, "Audio Settings");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextDisabled("Audio settings coming soon...");
}

} // namespace moosic