#pragma once
#include "../IWindow.h"
#include <windows.h>

class Win32Window : public IWindow {
public:
    bool init(int width, int height, const char* title) override;
    void pollEvents() override;
    void swapBuffers() override;
    bool shouldClose() override;

private:
    HWND hwnd;
    bool closed = false;
};