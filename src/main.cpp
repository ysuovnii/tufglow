#include "cmd/cmd.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Commands::help();
        return 1;
    }

    std::string command = argv[1];

    if (command == "brightness") {
        if (argc != 3) {
            std::cerr << "Usage: tufglow brightness <level>\n";
            return 1;
        }

        int level = std::stoi(argv[2]);

        Commands::brightness(level);
    }

    else if (command == "rgb") {

        if (argc != 7) {
            std::cerr
                << "Usage: tufglow rgb <mode> <red> <green> <blue> <speed>\n";
            return 1;
        }

        int mode  = std::stoi(argv[2]);
        int red   = std::stoi(argv[3]);
        int green = std::stoi(argv[4]);
        int blue  = std::stoi(argv[5]);
        int speed = std::stoi(argv[6]);

        Commands::rgb(
            mode,
            red,
            green,
            blue,
            speed
        );
    }

    else if (command == "help") {
        Commands::help();
    }

    else {
        std::cerr << "Unknown command: " << command << '\n';
        Commands::help();
        return 1;
    }

    return 0;
}
