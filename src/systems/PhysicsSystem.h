#pragma once

#include "../components/Transform.h"
#include "../components/RigidBody.h"

class PhysicsSystem {
public:
    static void update(
        TransformComponent& transform,
        RigidbodyComponent& rigidbody,
        float dt
    );
};