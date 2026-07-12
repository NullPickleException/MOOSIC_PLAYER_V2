#include "DirectoryScanner.h"
#include "../Models/MusicTrack.h"
#include "../Services/Metadata/MetadataReader.h"

#include <algorithm>
#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>

// Windows-specific optimizations
#ifdef _WIN32
#include <windows.h>
#include <fileapi.h>
#undef CreateDirectory  // Undefine windows macro
#endif

namespace moosic
{

//==============================================================================
// Helper: Fast directory iteration using Windows API (much faster than std::filesystem)
//==============================================================================

#ifdef _WIN32
static void ScanDirectoryWindows(const std::wstring& path, 
                                 std::vector<std::filesystem::path>& outFiles,
                                 std::atomic<int>& fileCount,
                                 std::atomic<bool>& cancelled)
{
    std::wstring searchPath = path + L"\\*";
    
    WIN32_FIND_DATAW findData;
    HANDLE hFind = FindFirstFileW(searchPath.c_str(), &findData);
    
    if (hFind == INVALID_HANDLE_VALUE)
        return;
    
    do
    {
        if (cancelled.load())
            break;
            
        // Skip . and ..
        if (wcscmp(findData.cFileName, L".") == 0 || 
            wcscmp(findData.cFileName, L"..") == 0)
            continue;
        
        std::wstring fullPath = path + L"\\" + findData.cFileName;
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // Recursively scan subdirectories
            ScanDirectoryWindows(fullPath, outFiles, fileCount, cancelled);
        }
        else
        {
            // Check if it's an audio file
            std::filesystem::path p(fullPath);
            std::string ext = p.extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            
            if (AudioExtensions::IsSupported(ext))
            {
                outFiles.push_back(p);
                fileCount++;
            }
        }
    }
    while (FindNextFileW(hFind, &findData) != 0);
    
    FindClose(hFind);
}
#endif

//==============================================================================
// Scan - Synchronous with optimizations
//==============================================================================

std::vector<std::filesystem::path>
DirectoryScanner::Scan(const std::filesystem::path& directory)
{
    std::vector<std::filesystem::path> audioFiles;
    std::atomic<int> fileCount{0};
    
    //--------------------------------------------------------------------------
    // Validate directory
    //--------------------------------------------------------------------------
    
    if (!std::filesystem::exists(directory))
    {
        std::cout << "[DirectoryScanner] Directory does not exist: "
                  << directory.string() << '\n';
        return audioFiles;
    }
    
    if (!std::filesystem::is_directory(directory))
    {
        std::cout << "[DirectoryScanner] Path is not a directory: "
                  << directory.string() << '\n';
        return audioFiles;
    }
    
    //--------------------------------------------------------------------------
    // Use Windows API for faster scanning (10-20x faster on Windows)
    //--------------------------------------------------------------------------
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
#ifdef _WIN32
    std::wstring wPath = directory.wstring();
    ScanDirectoryWindows(wPath, audioFiles, fileCount, m_cancelled);
#else
    // Fallback to std::filesystem on other platforms
    try
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(
            directory, std::filesystem::directory_options::skip_permission_denied))
        {
            if (m_cancelled.load())
                break;
                
            if (!entry.is_regular_file())
                continue;
                
            const auto& path = entry.path();
            if (IsAudioFile(path))
            {
                audioFiles.push_back(path);
                fileCount++;
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "[DirectoryScanner] Error: " << e.what() << '\n';
    }
#endif
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    
    std::cout << "[DirectoryScanner] Found " << audioFiles.size() 
              << " audio files in " << duration.count() << "ms\n";
    
    return audioFiles;
}

//==============================================================================
// ScanAsync - Non-blocking with progress
//==============================================================================

void DirectoryScanner::ScanAsync(const std::filesystem::path& directory,
                                 ScanProgressCallback progressCallback,
                                 std::function<void(std::vector<std::filesystem::path>)> completionCallback)
{
    m_cancelled = false;
    
    std::thread([this, directory, progressCallback, completionCallback]() {
        std::vector<std::filesystem::path> files;
        std::atomic<int> fileCount{0};
        ScanProgress progress;
        
#ifdef _WIN32
        std::wstring wPath = directory.wstring();
        
        // First pass: count files (optional, for progress)
        // Or we can just update progress as we go
        
        auto startTime = std::chrono::high_resolution_clock::now();
        
        ScanDirectoryWindows(wPath, files, fileCount, m_cancelled);
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        
        std::cout << "[DirectoryScanner] Async scan found " << files.size() 
                  << " files in " << duration.count() << "ms\n";
#else
        // Fallback
        try
        {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(
                directory, std::filesystem::directory_options::skip_permission_denied))
            {
                if (m_cancelled.load())
                    break;
                    
                if (!entry.is_regular_file())
                    continue;
                    
                const auto& path = entry.path();
                if (IsAudioFile(path))
                {
                    files.push_back(path);
                    fileCount++;
                    
                    // Update progress
                    progress.found = fileCount.load();
                    progress.currentPath = path.filename().string();
                    if (progressCallback)
                        progressCallback(progress);
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "[DirectoryScanner] Error: " << e.what() << '\n';
        }
#endif
        
        if (completionCallback)
            completionCallback(files);
        
    }).detach();
}

void DirectoryScanner::Cancel()
{
    m_cancelled = true;
}

//==============================================================================
// IsAudioFile
//==============================================================================

bool DirectoryScanner::IsAudioFile(const std::filesystem::path& filePath) const
{
    std::string ext = GetLowercaseExtension(filePath);
    return AudioExtensions::IsSupported(ext);
}

//==============================================================================
// GetLowercaseExtension
//==============================================================================

std::string DirectoryScanner::GetLowercaseExtension(
    const std::filesystem::path& filePath) const
{
    std::string ext = filePath.extension().string();
    std::transform(
        ext.begin(),
        ext.end(),
        ext.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return ext;
}

} // namespace moosic