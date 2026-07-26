//==============================================================================
// TheaterLayout.cpp
//==============================================================================

#include "TheaterLayout.h"
#include <imgui.h>

namespace moosic
{

TheaterLayout::TheaterLayout(LibraryDataModel& libraryData,
                             DirectoryDataModel& directoryData,
                             PlaylistDataModel& playlistData,
                             MusicLibrary& library, 
                             PlaybackController& playbackController)
    : m_libraryData(libraryData)
    , m_directoryData(directoryData)
    , m_playlistData(playlistData)
    , m_playbackController(playbackController)
{
    m_playerBar.SetPlaybackController(&playbackController);
    m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
}

void TheaterLayout::Draw(SDL_Renderer* renderer)
{
    m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    m_playlistData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
    
    m_playerBar.SetRenderer(renderer);
    m_playerBar.UpdatePlaybackState();

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("TheaterLayout", nullptr, flags);

    m_playerBar.Draw();

    ImGui::End();
}

} // namespace moosic