//==============================================================================
// AiffMetadataParser.cpp
//==============================================================================
// Custom binary parser for AIFF metadata (NAME, AUTH, copyright chunks)
//==============================================================================

#include "AiffMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool AiffMetadataParser::Parse(const std::filesystem::path& filePath, MusicTrack& track) const
{
    auto data = ReadFileBytes(filePath);
    if (data.size() < 12) return false;

    //----------------------------------------------------------------------
    // Check FORM header
    //----------------------------------------------------------------------
    if (data[0] != 'F' || data[1] != 'O' || data[2] != 'R' || data[3] != 'M') return false;
    if (data[8] != 'A' || data[9] != 'I' || data[10] != 'F' || data[11] != 'F') return false;

    bool hasMetadata = false;
    size_t offset = 12;

    //----------------------------------------------------------------------
    // Parse chunks
    //----------------------------------------------------------------------
    while (offset + 8 <= data.size())
    {
        std::string chunkId = ReadString(data, offset, 4);
        uint32_t chunkSize = ReadUInt32BE(data, offset + 4);

        //------------------------------------------------------------------
        // NAME chunk - Title
        //------------------------------------------------------------------
        if (chunkId == "NAME" && chunkSize > 0 && offset + 8 + chunkSize <= data.size())
        {
            std::string value = CleanString(ReadString(data, offset + 8, chunkSize));
            if (!value.empty()) { track.SetTitle(value); hasMetadata = true; }
        }
        //------------------------------------------------------------------
        // AUTH chunk - Artist
        //------------------------------------------------------------------
        else if (chunkId == "AUTH" && chunkSize > 0 && offset + 8 + chunkSize <= data.size())
        {
            std::string value = CleanString(ReadString(data, offset + 8, chunkSize));
            if (!value.empty()) { track.SetArtist(value); hasMetadata = true; }
        }
        //------------------------------------------------------------------
        // (c) chunk - Copyright/Album
        //------------------------------------------------------------------
        else if (chunkId == "(c) " && chunkSize > 0 && offset + 8 + chunkSize <= data.size())
        {
            std::string value = CleanString(ReadString(data, offset + 8, chunkSize));
            if (!value.empty()) track.SetAlbum(value);
        }

        offset += 8 + chunkSize;
        if (chunkSize % 2) offset++; // Padding byte
    }

    return hasMetadata;
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t AiffMetadataParser::ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset]) << 24) |
           (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

std::string AiffMetadataParser::ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

//==============================================================================
// File I/O
//==============================================================================

std::vector<uint8_t> AiffMetadataParser::ReadFileBytes(const std::filesystem::path& filePath) const
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

std::string AiffMetadataParser::CleanString(const std::string& input) const
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