//==============================================================================
// SidePlayerBar.h
//==============================================================================
// Vertical sidebar player bar for left/right sidebar layouts
//==============================================================================

#pragma once
#include "IPlayerBar.h"

namespace moosic
{
    class SidePlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
    };
}