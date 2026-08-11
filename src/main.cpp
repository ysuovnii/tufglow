#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

static const std::string RGB_PATH =
    "/sys/class/leds/asus::kbd_backlight/kbd_rgb_mode";

static const std::string BRIGHTNESS_PATH =
    "/sys/class/leds/asus::kbd_backlight/brightness";

bool writeFile(const std::string& path, const std::string& value)
{
    std::ofstream file(path);

    if (!file) {
        std::cerr << "Failed to open: " << path << '\n';
        std::cerr << "Try running the command with sudo.\n";
        return false;
    }

    file << value;

    if (!file) {
        std::cerr << "Failed to write to: " << path << '\n';
        return false;
    }

    return true;
}

void usage()
{
    std::cout <<
        "tufglow - ASUS TUF RGB controller\n\n"
        "Usage:\n"
        "  tufglow red\n"
        "  tufglow green\n"
        "  tufglow blue\n"
        "  tufglow off\n"
        "  tufglow brightness <0-3>\n"
        "  tufglow rgb <r> <g> <b>\n";
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        usage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "brightness") {

        if (argc != 3) {
            std::cerr << "Usage: tufglow brightness <0-3>\n";
            return 1;
        }

        int brightness = std::atoi(argv[2]);

        if (brightness < 0 || brightness > 3) {
            std::cerr << "Brightness must be between 0 and 3.\n";
            return 1;
        }

        return writeFile(
            BRIGHTNESS_PATH,
            std::to_string(brightness)
        ) ? 0 : 1;
    }

    if (command == "rgb") {

        if (argc != 5) {
            std::cerr << "Usage: tufglow rgb <r> <g> <b>\n";
            return 1;
        }

        int r = std::atoi(argv[2]);
        int g = std::atoi(argv[3]);
        int b = std::atoi(argv[4]);

        if (r < 0 || r > 255 ||
            g < 0 || g > 255 ||
            b < 0 || b > 255) {

            std::cerr << "RGB values must be 0-255.\n";
            return 1;
        }

        /*
         * The exact mode string is currently unknown.
         *
         * Format exposed by your driver:
         *
         *   cmd mode red green blue speed
         *
         * We'll initially use "static".
         */
        std::string value =
            "cmd static " +
            std::to_string(r) + " " +
            std::to_string(g) + " " +
            std::to_string(b) +
            " 0";

        return writeFile(RGB_PATH, value) ? 0 : 1;
    }

    if (command == "red") {
        return writeFile(RGB_PATH, "cmd static 255 0 0 0") ? 0 : 1;
    }

    if (command == "green") {
        return writeFile(RGB_PATH, "cmd static 0 255 0 0") ? 0 : 1;
    }

    if (command == "blue") {
        return writeFile(RGB_PATH, "cmd static 0 0 255 0") ? 0 : 1;
    }

    if (command == "off") {
        return writeFile(BRIGHTNESS_PATH, "0") ? 0 : 1;
    }

    std::cerr << "Unknown command: " << command << '\n';
    usage();

    return 1;
}
