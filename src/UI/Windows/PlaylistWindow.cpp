//==============================================================================
// UI/Windows/PlaylistWindow.cpp
//==============================================================================

#include "PlaylistWindow.h"
#include <imgui.h>
#include <algorithm>
#include <cctype>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif
#include <filesystem>

namespace moosic
{

    //==============================================================================
    // Constructor
    //==============================================================================

    PlaylistWindow::PlaylistWindow(PlaylistDataModel &dataModel,
                                   PlaybackController *playbackController)
        : m_data(dataModel), m_playbackController(playbackController)
    {
        //======================================================================
        // Main Track Table (Playlist Content)
        //======================================================================

        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Duration};
        config.Sortable = false;
        m_trackTable.ApplyConfig(config);

        TrackTableStyle style;
        style.TitleWidth = 350.0f;
        style.ArtistWidth = 180.0f;
        style.DurationWidth = 80.0f;
        style.RowHeight = 18.0f;
        m_trackTable.ApplyTheme(style);

        m_trackTable.OnRowClick([this](const RowEventData &event)
                                { OnTrackClicked(event.track, event.rowIndex); });

        m_trackTable.OnRowDoubleClick([this](const RowEventData &event)
                                      { OnTrackClicked(event.track, event.rowIndex); });

        //======================================================================
        // Track Right-Click Context Menu
        //======================================================================

