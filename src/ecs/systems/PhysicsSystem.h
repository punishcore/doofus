#pragma once

#include "../../world/World.h"
#include "../components/RigidBody.h"
#include "../components/Transform.h"

class PhysicsSystem {
public:
  static void update(TransformComponent &transform,
                     RigidbodyComponent &rigidbody, World &world, float dt);

private:
  static bool checkCollision(float x, float y, float z, World &world);
};