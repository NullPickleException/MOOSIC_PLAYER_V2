//==============================================================================
// MusicLibrary.cpp
//==============================================================================
// Central storage for music tracks and directories
// Uses std::deque for stable pointers during insertion
//==============================================================================

#include "MusicLibrary.h"
#include <algorithm>

namespace moosic
{

//--------------------------------------------------------------------------
// Directory Management
//--------------------------------------------------------------------------

void MusicLibrary::AddDirectory(const std::filesystem::path& directory)
{
    auto it = std::find(m_directories.begin(), m_directories.end(), directory);
    if (it == m_directories.end())
        m_directories.push_back(directory);
}

void MusicLibrary::RemoveDirectory(const std::filesystem::path& directory)
{
    m_directories.erase(
        std::remove(m_directories.begin(), m_directories.end(), directory),
        m_directories.end());
}

const std::vector<std::filesystem::path>& MusicLibrary::GetDirectories() const
{
    return m_directories;
}

bool MusicLibrary::HasDirectory(const std::filesystem::path& directory) const
{
    return std::find(m_directories.begin(), m_directories.end(), directory) 
           != m_directories.end();
}

//--------------------------------------------------------------------------
// Track Management
//--------------------------------------------------------------------------

void MusicLibrary::AddTrack(const MusicTrack& track)
{
    MusicTrack copy = track;
    copy.SetId(m_nextTrackId++);
    m_tracks.push_back(std::move(copy));
    // deque::push_back never invalidates existing pointers/references
}

void MusicLibrary::RemoveTrack(std::size_t id)
{
    m_tracks.erase(
        std::remove_if(m_tracks.begin(), m_tracks.end(),
            [id](const MusicTrack& track) { 
                return track.GetId() == id; 
            }),
        m_tracks.end());
    // WARNING: Removing elements invalidates pointers to erased elements
    // But pointers to other elements remain valid
}

void MusicLibrary::RemoveTracksFromDirectory(const std::filesystem::path& directory)
{
    m_tracks.erase(
        std::remove_if(m_tracks.begin(), m_tracks.end(),
            [&directory](const MusicTrack& track) { 
                return track.GetPath().parent_path() == directory; 
            }),
        m_tracks.end());
    // WARNING: Removing elements invalidates pointers to erased elements
    // But pointers to other elements remain valid
}

const std::deque<MusicTrack>& MusicLibrary::GetTracks() const
{
    return m_tracks;
}

std::size_t MusicLibrary::GetTrackCount() const
{
    return m_tracks.size();
}

//--------------------------------------------------------------------------
// Clear
//--------------------------------------------------------------------------

void MusicLibrary::Clear()
{
    m_directories.clear();
    m_tracks.clear();
    m_nextTrackId = 1;
}

} // namespace moosic