//==============================================================================
// UI/Windows/PlaylistWindow.cpp
//==============================================================================

#include "PlaylistWindow.h"
#include <imgui.h>
#include <algorithm>
#include <cctype>

namespace moosic
{

//==============================================================================
// Constructor
//==============================================================================

PlaylistWindow::PlaylistWindow(PlaylistDataModel& dataModel,
                               PlaybackController* playbackController)
    : m_data(dataModel)
    , m_playbackController(playbackController)
{
    // ── Main track table (playlist content) ──
    TrackTableConfig config;
    config.Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
       // TrackColumn::Album,
       // TrackColumn::Extension,
        TrackColumn::Duration
    };
    m_trackTable.ApplyConfig(config);
    
    TrackTableStyle style;
    style.TitleWidth = 350.0f;
    style.ArtistWidth = 180.0f;
    style.AlbumWidth = 180.0f;
    style.ExtensionWidth = 50.0f;
    style.DurationWidth = 80.0f;
    style.RowHeight = 18.0f;
    m_trackTable.ApplyTheme(style);
    
    m_trackTable.OnRowClick([this](const MusicTrack* track, int rowIndex) {
        OnTrackClicked(track, rowIndex);
    });
    
    m_trackTable.OnRowDoubleClick([this](const MusicTrack* track, int rowIndex) {
        OnTrackClicked(track, rowIndex);
    });
    
    // ── Add Track popup table (library tracks to add) ──
    TrackTableConfig addConfig;
    addConfig.Columns = {
        TrackColumn::Title,
        TrackColumn::Artist,
        TrackColumn::Album,
       // TrackColumn::Duration
    };
    addConfig.Sortable = true;
    addConfig.Resizable = true;
    m_addTrackTable.ApplyConfig(addConfig);
    
    TrackTableStyle addStyle;
    addStyle.TitleWidth = 250.0f;
    addStyle.ArtistWidth = 150.0f;
    addStyle.AlbumWidth = 150.0f;
    addStyle.DurationWidth = 70.0f;
    addStyle.RowHeight = 18.0f;
    m_addTrackTable.ApplyTheme(addStyle);
    
    m_addTrackTable.OnRowClick([this](const MusicTrack* track, int rowIndex) {
        m_selectedAddTrackIndex = rowIndex;
        m_selectedAddTrack = track;
    });
    
    m_addTrackTable.OnRowDoubleClick([this](const MusicTrack* track, int rowIndex) {
        m_selectedAddTrackIndex = rowIndex;
        m_selectedAddTrack = track;
        // Double-click adds immediately
        if (m_selectedPlaylistForAdd >= 0 && track)
        {
            m_data.AddTrackToPlaylist(
                static_cast<size_t>(m_selectedPlaylistForAdd),
                track->GetId());
        }
    });
    
    // ── Playlist sidebar context menu ──
    m_playlistContextMenu.SetItems({
        {"Add Tracks", true},
        {"Rename", true},
        {"", false, true},  // separator
        {"Delete", true}
    }, "PlaylistContextMenu");
    
    // ── Track context menu (right-click on playlist track) ──
    m_trackContextMenu.SetItems({
        {"Remove from Playlist", true},
        {"", false, true},  // separator
        {"Move Up", true},
        {"Move Down", true}
    }, "TrackContextMenu");
    
    m_data.SetOnDataChanged([this]() { });
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
    
    // Splitter
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.27f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.40f, 0.40f, 0.42f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.50f, 0.50f, 0.52f, 1.0f));
    ImGui::Button("##PlaylistSplitter", ImVec2(4.0f, -1));
    ImGui::PopStyleColor(3);
    
    if (ImGui::IsItemActive())
    {
        m_sidebarWidth += ImGui::GetIO().MouseDelta.x;
        if (m_sidebarWidth < MIN_SIDEBAR_WIDTH) m_sidebarWidth = MIN_SIDEBAR_WIDTH;
        if (m_sidebarWidth > MAX_SIDEBAR_WIDTH) m_sidebarWidth = MAX_SIDEBAR_WIDTH;
    }
    
    if (ImGui::IsItemHovered())
        ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
    
    ImGui::SameLine();
    
    DrawPlaylistContent();
    
    // Popups
    DrawCreatePlaylistPopup();
    DrawRenamePlaylistPopup();
    DrawAddTrackPopup();
}

