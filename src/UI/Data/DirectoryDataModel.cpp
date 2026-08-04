//==============================================================================
// UI/Data/DirectoryDataModel.cpp
//==============================================================================

#include "DirectoryDataModel.h"
#include "PlaylistDataModel.h"
#include "../../Models/MusicTrack.h"

#include <nfd.h>
#include <future>
#include <iostream>
#include <unordered_map>
#include <algorithm>

namespace moosic
{

    //==============================================================================
    // Helper to check if a path is a subpath of another
    //==============================================================================

    static bool IsSubPath(const std::filesystem::path &path, const std::filesystem::path &base)
    {
        std::error_code ec;
        auto rel = std::filesystem::relative(path, base, ec);
        if (ec)
            return false;
        return !rel.empty() && rel.native()[0] != '.';
    }

    //==============================================================================
    // Constructor / Destructor
    //==============================================================================

    DirectoryDataModel::DirectoryDataModel(MusicLibrary &library, PlaylistDataModel *playlistModel)
        : m_sourceLibrary(library), m_playlistModel(playlistModel)
    {
    }

    DirectoryDataModel::~DirectoryDataModel()
    {
        if (m_importThread.joinable())
            m_importThread.join();
    }

    //==============================================================================
    // Directory Access
    //==============================================================================

    const std::vector<std::filesystem::path> &DirectoryDataModel::GetDirectories() const
    {
        return m_sourceLibrary.GetDirectories();
    }

    bool DirectoryDataModel::HasDirectory(const std::filesystem::path &path) const
    {
        return m_sourceLibrary.HasDirectory(path);
    }

    //==============================================================================
    // Import State
    //==============================================================================

    float DirectoryDataModel::GetProgress() const
    {
        int total = m_totalFiles.load(std::memory_order_acquire);
        if (total > 0)
        {
            int processed = m_processedFiles.load(std::memory_order_acquire);
            return static_cast<float>(processed) / static_cast<float>(total);
        }
        return 0.0f;
    }

    //==============================================================================
    // Actions
    //==============================================================================

    void DirectoryDataModel::AddDirectory()
    {
        NFD_Init();

        nfdu8char_t *outPath = nullptr;
        nfdresult_t result = NFD_PickFolderU8(&outPath, nullptr);

        if (result == NFD_OKAY)
        {
            std::filesystem::path folder(outPath);
            NFD_FreePathU8(outPath);

            if (!m_sourceLibrary.HasDirectory(folder))
                StartImport(folder);
        }

        NFD_Quit();
    }

    void DirectoryDataModel::AddDirectory(const std::filesystem::path &folder)
    {
        if (!m_sourceLibrary.HasDirectory(folder))
            StartImport(folder);
    }

    void DirectoryDataModel::RemoveDirectory(const std::filesystem::path &path)
    {
        // Collect track IDs from this directory before removing them
        if (m_playlistModel)
        {
            std::vector<std::size_t> idsToRemove;
            for (const auto &track : m_sourceLibrary.GetTracks())
            {
                if (track.GetPath().parent_path() == path)
                    idsToRemove.push_back(track.GetId());
            }

            // Remove these IDs from all playlists
            auto &playlists = m_playlistModel->GetAllPlaylists();
            for (auto &playlist : playlists)
            {
                playlist.trackIds.erase(
                    std::remove_if(playlist.trackIds.begin(), playlist.trackIds.end(),
                                   [&](std::size_t id)
                                   {
                                       return std::find(idsToRemove.begin(), idsToRemove.end(), id) != idsToRemove.end();
                                   }),
                    playlist.trackIds.end());
            }

            // Rebuild active playlist if one is selected
            if (m_playlistModel->GetActivePlaylistIndex().has_value())
            {
                m_playlistModel->RebuildActiveTrackList();
            }

            m_playlistModel->NotifyDataChanged();
        }

        m_sourceLibrary.RemoveTracksFromDirectory(path);
        m_sourceLibrary.RemoveDirectory(path);

        NotifyChanged();
    }

    void DirectoryDataModel::ClearAll()
    {
        // Clear all track IDs from all playlists
        if (m_playlistModel)
        {
            auto &playlists = m_playlistModel->GetAllPlaylists();
            for (auto &playlist : playlists)
                playlist.trackIds.clear();

            m_playlistModel->ClearActivePlaylistData();
            m_playlistModel->NotifyDataChanged();
        }

        m_sourceLibrary.Clear();
        NotifyChanged();
    }

    //==============================================================================
    // Startup: Scan for new files in existing directories
    //==============================================================================

