//==============================================================================
// WavMetadataParser.cpp
//==============================================================================
// Custom binary parser for WAV RIFF metadata (INFO chunks)
// OPTIMIZED: Targeted reads - only reads metadata chunks, not the entire file
//==============================================================================

#include "WavMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool WavMetadataParser::Parse(const std::filesystem::path& filePath,
                               MusicTrack& track,
                               bool /*extractAlbumArt*/) const
{
    // Read RIFF header (first 12 bytes)
    auto header = ReadFileHead(filePath, 12);
    if (header.size() < 12) return false;

    //----------------------------------------------------------------------
    // Check RIFF header
    //----------------------------------------------------------------------
    if (header[0] != 'R' || header[1] != 'I' || header[2] != 'F' || header[3] != 'F') return false;
    if (header[8] != 'W' || header[9] != 'A' || header[10] != 'V' || header[11] != 'E') return false;

    bool hasMetadata = false;
    size_t offset = 12;
    size_t fileSize = GetFileSize(filePath);

    //----------------------------------------------------------------------
    // Parse chunks using targeted reads
    //----------------------------------------------------------------------
    while (offset + 8 <= fileSize)
    {
        // Read just the chunk header (8 bytes)
        auto chunkHeader = ReadFileRange(filePath, offset, 8);
        if (chunkHeader.size() < 8) break;

        std::string chunkId = ReadString(chunkHeader, 0, 4);
        uint32_t chunkSize = ReadUInt32LE(chunkHeader, 4);

        //------------------------------------------------------------------
        // LIST chunk (contains INFO) - read the LIST type (4 more bytes)
        //------------------------------------------------------------------
        if (chunkId == "LIST" && chunkSize >= 4)
        {
            auto listTypeData = ReadFileRange(filePath, offset + 8, 4);
            if (listTypeData.size() >= 4)
            {
                std::string listType = ReadString(listTypeData, 0, 4);
                if (listType == "INFO")
                {
                    hasMetadata |= ParseRIFFInfo(filePath, offset + 12, chunkSize - 4, track);
                }
            }
        }

        offset += 8 + chunkSize;
        if (chunkSize % 2) offset++; // Padding byte
    }

    return hasMetadata;
}

//==============================================================================
// Optimized File Reading Helpers
//==============================================================================

size_t WavMetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> WavMetadataParser::ReadFileRange(const std::filesystem::path& filePath,
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

std::vector<uint8_t> WavMetadataParser::ReadFileHead(const std::filesystem::path& filePath,
                                                       size_t length) const
{
    return ReadFileRange(filePath, 0, length);
}

//==============================================================================
// RIFF INFO Chunk Parser (reads only the INFO section)
//==============================================================================

bool WavMetadataParser::ParseRIFFInfo(const std::filesystem::path& filePath,
                                       size_t offset, size_t length,
                                       MusicTrack& track) const
{
    // Read the entire INFO section (typically very small, < 1KB)
    size_t readSize = (std::min)(length, static_cast<size_t>(64 * 1024)); // Cap at 64KB
    auto data = ReadFileRange(filePath, offset, readSize);
    if (data.empty()) return false;

    size_t end = data.size();
    size_t pos = 0;
    bool hasMetadata = false;

    while (pos + 8 <= end)
    {
        std::string chunkId = ReadString(data, pos, 4);
        uint32_t chunkSize = ReadUInt32LE(data, pos + 4);

        if (pos + 8 + chunkSize > end) break;

        std::string value = CleanString(ReadString(data, pos + 8, chunkSize));

        if (chunkId == "INAM" && !value.empty())      { track.SetTitle(value); hasMetadata = true; }
        else if (chunkId == "IART" && !value.empty()) { track.SetArtist(value); hasMetadata = true; }
        else if (chunkId == "IPRD" && !value.empty()) { track.SetAlbum(value); }
        else if (chunkId == "IGNR" && !value.empty()) { track.SetGenre(value); }
        else if (chunkId == "ICRD" && !value.empty()) { try { track.SetYear(std::stoi(value)); } catch (...) {} }

        pos += 8 + chunkSize;
        if (chunkSize % 2) pos++; // Padding byte
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