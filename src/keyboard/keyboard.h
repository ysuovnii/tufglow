#pragma once

#include <string>

namespace Keyboard {
    bool writeFile(const std::string& path, const std::string& value);
    bool setBrightness(int level);
    bool setRGB(int mode, int red, int green, int blue, int speed);
}
