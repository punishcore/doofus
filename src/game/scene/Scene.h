#pragma once

#include "../../camera/Camera.h"

#include "../../world/World.h"

#include "../../renderer/Sky.h"
#include "../../renderer/opengl/Shader.h"
#include "../../renderer/opengl/TextureArray.h"
#include "../../renderer/ui/Crosshair.h"

#include "../../ecs/components/RigidBody.h"
#include "../../ecs/components/Transform.h"
#include "../../player/PlayerController.h"
#include "../../renderer/model/Model.h"

#include "../../core/Time.h"

#include "../../platform/sdl/SDLWindow.h"

#include <memory>

class Scene {
public:
  void init();

  void update(float dt, SDL_Window *window);

  void render();

private:
  Camera camera;

  World world;

  Time time;

  Sky sky;

  Crosshair crosshair;

  std::unique_ptr<Shader> shader;

  std::unique_ptr<TextureArray> atlas;

  std::unique_ptr<Model> playerModel;

  PlayerController playerController;

  TransformComponent playerTransform;

  RigidbodyComponent playerRigidbody;

  bool cursorLocked = true;
};