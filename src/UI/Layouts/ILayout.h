//==============================================================================
// ILayout.h
//==============================================================================

#pragma once
#include "../Theme/Theme.h"
#include <SDL.h>

namespace moosic
{

class ILayout
{
public:
    virtual ~ILayout() = default;
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void ApplyTheme(const Theme& theme) = 0; 
};

} // namespace moosic