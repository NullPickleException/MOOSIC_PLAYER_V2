//==============================================================================
// WindowContentPanel.cpp
//==============================================================================
// Implementation of content panel with tabs - uses ImGui TabBar like Settings
//==============================================================================

#include "WindowContentPanel.h"
#include <imgui.h>

namespace moosic
{

    //==============================================================================
    // Construction
    //==============================================================================

    WindowContentPanel::WindowContentPanel(LibraryDataModel &libraryData,
                                           DirectoryDataModel &directoryData,
                                           MusicLibrary &library,
                                           PlaybackController *playbackController)
        : m_libraryData(libraryData), m_directoryData(directoryData), m_library(library), m_directoryWindow(directoryData), m_libraryWindow(libraryData, playbackController)
    {
    }

    void WindowContentPanel::UpdatePlayingTrack(const MusicTrack *track)
    {
        m_libraryData.SetPlayingTrack(track);
    }

    //==============================================================================
    // Drawing - Exactly like Settings window tab style
    //==============================================================================

    void WindowContentPanel::Draw()
    {
        if (ImGui::BeginTabBar("ContentTabs"))
        {
            if (ImGui::BeginTabItem("Library"))
            {
                m_libraryWindow.Draw();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Directories"))
            {
                m_directoryWindow.Draw();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Settings"))
            {
                m_settingsWindow.Draw();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }

} // namespace moosic