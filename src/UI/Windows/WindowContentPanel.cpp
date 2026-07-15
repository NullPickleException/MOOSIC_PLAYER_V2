//==============================================================================
// WindowContentPanel.cpp
//==============================================================================
// Implementation of content panel with tabs
//==============================================================================

#include "WindowContentPanel.h"
#include <imgui.h>

namespace moosic
{

//==============================================================================
// Construction
//==============================================================================

WindowContentPanel::WindowContentPanel(MusicLibrary& library, 
                                       PlaybackController* playbackController)
    : m_directoryWindow(library)
    , m_libraryWindow(library, playbackController)
{
}

void WindowContentPanel::UpdatePlayingTrack(const MusicTrack* track)
{
    m_libraryWindow.UpdatePlayingTrack(track);
}

//==============================================================================
// Drawing
//==============================================================================

void WindowContentPanel::Draw()
{
    DrawTabBar();

    // Border line under tabs
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2 pos = ImGui::GetCursorScreenPos();
    float w = ImGui::GetContentRegionAvail().x;
    dl->AddLine(
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + w, pos.y),
        ImGui::ColorConvertFloat4ToU32(m_theme.BorderColor),
        m_theme.BorderThickness);

    ImGui::Spacing();

    // Draw active tab content
    switch (m_activeTab)
    {
    case Tab::Library:    m_libraryWindow.Draw();   break;
    case Tab::Directory:  m_directoryWindow.Draw(); break;
    case Tab::Settings:   m_settingsWindow.Draw();  break;
    }
}

//==============================================================================
// Tab Bar
//==============================================================================

void WindowContentPanel::DrawTabBar()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(m_theme.TabSpacing, 0.0f));

    DrawTabButtons();

    ImGui::PopStyleVar();
}

void WindowContentPanel::DrawTabButtons()
{
    // Library Tab
    {
        bool active = (m_activeTab == Tab::Library);
        ImGui::PushStyleColor(ImGuiCol_Button, active ? m_theme.TabActive : m_theme.TabInactive);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.TabHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.TabActive);
        ImGui::PushStyleColor(ImGuiCol_Text, active ? m_theme.TabText : m_theme.TabTextInactive);
        
        if (ImGui::Button("Library"))
            m_activeTab = Tab::Library;
        
        ImGui::PopStyleColor(4);
    }

    ImGui::SameLine();

    // Directory Tab
    {
        bool active = (m_activeTab == Tab::Directory);
        ImGui::PushStyleColor(ImGuiCol_Button, active ? m_theme.TabActive : m_theme.TabInactive);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.TabHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.TabActive);
        ImGui::PushStyleColor(ImGuiCol_Text, active ? m_theme.TabText : m_theme.TabTextInactive);
        
        if (ImGui::Button("Directories"))
            m_activeTab = Tab::Directory;
        
        ImGui::PopStyleColor(4);
    }

    ImGui::SameLine();

    // Settings Tab
    {
        bool active = (m_activeTab == Tab::Settings);
        ImGui::PushStyleColor(ImGuiCol_Button, active ? m_theme.TabActive : m_theme.TabInactive);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.TabHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.TabActive);
        ImGui::PushStyleColor(ImGuiCol_Text, active ? m_theme.TabText : m_theme.TabTextInactive);
        
        if (ImGui::Button("Settings"))
            m_activeTab = Tab::Settings;
        
        ImGui::PopStyleColor(4);
    }
}

} // namespace moosic