#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace moosic
{

class MusicTrack
{
public:
    MusicTrack() = default;
    ~MusicTrack() = default;

    //----------------------------------------------------------
    // Setters
    //----------------------------------------------------------

    void SetId(std::size_t id);
    void SetPath(const std::filesystem::path& path);

    void SetTitle(const std::string& title);
    void SetArtist(const std::string& artist);
    void SetAlbum(const std::string& album);
    void SetGenre(const std::string& genre);

    void SetTrackNumber(unsigned int trackNumber);
    void SetYear(unsigned int year);

    void SetDuration(unsigned int seconds);
    void SetSampleRate(unsigned int sampleRate);
    void SetBitRate(unsigned int bitRate);
    void SetChannels(unsigned int channels);

    void SetHasAlbumArt(bool value);
    void SetAlbumArtData(const std::vector<unsigned char>& data);
    void SetFavourite(bool value);

    //----------------------------------------------------------
    // Getters
    //----------------------------------------------------------

    std::size_t GetId() const;
    const std::filesystem::path& GetPath() const;
    std::string GetFilename() const;
    std::string GetExtension() const;

    const std::string& GetTitle() const;
    const std::string& GetArtist() const;
    const std::string& GetAlbum() const;
    const std::string& GetGenre() const;

    unsigned int GetTrackNumber() const;
    unsigned int GetYear() const;

    unsigned int GetDuration() const;
    unsigned int GetSampleRate() const;
    unsigned int GetBitRate() const;
    unsigned int GetChannels() const;

    bool HasAlbumArt() const;
    const std::vector<unsigned char>& GetAlbumArtData() const;
    bool IsFavourite() const;

private:
    std::filesystem::path m_path;

    std::string m_title;
    std::string m_artist;
    std::string m_album;
    std::string m_genre;

    unsigned int m_trackNumber = 0;
    unsigned int m_year = 0;

    unsigned int m_durationSeconds = 0;
    unsigned int m_sampleRate = 0;
    unsigned int m_bitRate = 0;
    unsigned int m_channels = 0;

    bool m_hasAlbumArt = false;
    bool m_isFavourite = false;
    
    std::vector<unsigned char> m_albumArtData;  // Raw image data

    std::size_t m_id = 0;
};

}