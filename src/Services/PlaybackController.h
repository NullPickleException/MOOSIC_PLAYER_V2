//==============================================================================
// Services/PlaybackController.h
//==============================================================================
// Central playback controller managing audio engine, track navigation,
// playback modes, volume, and visualizer settings.
// Owns PlayerBarData as the single source of truth for all player bar UI state.
//==============================================================================

#pragma once

#include "AudioEngine.h"
#include "../Models/MusicLibrary.h"
#include "../UI/Data/PlayerBarData.h"
#include <vector>
#include <cstddef>
#include <unordered_map>

namespace moosic
{

//==============================================================================
// PlaybackController
//==============================================================================

class PlaybackController
{
public:
    explicit PlaybackController(MusicLibrary& library);

    //--------------------------------------------------------------------------
    // Track List Management
    //--------------------------------------------------------------------------

    void SetCurrentTrackList(const std::vector<const MusicTrack*>& trackList);
    void SetCurrentTrackListByIds(const std::vector<std::size_t>& trackIds);
    void RefreshTrackList();

    //--------------------------------------------------------------------------
    // Track Selection
    //--------------------------------------------------------------------------

    void SelectTrack(const MusicTrack& track);
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
    // Status (direct engine queries, used by non-UI code)
    //--------------------------------------------------------------------------

    const MusicTrack* GetCurrentTrack() const;
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
    // Update (call once per frame from main loop)
    // Handles track end detection AND refreshes PlayerBarData
    //--------------------------------------------------------------------------

    void Update();

    //--------------------------------------------------------------------------
    // PlayerBarData - Single source of truth for all player bars
    //--------------------------------------------------------------------------

    const PlayerBarData& GetPlayerBarData() const { return m_playerBarData; }

    //--------------------------------------------------------------------------
    // Album Art Cache (raw bytes stored in PlayerBarData)
    //--------------------------------------------------------------------------

    void CacheAlbumArt(std::size_t trackId, const std::vector<unsigned char>& data, int width, int height);
    void ClearAlbumArtCache();

private:
    //--------------------------------------------------------------------------
    // Internal Helpers
    //--------------------------------------------------------------------------

    size_t GetNextIndex() const;
    size_t GetPreviousIndex() const;
    void UpdateTrackList();
    void OnTrackEnded();
    void UpdatePlayerBarData();

    const MusicTrack* GetTrackById(std::size_t id) const;
    const MusicTrack* GetCurrentTrackSafe() const;
    void IncrementPlayCount(std::size_t trackId);

    //--------------------------------------------------------------------------
    // Members
    //--------------------------------------------------------------------------

    MusicLibrary& m_library;
    AudioEngine m_audioEngine;

    std::vector<std::size_t> m_currentTrackIds;
    size_t m_currentIndex = 0;
    PlaybackMode m_playbackMode = PlaybackMode::Normal;
    bool m_trackEndProcessed = false;
    int m_visualizerMode = 0;

    // Single source of truth for all player bar UI state
    PlayerBarData m_playerBarData;

    // Album art cache - raw image data, renderer-independent
    std::unordered_map<std::size_t, CachedAlbumArtData> m_albumArtCache;
};

} // namespace moosic