    void DirectoryDataModel::ScanForNewFiles()
    {
        // Don't scan if already importing
        if (m_isImporting.load(std::memory_order_acquire))
            return;

        const auto &directories = m_sourceLibrary.GetDirectories();
        if (directories.empty())
            return;

        // Phase 1: Quick scan to find new files (very fast - just file system check)
        std::vector<std::filesystem::path> allNewFiles;
        size_t totalNewFiles = 0;

        for (const auto &dir : directories)
        {
            std::error_code ec;
            if (!std::filesystem::exists(dir, ec) || !std::filesystem::is_directory(dir, ec))
                continue;

            auto newFiles = FindNewFiles(dir);
            if (!newFiles.empty())
            {
                totalNewFiles += newFiles.size();
                allNewFiles.insert(allNewFiles.end(), newFiles.begin(), newFiles.end());
            }
        }

        if (totalNewFiles == 0)
        {
            std::cout << "[DirectoryDataModel] No new files found in existing directories." << std::endl;
            return;
        }

        std::cout << "[DirectoryDataModel] Found " << totalNewFiles << " new file(s) to import." << std::endl;

        // Phase 2: Import new files
        if (totalNewFiles <= 5)
        {
            // For very few files, import synchronously (instant, no progress bar needed)
            std::vector<MusicTrack> newTracks;
            MetadataReader reader;

            for (const auto &file : allNewFiles)
            {
                MusicTrack track;
                try
                {
                    track = reader.ReadMetadataForSingleTrack(file);

                    // Get duration with BASS
                    try
                    {
                        unsigned int duration = reader.GetDurationWithBASS(file);
                        if (duration > 0)
                            track.SetDuration(duration);
                    }
                    catch (...)
                    {
                    }
                }
                catch (...)
                {
                    // Create fallback track
                    track.SetPath(file);
                    try
                    {
                        track.SetTitle(file.stem().u8string());
                    }
                    catch (...)
                    {
                        try
                        {
                            track.SetTitle(file.stem().string());
                        }
                        catch (...)
                        {
                            track.SetTitle("Unknown Track");
                        }
                    }
                    track.SetArtist("Unknown Artist");
                    track.SetAlbum("Unknown Album");
                    track.SetGenre("Unknown");
                    track.SetDuration(0);
                }

                newTracks.push_back(std::move(track));
            }

            // Add all new tracks to library
            for (auto &track : newTracks)
                m_sourceLibrary.AddTrack(track);

            std::cout << "[DirectoryDataModel] Successfully imported " << newTracks.size()
                      << " new track(s)." << std::endl;

            NotifyChanged();
        }
        else
        {
            // For many files, use the async import with progress bar
            // Use first directory as the "pending" directory for UI purposes
            m_pendingDirectory = directories[0];
            StartIncrementalImport(directories[0], allNewFiles); // FIXED: was 'allFiles', now 'allNewFiles'
        }
    }

    std::vector<std::filesystem::path> DirectoryDataModel::FindNewFiles(const std::filesystem::path &directory) const
    {
        std::vector<std::filesystem::path> newFiles;

        // Build a set of existing file paths for O(log n) lookup
        std::set<std::filesystem::path> existingPaths;
        for (const auto &track : m_sourceLibrary.GetTracks())
        {
            const auto &trackPath = track.GetPath();
            // Check if track is in this directory or any subdirectory
            if (trackPath.parent_path() == directory || IsSubPath(trackPath, directory))
            {
                existingPaths.insert(std::filesystem::absolute(trackPath));
            }
        }

        // Scan directory for current audio files
        DirectoryScanner scanner;
        auto currentFiles = scanner.Scan(directory);

        // Find files that aren't in the existing set (new files)
        for (const auto &file : currentFiles)
        {
            if (existingPaths.find(std::filesystem::absolute(file)) == existingPaths.end())
            {
                newFiles.push_back(file);
            }
        }

        return newFiles;
    }

    //==============================================================================
    // Update
    //==============================================================================

    void DirectoryDataModel::Update()
    {
        if (m_isFinished.load(std::memory_order_acquire))
            CommitImport();
    }

    //==============================================================================
    // Import (Private) - FULL IMPORT
    //==============================================================================

