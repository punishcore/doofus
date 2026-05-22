#pragma once

#include "../../camera/Camera.h"

#include "../../renderer/world/World.h"

#include "../../renderer/Shader.h"
#include "../../renderer/Sky.h"
#include "../../renderer/Texture.h"

#include "../../player/PlayerController.h"

#include "../../ecs/components/RigidBody.h"
#include "../../ecs/components/Transform.h"

#include "../../core/Time.h"

#include "../../platform/sdl/SDLWindow.h"

#include <memory>

class Scene
{
public:
    void init();

    void update(
        float dt,
        SDL_Window* window
    );

    void render();

private:
    Camera camera;

    World world;

    Time time;

    Sky sky;

    std::unique_ptr<Shader> shader;

    std::unique_ptr<Texture> atlas;

    PlayerController playerController;

    TransformComponent playerTransform;

    RigidbodyComponent playerRigidbody;

    bool cursorLocked = true;
};