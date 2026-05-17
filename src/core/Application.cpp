#include "Application.h"

#include "../platform/WindowFactory.h"
#include "../platform/sdl/SDLWindow.h"

#include "../renderer/Mesh.h"
#include "../renderer/Shader.h"

#include "../components/Transform.h"
#include "../components/RigidBody.h"

#include "../systems/PhysicsSystem.h"

#include <SDL3/SDL.h>

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

bool Application::init()
{
    window = CreateWindow(PlatformType::SDL);

    if (!window->init(1280, 720, "doofus"))
        return false;

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
    {
        std::cout << "GLAD FAILED\n";
        return false;
    }

    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    SDLWindow* sdl =
        static_cast<SDLWindow*>(window.get());

    SDL_SetWindowRelativeMouseMode(
        sdl->getWindow(),
        true
    );

    return true;
}

void Application::run()
{
    SDLWindow* sdl =
        static_cast<SDLWindow*>(window.get());

    const char* vertexShader = R"(
        #version 460 core

        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        out vec3 FragPos;

        void main()
        {
            FragPos = aPos;

            gl_Position =
                projection *
                view *
                model *
                vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShader = R"(
        #version 460 core

        in vec3 FragPos;

        out vec4 FragColor;

        void main()
        {
            float grid =
                abs(fract(FragPos.x * 0.5) - 0.5)
              + abs(fract(FragPos.z * 0.5) - 0.5);

            float line = step(0.48, grid);

            vec3 base = vec3(0.25);
            vec3 gridColor = vec3(0.4);

            vec3 color =
                mix(base, gridColor, line);

            FragColor = vec4(color, 1.0);
        }
    )";

    Shader shader(vertexShader, fragmentShader);

    float planeVertices[] = {

        -20.0f, 0.0f, -20.0f,
         20.0f, 0.0f, -20.0f,
         20.0f, 0.0f,  20.0f,

        -20.0f, 0.0f, -20.0f,
         20.0f, 0.0f,  20.0f,
        -20.0f, 0.0f,  20.0f
    };

    Mesh plane(
        planeVertices,
        sizeof(planeVertices)
    );

    TransformComponent playerTransform;
    playerTransform.position =
        glm::vec3(0.0f, 0.0f, 0.0f);

    RigidbodyComponent playerRigidbody;

    Uint64 last =
        SDL_GetPerformanceCounter();

    bool cursorLocked = true;

    while (!window->shouldClose())
    {
        Uint64 now =
            SDL_GetPerformanceCounter();

        float dt =
            (float)(now - last)
            / SDL_GetPerformanceFrequency();

        last = now;

        window->pollEvents();

        float mx, my;

        SDL_GetRelativeMouseState(
            &mx,
            &my
        );

        float sensitivity = 0.1f;

        if (cursorLocked)
        {
            camera.yaw += mx * sensitivity;

            camera.pitch -= my * sensitivity;

            if (camera.pitch > 89.0f)
                camera.pitch = 89.0f;

            if (camera.pitch < -89.0f)
                camera.pitch = -89.0f;

            camera.updateVectors();
        }

        const bool* keys =
            SDL_GetKeyboardState(NULL);

        float speed = 5.0f * dt;

        glm::vec3 right =
            glm::normalize(
                glm::cross(
                    camera.front,
                    camera.up
                )
            );

        glm::vec3 moveDir =
            glm::vec3(0.0f);

        glm::vec3 flatFront =
            glm::normalize(
                glm::vec3(
                    camera.front.x,
                    0.0f,
                    camera.front.z
                )
            );

        if (keys[SDL_SCANCODE_W])
            moveDir += flatFront;

        if (keys[SDL_SCANCODE_S])
            moveDir -= flatFront;

        if (keys[SDL_SCANCODE_A])
            moveDir -= right;

        if (keys[SDL_SCANCODE_D])
            moveDir += right;

        if (glm::length(moveDir) > 0.0f)
        {
            moveDir =
                glm::normalize(moveDir);

            playerTransform.position +=
                moveDir * speed;
        }

        if (
            keys[SDL_SCANCODE_SPACE]
            &&
            playerRigidbody.grounded
        )
        {
            playerRigidbody.velocity.y =
                playerRigidbody.jumpForce;
        }

        PhysicsSystem::update(
            playerTransform,
            playerRigidbody,
            dt
        );

        camera.position =
            playerTransform.position
            +
            glm::vec3(0.0f, 1.7f, 0.0f);

        static bool escPressed = false;

        if (keys[SDL_SCANCODE_ESCAPE])
        {
            if (!escPressed)
            {
                cursorLocked =
                    !cursorLocked;

                SDL_SetWindowRelativeMouseMode(
                    sdl->getWindow(),
                    cursorLocked
                );

                escPressed = true;
            }
        }
        else
        {
            escPressed = false;
        }

        glClearColor(
            0.1f,
            0.1f,
            0.12f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT
            |
            GL_DEPTH_BUFFER_BIT
        );

        shader.use();

        glm::mat4 model =
            glm::mat4(1.0f);

        glm::mat4 view =
            camera.getViewMatrix();

        glm::mat4 projection =
            glm::perspective(
                glm::radians(90.0f),
                1280.0f / 720.0f,
                0.1f,
                100.0f
            );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.id,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.id,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.id,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        plane.draw();

        window->swapBuffers();
    }
}

void Application::shutdown()
{
    window.reset();
}