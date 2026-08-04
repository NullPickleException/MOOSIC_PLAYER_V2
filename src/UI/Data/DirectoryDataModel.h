//==============================================================================
// UI/Data/DirectoryDataModel.h
//==============================================================================
// Central data store for directory management.
// Handles import state, directory list, and progress tracking.
// The window just reads from this and renders - no data ownership.
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../../Services/DirectoryScanner.h"
#include "../../Services/Metadata/MetadataReader.h"

#include <atomic>
#include <thread>
#include <vector>
#include <filesystem>
#include <functional>
#include <set>

namespace moosic
{

class PlaylistDataModel;

class DirectoryDataModel
{
public:
    explicit DirectoryDataModel(MusicLibrary& library, PlaylistDataModel* playlistModel = nullptr);
    ~DirectoryDataModel();

    //--------------------------------------------------------------------------
    // Directory Access (read-only for views)
    //--------------------------------------------------------------------------

    const std::vector<std::filesystem::path>& GetDirectories() const;
    bool HasDirectory(const std::filesystem::path& path) const;

    //--------------------------------------------------------------------------
    // Import State
    //--------------------------------------------------------------------------

    bool IsImporting() const { return m_isImporting.load(); }
    bool IsFinished() const { return m_isFinished.load(); }
    
    int GetTotalFiles() const { return m_totalFiles.load(); }
    int GetProcessedFiles() const { return m_processedFiles.load(); }
    int GetSuccessfulFiles() const { return m_successfulFiles.load(); }
    
    float GetProgress() const;

    //--------------------------------------------------------------------------
    // Actions
    //--------------------------------------------------------------------------

    void AddDirectory();                          // Opens NFD folder picker
    void AddDirectory(const std::filesystem::path& folder);  // Direct add
    void RemoveDirectory(const std::filesystem::path& path);
    void ClearAll();

    //--------------------------------------------------------------------------
    // Startup: Check for new files in existing directories
    //--------------------------------------------------------------------------

    void ScanForNewFiles();  // Call once on startup after library is loaded

    //--------------------------------------------------------------------------
    // Update (call each frame)
    //--------------------------------------------------------------------------

    void Update();  // Checks if import finished, commits if so

    //--------------------------------------------------------------------------
    // Change Notification
    //--------------------------------------------------------------------------

    using DataChangedCallback = std::function<void()>;
    void SetOnDataChanged(DataChangedCallback callback) { m_onDataChanged = std::move(callback); }

private:
    void StartImport(const std::filesystem::path& folder);
    void StartIncrementalImport(const std::filesystem::path& folder, const std::vector<std::filesystem::path>& newFiles);
    void CommitImport();
    
    std::vector<std::filesystem::path> FindNewFiles(const std::filesystem::path& directory) const;
    
    void NotifyChanged();

private:
    MusicLibrary& m_sourceLibrary;
    DirectoryScanner m_scanner;
    MetadataReader m_reader;

    // Import state
    std::thread m_importThread;
    std::atomic<bool> m_isImporting{false};
    std::atomic<bool> m_isFinished{false};
    std::atomic<int> m_totalFiles{0};
    std::atomic<int> m_processedFiles{0};
    std::atomic<int> m_successfulFiles{0};

    std::filesystem::path m_pendingDirectory;
    std::vector<MusicTrack> m_importedTracks;

    // Notification
    DataChangedCallback m_onDataChanged;
    
    // Playlist model for cleaning up track IDs on directory removal
    PlaylistDataModel* m_playlistModel = nullptr;
};

} // namespace moosic