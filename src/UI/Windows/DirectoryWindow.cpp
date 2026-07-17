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
    // Listen for data changes
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

    ImGui::Text("Directories");
    ImGui::Separator();

    bool isImporting = m_data.IsImporting();

    // Action buttons
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

    // Progress
    if (isImporting)
    {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Importing...");

        float progress = m_data.GetProgress();
        ImGui::ProgressBar(progress, ImVec2(-1.0f, 0.0f));
        ImGui::Text("%d / %d files | Added: %d", 
                    m_data.GetProcessedFiles(), 
                    m_data.GetTotalFiles(),
                    m_data.GetSuccessfulFiles());
        ImGui::Separator();
    }

    // Directory list
    const auto& directories = m_data.GetDirectories();
    ImGui::Text("Added Directories (%d)", static_cast<int>(directories.size()));

    if (directories.empty())
    {
        ImGui::TextDisabled("No directories added yet.");
        return;
    }

    for (const auto& dir : directories)
    {
        const std::string text = dir.string();
        ImGui::PushID(text.c_str());

        ImGui::BulletText("%s", text.c_str());
        ImGui::SameLine();

        if (!isImporting && ImGui::SmallButton("Remove"))
        {
            m_data.RemoveDirectory(dir);
        }

        ImGui::PopID();
    }
}

} // namespace moosic