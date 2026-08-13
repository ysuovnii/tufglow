#pragma once

namespace Commands {

    void brightness(int level);

    void rgb(
        int mode,
        int red,
        int green,
        int blue,
        int speed
    );

    void help();
}
