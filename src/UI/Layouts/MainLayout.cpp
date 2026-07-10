#include "MainLayout.h"
#include <imgui.h>

namespace moosic
{

MainLayout::MainLayout(MusicLibrary& library, PlaybackController& playbackController)
    : m_directoryWindow(library)
    , m_libraryWindow(library, &playbackController)
    , m_playbackController(playbackController)
{
    m_playerBar.SetPlaybackController(&playbackController);
    
    // Set initial track list from library
    const auto& tracks = library.GetTracks();
    std::vector<const MusicTrack*> trackList;
    trackList.reserve(tracks.size());
    for (const auto& track : tracks)
        trackList.push_back(&track);
    m_playbackController.SetCurrentTrackList(trackList);
}

void MainLayout::Draw()
{
    // Update player bar state every frame
    m_playerBar.UpdatePlaybackState();
    
    // Sync playing track with library window
    const MusicTrack* currentTrack = m_playbackController.GetCurrentTrack();
    m_libraryWindow.UpdatePlayingTrack(currentTrack);

    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoSavedSettings;

    ImGui::Begin("MainLayout", nullptr, flags);

    //--------------------------------------------------
    // Top Tabs
    //--------------------------------------------------

    if (ImGui::Button("Library"))
        m_activeWindow = ActiveWindow::Library;

    ImGui::SameLine();

    if (ImGui::Button("Directories"))
        m_activeWindow = ActiveWindow::Directory;

    ImGui::Separator();

    //--------------------------------------------------
    // Main Content
    //--------------------------------------------------

    constexpr float PLAYER_BAR_HEIGHT = 160.0f;

    ImGui::BeginChild(
        "Content",
        ImVec2(0, -PLAYER_BAR_HEIGHT),
        true);

    switch (m_activeWindow)
    {
    case ActiveWindow::Library:
        m_libraryWindow.Draw();
        break;

    case ActiveWindow::Directory:
        m_directoryWindow.Draw();
        break;
    }

    ImGui::EndChild();

    //--------------------------------------------------
    // Player
    //--------------------------------------------------

    ImGui::Separator();
    m_playerBar.Draw();

    ImGui::End();
}

}