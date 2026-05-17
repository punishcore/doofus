# Documentation

## Overview

This project currently includes a basic real-time 3D application setup using:

* SDL3 window system
* OpenGL rendering
* GLAD OpenGL loader
* CMake build system
* First-person camera movement
* Basic physics system
* Platform collision
* Mouse look controls
* Shader-based rendering
* Grid floor rendering
* Modular folder structure

---

# Features Implemented

## Window System

The application uses SDL3 to:

* Create an OpenGL window
* Handle input events
* Manage mouse capture
* Swap rendering buffers

### Implemented

* OpenGL context creation
* Window initialization
* Event polling
* Window close handling

---

## OpenGL Rendering

The renderer currently supports:

* VAO/VBO rendering
* Shader compilation
* Depth testing
* Basic mesh rendering

### Implemented

* Vertex shaders
* Fragment shaders
* Mesh abstraction
* Plane rendering
* Perspective projection

---

## Camera System

A first-person spectator camera has been implemented.

### Controls

| Key   | Action             |
| ----- | ------------------ |
| W     | Move forward       |
| S     | Move backward      |
| A     | Move left          |
| D     | Move right         |
| SPACE | Jump               |
| Mouse | Look around        |
| ESC   | Toggle cursor lock |

### Features

* Yaw & pitch rotation
* Mouse look
* Direction vectors
* View matrix generation
* Cursor lock toggle

---

## Physics System

A simple physics system has been added.

### Implemented

* Gravity
* Velocity system
* Jumping
* Ground detection
* Floor collision
* Movement bounds

### Physics Behavior

* Player falls using gravity
* Player cannot go below floor level
* Jump only works while grounded
* Movement limited inside map area

---

## Platform / Floor

A large platform is rendered using OpenGL.

### Features

* Gray floor
* Procedural grid pattern
* Large walkable area
* Collision support

### Visual Style

The floor uses:

* Fragment shader grid effect
* Dark gray base color
* Lighter grid lines

---

## Input System

Keyboard input is handled using SDL3.

### Implemented Inputs

* Movement keys
* Jump
* Cursor toggle
* Mouse movement

---

# Project Structure

```txt
src/
├── camera/
│   ├── Camera.cpp
│   └── Camera.h

├── components/
│   ├── RigidBody.h
│   └── Transform.h

├── core/
│   ├── Application.cpp
│   └── Application.h

├── ecs/

├── input/
│   ├── Input.cpp
│   └── input.h

├── platform/
│   ├── IWindow.h
│   ├── WindowFactory.cpp
│   ├── WindowFactory.h
│   │
│   ├── sdl/
│   │   ├── SDLWindow.cpp
│   │   └── SDLWindow.h
│   │
│   ├── linux/
│   │   ├── LinuxWindow.cpp
│   │   └── LinuxWindow.h
│   │
│   └── windows/
│       ├── Win32Window.cpp
│       └── Win32Window.h

├── renderer/
│   ├── Mesh.cpp
│   ├── Mesh.h
│   ├── Shader.cpp
│   └── Shader.h

├── systems/
│   ├── PhysicsSystem.cpp
│   └── PhysicsSystem.h

├── utils/

└── main.cpp
```

---

# Build System

The project uses:

* CMake
* GCC / G++
* SDL3
* OpenGL

---

## Build Script

```bash
./build.sh
```

The script automatically:

1. Removes old build files
2. Creates a new build directory
3. Runs CMake
4. Compiles the project
5. Launches the executable

---

# External Libraries

## SDL3

Used for:

* Windowing
* Input
* OpenGL context management

## GLAD

Used for:

* Loading OpenGL functions

## GLM

Used for:

* Vector math
* Matrix transformations
* Camera calculations

---

# Current Rendering Pipeline

The rendering flow currently works like this:

```txt
Application
    ↓
Camera Update
    ↓
Physics Update
    ↓
Shader Bind
    ↓
Mesh Draw
    ↓
Buffer Swap
```

---

# Current State

The application currently supports:

* Real-time rendering
* 3D camera movement
* Physics-based movement
* Jumping
* Mouse look
* Grid floor rendering
* Platform collision
* Modular architecture

---

# Planned Improvements

Possible next features:

* Cube rendering
* Texture loading
* Lighting
* Entity system
* Scene management
* Collision boxes
* Model loading
* UI system
* Shadow rendering
* Audio system
* Multiplayer
* Editor tools
