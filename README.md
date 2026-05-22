````md
# Documentation

# Overview

This project is a real-time 3D voxel-based engine built using:

* SDL3 window system
* OpenGL rendering (GLAD loader)
* GLM math library
* CMake build system
* Custom ECS-style physics system
* Procedural voxel world (chunk-based)
* Terrain generation system
* Dynamic sky rendering
* First-person camera controller
* Basic collision system with voxel world integration

The engine is structured around a modular architecture using:

```txt
Application
    ↓
Game
    ↓
Scene
    ↓
Renderer / World / Physics / Player
```

---

# Engine Architecture

## Application Layer

The `Application` layer handles:

* Window initialization
* OpenGL context setup
* Main loop execution
* Delta time calculation
* Buffer swapping
* Event polling

### Main Loop

```cpp
while (!window->shouldClose())
{
    window->pollEvents();

    game.update(dt, window);

    game.render();

    window->swapBuffers();
}
```

---

## Game Layer

The `Game` system acts as a high-level game manager.

### Responsibilities

* Scene management
* Game lifecycle
* Future scene switching support
* Gameplay orchestration

---

## Scene Layer

The `Scene` system contains the actual gameplay world.

### Responsibilities

* Camera
* Physics
* Player
* Sky rendering
* Terrain rendering
* Input handling
* World simulation

### Advantages

* Modular architecture
* Easier expansion
* Cleaner codebase
* Future support for:
  * Main menu
  * Pause scenes
  * Multiplayer lobby
  * Loading scenes

---

# Window System

The application uses SDL3 to manage:

* OpenGL context creation
* Window lifecycle
* Input polling
* Mouse capture
* Buffer swapping

---

## Features Implemented

### Native Window Features

* Resizable window
* Native title bar
* Minimize button
* Maximize button
* Close button
* Window dragging support

### SDL Window Flags

```cpp
SDL_WINDOW_OPENGL
| SDL_WINDOW_RESIZABLE
| SDL_WINDOW_HIGH_PIXEL_DENSITY
```

---

## OpenGL Context

Current renderer uses:

```txt
OpenGL 4.6 Core Profile
```

### Features

* Modern rendering pipeline
* VSync support
* Depth testing
* GLAD loader integration

---

# Input System

The engine has a dedicated SDL input abstraction layer.

Folder:

```txt
src/platform/input
```

---

## Features

* Keyboard state tracking
* Mouse delta tracking
* Relative mouse mode
* ESC cursor toggle
* Persistent key states

---

## Controls

| Key | Action |
|---|---|
| W | Move Forward |
| S | Move Backward |
| A | Move Left |
| D | Move Right |
| SPACE | Jump |
| Mouse | Look Around |
| ESC | Toggle Cursor |

---

# Camera System

A first-person FPS camera system is implemented.

Files:

```txt
src/camera/Camera.*
```

---

## Features

* Yaw rotation
* Pitch rotation
* Mouse sensitivity
* View matrix generation
* Direction vector recalculation
* FPS-style movement

---

## Camera Math

### Front Vector Calculation

```cpp
direction.x =
cos(glm::radians(yaw))
* cos(glm::radians(pitch));

direction.y =
sin(glm::radians(pitch));

direction.z =
sin(glm::radians(yaw))
* cos(glm::radians(pitch));
```

---

# Player Controller

Player movement is handled separately from physics.

Files:

```txt
src/player/PlayerController.*
```

---

## Features

* FPS movement
* Jumping
* Mouse look
* Cursor lock
* Camera follow
* Velocity-based movement

---

# Physics System

Physics is integrated with the voxel world system.

Files:

```txt
src/ecs/systems/PhysicsSystem.*
```

---

## Features

* Gravity simulation
* Velocity integration
* Ground detection
* Jump force
* Collision handling
* Horizontal movement damping

---

## Physics Flow

```txt
Input
    ↓
Velocity Update
    ↓
Gravity
    ↓
Collision Detection
    ↓
Position Correction
```

---

# ECS-style Architecture

The engine follows a lightweight ECS-inspired structure.

Folders:

```txt
src/ecs/components
src/ecs/systems
```

---

## Components

| Component | Purpose |
|---|---|
| TransformComponent | Position data |
| RigidbodyComponent | Physics data |

---

## Systems

| System | Purpose |
|---|---|
| PhysicsSystem | Physics simulation |

---

# Voxel World System

This is the core system of the engine.

The world is chunk-based and procedurally generated.

---

# World Structure

```txt
World
 ├── Chunk (-2, -2)
 ├── Chunk (-1, -2)
 ├── Chunk (0, 0)
 ├── Chunk (1, 0)
 └── Chunk (2, 2)
```

---

## Chunk System

Each chunk contains:

* SIZE = 16
* HEIGHT = 64
* 3D block array storage

### Block Storage

```cpp
BlockType blocks[SIZE][HEIGHT][SIZE];
```

---

# Procedural Terrain Generation

Terrain generation uses procedural mathematical functions.

---

