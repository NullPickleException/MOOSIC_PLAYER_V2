//==============================================================================
// CompactLayout.h
//==============================================================================
// Compact layout with reduced player bar height
//==============================================================================

#pragma once

#include "../../Models/MusicLibrary.h"
#include "../Windows/WindowContentPanel.h"
#include "../Widgets/PlayerBar/CompactPlayerBar.h"
#include "../../Services/PlaybackController.h"
#include "../Theme/Theme.h"
#include "../Layouts/ILayout.h"

#include <SDL.h>

namespace moosic
{

class CompactLayout : public ILayout
{
public:
    CompactLayout(MusicLibrary& library, PlaybackController& playbackController);

    void Draw(SDL_Renderer* renderer) override;

    void ApplyTheme(const Theme& theme) override
    {
        m_contentPanel.ApplyTheme(theme);
        m_playerBar.ApplyTheme(theme.PlayerBar);
    }

    WindowContentPanel* GetContentPanel() override { return &m_contentPanel; }

private:
    WindowContentPanel m_contentPanel;
    CompactPlayerBar m_playerBar;
    PlaybackController& m_playbackController;
};

} // namespace moosic