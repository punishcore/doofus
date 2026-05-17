#include "Win32Window.h"

bool Win32Window::init(int width, int height, const char* title)
{
    closed = false;
    return true;
}

void Win32Window::pollEvents()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void Win32Window::swapBuffers() {}

bool Win32Window::shouldClose()
{
    return closed;
}