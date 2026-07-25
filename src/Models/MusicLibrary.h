//==============================================================================
// MusicLibrary.h
//==============================================================================
// Central storage for music tracks and directories
// Uses std::deque for stable pointers during insertion
//==============================================================================

#pragma once

#include "MusicTrack.h"
#include <deque>
#include <filesystem>
#include <vector>

namespace moosic
{

class MusicLibrary
{
public:
    MusicLibrary() = default;
    ~MusicLibrary() = default;

    //--------------------------------------------------------------------------
    // Directory Management
    //--------------------------------------------------------------------------

    void AddDirectory(const std::filesystem::path& directory);
    void RemoveDirectory(const std::filesystem::path& directory);
    const std::vector<std::filesystem::path>& GetDirectories() const;
    bool HasDirectory(const std::filesystem::path& directory) const;

    //--------------------------------------------------------------------------
    // Track Management
    //--------------------------------------------------------------------------

    void AddTrack(const MusicTrack& track);
    void RemoveTrack(std::size_t id);
    void RemoveTracksFromDirectory(const std::filesystem::path& directory);
    const std::deque<MusicTrack>& GetTracks() const;
    std::size_t GetTrackCount() const;

    //--------------------------------------------------------------------------
    // Clear
    //--------------------------------------------------------------------------

    void Clear();

private:
    std::vector<std::filesystem::path> m_directories;
    std::deque<MusicTrack> m_tracks;  // deque never invalidates pointers on push_back
    std::size_t m_nextTrackId = 1;
};

} // namespace moosic