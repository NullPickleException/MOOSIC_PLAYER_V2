//==============================================================================
// SettingsWindow.cpp
//==============================================================================
// Implementation of settings window with theme selection and visualizer mode
// Now uses SettingsDataModel for centralized state management
//==============================================================================

#include "SettingsWindow.h"
#include <imgui.h>

namespace moosic
{

//==============================================================================
// Construction
//==============================================================================

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
    
    // Sync local state from the data model
    if (m_settingsModel)
    {
        m_visualizerMode = m_settingsModel->GetVisualizerMode();
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

//==============================================================================
// Visualizer Mode Callback
//==============================================================================

void SettingsWindow::OnVisualizerModeChanged(VisualizerModeCallback callback)
{
    m_onVisualizerModeChanged = callback;
}

//==============================================================================
// Drawing
//==============================================================================

void SettingsWindow::Draw()
{
    // Sync visualizer mode from data model on every frame
    if (m_settingsModel)
    {
        m_visualizerMode = m_settingsModel->GetVisualizerMode();
        
        // Update selected theme index from theme manager
        if (m_themeManager)
        {
            m_selectedThemeIndex = m_themeManager->GetCurrentThemeIndex();
            if (m_selectedThemeIndex < 0) m_selectedThemeIndex = 0;
        }
    }
    
    ImGui::Text("Settings");
    ImGui::Separator();

    //--------------------------------------------------------------------------
    // Tab Bar
    //--------------------------------------------------------------------------

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

//==============================================================================
// Appearance Section
//==============================================================================

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
    ImGui::TextColored(m_theme.TextSecondary, "Font");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("Font settings coming soon...");
}

//==============================================================================
// Theme Selector
//==============================================================================

void SettingsWindow::DrawThemeSelector()
{
    if (!m_themeManager)
    {
        ImGui::TextDisabled("Theme manager not available");
        return;
    }

    const auto& themes = m_themeManager->GetAvailableThemes();
    const auto themeNames = m_themeManager->GetThemeNames();

    if (themes.empty())
    {
        ImGui::TextDisabled("No themes available");
        return;
    }

    //--------------------------------------------------------------------------
    // Theme List with Preview
    //--------------------------------------------------------------------------

    ImGui::TextColored(m_theme.TextPrimary, "Select Theme:");

    // Get current theme name for display
    std::string currentThemeName = m_themeManager->GetCurrentThemeName();
    
    // Combo box for theme selection
    if (ImGui::BeginCombo("##ThemeSelector", currentThemeName.c_str()))
    {
        for (int i = 0; i < static_cast<int>(themes.size()); ++i)
        {
            bool isSelected = (themes[i].Name == currentThemeName);
            
            if (ImGui::Selectable(themes[i].Name.c_str(), isSelected))
            {
                ApplySelectedTheme(i);
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();

    //--------------------------------------------------------------------------
    // Theme Preview (simple color swatches)
    //--------------------------------------------------------------------------

    ImGui::TextColored(m_theme.TextSecondary, "Preview:");
    ImGui::Spacing();

    // Get the current selected theme for preview
    const Theme& selectedTheme = m_themeManager->GetTheme();
    
    // Show a simple color preview
    float previewSize = 20.0f;
    float spacing = 4.0f;
    
    // Preview colors from the theme
    ImVec4 colors[] = {
        selectedTheme.Window.TextPrimary,
        selectedTheme.Window.TextSecondary,
        selectedTheme.Window.ButtonNormal,
        selectedTheme.Window.ButtonHovered,
        selectedTheme.Window.ChildBg,
        selectedTheme.Window.SeparatorColor
    };

    const char* labels[] = {
        "Text",
        "Text Sec",
        "Button",
        "Button Hover",
        "Background",
        "Separator"
    };

    for (int i = 0; i < 6; ++i)
    {
        ImGui::ColorButton(labels[i], colors[i], ImGuiColorEditFlags_NoTooltip, 
                          ImVec2(previewSize, previewSize));
        
        if (i < 5)
        {
            ImGui::SameLine(0, spacing);
        }
        else
        {
            ImGui::Spacing();
        }
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Current: %s", 
                       m_themeManager->GetCurrentThemeName().c_str());
}

//==============================================================================
// Visualizer Mode Selector
//==============================================================================

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
                
                // Update the shared data model
                if (m_settingsModel)
                {
                    m_settingsModel->SetVisualizerMode(i);
                }
                
                // Notify listener (UI class) to propagate to PlaybackController
                if (m_onVisualizerModeChanged)
                {
                    m_onVisualizerModeChanged(i);
                }
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    ImGui::TextColored(m_theme.TextDisabled, "Current: %s", modes[m_visualizerMode]);
}

//==============================================================================
// Apply Theme
//==============================================================================

void SettingsWindow::ApplySelectedTheme(int index)
{
    if (!m_themeManager)
        return;

    const auto& themes = m_themeManager->GetAvailableThemes();
    if (index < 0 || index >= static_cast<int>(themes.size()))
        return;

    // Apply the theme through the manager
    m_themeManager->SetThemeByIndex(index);
    
    // Update the shared data model with the new theme name
    if (m_settingsModel)
    {
        m_settingsModel->SetThemeName(themes[index].Name);
    }

    // Notify listeners - UI class will call ApplyThemeToLayouts()
    if (m_onThemeChanged)
    {
        m_onThemeChanged();
    }
}

//==============================================================================
// Other Sections
//==============================================================================

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