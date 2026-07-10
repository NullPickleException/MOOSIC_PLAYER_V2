#pragma once

#include "../../Models/MusicLibrary.h"
#include "../../Services/DirectoryScanner.h"
#include "../../Services/MetadataReader.h"
#include "IWindow.h"

#include <atomic>
#include <thread>
#include <vector>
#include <filesystem>
#include <future>

namespace moosic
{

class DirectoryWindow : public IWindow
{
public:
    DirectoryWindow(MusicLibrary& library);
    ~DirectoryWindow();

    void Draw() override;

private:
    void AddDirectory();
    void StartImport(const std::filesystem::path& folder);
    void CommitFinishedImport();

private:
    MusicLibrary& m_library;
    DirectoryScanner m_scanner;
    MetadataReader m_reader;

    // Worker Thread
    std::thread m_importThread;
    std::atomic<bool> m_importing{false};
    std::atomic<bool> m_finished{false};
    std::atomic<int> m_totalFiles{0};
    std::atomic<int> m_processedFiles{0};
    std::atomic<int> m_successfulFiles{0};

    // Temporary results
    std::filesystem::path m_pendingDirectory;
    std::vector<MusicTrack> m_importedTracks;
    std::mutex m_tracksMutex;
};

} // namespace moosic