//==============================================================================
// MetadataReader.cpp
//==============================================================================
// Central metadata reader - dispatches to format-specific parsers
// BASS is called separately in Phase 2 of the import process
//==============================================================================

#include "MetadataReader.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>
#include <cstring>

// BASS headers
#include "../BassHeaders.h"

namespace moosic
{

    //==============================================================================
    // Thread-safe logging
    //==============================================================================

    namespace
    {
        std::mutex g_logMutex;

        void SafeLog(const std::string &prefix, const std::string &message)
        {
            std::lock_guard<std::mutex> lock(g_logMutex);
            std::cout << prefix << message << std::endl;
        }

        void SafeLogError(const std::string &prefix, const std::string &message, const std::string &details = "")
        {
            std::lock_guard<std::mutex> lock(g_logMutex);
            std::cerr << prefix << message;
            if (!details.empty())
                std::cerr << " - " << details;
            std::cerr << std::endl;
        }
    }

    void MetadataReader::Log(const std::string &message)
    {
        SafeLog("[MetadataReader] ", message);
    }

    void MetadataReader::LogError(const std::string &message, const std::string &details)
    {
        SafeLogError("[MetadataReader ERROR] ", message, details);
    }

    //==============================================================================
    // Constructor / Destructor
    //==============================================================================

    MetadataReader::MetadataReader()
    {
        Log("Initialized (Custom Parsers + BASS Phase 2)");
    }

    MetadataReader::~MetadataReader()
    {
        Log("Shutdown complete");
    }

    //==============================================================================
    // String Helpers
    //==============================================================================

    std::string MetadataReader::CleanString(const std::string &input) const
    {
        if (input.empty())
            return "";

        std::string result;
        result.reserve(input.size());
        bool inSpace = false;

        for (char c : input)
        {
            if (c == '\0' || (c < 32 && c != '\n' && c != '\t' && c != '\r'))
                continue;

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

        size_t start = result.find_first_not_of(" \t\n\r");
        if (start == std::string::npos)
            return "";
        size_t end = result.find_last_not_of(" \t\n\r");
        return result.substr(start, end - start + 1);
    }

    std::string MetadataReader::TruncateString(const std::string &input, size_t maxLength) const
    {
        std::string s = CleanString(input);
        if (s.length() <= maxLength)
            return s;

        size_t pos = maxLength;
        while (pos > 0 && s[pos] != ' ')
            pos--;
        if (pos < maxLength / 2)
            pos = maxLength;

        return s.substr(0, pos) + "...";
    }

    //==============================================================================
    // Main API - Metadata ONLY (no BASS - duration is 0)
    //==============================================================================

    MusicTrack MetadataReader::ReadMetadataForSingleTrack(const std::filesystem::path &filePath) const
    {
        //----------------------------------------------------------------------
        // Validate file - DON'T convert to string for file operations!
        //----------------------------------------------------------------------
        std::error_code ec;
        if (!std::filesystem::exists(filePath, ec))
        {
            LogError("File not found");
            return CreateFallbackTrack(filePath);
        }

        if (!std::filesystem::is_regular_file(filePath, ec))
        {
            LogError("Not a regular file");
            return CreateFallbackTrack(filePath);
        }

        if (!IsAudioFile(filePath))
        {
            LogError("Unsupported audio format: " + GetLowercaseExtension(filePath));
            return CreateFallbackTrack(filePath);
        }

        MusicTrack track;
        track.SetPath(filePath);

        //----------------------------------------------------------------------
        // Parse metadata ONLY (duration stays 0 - filled in Phase 2 by BASS)
        // Pass path directly to parsers - NO string conversion!
        //----------------------------------------------------------------------
        bool hasMetadata = false;
        std::string ext = GetLowercaseExtension(filePath);

        try
        {
            if (ext == ".mp3" || ext == ".mp2" || ext == ".mp1")
                hasMetadata = ParseMP3Metadata(filePath, track);
            else if (ext == ".flac")
                hasMetadata = ParseFLACMetadata(filePath, track);
            else if (ext == ".m4a" || ext == ".mp4" || ext == ".m4b")
                hasMetadata = ParseMP4Metadata(filePath, track);
            else if (ext == ".ogg" || ext == ".opus")
                hasMetadata = ParseOGGMetadata(filePath, track);
            else if (ext == ".wav")
                hasMetadata = ParseWAVMetadata(filePath, track);
            else if (ext == ".aiff" || ext == ".aif")
                hasMetadata = ParseAIFFMetadata(filePath, track);
            else if (ext == ".wv")
                hasMetadata = ParseWVMetadata(filePath, track);
        }
        catch (...)
        {
            LogError("Exception parsing metadata");
        }

        //----------------------------------------------------------------------
        // Fallback to filename parsing - use u8string() for cross-platform safety
        //----------------------------------------------------------------------
        if (!hasMetadata || track.GetTitle().empty())
        {
            std::string name;
            try
            {
                // u8string() returns UTF-8 on all platforms
                name = CleanString(filePath.stem().u8string());
            }
            catch (...)
            {
                try
                {
                    name = CleanString(filePath.stem().string());
                }
                catch (...)
                {
                    name = "Unknown Track";
                }
            }

            size_t dash = name.find(" - ");
            if (dash != std::string::npos)
            {
                if (track.GetArtist().empty())
                    track.SetArtist(TruncateString(name.substr(0, dash), 80));
                track.SetTitle(TruncateString(name.substr(dash + 3), 80));
            }
            else
            {
                track.SetTitle(TruncateString(name, 80));
            }
        }

        //----------------------------------------------------------------------
        // Set defaults for missing fields
        //----------------------------------------------------------------------
        if (track.GetArtist().empty())
            track.SetArtist("Unknown Artist");
        if (track.GetAlbum().empty())
            track.SetAlbum("Unknown Album");
        if (track.GetGenre().empty())
            track.SetGenre("Unknown");
        if (track.GetTitle().empty())
            track.SetTitle("Unknown Track");

        return track;
    }

    //==============================================================================
    // Format-Specific Parsers (delegated to individual parser classes)
    //==============================================================================
    bool MetadataReader::ParseMP3Metadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        Mp3MetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseFLACMetadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        FlacMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseMP4Metadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        Mp4MetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseOGGMetadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        OggMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseWAVMetadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        WavMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseAIFFMetadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        AiffMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseWVMetadata(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        WavPackMetadataParser parser;
        return parser.Parse(filePath, track);
    }
    //==============================================================================
    // BASS: Get duration (called in Phase 2, separate from metadata parsing)
    //==============================================================================

   unsigned int MetadataReader::GetDurationWithBASS(const std::filesystem::path &filePath) const
{
    // Use wstring on Windows for Unicode-safe cache key
#ifdef _WIN32
    std::wstring cacheKey = filePath.wstring();
#else
    std::string cacheKey = filePath.string();
#endif

    {
        std::lock_guard<std::mutex> lock(m_cacheMutex);
#ifdef _WIN32
        // Convert wstring to string for cache lookup (lossy but works for cache)
        std::string narrowKey(cacheKey.begin(), cacheKey.end());
        auto it = m_durationCache.find(narrowKey);
#else
        auto it = m_durationCache.find(cacheKey);
#endif
        if (it != m_durationCache.end())
            return it->second;
    }

    std::string ext = GetLowercaseExtension(filePath);
    unsigned int duration = 0;

#if defined(_WIN32)
    const std::wstring wpath = filePath.wstring();
    const void *filename = wpath.c_str();
    DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN | BASS_UNICODE;
#else
    const std::string path = filePath.string();
    const void *filename = path.c_str();
    DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN;
#endif

    HSTREAM stream = 0;

    stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, flags);

#if defined(_WIN32) || defined(__linux__)
    if (!stream && (ext == ".m4a" || ext == ".m4b" || ext == ".mp4"))
        stream = BASS_AAC_StreamCreateFile(FALSE, filename, 0, 0, flags);

    if (!stream && ext == ".flac")
        stream = BASS_FLAC_StreamCreateFile(FALSE, filename, 0, 0, flags);

    if (!stream && ext == ".opus")
        stream = BASS_OPUS_StreamCreateFile(FALSE, filename, 0, 0, flags);
#endif

#if defined(_WIN32)
    if (!stream && ext == ".wma")
        stream = BASS_WMA_StreamCreateFile(FALSE, filename, 0, 0, flags);
#endif

    if (!stream)
    {
#if defined(_WIN32)
        stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, BASS_STREAM_DECODE | BASS_UNICODE);
#else
        stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, BASS_STREAM_DECODE);
#endif
    }

    if (stream)
    {
        QWORD length = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
        if (length != static_cast<QWORD>(-1) && length > 0)
            duration = static_cast<unsigned int>(BASS_ChannelBytes2Seconds(stream, length));
        BASS_StreamFree(stream);
    }

    {
        std::lock_guard<std::mutex> lock(m_cacheMutex);
#ifdef _WIN32
        std::string narrowKey(cacheKey.begin(), cacheKey.end());
        m_durationCache[narrowKey] = duration;
#else
        m_durationCache[cacheKey] = duration;
#endif
    }

    return duration;
}
    //==============================================================================
    // Fallback track creation
    //==============================================================================

