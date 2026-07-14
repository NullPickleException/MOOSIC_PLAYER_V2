#pragma once

#include "../../Models/MusicLibrary.h"
#include "../../Services/DirectoryScanner.h"
#include "../../Services/Metadata/MetadataReader.h"
#include "IWindow.h"

#include <atomic>
#include <thread>
#include <vector>
#include <filesystem>

namespace moosic
{

// Forward declare Theme
struct Theme;

class DirectoryWindow : public IWindow
{
public:
    DirectoryWindow(MusicLibrary& library);
    ~DirectoryWindow();

    void Draw() override;
    void ApplyTheme(const Theme& theme) override {}  // Simple override

private:
    void AddDirectory();
    void StartImport(const std::filesystem::path& folder);
    void CommitImport();

private:
    MusicLibrary& m_library;
    DirectoryScanner m_scanner;
    MetadataReader m_reader;

    std::thread m_importThread;
    std::atomic<bool> m_isImporting{false};
    std::atomic<bool> m_isFinished{false};
    std::atomic<int> m_totalFiles{0};
    std::atomic<int> m_processedFiles{0};
    std::atomic<int> m_successfulFiles{0};
    
    std::filesystem::path m_pendingDirectory;
    std::vector<MusicTrack> m_importedTracks;
};

} // namespace moosic