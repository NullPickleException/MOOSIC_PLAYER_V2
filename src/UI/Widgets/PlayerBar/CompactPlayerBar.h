//==============================================================================
// CompactPlayerBar.h
//==============================================================================
// Single-row player with NO album art - just song info + controls
//==============================================================================

#pragma once
#include "IPlayerBar.h"

namespace moosic
{
    class CompactPlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
    };
}