//==============================================================================
// SidebarLeftLayout.cpp
//==============================================================================

#include "SidebarLeftLayout.h"
#include <imgui.h>

namespace moosic
{

SidebarLeftLayout::SidebarLeftLayout(MusicLibrary& library, PlaybackController& playbackController)
    : m_playbackController(playbackController)
    , m_contentPanel(library, &playbackController)
{
    m_playerBar.SetPlaybackController(&playbackController);

    const auto& tracks = library.GetTracks();
    std::vector<const MusicTrack*> trackList;
    trackList.reserve(tracks.size());
    for (const auto& track : tracks)
        trackList.push_back(&track);
    m_playbackController.SetCurrentTrackList(trackList);
}

void SidebarLeftLayout::Draw(SDL_Renderer* renderer)
{
    m_playerBar.UpdatePlaybackState();
    m_playerBar.SetRenderer(renderer);
    m_contentPanel.UpdatePlayingTrack(m_playbackController.GetCurrentTrack());

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("SidebarLeftLayout", nullptr, flags);

    //------------------------------------------------------------------
    // Left Sidebar (Player)
    //------------------------------------------------------------------
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.13f, 1.0f));
    ImGui::BeginChild("Sidebar", ImVec2(m_sidebarWidth, 0), true);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
    m_playerBar.Draw();
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::PopStyleColor();

    //------------------------------------------------------------------
    // Draggable splitter
    //------------------------------------------------------------------
    ImGui::SameLine(0.0f, 0.0f);
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.27f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.40f, 0.40f, 0.42f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.50f, 0.50f, 0.52f, 1.0f));
    ImGui::Button("##Splitter", ImVec2(4.0f, -1.0f));
    
    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    
    if (ImGui::IsItemActive())
    {
        float delta = ImGui::GetIO().MouseDelta.x;
        m_sidebarWidth += delta;
        if (m_sidebarWidth < MIN_SIDEBAR_WIDTH) m_sidebarWidth = MIN_SIDEBAR_WIDTH;
        if (m_sidebarWidth > MAX_SIDEBAR_WIDTH) m_sidebarWidth = MAX_SIDEBAR_WIDTH;
    }
    
    ImGui::PopStyleColor(3);

    //------------------------------------------------------------------
    // Right Content Area
    //------------------------------------------------------------------
    ImGui::SameLine(0.0f, 0.0f);
    ImGui::BeginChild("Content", ImVec2(0, 0), true);
    m_contentPanel.Draw();
    ImGui::EndChild();

    ImGui::End();
}

} // namespace moosic