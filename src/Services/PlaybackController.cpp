//==============================================================================
// Services/PlaybackController.cpp
//==============================================================================

#include "PlaybackController.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <cstdio>

namespace moosic
{

//==============================================================================
// Constructor
//==============================================================================

PlaybackController::PlaybackController(MusicLibrary& library)
    : m_library(library)
{
    std::cout << "[PlaybackController] Initialized\n";
}

//==============================================================================
// Safe Track Lookup
//==============================================================================

const MusicTrack* PlaybackController::GetTrackById(std::size_t id) const
{
    const auto& tracks = m_library.GetTracks();
    auto it = std::find_if(tracks.begin(), tracks.end(),
                           [id](const MusicTrack& t)
                           { return t.GetId() == id; });
    return (it != tracks.end()) ? &(*it) : nullptr;
}

const MusicTrack* PlaybackController::GetCurrentTrackSafe() const
{
    if (m_currentIndex < m_currentTrackIds.size())
        return GetTrackById(m_currentTrackIds[m_currentIndex]);
    return nullptr;
}

void PlaybackController::IncrementPlayCount(std::size_t trackId)
{
    auto& tracks = m_library.GetTracks();
    for (auto& t : tracks)
    {
        if (t.GetId() == trackId)
        {
            t.IncrementPlayCount();
            break;
        }
    }
}

//==============================================================================
// Track List Management
//==============================================================================

void PlaybackController::SetCurrentTrackList(const std::vector<const MusicTrack*>& trackList)
{
    m_currentTrackIds.clear();
    m_currentTrackIds.reserve(trackList.size());
    for (const auto* track : trackList)
    {
        if (track)
            m_currentTrackIds.push_back(track->GetId());
    }
    std::cout << "[PlaybackController] Track list updated: " << m_currentTrackIds.size() << " tracks\n";
}

void PlaybackController::SetCurrentTrackListByIds(const std::vector<std::size_t>& trackIds)
{
    m_currentTrackIds = trackIds;
    std::cout << "[PlaybackController] Track list updated by IDs: " << m_currentTrackIds.size() << " tracks\n";
}

void PlaybackController::RefreshTrackList()
{
    const auto& tracks = m_library.GetTracks();
    m_currentTrackIds.clear();
    m_currentTrackIds.reserve(tracks.size());
    for (const auto& track : tracks)
        m_currentTrackIds.push_back(track.GetId());
    std::cout << "[PlaybackController] Track list refreshed: " << m_currentTrackIds.size() << " tracks\n";
}

//==============================================================================
// Track Selection
//==============================================================================

void PlaybackController::SelectTrackByIndex(size_t index)
{
    if (index < m_currentTrackIds.size())
    {
        const MusicTrack* track = GetTrackById(m_currentTrackIds[index]);
        if (track)
        {
            m_currentIndex = index;
            m_audioEngine.Open(*track);
            m_audioEngine.SetPosition(0.0f);
            m_trackEndProcessed = false;

            // Increment play count
            IncrementPlayCount(m_currentTrackIds[index]);

            std::cout << "[PlaybackController] Selected index: " << index << "\n";
        }
        else
        {
            std::cout << "[PlaybackController] Track at index " << index << " no longer exists\n";
        }
    }
}

void PlaybackController::SelectTrack(const MusicTrack& track)
{
    std::size_t trackId = track.GetId();

    auto it = std::find(m_currentTrackIds.begin(), m_currentTrackIds.end(), trackId);
    if (it != m_currentTrackIds.end())
    {
        m_currentIndex = std::distance(m_currentTrackIds.begin(), it);
        m_audioEngine.Open(track);
        m_trackEndProcessed = false;

        // Increment play count
        IncrementPlayCount(trackId);

        std::cout << "[PlaybackController] Selected: " << track.GetTitle() << "\n";
    }
    else
    {
        m_currentTrackIds.push_back(trackId);
        m_currentIndex = m_currentTrackIds.size() - 1;
        m_audioEngine.Open(track);
        m_trackEndProcessed = false;

        // Increment play count
        IncrementPlayCount(trackId);

        std::cout << "[PlaybackController] Selected (added to list): " << track.GetTitle() << "\n";
    }
}

void PlaybackController::SelectTrackById(std::size_t trackId)
{
    auto it = std::find(m_currentTrackIds.begin(), m_currentTrackIds.end(), trackId);
    if (it != m_currentTrackIds.end())
    {
        m_currentIndex = std::distance(m_currentTrackIds.begin(), it);
        const MusicTrack* track = GetTrackById(trackId);
        if (track)
        {
            m_audioEngine.Open(*track);
            m_trackEndProcessed = false;

            // Increment play count
            IncrementPlayCount(trackId);

            std::cout << "[PlaybackController] Selected by ID: " << track->GetTitle() << "\n";
        }
    }
}

//==============================================================================
// Playback Control
//==============================================================================

void PlaybackController::Play()
{
    if (!m_audioEngine.HasTrack())
    {
        UpdateTrackList();
        if (!m_currentTrackIds.empty())
        {
            SelectTrackByIndex(0);
        }
        else
        {
            std::cout << "[PlaybackController] No tracks in list\n";
            return;
        }
    }

    m_audioEngine.Start();
}

void PlaybackController::Pause()
{
    m_audioEngine.Pause();
}

void PlaybackController::Stop()
{
    m_audioEngine.Stop();
}

void PlaybackController::TogglePlayPause()
{
    if (m_audioEngine.IsPlaying())
        Pause();
    else
        Play();
}

//==============================================================================
// Navigation
//==============================================================================

void PlaybackController::Next()
{
    UpdateTrackList();

    if (m_currentTrackIds.empty())
        return;

    // Repeat mode: restart current track
    if (m_playbackMode == PlaybackMode::Repeat)
    {
        m_audioEngine.SetPosition(0.0f);
        m_audioEngine.Start();
        return;
    }

    size_t nextIndex = GetNextIndex();

    // If no valid next index, stop
    if (nextIndex == m_currentIndex && m_playbackMode != PlaybackMode::Shuffle)
    {
        Stop();
        return;
    }

    SelectTrackByIndex(nextIndex);
    m_audioEngine.Start();
}

void PlaybackController::Previous()
{
    UpdateTrackList();

    if (m_currentTrackIds.empty())
        return;

    // Repeat mode: restart current track
    if (m_playbackMode == PlaybackMode::Repeat)
    {
        m_audioEngine.SetPosition(0.0f);
        m_audioEngine.Start();
        return;
    }

    // If we're more than 3 seconds in, restart current track
    if (m_audioEngine.GetPosition() > 3.0f)
    {
        m_audioEngine.SetPosition(0.0f);
        m_audioEngine.Start();
        return;
    }

    size_t prevIndex = GetPreviousIndex();
    SelectTrackByIndex(prevIndex);
    m_audioEngine.Start();
}

void PlaybackController::SeekTo(float seconds)
{
    m_audioEngine.SetPosition(seconds);
}

//==============================================================================
// Volume
//==============================================================================

void PlaybackController::SetVolume(float volume)
{
    m_audioEngine.SetVolume(std::clamp(volume, 0.0f, 1.0f));
}

float PlaybackController::GetVolume() const
{
    return m_audioEngine.GetVolume();
}

//==============================================================================
// Status
//==============================================================================

const MusicTrack* PlaybackController::GetCurrentTrack() const
{
    return m_audioEngine.GetCurrentTrack();
}

bool PlaybackController::IsPlaying() const
{
    return m_audioEngine.IsPlaying();
}

bool PlaybackController::IsPaused() const
{
    return m_audioEngine.IsPaused();
}

bool PlaybackController::IsStopped() const
{
    return m_audioEngine.IsStopped();
}

bool PlaybackController::HasTrack() const
{
    return m_audioEngine.HasTrack();
}

float PlaybackController::GetCurrentPosition() const
{
    return m_audioEngine.GetPosition();
}

float PlaybackController::GetCurrentDuration() const
{
    return m_audioEngine.GetDuration();
}

//==============================================================================
// Playback Modes
//==============================================================================

void PlaybackController::SetPlaybackMode(PlaybackMode mode)
{
    m_playbackMode = mode;

    const char* modeNames[] = {"Normal", "Reverse", "Repeat", "Shuffle"};
    std::cout << "[PlaybackController] Mode: " << modeNames[static_cast<int>(mode)] << "\n";
}

PlaybackMode PlaybackController::GetPlaybackMode() const
{
    return m_playbackMode;
}

//==============================================================================
// Internal Helpers
//==============================================================================

void PlaybackController::UpdateTrackList()
{
    if (m_currentTrackIds.empty())
    {
        const auto& tracks = m_library.GetTracks();
        m_currentTrackIds.clear();
        m_currentTrackIds.reserve(tracks.size());
        for (const auto& track : tracks)
            m_currentTrackIds.push_back(track.GetId());
    }
}

size_t PlaybackController::GetNextIndex() const
{
    if (m_currentTrackIds.empty())
        return 0;

    switch (m_playbackMode)
    {
    case PlaybackMode::Normal:
    {
        size_t nextIndex = m_currentIndex + 1;
        if (nextIndex >= m_currentTrackIds.size())
            return m_currentIndex; // Stop at end
        return nextIndex;
    }

    case PlaybackMode::Reverse:
    {
        // In reverse mode, "next" goes backwards
        if (m_currentIndex == 0)
            return m_currentIndex; // Stop at beginning
        return m_currentIndex - 1;
    }

    case PlaybackMode::Repeat:
        return m_currentIndex; // Stay on same track

    case PlaybackMode::Shuffle:
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        if (m_currentTrackIds.size() > 1)
        {
            std::uniform_int_distribution<size_t> dis(0, m_currentTrackIds.size() - 1);
            size_t newIndex;
            do
            {
                newIndex = dis(gen);
            } while (newIndex == m_currentIndex);
            return newIndex;
        }
        return m_currentIndex;
    }
    }

