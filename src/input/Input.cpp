#include "Input.h"
#include <SDL3/SDL.h>

bool Input::w = false;
bool Input::a = false;
bool Input::s = false;
bool Input::d = false;

void Input::update()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            exit(0);

        if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP)
        {
            bool pressed = (e.type == SDL_EVENT_KEY_DOWN);

            switch (e.key.keysym.sym)
            {
                case SDLK_w: w = pressed; break;
                case SDLK_a: a = pressed; break;
                case SDLK_s: s = pressed; break;
                case SDLK_d: d = pressed; break;
            }
        }
    }
}