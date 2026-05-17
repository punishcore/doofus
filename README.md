# doofus Engine Documentation

## Overview

**doofus** is a lightweight game engine/framework built with:

* C++
* SDL3
* OpenGL 4.6
* GLAD

The project is designed as a foundation for:

* 2D/3D rendering
* input handling
* camera systems
* platform abstraction
* ECS architecture
* future game engine expansion

---

# Features

## Current Features

### Window System

* SDL3 Window
* OpenGL Context
* Cross-platform abstraction
* Window Factory Pattern

### Rendering

* OpenGL 4.6 Core Profile
* Triangle rendering
* Basic shader system
* VAO & VBO setup

### Input System

* Keyboard input
* Mouse movement
* WASD movement
* ESC cursor toggle

### Camera System

* Free-look camera
* Mouse look
* Spectator movement
* FPS-style controls

### Platform Layer

Supported:

* Linux
* Windows
* SDL abstraction

### Project Architecture

* Core
* Renderer
* ECS
* Components
* Systems
* Utilities
* Input layer

---

# Project Structure

```txt
doofus/
├── assets/
├── build/
├── external/
│   └── glad/
├── src/
│   ├── components/
│   ├── core/
│   ├── ecs/
│   ├── input/
│   ├── platform/
│   ├── renderer/
│   ├── systems/
│   └── utils/
├── CMakeLists.txt
└── README.md
```

---

# Folder Explanation

## assets/

Stores:

* textures
* models
* shaders
* audio
* fonts

---

## external/

Third-party dependencies.

Current:

* GLAD

Future:

* stb_image
* glm
* assimp
* imgui

---

## src/core/

Handles the engine lifecycle.

### Files

#### `Application.h`

Responsible for:

* initialization
* main loop
* shutdown

#### `Application.cpp`

Contains:

* rendering loop
* updates
* camera logic
* input handling
* OpenGL initialization

---

## src/platform/

Platform and window abstraction layer.

### IWindow.h

Window abstraction interface.

```cpp
class IWindow {
public:
    virtual bool init(int width, int height, const char* title) = 0;
    virtual void pollEvents() = 0;
    virtual void swapBuffers() = 0;
    virtual bool shouldClose() = 0;
};
```

---

# SDL Backend

## SDLWindow.h / SDLWindow.cpp

Handles:

* SDL initialization
* OpenGL context creation
* buffer swapping
* event polling

---

# Linux Backend

## LinuxWindow.h / LinuxWindow.cpp

Native Linux backend placeholder.

Future:

* X11 support
* Wayland support

---

# Windows Backend

## Win32Window.h / Win32Window.cpp

Native Win32 backend placeholder.

Future:

* Win32 rendering
* DirectX support

---

# WindowFactory

## WindowFactory.h / WindowFactory.cpp

Factory pattern used to select the backend:

```cpp
CreateWindow(PlatformType::SDL);
```

---

# Renderer

## OpenGL Pipeline

Current renderer uses:

* VAO
* VBO
* Vertex Shader
* Fragment Shader

---

# Current Render Flow

```txt
Vertex Data
    ↓
VBO
    ↓
VAO
    ↓
Vertex Shader
    ↓
Fragment Shader
    ↓
Screen
```

---

# Input System

## Keyboard Controls

Current controls:

* W → Forward
* S → Backward
* A → Left
* D → Right
* ESC → Toggle Cursor

---

# Camera System

## Spectator Camera

Features:

* Mouse look
* Free movement
* FPS-style movement

Movement:

* forward/backward
* left/right
* vertical movement (future)

---

# OpenGL Setup

## Version

```txt
OpenGL 4.6 Core
```

SDL setup:

```cpp
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
```

---

# Build System

Uses:

* CMake

---

# Dependencies

## Linux

Install dependencies:

```bash
sudo pacman -S sdl3 mesa glew cmake gcc
```

Ubuntu:

```bash
sudo apt install libsdl3-dev mesa-common-dev build-essential cmake
```

---

# Build Instructions

## Clean Build

```bash
rm -rf build

mkdir build
cd build

cmake ..
cmake --build .
```

---

# Run

```bash
./doofus
```

---

# Current Engine Flow

```txt
main.cpp
    ↓
Application
    ↓
Window Creation
    ↓
OpenGL Init
    ↓
Game Loop
    ↓
Input
    ↓
Camera
    ↓
Render
```

---

# Future Roadmap

## Rendering

Planned:

* Texture system
* Mesh rendering
* Model loading
* Skybox
* Lighting
* Shadow mapping
* PBR pipeline

---

## ECS

Planned:

* Entity Manager
* Component Registry
* System Processing

---

## Physics

Planned:

* Collision
* Rigidbody
* Gravity
* Raycasting

---

## Audio

Planned:

* SDL Audio
* OpenAL
* FMOD support

---

## UI

Planned:

* ImGui integration
* Debug tools
* Inspector
* Console

---

## Scripting

Possible future support:

* Lua
* C#
* Python embedding

---

# Suggested Next Steps

Recommended development order:

1. Camera matrix
2. Projection matrix
3. Cube rendering
4. Depth testing
5. Texture loading
6. Basic ECS
7. Mesh abstraction
8. Scene system
9. Lighting
10. Model loading

---

# Recommended Libraries

## Math

Use:

[GLM](https://github.com/g-truc/glm?utm_source=chatgpt.com)

---

## Image Loading

Use:

[stb_image](https://github.com/nothings/stb?utm_source=chatgpt.com)

---

## GUI

Use:

[Dear ImGui](https://github.com/ocornut/imgui?utm_source=chatgpt.com)

---

# Engine Goal

doofus is intended to become:

* a lightweight engine
* a modern OpenGL renderer
* an ECS-based architecture
* a modular framework
* a learnable engine architecture
* a cross-platform engine foundation

---

# Current Capabilities

At the current stage, the engine can:

* open a window
* create an OpenGL context
* render a triangle
* handle input
* support basic camera movement
* lock/unlock the mouse cursor
* run a render loop
* compile shaders
* manage the VAO/VBO pipeline

---

# Example Expansion Path

```txt
Triangle
↓
Cube
↓
3D Camera
↓
Textures
↓
Lighting
↓
Scene System
↓
Game
```
