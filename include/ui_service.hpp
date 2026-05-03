//header file for ui_service.hpp
// Handles all user interaction and presentation logic
#ifndef UI_SERVICE_H
#define UI_SERVICE_H

#include <string>

class UIService {
public:
    // Menu operations
    void displayMainMenu();
    char getMenuChoice();
    
    // Theme UI
    std::string getThemeInput();
    void displayThemeChangeMessage();
    
    // Generic message display
    void displayMessage(const std::string& message);
    void displayError(const std::string& error);
    void displaySuccess(const std::string& message);
    
    // Input operations
    std::string getUserInput(const std::string& prompt);
};

#endif
