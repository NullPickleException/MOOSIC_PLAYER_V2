//==============================================================================
// MiniPlayerBar.h
//==============================================================================
// Mini floating player bar
//==============================================================================

#pragma once
#include "IPlayerBar.h"

namespace moosic
{
    class MiniPlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
        bool IsOpen() const { return m_open; }
        void Open() { m_open = true; }
        void Close() { m_open = false; }

    private:
        bool m_open = true;
    };
}