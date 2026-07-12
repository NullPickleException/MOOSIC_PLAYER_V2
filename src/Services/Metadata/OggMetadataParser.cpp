//==============================================================================
// OggMetadataParser.cpp
//==============================================================================
// Custom binary parser for OGG Vorbis/Opus metadata
//==============================================================================

#include "OggMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool OggMetadataParser::Parse(const std::string& filePath, MusicTrack& track) const
{
    auto data = ReadFileBytes(filePath);
    if (data.size() < 28) return false;

    //----------------------------------------------------------------------
    // Find Ogg pages
    //----------------------------------------------------------------------
    size_t offset = 0;
    while (offset + 4 <= data.size())
    {
        if (data[offset] == 'O' && data[offset + 1] == 'g' && 
            data[offset + 2] == 'g' && data[offset + 3] == 'S')
        {
            if (offset + 27 > data.size()) break;

            uint8_t numSegments = data[offset + 26];
            size_t segmentTable = offset + 27;
            size_t pageSize = 0;

            for (int i = 0; i < numSegments && (segmentTable + i) < data.size(); ++i)
                pageSize += data[segmentTable + i];

            size_t pageData = segmentTable + numSegments;

            //--------------------------------------------------------------
            // Vorbis comment packet (type 3, starts with "vorbis")
            //--------------------------------------------------------------
            if (pageData + 7 <= data.size() && data[pageData] == 3 &&
                data[pageData + 1] == 'v' && data[pageData + 2] == 'o' &&
                data[pageData + 3] == 'r' && data[pageData + 4] == 'b' &&
                data[pageData + 5] == 'i' && data[pageData + 6] == 's')
            {
                return ParseVorbisComments(data, pageData + 7, track);
            }
            //--------------------------------------------------------------
            // Opus comment packet ("OpusTags")
            //--------------------------------------------------------------
            else if (pageData + 8 <= data.size() &&
                     data[pageData] == 'O' && data[pageData + 1] == 'p' &&
                     data[pageData + 2] == 'u' && data[pageData + 3] == 's' &&
                     data[pageData + 4] == 'T' && data[pageData + 5] == 'a' &&
                     data[pageData + 6] == 'g' && data[pageData + 7] == 's')
            {
                return ParseVorbisComments(data, pageData + 8, track);
            }
        }
        offset++;
    }

    return false;
}

//==============================================================================
// Vorbis Comments Parser
//==============================================================================

bool OggMetadataParser::ParseVorbisComments(const std::vector<uint8_t>& data, size_t offset, MusicTrack& track) const
{
    if (offset + 4 > data.size()) return false;

    //----------------------------------------------------------------------
    // Skip vendor string
    //----------------------------------------------------------------------
    uint32_t vendorLength = ReadUInt32LE(data, offset);
    offset += 4 + vendorLength;

    if (offset + 4 > data.size()) return false;
    uint32_t commentCount = ReadUInt32LE(data, offset);
    offset += 4;

    bool hasMetadata = false;

    //----------------------------------------------------------------------
    // Parse each comment
    //----------------------------------------------------------------------
    for (uint32_t i = 0; i < commentCount && offset + 4 <= data.size(); ++i)
    {
        uint32_t commentLength = ReadUInt32LE(data, offset);
        offset += 4;

        if (offset + commentLength > data.size()) break;

        std::string comment = ReadString(data, offset, commentLength);
        offset += commentLength;

        size_t eqPos = comment.find('=');
        if (eqPos == std::string::npos) continue;

        std::string key = comment.substr(0, eqPos);
        std::string value = comment.substr(eqPos + 1);
        std::transform(key.begin(), key.end(), key.begin(), ::toupper);

        if (key == "TITLE")           { track.SetTitle(CleanString(value)); hasMetadata = true; }
        else if (key == "ARTIST")     { track.SetArtist(CleanString(value)); hasMetadata = true; }
        else if (key == "ALBUM")      { track.SetAlbum(CleanString(value)); }
        else if (key == "GENRE")      { track.SetGenre(CleanString(value)); }
        else if (key == "DATE" || key == "YEAR") { try { track.SetYear(std::stoi(value)); } catch (...) {} }
        else if (key == "TRACKNUMBER") { try { track.SetTrackNumber(std::stoi(value)); } catch (...) {} }
    }

    return hasMetadata;
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t OggMetadataParser::ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset + 3]) << 24) |
           (static_cast<uint32_t>(data[offset + 2]) << 16) |
           (static_cast<uint32_t>(data[offset + 1]) << 8) |
           static_cast<uint32_t>(data[offset]);
}

std::string OggMetadataParser::ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

//==============================================================================
// File I/O
//==============================================================================

std::vector<uint8_t> OggMetadataParser::ReadFileBytes(const std::string& filePath) const
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

std::string OggMetadataParser::CleanString(const std::string& input) const
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