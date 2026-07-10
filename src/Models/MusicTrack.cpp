#include "MusicTrack.h"

namespace moosic
{

//----------------------------------------------------------
// Setters
//----------------------------------------------------------

void MusicTrack::SetId(std::size_t id)
{
    m_id = id;
}

void MusicTrack::SetPath(const std::filesystem::path& path)
{
    m_path = path;
}

void MusicTrack::SetTitle(const std::string& title)
{
    m_title = title;
}

void MusicTrack::SetArtist(const std::string& artist)
{
    m_artist = artist;
}

void MusicTrack::SetAlbum(const std::string& album)
{
    m_album = album;
}

void MusicTrack::SetGenre(const std::string& genre)
{
    m_genre = genre;
}

void MusicTrack::SetTrackNumber(unsigned int trackNumber)
{
    m_trackNumber = trackNumber;
}

void MusicTrack::SetYear(unsigned int year)
{
    m_year = year;
}

void MusicTrack::SetDuration(unsigned int seconds)
{
    m_durationSeconds = seconds;
}

void MusicTrack::SetSampleRate(unsigned int sampleRate)
{
    m_sampleRate = sampleRate;
}

void MusicTrack::SetBitRate(unsigned int bitRate)
{
    m_bitRate = bitRate;
}

void MusicTrack::SetChannels(unsigned int channels)
{
    m_channels = channels;
}

void MusicTrack::SetHasAlbumArt(bool value)
{
    m_hasAlbumArt = value;
}

void MusicTrack::SetFavourite(bool value)
{
    m_isFavourite = value;
}

//----------------------------------------------------------
// Getters
//----------------------------------------------------------

std::size_t MusicTrack::GetId() const
{
    return m_id;
}

const std::filesystem::path& MusicTrack::GetPath() const
{
    return m_path;
}

std::string MusicTrack::GetFilename() const
{
    return m_path.filename().string();
}

std::string MusicTrack::GetExtension() const
{
    std::string ext = m_path.extension().string();
    if (!ext.empty() && ext[0] == '.')
        ext = ext.substr(1);  // Remove the dot
    return ext;
}

const std::string& MusicTrack::GetTitle() const
{
    return m_title;
}

const std::string& MusicTrack::GetArtist() const
{
    return m_artist;
}

const std::string& MusicTrack::GetAlbum() const
{
    return m_album;
}

const std::string& MusicTrack::GetGenre() const
{
    return m_genre;
}

unsigned int MusicTrack::GetTrackNumber() const
{
    return m_trackNumber;
}

unsigned int MusicTrack::GetYear() const
{
    return m_year;
}

unsigned int MusicTrack::GetDuration() const
{
    return m_durationSeconds;
}

unsigned int MusicTrack::GetSampleRate() const
{
    return m_sampleRate;
}

unsigned int MusicTrack::GetBitRate() const
{
    return m_bitRate;
}

unsigned int MusicTrack::GetChannels() const
{
    return m_channels;
}

bool MusicTrack::HasAlbumArt() const
{
    return m_hasAlbumArt;
}

bool MusicTrack::IsFavourite() const
{
    return m_isFavourite;
}

}