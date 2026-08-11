#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

static const string RGB_PATH =
    "/sys/class/leds/asus::kbd_backlight/kbd_rgb_mode";

static const string BRIGHTNESS_PATH =
    "/sys/class/leds/asus::kbd_backlight/brightness";


bool writeFile(const string& path, const string& value)
{
    ofstream file(path);

    if (!file) {
        cerr << "Failed to open: " << path << '\n';
        cerr << "Try running the command with sudo.\n";
        return false;
    }

    file << value;

    if (!file) {
        cerr << "Failed to write to: " << path << '\n';
        return false;
    }

    return true;
}


void usage()
{
    cout <<
        "\n"
        "tufglow - ASUS TUF RGB controller\n"
        "\n"
        "Usage:\n"
        "  red\n"
        "  green\n"
        "  blue\n"
        "  off\n"
        "  brightness <0-3>\n"
        "  rgb <r> <g> <b>\n"
        "  quit\n"
        "\n";
}


int main()
{
    string line;

    while (true) {

        cout << "tufglow ❯ ";

        if (!getline(cin, line)) break;

        if (line.empty()) continue;

        istringstream iss(line);
        vector<string> args;

        string token;

        while (iss >> token)
            args.push_back(token);

        if (args.empty())
            continue;

        string command = args[0];

        if (command == "quit" || command == "exit") break;

        else if (command == "brightness") {
            if (args.size() != 2) {
                cerr << "Usage: brightness <0-3>\n";
                continue;
            }

            try {

                int brightness = stoi(args[1]);

                if (brightness < 0 || brightness > 3) {
                    cerr << "Brightness must be between 0 and 3.\n";
                    continue;
                }

                writeFile(
                    BRIGHTNESS_PATH,
                    to_string(brightness)
                );

            } catch (...) {
                cerr << "Brightness must be a number between 0 and 3.\n";
            }
        }

        else if (command == "rgb") {

            if (args.size() != 4) {
                cerr << "Usage: rgb <r> <g> <b>\n";
                continue;
            }

            try {

                int r = stoi(args[1]);
                int g = stoi(args[2]);
                int b = stoi(args[3]);

                if (r < 0 || r > 255 ||
                    g < 0 || g > 255 ||
                    b < 0 || b > 255) {

                    cerr << "RGB values must be 0-255.\n";
                    continue;
                }

                string value =
                    "cmd static " +
                    to_string(r) + " " +
                    to_string(g) + " " +
                    to_string(b) +
                    " 0";

                writeFile(RGB_PATH, value);

            } catch (...) {
                cerr << "RGB values must be numbers between 0 and 255.\n";
            }
        }

        else if (command == "red") {

            if (args.size() != 1) {
                cerr << "Usage: red\n";
                continue;
            }

            writeFile(
                RGB_PATH,
                "cmd static 255 0 0 0"
            );
        }

        else if (command == "green") {

            if (args.size() != 1) {
                cerr << "Usage: green\n";
                continue;
            }

            writeFile(
                RGB_PATH,
                "cmd static 0 255 0 0"
            );
        }

        else if (command == "blue") {

            if (args.size() != 1) {
                cerr << "Usage: blue\n";
                continue;
            }

            writeFile(
                RGB_PATH,
                "cmd static 0 0 255 0"
            );
        }

        else if (command == "off") {

            if (args.size() != 1) {
                cerr << "Usage: off\n";
                continue;
            }

            writeFile(
                BRIGHTNESS_PATH,
                "0"
            );
        }

        else {
            cerr << "Unknown command: " << command << '\n';
            usage();
        }
    }

    return 0;
}
