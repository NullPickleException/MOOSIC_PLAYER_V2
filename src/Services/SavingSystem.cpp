//==============================================================================
// Services/SavingSystem.cpp
//==============================================================================
// Unified JSON save/load - handles ALL state in one organized file
//==============================================================================

#include "SavingSystem.h"
#include "../Models/MusicLibrary.h"
#include "../Models/MusicTrack.h"
#include "../UI/Data/PlaylistDataModel.h"
#include "../UI/Data/SettingsDataModel.h"
#include "../UI/Data/LayoutStateDataModel.h"
#include "PlaybackController.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

using json = nlohmann::json;

namespace moosic
{

    //==============================================================================
    // Constructor
    //==============================================================================

    SavingSystem::SavingSystem(const std::filesystem::path &savePath)
        : m_savePath(savePath)
    {
    }

    //==============================================================================
    // Save - Unified single JSON file
    //==============================================================================

    bool SavingSystem::Save(const MusicLibrary &library,
                            const PlaylistDataModel &playlists,
                            const PlaybackController &controller,
                            const SettingsDataModel &settings,
                            const LayoutStateDataModel &layoutState)
    {
        try
        {
            json j;

            j["metadata"]["version"] = "1.0.0";
            j["metadata"]["appName"] = "MOOSIC Player";

            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            char timeBuffer[30];
            std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%dT%H:%M:%SZ", std::gmtime(&now_time));
            j["metadata"]["lastSaved"] = timeBuffer;

#ifdef _WIN32
            j["metadata"]["platform"] = "windows";
#elif defined(__APPLE__)
            j["metadata"]["platform"] = "macos";
#else
            j["metadata"]["platform"] = "linux";
#endif

            //----------------------------------------------------------------------
            // Directories
            //----------------------------------------------------------------------
            j["library"]["directories"] = json::array();
            for (const auto &d : library.GetDirectories())
                j["library"]["directories"].push_back(d.u8string());

            //----------------------------------------------------------------------
            // Tracks
            //----------------------------------------------------------------------
            j["library"]["tracks"] = json::array();
            for (const auto &track : library.GetTracks())
            {
                json t;
                t["id"] = track.GetId();
                t["path"] = track.GetPath().u8string();
                t["title"] = track.GetTitle();
                t["artist"] = track.GetArtist();
                t["album"] = track.GetAlbum();
                t["genre"] = track.GetGenre();
                t["trackNumber"] = track.GetTrackNumber();
                t["year"] = track.GetYear();
                t["duration"] = track.GetDuration();
                t["sampleRate"] = track.GetSampleRate();
                t["bitRate"] = track.GetBitRate();
                t["channels"] = track.GetChannels();
                t["favourite"] = track.IsFavourite();
                t["playCount"] = track.GetPlayCount();
                j["library"]["tracks"].push_back(t);
            }

            //----------------------------------------------------------------------
            // Playlists
            //----------------------------------------------------------------------
            j["playlists"] = json::array();
            for (const auto &playlist : playlists.GetAllPlaylists())
            {
                json p;
                p["name"] = playlist.name;
                p["trackIds"] = playlist.trackIds;
                j["playlists"].push_back(p);
            }

            if (playlists.GetActivePlaylistIndex().has_value())
                j["playlists_activeIndex"] = static_cast<int>(playlists.GetActivePlaylistIndex().value());
            else
                j["playlists_activeIndex"] = -1;

            //----------------------------------------------------------------------
            // Player State
            //----------------------------------------------------------------------
            const MusicTrack *currentTrack = controller.GetCurrentTrack();
            j["playerState"]["currentTrackId"] = currentTrack ? currentTrack->GetId() : 0;
            j["playerState"]["position"] = controller.GetCurrentPosition();
            j["playerState"]["volume"] = controller.GetVolume();
            j["playerState"]["isPlaying"] = false;

            switch (controller.GetPlaybackMode())
            {
            case PlaybackMode::Normal:
                j["playerState"]["playbackMode"] = "normal";
                break;
            case PlaybackMode::Shuffle:
                j["playerState"]["playbackMode"] = "shuffle";
                break;
            case PlaybackMode::Repeat:
                j["playerState"]["playbackMode"] = "repeat";
                break;
            case PlaybackMode::Reverse:
                j["playerState"]["playbackMode"] = "reverse";
                break;
            }

            //----------------------------------------------------------------------
            // Settings
            //----------------------------------------------------------------------
            j["settings"]["themeName"] = settings.GetThemeName();
            j["settings"]["visualizerMode"] = settings.GetVisualizerMode();
            j["settings"]["layoutMode"] = settings.GetLayoutMode();
            j["settings"]["logoPath"] = settings.GetLogoPath();
            j["settings"]["fontPath"] = settings.GetFontPath();
            j["settings"]["fontName"] = settings.GetFontName();
            j["settings"]["fontSize"] = settings.GetFontSize();

            //----------------------------------------------------------------------
            // Layout State
            //----------------------------------------------------------------------
            j["layoutState"]["currentLayout"] = static_cast<int>(layoutState.GetCurrentLayout());
            j["layoutState"]["currentTab"] = static_cast<int>(layoutState.GetCurrentTab());
            j["layoutState"]["sidebarWidth"] = layoutState.sidebarWidth;
            j["layoutState"]["miniPlayerActiveWindow"] = static_cast<int>(layoutState.miniPlayerActiveWindow);

            //----------------------------------------------------------------------
            // Atomic save
            //----------------------------------------------------------------------
            std::string tempPath = m_savePath.string() + ".tmp";
            std::ofstream file(tempPath, std::ios::binary);
            if (!file.is_open())
            {
                std::cerr << "[SavingSystem] Failed to open: " << tempPath << "\n";
                return false;
            }

            std::string jsonStr = j.dump(2);
            file.write(jsonStr.c_str(), jsonStr.size());
            file.close();

            std::error_code ec;
            std::filesystem::remove(m_savePath, ec);
            std::filesystem::rename(tempPath, m_savePath, ec);

            std::cout << "[SavingSystem] Saved: " << library.GetTrackCount()
                      << " tracks, " << playlists.GetAllPlaylists().size()
                      << " playlists, theme: " << settings.GetThemeName()
                      << " -> " << m_savePath << "\n";
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[SavingSystem] Save error: " << e.what() << "\n";
            return false;
        }
    }

