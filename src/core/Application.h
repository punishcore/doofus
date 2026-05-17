#pragma once

#include "../platform/IWindow.h"
#include "../camera/Camera.h"

#include <memory>

class Application {
public:
    bool init();

    void run();

    void shutdown();

private:
    std::unique_ptr<IWindow> window;

    Camera camera;
};