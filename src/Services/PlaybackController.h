//==============================================================================
// PlaybackController.h
//==============================================================================
// Central playback controller managing audio engine, track navigation,
// playback modes, volume, and visualizer settings
//==============================================================================

#pragma once

#include "AudioEngine.h"
#include "../Models/MusicLibrary.h"
#include <vector>

namespace moosic
{

    //==============================================================================
    // Playback Modes
    //==============================================================================

    enum class PlaybackMode
    {
        Normal,  // Play in order, stop at end
        Reverse, // Play in reverse order, stop at beginning
        Repeat,  // Repeat current track only
        Shuffle  // Play in random order
    };

    //==============================================================================
    // PlaybackController
    //==============================================================================

    class PlaybackController
    {
    public:
        explicit PlaybackController(MusicLibrary &library);

        //--------------------------------------------------------------------------
        // Track List Management
        //--------------------------------------------------------------------------

        void SetCurrentTrackList(const std::vector<const MusicTrack *> &trackList);

        //--------------------------------------------------------------------------
        // Track Selection
        //--------------------------------------------------------------------------

        void SelectTrack(const MusicTrack &track);
        void SelectTrackByIndex(size_t index);

        //--------------------------------------------------------------------------
        // Playback Control
        //--------------------------------------------------------------------------

        void Play();
        void Pause();
        void Stop();
        void TogglePlayPause();

        //--------------------------------------------------------------------------
        // Navigation
        //--------------------------------------------------------------------------

        void Next();
        void Previous();
        void SeekTo(float seconds);

        //--------------------------------------------------------------------------
        // Volume
        //--------------------------------------------------------------------------

        void SetVolume(float volume);
        float GetVolume() const;

        //--------------------------------------------------------------------------
        // Status
        //--------------------------------------------------------------------------

        const MusicTrack *GetCurrentTrack() const;
        bool IsPlaying() const;
        bool IsPaused() const;
        bool IsStopped() const;
        bool HasTrack() const;

        float GetCurrentPosition() const;
        float GetCurrentDuration() const;

        //--------------------------------------------------------------------------
        // Playback Modes
        //--------------------------------------------------------------------------

        void SetPlaybackMode(PlaybackMode mode);
        PlaybackMode GetPlaybackMode() const;

        //--------------------------------------------------------------------------
        // Audio Stream
        //--------------------------------------------------------------------------

        HSTREAM GetAudioStream() const { return m_audioEngine.GetStream(); }

        //--------------------------------------------------------------------------
        // Visualizer Mode
        //--------------------------------------------------------------------------

        void SetVisualizerMode(int mode) { m_visualizerMode = mode; }
        int GetVisualizerMode() const { return m_visualizerMode; }

        //--------------------------------------------------------------------------
        // Update
        //--------------------------------------------------------------------------

        void Update();       // Call each frame to check if track ended
        void OnTrackEnded(); // Handle end-of-track auto-advance

    private:
        //--------------------------------------------------------------------------
        // Internal Helpers
        //--------------------------------------------------------------------------

        size_t GetNextIndex() const;
        size_t GetPreviousIndex() const;
        void UpdateTrackList();

    private:
        MusicLibrary &m_library;
        AudioEngine m_audioEngine;

        // Current track list (from library, playlist, etc.)
        std::vector<const MusicTrack *> m_currentTrackList;

        // Playback state
        size_t m_currentIndex = 0;
        PlaybackMode m_playbackMode = PlaybackMode::Normal;
        bool m_trackEndProcessed = false;

        // Visualizer mode (0=Spectrum, 1=Oscilloscope)
        int m_visualizerMode = 0;
    };

} // namespace moosic