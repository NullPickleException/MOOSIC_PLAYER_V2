//==============================================================================
// StandardArtLeftLayout.cpp
//==============================================================================

#include "StandardArtLeftLayout.h"
#include <imgui.h>

namespace moosic
{

StandardArtLeftLayout::StandardArtLeftLayout(LibraryDataModel& libraryData,
                                             DirectoryDataModel& directoryData,
                                             PlaylistDataModel& playlistData,
                                             MusicLibrary& library, 
                                             PlaybackController& playbackController)
    : m_libraryData(libraryData)
    , m_directoryData(directoryData)
    , m_playlistData(playlistData)
    , m_playbackController(playbackController)
    , m_contentPanel(libraryData, directoryData, playlistData, library, &playbackController)
{
    m_playerBar.SetPlaybackController(&playbackController);
    m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
}

void StandardArtLeftLayout::Draw(SDL_Renderer* renderer)
{
    m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    m_playlistData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    
    m_playerBar.UpdatePlaybackState();
    m_playerBar.SetRenderer(renderer);

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("StandardArtLeftLayout", nullptr, flags);

    constexpr float PLAYER_HEIGHT = 160.0f;
    ImGui::BeginChild("Content", ImVec2(0, -PLAYER_HEIGHT), true);
    m_contentPanel.Draw();
    ImGui::EndChild();

    ImGui::Separator();
    m_playerBar.Draw();

    ImGui::End();
}

} // namespace moosic