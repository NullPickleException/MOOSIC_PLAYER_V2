#pragma once

namespace moosic
{
    class IWindow
    {
    public:
        virtual ~IWindow() = default;

        virtual void Draw() = 0;

    protected:
        bool m_open = true;
    };
}