## Current Terrain Logic

```cpp
float noise =
sin(worldX * 0.12f)
* cos(worldZ * 0.12f);

int height =
20 + (noise * 8);
```

---

## Terrain Features

* Hills
* Smooth variation
* Deterministic generation
* Chunk-independent consistency

---

# Terrain Generator System

A modular terrain generator system exists.

Files:

```txt
renderer/world/TerrainGenerator.*
```

---

## Features

* Heightmap generation
* Layered terrain
* Chunk-aware coordinates
* Extensible generation pipeline

---

## Terrain Layers

| Layer | Block Type |
|---|---|
| Surface | Grass |
| Underground | Dirt |
| Deep Layer | Stone |

---

# Biome System

Biome architecture already exists.

Files:

```txt
renderer/world/biome
```

---

## Planned Biomes

* Grasslands
* Desert
* Mountains
* Snow
* Ocean

---

## Planned Biome Effects

* Height scaling
* Terrain roughness
* Noise frequency
* Block variation

---

# Chunk Mesh Generation

Chunks generate optimized meshes.

---

## Features

* Vertex batching
* Face culling
* Static mesh generation
* GPU upload optimization

---

# Face Culling Optimization

Only visible faces are rendered.

---

## Example

```cpp
if (isAir(x, y + 1, z))
    addFace(top);
```

---

## Advantages

* Lower vertex count
* Better rendering performance
* Lower VRAM usage
* Faster chunk rendering

---

# Texture System

Texture abstraction layer exists.

Files:

```txt
renderer/Texture.*
```

---

## Features

* PNG loading
* OpenGL texture upload
* Texture binding abstraction
* Texture atlas rendering

---

# Texture Atlas

Voxel textures use a shared atlas.

File:

```txt
assets/textures/atlas.png
```

---

## Advantages

* Reduced draw calls
* Better batching
* Fewer texture switches
* Better GPU performance

---

# Shader System

Modern GLSL shader abstraction exists.

Files:

```txt
renderer/Shader.*
```

---

## Features

* Shader loading
* Compilation
* Uniform management
* Program linking

---

## Current Shaders

| Shader | Purpose |
|---|---|
| block.vert | Terrain vertex shader |
| block.frag | Terrain fragment shader |
| sky.vert | Sky vertex shader |
| sky.frag | Sky atmosphere shader |

---

# Dynamic Sky System

The engine supports procedural sky rendering.

Files:

```txt
renderer/Sky.*
```

---

## Features

* Fullscreen sky rendering
* Atmospheric gradients
* Horizon blending
* Dynamic color transitions

---

# Day-Night Cycle System

Sky colors are controlled by the `Time` system.

Files:

```txt
core/Time.*
```

---

## Features

* Dynamic sky colors
* Smooth transitions
* Time progression
* Horizon interpolation

---

## Sky Rendering Flow

```txt
Time System
    ↓
Sky Colors
    ↓
Sky Shader
    ↓
Rendered Atmosphere
```

---

# Collision System

Physics interacts directly with voxel terrain.

---

## Collision Logic

```cpp
world.isSolid(x, y, z)
```

The system:

1. Converts world coordinates
2. Finds chunk
3. Converts to local chunk coordinates
4. Checks block solidity

---

# Chunk Coordinate Conversion

World → Chunk coordinate conversion:

```cpp
chunkX = floor(x / Chunk::SIZE);

localX =
x - chunkX * Chunk::SIZE;
```

---

## Features

* Negative coordinate support
* Infinite-world-ready foundation
* Dynamic chunk lookup

---

# Infinite World Foundation

Current architecture already supports future infinite terrain.

---

## Planned Expansion

```txt
Player Movement
    ↓
Chunk Streaming
    ↓
Chunk Generation
    ↓
Chunk Unloading
```

---

# Rendering Pipeline

```txt
Application Loop
    ↓
Input Update
    ↓
Camera Update
    ↓
Physics Update
    ↓
World Rendering
    ↓
Sky Rendering
    ↓
Swap Buffers
```

---

# Delta Time System

The engine uses delta-time simulation.

---

## Advantages

* FPS-independent movement
* Stable physics
* Smooth camera movement
* Consistent gameplay timing

---

## Delta Time Example

```cpp
float dt =
(now - last)
/ SDL_GetPerformanceFrequency();
```

---

# Window Abstraction Layer

The engine supports backend abstraction.

Folder:

```txt
src/platform
```

---

## Current Backends

| Backend | Status |
|---|---|
| SDLWindow | Active |
| LinuxWindow | Placeholder |
| Win32Window | Placeholder |

---

## Advantages

* Multi-platform foundation
* Easier backend swapping
* Cleaner platform separation

---

# Project Structure

```txt
src/
├── camera
├── core
├── ecs
├── game
├── platform
├── player
├── renderer
└── utils
```

---

# Memory & Performance Notes

Current optimizations:

* Chunk mesh caching
* Face culling
* Static chunk rendering
* Texture atlas batching
* OpenGL depth testing

---