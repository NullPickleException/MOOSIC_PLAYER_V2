//==============================================================================
// Mp4MetadataParser.h
//==============================================================================
// Custom binary parser for MP4/M4A metadata (iTunes atoms, cover art)
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

   bool Parse(const std::filesystem::path& filePath, MusicTrack& track) const;

private:
    // Atom parsing
    bool ParseAtoms(const std::vector<uint8_t>& data, MusicTrack& track) const;
    bool ParseMetaAtom(const std::vector<uint8_t>& data, size_t offset, size_t length, MusicTrack& track) const;
    bool ParseILST(const std::vector<uint8_t>& data, size_t offset, size_t length, MusicTrack& track) const;
    
    // Helper to detect Apple metadata atoms (0xA9 prefix)
    bool IsAppleMetaAtom(const std::string& atomType, const char* suffix) const;
    
    // Binary helpers
    uint32_t ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const;
    uint16_t ReadUInt16BE(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    
    // File I/O
   std::vector<uint8_t> ReadFileBytes(const std::filesystem::path& filePath) const;
    
    // String utilities
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic