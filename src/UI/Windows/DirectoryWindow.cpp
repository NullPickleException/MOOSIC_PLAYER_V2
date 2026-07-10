#include "DirectoryWindow.h"
#include "../../Models/MusicTrack.h"

#include <imgui.h>
#include <nfd.h>

#include <filesystem>
#include <iostream>
#include <future>
#include <mutex>

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
    // Commit finished import on UI thread
    if (m_finished)
    {
        CommitFinishedImport();
    }

    //==========================================================================
    // Header
    //==========================================================================

    ImGui::Text("Directories");
    ImGui::Separator();

    //==========================================================================
    // Action Buttons
    //==========================================================================

    bool isImporting = m_importing.load();

    if (ImGui::Button(isImporting ? "Scanning..." : "Add Folder"))
    {
        if (!isImporting)
            AddDirectory();
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear All") && !m_library.GetDirectories().empty())
    {
        if (!isImporting)
        {
            m_library.Clear();
            std::cout << "[DirectoryWindow] Library cleared.\n";
        }
    }

    //==========================================================================
    // Progress
    //==========================================================================

    if (isImporting)
    {
        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Importing music...");

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

    //==========================================================================
    // Directory List
    //==========================================================================

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

void DirectoryWindow::AddDirectory()
{
    NFD_Init();

    nfdu8char_t* outPath = nullptr;
    nfdpickfolderu8args_t args{};
    args.defaultPath = nullptr;

    nfdresult_t result = NFD_PickFolderU8_With(&outPath, &args);

    if (result == NFD_OKAY)
    {
        std::filesystem::path folder(outPath);
        NFD_FreePathU8(outPath);

        if (!m_library.HasDirectory(folder))
        {
            StartImport(folder);
        }
        else
        {
            std::cout << "[DirectoryWindow] Directory already added.\n";
        }
    }
    else if (result != NFD_CANCEL)
    {
        std::cout << "[DirectoryWindow] Error: " << NFD_GetError() << '\n';
    }

    NFD_Quit();
}

void DirectoryWindow::StartImport(const std::filesystem::path& folder)
{
    if (m_importing) return;

    if (m_importThread.joinable())
        m_importThread.join();

    m_pendingDirectory = folder;
    m_importedTracks.clear();
    m_totalFiles = 0;
    m_processedFiles = 0;
    m_successfulFiles = 0;
    m_finished = false;
    m_importing = true;

    m_importThread = std::thread([this, folder]()
    {
        try
        {
            std::cout << "[DirectoryWindow] Scanning: " << folder.string() << '\n';
            auto files = m_scanner.Scan(folder);
            int total = static_cast<int>(files.size());
            m_totalFiles = total;

            std::cout << "[DirectoryWindow] Found " << total << " files\n";

            if (total == 0)
            {
                m_finished = true;
                m_importing = false;
                return;
            }

            //==========================================================================
            // MULTI-THREADED PROCESSING - Like the previous app!
            //==========================================================================
            
            // Use hardware concurrency for max speed
            unsigned int numThreads = std::max(1u, std::min(std::thread::hardware_concurrency(), 8u));
            std::cout << "[DirectoryWindow] Using " << numThreads << " threads\n";

            std::vector<std::future<void>> futures;
            std::mutex tracksMutex;
            std::atomic<int> processedCount{0};
            std::vector<MusicTrack> tempTracks;
            tempTracks.reserve(total);

            // Process in parallel using std::async
            size_t chunkSize = (total + numThreads - 1) / numThreads;

            for (unsigned int t = 0; t < numThreads; ++t)
            {
                size_t start = t * chunkSize;
                if (start >= files.size()) break;
                size_t end = std::min(start + chunkSize, files.size());

                futures.push_back(std::async(std::launch::async, 
                    [this, &files, start, end, &processedCount, &tracksMutex, &tempTracks]()
                    {
                        for (size_t i = start; i < end; ++i)
                        {
                            const auto& file = files[i];

                            try
                            {
                                MusicTrack track = m_reader.ReadMetadataForSingleTrack(file);
                                
                                std::lock_guard<std::mutex> lock(tracksMutex);
                                tempTracks.push_back(std::move(track));
                            }
                            catch (...)
                            {
                                // Silent fail for individual files
                            }

                            // Increment processed count
                            int newCount = processedCount.fetch_add(1) + 1;
                            
                            // Update atomic values using store()
                            m_processedFiles.store(newCount);
                            m_successfulFiles.store(static_cast<int>(tempTracks.size()));
                        }
                    }
                ));
            }

            // Wait for all threads to complete
            for (auto& f : futures)
            {
                if (f.valid())
                    f.get();
            }

            // Move all tracks to main vector
            m_importedTracks = std::move(tempTracks);

            std::cout << "[DirectoryWindow] Successfully read " 
                      << m_importedTracks.size() << " out of " << total << " files\n";
        }
        catch (const std::exception& e)
        {
            std::cout << "[DirectoryWindow] Error: " << e.what() << '\n';
        }

        m_finished = true;
        m_importing = false;
    });
}

void DirectoryWindow::CommitFinishedImport()
{
    if (!m_finished) return;

    if (m_importThread.joinable())
        m_importThread.join();

    if (!m_importedTracks.empty())
    {
        m_library.AddDirectory(m_pendingDirectory);

        for (auto& track : m_importedTracks)
        {
            m_library.AddTrack(track);
        }

        std::cout << "[DirectoryWindow] Imported " 
                  << m_importedTracks.size() 
                  << " tracks from "
                  << m_pendingDirectory.filename().string() << '\n';
    }

    m_importedTracks.clear();
    m_finished = false;
}

} // namespace moosic