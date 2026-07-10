#include "UI.h"

namespace moosic
{

UI::UI(MusicLibrary& library, PlaybackController& playbackController)
    : m_mainLayout(library, playbackController)
{
}

void UI::Draw(SDL_Renderer* renderer)
{
    m_mainLayout.Draw(renderer);  
}

}