    void DirectoryDataModel::StartImport(const std::filesystem::path &folder)
    {
        // Prevent double-import
        bool expected = false;
        if (!m_isImporting.compare_exchange_strong(expected, true))
            return;

        if (m_importThread.joinable())
            m_importThread.join();

        // Reset state
        m_pendingDirectory = folder;
        m_importedTracks.clear();
        m_totalFiles.store(0, std::memory_order_release);
        m_processedFiles.store(0, std::memory_order_release);
        m_successfulFiles.store(0, std::memory_order_release);
        m_isFinished.store(false, std::memory_order_release);

        NotifyChanged();

        m_importThread = std::thread([this, folder]()
                                     {
        auto files = m_scanner.Scan(folder);
        int total = static_cast<int>(files.size());
        m_totalFiles.store(total, std::memory_order_release);

        if (total > 0)
        {
            unsigned int numThreads = std::max(1u, std::min(std::thread::hardware_concurrency(), 8u));
            
            std::vector<std::future<void>> futures;
            std::mutex tracksMutex;
            std::atomic<int> processed{0};
            std::vector<MusicTrack> tracks;
            std::vector<size_t> pendingBASS;
            tracks.reserve(total);

            size_t chunkSize = (total + numThreads - 1) / numThreads;

            for (unsigned int t = 0; t < numThreads; ++t)
            {
                size_t start = t * chunkSize;
                if (start >= files.size()) break;
                size_t end = std::min(start + chunkSize, files.size());

                futures.push_back(std::async(std::launch::async, 
                    [this, &files, start, end, &processed, &tracksMutex, &tracks, &pendingBASS]()
                    {
                        std::vector<size_t> localPending;
                        
                        for (size_t i = start; i < end; ++i)
                        {
                            MusicTrack track;
                            
                            try
                            {
                                track = m_reader.ReadMetadataForSingleTrack(files[i]);
                                track.SetDuration(0);
                            }
                            catch (...)
                            {
                                // CREATE FALLBACK - don't lose the file!
                                track.SetPath(files[i]);
                                try { track.SetTitle(files[i].stem().u8string()); } 
                                catch (...) { 
                                    try { track.SetTitle(files[i].stem().string()); } 
                                    catch (...) { track.SetTitle("Unknown Track"); }
                                }
                                track.SetArtist("Unknown Artist");
                                track.SetAlbum("Unknown Album");
                                track.SetGenre("Unknown");
                                track.SetDuration(0);
                            }
                            
                            {
                                std::lock_guard<std::mutex> lock(tracksMutex);
                                size_t trackIndex = tracks.size();
                                tracks.push_back(std::move(track));
                                localPending.push_back(trackIndex);
                            }

                            int count = processed.fetch_add(1, std::memory_order_relaxed) + 1;
                            m_processedFiles.store(count, std::memory_order_release);
                            m_successfulFiles.store(static_cast<int>(tracks.size()), std::memory_order_release);
                        }
                        
                        if (!localPending.empty())
                        {
                            std::lock_guard<std::mutex> lock(tracksMutex);
                            pendingBASS.insert(pendingBASS.end(), localPending.begin(), localPending.end());
                        }
                    }
                ));
            }

            for (auto& f : futures)
                if (f.valid()) f.get();

            // PHASE 2: BASS duration
            if (!pendingBASS.empty())
            {
                m_processedFiles.store(0, std::memory_order_release);
                
                // DO BASS SEQUENTIALLY to avoid threading issues
                for (size_t i = 0; i < pendingBASS.size(); ++i)
                {
                    size_t trackIndex = pendingBASS[i];
                    if (trackIndex < tracks.size())
                    {
                        try
                        {
                            unsigned int duration = m_reader.GetDurationWithBASS(tracks[trackIndex].GetPath());
                            if (duration > 0)
                                tracks[trackIndex].SetDuration(duration);
                        }
                        catch (...) {}
                    }
                    m_processedFiles.store(static_cast<int>(i + 1), std::memory_order_release);
                }
            }

            m_importedTracks = std::move(tracks);
        }

        m_isFinished.store(true, std::memory_order_release);
        m_isImporting.store(false, std::memory_order_release); });
    }

    //==============================================================================
    // Import (Private) - INCREMENTAL IMPORT (for new files in existing directory)
    //==============================================================================

