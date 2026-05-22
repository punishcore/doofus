#pragma once
#include "IWindow.h"
#include <memory>

enum class PlatformType { SDL, WIN32, LINUX };

std::unique_ptr<IWindow> CreateWindow(PlatformType type);