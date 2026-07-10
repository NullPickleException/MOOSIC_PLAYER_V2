#define SDL_MAIN_HANDLED
#include <SDL.h>


#include "Core/Application.h"

int main(int argc, char* argv[])
{
    moosic::Application app;
    return app.Run();
}