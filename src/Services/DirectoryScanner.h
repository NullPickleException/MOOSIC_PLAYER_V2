#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <atomic>
#include <functional>

namespace moosic
{

    //==============================================================================
    // Supported audio file extensions
    //==============================================================================

    namespace AudioExtensions
    {
        // Supported formats - optimized for fast lookup
        inline const std::vector<std::string> All = {
            ".mp3", ".mp2", ".mp1",
            ".flac",
            ".wav",
            ".ogg",
            ".m4a", ".mp4", ".m4b",
            ".wma",
            ".opus",
            ".aac"};

        // Fast O(1) lookup using a small set
        inline bool IsSupported(const std::string &extension)
        {
            std::string ext = extension;
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

            // Quick check for common extensions first
            if (ext == ".mp3" || ext == ".m4a" || ext == ".flac" || 
                ext == ".wav" || ext == ".ogg" || ext == ".mp4")
                return true;
            
            if (ext == ".mp2" || ext == ".mp1" || ext == ".m4b" ||
                ext == ".wma" || ext == ".opus" || ext == ".aac")
                return true;

            return false;
        }
    }

    //==============================================================================
    // Progress callback for async scanning
    //==============================================================================

    struct ScanProgress
    {
        int total = 0;
        int processed = 0;
        int found = 0;
        std::string currentPath;
    };

    using ScanProgressCallback = std::function<void(const ScanProgress&)>;

    //==============================================================================
    // Directory Scanner - FAST version with multi-threading
    //==============================================================================
    class DirectoryScanner
    {
    public:
        DirectoryScanner() = default;
        ~DirectoryScanner() = default;

        // Synchronous scan (blocking)
        std::vector<std::filesystem::path> Scan(const std::filesystem::path &directory);

        // Asynchronous scan (non-blocking) with progress
        void ScanAsync(const std::filesystem::path &directory, 
                       ScanProgressCallback progressCallback,
                       std::function<void(std::vector<std::filesystem::path>)> completionCallback);

        // Cancel async scan
        void Cancel();

    private:
        bool IsAudioFile(const std::filesystem::path &filePath) const;
        std::string GetLowercaseExtension(const std::filesystem::path &filePath) const;
        void ScanDirectoryInternal(const std::filesystem::path &directory, 
                                   std::vector<std::filesystem::path> &outFiles,
                                   std::atomic<int> &fileCount);

    private:
        std::atomic<bool> m_cancelled{false};
    };
    
} // namespace moosic