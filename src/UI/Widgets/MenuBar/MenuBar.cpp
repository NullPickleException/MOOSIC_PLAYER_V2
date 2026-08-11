//==============================================================================
// UI/Widgets/MenuBar/MenuBar.cpp
//==============================================================================

#include "MenuBar.h"
#include <iostream>

namespace moosic
{
    void MenuBar::Draw(float titleBarHeight, float borderThickness, const ImVec4 &borderColor, const ImVec4 &bgColor)
    {
        ImGuiViewport *viewport = ImGui::GetMainViewport();

        float menuBarHeight = m_theme.Height;

        // Position below title bar
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + titleBarHeight));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, menuBarHeight));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar |
                                        ImGuiWindowFlags_NoTitleBar |
                                        ImGuiWindowFlags_NoResize |
                                        ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoScrollbar |
                                        ImGuiWindowFlags_NoScrollWithMouse |
                                        ImGuiWindowFlags_NoSavedSettings |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus;

        // Window styling
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, borderThickness);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10.0f, 0.0f));

        // Calculate vertical padding to perfectly center text in menu bar
        float fontHeight = ImGui::GetFontSize();

        float vertPadding = (menuBarHeight - fontHeight) / 2.0f;
        if (vertPadding < 0.0f)
            vertPadding = 0.0f;

        // Use the exact vertical padding to center text
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.0f, vertPadding));

        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgColor);
        ImGui::PushStyleColor(ImGuiCol_MenuBarBg, bgColor);
        ImGui::PushStyleColor(ImGuiCol_PopupBg, m_theme.PopupBackground);
        ImGui::PushStyleColor(ImGuiCol_Border, borderColor);

        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextColor);

        // Hover / open / pressed on File, View, ... and on dropdown items
        ImGui::PushStyleColor(ImGuiCol_Header, m_theme.HighlightColor);
        ImGui::PushStyleColor(ImGuiCol_HeaderHovered, m_theme.HighlightHovered);
        ImGui::PushStyleColor(ImGuiCol_HeaderActive, m_theme.HighlightActive);

        // Optional: slightly brighter text while hovering a top-level title
        ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, m_theme.HighlightHovered);

        bool open = true;
        if (ImGui::Begin("##MenuBarWindow", &open, window_flags))
        {
            if (ImGui::BeginMenuBar())
            {
                // Style the dropdown menus
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 6.0f));
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 5.0f));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, 3.0f));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(8.0f, 0.0f));
                ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 4.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_PopupBorderSize, 1.0f);

                // File Menu
                if (ImGui::BeginMenu("File"))
                {
                    // Use empty string for shortcut to handle it manually, or use "Ctrl+O"
                    // The shortcut display works - the issue is that ImGui doesn't auto-bind shortcuts
                    // in menu items. You need to handle it in your input system.
                    if (ImGui::MenuItem("Open Audio File...", "Ctrl+O"))
                    {
                        if (OnFileOpen)
                            OnFileOpen();
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem("Exit", "Alt+F4"))
                    {
                        if (OnFileExit)
                            OnFileExit();
                    }
                    ImGui::EndMenu();
                }

                // View Menu
                if (ImGui::BeginMenu("View"))
                {
                    if (ImGui::MenuItem("Standard Layout", "1"))
                    {
                        if (OnViewLayout)
                            OnViewLayout(0);
                    }
                    if (ImGui::MenuItem("Compact Layout", "2"))
                    {
                        if (OnViewLayout)
                            OnViewLayout(1);
                    }
                    if (ImGui::MenuItem("Standard Art Left", "3"))
                    {
                        if (OnViewLayout)
                            OnViewLayout(2);
                    }
                    if (ImGui::MenuItem("Sidebar Left", "4"))
                    {
                        if (OnViewLayout)
                            OnViewLayout(3);
                    }
                    if (ImGui::MenuItem("Theater Mode", "5"))
                    {
                        if (OnViewLayout)
                            OnViewLayout(4);
                    }
                    ImGui::EndMenu();
                }

                // Playback Menu
                // Playback Menu
                if (ImGui::BeginMenu("Playback"))
                {
                    if (ImGui::MenuItem("Play/Pause", "Space"))
                    {
                        if (OnPlaybackPlay)
                            OnPlaybackPlay(); // This now calls TogglePlayPause (fixed in UI.cpp setup)
                    }
                    ImGui::Separator();
                    if (ImGui::MenuItem("Next Track", "Ctrl+Right"))
                    {
                        if (OnNextTrack)
                            OnNextTrack();
                    }
                    if (ImGui::MenuItem("Previous Track", "Ctrl+Left"))
                    {
                        if (OnPreviousTrack)
                            OnPreviousTrack();
                    }
                    ImGui::EndMenu();
                }

                // Help Menu
                if (ImGui::BeginMenu("Help"))
                {
                    if (ImGui::MenuItem("About Moosic..."))
                    {
                        if (OnHelpAbout)
                            OnHelpAbout();
                    }
                    ImGui::EndMenu();
                }

                // Version number aligned to the right
                {
                    const char *version = "v2.0.0";
                    float textWidth = ImGui::CalcTextSize(version).x;
                    float rightPadding = 12.0f;

                    ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - textWidth - rightPadding);

                    ImGui::TextUnformatted(version);
                }

                ImGui::PopStyleVar(6);
                ImGui::EndMenuBar();
            }
            ImGui::End();
        }

        ImGui::PopStyleColor(9);
        ImGui::PopStyleVar(5);
    }

} // namespace moosic