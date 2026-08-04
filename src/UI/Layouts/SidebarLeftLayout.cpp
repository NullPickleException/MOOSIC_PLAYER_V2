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

        // Clamp sidebar width on every frame
        float& sidebarWidth = m_layoutState.sidebarWidth;
        if (sidebarWidth < MIN_SIDEBAR_WIDTH) sidebarWidth = MIN_SIDEBAR_WIDTH;
        if (sidebarWidth > MAX_SIDEBAR_WIDTH) sidebarWidth = MAX_SIDEBAR_WIDTH;

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
                                 ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
        
        ImGui::Begin("SidebarLeftLayout", nullptr, flags);

        constexpr float SPLITTER_WIDTH = 4.0f;
        constexpr float SIDEBAR_CONTENT_SPACING = 4.0f;
        
        // Get full available height once
        float availHeight = ImGui::GetContentRegionAvail().y;
        float availWidth = ImGui::GetContentRegionAvail().x;

        // Sidebar panel - use exact height to prevent oscillation
        ImGui::BeginChild("Sidebar", ImVec2(sidebarWidth, availHeight), true, 
                          ImGuiWindowFlags_NoScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
        m_playerBar.Draw();
        ImGui::PopStyleVar();
        ImGui::EndChild();

        ImGui::SameLine(0.0f, SIDEBAR_CONTENT_SPACING);
        
        // Splitter
        ImGui::PushID("##VerticalSplitter");
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.27f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.40f, 0.40f, 0.42f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.50f, 0.50f, 0.52f, 1.0f));
        
        ImGui::Button("##Splitter", ImVec2(SPLITTER_WIDTH, availHeight));
        
        if (ImGui::IsItemHovered() || ImGui::IsItemActive())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
        
        if (ImGui::IsItemActive())
        {
            float delta = ImGui::GetIO().MouseDelta.x;
            float newWidth = sidebarWidth + delta;
            if (newWidth < MIN_SIDEBAR_WIDTH) newWidth = MIN_SIDEBAR_WIDTH;
            if (newWidth > MAX_SIDEBAR_WIDTH) newWidth = MAX_SIDEBAR_WIDTH;
            
            // Also ensure content area has minimum width
            float maxSidebarForContent = availWidth - SPLITTER_WIDTH - SIDEBAR_CONTENT_SPACING * 2 - 200.0f;
            if (newWidth > maxSidebarForContent) newWidth = maxSidebarForContent;
            if (newWidth < MIN_SIDEBAR_WIDTH) newWidth = MIN_SIDEBAR_WIDTH;
            
            m_layoutState.sidebarWidth = newWidth;
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::SameLine(0.0f, SIDEBAR_CONTENT_SPACING);
        
        // Content area - also use exact height
        ImGui::BeginChild("Content", ImVec2(0, availHeight), true);
        m_contentPanel.Draw();
        ImGui::EndChild();
        
        ImGui::End();
    }
} // namespace moosic