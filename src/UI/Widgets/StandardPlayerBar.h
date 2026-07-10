#pragma once

#include "IPlayerBar.h"

namespace moosic
{
    class StandardPlayerBar : public IPlayerBar
    {
    public:
        void Draw() override;
    };
}