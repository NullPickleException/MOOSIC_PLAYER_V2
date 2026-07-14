//==============================================================================
// MiniPlayerLayout.cpp
//==============================================================================

#include "MiniPlayerLayout.h"
#include <imgui.h>

namespace moosic
{

MiniPlayerLayout::MiniPlayerLayout(MusicLibrary& library, PlaybackController& playbackController)
    : m_directoryWindow(library)
    , m_libraryWindow(library, &playbackController)
    , m_playbackController(playbackController)
{
    m_miniPlayerBar.SetPlaybackController(&playbackController);
    m_mainPlayerBar.SetPlaybackController(&playbackController);

    const auto& tracks = library.GetTracks();
    std::vector<const MusicTrack*> trackList;
    trackList.reserve(tracks.size());
    for (const auto& track : tracks)
        trackList.push_back(&track);
    m_playbackController.SetCurrentTrackList(trackList);
}

void MiniPlayerLayout::Draw(SDL_Renderer* renderer)
{
    m_mainPlayerBar.UpdatePlaybackState();
    m_miniPlayerBar.UpdatePlaybackState();
    m_mainPlayerBar.SetRenderer(renderer);
    m_miniPlayerBar.SetRenderer(renderer);

    const MusicTrack* currentTrack = m_playbackController.GetCurrentTrack();
    m_libraryWindow.UpdatePlayingTrack(currentTrack);

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("MiniPlayerLayout", nullptr, flags);

    // Tabs
    if (ImGui::Button("Library")) m_activeWindow = ActiveWindow::Library;
    ImGui::SameLine();
    if (ImGui::Button("Directories")) m_activeWindow = ActiveWindow::Directory;
    ImGui::Separator();

    // Content
    constexpr float PLAYER_HEIGHT = 160.0f;
    ImGui::BeginChild("Content", ImVec2(0, -PLAYER_HEIGHT), true);
    switch (m_activeWindow)
    {
    case ActiveWindow::Library: m_libraryWindow.Draw(); break;
    case ActiveWindow::Directory: m_directoryWindow.Draw(); break;
    }
    ImGui::EndChild();

    // Main player at bottom
    ImGui::Separator();
    m_mainPlayerBar.Draw();

    ImGui::End();

    // Floating mini player on top
    m_miniPlayerBar.Draw();
}

} // namespace moosic