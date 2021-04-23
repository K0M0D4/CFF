#pragma once

#include <iostream>
#include <cstdlib>

namespace cff {
    enum Color {
        RESET,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        BLACK_DARK,
        RED_DARK,
        GREEN_DARK,
        YELLOW_DARK,
        BLUE_DARK,
        MAGENTA_DARK,
        CYAN_DARK,
        WHITE_DARK
    };

    class ColorManager {
    public:
        ColorManager();

        void SetFgColor(Color col);
        void SetBgColor(Color col);
        void SetColors(Color fgCol, Color bgCol);
    };
}
