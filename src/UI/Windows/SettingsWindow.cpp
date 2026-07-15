//==============================================================================
// SettingsWindow.cpp
//==============================================================================
// Implementation of settings window with theme selection
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
// Drawing
//==============================================================================

void SettingsWindow::Draw()
{
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
    const auto& themeNames = m_themeManager->GetThemeNames();

    if (themes.empty())
    {
        ImGui::TextDisabled("No themes available");
        return;
    }

    //--------------------------------------------------------------------------
    // Theme List with Preview
    //--------------------------------------------------------------------------

    ImGui::TextColored(m_theme.TextPrimary, "Select Theme:");

    // Combo box for theme selection
    if (ImGui::BeginCombo("##ThemeSelector", 
                          themeNames[m_selectedThemeIndex].c_str()))
    {
        for (int i = 0; i < static_cast<int>(themes.size()); ++i)
        {
            bool isSelected = (i == m_selectedThemeIndex);
            
            if (ImGui::Selectable(themes[i].Name.c_str(), isSelected))
            {
                m_selectedThemeIndex = i;
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

    // Get the current selected theme
    const Theme& selectedTheme = themes[m_selectedThemeIndex].Factory();
    
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
                       themes[m_selectedThemeIndex].Name.c_str());
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

    // Notify listeners - no parameter needed
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