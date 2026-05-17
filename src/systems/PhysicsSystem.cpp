#include "PhysicsSystem.h"

void PhysicsSystem::update(
    TransformComponent& transform,
    RigidbodyComponent& rigidbody,
    float dt
)
{
    rigidbody.velocity.y += rigidbody.gravity * dt;

    transform.position += rigidbody.velocity * dt;

    // floor collision
    if (transform.position.y < 0.0f)
    {
        transform.position.y = 0.0f;

        rigidbody.velocity.y = 0.0f;

        rigidbody.grounded = true;
    }
    else
    {
        rigidbody.grounded = false;
    }

    // map bounds
    float limit = 20.0f;

    if (transform.position.x > limit)
        transform.position.x = limit;

    if (transform.position.x < -limit)
        transform.position.x = -limit;

    if (transform.position.z > limit)
        transform.position.z = limit;

    if (transform.position.z < -limit)
        transform.position.z = -limit;
}