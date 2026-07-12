//==============================================================================
// MetadataReader.cpp
//==============================================================================
// Central metadata reader - dispatches to format-specific parsers
// BASS handles all duration extraction
//==============================================================================

#include "MetadataReader.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <mutex>
#include <cstring>

// BASS headers
#include <bass.h>
#include <bass_aac.h>
#include <bassflac.h>
#include <bassopus.h>
#include <basswma.h>

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
        Log("Initialized (Custom Parsers + BASS)");
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
    // Main API
    //==============================================================================

    MusicTrack MetadataReader::ReadMetadataForSingleTrack(const std::filesystem::path &filePath) const
    {
        std::string pathStr = filePath.string();

        //----------------------------------------------------------------------
        // Validate file
        //----------------------------------------------------------------------
        if (!std::filesystem::exists(filePath))
        {
            LogError("File not found: " + pathStr);
            return CreateFallbackTrack(filePath);
        }

        if (!std::filesystem::is_regular_file(filePath))
        {
            LogError("Not a regular file: " + pathStr);
            return CreateFallbackTrack(filePath);
        }

        if (!IsAudioFile(filePath))
        {
            LogError("Unsupported audio format: " + GetLowercaseExtension(filePath));
            return CreateFallbackTrack(filePath);
        }

        Log("Processing: " + pathStr);
        MusicTrack track;
        track.SetPath(filePath);

        //----------------------------------------------------------------------
        // Step 1: Parse metadata with format-specific parsers
        //----------------------------------------------------------------------
        bool hasMetadata = false;
        std::string ext = GetLowercaseExtension(filePath);

        try
        {
            if (ext == ".mp3" || ext == ".mp2" || ext == ".mp1")
                hasMetadata = ParseMP3Metadata(pathStr, track);
            else if (ext == ".flac")
                hasMetadata = ParseFLACMetadata(pathStr, track);
            else if (ext == ".m4a" || ext == ".mp4" || ext == ".m4b")
                hasMetadata = ParseMP4Metadata(pathStr, track);
            else if (ext == ".ogg" || ext == ".opus")
                hasMetadata = ParseOGGMetadata(pathStr, track);
            else if (ext == ".wav")
                hasMetadata = ParseWAVMetadata(pathStr, track);
            else if (ext == ".aiff" || ext == ".aif")
                hasMetadata = ParseAIFFMetadata(pathStr, track);
            else if (ext == ".wv")
                hasMetadata = ParseWVMetadata(pathStr, track);
        }
        catch (...)
        {
            LogError("Exception parsing metadata");
        }

        //----------------------------------------------------------------------
        // Step 2: Get duration with BASS (always used)
        //----------------------------------------------------------------------
        unsigned int duration = GetDurationWithBASS(filePath);
        if (duration > 0)
        {
            track.SetDuration(duration);
            Log("BASS duration: " + std::to_string(duration) + "s");
        }

        //----------------------------------------------------------------------
        // Step 3: Fallback to filename parsing
        //----------------------------------------------------------------------
        if (!hasMetadata || track.GetTitle().empty())
        {
            std::string name = CleanString(filePath.stem().string());
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
        // Step 4: Set defaults for missing fields
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

    bool MetadataReader::ParseMP3Metadata(const std::string &filePath, MusicTrack &track) const
    {
        Mp3MetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseFLACMetadata(const std::string &filePath, MusicTrack &track) const
    {
        FlacMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseMP4Metadata(const std::string &filePath, MusicTrack &track) const
    {
        Mp4MetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseOGGMetadata(const std::string &filePath, MusicTrack &track) const
    {
        OggMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseWAVMetadata(const std::string &filePath, MusicTrack &track) const
    {
        WavMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseAIFFMetadata(const std::string &filePath, MusicTrack &track) const
    {
        AiffMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    bool MetadataReader::ParseWVMetadata(const std::string &filePath, MusicTrack &track) const
    {
        WavPackMetadataParser parser;
        return parser.Parse(filePath, track);
    }

    //==============================================================================
    // BASS: Get duration
    //==============================================================================

    unsigned int MetadataReader::GetDurationWithBASS(const std::filesystem::path &filePath) const
    {
        std::string pathStr = filePath.string();

        {
            std::lock_guard<std::mutex> lock(m_cacheMutex);
            auto it = m_durationCache.find(pathStr);
            if (it != m_durationCache.end())
                return it->second;
        }

        std::string ext = GetLowercaseExtension(filePath);
        unsigned int duration = 0;

#ifdef _WIN32
        const std::wstring path = filePath.wstring();
        const void *filename = path.c_str();
        DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN | BASS_UNICODE;
#else
        const std::string path = filePath.string();
        const void *filename = path.c_str();
        DWORD flags = BASS_STREAM_DECODE | BASS_STREAM_PRESCAN;
#endif

        HSTREAM stream = 0;

        if (ext == ".m4a" || ext == ".m4b" || ext == ".mp4")
            stream = BASS_AAC_StreamCreateFile(FALSE, filename, 0, 0, flags);
        if (!stream && ext == ".flac")
            stream = BASS_FLAC_StreamCreateFile(FALSE, filename, 0, 0, flags);
        if (!stream && ext == ".opus")
            stream = BASS_OPUS_StreamCreateFile(FALSE, filename, 0, 0, flags);
        if (!stream && ext == ".wma")
            stream = BASS_WMA_StreamCreateFile(FALSE, filename, 0, 0, flags);
        if (!stream)
            stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, flags);
        if (!stream)
        {
#ifdef _WIN32
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
            m_durationCache[pathStr] = duration;
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
        track.SetTitle(TruncateString(CleanString(filePath.stem().string()), 80));
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
            ".m4a", ".m4b", ".mp4", ".wma", ".aac", ".aiff", ".aif",
            ".wv", ".ape", ".dsd", ".dff"};

        std::string ext = GetLowercaseExtension(filePath);
        return std::find(supported.begin(), supported.end(), ext) != supported.end();
    }

} // namespace moosic