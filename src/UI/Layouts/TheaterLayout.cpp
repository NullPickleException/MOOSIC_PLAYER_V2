//==============================================================================
// TheaterLayout.cpp
//==============================================================================

#include "TheaterLayout.h"
#include <imgui.h>

namespace moosic
{

TheaterLayout::TheaterLayout(MusicLibrary& library, PlaybackController& playbackController)
    : m_playbackController(playbackController)
{
    m_playerBar.SetPlaybackController(&playbackController);

    const auto& tracks = library.GetTracks();
    std::vector<const MusicTrack*> trackList;
    trackList.reserve(tracks.size());
    for (const auto& track : tracks)
        trackList.push_back(&track);
    m_playbackController.SetCurrentTrackList(trackList);
}

void TheaterLayout::Draw(SDL_Renderer* renderer)
{
    m_playerBar.UpdatePlaybackState();
    m_playerBar.SetRenderer(renderer);

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