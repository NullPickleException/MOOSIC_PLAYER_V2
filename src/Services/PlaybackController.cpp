#include "PlaybackController.h"

#include <iostream>
#include <algorithm>
#include <random>

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
// Track List Management
//==============================================================================

void PlaybackController::SetCurrentTrackList(const std::vector<const MusicTrack*>& trackList)
{
    m_currentTrackList = trackList;
    std::cout << "[PlaybackController] Track list updated: " << m_currentTrackList.size() << " tracks\n";
}

//==============================================================================
// Track Selection
//==============================================================================

void PlaybackController::SelectTrack(const MusicTrack& track)
{
    auto it = std::find_if(m_currentTrackList.begin(), m_currentTrackList.end(),
        [&track](const MusicTrack* t) {
            return t && t->GetId() == track.GetId();
        });

    if (it != m_currentTrackList.end())
    {
        m_currentIndex = std::distance(m_currentTrackList.begin(), it);
        m_audioEngine.Open(track);
        std::cout << "[PlaybackController] Selected: " << track.GetTitle() << "\n";
    }
}

void PlaybackController::SelectTrackByIndex(size_t index)
{
    if (index < m_currentTrackList.size() && m_currentTrackList[index])
    {
        m_currentIndex = index;
        m_audioEngine.Open(*m_currentTrackList[index]);
        std::cout << "[PlaybackController] Selected index: " << index << "\n";
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
        if (!m_currentTrackList.empty())
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
    
    if (m_currentTrackList.empty())
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
    if (nextIndex == m_currentIndex)
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
    
    if (m_currentTrackList.empty())
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
    if (m_currentTrackList.empty())
    {
        const auto& tracks = m_library.GetTracks();
        m_currentTrackList.clear();
        m_currentTrackList.reserve(tracks.size());
        for (const auto& track : tracks)
            m_currentTrackList.push_back(&track);
    }
}

size_t PlaybackController::GetNextIndex() const
{
    if (m_currentTrackList.empty())
        return 0;

    switch (m_playbackMode)
    {
        case PlaybackMode::Normal:
        {
            size_t nextIndex = m_currentIndex + 1;
            if (nextIndex >= m_currentTrackList.size())
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
            if (m_currentTrackList.size() > 1)
            {
                std::uniform_int_distribution<size_t> dis(0, m_currentTrackList.size() - 1);
                size_t newIndex;
                do {
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
    if (m_currentTrackList.empty())
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
            if (prevIndex >= m_currentTrackList.size())
                return m_currentIndex; // Stop at end
            return prevIndex;
        }
        
        case PlaybackMode::Repeat:
            return m_currentIndex; // Stay on same track
        
        case PlaybackMode::Shuffle:
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            if (m_currentTrackList.size() > 1)
            {
                std::uniform_int_distribution<size_t> dis(0, m_currentTrackList.size() - 1);
                size_t newIndex;
                do {
                    newIndex = dis(gen);
                } while (newIndex == m_currentIndex);
                return newIndex;
            }
            return m_currentIndex;
        }
    }
    
    return m_currentIndex;
}

} // namespace moosic