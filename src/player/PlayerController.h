#pragma once

#include <SDL3/SDL.h>

#include "../camera/Camera.h"

#include "../ecs/components/RigidBody.h"
#include "../ecs/components/Transform.h"

class PlayerController
{
public:

    void update(
        Camera& camera,
        TransformComponent& transform,
        RigidbodyComponent& rigidbody,
        bool& cursorLocked,
        SDL_Window* window
    );
};