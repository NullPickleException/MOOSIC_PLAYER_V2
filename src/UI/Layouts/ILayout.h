#pragma once


namespace moosic
{
    class ILayout
    {
    public:
        virtual ~ILayout() = default;

        virtual void Draw() = 0;


    };

}