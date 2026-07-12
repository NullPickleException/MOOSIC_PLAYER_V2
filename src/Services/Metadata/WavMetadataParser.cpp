//==============================================================================
// WavMetadataParser.cpp
//==============================================================================
// Custom binary parser for WAV RIFF metadata (INFO chunks)
//==============================================================================

#include "WavMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool WavMetadataParser::Parse(const std::string& filePath, MusicTrack& track) const
{
    auto data = ReadFileBytes(filePath);
    if (data.size() < 12) return false;

    //----------------------------------------------------------------------
    // Check RIFF header
    //----------------------------------------------------------------------
    if (data[0] != 'R' || data[1] != 'I' || data[2] != 'F' || data[3] != 'F') return false;
    if (data[8] != 'W' || data[9] != 'A' || data[10] != 'V' || data[11] != 'E') return false;

    bool hasMetadata = false;
    size_t offset = 12;

    //----------------------------------------------------------------------
    // Parse chunks
    //----------------------------------------------------------------------
    while (offset + 8 <= data.size())
    {
        std::string chunkId = ReadString(data, offset, 4);
        uint32_t chunkSize = ReadUInt32LE(data, offset + 4);

        //------------------------------------------------------------------
        // LIST chunk (contains INFO)
        //------------------------------------------------------------------
        if (chunkId == "LIST" && offset + 12 <= data.size())
        {
            std::string listType = ReadString(data, offset + 8, 4);
            if (listType == "INFO")
                hasMetadata |= ParseRIFFInfo(data, offset + 12, chunkSize - 4, track);
        }

        offset += 8 + chunkSize;
        if (chunkSize % 2) offset++; // Padding byte
    }

    return hasMetadata;
}

//==============================================================================
// RIFF INFO Chunk Parser
//==============================================================================

bool WavMetadataParser::ParseRIFFInfo(const std::vector<uint8_t>& data, size_t offset, size_t length, MusicTrack& track) const
{
    size_t end = offset + length;
    bool hasMetadata = false;

    while (offset + 8 <= end)
    {
        std::string chunkId = ReadString(data, offset, 4);
        uint32_t chunkSize = ReadUInt32LE(data, offset + 4);

        if (offset + 8 + chunkSize > end) break;

        std::string value = CleanString(ReadString(data, offset + 8, chunkSize));

        if (chunkId == "INAM" && !value.empty())      { track.SetTitle(value); hasMetadata = true; }
        else if (chunkId == "IART" && !value.empty()) { track.SetArtist(value); hasMetadata = true; }
        else if (chunkId == "IPRD" && !value.empty()) { track.SetAlbum(value); }
        else if (chunkId == "IGNR" && !value.empty()) { track.SetGenre(value); }
        else if (chunkId == "ICRD" && !value.empty()) { try { track.SetYear(std::stoi(value)); } catch (...) {} }

        offset += 8 + chunkSize;
        if (chunkSize % 2) offset++; // Padding byte
    }

    return hasMetadata;
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t WavMetadataParser::ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset + 3]) << 24) |
           (static_cast<uint32_t>(data[offset + 2]) << 16) |
           (static_cast<uint32_t>(data[offset + 1]) << 8) |
           static_cast<uint32_t>(data[offset]);
}

std::string WavMetadataParser::ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

//==============================================================================
// File I/O
//==============================================================================

std::vector<uint8_t> WavMetadataParser::ReadFileBytes(const std::string& filePath) const
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return {};

    std::streamsize size = file.tellg();
    if (size <= 0 || size > 100 * 1024 * 1024) return {};

    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(static_cast<size_t>(size));

    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        return {};

    return buffer;
}

//==============================================================================
// String Utilities
//==============================================================================

std::string WavMetadataParser::CleanString(const std::string& input) const
{
    if (input.empty()) return "";

    std::string result;
    result.reserve(input.size());
    bool inSpace = false;

    for (char c : input)
    {
        if (c == '\0' || (c < 32 && c != '\n' && c != '\t' && c != '\r'))
            continue;

        if (std::isspace(static_cast<unsigned char>(c)))
        {
            if (!inSpace) { result.push_back(' '); inSpace = true; }
        }
        else
        {
            result.push_back(c);
            inSpace = false;
        }
    }

    size_t start = result.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = result.find_last_not_of(" \t\n\r");
    return result.substr(start, end - start + 1);
}

} // namespace moosic