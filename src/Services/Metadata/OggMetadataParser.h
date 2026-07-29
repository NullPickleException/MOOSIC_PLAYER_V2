//==============================================================================
// OggMetadataParser.h
//==============================================================================
// Custom binary parser for OGG Vorbis/Opus metadata
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

class OggMetadataParser
{
public:
    OggMetadataParser() = default;
    ~OggMetadataParser() = default;

    bool Parse(const std::filesystem::path& filePath, MusicTrack& track) const;

private:
    // Vorbis comment parsing
    bool ParseVorbisComments(const std::vector<uint8_t>& data, size_t offset, MusicTrack& track) const;
    
    // Binary helpers
    uint32_t ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    
    // File I/O
    std::vector<uint8_t> ReadFileBytes(const std::filesystem::path& filePath) const;
    
    // String utilities
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic