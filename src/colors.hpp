#pragma once

#include <iostream>
#include <cstdlib>

enum Color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

void SetColor(Color color) {
    std::string colVal;

    std::system("setlocal");

    switch(color) {
    case BLACK:
        colVal = "\x1B[30m";
    break;
    case RED:
        colVal = "\x1B[31m";
    break;
    case GREEN:
        colVal = "\x1B[32m";
    break;
    case YELLOW:
        colVal = "\x1B[33m";
    break;
    case BLUE:
        colVal = "\x1B[34m";
    break;
    case MAGENTA:
        colVal = "\x1B[35m";
    break;
    case CYAN:
        colVal = "\x1B[36m";
    break;
    case WHITE:
        colVal = "\x1B[37m";
    }
    std::cout << colVal;
}
