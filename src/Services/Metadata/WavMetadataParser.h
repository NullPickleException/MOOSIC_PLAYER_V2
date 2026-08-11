//==============================================================================
// WavMetadataParser.h
//==============================================================================
// Custom binary parser for WAV RIFF metadata (INFO chunks)
// OPTIMIZED: Targeted reads - only reads metadata chunks, not the entire file
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>
#include <algorithm>
#include <cctype>

namespace moosic
{

class WavMetadataParser
{
public:
    WavMetadataParser() = default;
    ~WavMetadataParser() = default;

    bool Parse(const std::filesystem::path& filePath, 
               MusicTrack& track,
               bool extractAlbumArt = true) const;

private:
    // Optimized file reading
    std::vector<uint8_t> ReadFileRange(const std::filesystem::path& filePath,
                                        size_t offset, size_t length) const;
    size_t GetFileSize(const std::filesystem::path& filePath) const;
    std::vector<uint8_t> ReadFileHead(const std::filesystem::path& filePath,
                                       size_t length) const;

    // RIFF INFO parsing
    bool ParseRIFFInfo(const std::filesystem::path& filePath,
                       size_t offset, size_t length,
                       MusicTrack& track) const;
    
    // Binary helpers
    uint32_t ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    
    // String utilities
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic