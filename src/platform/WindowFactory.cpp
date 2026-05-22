#include "WindowFactory.h"
#include "sdl/SDLWindow.h"

#ifdef _WIN32
#include "windows/Win32Window.h"
#endif

#include "linux/LinuxWindow.h"

std::unique_ptr<IWindow> CreateWindow(PlatformType type) {
  switch (type) {
  case PlatformType::SDL:
    return std::make_unique<SDLWindow>();

#ifdef _WIN32
  case PlatformType::WIN32:
    return std::make_unique<Win32Window>();
#endif

#ifdef __linux__
  case PlatformType::LINUX:
    return std::make_unique<LinuxWindow>();
#endif

  default:
    return nullptr;
  }
}