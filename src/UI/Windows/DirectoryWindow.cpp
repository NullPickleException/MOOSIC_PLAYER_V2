#include "DirectoryWindow.h"
#include "../../Models/MusicTrack.h"

#include <imgui.h>
#include <nfd.h>

#include <iostream>
#include <future>

namespace moosic
{

//==============================================================================
// Constructor / Destructor
//==============================================================================

DirectoryWindow::DirectoryWindow(MusicLibrary& library)
    : m_library(library)
{
}

DirectoryWindow::~DirectoryWindow()
{
    if (m_importThread.joinable())
        m_importThread.join();
}

//==============================================================================
// Draw
//==============================================================================

void DirectoryWindow::Draw()
{
    // Commit finished import
    if (m_isFinished)
        CommitImport();

    ImGui::Text("Directories");
    ImGui::Separator();

    bool isImporting = m_isImporting.load();

    // Action buttons
    if (ImGui::Button(isImporting ? "Scanning..." : "Add Folder"))
    {
        if (!isImporting)
            AddDirectory();
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear All") && !m_library.GetDirectories().empty())
    {
        if (!isImporting)
            m_library.Clear();
    }

    // Progress
    if (isImporting)
    {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Importing...");

        float progress = 0.0f;
        int total = m_totalFiles.load();
        if (total > 0)
            progress = static_cast<float>(m_processedFiles.load()) / static_cast<float>(total);

        ImGui::ProgressBar(progress, ImVec2(-1.0f, 0.0f));
        ImGui::Text("%d / %d files | Added: %d", 
                    m_processedFiles.load(), 
                    total,
                    m_successfulFiles.load());
        ImGui::Separator();
    }

    // Directory list
    const auto& directories = m_library.GetDirectories();
    ImGui::Text("Added Directories (%d)", static_cast<int>(directories.size()));

    if (directories.empty())
    {
        ImGui::TextDisabled("No directories added yet.");
        return;
    }

    for (const auto& dir : directories)
    {
        const std::string text = dir.string();
        ImGui::PushID(text.c_str());

        ImGui::BulletText("%s", text.c_str());
        ImGui::SameLine();

        if (!isImporting && ImGui::SmallButton("Remove"))
        {
            m_library.RemoveTracksFromDirectory(dir);
            m_library.RemoveDirectory(dir);
        }

        ImGui::PopID();
    }
}

//==============================================================================
// Add Directory
//==============================================================================

void DirectoryWindow::AddDirectory()
{
    NFD_Init();

    nfdu8char_t* outPath = nullptr;
    nfdresult_t result = NFD_PickFolderU8(&outPath, nullptr);

    if (result == NFD_OKAY)
    {
        std::filesystem::path folder(outPath);
        NFD_FreePathU8(outPath);

        if (!m_library.HasDirectory(folder))
            StartImport(folder);
    }

    NFD_Quit();
}

//==============================================================================
// Import
//==============================================================================

void DirectoryWindow::StartImport(const std::filesystem::path& folder)
{
    if (m_isImporting) return;

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

void DirectoryWindow::CommitImport()
{
    if (!m_isFinished) return;

    if (m_importThread.joinable())
        m_importThread.join();

    if (!m_importedTracks.empty())
    {
        m_library.AddDirectory(m_pendingDirectory);
        
        for (auto& track : m_importedTracks)
            m_library.AddTrack(track);
    }

    m_importedTracks.clear();
    m_isFinished = false;
}

} // namespace moosic