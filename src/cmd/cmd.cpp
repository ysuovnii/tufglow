#include "cmd.h"
#include "../keyboard/keyboard.h"

#include <iostream>

namespace Commands {

    void brightness(int level){
        if (!Keyboard::setBrightness(level)) {
            std::cerr << "Failed to set brightness\n";
            return;
        }
    }

    void rgb(int mode, int red, int green, int blue, int speed){
        if (!Keyboard::setRGB(mode, red, green, blue, speed)) {
            std::cerr << "Failed to set RGB\n";
            return;
        }
    }

    void help() {
        std::cout
            << "tufglow - ASUS TUF RGB controller\n\n"
            << "Usage:\n"
            << "  tufglow brightness <level>\n"
            << "  tufglow rgb <mode> <red> <green> <blue> <speed>\n"
            << "  tufglow help\n";
    }
}
