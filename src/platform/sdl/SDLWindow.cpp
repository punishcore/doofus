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
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

    SDL_SetWindowRelativeMouseMode(window, true);
    SDL_HideCursor();

    return true;
}

void SDLWindow::pollEvents()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            closed = true;

        if (e.type == SDL_EVENT_KEY_DOWN)
        {
            if (e.key.key == SDLK_ESCAPE)
            {
                bool relative =
                    SDL_GetWindowRelativeMouseMode(window);

                if (relative)
                {
                    SDL_SetWindowRelativeMouseMode(
                        window,
                        false
                    );

                    SDL_ShowCursor();
                }
                else
                {
                    SDL_SetWindowRelativeMouseMode(
                        window,
                        true
                    );

                    SDL_HideCursor();
                }
            }
        }

        if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        {
            bool relative =
                SDL_GetWindowRelativeMouseMode(window);

            if (!relative)
            {
                SDL_SetWindowRelativeMouseMode(
                    window,
                    true
                );

                SDL_HideCursor();
            }
        }
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