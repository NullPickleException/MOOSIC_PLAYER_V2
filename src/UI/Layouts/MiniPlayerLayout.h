//==============================================================================
// MiniPlayerLayout.h
//==============================================================================
// Floating mini player window (Key 5)
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/DirectoryWindow.h"
#include "../Windows/LibraryWindow.h"
#include "../Widgets/PlayerBar/MiniPlayerBar.h"
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include <SDL.h>

namespace moosic
{

class MiniPlayerLayout
{
public:
    MiniPlayerLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw(SDL_Renderer* renderer);

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