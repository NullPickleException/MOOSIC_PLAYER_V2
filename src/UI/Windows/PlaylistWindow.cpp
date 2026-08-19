//==============================================================================
// UI/Windows/PlaylistWindow.cpp
//==============================================================================

#include "PlaylistWindow.h"
#include <imgui.h>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

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
        // Main Track Table (Playlist Content) - Config from DataModel
        //======================================================================

        m_trackTable.ApplyConfig(m_data.GetTrackTableConfig());

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

        // Track columns changed callback - save to DataModel
        m_trackTable.OnColumnsChanged([this](const TrackTableConfig &config)
                                      { m_data.SetTrackTableConfig(config); });

        //======================================================================
        // Track Right-Click Context Menu
        //======================================================================

        m_trackTable.OnRowRightClick([this](const RowEventData &event)
                                     {
            m_data.SetContextRow(event.rowIndex);
            m_data.SetContextTrack(event.track);
            
            std::vector<MenuItem> items;
            const int contextRow = m_data.GetContextRow();
            const MusicTrack* contextTrack = m_data.GetContextTrack();
            
            items.push_back({"Play", true, false, [this, contextRow, contextTrack]() {
                OnTrackClicked(contextTrack, contextRow);
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Remove from Playlist", true, false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.RemoveTrackFromPlaylist(activeIdx.value(), static_cast<size_t>(m_data.GetContextRow()));
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Move Up", m_data.GetContextRow() > 0, false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.MoveTrack(activeIdx.value(), 
                                   static_cast<size_t>(m_data.GetContextRow()), 
                                   static_cast<size_t>(m_data.GetContextRow() - 1));
            }});
            
            items.push_back({"Move Down", 
                           m_data.GetContextRow() < static_cast<int>(m_data.GetFilteredTrackCount()) - 1, 
                           false, [this]() {
                auto activeIdx = m_data.GetActivePlaylistIndex();
                if (activeIdx.has_value())
                    m_data.MoveTrack(activeIdx.value(), 
                                   static_cast<size_t>(m_data.GetContextRow()), 
                                   static_cast<size_t>(m_data.GetContextRow() + 1));
            }});
            
            items.push_back({"", false, true, nullptr});
            
            items.push_back({"Open Folder", true, false, [this]() {
                const MusicTrack* contextTrack = m_data.GetContextTrack();
                if (!contextTrack) return;
                try {
                    std::filesystem::path filePath = contextTrack->GetPath();
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
            
            items.push_back({"Edit Track Info...", true, false, [this]() {
                m_editTrackDialog.Open(m_data.GetContextTrack());
            }});
            
            m_trackContextMenu.SetItems(items);
            m_trackContextMenu.Open(
                static_cast<int>(ImGui::GetMousePos().x),
                static_cast<int>(ImGui::GetMousePos().y)
            ); });

        //======================================================================
        // Add Track Table (Library Tracks) - Config from DataModel
        //======================================================================

        m_addTrackTable.ApplyConfig(m_data.GetAddTrackTableConfig());

        TrackTableStyle addStyle;
        addStyle.TitleWidth = 250.0f;
        addStyle.ArtistWidth = 150.0f;
        addStyle.AlbumWidth = 150.0f;
        addStyle.RowHeight = 18.0f;
        m_addTrackTable.ApplyTheme(addStyle);

        m_addTrackTable.OnRowClick([this](const RowEventData &event)
                                   {
            m_data.SetSelectedAddTrackIndex(event.rowIndex); });

        m_addTrackTable.OnRowDoubleClick([this](const RowEventData &event)
                                         {
            m_data.SetSelectedAddTrackIndex(event.rowIndex);
            const MusicTrack* selectedTrack = m_data.GetSelectedAddTrack();
            if (m_data.GetSelectedPlaylistForAdd() >= 0 && selectedTrack)
            {
                m_data.AddTrackToPlaylist(
                    static_cast<size_t>(m_data.GetSelectedPlaylistForAdd()),
                    selectedTrack->GetId());
            } });

        // Add track table columns changed callback - save to DataModel
        m_addTrackTable.OnColumnsChanged([this](const TrackTableConfig &config)
                                         { m_data.SetAddTrackTableConfig(config); });

        //======================================================================
        // Edit Track Dialog
        //======================================================================

        m_editTrackDialog.SetSaveCallback([this](const MusicTrack *track,
                                                 const std::string &title,
                                                 const std::string &artist,
                                                 const std::string &album)
                                          {
            if (track)
            {
                m_data.GetLibrary().UpdateTrackMetadata(track->GetId(), title, artist, album);
                m_data.NotifyDataChanged();
            } });
    }

    //==============================================================================
    // Draw
    //==============================================================================

    void PlaylistWindow::Draw()
    {
        if (m_playbackController)
            m_data.SyncPlayingTrack(m_playbackController->GetCurrentTrack());

        // Apply config from data model each frame
        m_trackTable.ApplyConfig(m_data.GetTrackTableConfig());
        m_addTrackTable.ApplyConfig(m_data.GetAddTrackTableConfig());

        // Sync search buffers with data model
        strncpy(m_playlistSearchBuffer, m_data.GetPlaylistSearchFilter().c_str(), sizeof(m_playlistSearchBuffer) - 1);
        strncpy(m_trackSearchBuffer, m_data.GetSearchFilter().c_str(), sizeof(m_trackSearchBuffer) - 1);
        strncpy(m_addTrackSearchBuffer, m_data.GetAddTrackSearchFilter().c_str(), sizeof(m_addTrackSearchBuffer) - 1);

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
        m_editTrackDialog.Draw();
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
            m_data.SetShowCreatePlaylistPopup(true);
        }

        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);

        ImGui::Spacing();

        // ── Search ──
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
        ImGui::SetNextItemWidth(-1);
        if (ImGui::InputTextWithHint("##PlaylistSearch", "Search...",
                                     m_playlistSearchBuffer, sizeof(m_playlistSearchBuffer)))
        {
            m_data.SetPlaylistSearchFilter(m_playlistSearchBuffer);
        }
        ImGui::PopStyleColor(2);

        ImGui::Separator();
        ImGui::Spacing();

        // ── Playlist List ──
        const auto &playlists = m_data.GetFilteredPlaylists();
        const auto activeIndex = m_data.GetActivePlaylistIndex();

        for (size_t i = 0; i < playlists.size(); ++i)
        {
            const auto *playlist = playlists[i];
            if (!playlist)
                continue;

            // Find the actual index in the full playlist vector
            size_t actualIndex = 0;
            const auto &allPlaylists = m_data.GetAllPlaylists();
            for (size_t j = 0; j < allPlaylists.size(); ++j)
            {
                if (&allPlaylists[j] == playlist)
                {
                    actualIndex = j;
                    break;
                }
            }

            bool isActive = activeIndex.has_value() && activeIndex.value() == actualIndex;

            if (isActive)
                ImGui::PushStyleColor(ImGuiCol_Text, m_theme.BrandText);

            char label[512];
            snprintf(label, sizeof(label), "  %s", playlist->name.c_str());

            ImGui::PushID(static_cast<int>(actualIndex));

            if (ImGui::Selectable(label, isActive, 0, ImVec2(0, 22.0f)))
            {
                m_data.SetActivePlaylist(actualIndex);
            }

            if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                std::vector<MenuItem> items;

                items.push_back({"Add Tracks", true, false, [this, actualIndex]()
                                 {
                                     m_data.SetSelectedPlaylistForAdd(static_cast<int>(actualIndex));
                                     m_data.SetAddTrackSearchFilter("");
                                     m_data.ClearAddTrackSelection();
                                     m_data.SetShowAddTrackPopup(true);
                                 }});

                items.push_back({"Rename", true, false, [this, actualIndex]()
                                 {
                                     m_data.SetRenamePlaylistIndex(static_cast<int>(actualIndex));
                                     const auto* playlist = m_data.GetPlaylist(actualIndex);
                                     if (playlist)
                                     {
                                         strncpy(m_renamePlaylistBuffer, playlist->name.c_str(), sizeof(m_renamePlaylistBuffer) - 1);
                                         m_renamePlaylistBuffer[sizeof(m_renamePlaylistBuffer) - 1] = '\0';
                                     }
                                     m_data.SetShowRenamePopup(true);
                                 }});

                items.push_back({"", false, true, nullptr});

                items.push_back({"Delete", true, false, [this, actualIndex]()
                                 {
                                     m_data.DeletePlaylist(actualIndex);
                                 }});

                m_playlistContextMenu.SetItems(items);
                m_playlistContextMenu.Open(
                    static_cast<int>(ImGui::GetMousePos().x),
                    static_cast<int>(ImGui::GetMousePos().y));
            }

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 30);
            ImGui::TextColored(m_theme.TextDisabled, "%zu", playlist->trackIds.size());

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
            m_data.SetSelectedPlaylistForAdd(static_cast<int>(activeIndex.value()));
            m_data.SetAddTrackSearchFilter("");
            m_data.ClearAddTrackSelection();
            m_data.SetShowAddTrackPopup(true);
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
        if (m_data.GetShowAddTrackPopup())
        {
            ImGui::OpenPopup("AddTrackToPlaylist");
            m_data.SetShowAddTrackPopup(false);
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
                m_addTrackTable.SetSelectedRow(m_data.GetSelectedAddTrackIndex(), m_data.GetSelectedAddTrack());
                m_addTrackTable.Draw(results);
                ImGui::EndChild();
            }

            ImGui::Spacing();
            ImGui::Separator();

            const MusicTrack* selectedAddTrack = m_data.GetSelectedAddTrack();
            if (selectedAddTrack)
                ImGui::TextColored(m_theme.TextPrimary, "Selected: %s - %s",
                                   selectedAddTrack->GetTitle().c_str(),
                                   selectedAddTrack->GetArtist().c_str());
            else
                ImGui::TextColored(m_theme.TextDisabled, "Select a track to add");

            ImGui::SameLine(ImGui::GetContentRegionAvail().x - 200.0f);

            bool canAdd = (selectedAddTrack != nullptr && m_data.GetSelectedPlaylistForAdd() >= 0);
            if (!canAdd)
                ImGui::BeginDisabled();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Add Selected", ImVec2(100, 0)))
            {
                m_data.AddTrackToPlaylist(
                    static_cast<size_t>(m_data.GetSelectedPlaylistForAdd()),
                    selectedAddTrack->GetId());
                m_data.ClearAddTrackSelection();
            }
            if (!canAdd)
                ImGui::EndDisabled();

            ImGui::SameLine();

            if (ImGui::Button("Close", ImVec2(80, 0)))
            {
                m_data.ClearAddTrackSelection();
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            ImGui::EndPopup();
        }
    }

    //==============================================================================
    // Create Playlist Popup
    //==============================================================================

    void PlaylistWindow::DrawCreatePlaylistPopup()
    {
        if (m_data.GetShowCreatePlaylistPopup())
        {
            ImGui::OpenPopup("CreatePlaylist");
            m_data.SetShowCreatePlaylistPopup(false);
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

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);

            if (!canCreate)
                ImGui::EndDisabled();

            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                m_newPlaylistNameBuffer[0] = '\0';
                ImGui::CloseCurrentPopup();
            }
            
            ImGui::EndPopup();
        }
    }

    //==============================================================================
    // Rename Playlist Popup
    //==============================================================================

    void PlaylistWindow::DrawRenamePlaylistPopup()
    {
        if (m_data.GetShowRenamePopup())
        {
            ImGui::OpenPopup("RenamePlaylist");
            m_data.SetShowRenamePopup(false);
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

            bool canRename = m_renamePlaylistBuffer[0] != '\0' && m_data.GetRenamePlaylistIndex() >= 0;
            if (!canRename)
                ImGui::BeginDisabled();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Rename", ImVec2(120, 0)) || (enter && canRename))
            {
                m_data.RenamePlaylist(static_cast<size_t>(m_data.GetRenamePlaylistIndex()), m_renamePlaylistBuffer);
                m_renamePlaylistBuffer[0] = '\0';
                m_data.SetRenamePlaylistIndex(-1);
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0)))
            {
                m_renamePlaylistBuffer[0] = '\0';
                m_data.SetRenamePlaylistIndex(-1);
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