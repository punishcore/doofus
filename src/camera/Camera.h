#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:

    glm::vec3 position = glm::vec3(0.0f, 2.0f, 5.0f);

    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    Camera();

    glm::mat4 getViewMatrix();

    void updateVectors();
};