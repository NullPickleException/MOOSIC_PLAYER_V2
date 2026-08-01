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
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            
            if (ext == ".png")
            {
                LogoInfo info;
                info.path = entry.path().string();
                info.name = entry.path().stem().string();
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
    
    ImGui::TextColored(m_theme.BrandText, "Settings");
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
    ImGui::TextColored(m_theme.BrandText, "Theme");
    ImGui::Separator();
    ImGui::Spacing();
    DrawThemeSelector();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.BrandText, "Visualization");
    ImGui::Separator();
    ImGui::Spacing();
    DrawVisualizerModeSelector();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.BrandText, "Logo");
    ImGui::Separator();
    ImGui::Spacing();
    DrawLogoSelector();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.BrandText, "Font");
    ImGui::Separator();
    ImGui::Spacing();
    DrawFontSelector();
}

void SettingsWindow::DrawLogoSelector()
{
    ImGui::TextColored(m_theme.TextPrimary, "Title Bar Logo:");

    if (m_availableLogos.empty())
    {
        ImGui::TextColored(m_theme.TextDisabled, "No logos found in assets/Logo_img/");
        ImGui::TextColored(m_theme.TextDisabled, "Place .png files in the Logo_img folder");
        return;
    }

    std::string currentLogoName = "Default";
    if (m_selectedLogoIndex >= 0 && m_selectedLogoIndex < static_cast<int>(m_availableLogos.size()))
        currentLogoName = m_availableLogos[m_selectedLogoIndex].name;

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
    
    ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
    
    if (ImGui::Button("Reset to Default"))
    {
        ApplySelectedLogo(-1);
    }
    
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
    
    ImGui::SameLine();
    ImGui::TextColored(m_theme.TextDisabled, "Default: Moosic_Logo_Default.png");
}

void SettingsWindow::ApplySelectedLogo(int index)
{
    m_selectedLogoIndex = index;
    
    std::string logoPath;
    if (index >= 0 && index < static_cast<int>(m_availableLogos.size()))
        logoPath = m_availableLogos[index].path;
    
    if (m_settingsModel)
        m_settingsModel->SetLogoPath(logoPath);
    
    if (m_onLogoChanged)
        m_onLogoChanged(logoPath);
}

void SettingsWindow::DrawThemeSelector()
{
    if (!m_themeManager)
    {
        ImGui::TextColored(m_theme.TextDisabled, "Theme manager not available");
        return;
    }

    const auto& themes = m_themeManager->GetAvailableThemes();

    if (themes.empty())
    {
        ImGui::TextColored(m_theme.TextDisabled, "No themes available");
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
    ImGui::TextColored(m_theme.BrandText, "General Settings");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "General settings coming soon...");
}

void SettingsWindow::DrawAudioSection()
{
    ImGui::Spacing();
    ImGui::TextColored(m_theme.BrandText, "Audio Settings");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Audio settings coming soon...");
}

void SettingsWindow::ScanAvailableFonts()
{
    m_availableFonts.clear();
    m_selectedFontIndex = 0;

    std::vector<std::string> searchPaths = {
        "assets/Fonts",
        "../assets/Fonts",
        "../../assets/Fonts"
    };

    for (const auto& searchPath : searchPaths)
    {
        if (!std::filesystem::exists(searchPath))
            continue;

        for (const auto& entry : std::filesystem::directory_iterator(searchPath))
        {
            if (!entry.is_directory())
                continue;

            std::string folderName = entry.path().filename().string();
            
            if (folderName == "__MACOSX")
                continue;

            for (const auto& fontFile : std::filesystem::directory_iterator(entry.path()))
            {
                if (!fontFile.is_regular_file()) continue;
                
                std::string ext = fontFile.path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                
                if (ext == ".ttf" || ext == ".otf")
                {
                    FontInfo info;
                    info.name = folderName + " " + fontFile.path().stem().string();
                    info.path = fontFile.path().string();
                    info.folder = entry.path().string();
                    m_availableFonts.push_back(info);
                }
            }
        }

        if (!m_availableFonts.empty())
        {
            std::cout << "[SettingsWindow] Found " << m_availableFonts.size() 
                      << " fonts in: " << searchPath << "\n";
            break;
        }
    }

    if (m_settingsModel)
    {
        std::string savedPath = m_settingsModel->GetFontPath();
        m_fontSize = m_settingsModel->GetFontSize();
        if (m_fontSize < 12.0f) m_fontSize = 16.0f;
        
        if (!savedPath.empty())
        {
            for (size_t i = 0; i < m_availableFonts.size(); ++i)
            {
                if (m_availableFonts[i].path == savedPath)
                {
                    m_selectedFontIndex = static_cast<int>(i);
                    break;
                }
            }
        }
    }
}

void SettingsWindow::OnFontChanged(FontChangeCallback callback)
{
    m_onFontChanged = callback;
}

void SettingsWindow::DrawFontSelector()
{
    ImGui::TextColored(m_theme.TextPrimary, "Font:");

    if (m_availableFonts.empty())
    {
        ImGui::TextColored(m_theme.TextDisabled, "No fonts found in assets/Fonts/");
        ImGui::TextColored(m_theme.TextDisabled, "Place .ttf files in subdirectories");
        return;
    }

    std::string currentName = "Default";
    if (m_selectedFontIndex >= 0 && m_selectedFontIndex < static_cast<int>(m_availableFonts.size()))
        currentName = m_availableFonts[m_selectedFontIndex].name;

    if (ImGui::BeginCombo("##FontSelector", currentName.c_str()))
    {
        bool isDefault = (m_selectedFontIndex == -1);
        if (ImGui::Selectable("Default", isDefault))
            ApplySelectedFont(-1);
        if (isDefault) ImGui::SetItemDefaultFocus();

        for (int i = 0; i < static_cast<int>(m_availableFonts.size()); ++i)
        {
            bool isSelected = (i == m_selectedFontIndex);
            if (ImGui::Selectable(m_availableFonts[i].name.c_str(), isSelected))
                ApplySelectedFont(i);
            if (isSelected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if (m_selectedFontIndex >= 0)
    {
        ImGui::Spacing();
        ImGui::TextColored(m_theme.TextPrimary, "Font Size:");
        if (ImGui::SliderFloat("##FontSize", &m_fontSize, 12.0f, 32.0f, "%.0f"))
        {
            if (m_settingsModel)
                m_settingsModel->SetFontSize(m_fontSize);
            if (m_onFontChanged)
            {
                std::string path;
                if (m_selectedFontIndex >= 0 && m_selectedFontIndex < static_cast<int>(m_availableFonts.size()))
                    path = m_availableFonts[m_selectedFontIndex].path;
                m_onFontChanged(path, m_fontSize);
            }
        }
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Current: %s%s", 
                       currentName.c_str(),
                       m_selectedFontIndex >= 0 ? (" (" + std::to_string(static_cast<int>(m_fontSize)) + "px)").c_str() : "");
}

void SettingsWindow::ApplySelectedFont(int index)
{
    m_selectedFontIndex = index;
    
    std::string fontPath;
    std::string fontName = "Default";
    
    if (index >= 0 && index < static_cast<int>(m_availableFonts.size()))
    {
        fontPath = m_availableFonts[index].path;
        fontName = m_availableFonts[index].name;
    }
    
    if (m_settingsModel)
    {
        m_settingsModel->SetFontPath(fontPath);
        m_settingsModel->SetFontName(fontName);
    }
    
    if (m_onFontChanged)
        m_onFontChanged(fontPath, m_fontSize);
}

} // namespace moosic