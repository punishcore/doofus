#pragma once

#include <vector>
#include <string>

class OBJLoader {
public:
    static std::vector<float> load(const std::string& path);
};