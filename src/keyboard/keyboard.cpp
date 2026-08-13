#include "keyboard.h"
#include <fstream>

namespace Keyboard {

    static const std::string RGB_PATH = "/sys/class/leds/asus::kbd_backlight/kbd_rgb_mode";

    static const std::string BRIGHTNESS_PATH = "/sys/class/leds/asus::kbd_backlight/brightness";

    bool writeFile(const std::string& path, const std::string& value) {
        std::ofstream file(path);

        if (!file) return false;
        file << value;

        return file.good();
    }

    bool setBrightness(int level) {
        return writeFile(
            BRIGHTNESS_PATH,
            std::to_string(level)
        );
    }

    bool setRGB(int mode, int red, int green, int blue, int speed) {
        std::string value =
            std::to_string(mode) + " " +
            std::to_string(red) + " " +
            std::to_string(green) + " " +
            std::to_string(blue) + " " +
            std::to_string(speed);

        return writeFile(RGB_PATH, value);
    }

}
