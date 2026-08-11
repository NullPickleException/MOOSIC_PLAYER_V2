//==============================================================================
// MetadataReader.h
//==============================================================================
// Central metadata reader that dispatches to format-specific parsers
// Duration is always handled by BASS
// extractAlbumArt parameter controls whether album art is extracted
// Set to false during bulk imports for massive speed improvement
//==============================================================================

#pragma once

#include "../../Models/MusicTrack.h"
#include "Mp3MetadataParser.h"
#include "FlacMetadataParser.h"
#include "Mp4MetadataParser.h"
#include "OggMetadataParser.h"
#include "WavMetadataParser.h"
#include "AiffMetadataParser.h"
#include "WavPackMetadataParser.h"
#include <filesystem>
#include <mutex>
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

namespace moosic
{

    //==============================================================================
    // MetadataReader
    //==============================================================================

    class MetadataReader
    {
    public:
        //--------------------------------------------------------------------------
        // Construction / Destruction
        //--------------------------------------------------------------------------

        MetadataReader();
        ~MetadataReader();

        //--------------------------------------------------------------------------
        // Main API
        // extractAlbumArt: set to false for bulk imports (much faster!)
        //--------------------------------------------------------------------------

        MusicTrack ReadMetadataForSingleTrack(const std::filesystem::path &filePath,
                                              bool extractAlbumArt = true) const;

        //--------------------------------------------------------------------------
        // Duration API (for 2-phase import - called separately)
        //--------------------------------------------------------------------------

        unsigned int GetDurationWithBASS(const std::filesystem::path &filePath) const;

    private:
        //--------------------------------------------------------------------------
        // Format-Specific Parsers (delegated to individual parser classes)
        //--------------------------------------------------------------------------

        bool ParseMP3Metadata(const std::filesystem::path &filePath, 
                              MusicTrack &track,
                              bool extractAlbumArt) const;
        bool ParseFLACMetadata(const std::filesystem::path &filePath, 
                               MusicTrack &track,
                               bool extractAlbumArt) const;
        bool ParseMP4Metadata(const std::filesystem::path &filePath, 
                              MusicTrack &track,
                              bool extractAlbumArt) const;
        bool ParseOGGMetadata(const std::filesystem::path &filePath, 
                              MusicTrack &track,
                              bool extractAlbumArt) const;
        bool ParseWAVMetadata(const std::filesystem::path &filePath, 
                              MusicTrack &track,
                              bool extractAlbumArt) const;
        bool ParseAIFFMetadata(const std::filesystem::path &filePath, 
                               MusicTrack &track,
                               bool extractAlbumArt) const;
        bool ParseWVMetadata(const std::filesystem::path &filePath, 
                             MusicTrack &track,
                             bool extractAlbumArt) const;

        //--------------------------------------------------------------------------
        // Helpers
        //--------------------------------------------------------------------------

        MusicTrack CreateFallbackTrack(const std::filesystem::path &filePath) const;
        std::string CleanString(const std::string &input) const;
        std::string TruncateString(const std::string &input, size_t maxLength) const;
        std::string GetLowercaseExtension(const std::filesystem::path &filePath) const;
        bool IsAudioFile(const std::filesystem::path &filePath) const;

        //--------------------------------------------------------------------------
        // Members
        //--------------------------------------------------------------------------

        mutable std::mutex m_cacheMutex;
        mutable std::unordered_map<std::string, unsigned int> m_durationCache;

        //--------------------------------------------------------------------------
        // Logging
        //--------------------------------------------------------------------------

        static void Log(const std::string &message);
        static void LogError(const std::string &message, const std::string &details = "");
    };

} // namespace moosic