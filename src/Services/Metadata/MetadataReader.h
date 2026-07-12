//==============================================================================
// MetadataReader.h
//==============================================================================
// Central metadata reader that dispatches to format-specific parsers
// Duration is always handled by BASS
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
        //--------------------------------------------------------------------------

        MusicTrack ReadMetadataForSingleTrack(const std::filesystem::path &filePath) const;

    private:
        //--------------------------------------------------------------------------
        // Format-Specific Parsers (delegated to individual parser classes)
        //--------------------------------------------------------------------------

        bool ParseMP3Metadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseFLACMetadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseMP4Metadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseOGGMetadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseWAVMetadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseAIFFMetadata(const std::string &filePath, MusicTrack &track) const;
        bool ParseWVMetadata(const std::string &filePath, MusicTrack &track) const;

        //--------------------------------------------------------------------------
        // BASS Duration (unchanged - always used for duration)
        //--------------------------------------------------------------------------

        unsigned int GetDurationWithBASS(const std::filesystem::path &filePath) const;

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