    void DirectoryDataModel::StartIncrementalImport(const std::filesystem::path &folder,
                                                    const std::vector<std::filesystem::path> &newFiles)
    {
        // Prevent double-import
        bool expected = false;
        if (!m_isImporting.compare_exchange_strong(expected, true))
            return;

        if (m_importThread.joinable())
            m_importThread.join();

        // Reset state
        m_importedTracks.clear();

        int total = static_cast<int>(newFiles.size());
        m_totalFiles.store(total, std::memory_order_release);
        m_processedFiles.store(0, std::memory_order_release);
        m_successfulFiles.store(0, std::memory_order_release);
        m_isFinished.store(false, std::memory_order_release);

        NotifyChanged();

        m_importThread = std::thread([this, newFiles]()
                                     {
        int total = static_cast<int>(newFiles.size());
        
        if (total > 0)
        {
            std::vector<MusicTrack> tracks;
            std::vector<size_t> pendingBASS;
            tracks.reserve(total);

            // Process files - single-threaded for small batches, multi-threaded for large
            if (total <= 10)
            {
                // Small batch - single threaded (lower overhead)
                for (const auto& file : newFiles)
                {
                    MusicTrack track;
                    try
                    {
                        track = m_reader.ReadMetadataForSingleTrack(file);
                        track.SetDuration(0);
                    }
                    catch (...)
                    {
                        track.SetPath(file);
                        try { track.SetTitle(file.stem().u8string()); } 
                        catch (...) { 
                            try { track.SetTitle(file.stem().string()); } 
                            catch (...) { track.SetTitle("Unknown Track"); }
                        }
                        track.SetArtist("Unknown Artist");
                        track.SetAlbum("Unknown Album");
                        track.SetGenre("Unknown");
                        track.SetDuration(0);
                    }
                    
                    size_t index = tracks.size();
                    tracks.push_back(std::move(track));
                    pendingBASS.push_back(index);
                    
                    m_processedFiles.store(static_cast<int>(index + 1), std::memory_order_release);
                    m_successfulFiles.store(static_cast<int>(index + 1), std::memory_order_release);
                }
            }
            else
            {
                // Larger batch - multi-threaded
                unsigned int numThreads = std::max(1u, std::min(std::thread::hardware_concurrency(), 4u));
                std::vector<std::future<void>> futures;
                std::mutex tracksMutex;
                std::atomic<int> processed{0};

                size_t chunkSize = (total + numThreads - 1) / numThreads;

                for (unsigned int t = 0; t < numThreads; ++t)
                {
                    size_t start = t * chunkSize;
                    if (start >= newFiles.size()) break;
                    size_t end = std::min(start + chunkSize, newFiles.size());

                    futures.push_back(std::async(std::launch::async, 
                        [this, &newFiles, start, end, &processed, &tracksMutex, &tracks, &pendingBASS]()
                        {
                            std::vector<size_t> localPending;
                            
                            for (size_t i = start; i < end; ++i)
                            {
                                MusicTrack track;
                                try
                                {
                                    track = m_reader.ReadMetadataForSingleTrack(newFiles[i]);
                                    track.SetDuration(0);
                                }
                                catch (...)
                                {
                                    track.SetPath(newFiles[i]);
                                    try { track.SetTitle(newFiles[i].stem().u8string()); } 
                                    catch (...) { 
                                        try { track.SetTitle(newFiles[i].stem().string()); } 
                                        catch (...) { track.SetTitle("Unknown Track"); }
                                    }
                                    track.SetArtist("Unknown Artist");
                                    track.SetAlbum("Unknown Album");
                                    track.SetGenre("Unknown");
                                    track.SetDuration(0);
                                }
                                
                                {
                                    std::lock_guard<std::mutex> lock(tracksMutex);
                                    size_t trackIndex = tracks.size();
                                    tracks.push_back(std::move(track));
                                    localPending.push_back(trackIndex);
                                }

                                int count = processed.fetch_add(1, std::memory_order_relaxed) + 1;
                                m_processedFiles.store(count, std::memory_order_release);
                                m_successfulFiles.store(static_cast<int>(tracks.size()), std::memory_order_release);
                            }
                            
                            if (!localPending.empty())
                            {
                                std::lock_guard<std::mutex> lock(tracksMutex);
                                pendingBASS.insert(pendingBASS.end(), localPending.begin(), localPending.end());
                            }
                        }
                    ));
                }

                for (auto& f : futures)
                    if (f.valid()) f.get();
            }

            // PHASE 2: BASS duration (sequential to avoid threading issues)
            if (!pendingBASS.empty())
            {
                m_processedFiles.store(0, std::memory_order_release);
                
                for (size_t i = 0; i < pendingBASS.size(); ++i)
                {
                    size_t trackIndex = pendingBASS[i];
                    if (trackIndex < tracks.size())
                    {
                        try
                        {
                            unsigned int duration = m_reader.GetDurationWithBASS(tracks[trackIndex].GetPath());
                            if (duration > 0)
                                tracks[trackIndex].SetDuration(duration);
                        }
                        catch (...) {}
                    }
                    m_processedFiles.store(static_cast<int>(i + 1), std::memory_order_release);
                }
            }

            m_importedTracks = std::move(tracks);
        }

        m_isFinished.store(true, std::memory_order_release);
        m_isImporting.store(false, std::memory_order_release); });
    }

    void DirectoryDataModel::CommitImport()
    {
        if (!m_isFinished.load(std::memory_order_acquire))
            return;

        if (m_importThread.joinable())
            m_importThread.join();

        if (!m_importedTracks.empty())
        {
            // Add directory if it's not already in the library (for new imports)
            if (!m_sourceLibrary.HasDirectory(m_pendingDirectory))
                m_sourceLibrary.AddDirectory(m_pendingDirectory);

            for (auto &track : m_importedTracks)
                m_sourceLibrary.AddTrack(track);
        }

        m_importedTracks.clear();
        m_isFinished.store(false, std::memory_order_release);

        NotifyChanged();
    }

    //==============================================================================
    // Notification
    //==============================================================================

    void DirectoryDataModel::NotifyChanged()
    {
        if (m_onDataChanged)
            m_onDataChanged();
    }

} // namespace moosic