    return m_currentIndex;
}

size_t PlaybackController::GetPreviousIndex() const
{
    if (m_currentTrackIds.empty())
        return 0;

    switch (m_playbackMode)
    {
    case PlaybackMode::Normal:
    {
        if (m_currentIndex == 0)
            return 0;
        return m_currentIndex - 1;
    }

    case PlaybackMode::Reverse:
    {
        // In reverse mode, "previous" goes forward
        size_t prevIndex = m_currentIndex + 1;
        if (prevIndex >= m_currentTrackIds.size())
            return m_currentIndex; // Stop at end
        return prevIndex;
    }

    case PlaybackMode::Repeat:
        return m_currentIndex; // Stay on same track

    case PlaybackMode::Shuffle:
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        if (m_currentTrackIds.size() > 1)
        {
            std::uniform_int_distribution<size_t> dis(0, m_currentTrackIds.size() - 1);
            size_t newIndex;
            do
            {
                newIndex = dis(gen);
            } while (newIndex == m_currentIndex);
            return newIndex;
        }
        return m_currentIndex;
    }
    }

    return m_currentIndex;
}

//==============================================================================
// Update (call once per frame from main loop)
//==============================================================================

void PlaybackController::Update()
{
    // Track end detection
    if (m_playbackMode != PlaybackMode::Repeat && m_audioEngine.HasTrack() && m_audioEngine.IsPlaying())
    {
        float position = m_audioEngine.GetPosition();
        float duration = m_audioEngine.GetDuration();

        if (duration > 0.0f && position >= duration - 0.1f)
        {
            if (!m_trackEndProcessed)
            {
                m_trackEndProcessed = true;
                OnTrackEnded();
            }
        }
        else
        {
            m_trackEndProcessed = false;
        }
    }

    // Always refresh PlayerBarData so bars have latest state
    UpdatePlayerBarData();
}


