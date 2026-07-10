#pragma once

#include "../Models/MusicTrack.h"
#include <bass.h>  // ADD THIS - defines HSTREAM
#include <atomic>
#include <mutex>

namespace moosic
{

class AudioEngine
{
public:
    AudioEngine();
    ~AudioEngine();

    //----------------------------------------------------------
    // Playback Control
    //----------------------------------------------------------

    bool Open(const MusicTrack& track);
    void Start();
    void Pause();
    void Resume();
    void Stop();
    void TogglePlayPause();

    //----------------------------------------------------------
    // Seeking & Volume
    //----------------------------------------------------------

    void SetPosition(float seconds);
    void SetVolume(float volume);  // 0.0 to 1.0

    //----------------------------------------------------------
    // Status
    //----------------------------------------------------------

    bool IsPlaying() const;
    bool IsPaused() const;
    bool IsStopped() const;
    bool HasTrack() const;

    float GetPosition() const;     // seconds
    float GetDuration() const;     // seconds
    float GetVolume() const;       // 0.0 to 1.0

    const MusicTrack* GetCurrentTrack() const;

private:
    //----------------------------------------------------------
    // Internal Helpers
    //----------------------------------------------------------

    void CloseStream();
    void UpdatePlaybackState();

private:
    // BASS stream handle - now HSTREAM is defined because bass.h is included
    HSTREAM m_stream = 0;

    // Current track
    const MusicTrack* m_currentTrack = nullptr;

    // State
    enum class State
    {
        Stopped,
        Playing,
        Paused
    };
    State m_state = State::Stopped;

    // Volume
    float m_volume = 1.0f;

    // Thread safety
    mutable std::mutex m_mutex;

    // BASS initialized flag
    bool m_bassInitialized = false;
};

} // namespace moosic