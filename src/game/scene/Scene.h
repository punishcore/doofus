#pragma once

#include "../../camera/Camera.h"
#include "../../core/Time.h"
#include "../../ecs/components/RigidBody.h"
#include "../../ecs/components/Transform.h"
#include "../../platform/sdl/SDLWindow.h"
#include "../../player/PlayerController.h"
#include "../../renderer/Frustum.h"
#include "../../renderer/Sky.h"
#include "../../renderer/model/Model.h"
#include "../../renderer/opengl/Shader.h"
#include "../../renderer/opengl/TextureArray.h"
#include "../../renderer/ui/Crosshair.h"
#include "../../renderer/ui/DebugOverlay.h"
#include "../../world/World.h"

#include <memory>

class Scene {
public:
  void init();
  void update(float dt, SDL_Window *window);
  void render();
  bool isLoading = true;

private:
  Camera camera;
  World world;
  Time time;
  Frustum frustum;
  Sky sky;
  Crosshair crosshair;
  DebugOverlay debugOverlay;

  std::unique_ptr<Shader> shader;
  std::unique_ptr<Shader> uiShader;
  std::unique_ptr<TextureArray> atlas;
  std::unique_ptr<Model> playerModel;

  PlayerController playerController;
  TransformComponent playerTransform;
  RigidbodyComponent playerRigidbody;

  bool cursorLocked = true;
  float fps = 0.0f;
};