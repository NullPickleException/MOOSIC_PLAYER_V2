//==============================================================================
// Mp3MetadataParser.cpp
//==============================================================================
// Custom binary parser for MP3 metadata (ID3v1 and ID3v2 tags)
// OPTIMIZED: Targeted reads - only reads metadata sections, not the entire file
//==============================================================================

#include "Mp3MetadataParser.h"
#include <algorithm>
#include <fstream>
#include <cctype>
#include <cstring>

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool Mp3MetadataParser::Parse(const std::filesystem::path& filePath, 
                               MusicTrack& track,
                               bool extractAlbumArt) const
{
    //----------------------------------------------------------------------
    // Quick check: read just the first 10 bytes to check for ID3v2 header
    //----------------------------------------------------------------------
    auto headerData = ReadFileHead(filePath, 10);
    if (headerData.size() < 3) return false;

    bool hasMetadata = false;

    //----------------------------------------------------------------------
    // Check for ID3v2 at beginning of file
    //----------------------------------------------------------------------
    if (headerData.size() >= 10 && 
        headerData[0] == 'I' && headerData[1] == 'D' && headerData[2] == '3')
    {
        // Parse ID3v2 header size from the first 10 bytes we already have
        uint32_t tagSize = ReadSynchSafeInt(headerData, 6);
        
        // Now read ONLY the ID3v2 tag (header + body)
        // Add some padding for safety
        size_t totalV2Size = 10 + tagSize;
        
        // Cap at 5MB to prevent allocation attacks (ID3v2 tags are rarely larger than 100KB)
        if (totalV2Size > 5 * 1024 * 1024)
            totalV2Size = 5 * 1024 * 1024;
            
        auto v2Data = ReadFileHead(filePath, totalV2Size);
        if (!v2Data.empty())
        {
            hasMetadata = ParseID3v2(filePath, track, tagSize, extractAlbumArt);
        }
    }

    //----------------------------------------------------------------------
    // Check for ID3v1 at end of file (last 128 bytes)
    // Only read 128 bytes!
    //----------------------------------------------------------------------
    size_t fileSize = GetFileSize(filePath);
    if (fileSize >= 128)
    {
        auto v1Data = ReadFileTail(filePath, 128);
        if (v1Data.size() >= 128 && 
            v1Data[0] == 'T' && v1Data[1] == 'A' && v1Data[2] == 'G')
        {
            hasMetadata |= ParseID3v1(v1Data, 0, track);
        }
    }

    return hasMetadata;
}

//==============================================================================
// Optimized File Reading Helpers
//==============================================================================

size_t Mp3MetadataParser::GetFileSize(const std::filesystem::path& filePath) const
{
    std::error_code ec;
    size_t size = std::filesystem::file_size(filePath, ec);
    if (ec) return 0;
    return size;
}

std::vector<uint8_t> Mp3MetadataParser::ReadFileRange(const std::filesystem::path& filePath, 
                                                       size_t offset, size_t length) const
{
    if (length == 0 || length > 100 * 1024 * 1024) return {};
    
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return {};
    
    // Seek to the offset
    file.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
    if (!file.good()) return {};
    
    std::vector<uint8_t> buffer(length);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(length)))
    {
        // If we couldn't read the full amount, resize to what we actually got
        size_t actualRead = static_cast<size_t>(file.gcount());
        if (actualRead == 0) return {};
        buffer.resize(actualRead);
    }
    
    return buffer;
}

std::vector<uint8_t> Mp3MetadataParser::ReadFileHead(const std::filesystem::path& filePath, 
                                                       size_t length) const
{
    return ReadFileRange(filePath, 0, length);
}

std::vector<uint8_t> Mp3MetadataParser::ReadFileTail(const std::filesystem::path& filePath, 
                                                       size_t length) const
{
    size_t fileSize = GetFileSize(filePath);
    if (fileSize == 0 || length > fileSize) return {};
    
    size_t offset = fileSize - length;
    return ReadFileRange(filePath, offset, length);
}

//==============================================================================
// ID3v2 Parser
//==============================================================================

