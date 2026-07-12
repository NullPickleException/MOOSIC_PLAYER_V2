//==============================================================================
// Mp3MetadataParser.cpp
//==============================================================================
// Custom binary parser for MP3 metadata (ID3v1 and ID3v2 tags)
//==============================================================================

#include "Mp3MetadataParser.h"
#include <algorithm>
#include <fstream>
#include <cctype>

namespace moosic
{

//==============================================================================
// Main Parse API
//==============================================================================

bool Mp3MetadataParser::Parse(const std::string& filePath, MusicTrack& track) const
{
    auto data = ReadFileBytes(filePath);
    if (data.size() < 3) return false;

    bool hasMetadata = false;

    //----------------------------------------------------------------------
    // Check for ID3v2 at beginning of file
    //----------------------------------------------------------------------
    if (data.size() >= 10 && 
        data[0] == 'I' && data[1] == 'D' && data[2] == '3')
    {
        hasMetadata = ParseID3v2(data, track);
    }

    //----------------------------------------------------------------------
    // Check for ID3v1 at end of file (last 128 bytes)
    //----------------------------------------------------------------------
    if (data.size() >= 128)
    {
        size_t offset = data.size() - 128;
        if (data[offset] == 'T' && data[offset + 1] == 'A' && data[offset + 2] == 'G')
        {
            hasMetadata |= ParseID3v1(data, offset, track);
        }
    }

    return hasMetadata;
}

//==============================================================================
// ID3v2 Parser
//==============================================================================

bool Mp3MetadataParser::ParseID3v2(const std::vector<uint8_t>& data, MusicTrack& track) const
{
    if (data.size() < 10) return false;
    
    //----------------------------------------------------------------------
    // Read ID3v2 header
    //----------------------------------------------------------------------
    uint8_t majorVersion = data[3];
    uint8_t flags = data[5];
    uint32_t tagSize = ReadSynchSafeInt(data, 6);
    
    if (tagSize == 0 || tagSize + 10 > data.size()) return false;
    
    bool hasMetadata = false;
    bool hasFooter = (flags & 0x10) != 0;
    size_t offset = 10;
    size_t endOffset = offset + tagSize;
    
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
    while (offset + 10 <= endOffset)
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
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetTitle(CleanString(text));
                hasMetadata = true;
            }
        }
        // TPE1/TP1 - Artist
        else if (frameId == "TPE1" || frameId == "TP1")
        {
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetArtist(CleanString(text));
                hasMetadata = true;
            }
        }
        // TALB/TAL - Album
        else if (frameId == "TALB" || frameId == "TAL")
        {
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetAlbum(CleanString(text));
            }
        }
        // TCON/TCO - Genre
        else if (frameId == "TCON" || frameId == "TCO")
        {
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                track.SetGenre(CleanString(text));
            }
        }
        // TYER/TYE - Year
        else if (frameId == "TYER" || frameId == "TYE")
        {
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                try { track.SetYear(std::stoi(text)); } catch (...) {}
            }
        }
        // TRCK/TRK - Track number
        else if (frameId == "TRCK" || frameId == "TRK")
        {
            if (frameSize > 1)
            {
                std::string text = ReadString(data, offset + 1, frameSize - 1);
                try { track.SetTrackNumber(std::stoi(text)); } catch (...) {}
            }
        }
        // APIC/PIC - Album art
        else if (frameId == "APIC" || frameId == "PIC")
        {
            ExtractAlbumArt(data, offset, frameSize, frameId, albumArt);
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
    try { if (!year.empty()) track.SetYear(std::stoi(year)); } catch (...) {}
    
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
    if (offset + length > data.size()) return "";
    return std::string(reinterpret_cast<const char*>(&data[offset]), length);
}

std::string Mp3MetadataParser::ReadNullTerminatedString(const std::vector<uint8_t>& data, 
                                                        size_t offset, 
                                                        size_t maxLength) const
{
    std::string result;
    for (size_t i = 0; i < maxLength && (offset + i) < data.size(); ++i)
    {
        if (data[offset + i] == 0) break;
        result += static_cast<char>(data[offset + i]);
    }
    return result;
}

//==============================================================================
// File I/O
//==============================================================================

std::vector<uint8_t> Mp3MetadataParser::ReadFileBytes(const std::string& filePath) const
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return {};
    
    std::streamsize size = file.tellg();
    if (size <= 0 || size > 100 * 1024 * 1024) return {};  // Max 100MB
    
    file.seekg(0, std::ios::beg);
    std::vector<uint8_t> buffer(static_cast<size_t>(size));
    
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
        return {};
    
    return buffer;
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