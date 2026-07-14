//==============================================================================
// SettingsWindow.cpp
//==============================================================================

#include "SettingsWindow.h"
#include "../Theme/Theme.h"
#include <imgui.h>

namespace moosic
{

SettingsWindow::SettingsWindow()
{
}

void SettingsWindow::Draw()
{
    ImGui::Text("Settings");
    ImGui::Separator();
    DrawAppearanceSection();
}

void SettingsWindow::DrawAppearanceSection()
{
    ImGui::Spacing();
    ImGui::Text("Appearance");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextDisabled("Theme selection coming soon...");
}

} // namespace moosic