    //==============================================================================
    // Load - Unified single JSON file
    //==============================================================================

    bool SavingSystem::Load(MusicLibrary &library,
                            PlaylistDataModel &playlists,
                            PlaybackController &controller,
                            SettingsDataModel &settings,
                            LayoutStateDataModel &layoutState)
    {
        try
        {
            std::ifstream file(m_savePath, std::ios::binary);
            if (!file.is_open())
            {
                std::cout << "[SavingSystem] No save file found (first run?) -> " << m_savePath << "\n";
                return false;
            }

            std::string content((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
            file.close();

            if (content.empty())
            {
                std::cout << "[SavingSystem] Empty save file\n";
                return false;
            }

            json j = json::parse(content);

            if (j.contains("metadata"))
            {
                std::cout << "[SavingSystem] Save version: "
                          << j["metadata"].value("version", "unknown")
                          << ", last saved: "
                          << j["metadata"].value("lastSaved", "unknown") << "\n";
            }

            if (j.contains("library"))
            {
                if (j["library"].contains("directories"))
                {
                    for (const auto &dir : j["library"]["directories"])
                    {
                        std::string dirStr = dir.get<std::string>();
                        library.AddDirectory(std::filesystem::u8path(dirStr));
                    }
                }

                if (j["library"].contains("tracks"))
                {
                    for (const auto &trackJson : j["library"]["tracks"])
                    {
                        MusicTrack track;
                        track.SetId(trackJson["id"].get<std::size_t>());

                        std::string pathStr = trackJson["path"].get<std::string>();
                        std::filesystem::path filePath = std::filesystem::u8path(pathStr);
                        track.SetPath(filePath);

                        track.SetTitle(trackJson.value("title", "Unknown Track"));
                        track.SetArtist(trackJson.value("artist", "Unknown Artist"));
                        track.SetAlbum(trackJson.value("album", "Unknown Album"));
                        track.SetGenre(trackJson.value("genre", ""));
                        track.SetTrackNumber(trackJson.value("trackNumber", 0));
                        track.SetYear(trackJson.value("year", 0));
                        track.SetDuration(trackJson.value("duration", 0));
                        track.SetSampleRate(trackJson.value("sampleRate", 0));
                        track.SetBitRate(trackJson.value("bitRate", 0));
                        track.SetChannels(trackJson.value("channels", 0));
                        track.SetFavourite(trackJson.value("favourite", false));
                        track.SetPlayCount(trackJson.value("playCount", 0));

                        if (std::filesystem::exists(filePath))
                            library.AddTrack(track);
                        else
                            std::cout << "[SavingSystem] Missing file: " << pathStr << "\n";
                    }
                }
            }

            if (j.contains("playlists"))
            {
                for (const auto &playlistJson : j["playlists"])
                {
                    std::string name = playlistJson["name"].get<std::string>();
                    playlists.CreatePlaylist(name);
                    size_t index = playlists.GetAllPlaylists().size() - 1;

                    if (playlistJson.contains("trackIds"))
                    {
                        for (const auto &id : playlistJson["trackIds"])
                            playlists.AddTrackToPlaylist(index, id.get<std::size_t>());
                    }
                }

                int activeIndex = j.value("playlists_activeIndex", -1);
                if (activeIndex >= 0)
                    playlists.SetActivePlaylist(static_cast<size_t>(activeIndex));
            }

            if (j.contains("playerState"))
            {
                std::size_t trackId = j["playerState"].value("currentTrackId", 0);
                if (trackId != 0)
                {
                    const auto &tracks = library.GetTracks();
                    auto it = std::find_if(tracks.begin(), tracks.end(),
                                           [trackId](const MusicTrack &t)
                                           { return t.GetId() == trackId; });

                    if (it != tracks.end())
                    {
                        std::vector<const MusicTrack *> trackPtrs;
                        trackPtrs.reserve(tracks.size());
                        for (const auto &t : tracks)
                            trackPtrs.push_back(&t);

                        controller.SetCurrentTrackList(trackPtrs);
                        controller.SelectTrack(*it);
                        controller.SeekTo(j["playerState"].value("position", 0.0f));
                        controller.SetVolume(j["playerState"].value("volume", 0.80f));

                        std::string mode = j["playerState"].value("playbackMode", "normal");
                        if (mode == "normal")
                            controller.SetPlaybackMode(PlaybackMode::Normal);
                        if (mode == "shuffle")
                            controller.SetPlaybackMode(PlaybackMode::Shuffle);
                        if (mode == "repeat")
                            controller.SetPlaybackMode(PlaybackMode::Repeat);
                        if (mode == "reverse")
                            controller.SetPlaybackMode(PlaybackMode::Reverse);
                    }
                }
            }

            if (j.contains("settings"))
            {
                settings.SetThemeName(j["settings"].value("themeName", "Dark"));
                settings.SetVisualizerMode(j["settings"].value("visualizerMode", 0));
                settings.SetLayoutMode(j["settings"].value("layoutMode", 0));
                settings.SetLogoPath(j["settings"].value("logoPath", ""));
                settings.SetFontPath(j["settings"].value("fontPath", ""));
                settings.SetFontName(j["settings"].value("fontName", "Default"));
                settings.SetFontSize(j["settings"].value("fontSize", 16.0f));
            }

            //----------------------------------------------------------------------
            // Layout State
            //----------------------------------------------------------------------
            if (j["layoutState"].contains("currentLayout"))
                layoutState.SetCurrentLayout(static_cast<LayoutStateDataModel::Layout>(j["layoutState"]["currentLayout"].get<int>()));
            if (j["layoutState"].contains("currentTab"))
                layoutState.SetCurrentTab(static_cast<LayoutStateDataModel::Tab>(j["layoutState"]["currentTab"].get<int>()));

            std::cout << "[SavingSystem] Loaded: " << library.GetTrackCount()
                      << " tracks, " << playlists.GetAllPlaylists().size()
                      << " playlists <- " << m_savePath << "\n";
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[SavingSystem] Load error: " << e.what() << "\n";
            return false;
        }
    }

} // namespace moosic