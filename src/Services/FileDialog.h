//==============================================================================
// Services/FileDialog.h
//==============================================================================

#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace moosic
{
    // Single audio file selection
    std::optional<std::filesystem::path> OpenAudioFileDialog();
    
    // Folder selection
    std::optional<std::filesystem::path> OpenFolderDialog();
    
    // Multiple audio file selection
    std::vector<std::filesystem::path> OpenMultipleAudioFilesDialog();
    
    // Save file dialog (for playlists, etc.)
    std::optional<std::filesystem::path> SaveFileDialog(const std::string& defaultExtension = ".m3u");
}