//==============================================================================
// UI/Layouts/SidebarLeftLayout.cpp
//==============================================================================

#include "SidebarLeftLayout.h"
#include <imgui.h>

namespace moosic
{
    SidebarLeftLayout::SidebarLeftLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                                         PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                                         MusicLibrary& library, PlaybackController& playbackController)
        : m_libraryData(libraryData), m_directoryData(directoryData), m_playlistData(playlistData),
          m_layoutState(layoutState), m_playbackController(playbackController),
          m_contentPanel(libraryData, directoryData, playlistData, layoutState, library, &playbackController)
    {
        m_playerBar.SetPlaybackController(&playbackController);
        m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
    }

    void SidebarLeftLayout::Draw(SDL_Renderer* renderer)
    {
        m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
        m_playlistData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
        m_playerBar.SetRenderer(renderer);

        float sidebarWidth = m_layoutState.sidebarWidth;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
        ImGui::Begin("SidebarLeftLayout", nullptr, flags);

        constexpr float SIDEBAR_CONTENT_SPACING = 8.0f;

        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, 0), true);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
        m_playerBar.Draw();
        ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::SameLine(0.0f, SIDEBAR_CONTENT_SPACING);
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.27f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.40f, 0.40f, 0.42f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.50f, 0.50f, 0.52f, 1.0f));
        ImGui::Button("##Splitter", ImVec2(4.0f, -1.0f));
        if (ImGui::IsItemHovered()) ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
        if (ImGui::IsItemActive())
        {
            float delta = ImGui::GetIO().MouseDelta.x;
            m_layoutState.sidebarWidth += delta;
            if (m_layoutState.sidebarWidth < MIN_SIDEBAR_WIDTH) m_layoutState.sidebarWidth = MIN_SIDEBAR_WIDTH;
            if (m_layoutState.sidebarWidth > MAX_SIDEBAR_WIDTH) m_layoutState.sidebarWidth = MAX_SIDEBAR_WIDTH;
        }
        ImGui::PopStyleColor(3);

        ImGui::SameLine(0.0f, SIDEBAR_CONTENT_SPACING);
        ImGui::BeginChild("Content", ImVec2(0, 0), true);
        m_contentPanel.Draw();
        ImGui::EndChild();
        ImGui::End();
    }
} // namespace moosic