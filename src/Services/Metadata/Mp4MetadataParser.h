//==============================================================================
// Mp4MetadataParser.h
//==============================================================================
// Custom binary parser for MP4/M4A metadata (iTunes atoms, cover art)
// OPTIMIZED: Targeted reads - only reads metadata atoms, not the entire file
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

class Mp4MetadataParser
{
public:
    Mp4MetadataParser() = default;
    ~Mp4MetadataParser() = default;

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

    // Atom parsing
    bool ParseAtoms(const std::filesystem::path& filePath,
                    MusicTrack& track,
                    bool extractAlbumArt) const;
    bool ParseMetaAtom(const std::filesystem::path& filePath,
                       size_t atomOffset, size_t atomSize,
                       MusicTrack& track,
                       bool extractAlbumArt) const;
    bool ParseILST(const std::filesystem::path& filePath,
                   size_t offset, size_t length,
                   MusicTrack& track,
                   bool extractAlbumArt) const;
    
    // Helper to detect Apple metadata atoms (0xA9 prefix)
    bool IsAppleMetaAtom(const std::string& atomType, const char* suffix) const;
    
    // Binary helpers
    uint32_t ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const;
    uint16_t ReadUInt16BE(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    
    // String utilities
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic