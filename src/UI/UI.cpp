//==============================================================================
// UI.cpp
//==============================================================================

#include "UI.h"

namespace moosic
{

UI::UI(MusicLibrary& library, PlaybackController& playbackController)
    : m_library(library)
    , m_playbackController(playbackController)
    , m_standardLayout(library, playbackController)
    , m_sidebarLayout(library, playbackController)
    , m_compactLayout(library, playbackController)
    , m_miniPlayerLayout(library, playbackController)
    , m_theaterLayout(library, playbackController)
    , m_standardArtLeftLayout(library, playbackController)
{
}

void UI::HandleLayoutSwitch(InputManager& input)
{
    if (input.IsKeyPressed(SDLK_1)) m_layoutMode = LayoutMode::Standard;
    if (input.IsKeyPressed(SDLK_2)) m_layoutMode = LayoutMode::Compact;
    if (input.IsKeyPressed(SDLK_3)) m_layoutMode = LayoutMode::StandardArtLeft;
    if (input.IsKeyPressed(SDLK_4)) m_layoutMode = LayoutMode::SidebarLeft;
    if (input.IsKeyPressed(SDLK_5)) m_layoutMode = LayoutMode::MiniPlayer;
    if (input.IsKeyPressed(SDLK_6)) m_layoutMode = LayoutMode::Theater;
}

void UI::DrawCurrentLayout(SDL_Renderer* renderer)
{
    switch (m_layoutMode)
    {
    case LayoutMode::Standard:       m_standardLayout.Draw(renderer);       break;
    case LayoutMode::SidebarLeft:    m_sidebarLayout.Draw(renderer);        break;
    case LayoutMode::Compact:        m_compactLayout.Draw(renderer);        break;
    case LayoutMode::MiniPlayer:     m_miniPlayerLayout.Draw(renderer);     break;
    case LayoutMode::Theater:        m_theaterLayout.Draw(renderer);        break;
    case LayoutMode::StandardArtLeft: m_standardArtLeftLayout.Draw(renderer); break;
    }
}

void UI::Draw(SDL_Renderer* renderer, InputManager& input)
{
    HandleLayoutSwitch(input);
    DrawCurrentLayout(renderer);
}

} // namespace moosic