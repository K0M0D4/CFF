#pragma once

#include <iostream>

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

#if defined(_WIN32)
    #include <windows.h>

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    void SetColor(Color color) {
        switch(color) {
        case BLACK:
            SetConsoleTextAttribute(hOut, 0);
        break;
        case RED:
            SetConsoleTextAttribute(hOut, FOREGROUND_RED);
        break;
        case GREEN:
            SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
        break;
        case YELLOW:
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN);
        break;
        case BLUE:
            SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
        break;
        case MAGENTA:
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE);
        break;
        case CYAN:
            SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
        case WHITE:
            SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
#elif defined(__linux__)
    void SetColor(Color color) {
        std::string colVal;

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
#endif