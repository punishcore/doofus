#include "Time.h"

#include <cmath>

void Time::update(float dt)
{
    static float accumulator = 0.0f;

    accumulator += dt;

    /*
        20 tick per second
    */

    while (accumulator >= (1.0f / 20.0f))
    {
        ticks++;

        accumulator -= (1.0f / 20.0f);
    }

    if (ticks >= TICKS_PER_DAY)
    {
        ticks = 0;
    }
}

float Time::getDayProgress()
{
    return (float)ticks / (float)TICKS_PER_DAY;
}

glm::vec3 Time::getSkyTopColor()
{
    float t =
        std::sin(
            getDayProgress() * 3.141592f
        );

    glm::vec3 day(0.2f, 0.4f, 0.9f);

    glm::vec3 night(0.02f, 0.02f, 0.08f);

    return glm::mix(night, day, t);
}

glm::vec3 Time::getSkyHorizonColor()
{
    float t =
        std::sin(
            getDayProgress() * 3.141592f
        );

    glm::vec3 day(0.8f, 0.5f, 0.3f);

    glm::vec3 night(0.03f, 0.03f, 0.1f);

    return glm::mix(night, day, t);
}

glm::vec3 Time::getSkyBottomColor()
{
    float t =
        std::sin(
            getDayProgress() * 3.141592f
        );

    glm::vec3 day(0.1f, 0.1f, 0.2f);

    glm::vec3 night(0.0f, 0.0f, 0.02f);

    return glm::mix(night, day, t);
}