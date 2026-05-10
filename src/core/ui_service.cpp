// Implementation of UIService
// Handles all user interaction and presentation logic
#include "../../include/ui_service.hpp"
#include <iostream>
#include <cctype>

void UIService::displayMainMenu() {
    std::cout << "\n\t--- TermiFlow (beta) ---\n";
    std::cout << "1. Launch an application\n";
    std::cout << "2. Manage shortcuts\n";
    std::cout << "3. View running tasks (unavailable)\n";
    std::cout << "4. Change theme\n";
    std::cout << "5. Config settings (unavailable)\n";
    std::cout << "6. Check History\n";
    std::cout << "7. View system stats\n";
    std::cout << "8. Session manager (unavailable)\n";
}

char UIService::getMenuChoice() {
    std::string choiceStr;
    char choice;
    std::string buffer;

    do {
        std::cout << "Enter your choice: ";
        std::cin >> choiceStr;
        
        if (choiceStr.length() == 1 && isdigit(choiceStr[0])) {
            choice = choiceStr[0];
        } else {
            std::cout << "Error! Invalid choice format. (Use digits from 0->9)\n";
            choice = ' ';
        }
    } while (!isdigit(choice));

    std::getline(std::cin, buffer);
    return choice;
}

std::string UIService::getThemeInput() {
    std::string theme;
    std::cout << "Enter theme (dark / light): ";
    std::cin >> theme;
    return theme;
}

void UIService::displayThemeChangeMessage() {
    std::cout << "Theme changed successfully!\n";
}

void UIService::displayMessage(const std::string& message) {
    std::cout << message << "\n";
}

void UIService::displayError(const std::string& error) {
    std::cerr << "Error: " << error << "\n";
}

void UIService::displaySuccess(const std::string& message) {
    std::cout << "Success: " << message << "\n";
}

std::string UIService::getUserInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}
