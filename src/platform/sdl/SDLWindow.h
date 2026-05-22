#pragma once

#include "../IWindow.h"

#include <SDL3/SDL.h>

class SDLWindow : public IWindow
{
public:
    SDLWindow();

    ~SDLWindow();

    bool init(
        int width,
        int height,
        const char* title
    ) override;

    void pollEvents() override;

    void swapBuffers() override;

    bool shouldClose() override;

    int getWidth() override;

    int getHeight() override;

    SDL_Window* getWindow();

private:
    SDL_Window* window = nullptr;

    SDL_GLContext glContext = nullptr;

    bool closed = false;
};