#pragma once
#include <memory>
#include "IWindow.h"

enum class PlatformType {
    SDL,
    WIN32,
    LINUX
};

std::unique_ptr<IWindow> CreateWindow(
    PlatformType type
);