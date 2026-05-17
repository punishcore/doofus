#pragma once

class IWindow {
public:
    virtual ~IWindow() = default;

    virtual bool init(
        int width,
        int height,
        const char* title
    ) = 0;

    virtual void pollEvents() = 0;
    virtual void swapBuffers() = 0;
    virtual bool shouldClose() = 0;
};