MusicTrack MetadataReader::CreateFallbackTrack(const std::filesystem::path &filePath) const
{
    MusicTrack track;
    track.SetPath(filePath);
    
    // Use u8string() for cross-platform Unicode-safe filename
    std::string title;
    try {
        title = TruncateString(CleanString(filePath.stem().u8string()), 80);
    } catch (...) {
        try {
            title = TruncateString(CleanString(filePath.stem().string()), 80);
        } catch (...) {
            title = "Unknown Track";
        }
    }
    
    track.SetTitle(title);
    track.SetArtist("Unknown Artist");
    track.SetAlbum("Unknown Album");
    track.SetGenre("Unknown");
    track.SetDuration(0);
    track.SetBitRate(0);
    track.SetSampleRate(0);
    track.SetChannels(0);
    track.SetHasAlbumArt(false);
    return track;
}
    //==============================================================================
    // Utilities
    //==============================================================================

    std::string MetadataReader::GetLowercaseExtension(const std::filesystem::path &filePath) const
    {
        std::string ext = filePath.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        return ext;
    }

    bool MetadataReader::IsAudioFile(const std::filesystem::path &filePath) const
    {
        static const std::vector<std::string> supported = {
            ".mp3", ".mp2", ".mp1", ".flac", ".wav", ".ogg", ".opus",
            ".m4a", ".m4b", /*".mp4",*/ ".wma", ".aac", ".aiff", ".aif",
            ".wv", ".ape", ".dsd", ".dff"};

        std::string ext = GetLowercaseExtension(filePath);
        return std::find(supported.begin(), supported.end(), ext) != supported.end();
    }

} // namespace moosic