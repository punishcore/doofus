#include "LinuxWindow.h"

LinuxWindow::LinuxWindow()
{
}

LinuxWindow::~LinuxWindow()
{
}

bool LinuxWindow::init(
    int w,
    int h,
    const char*
)
{
    width = w;

    height = h;

    closed = false;

    return true;
}

void LinuxWindow::pollEvents()
{
}

void LinuxWindow::swapBuffers()
{
}

bool LinuxWindow::shouldClose()
{
    return closed;
}

int LinuxWindow::getWidth()
{
    return width;
}

int LinuxWindow::getHeight()
{
    return height;
}