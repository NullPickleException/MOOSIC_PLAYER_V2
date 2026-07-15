//==============================================================================
// MiniPlayerLayout.h
//==============================================================================
// Floating mini player window with compact controls (Key 5)
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/DirectoryWindow.h"
#include "../Windows/LibraryWindow.h"
#include "../Widgets/PlayerBar/MiniPlayerBar.h"
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"

#include <SDL.h>

namespace moosic
{

//==============================================================================
// MiniPlayerLayout
//==============================================================================

class MiniPlayerLayout : public ILayout
{
public:
    MiniPlayerLayout(MusicLibrary& library, PlaybackController& playbackController);

    void Draw(SDL_Renderer* renderer) override;

    void ApplyTheme(const Theme& theme) override
    {
        m_libraryWindow.ApplyTheme(theme.Window);
        m_libraryWindow.ApplyTrackTableTheme(theme.TrackTable);
        m_directoryWindow.ApplyTheme(theme.Window);
        m_miniPlayerBar.ApplyTheme(theme.PlayerBar);
        m_mainPlayerBar.ApplyTheme(theme.PlayerBar);
    }

    // MiniPlayer doesn't have WindowContentPanel, so return nullptr
    WindowContentPanel* GetContentPanel() override { return nullptr; }

private:
    enum class ActiveWindow { Library, Directory };
    ActiveWindow m_activeWindow = ActiveWindow::Library;

    DirectoryWindow m_directoryWindow;
    LibraryWindow   m_libraryWindow;
    MiniPlayerBar   m_miniPlayerBar;
    StandardPlayerBar m_mainPlayerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic