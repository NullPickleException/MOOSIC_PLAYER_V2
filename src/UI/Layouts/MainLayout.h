//==============================================================================
// MainLayout.h
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/StandardPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"

#include <SDL.h>

namespace moosic
{

class MainLayout : public ILayout
{
public:
    MainLayout(MusicLibrary& library, PlaybackController& playbackController);

    void Draw(SDL_Renderer* renderer) override;

    void ApplyTheme(const Theme& theme) override
    {
        m_contentPanel.ApplyTheme(theme);
        m_playerBar.ApplyTheme(theme.PlayerBar);
    }

    WindowContentPanel* GetContentPanel() override { return &m_contentPanel; }

private:
    WindowContentPanel m_contentPanel;
    StandardPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic