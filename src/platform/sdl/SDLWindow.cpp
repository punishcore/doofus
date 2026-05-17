#include "SDLWindow.h"
#include <iostream>

SDLWindow::SDLWindow() {}

SDLWindow::~SDLWindow()
{
    if (glContext)
        SDL_GL_DestroyContext(glContext);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}

bool SDLWindow::init(int width, int height, const char* title)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL init failed\n";
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );

    window = SDL_CreateWindow(
        title,
        width,
        height,
        SDL_WINDOW_OPENGL
    );

    if (!window)
    {
        std::cout << "Window failed\n";
        return false;
    }

    glContext = SDL_GL_CreateContext(window);

    if (!glContext)
    {
        std::cout << "GL Context failed\n";
        return false;
    }

    SDL_GL_MakeCurrent(window, glContext);

    return true;
}

void SDLWindow::pollEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            closed = true;
    }
}

void SDLWindow::swapBuffers()
{
    SDL_GL_SwapWindow(window);
}

bool SDLWindow::shouldClose()
{
    return closed;
}

SDL_Window* SDLWindow::getWindow()
{
    return window;
}