//==============================================================================
// Sidebar - Playlist List
//==============================================================================

void PlaylistWindow::DrawPlaylistSidebar()
{
    ImGui::BeginChild("##PlaylistSidebar", ImVec2(m_sidebarWidth, 0), true);
    
    ImGui::TextColored(m_theme.BrandText, "PLAYLISTS");
    ImGui::Separator();
    
    if (ImGui::Button("+ New Playlist", ImVec2(-1, 0)))
    {
        m_newPlaylistNameBuffer[0] = '\0';
        m_showCreatePlaylistPopup = true;
    }
    
    ImGui::Spacing();
    
    ImGui::SetNextItemWidth(-1);
    ImGui::InputTextWithHint("##PlaylistSearch", "Search...",
                             m_playlistSearchBuffer, sizeof(m_playlistSearchBuffer));
    
    ImGui::Separator();
    ImGui::Spacing();
    
    const auto& playlists = m_data.GetAllPlaylists();
    std::string filter = m_playlistSearchBuffer;
    std::transform(filter.begin(), filter.end(), filter.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    
    for (size_t i = 0; i < playlists.size(); ++i)
    {
        const auto& playlist = playlists[i];
        
        std::string nameLower = playlist.name;
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        
        if (!filter.empty() && nameLower.find(filter) == std::string::npos)
            continue;
        
        bool isActive = m_data.GetActivePlaylistIndex().has_value() &&
                        m_data.GetActivePlaylistIndex().value() == i;
        
        if (isActive)
            ImGui::PushStyleColor(ImGuiCol_Text, m_theme.BrandText);
        
        char label[256];
        snprintf(label, sizeof(label), "  %s", playlist.name.c_str());
        
        ImGui::PushID(static_cast<int>(i));
        
        if (ImGui::Selectable(label, isActive, 0, ImVec2(0, 22.0f)))
        {
            m_data.SetActivePlaylist(i);
        }
        
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 30);
        ImGui::TextDisabled("%zu", playlist.trackIds.size());
        
        if (isActive)
            ImGui::PopStyleColor();
        
        // Right-click context menu
        auto menuResult = m_playlistContextMenu.Show();
        if (menuResult.clickedIndex >= 0)
        {
            switch (menuResult.clickedIndex)
            {
            case 0: // Add Tracks
                m_selectedPlaylistForAdd = static_cast<int>(i);
                m_addTrackSearchBuffer[0] = '\0';
                m_data.SetAddTrackSearchFilter("");
                m_selectedAddTrackIndex = -1;
                m_selectedAddTrack = nullptr;
                m_showAddTrackPopup = true;
                break;
            case 1: // Rename
                m_renamePlaylistIndex = static_cast<int>(i);
                strncpy(m_renamePlaylistBuffer, playlist.name.c_str(), sizeof(m_renamePlaylistBuffer) - 1);
                m_renamePlaylistBuffer[sizeof(m_renamePlaylistBuffer) - 1] = '\0';
                m_showRenamePopup = true;
                break;
            case 3: // Delete
                m_data.DeletePlaylist(i);
                ImGui::PopID();
                ImGui::EndChild();
                return;
            }
        }
        
        ImGui::PopID();
    }
    
    if (playlists.empty())
    {
        ImGui::Spacing();
        ImGui::TextDisabled("  No playlists yet");
    }
    
    ImGui::EndChild();
}

//==============================================================================
// Content - Playlist Tracks
//==============================================================================

