//==============================================================================
// WindowContentPanel.cpp
//==============================================================================

#include "WindowContentPanel.h"
#include <imgui.h>

namespace moosic
{

    //==============================================================================
    // Construction
    //==============================================================================

    WindowContentPanel::WindowContentPanel(LibraryDataModel &libraryData,
                                           DirectoryDataModel &directoryData,
                                           PlaylistDataModel &playlistData,
                                           MusicLibrary &library,
                                           PlaybackController *playbackController)
        : m_libraryData(libraryData)
        , m_directoryData(directoryData)
        , m_playlistData(playlistData)
        , m_library(library)
        , m_directoryWindow(directoryData)
        , m_libraryWindow(libraryData, playbackController)
        , m_playlistWindow(playlistData, playbackController)
    {
    }

    void WindowContentPanel::UpdatePlayingTrack(const MusicTrack *track)
    {
        m_libraryData.SetPlayingTrack(track);
        m_playlistData.SyncPlayingTrack(track);
    }

    //==============================================================================
    // Drawing
    //==============================================================================

    void WindowContentPanel::Draw()
    {
        // Calculate padding based on border thickness so content never overlaps the border
        float pad = (m_theme.BorderThickness > 0.0f) ? m_theme.BorderThickness + 8.0f : 4.0f;

        // Draw the themed border around the content panel
        if (m_theme.BorderThickness > 0.0f)
        {
            ImVec2 cursorPos = ImGui::GetCursorScreenPos();
            ImVec2 availSize = ImGui::GetContentRegionAvail();

            ImDrawList *dl = ImGui::GetWindowDrawList();
            dl->AddRect(
                cursorPos,
                ImVec2(cursorPos.x + availSize.x, cursorPos.y + availSize.y),
                ImGui::GetColorU32(m_theme.BorderColor),
                4.0f,
                ImDrawFlags_RoundCornersAll,
                m_theme.BorderThickness);
        }

        // Push cursor inward on all sides so content scales inside the border
        ImGui::SetCursorPos(ImVec2(
            ImGui::GetCursorPosX() + pad,
            ImGui::GetCursorPosY() + pad));

        // Create a child region that respects the right/bottom padding too
        // This ensures child windows don't extend past the border
        ImVec2 innerSize = ImVec2(
            ImGui::GetContentRegionAvail().x - pad,
            ImGui::GetContentRegionAvail().y - pad);

        ImGui::BeginChild("##ContentPanelInner", innerSize, false);

        // Tab bar with all inner windows
        if (ImGui::BeginTabBar("ContentTabs"))
        {
            if (ImGui::BeginTabItem("Library"))
            {
                m_libraryWindow.Draw();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Playlists"))
            {
                m_playlistWindow.Draw();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Directories"))
            {
                m_directoryWindow.Draw();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Settings"))
            {
                m_settingsWindow.Draw();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        ImGui::EndChild();
    }

} // namespace moosic