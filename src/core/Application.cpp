#include "core/Application.h"
#include "platform/WindowFactory.h"

#include <iostream>
#include <vector>

#include <SDL3/SDL.h>

#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    std::cout << "OpenGL Version: "
              << glGetString(GL_VERSION)
              << "\n";

    glViewport(0, 0, 1280, 720);

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Application::run()
{
    float vertices[] = {
        // floor
        -50.0f, 0.0f, -50.0f,
         50.0f, 0.0f, -50.0f,
         50.0f, 0.0f,  50.0f,

         50.0f, 0.0f,  50.0f,
        -50.0f, 0.0f,  50.0f,
        -50.0f, 0.0f, -50.0f
    };

    const char* vertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"

        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 460 core\n"

        "out vec4 FragColor;\n"

        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.3, 0.8, 0.3, 1.0);\n"
        "}\0";

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    GLuint vertexShader =
        glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );

    glCompileShader(vertexShader);

    GLuint fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        NULL
    );

    glCompileShader(fragmentShader);

    GLuint shaderProgram =
        glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glm::vec3 cameraPos   = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;

    SDL_SetWindowRelativeMouseMode(
        SDL_GetKeyboardFocus(),
        true
    );

    glm::mat4 projection = glm::perspective(
        glm::radians(75.0f),
        1280.0f / 720.0f,
        0.1f,
        500.0f
    );

    Uint64 last = SDL_GetPerformanceCounter();

    while (!window->shouldClose())
    {
        window->pollEvents();

        Uint64 now = SDL_GetPerformanceCounter();

        float dt =
            (float)(now - last) /
            SDL_GetPerformanceFrequency();

        last = now;

        const bool* keys =
            SDL_GetKeyboardState(NULL);

        float cameraSpeed = 10.0f * dt;

        if (keys[SDL_SCANCODE_W])
            cameraPos += cameraSpeed * cameraFront;

        if (keys[SDL_SCANCODE_S])
            cameraPos -= cameraSpeed * cameraFront;

        if (keys[SDL_SCANCODE_A])
            cameraPos -= glm::normalize(
                glm::cross(cameraFront, cameraUp)
            ) * cameraSpeed;

        if (keys[SDL_SCANCODE_D])
            cameraPos += glm::normalize(
                glm::cross(cameraFront, cameraUp)
            ) * cameraSpeed;

        if (keys[SDL_SCANCODE_SPACE])
            cameraPos.y += cameraSpeed;

        if (keys[SDL_SCANCODE_LSHIFT])
            cameraPos.y -= cameraSpeed;

        float mouseX, mouseY;

        SDL_GetRelativeMouseState(
            &mouseX,
            &mouseY
        );

        float sensitivity = 0.1f;

        mouseX *= sensitivity;
        mouseY *= sensitivity;

        yaw += mouseX;
        pitch -= mouseY;

        if (pitch > 89.0f)
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;

        direction.x =
            cos(glm::radians(yaw)) *
            cos(glm::radians(pitch));

        direction.y =
            sin(glm::radians(pitch));

        direction.z =
            sin(glm::radians(yaw)) *
            cos(glm::radians(pitch));

        cameraFront =
            glm::normalize(direction);

        glm::mat4 model =
            glm::mat4(1.0f);

        glm::mat4 view = glm::lookAt(
            cameraPos,
            cameraPos + cameraFront,
            cameraUp
        );

        glClearColor(
            0.1f,
            0.1f,
            0.15f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        glUseProgram(shaderProgram);

        unsigned int modelLoc =
            glGetUniformLocation(
                shaderProgram,
                "model"
            );

        unsigned int viewLoc =
            glGetUniformLocation(
                shaderProgram,
                "view"
            );

        unsigned int projectionLoc =
            glGetUniformLocation(
                shaderProgram,
                "projection"
            );

        glUniformMatrix4fv(
            modelLoc,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        window->swapBuffers();
    }
}

void Application::shutdown()
{
    window.reset();
}