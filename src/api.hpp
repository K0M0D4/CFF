#pragma once

#include "color_manager.hpp"

namespace cff {
    class API {
    public:
        API();

        void Print(std::string val, Color fgCol = Color::RESET, Color bgCol = Color::RESET);
        void PrintError(std::string val);

    private:
        ColorManager m_colorManager;

    };
}