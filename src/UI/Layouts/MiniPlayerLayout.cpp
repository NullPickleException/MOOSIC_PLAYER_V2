//==============================================================================
// MiniPlayerLayout.cpp
//==============================================================================

#include "MiniPlayerLayout.h"
#include <imgui.h>

namespace moosic
{

MiniPlayerLayout::MiniPlayerLayout(LibraryDataModel& libraryData,
                                   DirectoryDataModel& directoryData,
                                   PlaylistDataModel& playlistData,
                                   MusicLibrary& library, 
                                   PlaybackController& playbackController)
    : m_libraryData(libraryData)
    , m_directoryData(directoryData)
    , m_playlistData(playlistData)
    , m_directoryWindow(directoryData)
    , m_libraryWindow(libraryData, &playbackController)
    , m_playlistWindow(playlistData, &playbackController)
    , m_playbackController(playbackController)
{
    m_miniPlayerBar.SetPlaybackController(&playbackController);
    m_mainPlayerBar.SetPlaybackController(&playbackController);
    m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
}

void MiniPlayerLayout::Draw(SDL_Renderer* renderer)
{
    m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    m_playlistData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    
    m_miniPlayerBar.SetRenderer(renderer);
    m_mainPlayerBar.UpdatePlaybackState();

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("MiniPlayerLayout", nullptr, flags);

    // Tab buttons for switching between Library, Playlists, and Directories
    if (ImGui::Button("Library")) m_activeWindow = ActiveWindow::Library;
    ImGui::SameLine();
    if (ImGui::Button("Playlists")) m_activeWindow = ActiveWindow::Playlists;
    ImGui::SameLine();
    if (ImGui::Button("Directories")) m_activeWindow = ActiveWindow::Directory;
    ImGui::Separator();

    constexpr float PLAYER_HEIGHT = 160.0f;
    ImGui::BeginChild("Content", ImVec2(0, -PLAYER_HEIGHT), true);
    switch (m_activeWindow)
    {
    case ActiveWindow::Library:   m_libraryWindow.Draw(); break;
    case ActiveWindow::Playlists: m_playlistWindow.Draw(); break;
    case ActiveWindow::Directory: m_directoryWindow.Draw(); break;
    }
    ImGui::EndChild();

    ImGui::Separator();
    m_mainPlayerBar.Draw();

    ImGui::End();

    m_miniPlayerBar.Draw();
}

} // namespace moosic