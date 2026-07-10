#include "MetadataReader.h"
#include <bass.h>
#include <bass_aac.h>
#include <bassflac.h>
#include <bassopus.h>
#include <basswma.h>
#include <algorithm>
#include <iostream>

namespace moosic
{

MetadataReader::MetadataReader()
{
    // Don't init BASS - AudioEngine already did it
    std::cout << "[MetadataReader] Ready\n";
}

MetadataReader::~MetadataReader()
{
    // Don't free BASS - AudioEngine owns it
}

MusicTrack MetadataReader::ReadMetadataForSingleTrack(
    const std::filesystem::path& filePath) const
{
    if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath))
        return CreateFallbackTrack(filePath);

    if (!IsAudioFile(filePath))
        return CreateFallbackTrack(filePath);

    try
    {
        return ExtractWithBASS(filePath);
    }
    catch (...)
    {
        return CreateFallbackTrack(filePath);
    }
}

MusicTrack MetadataReader::ExtractWithBASS(const std::filesystem::path& filePath) const
{
    MusicTrack track;
    track.SetPath(filePath);

    std::string path = filePath.string();
    std::string ext = GetLowercaseExtension(filePath);

    HSTREAM stream = 0;

    if (ext == ".m4a" || ext == ".m4b" || ext == ".mp4")
    {
        stream = BASS_AAC_StreamCreateFile(FALSE, path.c_str(), 0, 0, BASS_STREAM_DECODE);
    }

    if (!stream)
    {
        stream = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, BASS_STREAM_DECODE | BASS_STREAM_PRESCAN);
    }

    if (!stream)
    {
        stream = BASS_StreamCreateFile(FALSE, path.c_str(), 0, 0, BASS_STREAM_DECODE);
        if (!stream)
        {
            return CreateFallbackTrack(filePath);
        }
    }

    QWORD length = BASS_ChannelGetLength(stream, BASS_POS_BYTE);
    double duration = 0.0;
    
    if (length != (QWORD)-1 && length > 0)
    {
        duration = BASS_ChannelBytes2Seconds(stream, length);
    }
    
    if (duration > 0)
    {
        track.SetDuration(static_cast<unsigned int>(duration));
    }

    BASS_CHANNELINFO info{};
    if (BASS_ChannelGetInfo(stream, &info))
    {
        track.SetSampleRate(info.freq);
        track.SetChannels(info.chans);
        track.SetBitRate(info.freq * info.chans * 16 / 1000);
    }

    BASS_StreamFree(stream);

    std::string filename = filePath.stem().string();
    size_t dash = filename.find(" - ");
    if (dash != std::string::npos)
    {
        track.SetArtist(filename.substr(0, dash));
        track.SetTitle(filename.substr(dash + 3));
    }
    else
    {
        track.SetTitle(filename);
        track.SetArtist("Unknown Artist");
    }

    track.SetAlbum("Unknown Album");
    track.SetGenre("Unknown");

    return track;
}

MusicTrack MetadataReader::CreateFallbackTrack(const std::filesystem::path& filePath) const
{
    MusicTrack track;
    track.SetPath(filePath);
    track.SetTitle(filePath.stem().string());
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

std::string MetadataReader::GetLowercaseExtension(const std::filesystem::path& filePath) const
{
    std::string ext = filePath.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return ext;
}

bool MetadataReader::IsAudioFile(const std::filesystem::path& filePath) const
{
    static const std::vector<std::string> supported = {
        ".mp3", ".mp2", ".mp1", ".flac", ".wav", ".ogg",
        ".m4a", ".m4b", ".mp4", ".wma", ".opus", ".aac"
    };
    std::string ext = GetLowercaseExtension(filePath);
    return std::find(supported.begin(), supported.end(), ext) != supported.end();
}

} // namespace moosic