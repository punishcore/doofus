#pragma once

#include "../IWindow.h"

class LinuxWindow : public IWindow
{
public:
    LinuxWindow();

    ~LinuxWindow() override;

    bool init(
        int width,
        int height,
        const char* title
    ) override;

    void pollEvents() override;

    void swapBuffers() override;

    bool shouldClose() override;

    int getWidth() override;

    int getHeight() override;

private:
    bool closed = false;

    int width = 0;

    int height = 0;
};