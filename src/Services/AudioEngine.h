#pragma once

#include "../Models/MusicTrack.h"
#include <bass.h>
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

        bool Open(const MusicTrack &track);
        void Start();
        void Pause();
        void Resume();
        void Stop();
        void TogglePlayPause();

        //----------------------------------------------------------
        // Seeking & Volume
        //----------------------------------------------------------

        void SetPosition(float seconds);
        void SetVolume(float volume);

        //----------------------------------------------------------
        // Status
        //----------------------------------------------------------

        bool IsPlaying() const;
        bool IsPaused() const;
        bool IsStopped() const;
        bool HasTrack() const;

        float GetPosition() const;
        float GetDuration() const;
        float GetVolume() const;

        const MusicTrack *GetCurrentTrack() const;
        HSTREAM GetStream() const { return m_stream; }

    private:
        void CloseStream();
        void UpdatePlaybackState();

    private:
        HSTREAM m_stream = 0;
        const MusicTrack *m_currentTrack = nullptr;

        enum class State
        {
            Stopped,
            Playing,
            Paused
        };
        State m_state = State::Stopped;

        float m_volume = 1.0f;
        mutable std::mutex m_mutex;
    };

} // namespace moosic