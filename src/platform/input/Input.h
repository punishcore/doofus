#pragma once

#include <SDL3/SDL.h>

class Input
{
public:
    static bool w;
    static bool a;
    static bool s;
    static bool d;

    static bool space;

    static bool escape;

    static bool escapePressed;

    static float mouseX;
    static float mouseY;

    static void beginFrame();

    static void handleEvent(
        SDL_Event& e
    );
};