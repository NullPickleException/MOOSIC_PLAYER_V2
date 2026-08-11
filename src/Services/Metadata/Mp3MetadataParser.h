//==============================================================================
// Mp3MetadataParser.h
//==============================================================================
// Custom binary parser for MP3 metadata (ID3v1 and ID3v2 tags)
// Extracts: title, artist, album, genre, year, track number, album art (optional)
// OPTIMIZED: Targeted reads - only reads metadata sections, not the entire file
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"
#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

namespace moosic
{

//==============================================================================
// Mp3MetadataParser
//==============================================================================

class Mp3MetadataParser
{
public:
    //--------------------------------------------------------------------------
    // Construction / Destruction
    //--------------------------------------------------------------------------
    
    Mp3MetadataParser() = default;
    ~Mp3MetadataParser() = default;

    //--------------------------------------------------------------------------
    // Main Parse API
    //--------------------------------------------------------------------------
    // Parses MP3 file and fills track metadata
    // extractAlbumArt: set to false for bulk imports (much faster)
    // Returns true if any metadata was successfully extracted
    
    bool Parse(const std::filesystem::path& filePath, 
               MusicTrack& track,
               bool extractAlbumArt = true) const;

private:
    //--------------------------------------------------------------------------
    // Optimized File Reading Helpers
    //--------------------------------------------------------------------------
    
    std::vector<uint8_t> ReadFileRange(const std::filesystem::path& filePath, 
                                       size_t offset, size_t length) const;
    
    size_t GetFileSize(const std::filesystem::path& filePath) const;
    
    std::vector<uint8_t> ReadFileHead(const std::filesystem::path& filePath, 
                                      size_t length) const;
    
    std::vector<uint8_t> ReadFileTail(const std::filesystem::path& filePath, 
                                      size_t length) const;

    //--------------------------------------------------------------------------
    // ID3v2 Parsing
    //--------------------------------------------------------------------------
    
    bool ParseID3v2(const std::filesystem::path& filePath, 
                    MusicTrack& track,
                    uint32_t tagSize,
                    bool extractAlbumArt) const;
    
    void ExtractAlbumArt(const std::vector<uint8_t>& data, 
                         size_t offset, 
                         uint32_t frameSize,
                         const std::string& frameId, 
                         std::vector<uint8_t>& albumArt) const;

    //--------------------------------------------------------------------------
    // ID3v1 Parsing
    //--------------------------------------------------------------------------
    
    bool ParseID3v1(const std::vector<uint8_t>& data, 
                    size_t offset, 
                    MusicTrack& track) const;
    
    static const char* GetID3v1Genre(uint8_t index);

    //--------------------------------------------------------------------------
    // Binary Helpers
    //--------------------------------------------------------------------------
    
    uint32_t ReadUInt32BE(const std::vector<uint8_t>& data, size_t offset) const;
    uint32_t ReadSynchSafeInt(const std::vector<uint8_t>& data, size_t offset) const;
    std::string ReadString(const std::vector<uint8_t>& data, size_t offset, size_t length) const;
    std::string ReadNullTerminatedString(const std::vector<uint8_t>& data, size_t offset, size_t maxLength) const;
    
    //--------------------------------------------------------------------------
    // String Utilities
    //--------------------------------------------------------------------------
    
    std::string CleanString(const std::string& input) const;
};

} // namespace moosic