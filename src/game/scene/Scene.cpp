#include "Scene.h"

#include "../../platform/input/Input.h"

#include "../../ecs/systems/PhysicsSystem.h"

#include <glad/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Scene::init()
{
    sky.Init();

    shader = std::make_unique<Shader>(
        "assets/shaders/block.vert",
        "assets/shaders/block.frag"
    );

    atlas = std::make_unique<Texture>(
        "assets/textures/atlas.png"
    );

    world.update(0.0f, 0.0f);

    playerTransform.position =
        glm::vec3(
            0.0f,
            world.getHeight(0, 0),
            0.0f
        );
}

void Scene::update(
    float dt,
    SDL_Window* window
)
{
    time.update(dt);

    playerController.update(
        camera,
        playerTransform,
        playerRigidbody,
        cursorLocked,
        window
    );

    world.update(
        playerTransform.position.x,
        playerTransform.position.z
    );

    PhysicsSystem::update(
        playerTransform,
        playerRigidbody,
        world,
        dt
    );
}

void Scene::render()
{
    glm::vec3 top =
        time.getSkyTopColor();

    glm::vec3 hor =
        time.getSkyHorizonColor();

    glm::vec3 bot =
        time.getSkyBottomColor();

    glEnable(GL_DEPTH_TEST);

    glDepthMask(GL_TRUE);

    glClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );

    glClear(
        GL_COLOR_BUFFER_BIT
        | GL_DEPTH_BUFFER_BIT
    );

    glm::mat4 projection =
        glm::perspective(
            glm::radians(90.0f),
            1280.0f / 720.0f,
            0.1f,
            100.0f
        );

    glm::mat4 view =
        camera.getViewMatrix();

    glm::mat4 invProj =
        glm::inverse(projection);

    glm::mat4 rotationView =
        glm::mat4(glm::mat3(view));

    glm::mat4 invView =
        glm::inverse(rotationView);

    // SKY
    sky.shader->use();

    glUniformMatrix4fv(
        glGetUniformLocation(
            sky.shader->id,
            "invProj"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(invProj)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(
            sky.shader->id,
            "invView"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(invView)
    );

    sky.Render(top, hor, bot);

    // WORLD
    shader->use();

    glm::mat4 model =
        glm::mat4(1.0f);

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader->id,
            "model"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader->id,
            "view"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader->id,
            "projection"
        ),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );

    atlas->bind(0);

    shader->setInt("atlas", 0);

    world.draw(
        playerTransform.position.x,
        playerTransform.position.z
    );
}