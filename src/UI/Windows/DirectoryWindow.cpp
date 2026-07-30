//==============================================================================
// UI/Windows/DirectoryWindow.cpp
//==============================================================================

#include "DirectoryWindow.h"
#include <imgui.h>

namespace moosic
{

//==============================================================================
// Constructor
//==============================================================================

DirectoryWindow::DirectoryWindow(DirectoryDataModel& dataModel)
    : m_data(dataModel)
{
    m_data.SetOnDataChanged([this]() {
        // Data changed - next Draw() will pick it up
    });
}

//==============================================================================
// Draw - Just renders what the data model gives us
//==============================================================================

void DirectoryWindow::Draw()
{
    // Check for finished imports
    m_data.Update();

    ImGui::TextColored(m_theme.BrandText, "Directories");
    ImGui::Separator();

    bool isImporting = m_data.IsImporting();

    // Action buttons with theme
    ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
    
    if (ImGui::Button(isImporting ? "Scanning..." : "Add Folder"))
    {
        if (!isImporting)
            m_data.AddDirectory();
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear All") && !m_data.GetDirectories().empty())
    {
        if (!isImporting)
            m_data.ClearAll();
    }
    
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);

    // Progress
    if (isImporting)
    {
        ImGui::Spacing();
        ImGui::TextColored(m_theme.TextPrimary, "Importing...");
        ImGui::ProgressBar(m_data.GetProgress(), ImVec2(-1.0f, 0.0f));
        ImGui::TextColored(m_theme.TextSecondary, "%d / %d files | Added: %d", 
                    m_data.GetProcessedFiles(), 
                    m_data.GetTotalFiles(),
                    m_data.GetSuccessfulFiles());
        ImGui::Separator();
    }

    // Directory list
    const auto& directories = m_data.GetDirectories();
    ImGui::TextColored(m_theme.TextPrimary, "Added Directories (%d)", static_cast<int>(directories.size()));

    if (directories.empty())
    {
        ImGui::TextColored(m_theme.TextDisabled, "No directories added yet.");
        return;
    }

    for (const auto& dir : directories)
    {
        const std::string text = dir.string();
        ImGui::PushID(text.c_str());

        ImGui::BulletText("%s", text.c_str());
        ImGui::SameLine();

        if (!isImporting)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
            
            if (ImGui::SmallButton("Remove"))
            {
                m_data.RemoveDirectory(dir);
            }
            
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
        }

        ImGui::PopID();
    }
}

} // namespace moosic