void PlaylistWindow::DrawPlaylistContent()
{
    ImGui::BeginChild("##PlaylistContent", ImVec2(0, 0), true);
    
    auto activeIndex = m_data.GetActivePlaylistIndex();
    
    if (!activeIndex.has_value())
    {
        ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y * 0.4f);
        ImGui::TextDisabled("  Select a playlist from the sidebar");
        ImGui::EndChild();
        return;
    }
    
    const auto* playlist = m_data.GetActivePlaylist();
    if (!playlist)
    {
        ImGui::EndChild();
        return;
    }
    
    // Header row
    ImGui::TextColored(m_theme.BrandText, "%s", playlist->name.c_str());
    ImGui::SameLine();
    ImGui::TextDisabled("(%zu tracks)", m_data.GetFilteredTrackCount());
    
    float buttonWidth = 110.0f;
    ImGui::SameLine(ImGui::GetContentRegionAvail().x - buttonWidth);
    if (ImGui::Button("+ Add Tracks", ImVec2(buttonWidth, 0)))
    {
        m_selectedPlaylistForAdd = static_cast<int>(activeIndex.value());
        m_addTrackSearchBuffer[0] = '\0';
        m_data.SetAddTrackSearchFilter("");
        m_selectedAddTrackIndex = -1;
        m_selectedAddTrack = nullptr;
        m_showAddTrackPopup = true;
    }
    
    ImGui::Separator();
    
    // Search within playlist
    ImGui::SetNextItemWidth(200.0f);
    if (ImGui::InputTextWithHint("##PlaylistTrackSearch", "Search tracks...",
                                  m_trackSearchBuffer, sizeof(m_trackSearchBuffer)))
    {
        m_data.SetSearchFilter(m_trackSearchBuffer);
    }
    
    if (m_trackSearchBuffer[0] != '\0')
    {
        ImGui::SameLine();
        if (ImGui::SmallButton("X"))
        {
            m_trackSearchBuffer[0] = '\0';
            m_data.SetSearchFilter("");
        }
    }
    
    ImGui::Separator();
    ImGui::Spacing();
    
    // Track table
    m_trackTable.SetSelectedRow(m_data.GetSelectedIndex(), m_data.GetSelectedTrack());
    m_trackTable.SetPlayingRow(m_data.GetPlayingIndex(), m_data.GetPlayingTrack());
    m_trackTable.Draw(m_data.GetFilteredTracks());
    
    // Right-click context menu for the selected track
    DrawTrackContextMenu(m_data.GetSelectedIndex());
    
    HandleTableSorting();
    
    ImGui::EndChild();
}

//==============================================================================
// Track Context Menu
//==============================================================================

