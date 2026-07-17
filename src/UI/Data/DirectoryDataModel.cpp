//==============================================================================
// UI/Data/DirectoryDataModel.cpp
//==============================================================================

#include "DirectoryDataModel.h"
#include "../../Models/MusicTrack.h"

#include <nfd.h>
#include <future>
#include <iostream>

namespace moosic
{

//==============================================================================
// Constructor / Destructor
//==============================================================================

DirectoryDataModel::DirectoryDataModel(MusicLibrary& library)
    : m_sourceLibrary(library)
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
    int total = m_totalFiles.load();
    if (total > 0)
        return static_cast<float>(m_processedFiles.load()) / static_cast<float>(total);
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
    m_sourceLibrary.RemoveTracksFromDirectory(path);
    m_sourceLibrary.RemoveDirectory(path);
    
    NotifyChanged();
}

void DirectoryDataModel::ClearAll()
{
    m_sourceLibrary.Clear();
    NotifyChanged();
}

//==============================================================================
// Update
//==============================================================================

void DirectoryDataModel::Update()
{
    if (m_isFinished.load())
        CommitImport();
}

//==============================================================================
// Import (Private)
//==============================================================================

void DirectoryDataModel::StartImport(const std::filesystem::path& folder)
{
    if (m_isImporting.load()) return;

    if (m_importThread.joinable())
        m_importThread.join();

    // Reset state
    m_pendingDirectory = folder;
    m_importedTracks.clear();
    m_totalFiles = 0;
    m_processedFiles = 0;
    m_successfulFiles = 0;
    m_isFinished = false;
    m_isImporting = true;
    
    NotifyChanged();

    m_importThread = std::thread([this, folder]()
    {
        // Scan
        auto files = m_scanner.Scan(folder);
        int total = static_cast<int>(files.size());
        m_totalFiles = total;

        if (total > 0)
        {
            // Process in parallel
            unsigned int numThreads = std::max(1u, std::min(std::thread::hardware_concurrency(), 8u));
            
            std::vector<std::future<void>> futures;
            std::mutex tracksMutex;
            std::atomic<int> processed{0};
            std::vector<MusicTrack> tracks;
            tracks.reserve(total);

            size_t chunkSize = (total + numThreads - 1) / numThreads;

            for (unsigned int t = 0; t < numThreads; ++t)
            {
                size_t start = t * chunkSize;
                if (start >= files.size()) break;
                size_t end = std::min(start + chunkSize, files.size());

                futures.push_back(std::async(std::launch::async, 
                    [this, &files, start, end, &processed, &tracksMutex, &tracks]()
                    {
                        for (size_t i = start; i < end; ++i)
                        {
                            try
                            {
                                auto track = m_reader.ReadMetadataForSingleTrack(files[i]);
                                std::lock_guard<std::mutex> lock(tracksMutex);
                                tracks.push_back(std::move(track));
                            }
                            catch (...) {}

                            int count = processed.fetch_add(1) + 1;
                            m_processedFiles.store(count);
                            m_successfulFiles.store(static_cast<int>(tracks.size()));
                        }
                    }
                ));
            }

            for (auto& f : futures)
                if (f.valid()) f.get();

            m_importedTracks = std::move(tracks);
        }

        m_isFinished = true;
        m_isImporting = false;
    });
}

void DirectoryDataModel::CommitImport()
{
    if (!m_isFinished.load()) return;

    if (m_importThread.joinable())
        m_importThread.join();

    if (!m_importedTracks.empty())
    {
        m_sourceLibrary.AddDirectory(m_pendingDirectory);
        
        for (auto& track : m_importedTracks)
            m_sourceLibrary.AddTrack(track);
    }

    m_importedTracks.clear();
    m_isFinished = false;
    
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