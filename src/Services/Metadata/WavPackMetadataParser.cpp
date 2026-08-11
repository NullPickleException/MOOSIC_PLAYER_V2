//==============================================================================
// WavPackMetadataParser.cpp
//==============================================================================
// Custom binary parser for WavPack metadata (APEv2 tags)
// OPTIMIZED: Targeted reads - only reads metadata blocks, not the entire file
//==============================================================================

#include "WavPackMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool WavPackMetadataParser::Parse(const std::filesystem::path& filePath,
                                   MusicTrack& track,
                                   bool /*extractAlbumArt*/) const
{
    // Read first block header (32 bytes)
    auto header = ReadFileHead(filePath, 32);
    if (header.size() < 32) return false;

    //----------------------------------------------------------------------
    // Check for "wvpk" marker
    //----------------------------------------------------------------------
    if (header[0] != 'w' || header[1] != 'v' || header[2] != 'p' || header[3] != 'k')
        return false;

    bool hasMetadata = false;
    size_t offset = 32; // Skip first block header
    size_t fileSize = GetFileSize(filePath);

    //----------------------------------------------------------------------
    // Parse blocks using targeted reads
    //----------------------------------------------------------------------
    while (offset + 8 <= fileSize)
    {
        // Read just the block header (8 bytes)
        auto blockHeader = ReadFileRange(filePath, offset, 8);
        if (blockHeader.size() < 8) break;

        std::string blockId = ReadString(blockHeader, 0, 4);
        uint32_t blockSize = ReadUInt32LE(blockHeader, 4);

        //------------------------------------------------------------------
        // APET block - APEv2 tags (read the tag data)
        //------------------------------------------------------------------
        if (blockId == "APET" && blockSize >= 24)
        {
            // Read the APEv2 header (24 bytes: ID + version + size + items + flags)
            auto apeHeader = ReadFileRange(filePath, offset + 8, 24);
            if (apeHeader.size() >= 24)
            {
                // Check for "APETAGEX" signature
                if (apeHeader[0] == 'A' && apeHeader[1] == 'P' &&
                    apeHeader[2] == 'E' && apeHeader[3] == 'T' &&
                    apeHeader[4] == 'A' && apeHeader[5] == 'G' &&
                    apeHeader[6] == 'E' && apeHeader[7] == 'X')
                {
                    uint32_t tagSize = ReadUInt32LE(apeHeader, 12);
                    uint32_t itemCount = ReadUInt32LE(apeHeader, 16);
                    
                    // Read the tag data (APEv2 tags are typically small, < 100KB)
                    size_t readSize = (std::min)(static_cast<size_t>(tagSize), static_cast<size_t>(256 * 1024));
                    auto tagData = ReadFileRange(filePath, offset + 32, readSize);
                    
                    if (!tagData.empty())
                    {
                        size_t tagOffset = 0;

                        //----------------------------------------------------------
                        // Parse each tag item
                        //----------------------------------------------------------
                        for (uint32_t i = 0; i < itemCount && tagOffset + 8 <= tagData.size(); ++i)
                        {
                            uint32_t valueLength = ReadUInt32LE(tagData, tagOffset);
                            tagOffset += 8; // Skip value length and flags

                            // Read key (null-terminated)
                            std::string key;
                            while (tagOffset < tagData.size() && tagData[tagOffset] != 0)
                                key += static_cast<char>(tagData[tagOffset++]);
                            tagOffset++; // Skip null terminator

                            if (tagOffset + valueLength > tagData.size()) break;

                            std::string value = ReadString(tagData, tagOffset, valueLength);
                            tagOffset += valueLength;
                            std::transform(key.begin(), key.end(), key.begin(), ::toupper);

                            if (key == "TITLE")      { track.SetTitle(CleanString(value)); hasMetadata = true; }
                            else if (key == "ARTIST") { track.SetArtist(CleanString(value)); hasMetadata = true; }
                            else if (key == "ALBUM")  { track.SetAlbum(CleanString(value)); }
                            else if (key == "GENRE")  { track.SetGenre(CleanString(value)); }
                            else if (key == "YEAR" || key == "DATE") { try { track.SetYear(std::stoi(value)); } catch (...) {} }
                            else if (key == "TRACK" || key == "TRACKNUMBER") { try { track.SetTrackNumber(std::stoi(value)); } catch (...) {} }
                        }
                    }
                }
            }
        }

        offset += 8 + blockSize;
        if (blockSize == 0) break; // Prevent infinite loop on zero-size blocks
    }

    return hasMetadata;
}

//==============================================================================
// Optimized File Reading Helpers
//==============================================================================

size_t WavPackMetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> WavPackMetadataParser::ReadFileRange(const std::filesystem::path& filePath,
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

std::vector<uint8_t> WavPackMetadataParser::ReadFileHead(const std::filesystem::path& filePath,
                                                           size_t length) const
{
    return ReadFileRange(filePath, 0, length);
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