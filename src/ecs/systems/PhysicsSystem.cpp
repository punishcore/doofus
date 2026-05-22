#include "PhysicsSystem.h"
#include <cmath>

bool PhysicsSystem::checkCollision(float x, float y, float z, World &world) {
  float size = 0.3f;

  for (float ix = -size; ix <= size; ix += size)
    for (float iy = 0; iy <= 1.8f; iy += 0.9f)
      for (float iz = -size; iz <= size; iz += size) {
        if (world.isSolid((int)floor(x + ix), (int)floor(y + iy),
                          (int)floor(z + iz))) {
          return true;
        }
      }

  return false;
}

void PhysicsSystem::update(TransformComponent &transform,
                           RigidbodyComponent &rigidbody, World &world,
                           float dt) {
  // gravity
  rigidbody.velocity.y += rigidbody.gravity * dt;

  glm::vec3 pos = transform.position;

  glm::vec3 next = pos;

  // =========================
  // X axis
  // =========================
  next.x = pos.x + rigidbody.velocity.x * dt;

  if (checkCollision(next.x, pos.y, pos.z, world)) {
    rigidbody.velocity.x = 0.0f;
    next.x = pos.x;
  }

  // =========================
  // Z axis
  // =========================
  next.z = pos.z + rigidbody.velocity.z * dt;

  if (checkCollision(next.x, pos.y, next.z, world)) {
    rigidbody.velocity.z = 0.0f;
    next.z = pos.z;
  }

  // =========================
  // Y axis
  // =========================
  next.y = pos.y + rigidbody.velocity.y * dt;

  bool hitY = checkCollision(next.x, next.y, next.z, world);

  if (hitY) {
    if (rigidbody.velocity.y < 0.0f) {
      rigidbody.grounded = true;
    }

    rigidbody.velocity.y = 0.0f;
    next.y = pos.y;
  } else {
    rigidbody.grounded = false;
  }

  // apply final position
  transform.position = next;

  // friction (ground movement feel)
  rigidbody.velocity.x *= 0.82f;
  rigidbody.velocity.z *= 0.82f;
}