void PlaylistWindow::DrawTrackContextMenu(int trackIndex)
{
    if (trackIndex < 0) return;
    
    auto activeIndex = m_data.GetActivePlaylistIndex();
    if (!activeIndex.has_value()) return;
    
    auto menuResult = m_trackContextMenu.Show();
    if (menuResult.clickedIndex >= 0)
    {
        size_t playlistIdx = activeIndex.value();
        
        switch (menuResult.clickedIndex)
        {
        case 0: // Remove from Playlist
            m_data.RemoveTrackFromPlaylist(playlistIdx, static_cast<size_t>(trackIndex));
            break;
        case 2: // Move Up
            if (trackIndex > 0)
                m_data.MoveTrack(playlistIdx, static_cast<size_t>(trackIndex), static_cast<size_t>(trackIndex - 1));
            break;
        case 3: // Move Down
            if (trackIndex < static_cast<int>(m_data.GetFilteredTrackCount()) - 1)
                m_data.MoveTrack(playlistIdx, static_cast<size_t>(trackIndex), static_cast<size_t>(trackIndex + 1));
            break;
        }
    }
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
        ImGui::Text("Add Tracks to Playlist");
        ImGui::Separator();
        
        // Search bar
        ImGui::SetNextItemWidth(-1);
        if (ImGui::InputTextWithHint("##AddTrackSearch", "Search title, artist or album...",
                                      m_addTrackSearchBuffer, sizeof(m_addTrackSearchBuffer)))
        {
            m_data.SetAddTrackSearchFilter(m_addTrackSearchBuffer);
        }
        
        ImGui::Spacing();
        
        // Track table with library tracks
        auto results = m_data.SearchLibraryForTracks();
        
        if (results.empty())
        {
            ImGui::Separator();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
            if (m_addTrackSearchBuffer[0] != '\0')
                ImGui::TextDisabled("  No tracks found matching \"%s\"", m_addTrackSearchBuffer);
            else
                ImGui::TextDisabled("  No tracks in library. Add music files first.");
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
        
        // Bottom bar: selected track info + Add button + Close button
        if (m_selectedAddTrack)
        {
            ImGui::Text("Selected: %s - %s", 
                m_selectedAddTrack->GetTitle().c_str(),
                m_selectedAddTrack->GetArtist().c_str());
        }
        else
        {
            ImGui::TextDisabled("Select a track to add");
        }
        
        ImGui::SameLine(ImGui::GetContentRegionAvail().x - 200.0f);
        
        bool canAdd = (m_selectedAddTrack != nullptr && m_selectedPlaylistForAdd >= 0);
        
        if (!canAdd) ImGui::BeginDisabled();
        
        if (ImGui::Button("Add Selected", ImVec2(100, 0)))
        {
            m_data.AddTrackToPlaylist(
                static_cast<size_t>(m_selectedPlaylistForAdd),
                m_selectedAddTrack->GetId());
            m_selectedAddTrackIndex = -1;
            m_selectedAddTrack = nullptr;
        }
        
        if (!canAdd) ImGui::EndDisabled();
        
        ImGui::SameLine();
        
        if (ImGui::Button("Close", ImVec2(80, 0)))
        {
            m_selectedAddTrackIndex = -1;
            m_selectedAddTrack = nullptr;
            ImGui::CloseCurrentPopup();
        }
        
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
        ImGui::Text("Create New Playlist");
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::SetNextItemWidth(-1);
        
        if (ImGui::IsWindowAppearing())
            ImGui::SetKeyboardFocusHere();
        
        bool enter = ImGui::InputTextWithHint("##NewPlaylistName", "Playlist name...",
                                               m_newPlaylistNameBuffer, 
                                               sizeof(m_newPlaylistNameBuffer),
                                               ImGuiInputTextFlags_EnterReturnsTrue);
        
        ImGui::Spacing();
        
        bool canCreate = m_newPlaylistNameBuffer[0] != '\0';
        
        if (!canCreate) ImGui::BeginDisabled();
        
        if (ImGui::Button("Create", ImVec2(120, 0)) || (enter && canCreate))
        {
            m_data.CreatePlaylist(m_newPlaylistNameBuffer);
            m_newPlaylistNameBuffer[0] = '\0';
            ImGui::CloseCurrentPopup();
        }
        
        if (!canCreate) ImGui::EndDisabled();
        
        ImGui::SameLine();
        
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
        ImGui::Text("Rename Playlist");
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::SetNextItemWidth(-1);
        
        if (ImGui::IsWindowAppearing())
            ImGui::SetKeyboardFocusHere();
        
        bool enter = ImGui::InputText("##RenamePlaylistName", m_renamePlaylistBuffer,
                                       sizeof(m_renamePlaylistBuffer),
                                       ImGuiInputTextFlags_EnterReturnsTrue);
        
        ImGui::Spacing();
        
        bool canRename = m_renamePlaylistBuffer[0] != '\0' && m_renamePlaylistIndex >= 0;
        
        if (!canRename) ImGui::BeginDisabled();
        
        if (ImGui::Button("Rename", ImVec2(120, 0)) || (enter && canRename))
        {
            m_data.RenamePlaylist(static_cast<size_t>(m_renamePlaylistIndex), m_renamePlaylistBuffer);
            m_renamePlaylistBuffer[0] = '\0';
            m_renamePlaylistIndex = -1;
            ImGui::CloseCurrentPopup();
        }
        
        if (!canRename) ImGui::EndDisabled();
        
        ImGui::SameLine();
        
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            m_renamePlaylistBuffer[0] = '\0';
            m_renamePlaylistIndex = -1;
            ImGui::CloseCurrentPopup();
        }
        
        ImGui::EndPopup();
    }
}

//==============================================================================
// Track Click Handler
//==============================================================================

void PlaylistWindow::OnTrackClicked(const MusicTrack* track, int rowIndex)
{
    if (!track) return;
    
    m_data.SetSelectedIndex(rowIndex);
    m_data.SetPlayingIndex(rowIndex);
    
    if (m_playbackController)
    {
        m_playbackController->SetCurrentTrackList(m_data.GetFilteredTracks());
        m_playbackController->SelectTrack(*track);
        m_playbackController->Play();
    }
}

//==============================================================================
// Sort Handling
//==============================================================================

void PlaylistWindow::HandleTableSorting()
{
    auto sortRequest = m_trackTable.GetSortRequest();
    if (sortRequest)
    {
        m_data.ApplySort(sortRequest.value());
    }
}

} // namespace moosic