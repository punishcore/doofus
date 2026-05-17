#include "LinuxWindow.h"

LinuxWindow::LinuxWindow() {}

LinuxWindow::~LinuxWindow() {}

bool LinuxWindow::init(int, int, const char*)
{
    closed = false;
    return true;
}

void LinuxWindow::pollEvents() {}

void LinuxWindow::swapBuffers() {}

bool LinuxWindow::shouldClose()
{
    return closed;
}