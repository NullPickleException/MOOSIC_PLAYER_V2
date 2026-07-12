//==============================================================================
// WavMetadataParser.h
//==============================================================================
// Custom binary parser for WAV RIFF metadata (INFO chunks)
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

    bool Parse(const std::string& filePath, MusicTrack& track) const;

private:
    // RIFF INFO parsing
    bool ParseRIFFInfo(const std::vector<uint8_t>& data, size_t offset, size_t length, MusicTrack& track) const;
    
    // Binary helpers
    uint32_t ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    
    // File I/O
    std::vector<uint8_t> ReadFileBytes(const std::string& filePath) const;
    
    // String utilities
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic