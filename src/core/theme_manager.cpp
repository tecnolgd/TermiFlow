//theme_manager.cpp: Handles theme application logic only
// File I/O for theme persistence is handled by ConfigService
#include "../../include/theme_manager.hpp"
#include <stdexcept>

#ifndef _WIN32
#include <sys/ioctl.h>
#include <unistd.h>

static bool getTerminalSize(int& rows, int& cols) {
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_row == 0 || ws.ws_col == 0) {
        return false;
    }
    rows = ws.ws_row;
    cols = ws.ws_col;
    return true;
}

static void applyAnsiTheme(const std::string& colorCode) {
    std::cout << colorCode;

    int rows = 0;
    int cols = 0;
    if (!getTerminalSize(rows, cols)) {
        std::cout << "\033[2J\033[H";
        std::cout.flush();
        return;
    }

    std::cout << "\033[H";
    std::string blankLine(cols, ' ');
    for (int r = 0; r < rows; ++r) {
        std::cout << blankLine;
        if (r < rows - 1) {
            std::cout << '\n';
        }
    }
    std::cout << "\033[H";
    std::cout.flush();
}
#else
static void applyAnsiTheme(const std::string& colorCode) {
    (void)colorCode;
}
#endif

void changeTheme(std::string theme) {
    // Apply theme to terminal (business logic only)
    #ifdef _WIN32
        if (theme == "light") {
            system("cls");
            system("color 70"); // white background with black text
        }
        else if (theme == "dark") {
            system("cls");
            system("color 07"); // black background with white text / default theme
        }
        else {
            throw std::invalid_argument("Invalid theme: " + theme);
        }
    #else
        if (theme == "light") {
            applyAnsiTheme("\033[47;30m"); // white background with black text
        }
        else if (theme == "dark") {
            applyAnsiTheme("\033[40;37m"); // black background with white text / default theme
        }
        else {
            std::cerr << "Error: Invalid theme!\n";
        }
    #endif
}

