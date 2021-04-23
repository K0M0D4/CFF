#include "color_manager.hpp"

namespace cff {
    ColorManager::ColorManager() {
#ifdef _WIN32
    std::system("setlocal");
#endif
    }

    void ColorManager::SetFgColor(Color col) {
        if(col == RESET) {
            std::cout << "\033[0m";
        } else if(col == BLACK) {
            std::cout << "\x1B[90m";
        } else if(col == RED) {
            std::cout << "\x1B[91m";
        } else if(col == GREEN) {
            std::cout << "\x1B[92m";
        } else if(col == YELLOW) {
            std::cout << "\x1B[93m";
        } else if(col == BLUE) {
            std::cout << "\x1B[94m";
        } else if(col == MAGENTA) {
            std::cout << "\x1B[95m";
        } else if(col == CYAN) {
            std::cout << "\x1B[96m";
        } else if(col == WHITE) {
            std::cout << "\x1B[97m";
        } else if(col == BLACK_DARK) {
            std::cout << "\x1B[30m";
        } else if(col == RED_DARK) {
            std::cout << "\x1B[31m";
        } else if(col == GREEN_DARK) {
            std::cout << "\x1B[32m";
        } else if(col == YELLOW_DARK) {
            std::cout << "\x1B[33m";
        } else if(col == BLUE_DARK) {
            std::cout << "\x1B[34m";
        } else if(col == MAGENTA_DARK) {
            std::cout << "\x1B[35m";
        } else if(col == CYAN_DARK) {
            std::cout << "\x1B[36m";
        } else if(col == WHITE_DARK) {
            std::cout << "\x1B[37m";
        }
    }

    void ColorManager::SetBgColor(Color col) {
        if(col == RESET) {
            std::cout << "\033[0m";
        } else if(col == BLACK) {
            std::cout << "\x1B[100m";
        } else if(col == RED) {
            std::cout << "\x1B[101m";
        } else if(col == GREEN) {
            std::cout << "\x1B[102m";
        } else if(col == YELLOW) {
            std::cout << "\x1B[103m";
        } else if(col == BLUE) {
            std::cout << "\x1B[104m";
        } else if(col == MAGENTA) {
            std::cout << "\x1B[105m";
        } else if(col == CYAN) {
            std::cout << "\x1B[106m";
        } else if(col == WHITE) {
            std::cout << "\x1B[107m";
        } else if(col == BLACK_DARK) {
            std::cout << "\x1B[40m";
        } else if(col == RED_DARK) {
            std::cout << "\x1B[41m";
        } else if(col == GREEN_DARK) {
            std::cout << "\x1B[42m";
        } else if(col == YELLOW_DARK) {
            std::cout << "\x1B[43m";
        } else if(col == BLUE_DARK) {
            std::cout << "\x1B[44m";
        } else if(col == MAGENTA_DARK) {
            std::cout << "\x1B[45m";
        } else if(col == CYAN_DARK) {
            std::cout << "\x1B[46m";
        } else if(col == WHITE_DARK) {
            std::cout << "\x1B[47m";
        }
    }

    void ColorManager::SetColors(Color fgCol, Color bgCol) {
        SetBgColor(bgCol);
        SetFgColor(fgCol);
    }
}