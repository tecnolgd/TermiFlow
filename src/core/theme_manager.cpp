//theme_manager.cpp: Handles theme application logic only
// File I/O for theme persistence is handled by ConfigService
#include "../../include/theme_manager.hpp"

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
            std::cerr << "Invalid theme: " << theme << "\n";
        }
    #else
        if (theme == "light") {
            std::cout << "\033[47;30m"; // white background with black text
        }
        else if (theme == "dark") {
            std::cout << "\033[40;37m"; // black background with white text / default theme
        }
        else {
            std::cerr << "Invalid theme: " << theme << "\n";
        }
    #endif
}

// Interactive mode - UI is delegated to UIService in the new architecture
// This function is kept for backward compatibility but should use UIService
void changeTheme() {
    std::string themeType;
    std::cout << "Enter theme: (dark / light) :";
    std::cin >> themeType;
    changeTheme(themeType);
}

// DEPRECATED: File I/O is now handled by ConfigService
// This function is removed - use ConfigService::saveConfig() instead
void saveThemeToConfig(const std::string& theme) {
    std::cerr << "WARNING: saveThemeToConfig() is deprecated. Use ConfigService for file I/O.\n";
}
