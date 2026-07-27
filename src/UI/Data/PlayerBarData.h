//==============================================================================
// UI/Data/PlayerBarData.h
//==============================================================================
// Single source of truth for all player bar rendering state.
// Owned by PlaybackController. Read by IPlayerBar implementations.
// Also defines shared types PlaybackMode and CachedAlbumArtData to avoid
// circular includes between controller and data.
//==============================================================================

#pragma once

#include "../../Services/BassHeaders.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cstddef>

namespace moosic
{

//==============================================================================
// Playback Modes (moved here to avoid circular includes)
//==============================================================================

enum class PlaybackMode
{
    Normal,  // Play in order, stop at end
    Reverse, // Play in reverse order, stop at beginning
    Repeat,  // Repeat current track only
    Shuffle  // Play in random order
};

//==============================================================================
// Cached Album Art Data (raw bytes, renderer-independent)
//==============================================================================

struct CachedAlbumArtData
{
    std::vector<unsigned char> data;
    int width = 0;
    int height = 0;
};

//==============================================================================
// PlayerBarData
//==============================================================================

struct PlayerBarData
{
    //--------------------------------------------------------------------------
    // Track Info
    //--------------------------------------------------------------------------
    std::size_t currentTrackId = 0;
    std::string title;
    std::string artist;
    std::string album;
    float durationSeconds = 0.0f;

    //--------------------------------------------------------------------------
    // Playback State
    //--------------------------------------------------------------------------
    bool isPlaying = false;
    bool isPaused = false;
    bool isStopped = true;
    bool hasTrack = false;

    float positionSeconds = 0.0f;
    float progress = 0.0f;          // 0.0 to 1.0

    //--------------------------------------------------------------------------
    // Formatted Strings (computed once by controller, used by all bars)
    //--------------------------------------------------------------------------
    std::string elapsedFormatted;   // "02:35"
    std::string totalFormatted;     // "04:12"

    //--------------------------------------------------------------------------
    // Volume
    //--------------------------------------------------------------------------
    float volume = 0.80f;

    //--------------------------------------------------------------------------
    // Playback Mode
    //--------------------------------------------------------------------------
    PlaybackMode playbackMode = PlaybackMode::Normal;
    std::string modeLabel;          // "Normal", "Shuffle", etc.

    //--------------------------------------------------------------------------
    // Visualizer
    //--------------------------------------------------------------------------
    int visualizerMode = 0;         // 0 = Spectrum, 1 = Oscilloscope
    HSTREAM audioStream = 0;        // For visualizer to attach to

    //--------------------------------------------------------------------------
    // Track Change Detection (set by controller, read by bars)
    //--------------------------------------------------------------------------
    bool trackJustChanged = false;

    //--------------------------------------------------------------------------
    // Album Art Cache (raw bytes, renderer-independent)
    // Multiple bars can each create textures from the same bytes.
    //--------------------------------------------------------------------------
    std::unordered_map<std::size_t, CachedAlbumArtData> albumArtCache;

    //--------------------------------------------------------------------------
    // Convenience: get cached art for current track
    //--------------------------------------------------------------------------
    const CachedAlbumArtData* GetCurrentArt() const
    {
        auto it = albumArtCache.find(currentTrackId);
        return (it != albumArtCache.end()) ? &it->second : nullptr;
    }

    //--------------------------------------------------------------------------
    // Clear all state (on library reset, etc.)
    //--------------------------------------------------------------------------
    void Clear()
    {
        currentTrackId = 0;
        title.clear();
        artist.clear();
        album.clear();
        durationSeconds = 0.0f;
        isPlaying = false;
        isPaused = false;
        isStopped = true;
        hasTrack = false;
        positionSeconds = 0.0f;
        progress = 0.0f;
        elapsedFormatted = "00:00";
        totalFormatted = "00:00";
        volume = 0.80f;
        playbackMode = PlaybackMode::Normal;
        modeLabel = "Normal";
        visualizerMode = 0;
        audioStream = 0;
        trackJustChanged = false;
        albumArtCache.clear();
    }
};

} // namespace moosic