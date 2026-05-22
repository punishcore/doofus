#pragma once

#include "../camera/Camera.h"

#include "../platform/IWindow.h"

#include "../game/Game.h"

#include <memory>

class Application
{
public:
    bool init();

    void run();

    void shutdown();

private:
    std::unique_ptr<IWindow> window;

    Game game;
};