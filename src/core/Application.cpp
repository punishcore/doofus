#include "Application.h"

#include "../platform/WindowFactory.h"
#include "../platform/sdl/SDLWindow.h"
#include "../platform/input/Input.h"

#include <SDL3/SDL.h>

#include <glad/gl.h>

#include <iostream>

bool Application::init()
{
    window = CreateWindow(
        PlatformType::SDL
    );

    if (!window->init(
        1280,
        720,
        "doofus"
    ))
        return false;

    if (!gladLoadGL(
        (GLADloadfunc)
        SDL_GL_GetProcAddress
    ))
    {
        std::cout
            << "GLAD FAILED\n";

        return false;
    }

    glViewport(
        0,
        0,
        1280,
        720
    );

    glEnable(GL_DEPTH_TEST);

    SDLWindow* sdl =
        static_cast<SDLWindow*>(
            window.get()
        );

    SDL_SetWindowRelativeMouseMode(
        sdl->getWindow(),
        true
    );

    game.init();

    return true;
}

void Application::run()
{
    SDLWindow* sdl =
        static_cast<SDLWindow*>(
            window.get()
        );

    Uint64 last =
        SDL_GetPerformanceCounter();

    while (!window->shouldClose())
{
    Input::beginFrame();

    window->pollEvents();

    Uint64 now =
        SDL_GetPerformanceCounter();

    float dt =
        (float)(now - last)
        / SDL_GetPerformanceFrequency();

    last = now;

    game.update(
        dt,
        sdl->getWindow()
    );

    game.render();

    window->swapBuffers();
}
}

void Application::shutdown()
{
    window.reset();
}