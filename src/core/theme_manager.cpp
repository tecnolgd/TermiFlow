//theme_manager.cpp: Handles theme application logic only
// File I/O for theme persistence is handled by ConfigService
#include "../../include/theme_manager.hpp"
#include <stdexcept>

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
            std::cout << "\033[47;30m"; // white background with black text
        }
        else if (theme == "dark") {
            std::cout << "\033[40;37m"; // black background with white text / default theme
        }
        else {
            throw std::invalid_argument("Invalid theme: " + theme);
        }
    #endif
}