bool Mp3MetadataParser::ParseID3v2(const std::filesystem::path& filePath, 
                                    MusicTrack& track,
                                    uint32_t tagSize,
                                    bool extractAlbumArt) const
{
    // Read the ID3v2 tag body (after the 10-byte header)
    size_t readSize = (std::min)(static_cast<size_t>(tagSize), static_cast<size_t>(5 * 1024 * 1024));
    auto data = ReadFileRange(filePath, 10, readSize);
    
    if (data.empty()) return false;
    
    //----------------------------------------------------------------------
    // Read ID3v2 header (from the beginning of the file)
    //----------------------------------------------------------------------
    auto headerData = ReadFileHead(filePath, 10);
    if (headerData.size() < 10) return false;
    
    uint8_t majorVersion = headerData[3];
    uint8_t flags = headerData[5];
    
    bool hasMetadata = false;
    bool hasFooter = (flags & 0x10) != 0;
    size_t offset = 0;  // Now relative to the tag body
    size_t endOffset = tagSize;
    
    //----------------------------------------------------------------------
    // Account for optional footer
    //----------------------------------------------------------------------
    if (hasFooter && endOffset >= 10)
        endOffset -= 10;
    
    std::vector<uint8_t> albumArt;
    
    //----------------------------------------------------------------------
    // Skip extended header if present (v2.4+)
    //----------------------------------------------------------------------
    if (majorVersion >= 3 && (flags & 0x40))
    {
        if (offset + 4 > endOffset) return false;
        uint32_t extHeaderSize = ReadSynchSafeInt(data, offset);
        offset += 4 + extHeaderSize;
    }
    
    //----------------------------------------------------------------------
    // Parse each frame
    //----------------------------------------------------------------------
    while (offset + 10 <= endOffset && offset < data.size())
    {
        std::string frameId;
        uint32_t frameSize;
        
        //------------------------------------------------------------------
        // Read frame header based on version
        //------------------------------------------------------------------
        if (majorVersion >= 3)  // ID3v2.3 or ID3v2.4
        {
            frameId = ReadString(data, offset, 4);
            offset += 4;
            
            if (frameId[0] == 0) break;  // Padding reached
            
            if (majorVersion == 4)
                frameSize = ReadSynchSafeInt(data, offset);
            else
                frameSize = ReadUInt32BE(data, offset);
            offset += 4;
            offset += 2;  // Skip flags
        }
        else  // ID3v2.2
        {
            frameId = ReadString(data, offset, 3);
            offset += 3;
            frameSize = (static_cast<uint32_t>(data[offset]) << 16) |
                        (static_cast<uint32_t>(data[offset + 1]) << 8) |
                        static_cast<uint32_t>(data[offset + 2]);
            offset += 3;
        }
        
        if (frameSize == 0 || offset + frameSize > endOffset) break;
        if (frameId.empty()) break;
        
        //------------------------------------------------------------------
        // Process known frame types
        //------------------------------------------------------------------
        
        // TIT2/TT2 - Title
        if (frameId == "TIT2" || frameId == "TT2")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetTitle(CleanString(text));
                hasMetadata = true;
            }
        }
        // TPE1/TP1 - Artist
        else if (frameId == "TPE1" || frameId == "TP1")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetArtist(CleanString(text));
                hasMetadata = true;
            }
        }
        // TALB/TAL - Album
        else if (frameId == "TALB" || frameId == "TAL")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetAlbum(CleanString(text));
            }
        }
        // TCON/TCO - Genre
        else if (frameId == "TCON" || frameId == "TCO")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetGenre(CleanString(text));
            }
        }
        // TYER/TYE - Year
        else if (frameId == "TYER" || frameId == "TYE")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                try { track.SetYear(static_cast<int>(std::stoul(text))); } catch (...) {}
            }
        }
        // TRCK/TRK - Track number
        else if (frameId == "TRCK" || frameId == "TRK")
        {
            if (frameSize > 1 && offset + frameSize <= data.size())
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                // Handle "1/10" format
                size_t slashPos = text.find('/');
                if (slashPos != std::string::npos)
                    text = text.substr(0, slashPos);
                try { track.SetTrackNumber(static_cast<int>(std::stoul(text))); } catch (...) {}
            }
        }
        // APIC/PIC - Album art (ONLY if extractAlbumArt is true)
        else if (frameId == "APIC" || frameId == "PIC")
        {
            if (extractAlbumArt && offset + frameSize <= data.size())
            {
                ExtractAlbumArt(data, offset, frameSize, frameId, albumArt);
            }
        }
        
        offset += frameSize;
    }
    
    //----------------------------------------------------------------------
    // Set album art if found
    //----------------------------------------------------------------------
    if (!albumArt.empty())
    {
        track.SetAlbumArtData(albumArt);
        track.SetHasAlbumArt(true);
    }
    
    return hasMetadata;
}

