#include "MetadataReader.h"
#include <algorithm>
#include <iostream>
#include <vector>

// FFmpeg headers
extern "C"
{
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/dict.h>
#include <libavutil/avutil.h>
}

// BASS headers
#include <bass.h>
#include <bass_aac.h>
#include <bassflac.h>
#include <bassopus.h>
#include <basswma.h>

namespace moosic
{

    //==============================================================================
    // Constructor / Destructor
    //==============================================================================

    MetadataReader::MetadataReader()
    {
        avformat_network_init();
        std::cout << "[MetadataReader] Ready (FFmpeg metadata + BASS duration)\n";
    }

    MetadataReader::~MetadataReader()
    {
        avformat_network_deinit();
        std::cout << "[MetadataReader] Shutdown\n";
    }

    //==============================================================================
    // String Helpers
    //==============================================================================

    std::string MetadataReader::CleanString(const std::string &input) const
    {
        if (input.empty())
            return "";

        std::string result = input;
        result.erase(std::remove(result.begin(), result.end(), '\0'), result.end());

        result.erase(std::remove_if(result.begin(), result.end(),
                                    [](char c)
                                    { return c < 32 && c != '\n' && c != '\t' && c != '\r'; }),
                     result.end());

        std::string cleaned;
        cleaned.reserve(result.size());
        bool inSpace = false;
        for (char c : result)
        {
            if (std::isspace(static_cast<unsigned char>(c)))
            {
                if (!inSpace)
                {
                    cleaned.push_back(' ');
                    inSpace = true;
                }
            }
            else
            {
                cleaned.push_back(c);
                inSpace = false;
            }
        }

        size_t start = cleaned.find_first_not_of(" \t\n\r");
        if (start == std::string::npos)
            return "";
        size_t end = cleaned.find_last_not_of(" \t\n\r");
        return cleaned.substr(start, end - start + 1);
    }

    std::string MetadataReader::TruncateString(const std::string &input, size_t maxLength) const
    {
        std::string s = CleanString(input);
        if (s.length() <= maxLength)
            return s;

        size_t pos = maxLength;
        while (pos > 0 && s[pos] != ' ')
            pos--;
        if (pos < maxLength - 10)
            pos = maxLength;

        return s.substr(0, pos) + "...";
    }

    //==============================================================================
    // Public API
    //==============================================================================

