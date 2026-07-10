#include "UI.h"

namespace moosic
{

UI::UI(MusicLibrary& library, PlaybackController& playbackController)
    : m_mainLayout(library, playbackController)  // Pass to main layout
{
}

void UI::Draw()
{
    m_mainLayout.Draw();
}

}