//==============================================================================
// Extract Album Art from APIC/PIC frame
//==============================================================================

void Mp3MetadataParser::ExtractAlbumArt(const std::vector<uint8_t>& data, 
                                        size_t offset, 
                                        uint32_t frameSize,
                                        const std::string& frameId, 
                                        std::vector<uint8_t>& albumArt) const
{
    if (frameSize == 0) return;
    
    //----------------------------------------------------------------------
    // Skip encoding byte
    //----------------------------------------------------------------------
    size_t picOffset = offset + 1;
    
    //----------------------------------------------------------------------
    // Skip MIME type (null-terminated string)
    //----------------------------------------------------------------------
    if (frameId == "APIC")
    {
        while (picOffset < offset + frameSize && data[picOffset] != 0)
            picOffset++;
        picOffset++;  // Skip null terminator
    }
    else
    {
        picOffset += 4;  // v2.2: skip format and picture type
    }
    
    //----------------------------------------------------------------------
    // Skip picture type byte
    //----------------------------------------------------------------------
    if (picOffset < offset + frameSize)
        picOffset++;
    
    //----------------------------------------------------------------------
    // Skip description (null-terminated string)
    //----------------------------------------------------------------------
    while (picOffset < offset + frameSize && data[picOffset] != 0)
        picOffset++;
    if (picOffset < offset + frameSize)
        picOffset++;
    
    //----------------------------------------------------------------------
    // Remaining data is the image
    //----------------------------------------------------------------------
    size_t imageSize = offset + frameSize - picOffset;
    if (imageSize > 0 && imageSize < 10 * 1024 * 1024)  // Max 10MB
    {
        albumArt.assign(data.begin() + picOffset, 
                       data.begin() + picOffset + imageSize);
    }
}

//==============================================================================
// ID3v1 Parser
//==============================================================================

bool Mp3MetadataParser::ParseID3v1(const std::vector<uint8_t>& data, 
                                   size_t offset, 
                                   MusicTrack& track) const
{
    if (offset + 128 > data.size()) return false;
    
    //----------------------------------------------------------------------
    // Verify "TAG" marker
    //----------------------------------------------------------------------
    if (data[offset] != 'T' || data[offset + 1] != 'A' || data[offset + 2] != 'G')
        return false;
    
    bool hasMetadata = false;
    
    //----------------------------------------------------------------------
    // Title (bytes 3-32, 30 chars)
    //----------------------------------------------------------------------
    std::string title = ReadNullTerminatedString(data, offset + 3, 30);
    if (!title.empty()) 
    { 
        track.SetTitle(CleanString(title)); 
        hasMetadata = true; 
    }
    
    //----------------------------------------------------------------------
    // Artist (bytes 33-62, 30 chars)
    //----------------------------------------------------------------------
    std::string artist = ReadNullTerminatedString(data, offset + 33, 30);
    if (!artist.empty()) 
    { 
        track.SetArtist(CleanString(artist)); 
        hasMetadata = true; 
    }
    
    //----------------------------------------------------------------------
    // Album (bytes 63-92, 30 chars)
    //----------------------------------------------------------------------
    std::string album = ReadNullTerminatedString(data, offset + 63, 30);
    if (!album.empty()) 
        track.SetAlbum(CleanString(album));
    
    //----------------------------------------------------------------------
    // Year (bytes 93-96, 4 chars)
    //----------------------------------------------------------------------
    std::string year = ReadNullTerminatedString(data, offset + 93, 4);
    try { if (!year.empty()) track.SetYear(static_cast<int>(std::stoul(year))); } catch (...) {}
    
    //----------------------------------------------------------------------
    // Comment (bytes 97-124, 28 chars)
    // Track number in ID3v1.1 (bytes 125-126)
    //----------------------------------------------------------------------
    if (data[offset + 125] == 0 && data[offset + 126] > 0)
        track.SetTrackNumber(data[offset + 126]);
    
    //----------------------------------------------------------------------
    // Genre (byte 127, 1 byte index)
    //----------------------------------------------------------------------
    uint8_t genreByte = data[offset + 127];
    if (genreByte < 80)  // 80 genres in ID3v1 list
        track.SetGenre(GetID3v1Genre(genreByte));
    
    return hasMetadata;
}

