#include "api.hpp"

namespace cff {
    API::API() {

    }

    void API::Print(std::string val, Color fgCol, Color bgCol) {
        m_colorManager.SetColors(fgCol, bgCol);
        std::cout << val;
        m_colorManager.SetFgColor(Color::RESET);
    }

    void API::PrintError(std::string val) {
        m_colorManager.SetColors(Color::RED, Color::RESET);
        std::cout << "\n" << "ERROR: " << val << "\n";
        m_colorManager.SetFgColor(Color::RESET);
    }
}