//==============================================================================
// ILayout.h
//==============================================================================
// Interface for all layouts
//==============================================================================

#pragma once

#include "../Theme/Theme.h"
#include <SDL.h>

namespace moosic
{

// Forward declare
class WindowContentPanel;

//==============================================================================
// ILayout
//==============================================================================

class ILayout
{
public:
    virtual ~ILayout() = default;

    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void ApplyTheme(const Theme& theme) = 0;
    
    // Allow layouts to expose their content panel
    virtual WindowContentPanel* GetContentPanel() { return nullptr; }
};

} // namespace moosic