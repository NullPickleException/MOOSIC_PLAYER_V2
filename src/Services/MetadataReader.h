#pragma once
#include "../Models/MusicTrack.h"
#include <filesystem>
#include <vector>

namespace moosic
{

class MetadataReader
{
public:
    MetadataReader();
    ~MetadataReader();

    MusicTrack ReadMetadataForSingleTrack(const std::filesystem::path& filePath) const;

private:
    MusicTrack ExtractWithBASS(const std::filesystem::path& filePath) const;
    MusicTrack CreateFallbackTrack(const std::filesystem::path& filePath) const;
    bool IsAudioFile(const std::filesystem::path& filePath) const;
    std::string GetLowercaseExtension(const std::filesystem::path& filePath) const;
};

} // namespace moosic