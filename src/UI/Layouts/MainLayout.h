#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/DirectoryWindow.h"
#include "../Windows/LibraryWindow.h"
#include "../Widgets/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"

namespace moosic
{

class MainLayout
{
public:
    MainLayout(MusicLibrary& library, PlaybackController& playbackController);
    void Draw();

private:
    enum class ActiveWindow
    {
        Library,
        Directory
    };

    ActiveWindow m_activeWindow = ActiveWindow::Library;

    DirectoryWindow m_directoryWindow;
    LibraryWindow   m_libraryWindow;
    StandardPlayerBar m_playerBar;
    PlaybackController& m_playbackController;  
};

}