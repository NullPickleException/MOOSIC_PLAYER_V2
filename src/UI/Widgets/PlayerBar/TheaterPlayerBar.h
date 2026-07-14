//==============================================================================
// TheaterPlayerBar.h
//==============================================================================
// Theater mode player with large centered album art
//==============================================================================

#pragma once
#include "IPlayerBar.h"

namespace moosic
{
    class TheaterPlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
    };
}