//==============================================================================
// ID3v1 Genre Mapping
//==============================================================================

const char* Mp3MetadataParser::GetID3v1Genre(uint8_t index)
{
    static const char* genres[] = {
        "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk",
        "Grunge", "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies",
        "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno",
        "Industrial", "Alternative", "Ska", "Death Metal", "Pranks",
        "Soundtrack", "Euro-Techno", "Ambient", "Trip-Hop", "Vocal",
        "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental",
        "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise",
        "AlternRock", "Bass", "Soul", "Punk", "Space", "Meditative",
        "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic",
        "Darkwave", "Techno-Industrial", "Electronic", "Pop-Folk",
        "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult",
        "Gangsta", "Top 40", "Christian Rap", "Pop/Funk", "Jungle",
        "Native American", "Cabaret", "New Wave", "Psychedelic", "Rave",
        "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk",
        "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock"
    };
    
    return genres[index];
}

//==============================================================================
// Binary Helpers
//==============================================================================

uint32_t Mp3MetadataParser::ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset]) << 24) |
           (static_cast<uint32_t>(data[offset + 1]) << 16) |
           (static_cast<uint32_t>(data[offset + 2]) << 8) |
           static_cast<uint32_t>(data[offset + 3]);
}

uint32_t Mp3MetadataParser::ReadSynchSafeInt(const std::vector<uint8_t>& data, size_t offset) const
{
    if (offset + 4 > data.size()) return 0;
    return (static_cast<uint32_t>(data[offset]) << 21) |
           (static_cast<uint32_t>(data[offset + 1]) << 14) |
           (static_cast<uint32_t>(data[offset + 2]) << 7) |
           static_cast<uint32_t>(data[offset + 3]);
}

std::string Mp3MetadataParser::ReadString(const std::vector<uint8_t>& data, 
                                          size_t offset, 
                                          size_t length) const
{
    if (offset + length > data.size()) 
        length = (offset < data.size()) ? (data.size() - offset) : 0;
    if (length == 0) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

std::string Mp3MetadataParser::ReadNullTerminatedString(const std::vector<uint8_t>& data, 
                                                        size_t offset, 
                                                        size_t maxLength) const
{
    std::string result;
    result.reserve(maxLength);
    size_t actualMax = (std::min)(maxLength, data.size() - offset);
    
    for (size_t i = 0; i < actualMax; ++i)
    {
        if (data[offset + i] == 0) break;
        result += static_cast<char>(data[offset + i]);
    }
    return result;
}

//==============================================================================
// String Utilities
//==============================================================================

std::string Mp3MetadataParser::CleanString(const std::string& input) const
{
    if (input.empty()) return "";
    
    std::string result;
    result.reserve(input.size());
    bool inSpace = false;
    
    for (char c : input)
    {
        // Skip null chars and control characters (except newline/tab)
        if (c == '\0' || (c < 32 && c != '\n' && c != '\t' && c != '\r'))
            continue;
        
        // Normalize whitespace
        if (std::isspace(static_cast<unsigned char>(c)))
        {
            if (!inSpace) 
            { 
                result.push_back(' '); 
                inSpace = true; 
            }
        }
        else
        {
            result.push_back(c);
            inSpace = false;
        }
    }
    
    // Trim leading/trailing whitespace
    size_t start = result.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = result.find_last_not_of(" \t\n\r");
    return result.substr(start, end - start + 1);
}

} // namespace moosic