void PlaybackController::OnTrackEnded()
{
    std::cout << "[PlaybackController] Track ended, advancing to next\n";

    if (m_currentTrackIds.empty())
    {
        UpdateTrackList();
        if (m_currentTrackIds.empty())
            return;
    }

    size_t nextIndex = GetNextIndex();

    // If at end of list, loop back to first track instead of stopping
    if (nextIndex == m_currentIndex && m_playbackMode == PlaybackMode::Normal)
    {
        // Check if we're at the last track
        if (m_currentIndex >= m_currentTrackIds.size() - 1)
        {
            // Loop back to first track
            nextIndex = 0;
        }
        else
        {
            Stop();
            return;
        }
    }
    // For Reverse mode, loop back to last track
    else if (nextIndex == m_currentIndex && m_playbackMode == PlaybackMode::Reverse)
    {
        if (m_currentIndex == 0)
        {
            nextIndex = m_currentTrackIds.size() - 1;
        }
        else
        {
            Stop();
            return;
        }
    }

    SelectTrackByIndex(nextIndex);
    m_audioEngine.Start();
}

//==============================================================================
// PlayerBarData Update
//==============================================================================

void PlaybackController::UpdatePlayerBarData()
{
    const MusicTrack* track = GetCurrentTrack();
    std::size_t newTrackId = track ? track->GetId() : 0;

    // Detect track change
    m_playerBarData.trackJustChanged = (newTrackId != m_playerBarData.currentTrackId);
    m_playerBarData.currentTrackId = newTrackId;

    // Track info
    if (track)
    {
        m_playerBarData.title = track->GetTitle();
        m_playerBarData.artist = track->GetArtist();
        m_playerBarData.album = track->GetAlbum();
        m_playerBarData.durationSeconds = static_cast<float>(track->GetDuration());
        m_playerBarData.hasTrack = true;
    }
    else
    {
        m_playerBarData.title = "No Song Playing";
        m_playerBarData.artist = "Unknown Artist";
        m_playerBarData.album.clear();
        m_playerBarData.durationSeconds = 0.0f;
        m_playerBarData.hasTrack = false;
    }

    // Playback state
    m_playerBarData.isPlaying = m_audioEngine.IsPlaying();
    m_playerBarData.isPaused = m_audioEngine.IsPaused();
    m_playerBarData.isStopped = m_audioEngine.IsStopped();
    m_playerBarData.positionSeconds = m_audioEngine.GetPosition();

    if (m_playerBarData.durationSeconds > 0.0f)
        m_playerBarData.progress = m_playerBarData.positionSeconds / m_playerBarData.durationSeconds;
    else
        m_playerBarData.progress = 0.0f;

    // Format times
    auto fmt = [](float secs) -> std::string {
        int m = static_cast<int>(secs) / 60;
        int s = static_cast<int>(secs) % 60;
        char buf[8];
        snprintf(buf, sizeof(buf), "%02d:%02d", m, s);
        return buf;
    };
    m_playerBarData.elapsedFormatted = fmt(m_playerBarData.positionSeconds);
    m_playerBarData.totalFormatted = fmt(m_playerBarData.durationSeconds);

    // Volume
    m_playerBarData.volume = m_audioEngine.GetVolume();

    // Playback mode
    m_playerBarData.playbackMode = m_playbackMode;
    switch (m_playbackMode)
    {
    case PlaybackMode::Normal:  m_playerBarData.modeLabel = "Normal";  break;
    case PlaybackMode::Reverse: m_playerBarData.modeLabel = "Reverse"; break;
    case PlaybackMode::Repeat:  m_playerBarData.modeLabel = "Repeat";  break;
    case PlaybackMode::Shuffle: m_playerBarData.modeLabel = "Shuffle"; break;
    }

    // Visualizer
    m_playerBarData.visualizerMode = m_visualizerMode;
    m_playerBarData.audioStream = m_audioEngine.GetStream();

    // Album art cache - ONLY copy when it actually changed
    static size_t lastCacheSize = 0;
    if (m_albumArtCache.size() != lastCacheSize)
    {
        m_playerBarData.albumArtCache = m_albumArtCache;
        lastCacheSize = m_albumArtCache.size();
    }
}


//==============================================================================
// Album Art Cache
//==============================================================================

void PlaybackController::CacheAlbumArt(std::size_t trackId, const std::vector<unsigned char>& data, int width, int height)
{
    if (trackId == 0 || data.empty())
        return;
    m_albumArtCache[trackId] = {data, width, height};
}

void PlaybackController::ClearAlbumArtCache()
{
    m_albumArtCache.clear();
}

} // namespace moosic