//==============================================================================
// WavPackMetadataParser.cpp
//==============================================================================
// Custom binary parser for WavPack metadata (APEv2 tags)
//==============================================================================

#include "WavPackMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool WavPackMetadataParser::Parse(const std::filesystem::path& filePath, MusicTrack& track) const
{
    auto data = ReadFileBytes(filePath);
    if (data.size() < 32) return false;

    //----------------------------------------------------------------------
    // Check for "wvpk" marker
    //----------------------------------------------------------------------
    if (data[0] != 'w' || data[1] != 'v' || data[2] != 'p' || data[3] != 'k')
        return false;

    bool hasMetadata = false;
    size_t offset = 32; // Skip first block header

    //----------------------------------------------------------------------
    // Parse blocks
    //----------------------------------------------------------------------
    while (offset + 8 <= data.size())
    {
        std::string blockId = ReadString(data, offset, 4);
        uint32_t blockSize = ReadUInt32LE(data, offset + 4);

        //------------------------------------------------------------------
        // APET block - APEv2 tags
        //------------------------------------------------------------------
        if (blockId == "APET" && offset + 16 + blockSize <= data.size())
        {
            if (data[offset + 8] == 'A' && data[offset + 9] == 'P' &&
                data[offset + 10] == 'E' && data[offset + 11] == 'T' &&
                data[offset + 12] == 'A' && data[offset + 13] == 'G' &&
                data[offset + 14] == 'E' && data[offset + 15] == 'X')
            {
                uint32_t itemCount = ReadUInt32LE(data, offset + 20);
                size_t tagOffset = offset + 32;

                //----------------------------------------------------------
                // Parse each tag item
                //----------------------------------------------------------
                for (uint32_t i = 0; i < itemCount && tagOffset + 8 <= data.size(); ++i)
                {
                    uint32_t valueLength = ReadUInt32LE(data, tagOffset);
                    tagOffset += 8; // Skip value length and flags

                    // Read key (null-terminated)
                    std::string key;
                    while (tagOffset < data.size() && data[tagOffset] != 0)
                        key += static_cast<char>(data[tagOffset++]);
                    tagOffset++; // Skip null terminator

                    if (tagOffset + valueLength > data.size()) break;

                    std::string value = ReadString(data, tagOffset, valueLength);
                    tagOffset += valueLength;
                    std::transform(key.begin(), key.end(), key.begin(), ::toupper);

                    if (key == "TITLE")      { track.SetTitle(CleanString(value)); hasMetadata = true; }
                    else if (key == "ARTIST") { track.SetArtist(CleanString(value)); hasMetadata = true; }
                    else if (key == "ALBUM")  { track.SetAlbum(CleanString(value)); }
                }
            }
        }

        offset += blockSize;
    }

    return hasMetadata;
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t WavPackMetadataParser::ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset + 3]) << 24) |
           (static_cast<uint32_t>(data[offset + 2]) << 16) |
           (static_cast<uint32_t>(data[offset + 1]) << 8) |
           static_cast<uint32_t>(data[offset]);
}

std::string WavPackMetadataParser::ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

//==============================================================================
// File I/O
//==============================================================================

std::vector<uint8_t> WavPackMetadataParser::ReadFileBytes(const std::filesystem::path& filePath) const
{
    // std::ifstream accepts std::filesystem::path natively - handles Unicode on all platforms
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

std::string WavPackMetadataParser::CleanString(const std::string& input) const
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