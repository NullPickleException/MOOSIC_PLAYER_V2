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
#include <cstddef>

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
        void SetCurrentTrackListByIds(const std::vector<std::size_t> &trackIds);
        void RefreshTrackList();  // Rebuild from library (call after library changes)

        //--------------------------------------------------------------------------
        // Track Selection
        //--------------------------------------------------------------------------

        void SelectTrack(const MusicTrack &track);
        void SelectTrackByIndex(size_t index);
        void SelectTrackById(std::size_t trackId);

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
        
        // Safe track lookup - returns nullptr if track no longer exists
        const MusicTrack* GetTrackById(std::size_t id) const;
        const MusicTrack* GetCurrentTrackSafe() const;

    private:
        MusicLibrary &m_library;
        AudioEngine m_audioEngine;

        // Current track list - STORES IDs, NOT POINTERS!
        // This prevents dangling pointers when vector reallocates
        std::vector<std::size_t> m_currentTrackIds;

        // Playback state
        size_t m_currentIndex = 0;
        PlaybackMode m_playbackMode = PlaybackMode::Normal;
        bool m_trackEndProcessed = false;

        // Visualizer mode (0=Spectrum, 1=Oscilloscope)
        int m_visualizerMode = 0;
    };

} // namespace moosic