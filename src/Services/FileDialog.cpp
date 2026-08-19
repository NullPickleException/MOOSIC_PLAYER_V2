//==============================================================================
// Services/FileDialog.cpp
//==============================================================================

#include "FileDialog.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "shell32.lib")
#else
#include <array>
#include <cstdio>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#endif

namespace moosic
{

#ifdef _WIN32

std::optional<std::filesystem::path> OpenAudioFileDialog()
{
    char file[MAX_PATH * 2] = {}; // Double buffer for safety
    OPENFILENAMEA ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr; // Can be set to main window HWND if needed
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.lpstrFilter =
        "All Supported Audio\0*.mp3;*.flac;*.wav;*.ogg;*.m4a;*.aac;*.wma;*.opus;*.mp2;*.mp1;*.m4b\0"
        "MP3 Files (*.mp3)\0*.mp3\0"
        "FLAC Files (*.flac)\0*.flac\0"
        "WAV Files (*.wav)\0*.wav\0"
        "OGG Files (*.ogg)\0*.ogg\0"
        "M4A Files (*.m4a)\0*.m4a\0"
        "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_HIDEREADONLY;
    ofn.lpstrTitle = "Open Audio File";

    if (!GetOpenFileNameA(&ofn))
    {
        DWORD error = CommDlgExtendedError();
        if (error != 0)
        {
            // Log error but don't show message box
            fprintf(stderr, "[FileDialog] Error opening file dialog: %lu\n", error);
        }
        return std::nullopt;
    }

    return std::filesystem::path(file);
}

std::vector<std::filesystem::path> OpenMultipleAudioFilesDialog()
{
    char file[MAX_PATH * 10] = {}; // Large buffer for multiple files
    OPENFILENAMEA ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.lpstrFilter =
        "All Supported Audio\0*.mp3;*.flac;*.wav;*.ogg;*.m4a;*.aac;*.wma;*.opus\0"
        "All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | 
                OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT | OFN_EXPLORER;
    ofn.lpstrTitle = "Open Audio Files";

    if (!GetOpenFileNameA(&ofn))
        return {};

    std::vector<std::filesystem::path> files;
    
    // First part is directory, subsequent parts are filenames
    std::string directory(file);
    size_t dirLen = strlen(file);
    
    if (dirLen < ofn.nFileOffset)
    {
        // Only one file selected
        files.push_back(std::filesystem::path(file));
    }
    else
    {
        // Multiple files selected
        std::string dir = directory.substr(0, ofn.nFileOffset);
        const char* p = file + ofn.nFileOffset;
        
        while (*p)
        {
            std::string filename(p);
            files.push_back(std::filesystem::path(dir) / filename);
            p += filename.length() + 1;
        }
    }
    
    return files;
}

std::optional<std::filesystem::path> OpenFolderDialog()
{
    BROWSEINFOA bi{};
    bi.hwndOwner = nullptr;
    bi.lpszTitle = "Select Music Folder";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;

    LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);
    if (!pidl)
        return std::nullopt;

    char folder[MAX_PATH] = {};
    const BOOL ok = SHGetPathFromIDListA(pidl, folder);
    CoTaskMemFree(pidl);

    if (!ok || folder[0] == '\0')
        return std::nullopt;

    return std::filesystem::path(folder);
}

std::optional<std::filesystem::path> SaveFileDialog(const std::string& defaultExtension)
{
    char file[MAX_PATH] = {};
    OPENFILENAMEA ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = file;
    ofn.nMaxFile = sizeof(file);
    ofn.lpstrFilter = "Playlist Files\0*.m3u;*.m3u8\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrDefExt = defaultExtension.c_str();
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_HIDEREADONLY;
    ofn.lpstrTitle = "Save Playlist As";

    if (!GetSaveFileNameA(&ofn))
        return std::nullopt;

    return std::filesystem::path(file);
}

#else // Non-Windows (Linux/macOS)

static std::optional<std::filesystem::path> RunZenity(const char* cmd)
{
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        // Fallback to basic terminal input
        fprintf(stderr, "[FileDialog] Zenity not available. Please install zenity.\n");
        return std::nullopt;
    }

    std::array<char, 4096> buf{};
    std::string result;
    while (fgets(buf.data(), static_cast<int>(buf.size()), pipe.get()))
        result += buf.data();

    // Remove trailing whitespace
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r'))
        result.pop_back();

    if (result.empty())
        return std::nullopt;

    return std::filesystem::path(result);
}

// Helper function to parse zenity's multiple file output (newline-separated)
static std::vector<std::filesystem::path> ParseMultipleFiles(const std::string& output)
{
    std::vector<std::filesystem::path> files;
    std::istringstream stream(output);
    std::string line;
    
    while (std::getline(stream, line))
    {
        if (!line.empty())
            files.push_back(std::filesystem::path(line));
    }
    
    return files;
}

std::optional<std::filesystem::path> OpenAudioFileDialog()
{
    return RunZenity(
        "zenity --file-selection "
        "--title=\"Open Audio File\" "
        "--file-filter=\"Audio Files | *.mp3 *.flac *.wav *.ogg *.m4a *.aac *.opus *.wma\" "
        "--file-filter=\"All files | *\" 2>/dev/null");
}

std::vector<std::filesystem::path> OpenMultipleAudioFilesDialog()
{
    auto result = RunZenity(
        "zenity --file-selection --multiple "
        "--title=\"Open Audio Files\" "
        "--file-filter=\"Audio Files | *.mp3 *.flac *.wav *.ogg *.m4a *.aac *.opus *.wma\" "
        "--file-filter=\"All files | *\" "
        "--separator='\n' 2>/dev/null");
    
    if (!result)
        return {};
    
    // For multiple files, zenity outputs them separated by newlines
    // If we got a single path, check if it contains newlines
    std::string pathStr = result->string();
    
    if (pathStr.find('\n') != std::string::npos)
    {
        // Multiple files selected
        return ParseMultipleFiles(pathStr);
    }
    else
    {
        // Single file selected
        return { *result };
    }
}

std::optional<std::filesystem::path> OpenFolderDialog()
{
    return RunZenity(
        "zenity --file-selection --directory "
        "--title=\"Select Music Folder\" 2>/dev/null");
}

std::optional<std::filesystem::path> SaveFileDialog(const std::string& defaultExtension)
{
    return RunZenity(
        "zenity --file-selection --save "
        "--title=\"Save File\" "
        "--confirm-overwrite 2>/dev/null");
}

#endif

} // namespace moosic