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

namespace moosic
{

//==============================================================================
// Constructor / Destructor
//==============================================================================

DirectoryDataModel::DirectoryDataModel(MusicLibrary& library, PlaylistDataModel* playlistModel)
    : m_sourceLibrary(library)
    , m_playlistModel(playlistModel)
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

const std::vector<std::filesystem::path>& DirectoryDataModel::GetDirectories() const
{
    return m_sourceLibrary.GetDirectories();
}

bool DirectoryDataModel::HasDirectory(const std::filesystem::path& path) const
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

    nfdu8char_t* outPath = nullptr;
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

void DirectoryDataModel::AddDirectory(const std::filesystem::path& folder)
{
    if (!m_sourceLibrary.HasDirectory(folder))
        StartImport(folder);
}

void DirectoryDataModel::RemoveDirectory(const std::filesystem::path& path)
{
    // Collect track IDs from this directory before removing them
    if (m_playlistModel)
    {
        std::vector<std::size_t> idsToRemove;
        for (const auto& track : m_sourceLibrary.GetTracks())
        {
            if (track.GetPath().parent_path() == path)
                idsToRemove.push_back(track.GetId());
        }
        
        // Remove these IDs from all playlists
        auto& playlists = m_playlistModel->GetAllPlaylists();
        for (auto& playlist : playlists)
        {
            playlist.trackIds.erase(
                std::remove_if(playlist.trackIds.begin(), playlist.trackIds.end(),
                    [&](std::size_t id) {
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
        auto& playlists = m_playlistModel->GetAllPlaylists();
        for (auto& playlist : playlists)
            playlist.trackIds.clear();
        
        m_playlistModel->ClearActivePlaylistData();
        m_playlistModel->NotifyDataChanged();
    }

    m_sourceLibrary.Clear();
    NotifyChanged();
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
// Import (Private) - SMART 2-PHASE APPROACH
//==============================================================================

void DirectoryDataModel::StartImport(const std::filesystem::path& folder)
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
        m_isImporting.store(false, std::memory_order_release);
    });
}


void DirectoryDataModel::CommitImport()
{
    if (!m_isFinished.load(std::memory_order_acquire)) return;

    if (m_importThread.joinable())
        m_importThread.join();

    if (!m_importedTracks.empty())
    {
        m_sourceLibrary.AddDirectory(m_pendingDirectory);
        
        for (auto& track : m_importedTracks)
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