        m_trackTable.OnRowRightClick([this](const RowEventData &event)
                                     {
            m_contextRow = event.rowIndex;
            m_contextTrack = event.track;
            
            std::vector<MenuItem> items;
            
            items.push_back({"Play", true, false, [this]() {
                OnTrackClicked(m_contextTrack, m_contextRow);
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Remove from Playlist", true, false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.RemoveTrackFromPlaylist(activeIdx.value(), static_cast<size_t>(m_contextRow));
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Move Up", m_contextRow > 0, false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.MoveTrack(activeIdx.value(), static_cast<size_t>(m_contextRow), static_cast<size_t>(m_contextRow - 1));
            }});
            
            items.push_back({"Move Down", m_contextRow < static_cast<int>(m_data.GetFilteredTrackCount()) - 1, false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.MoveTrack(activeIdx.value(), static_cast<size_t>(m_contextRow), static_cast<size_t>(m_contextRow + 1));
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Open Folder", true, false, [this]() {
                if (!m_contextTrack) return;
                try {
                    std::filesystem::path filePath = m_contextTrack->GetPath();
                    if (filePath.empty()) return;

#ifdef _WIN32
                    std::wstring wpath = filePath.wstring();
                    std::wstring cmd = L"/select,\"" + wpath + L"\"";
                    ShellExecuteW(NULL, L"open", L"explorer.exe", cmd.c_str(), NULL, SW_SHOWNORMAL);
#elif defined(__APPLE__)
                    std::string cmd = "open -R \"" + filePath.string() + "\"";
                    system(cmd.c_str());
#else
                    std::string cmd = "xdg-open \"" + filePath.parent_path().string() + "\"";
                    system(cmd.c_str());
#endif
                } catch (...) {}
            }});
            
            items.push_back({"Edit Track Info", true, false, []() {
                // TODO: Implement track metadata editing dialog
            }});
            
            m_trackContextMenu.SetItems(items);
            m_trackContextMenu.Open(
                static_cast<int>(ImGui::GetMousePos().x),
                static_cast<int>(ImGui::GetMousePos().y)
            ); });

        //======================================================================
        // Add Track Table (Library Tracks)
        //======================================================================

        TrackTableConfig addConfig;
        addConfig.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
        };
        addConfig.Sortable = true;
        addConfig.Resizable = true;
        m_addTrackTable.ApplyConfig(addConfig);

        TrackTableStyle addStyle;
        addStyle.TitleWidth = 250.0f;
        addStyle.ArtistWidth = 150.0f;
        addStyle.AlbumWidth = 150.0f;
        addStyle.RowHeight = 18.0f;
        m_addTrackTable.ApplyTheme(addStyle);

        m_addTrackTable.OnRowClick([this](const RowEventData &event)
                                   {
            m_selectedAddTrackIndex = event.rowIndex;
            m_selectedAddTrack = event.track; });

        m_addTrackTable.OnRowDoubleClick([this](const RowEventData &event)
                                         {
            m_selectedAddTrackIndex = event.rowIndex;
            m_selectedAddTrack = event.track;
            if (m_selectedPlaylistForAdd >= 0 && event.track)
            {
                m_data.AddTrackToPlaylist(
                    static_cast<size_t>(m_selectedPlaylistForAdd),
                    event.track->GetId());
            } });

        m_data.SetOnDataChanged([this]() {});
    }

    //==============================================================================
    // Draw
    //==============================================================================

    void PlaylistWindow::Draw()
    {
        if (m_playbackController)
            m_data.SyncPlayingTrack(m_playbackController->GetCurrentTrack());

        DrawPlaylistSidebar();

        ImGui::SameLine();

        // ── Splitter ──
        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.SeparatorColor);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
        ImGui::Button("##PlaylistSplitter", ImVec2(4.0f, -1));
        ImGui::PopStyleColor(3);

        if (ImGui::IsItemActive())
        {
            m_sidebarWidth += ImGui::GetIO().MouseDelta.x;
            if (m_sidebarWidth < MIN_SIDEBAR_WIDTH)
                m_sidebarWidth = MIN_SIDEBAR_WIDTH;
            if (m_sidebarWidth > MAX_SIDEBAR_WIDTH)
                m_sidebarWidth = MAX_SIDEBAR_WIDTH;
        }

        if (ImGui::IsItemHovered())
            ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);

        ImGui::SameLine();

        DrawPlaylistContent();

        // ── Popups ──
        DrawCreatePlaylistPopup();
        DrawRenamePlaylistPopup();
        DrawAddTrackPopup();
    }

    //==============================================================================
    // Sidebar - Playlist List
    //==============================================================================

    void PlaylistWindow::DrawPlaylistSidebar()
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_theme.ChildBg);
        ImGui::BeginChild("##PlaylistSidebar", ImVec2(m_sidebarWidth, 0), true);
        ImGui::PopStyleColor();

        // ── Header ──
        ImGui::TextColored(m_theme.BrandText, "PLAYLISTS");
        ImGui::Separator();

        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
        
        if (ImGui::Button("+ New Playlist", ImVec2(-1, 0)))
        {
            m_newPlaylistNameBuffer[0] = '\0';
            m_showCreatePlaylistPopup = true;
        }
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);

        ImGui::Spacing();

        // ── Search ──
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
        ImGui::SetNextItemWidth(-1);
        ImGui::InputTextWithHint("##PlaylistSearch", "Search...",
                                 m_playlistSearchBuffer, sizeof(m_playlistSearchBuffer));
        ImGui::PopStyleColor(2);

        ImGui::Separator();
        ImGui::Spacing();

        // ── Playlist List ──
        const auto &playlists = m_data.GetAllPlaylists();
        std::string filter = m_playlistSearchBuffer;
        std::transform(filter.begin(), filter.end(), filter.begin(),
                       [](unsigned char c)
                       { return static_cast<char>(std::tolower(c)); });

        for (size_t i = 0; i < playlists.size(); ++i)
        {
            const auto &playlist = playlists[i];

            std::string nameLower = playlist.name;
            std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(),
                           [](unsigned char c)
                           { return static_cast<char>(std::tolower(c)); });

            if (!filter.empty() && nameLower.find(filter) == std::string::npos)
                continue;

            bool isActive = m_data.GetActivePlaylistIndex().has_value() &&
                            m_data.GetActivePlaylistIndex().value() == i;

            if (isActive)
                ImGui::PushStyleColor(ImGuiCol_Text, m_theme.BrandText);

            char label[512];
            snprintf(label, sizeof(label), "  %s", playlist.name.c_str());

            ImGui::PushID(static_cast<int>(i));

            if (ImGui::Selectable(label, isActive, 0, ImVec2(0, 22.0f)))
            {
                m_data.SetActivePlaylist(i);
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                std::vector<MenuItem> items;

                items.push_back({"Add Tracks", true, false, [this, i]()
                                 {
                                     m_selectedPlaylistForAdd = static_cast<int>(i);
                                     m_addTrackSearchBuffer[0] = '\0';
                                     m_data.SetAddTrackSearchFilter("");
                                     m_selectedAddTrackIndex = -1;
                                     m_selectedAddTrack = nullptr;
                                     m_showAddTrackPopup = true;
                                 }});

                items.push_back({"Rename", true, false, [this, i, &playlist]()
                                 {
                                     m_renamePlaylistIndex = static_cast<int>(i);
                                     strncpy(m_renamePlaylistBuffer, playlist.name.c_str(), sizeof(m_renamePlaylistBuffer) - 1);
                                     m_renamePlaylistBuffer[sizeof(m_renamePlaylistBuffer) - 1] = '\0';
                                     m_showRenamePopup = true;
                                 }});

                items.push_back({"", false, true, nullptr});

                items.push_back({"Delete", true, false, [this, i]()
                                 {
                                     m_data.DeletePlaylist(i);
                                 }});

                m_playlistContextMenu.SetItems(items);
                m_playlistContextMenu.Open(
                    static_cast<int>(ImGui::GetMousePos().x),
                    static_cast<int>(ImGui::GetMousePos().y));
            }

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 30);
            ImGui::TextColored(m_theme.TextDisabled, "%zu", playlist.trackIds.size());

            if (isActive)
                ImGui::PopStyleColor();

            ImGui::PopID();
        }

        if (playlists.empty())
        {
            ImGui::Spacing();
            ImGui::TextColored(m_theme.TextDisabled, "  No playlists yet");
        }

        m_playlistContextMenu.Draw("##PlaylistContextMenu");

        ImGui::EndChild();
    }

    //==============================================================================
    // Content - Playlist Tracks
    //==============================================================================

    void PlaylistWindow::DrawPlaylistContent()
    {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_theme.ChildBg);
        ImGui::BeginChild("##PlaylistContent", ImVec2(0, 0), true);
        ImGui::PopStyleColor();

        auto activeIndex = m_data.GetActivePlaylistIndex();

        if (!activeIndex.has_value())
        {
            ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y * 0.4f);
            ImGui::TextColored(m_theme.TextDisabled, "  Select a playlist from the sidebar");
            ImGui::EndChild();
            return;
        }

        const auto *playlist = m_data.GetActivePlaylist();
        if (!playlist)
        {
            ImGui::EndChild();
            return;
        }

        // ── Header ──
        ImGui::TextColored(m_theme.BrandText, "%s", playlist->name.c_str());
        ImGui::SameLine();
        ImGui::TextColored(m_theme.TextSecondary, "(%zu tracks)", m_data.GetFilteredTrackCount());

        float buttonWidth = 110.0f;
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - buttonWidth);
        
        ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
        
        if (ImGui::Button("+ Add Tracks", ImVec2(buttonWidth, 0)))
        {
            m_selectedPlaylistForAdd = static_cast<int>(activeIndex.value());
            m_addTrackSearchBuffer[0] = '\0';
            m_data.SetAddTrackSearchFilter("");
            m_selectedAddTrackIndex = -1;
            m_selectedAddTrack = nullptr;
            m_showAddTrackPopup = true;
        }
        
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);

        ImGui::Separator();

        // ── Search ──
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
        ImGui::SetNextItemWidth(200.0f);
        if (ImGui::InputTextWithHint("##PlaylistTrackSearch", "Search tracks...",
                                     m_trackSearchBuffer, sizeof(m_trackSearchBuffer)))
        {
            m_data.SetSearchFilter(m_trackSearchBuffer);
        }
        ImGui::PopStyleColor(2);

        if (m_trackSearchBuffer[0] != '\0')
        {
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
            if (ImGui::SmallButton("X"))
            {
                m_trackSearchBuffer[0] = '\0';
                m_data.SetSearchFilter("");
            }
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
        }

        ImGui::Separator();
        ImGui::Spacing();

        // ── Track Table ──
        m_trackTable.SetSelectedRow(m_data.GetSelectedIndex(), m_data.GetSelectedTrack());
        m_trackTable.SetPlayingRow(m_data.GetPlayingIndex(), m_data.GetPlayingTrack());
        m_trackTable.Draw(m_data.GetFilteredTracks());

        m_trackContextMenu.Draw("##TrackContextMenu");

        ImGui::EndChild();
    }

    //==============================================================================
    // Add Track Popup
    //==============================================================================

    void PlaylistWindow::DrawAddTrackPopup()
    {
        if (m_showAddTrackPopup)
        {
            ImGui::OpenPopup("AddTrackToPlaylist");
            m_showAddTrackPopup = false;
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(650, 500), ImGuiCond_Appearing);

        if (ImGui::BeginPopupModal("AddTrackToPlaylist", nullptr, ImGuiWindowFlags_NoResize))
        {
            ImGui::TextColored(m_theme.BrandText, "Add Tracks to Playlist");
            ImGui::Separator();

            ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
            ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::InputTextWithHint("##AddTrackSearch", "Search title, artist or album...",
                                         m_addTrackSearchBuffer, sizeof(m_addTrackSearchBuffer)))
            {
                m_data.SetAddTrackSearchFilter(m_addTrackSearchBuffer);
            }
            ImGui::PopStyleColor(2);

            ImGui::Spacing();

            auto results = m_data.SearchLibraryForTracks();

            if (results.empty())
            {
                ImGui::Separator();
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
                if (m_addTrackSearchBuffer[0] != '\0')
                    ImGui::TextColored(m_theme.TextDisabled, "  No tracks found matching \"%s\"", m_addTrackSearchBuffer);
                else
                    ImGui::TextColored(m_theme.TextDisabled, "  No tracks in library. Add music files first.");
            }
            else
            {
                ImGui::Separator();
                float tableHeight = ImGui::GetContentRegionAvail().y - 60.0f;
                ImGui::BeginChild("##AddTrackTableContainer", ImVec2(0, tableHeight), true);
                m_addTrackTable.SetSelectedRow(m_selectedAddTrackIndex, m_selectedAddTrack);
                m_addTrackTable.Draw(results);
                ImGui::EndChild();
            }

            ImGui::Spacing();
            ImGui::Separator();

            if (m_selectedAddTrack)
                ImGui::TextColored(m_theme.TextPrimary, "Selected: %s - %s",
                            m_selectedAddTrack->GetTitle().c_str(),
                            m_selectedAddTrack->GetArtist().c_str());
            else
                ImGui::TextColored(m_theme.TextDisabled, "Select a track to add");

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 200.0f);

            bool canAdd = (m_selectedAddTrack != nullptr && m_selectedPlaylistForAdd >= 0);
            if (!canAdd)
                ImGui::BeginDisabled();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);
            
            if (ImGui::Button("Add Selected", ImVec2(100, 0)))
            {
                m_data.AddTrackToPlaylist(
                    static_cast<size_t>(m_selectedPlaylistForAdd),
                    m_selectedAddTrack->GetId());
                m_selectedAddTrackIndex = -1;
                m_selectedAddTrack = nullptr;
            }

            ImGui::SameLine();

            if (ImGui::Button("Close", ImVec2(80, 0)))
            {
                m_selectedAddTrackIndex = -1;
                m_selectedAddTrack = nullptr;
                ImGui::CloseCurrentPopup();
            }
            
            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            if (!canAdd)
                ImGui::EndDisabled();

            ImGui::EndPopup();
        }
    }

    //==============================================================================
    // Create Playlist Popup
    //==============================================================================

    void PlaylistWindow::DrawCreatePlaylistPopup()
    {
        if (m_showCreatePlaylistPopup)
        {
            ImGui::OpenPopup("CreatePlaylist");
            m_showCreatePlaylistPopup = false;
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(350, 130), ImGuiCond_Appearing);

        if (ImGui::BeginPopupModal("CreatePlaylist", nullptr, ImGuiWindowFlags_NoResize))
        {
            ImGui::TextColored(m_theme.BrandText, "Create New Playlist");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
            ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::IsWindowAppearing())
                ImGui::SetKeyboardFocusHere();

            bool enter = ImGui::InputTextWithHint("##NewPlaylistName", "Playlist name...",
                                                  m_newPlaylistNameBuffer,
                                                  sizeof(m_newPlaylistNameBuffer),
                                                  ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopStyleColor(2);

            ImGui::Spacing();

            bool canCreate = m_newPlaylistNameBuffer[0] != '\0';
            if (!canCreate)
                ImGui::BeginDisabled();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Create", ImVec2(120, 0)) || (enter && canCreate))
            {
                m_data.CreatePlaylist(m_newPlaylistNameBuffer);
                m_newPlaylistNameBuffer[0] = '\0';
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                m_newPlaylistNameBuffer[0] = '\0';
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            if (!canCreate)
                ImGui::EndDisabled();

            ImGui::EndPopup();
        }
    }

    //==============================================================================
    // Rename Playlist Popup
    //==============================================================================

    void PlaylistWindow::DrawRenamePlaylistPopup()
    {
        if (m_showRenamePopup)
        {
            ImGui::OpenPopup("RenamePlaylist");
            m_showRenamePopup = false;
        }

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(350, 130), ImGuiCond_Appearing);

        if (ImGui::BeginPopupModal("RenamePlaylist", nullptr, ImGuiWindowFlags_NoResize))
        {
            ImGui::TextColored(m_theme.BrandText, "Rename Playlist");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
            ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
            ImGui::SetNextItemWidth(-1);
            if (ImGui::IsWindowAppearing())
                ImGui::SetKeyboardFocusHere();

            bool enter = ImGui::InputText("##RenamePlaylistName", m_renamePlaylistBuffer,
                                          sizeof(m_renamePlaylistBuffer),
                                          ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopStyleColor(2);

            ImGui::Spacing();

            bool canRename = m_renamePlaylistBuffer[0] != '\0' && m_renamePlaylistIndex >= 0;
            if (!canRename)
                ImGui::BeginDisabled();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Rename", ImVec2(120, 0)) || (enter && canRename))
            {
                m_data.RenamePlaylist(static_cast<size_t>(m_renamePlaylistIndex), m_renamePlaylistBuffer);
                m_renamePlaylistBuffer[0] = '\0';
                m_renamePlaylistIndex = -1;
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                m_renamePlaylistBuffer[0] = '\0';
                m_renamePlaylistIndex = -1;
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            if (!canRename)
                ImGui::EndDisabled();

            ImGui::EndPopup();
        }
    }

    //==============================================================================
    // Track Click Handler
    //==============================================================================

    void PlaylistWindow::OnTrackClicked(const MusicTrack *track, int rowIndex)
    {
        if (!track)
            return;

        m_data.SetSelectedIndex(rowIndex);
        m_data.SetPlayingIndex(rowIndex);

        if (m_playbackController)
        {
            m_playbackController->SetCurrentTrackList(m_data.GetFilteredTracks());
            m_playbackController->SelectTrack(*track);
            m_playbackController->Play();
        }
    }

} // namespace moosic