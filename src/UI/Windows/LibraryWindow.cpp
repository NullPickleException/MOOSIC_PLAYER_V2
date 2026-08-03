//==============================================================================
// UI/Windows/LibraryWindow.cpp
//==============================================================================

#include "LibraryWindow.h"
#include "../Theme/Theme.h"
#include <iostream>
#include <imgui.h>

#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#endif
#include <filesystem>

namespace moosic
{

    //==========================================================================
    // Constructor
    //==========================================================================

    LibraryWindow::LibraryWindow(LibraryDataModel &dataModel,
                                 PlaybackController *playbackController)
        : m_data(dataModel), m_playbackController(playbackController)
    {
        //======================================================================
        // Track Table Configuration
        //======================================================================

        TrackTableConfig config;
        config.Columns = {
            TrackColumn::Title,
            TrackColumn::Artist,
            TrackColumn::Album,
            TrackColumn::Extension,
            TrackColumn::Duration};
        m_trackTable.ApplyConfig(config);

        TrackTableStyle style;
        style.TitleWidth = 350.0f;
        style.ArtistWidth = 180.0f;
        style.AlbumWidth = 180.0f;
        style.ExtensionWidth = 50.0f;
        style.DurationWidth = 80.0f;
        style.RowHeight = 18.0f;
        m_trackTable.ApplyTheme(style);

        //======================================================================
        // Toolbar Defaults
        //======================================================================

        m_toolbarOptions.ShowSearchBar = true;
        m_toolbarOptions.ShowRefreshButton = true;
        m_toolbarOptions.ShowClearButton = false;
        m_toolbarOptions.ShowTrackCount = true;
        m_toolbarOptions.ShowBrandHeader = true;
        m_toolbarOptions.BrandText = "MOOSIC LIBRARY";
        m_toolbarOptions.SearchBarWidth = 500.0f;
        m_toolbarOptions.SearchHint = "Search title, artist or album...";

        SetupSearchBar();

        //======================================================================
        // Track Table Callbacks
        //======================================================================

        m_trackTable.OnRowClick([this](const RowEventData &event)
                                { OnTrackClicked(event.track, event.rowIndex); });

        m_trackTable.OnRowDoubleClick([this](const RowEventData &event)
                                      { OnTrackClicked(event.track, event.rowIndex); });

        //======================================================================
        // Right-Click Context Menu
        //======================================================================

        m_trackTable.OnRowRightClick([this](const RowEventData &event)
                                     {
            m_contextRow = event.rowIndex;
            m_contextTrack = event.track;
            
            std::vector<MenuItem> items;
            BuildContextMenu(items);
            
            m_contextMenu.SetItems(items);
            m_contextMenu.Open(
                ImGui::GetMousePos().x,
                ImGui::GetMousePos().y); });

        //======================================================================
        // Sort Handler
        //======================================================================

        m_trackTable.OnSort([this](const SortRequest &sort)
                            { m_data.ApplySort(sort); });

        //======================================================================
        // Edit Track Dialog
        //======================================================================

        m_editTrackDialog.SetSaveCallback([this](const MusicTrack *track,
                                                 const std::string &title,
                                                 const std::string &artist,
                                                 const std::string &album)
                                          {
            MusicTrack* mutableTrack = const_cast<MusicTrack*>(track);
            mutableTrack->UpdateTitle(title);
            mutableTrack->UpdateArtist(artist);
            mutableTrack->UpdateAlbum(album);
            m_data.NotifyDataChanged(); });

        // Apply theme to edit dialog
        {
            EditTrackDialogTheme dialogTheme;
            dialogTheme.BrandText = m_theme.BrandText;
            dialogTheme.TextPrimary = m_theme.TextPrimary;
            dialogTheme.TextDisabled = m_theme.TextDisabled;
            dialogTheme.FrameBg = m_theme.ChildBg;
            dialogTheme.ButtonNormal = m_theme.ButtonNormal;
            dialogTheme.ButtonHovered = m_theme.ButtonHovered;
            dialogTheme.ButtonActive = m_theme.ButtonActive;
            dialogTheme.ButtonRounding = m_theme.ButtonRounding;
            m_editTrackDialog.SetTheme(dialogTheme);
        }

        m_data.SetOnDataChanged([this]() {});
    }

    //==========================================================================
    // Main Draw
    //==========================================================================

    void LibraryWindow::Draw()
    {
        if (m_data.NeedsRefresh())
            m_data.Refresh();

        if (m_playbackController)
            m_data.SyncPlayingTrack(m_playbackController->GetCurrentTrack());

        DrawHeader();
        DrawToolbar();
        ImGui::Separator();
        DrawTrackTable();

        m_contextMenu.Draw("##LibraryContextMenu");
        m_editTrackDialog.Draw();
    }

