//==============================================================================
// CompactLayout.cpp
//==============================================================================

#include "CompactLayout.h"
#include <imgui.h>

namespace moosic
{

CompactLayout::CompactLayout(MusicLibrary& library, PlaybackController& playbackController)
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

void CompactLayout::Draw(SDL_Renderer* renderer)
{
    m_playerBar.UpdatePlaybackState();
    m_playerBar.SetRenderer(renderer);
    m_contentPanel.UpdatePlayingTrack(m_playbackController.GetCurrentTrack());

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("CompactLayout", nullptr, flags);

    constexpr float PLAYER_HEIGHT = 130.0f;
    ImGui::BeginChild("Content", ImVec2(0, -PLAYER_HEIGHT), true);
    m_contentPanel.Draw();
    ImGui::EndChild();

    ImGui::Separator();
    m_playerBar.Draw();

    ImGui::End();
}

} // namespace moosic