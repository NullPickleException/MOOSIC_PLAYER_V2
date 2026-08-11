//==============================================================================
// FlacMetadataParser.cpp
//==============================================================================
// Custom binary parser for FLAC metadata (Vorbis comments, pictures)
// OPTIMIZED: Targeted reads - only reads metadata blocks, not the entire file
//==============================================================================

#include "FlacMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool FlacMetadataParser::Parse(const std::filesystem::path& filePath,
                                MusicTrack& track,
                                bool extractAlbumArt) const
{
    // Read FLAC header + STREAMINFO (first 42 bytes)
    auto header = ReadFileHead(filePath, 42);
    if (header.size() < 42) return false;

    //----------------------------------------------------------------------
    // Check for "fLaC" marker
    //----------------------------------------------------------------------
    if (header[0] != 'f' || header[1] != 'L' || header[2] != 'a' || header[3] != 'C')
        return false;

    bool hasMetadata = false;
    size_t offset = 4;
    bool lastBlock = false;

    //----------------------------------------------------------------------
    // Parse metadata blocks using targeted reads
    //----------------------------------------------------------------------
    while (!lastBlock && offset + 4 <= header.size())
    {
        uint8_t blockHeader = header[offset];
        lastBlock = (blockHeader & 0x80) != 0;
        uint8_t blockType = blockHeader & 0x7F;
        uint32_t blockSize = ReadUInt24BE(header, offset);
        offset += 4;

        if (offset + blockSize > header.size())
        {
            // Need to read more data for this block
            // Read the block data from file
            auto blockData = ReadFileRange(filePath, offset, blockSize);
            if (blockData.size() < blockSize) break;

            if (blockType == 4) // VORBIS_COMMENT
            {
                hasMetadata = ParseVorbisComments(blockData, 0, blockSize, track);
            }
            else if (blockType == 6 && extractAlbumArt) // PICTURE
            {
                ParsePicture(blockData, 0, track);
            }

            offset += blockSize;
        }
        else
        {
            // Block data is already in header buffer
            if (blockType == 4) // VORBIS_COMMENT
            {
                hasMetadata = ParseVorbisComments(header, offset, blockSize, track);
            }
            else if (blockType == 6 && extractAlbumArt) // PICTURE
            {
                ParsePicture(header, offset, track);
            }

            offset += blockSize;
        }

        // If we've exhausted the header buffer, read the next block header
        if (offset + 4 > header.size() && !lastBlock)
        {
            auto nextHeader = ReadFileRange(filePath, offset, 4);
            if (nextHeader.size() < 4) break;
            header = nextHeader;
            offset = 0;
        }
    }

    return hasMetadata;
}

//==============================================================================
// Optimized File Reading Helpers
//==============================================================================

size_t FlacMetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> FlacMetadataParser::ReadFileRange(const std::filesystem::path& filePath,
                                                        size_t offset, size_t length) const
{
    if (length == 0 || length > 100 * 1024 * 1024) return {};
    
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return {};
    
    file.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
    if (!file.good()) return {};
    
    std::vector<uint8_t> buffer(length);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(length)))
    {
        size_t actualRead = static_cast<size_t>(file.gcount());
        if (actualRead == 0) return {};
        buffer.resize(actualRead);
    }
    
    return buffer;
}

std::vector<uint8_t> FlacMetadataParser::ReadFileHead(const std::filesystem::path& filePath,
                                                        size_t length) const
{
    return ReadFileRange(filePath, 0, length);
}

//==============================================================================
// Vorbis Comments Parser
//==============================================================================

bool FlacMetadataParser::ParseVorbisComments(const std::vector<uint8_t>& data, size_t offset, size_t length, MusicTrack& track) const
{
    if (length < 4) return false;

    size_t end = offset + length;
    
    //----------------------------------------------------------------------
    // Skip vendor string
    //----------------------------------------------------------------------
    uint32_t vendorLength = ReadUInt32LE(data, offset);
    offset += 4 + vendorLength;

    if (offset + 4 > end) return false;
    uint32_t commentCount = ReadUInt32LE(data, offset);
    offset += 4;

    bool hasMetadata = false;

    //----------------------------------------------------------------------
    // Parse each comment
    //----------------------------------------------------------------------
    for (uint32_t i = 0; i < commentCount && offset + 4 <= end; ++i)
    {
        uint32_t commentLength = ReadUInt32LE(data, offset);
        offset += 4;

        if (offset + commentLength > end) break;

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
// Picture Block Parser
//==============================================================================

bool FlacMetadataParser::ParsePicture(const std::vector<uint8_t>& data, size_t offset, MusicTrack& track) const
{
    if (offset + 8 > data.size()) return false;

    //----------------------------------------------------------------------
    // Skip picture type, MIME type, description
    //----------------------------------------------------------------------
    uint32_t mimeLength = ReadUInt32BE(data, offset + 4);
    offset += 8 + mimeLength;

    if (offset + 4 > data.size()) return false;
    uint32_t descLength = ReadUInt32BE(data, offset);
    offset += 4 + descLength;

    //----------------------------------------------------------------------
    // Skip width, height, color depth, colors used (16 bytes)
    //----------------------------------------------------------------------
    if (offset + 20 > data.size()) return false;
    offset += 16;

    //----------------------------------------------------------------------
    // Read picture data
    //----------------------------------------------------------------------
    uint32_t dataLength = ReadUInt32BE(data, offset);
    offset += 4;

    if (offset + dataLength > data.size()) return false;

    if (dataLength > 0 && dataLength < 10 * 1024 * 1024) // Max 10MB
    {
        std::vector<uint8_t> imageData(data.begin() + offset, data.begin() + offset + dataLength);
        track.SetAlbumArtData(imageData);
        track.SetHasAlbumArt(true);
        return true;
    }

    return false;
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t FlacMetadataParser::ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset]) << 24) |
           (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

uint32_t FlacMetadataParser::ReadUInt32LE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset + 3]) << 24) |
           (static_cast<uint32_t>(data[offset + 2]) << 16) |
           (static_cast<uint32_t>(data[offset + 1]) << 8) |
           static_cast<uint32_t>(data[offset]);
}

uint32_t FlacMetadataParser::ReadUInt24BE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 3 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

std::string FlacMetadataParser::ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const
{
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

//==============================================================================
// String Utilities
//==============================================================================

std::string FlacMetadataParser::CleanString(const std::string& input) const
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