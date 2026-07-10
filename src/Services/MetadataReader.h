#pragma once
#include "../Models/MusicTrack.h"
#include <filesystem>
#include <vector>
#include <string>
#include <unordered_map>
#include <mutex>

// Forward declare FFmpeg types
struct AVFormatContext;

namespace moosic
{
class MetadataReader
{
public:
    MetadataReader();
    ~MetadataReader();

    MusicTrack ReadMetadataForSingleTrack(const std::filesystem::path& filePath) const;

private:
    // FFmpeg: Get all metadata INCLUDING album art
    bool ReadMetadataWithFFmpeg(const std::filesystem::path& filePath, MusicTrack& track) const;
    
    // Extract album art from FFmpeg metadata (APIC tags)
    bool ExtractAlbumArt(AVFormatContext* fmt_ctx, MusicTrack& track) const;
    
    // Extract album art from video stream packets (for MP3 with embedded art)
    bool ExtractAlbumArtFromPackets(AVFormatContext* fmt_ctx, MusicTrack& track) const;
    
    // BASS: Get duration only
    unsigned int GetDurationWithBASS(const std::filesystem::path& filePath) const;

    // Fallback
    MusicTrack CreateFallbackTrack(const std::filesystem::path& filePath) const;

    // Utilities
    bool IsAudioFile(const std::filesystem::path& filePath) const;
    std::string GetLowercaseExtension(const std::filesystem::path& filePath) const;
    std::string CleanString(const std::string& input) const;
    std::string TruncateString(const std::string& input, size_t maxLength = 80) const;

    // Cache for BASS durations
    mutable std::unordered_map<std::string, unsigned int> m_durationCache;
    mutable std::mutex m_cacheMutex;
};
} // namespace moosic