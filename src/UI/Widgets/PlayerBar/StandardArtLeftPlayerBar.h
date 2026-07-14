//==============================================================================
// StandardArtLeftPlayerBar.h
//==============================================================================
// Standard player bar with album art on the LEFT side
//==============================================================================

#pragma once
#include "IPlayerBar.h"

namespace moosic
{
    class StandardArtLeftPlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
    };
}