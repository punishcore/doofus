cmake_minimum_required(VERSION 3.20)

project(doofus)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(doofus

    src/main.cpp

    src/core/Application.cpp

    src/platform/sdl/SDLWindow.cpp
    src/platform/WindowFactory.cpp
    src/platform/linux/LinuxWindow.cpp

    src/renderer/Shader.cpp
    src/renderer/Mesh.cpp

    src/camera/Camera.cpp

    src/systems/PhysicsSystem.cpp

    external/glad/src/gl.c
)

target_include_directories(doofus PRIVATE
    src
    external/glad/include
)

target_link_libraries(doofus PRIVATE
    SDL3::SDL3
    OpenGL::GL
)