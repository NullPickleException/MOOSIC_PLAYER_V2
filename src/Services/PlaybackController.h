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
#include <unordered_map>

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
    // Cached Album Art Data (raw bytes, not textures)
    //==============================================================================

    struct CachedAlbumArtData
    {
        std::vector<unsigned char> data;
        int width = 0;
        int height = 0;
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
        void RefreshTrackList();

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

        void Update();
        void OnTrackEnded();

        //--------------------------------------------------------------------------
        // Album Art Cache (shared across all player bars)
        //--------------------------------------------------------------------------

        const CachedAlbumArtData* GetCachedAlbumArt(std::size_t trackId) const;
        void CacheAlbumArt(std::size_t trackId, const std::vector<unsigned char>& data, int width, int height);
        void ClearAlbumArtCache();

    private:
        //--------------------------------------------------------------------------
        // Internal Helpers
        //--------------------------------------------------------------------------

        size_t GetNextIndex() const;
        size_t GetPreviousIndex() const;
        void UpdateTrackList();
        
        const MusicTrack* GetTrackById(std::size_t id) const;
        const MusicTrack* GetCurrentTrackSafe() const;
        void IncrementPlayCount(std::size_t trackId);

    private:
        MusicLibrary &m_library;
        AudioEngine m_audioEngine;

        std::vector<std::size_t> m_currentTrackIds;
        size_t m_currentIndex = 0;
        PlaybackMode m_playbackMode = PlaybackMode::Normal;
        bool m_trackEndProcessed = false;
        int m_visualizerMode = 0;

        // Album art cache - raw image data, renderer-independent
        std::unordered_map<std::size_t, CachedAlbumArtData> m_albumArtCache;
    };

} // namespace moosic