    //==========================================================================
    // Header
    //==========================================================================

    void LibraryWindow::DrawHeader()
    {
        if (!m_toolbarOptions.ShowBrandHeader && !m_toolbarOptions.ShowTrackCount)
        {
            ImGui::Separator();
            return;
        }

        if (m_toolbarOptions.ShowBrandHeader)
            ImGui::TextColored(m_theme.BrandText, "%s", m_toolbarOptions.BrandText.c_str());

        if (m_toolbarOptions.ShowTrackCount)
        {
            if (m_toolbarOptions.ShowBrandHeader)
                ImGui::SameLine();
            ImGui::TextColored(m_theme.TextSecondary, "(%zu Tracks)", m_data.GetTrackCount());
        }

        ImGui::Separator();
    }

    //==========================================================================
    // Toolbar
    //==========================================================================

    void LibraryWindow::DrawToolbar()
    {
        bool anyToolbar = m_toolbarOptions.ShowSearchBar ||
                          m_toolbarOptions.ShowRefreshButton ||
                          m_toolbarOptions.ShowClearButton;

        if (!anyToolbar)
            return;

        if (m_toolbarOptions.ShowSearchBar)
        {
            if (m_useDropdownSearch)
            {
                DrawDropdownSearch();
                m_searchBar.BlockExternalScroll();
            }
            else
                DrawInlineSearch();
        }

        if (m_toolbarOptions.ShowClearButton && !m_useDropdownSearch)
        {
            if (m_toolbarOptions.ShowSearchBar)
                ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Clear"))
            {
                m_searchBuffer[0] = '\0';
                m_data.SetSearchFilter("");
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);
        }

        if (m_toolbarOptions.ShowRefreshButton)
        {
            bool hasSearch = m_toolbarOptions.ShowSearchBar;
            bool hasClear = m_toolbarOptions.ShowClearButton && !m_useDropdownSearch;
            if (hasSearch || hasClear)
                ImGui::SameLine();

            ImGui::PushStyleColor(ImGuiCol_Button, m_theme.ButtonNormal);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, m_theme.ButtonHovered);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, m_theme.ButtonActive);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_theme.ButtonRounding);

            if (ImGui::Button("Refresh"))
                m_data.Refresh();

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(3);
        }

        ImGui::Spacing();
    }

    //==========================================================================
    // Dropdown Search
    //==========================================================================

    void LibraryWindow::DrawDropdownSearch()
    {
        m_searchBar.SetWidth(m_toolbarOptions.SearchBarWidth);
        m_searchBar.SetHint(m_toolbarOptions.SearchHint);
        m_searchBar.Draw();
    }

    //==========================================================================
    // Inline Search
    //==========================================================================

    void LibraryWindow::DrawInlineSearch()
    {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, m_theme.ChildBg);
        ImGui::PushStyleColor(ImGuiCol_Text, m_theme.TextPrimary);
        ImGui::PushStyleColor(ImGuiCol_TextDisabled, m_theme.TextDisabled);

        ImGui::SetNextItemWidth(m_toolbarOptions.SearchBarWidth);
        if (ImGui::InputTextWithHint("##Search",
                                     m_toolbarOptions.SearchHint.c_str(),
                                     m_searchBuffer, sizeof(m_searchBuffer)))
        {
            m_data.SetSearchFilter(m_searchBuffer);
        }

        ImGui::PopStyleColor(3);
    }

    //==========================================================================
    // Track Table
    //==========================================================================

    void LibraryWindow::DrawTrackTable()
    {
        m_trackTable.SetSelectedRow(m_data.GetSelectedIndex(),
                                    m_data.GetSelectedTrack());
        m_trackTable.SetPlayingRow(m_data.GetPlayingIndex(),
                                   m_data.GetPlayingTrack());

        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        ImGui::PushStyleColor(ImGuiCol_Border, m_theme.WindowBorder);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, m_theme.ChildBg);

        ImGui::BeginChild("##TrackTableContainer", ImVec2(0, 0), ImGuiChildFlags_Border,
                          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

        m_trackTable.Draw(m_data.GetTracks());

        ImGui::EndChild();

        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar();
    }

    //==========================================================================
    // Track Click Handler
    //==========================================================================

    void LibraryWindow::OnTrackClicked(const MusicTrack *track, int rowIndex)
    {
        if (!track)
            return;

        std::cout << "[LibraryWindow] Playing: " << track->GetTitle()
                  << " (" << track->GetDuration() << "s)\n";

        m_data.SetSelectedIndex(rowIndex);
        m_data.SetPlayingIndex(rowIndex);

        if (m_playbackController)
        {
            m_playbackController->SetCurrentTrackList(m_data.GetTracks());
            m_playbackController->SelectTrack(*track);
            m_playbackController->Play();
        }
    }

    //==========================================================================
    // Context Menu Builder
    //==========================================================================

    void LibraryWindow::BuildContextMenu(std::vector<MenuItem> &items)
    {
        // ── Play ──
        items.push_back({"Play", true, false, [this]()
                         { OnTrackClicked(m_contextTrack, m_contextRow); }});

        items.push_back({"", false, true, nullptr});

        // ── Add to Playlist (Submenu) ──
        if (m_playlistModel && !m_playlistModel->GetAllPlaylists().empty())
        {
            std::vector<MenuItem> playlistItems;
            const auto &playlists = m_playlistModel->GetAllPlaylists();

            for (size_t j = 0; j < playlists.size(); ++j)
            {
                const auto &playlist = playlists[j];
                playlistItems.push_back({playlist.name, true, false, [this, j]()
                                         {
                    if (m_playlistModel && m_contextTrack)
                        m_playlistModel->AddTrackToPlaylist(j, m_contextTrack->GetId()); }});
            }

            // Separator before "New Playlist..."
            playlistItems.push_back({"", false, true, nullptr});

            // "New Playlist..." option
            playlistItems.push_back({"New Playlist...", true, false, [this]()
                                     {
                if (m_playlistModel && m_contextTrack)
                {
                    static int counter = 1;
                    std::string name = "New Playlist " + std::to_string(counter++);
                    m_playlistModel->CreatePlaylist(name);
                    size_t newIndex = m_playlistModel->GetAllPlaylists().size() - 1;
                    m_playlistModel->AddTrackToPlaylist(newIndex, m_contextTrack->GetId());
                } }});

            MenuItem addToPlaylistItem;
            addToPlaylistItem.label = "Add to Playlist";
            addToPlaylistItem.enabled = true;
            addToPlaylistItem.isSeparator = false;
            addToPlaylistItem.isSubmenuArrow = true;
            addToPlaylistItem.children = playlistItems;
            addToPlaylistItem.action = nullptr;

            items.push_back(addToPlaylistItem);
        }
        else
        {
            items.push_back({"Add to Playlist", false, false, nullptr});
        }

        items.push_back({"", false, true, nullptr});

        // ── Open Folder ──
        items.push_back({"Open Folder", true, false, [this]()
                         {
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
            } catch (...) {} }});

        // ── Edit Track Info ──
        items.push_back({"Edit Track Info...", true, false, [this]()
                         { m_editTrackDialog.Open(m_contextTrack); }});
    }

    //==========================================================================
    // Search Bar Setup
    //==========================================================================

    void LibraryWindow::SetupSearchBar()
    {
        m_searchBar.SetWidth(m_toolbarOptions.SearchBarWidth);
        m_searchBar.SetHint(m_toolbarOptions.SearchHint);

        m_searchBar.SetSearchCallback([this](const std::string &query) -> std::vector<TrackSearchResult>
                                      {
            m_data.SetSearchFilter("");
            
            auto allTracks = m_data.GetTracks();
            std::vector<TrackSearchResult> results;
            
            std::string lowerQuery = query;
            std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(),
                [](unsigned char c) { return std::tolower(c); });
            
            for (size_t i = 0; i < allTracks.size() && results.size() < 100; ++i)
            {
                std::string title = allTracks[i]->GetTitle();
                std::string artist = allTracks[i]->GetArtist();
                
                std::string lowerTitle = title;
                std::string lowerArtist = artist;
                std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                std::transform(lowerArtist.begin(), lowerArtist.end(), lowerArtist.begin(),
                    [](unsigned char c) { return std::tolower(c); });
                
                if (lowerTitle.find(lowerQuery) != std::string::npos ||
                    lowerArtist.find(lowerQuery) != std::string::npos)
                {
                    TrackSearchResult r;
                    r.title = title;
                    r.artist = artist;
                    r.displayText = title + "  -  " + artist;
                    r.trackIndex = static_cast<int>(i);
                    results.push_back(r);
                }
            }
            return results; });

        m_searchBar.SetSelectCallback([this](const TrackSearchResult &result)
                                      {
            auto tracks = m_data.GetTracks();
            if (result.trackIndex >= 0 && result.trackIndex < static_cast<int>(tracks.size()))
            {
                OnTrackClicked(tracks[result.trackIndex], result.trackIndex);
            } });
    }

} // namespace moosic