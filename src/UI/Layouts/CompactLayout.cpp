//==============================================================================
// UI/Layouts/CompactLayout.cpp
//==============================================================================

#include "CompactLayout.h"
#include <imgui.h>

namespace moosic
{
    CompactLayout::CompactLayout(LibraryDataModel& libraryData, DirectoryDataModel& directoryData,
                                 PlaylistDataModel& playlistData, LayoutStateDataModel& layoutState,
                                 MusicLibrary& library, PlaybackController& playbackController)
        : m_libraryData(libraryData), m_directoryData(directoryData), m_playlistData(playlistData),
          m_playbackController(playbackController),
          m_contentPanel(libraryData, directoryData, playlistData, layoutState, library, &playbackController)
    {
        m_playerBar.SetPlaybackController(&playbackController);
        m_playbackController.SetCurrentTrackList(m_libraryData.GetTracks());
    }

    void CompactLayout::Draw(SDL_Renderer* renderer)
    {
        m_libraryData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
        m_playlistData.SyncPlayingTrack(m_playbackController.GetCurrentTrack());
        m_playerBar.SetRenderer(renderer);

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