//==============================================================================
// UI/Widgets/EditTrackDialog.h
//==============================================================================

#pragma once

#include <imgui.h>
#include <string>
#include <functional>
#include "../../Models/MusicTrack.h"

namespace moosic
{

struct EditTrackDialogTheme
{
    ImVec4 BrandText       = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);  // Orange
    ImVec4 TextPrimary     = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);  // White
    ImVec4 TextDisabled    = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);  // Gray
    ImVec4 FrameBg         = ImVec4(0.15f, 0.15f, 0.15f, 1.0f); // Dark gray
    ImVec4 ButtonNormal    = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
    ImVec4 ButtonHovered   = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
    ImVec4 ButtonActive    = ImVec4(0.45f, 0.45f, 0.45f, 1.0f);
    float ButtonRounding   = 4.0f;
};

class EditTrackDialog
{
public:
    EditTrackDialog() = default;

    //--------------------------------------------------------------------------
    // Configuration
    //--------------------------------------------------------------------------

    void SetTheme(const EditTrackDialogTheme& theme) { m_theme = theme; }
    
    using SaveCallback = std::function<void(const MusicTrack* track, 
                                            const std::string& title,
                                            const std::string& artist,
                                            const std::string& album)>;
    void SetSaveCallback(SaveCallback callback) { m_onSave = std::move(callback); }

    //--------------------------------------------------------------------------
    // Open/Close
    //--------------------------------------------------------------------------

    void Open(const MusicTrack* track);
    void Close();
    bool IsOpen() const { return m_isOpen; }

    //--------------------------------------------------------------------------
    // Draw
    //--------------------------------------------------------------------------

    void Draw();

private:
    EditTrackDialogTheme m_theme;
    
    bool m_isOpen = false;
    bool m_shouldOpen = false;
    const MusicTrack* m_editingTrack = nullptr;
    
    char m_titleBuffer[256] = "";
    char m_artistBuffer[256] = "";
    char m_albumBuffer[256] = "";
    
    SaveCallback m_onSave;
};

} // namespace moosic