    MusicTrack MetadataReader::ReadMetadataForSingleTrack(const std::filesystem::path &filePath) const
    {
        // Validate file
        if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath))
            return CreateFallbackTrack(filePath);

        if (!IsAudioFile(filePath))
            return CreateFallbackTrack(filePath);

        // Create track
        MusicTrack track;
        track.SetPath(filePath);

        // Step 1: Read metadata with FFmpeg (title, artist, album, album art, etc.)
        bool hasMetadata = ReadMetadataWithFFmpeg(filePath, track);

        // Step 2: Get duration with BASS (always use BASS for duration)
        unsigned int duration = GetDurationWithBASS(filePath);
        if (duration > 0)
        {
            track.SetDuration(duration);
        }

        // Step 3: Filename fallback if FFmpeg didn't find title/artist
        if (!hasMetadata)
        {
            std::string name = CleanString(filePath.stem().string());
            size_t dash = name.find(" - ");
            if (dash != std::string::npos)
            {
                if (track.GetArtist().empty() || track.GetArtist() == "Unknown Artist")
                    track.SetArtist(TruncateString(name.substr(0, dash), 80));
                track.SetTitle(TruncateString(name.substr(dash + 3), 80));
            }
            else
            {
                track.SetTitle(TruncateString(name, 80));
            }
        }

        // Step 4: Set defaults for missing fields
        if (track.GetArtist().empty())
            track.SetArtist("Unknown Artist");
        if (track.GetAlbum().empty())
            track.SetAlbum("Unknown Album");
        if (track.GetGenre().empty())
            track.SetGenre("Unknown");

        return track;
    }

    //==============================================================================
    // Extract Album Art from Packet Stream (for MP3 with embedded art)
    //==============================================================================

    bool MetadataReader::ExtractAlbumArtFromPackets(AVFormatContext *fmt_ctx, MusicTrack &track) const
    {
        // Find the picture/album art stream
        int picture_stream_index = -1;
        for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i)
        {
            AVStream *stream = fmt_ctx->streams[i];
            if (!stream || !stream->codecpar)
                continue;

            if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            {
                AVCodecParameters *p = stream->codecpar;
                if (p->codec_id == AV_CODEC_ID_MJPEG ||
                    p->codec_id == AV_CODEC_ID_PNG ||
                    p->codec_id == AV_CODEC_ID_BMP ||
                    p->codec_id == AV_CODEC_ID_GIF)
                {
                    picture_stream_index = i;
                    std::cout << "[MetadataReader] Found album art stream: " << i
                              << " codec_id: " << p->codec_id << "\n";
                    break;
                }
            }
        }

        if (picture_stream_index == -1)
        {
            return false;
        }

        // Read packets to extract the image
        AVPacket packet;
        av_init_packet(&packet);
        packet.data = nullptr;
        packet.size = 0;

        // Seek to the beginning of the file
        av_seek_frame(fmt_ctx, -1, 0, AVSEEK_FLAG_BACKWARD);

        int ret = av_read_frame(fmt_ctx, &packet);
        while (ret >= 0)
        {
            if (packet.stream_index == picture_stream_index && packet.size > 0)
            {
                // Found the picture packet - extract the data
                std::cout << "[MetadataReader] Extracted album art from stream: " << packet.size << " bytes\n";

                std::vector<unsigned char> imageData;
                imageData.resize(packet.size);
                memcpy(imageData.data(), packet.data, packet.size);

                track.SetAlbumArtData(imageData);
                track.SetHasAlbumArt(true);

                av_packet_unref(&packet);
                return true;
            }
            av_packet_unref(&packet);
            ret = av_read_frame(fmt_ctx, &packet);
        }

        return false;
    }

    //==============================================================================
    // Extract Album Art from FFmpeg Metadata (APIC tags) - FIXED
    //==============================================================================
    bool MetadataReader::ExtractAlbumArt(AVFormatContext *fmt_ctx, MusicTrack &track) const
    {
        track.SetHasAlbumArt(false);
        track.SetAlbumArtData(std::vector<unsigned char>());

        if (!fmt_ctx)
            return false;

        // Try to find attached picture (APIC) using the correct FFmpeg API
        for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i)
        {
            AVStream *stream = fmt_ctx->streams[i];
            if (!stream || !stream->codecpar)
                continue;

            // Look for attached picture streams (album art)
            if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO &&
                (stream->codecpar->codec_id == AV_CODEC_ID_MJPEG ||
                 stream->codecpar->codec_id == AV_CODEC_ID_PNG))
            {

                // Read packets to extract the image data
                AVPacket packet;
                av_init_packet(&packet);
                packet.data = nullptr;
                packet.size = 0;

                av_seek_frame(fmt_ctx, -1, 0, AVSEEK_FLAG_BACKWARD);

                while (av_read_frame(fmt_ctx, &packet) >= 0)
                {
                    if (packet.stream_index == (int)i && packet.size > 0)
                    {
                        std::cout << "[MetadataReader] Found album art: " << packet.size << " bytes\n";

                        std::vector<unsigned char> imageData;
                        imageData.resize(packet.size);
                        memcpy(imageData.data(), packet.data, packet.size);

                        track.SetAlbumArtData(imageData);
                        track.SetHasAlbumArt(true);

                        av_packet_unref(&packet);
                        return true;
                    }
                    av_packet_unref(&packet);
                }
            }
        }

        return false;
    }
    //==============================================================================
    // FFmpeg: Read all metadata INCLUDING album art
    //==============================================================================

    bool MetadataReader::ReadMetadataWithFFmpeg(const std::filesystem::path &filePath, MusicTrack &track) const
    {
        AVFormatContext *fmt_ctx = nullptr;
        bool hasMetadata = false;

        // Open file
        int ret = avformat_open_input(&fmt_ctx, filePath.string().c_str(), nullptr, nullptr);
        if (ret < 0)
        {
            avformat_close_input(&fmt_ctx);
            return false;
        }

        // Read stream info (needed for codec params)
        ret = avformat_find_stream_info(fmt_ctx, nullptr);
        if (ret < 0)
        {
            std::cout << "[MetadataReader] Failed to find stream info\n";
            avformat_close_input(&fmt_ctx);
            return false;
        }

        // Extract metadata tags
        if (fmt_ctx->metadata)
        {
            AVDictionaryEntry *entry = nullptr;
            while ((entry = av_dict_get(fmt_ctx->metadata, "", entry, AV_DICT_IGNORE_SUFFIX)))
            {
                std::string key = entry->key ? entry->key : "";
                std::string val = entry->value ? entry->value : "";
                std::string cleanVal = CleanString(val);

                // Title
                if (key == "title" || key == "TIT2")
                {
                    track.SetTitle(TruncateString(cleanVal, 80));
                    hasMetadata = true;
                }
                // Artist
                else if (key == "artist" || key == "TPE1" || key == "ARTIST")
                {
                    track.SetArtist(TruncateString(cleanVal, 80));
                    hasMetadata = true;
                }
                // Album
                else if (key == "album" || key == "TALB" || key == "ALBUM")
                {
                    track.SetAlbum(TruncateString(cleanVal, 80));
                }
                // Genre
                else if (key == "genre" || key == "TCON" || key == "GENRE")
                {
                    track.SetGenre(TruncateString(cleanVal, 50));
                }
                // Year
                else if (key == "date" || key == "year" || key == "YEAR" || key == "TDRC")
                {
                    try
                    {
                        track.SetYear(std::stoi(cleanVal.substr(0, 4)));
                    }
                    catch (...)
                    {
                    }
                }
                // Track number
                else if (key == "track" || key == "TRCK" || key == "TRACKNUMBER")
                {
                    try
                    {
                        std::string t = cleanVal;
                        size_t p = t.find('/');
                        if (p != std::string::npos)
                            t = t.substr(0, p);
                        track.SetTrackNumber(std::stoi(t));
                    }
                    catch (...)
                    {
                    }
                }
            }
        }

        // Extract technical info (sample rate, channels, bitrate)
        for (unsigned i = 0; i < fmt_ctx->nb_streams; ++i)
        {
            if (fmt_ctx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                auto *p = fmt_ctx->streams[i]->codecpar;
                track.SetSampleRate(p->sample_rate);
                track.SetChannels(p->ch_layout.nb_channels);

                int br = fmt_ctx->bit_rate > 0 ? fmt_ctx->bit_rate / 1000
                         : p->bit_rate > 0     ? p->bit_rate / 1000
                                               : 0;
                track.SetBitRate(br);
                break;
            }
        }

        // ====================== EXTRACT ALBUM ART ======================
        bool hasArt = false;

        // Method 1: Try packet-based extraction first (most reliable for MP3)
        // This is the preferred method for MP3 files with embedded album art
        std::cout << "[MetadataReader] Trying packet-based album art extraction...\n";
        hasArt = ExtractAlbumArtFromPackets(fmt_ctx, track);

        // Method 2: If no art found, try metadata extraction (for APIC tags)
        if (!hasArt || track.GetAlbumArtData().empty())
        {
            std::cout << "[MetadataReader] Trying metadata-based album art extraction...\n";
            hasArt = ExtractAlbumArt(fmt_ctx, track);
        }

        if (hasArt && !track.GetAlbumArtData().empty())
        {
            std::cout << "[MetadataReader] Album art extracted successfully: "
                      << track.GetAlbumArtData().size() << " bytes\n";
        }
        else if (hasArt && track.GetAlbumArtData().empty())
        {
            std::cout << "[MetadataReader] Album art detected but data extraction failed\n";
            track.SetHasAlbumArt(false);
        }

        avformat_close_input(&fmt_ctx);
        return hasMetadata;
    }

    //==============================================================================
    // BASS: Get duration only
    //==============================================================================

    unsigned int MetadataReader::GetDurationWithBASS(const std::filesystem::path &filePath) const
    {
        // Check cache
        std::string pathStr = filePath.string();
        {
            std::lock_guard<std::mutex> lock(m_cacheMutex);
            auto it = m_durationCache.find(pathStr);
            if (it != m_durationCache.end())
            {
                return it->second;
            }
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

        // Try AAC for MP4/M4A
        if (ext == ".m4a" || ext == ".m4b" || ext == ".mp4")
        {
            stream = BASS_AAC_StreamCreateFile(FALSE, filename, 0, 0, flags);
        }

        // Try standard stream
        if (!stream)
        {
            stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, flags);
        }

        // Retry without PRESCAN
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
            {
                duration = static_cast<unsigned int>(BASS_ChannelBytes2Seconds(stream, length));
            }
            BASS_StreamFree(stream);
        }

        // Cache result
        {
            std::lock_guard<std::mutex> lock(m_cacheMutex);
            m_durationCache[pathStr] = duration;
        }

        return duration;
    }

    //==============================================================================
    // Fallback
    //==============================================================================

    MusicTrack MetadataReader::CreateFallbackTrack(const std::filesystem::path &filePath) const
    {
        MusicTrack track;
        track.SetPath(filePath);

        std::string name = CleanString(filePath.stem().string());
        track.SetTitle(TruncateString(name, 80));
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
        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c)
                       { return static_cast<char>(std::tolower(c)); });
        return ext;
    }

    bool MetadataReader::IsAudioFile(const std::filesystem::path &filePath) const
    {
        static const std::vector<std::string> supported = {
            ".mp3", ".mp2", ".mp1", ".flac", ".wav", ".ogg", ".opus",
            ".m4a", ".m4b", ".mp4", ".wma", ".aac", ".aiff", ".aif",
            ".wv", ".ape", ".dsd", ".dff"};
        return std::find(supported.begin(), supported.end(), GetLowercaseExtension(filePath)) != supported.end();
    }

} // namespace moosic