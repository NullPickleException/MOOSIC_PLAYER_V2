//==============================================================================
// WindowContentPanel.cpp
//==============================================================================

#include "WindowContentPanel.h"
#include <imgui.h>

namespace moosic
{

    WindowContentPanel::WindowContentPanel(LibraryDataModel &libraryData,
                                           DirectoryDataModel &directoryData,
                                           PlaylistDataModel &playlistData,
                                           LayoutStateDataModel &layoutState,
                                           MusicLibrary &library,
                                           PlaybackController *playbackController)
        : m_libraryData(libraryData), m_directoryData(directoryData), m_playlistData(playlistData),
          m_library(library),
          m_layoutState(layoutState),
          m_directoryWindow(directoryData),
          m_libraryWindow(libraryData, playbackController),
          m_playlistWindow(playlistData, playbackController)
    {

        m_libraryWindow.SetPlaylistDataModel(&m_playlistData);
    }

    void WindowContentPanel::UpdatePlayingTrack(const MusicTrack *track)
    {
        m_libraryData.SetPlayingTrack(track);
        m_playlistData.SyncPlayingTrack(track);
    }

    static void DrawTabBevelEdges(ImDrawList *dl, const ImVec2 &min, const ImVec2 &max,
                                  float rounding, float thickness,
                                  const ImVec4 &lightColor, const ImVec4 &darkColor,
                                  const ImVec4 &borderColor)
    {
        if (thickness <= 0.0f)
            return;
        float t = thickness, r = rounding;
        ImU32 borderCol = ImGui::GetColorU32(borderColor);
        dl->PushClipRect(min, max, true);
        dl->AddRect(min, max, borderCol, r, ImDrawFlags_RoundCornersAll, 1.0f);
        for (float i = 0.0f; i < t; i += 0.5f)
        {
            float alpha = 1.0f - (i / t);
            ImU32 col = ImGui::GetColorU32(ImVec4(lightColor.x, lightColor.y, lightColor.z, lightColor.w * alpha));
            dl->AddRect(ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                        ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                        col, r, ImDrawFlags_RoundCornersAll, 1.0f);
        }
        for (float i = 0.0f; i < t; i += 0.5f)
        {
            float alpha = 1.0f - (i / t);
            ImU32 col = ImGui::GetColorU32(ImVec4(darkColor.x, darkColor.y, darkColor.z, darkColor.w * alpha));
            dl->AddRect(ImVec2(min.x + i + 1.0f, min.y + i + 1.0f),
                        ImVec2(max.x - i - 1.0f, max.y - i - 1.0f),
                        col, r, ImDrawFlags_RoundCornersAll, 1.0f);
        }
        dl->PopClipRect();
    }

    void WindowContentPanel::Draw()
    {
        float pad = (m_theme.BorderThickness > 0.0f) ? m_theme.BorderThickness + 8.0f : 4.0f;

        if (m_theme.BorderThickness > 0.0f)
        {
            ImVec2 cursorPos = ImGui::GetCursorScreenPos();
            ImVec2 availSize = ImGui::GetContentRegionAvail();
            ImDrawList *dl = ImGui::GetWindowDrawList();
            if (m_theme.UseGradientTabs)
            {
                dl->AddRectFilledMultiColor(cursorPos,
                                            ImVec2(cursorPos.x + availSize.x, cursorPos.y + availSize.y),
                                            ImGui::GetColorU32(m_theme.TabGradientTop),
                                            ImGui::GetColorU32(m_theme.TabGradientTop),
                                            ImGui::GetColorU32(m_theme.TabGradientBottom),
                                            ImGui::GetColorU32(m_theme.TabGradientBottom));
            }
            if (m_theme.UseTabBevel)
            {
                DrawTabBevelEdges(dl, cursorPos,
                                  ImVec2(cursorPos.x + availSize.x, cursorPos.y + availSize.y),
                                  4.0f, m_theme.TabBevelThickness,
                                  m_theme.TabBevelLight, m_theme.TabBevelDark,
                                  m_theme.TabBevelBorderColor);
            }
            else
            {
                dl->AddRect(cursorPos,
                            ImVec2(cursorPos.x + availSize.x, cursorPos.y + availSize.y),
                            ImGui::GetColorU32(m_theme.BorderColor),
                            4.0f, ImDrawFlags_RoundCornersAll, m_theme.BorderThickness);
            }
        }

        ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + pad, ImGui::GetCursorPosY() + pad));
        ImVec2 innerSize = ImVec2(ImGui::GetContentRegionAvail().x - pad,
                                  ImGui::GetContentRegionAvail().y - pad);
        ImGui::BeginChild("##ContentPanelInner", innerSize, false);

        // NOTE: Data-layer ticks (directory Update + library Refresh) live in UI::Draw.
        // Do not call them here.

        const auto desiredTab = m_layoutState.GetCurrentTab();
        const bool needForceSelect = (desiredTab != m_appliedTab);

        if (ImGui::BeginTabBar("##SharedContentTabs", ImGuiTabBarFlags_None))
        {
            auto handleTab = [&](const char *label, LayoutStateDataModel::Tab tab, auto &&drawContent)
            {
                ImGuiTabItemFlags flags = 0;
                if (needForceSelect && desiredTab == tab)
                    flags = ImGuiTabItemFlags_SetSelected;

                if (ImGui::BeginTabItem(label, nullptr, flags))
                {
                    if (needForceSelect)
                    {
                        if (desiredTab == tab)
                        {
                            m_appliedTab = tab;
                            drawContent();
                        }
                    }
                    else
                    {
                        m_layoutState.SetCurrentTab(tab);
                        m_appliedTab = tab;
                        drawContent();
                    }

                    ImGui::EndTabItem();
                }
            };

            handleTab("Library", LayoutStateDataModel::Tab::Library,
                      [&]()
                      { m_libraryWindow.Draw(); });

            handleTab("Playlists", LayoutStateDataModel::Tab::Playlists,
                      [&]()
                      { m_playlistWindow.Draw(); });

            handleTab("Directories", LayoutStateDataModel::Tab::Directory,
                      [&]()
                      { m_directoryWindow.Draw(); });

            handleTab("Settings", LayoutStateDataModel::Tab::Settings, [&]()
                      {
            ImGui::BeginChild("##SettingsScrollRegion", ImVec2(0, 0), false,
                              ImGuiWindowFlags_AlwaysVerticalScrollbar);
            m_settingsWindow.Draw();
            ImGui::EndChild(); });

            ImGui::EndTabBar();
        }

        ImGui::EndChild();
    }

} // namespace moosic