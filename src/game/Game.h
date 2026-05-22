#pragma once

#include "scene/Scene.h"

#include "../platform/sdl/SDLWindow.h"

class Game
{
public:
    void init();

    void update(
        float dt,
        SDL_Window* window
    );

    void render();

private:
    Scene scene;
};