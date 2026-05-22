#include "Input.h"

#include <cstdlib>

bool Input::w = false;
bool Input::a = false;
bool Input::s = false;
bool Input::d = false;

bool Input::space = false;

bool Input::escape = false;

bool Input::escapePressed = false;

float Input::mouseX = 0.0f;
float Input::mouseY = 0.0f;

void Input::beginFrame()
{
    escapePressed = false;

    mouseX = 0.0f;
    mouseY = 0.0f;
}

void Input::handleEvent(
    SDL_Event& e
)
{
    if (e.type == SDL_EVENT_QUIT)
    {
        exit(0);
    }

    if (
        e.type == SDL_EVENT_KEY_DOWN
        || e.type == SDL_EVENT_KEY_UP
    )
    {
        bool pressed =
            (
                e.type
                == SDL_EVENT_KEY_DOWN
            );

        switch (e.key.key)
        {
            case SDLK_W:
                w = pressed;
                break;

            case SDLK_A:
                a = pressed;
                break;

            case SDLK_S:
                s = pressed;
                break;

            case SDLK_D:
                d = pressed;
                break;

            case SDLK_SPACE:
                space = pressed;
                break;

            case SDLK_ESCAPE:

                escape = pressed;

                if (pressed)
                    escapePressed = true;

                break;
        }
    }

    if (e.type == SDL_EVENT_MOUSE_MOTION)
    {
        mouseX = e.motion.xrel;

        mouseY = e.motion.yrel;
    }
}