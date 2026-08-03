//==============================================================================
// Services/PlaybackController.h (REVISED)
//==============================================================================
// Central playback controller managing audio engine, track navigation,
// playback modes, volume, and visualizer settings.
// Owns PlayerBarData as the single source of truth for all player bar UI state.
// NOW OWNS TEMPORARY TRACKS as well - full ownership of current playback.
//==============================================================================

#pragma once

#include "AudioEngine.h"
#include "../Models/MusicLibrary.h"
#include "../UI/Data/PlayerBarData.h"
#include <vector>
#include <cstddef>
#include <unordered_map>
#include <memory>

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
    
    // Set track list from library tracks (permanent)
    void SetCurrentTrackList(const std::vector<const MusicTrack*>& trackList);
    void SetCurrentTrackListByIds(const std::vector<std::size_t>& trackIds);
    void RefreshTrackList();
    
    // Set a single temporary track (not from library)
    // PlaybackController takes full ownership of the track
    void SetTemporaryTrack(const MusicTrack& track);
    void SetTemporaryTrack(MusicTrack&& track);
    
    // Check if current track is temporary (not in library)
    bool IsCurrentTrackTemporary() const;

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
    // Status
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
    //--------------------------------------------------------------------------

    void Update();

    //--------------------------------------------------------------------------
    // PlayerBarData - Single source of truth for all player bars
    //--------------------------------------------------------------------------

    const PlayerBarData& GetPlayerBarData() const { return m_playerBarData; }

    //--------------------------------------------------------------------------
    // Album Art Cache
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

    // Track list management
    std::vector<std::size_t> m_currentTrackIds;
    size_t m_currentIndex = 0;
    
    // Storage for temporary tracks (owned by controller)
    std::vector<std::unique_ptr<MusicTrack>> m_temporaryTracks;
    std::unordered_map<std::size_t, MusicTrack*> m_allTracks;  // id -> track pointer
    
    // Next ID for temporary tracks (use large numbers to avoid collision with library IDs)
    static constexpr std::size_t TEMPORARY_TRACK_ID_START = 0xFFFFFFFF - 1000;
    std::size_t m_nextTemporaryId = TEMPORARY_TRACK_ID_START;

    PlaybackMode m_playbackMode = PlaybackMode::Normal;
    bool m_trackEndProcessed = false;
    int m_visualizerMode = 0;

    // Single source of truth for all player bar UI state
    PlayerBarData m_playerBarData;

    // Album art cache
    std::unordered_map<std::size_t, CachedAlbumArtData> m_albumArtCache;
};

} // namespace moosic