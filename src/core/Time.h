#pragma once

#include <glm/glm.hpp>

class Time
{
public:

    int ticks = 0;

    static constexpr int TICKS_PER_DAY = 24000;

    void update(float dt);

    float getDayProgress();

    glm::vec3 getSkyTopColor();
    glm::vec3 getSkyHorizonColor();
    glm::vec3 getSkyBottomColor();
};