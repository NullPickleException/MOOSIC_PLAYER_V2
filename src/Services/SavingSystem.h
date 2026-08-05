//==============================================================================
// Services/SavingSystem.h
//==============================================================================
// Unified JSON save/load system for all application state
//==============================================================================

#pragma once

#include <string>
#include <filesystem>

namespace moosic
{
    class MusicLibrary;
    class PlaylistDataModel;
    class PlaybackController;
    class SettingsDataModel;
    struct LayoutStateDataModel;
    class LibraryDataModel;
}

namespace moosic
{

class SavingSystem
{
public:
    explicit SavingSystem(const std::filesystem::path& savePath);

    //--------------------------------------------------------------------------
    // Core Operations - Unified single JSON file
    //--------------------------------------------------------------------------

    bool Save(const MusicLibrary& library,
              const PlaylistDataModel& playlists,
              const PlaybackController& controller,
              const SettingsDataModel& settings,
              const LayoutStateDataModel& layoutState,
              const LibraryDataModel& libraryData);

    bool Load(MusicLibrary& library,
              PlaylistDataModel& playlists,
              PlaybackController& controller,
              SettingsDataModel& settings,
              LayoutStateDataModel& layoutState,
              LibraryDataModel& libraryData);

private:
    std::filesystem::path m_savePath;
};

} // namespace moosic