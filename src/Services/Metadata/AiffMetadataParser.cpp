//==============================================================================
// AiffMetadataParser.cpp
//==============================================================================
// Custom binary parser for AIFF metadata (NAME, AUTH, copyright chunks)
// OPTIMIZED: Targeted reads - only reads metadata chunks, not the entire file
//==============================================================================

#include "AiffMetadataParser.h"

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool AiffMetadataParser::Parse(const std::filesystem::path& filePath,
                                MusicTrack& track,
                                bool /*extractAlbumArt*/) const
{
    // Read FORM header (first 12 bytes)
    auto header = ReadFileHead(filePath, 12);
    if (header.size() < 12) return false;

    //----------------------------------------------------------------------
    // Check FORM header
    //----------------------------------------------------------------------
    if (header[0] != 'F' || header[1] != 'O' || header[2] != 'R' || header[3] != 'M') return false;
    if (header[8] != 'A' || header[9] != 'I' || header[10] != 'F' || header[11] != 'F') return false;

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
        uint32_t chunkSize = ReadUInt32BE(chunkHeader, 4);

        if (chunkSize > 0 && offset + 8 + chunkSize <= fileSize)
        {
            // Read the chunk data (metadata chunks are tiny, typically < 256 bytes)
            size_t readSize = (std::min)(static_cast<size_t>(chunkSize), static_cast<size_t>(4096)); // Cap at 4KB
            auto chunkData = ReadFileRange(filePath, offset + 8, readSize);
            
            if (!chunkData.empty())
            {
                std::string value = CleanString(ReadString(chunkData, 0, chunkData.size()));

                //------------------------------------------------------------------
                // NAME chunk - Title
                //------------------------------------------------------------------
                if (chunkId == "NAME" && !value.empty()) 
                { 
                    track.SetTitle(value); 
                    hasMetadata = true; 
                }
                //------------------------------------------------------------------
                // AUTH chunk - Artist
                //------------------------------------------------------------------
                else if (chunkId == "AUTH" && !value.empty()) 
                { 
                    track.SetArtist(value); 
                    hasMetadata = true; 
                }
                //------------------------------------------------------------------
                // (c) chunk - Copyright/Album
                //------------------------------------------------------------------
                else if (chunkId == "(c) " && !value.empty()) 
                { 
                    track.SetAlbum(value); 
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

size_t AiffMetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> AiffMetadataParser::ReadFileRange(const std::filesystem::path& filePath,
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

std::vector<uint8_t> AiffMetadataParser::ReadFileHead(const std::filesystem::path& filePath,
                                                        size_t length) const
{
    return ReadFileRange(filePath, 0, length);
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