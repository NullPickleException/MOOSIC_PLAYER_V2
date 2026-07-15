//==============================================================================
// TheaterLayout.h
//==============================================================================
// Theater mode - large album art with minimal controls (Key 6)
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Widgets/PlayerBar/TheaterPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"

#include <SDL.h>

namespace moosic
{

//==============================================================================
// TheaterLayout
//==============================================================================

class TheaterLayout : public ILayout
{
public:
    TheaterLayout(MusicLibrary& library, PlaybackController& playbackController);

    void Draw(SDL_Renderer* renderer) override;

    void ApplyTheme(const Theme& theme) override
    {
        m_playerBar.ApplyTheme(theme.PlayerBar);
    }

    // TheaterLayout doesn't have WindowContentPanel, so return nullptr
    WindowContentPanel* GetContentPanel() override { return nullptr; }

private:
    TheaterPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic