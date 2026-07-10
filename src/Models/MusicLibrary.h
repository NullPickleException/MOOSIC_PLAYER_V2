#pragma once

#include "MusicTrack.h"
#include <filesystem>
#include <vector>

namespace moosic
{

class MusicLibrary
{
public:
    MusicLibrary() = default;
    ~MusicLibrary() = default;

    //----------------------------------------------------------
    // Directory Management
    //----------------------------------------------------------

    void AddDirectory(const std::filesystem::path& directory);
    void RemoveDirectory(const std::filesystem::path& directory);
    const std::vector<std::filesystem::path>& GetDirectories() const;
    bool HasDirectory(const std::filesystem::path& directory) const;

    //----------------------------------------------------------
    // Track Management
    //----------------------------------------------------------

    void AddTrack(const MusicTrack& track);
    void RemoveTrack(std::size_t id);
    void RemoveTracksFromDirectory(const std::filesystem::path& directory);
    const std::vector<MusicTrack>& GetTracks() const;
    std::size_t GetTrackCount() const;

    //----------------------------------------------------------
    // Clear
    //----------------------------------------------------------

    void Clear();

private:
    std::vector<std::filesystem::path> m_directories;
    std::vector<MusicTrack> m_tracks;
    std::size_t m_nextTrackId = 1;
};

}