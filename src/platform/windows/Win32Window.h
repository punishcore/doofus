#pragma once

#include "../IWindow.h"

#include <windows.h>

class Win32Window : public IWindow
{
public:
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
    HWND hwnd;

    bool closed = false;

    int width = 0;

    int height = 0;
};