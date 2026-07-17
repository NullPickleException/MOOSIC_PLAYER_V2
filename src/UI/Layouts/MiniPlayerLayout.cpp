//==============================================================================
// MiniPlayerLayout.cpp
//==============================================================================

#include "MiniPlayerLayout.h"
#include <imgui.h>

namespace moosic
{

MiniPlayerLayout::MiniPlayerLayout(LibraryDataModel& libraryData,
                                   DirectoryDataModel& directoryData,
                                   MusicLibrary& library, 
                                   PlaybackController& playbackController)
    : m_libraryData(libraryData)
    , m_directoryData(directoryData)
    , m_directoryWindow(directoryData)
    , m_libraryWindow(libraryData, &playbackController)
    , m_playbackController(playbackController)
{
    m_miniPlayerBar.SetPlaybackController(&playbackController);
    m_mainPlayerBar.SetPlaybackController(&playbackController);
    m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
}

void MiniPlayerLayout::Draw(SDL_Renderer* renderer)
{
    m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    
    m_mainPlayerBar.UpdatePlaybackState();
    m_miniPlayerBar.UpdatePlaybackState();
    m_mainPlayerBar.SetRenderer(renderer);
    m_miniPlayerBar.SetRenderer(renderer);

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("MiniPlayerLayout", nullptr, flags);

    if (ImGui::Button("Library")) m_activeWindow = ActiveWindow::Library;
    ImGui::SameLine();
    if (ImGui::Button("Directories")) m_activeWindow = ActiveWindow::Directory;
    ImGui::Separator();

    constexpr float PLAYER_HEIGHT = 160.0f;
    ImGui::BeginChild("Content", ImVec2(0, -PLAYER_HEIGHT), true);
    switch (m_activeWindow)
    {
    case ActiveWindow::Library: m_libraryWindow.Draw(); break;
    case ActiveWindow::Directory: m_directoryWindow.Draw(); break;
    }
    ImGui::EndChild();

    ImGui::Separator();
    m_mainPlayerBar.Draw();

    ImGui::End();

    m_miniPlayerBar.Draw();
}

} // namespace moosic