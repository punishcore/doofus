#pragma once

#include <SDL3/SDL.h>

#include "../camera/Camera.h"

#include "../ecs/components/RigidBody.h"
#include "../ecs/components/Transform.h"

class Time;
class World;

class PlayerController
{
public:

    void update(
        Camera& camera,
        TransformComponent& transform,
        RigidbodyComponent& rigidbody,
        bool& cursorLocked,
        SDL_Window* window,
        Time& time,
        World& world
    );

private:

    void raycast(
        Camera& camera,
        World& world,
        bool place
    );

private:

    float reach = 6.0f;

    int breakCooldown = 5;
    int placeCooldown = 5;

    int lastBreakTick = 0;
    int lastPlaceTick = 0;
};