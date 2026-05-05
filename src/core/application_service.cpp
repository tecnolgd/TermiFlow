// Implementation of ApplicationService
// Handles core business logic and application orchestration
#include "../../include/application_service.hpp"
#include "../../include/launch.hpp"
#include "../../include/shortcuts.hpp"
#include "../../include/history.hpp"
#include "../../include/system_stats.hpp"
#include "../../include/command_handler.hpp"
#include <iostream>

ApplicationService::ApplicationService() 
    : configService("config/termiflow.conf") {
}

void ApplicationService::initialize() {
    // Load configuration and apply auto-theme if enabled
    if (shouldApplyAutoTheme()) {
        std::string theme = getCurrentTheme();
        changeTheme(theme);
    }
}

void ApplicationService::run() {
    try {
        while (true) {
            uiService.displayMainMenu();
            char choice = uiService.getMenuChoice();

            switch (choice) {
                case '1':
                    launchApp();
                    break;
                case '2':
                    shortcutInteractive();
                    break;
                case '3':
                    uiService.displayMessage(">> Not available for the current version. <<");
                    break;
                case '4':
                    handleThemeChange();
                    break;
                case '6':
                    historyInteractive();
                    break;
                case '7':
                    statsInteractive();
                    break;
                case '9':
                    cmdHandler();
                    break;
                case '0':
                    uiService.displayMessage("Application terminated..\nHave a nice day!");
                    return;
                default:
                    uiService.displayError("Invalid option! Try again.");
            }
        }
    } catch (const std::exception& e) {
        uiService.displayError(e.what());
    }
}

void ApplicationService::launchApp() {
    ::launchApp();
}

void ApplicationService::shortcutInteractive() {
    ::shortcutInteractive();
}



void ApplicationService::historyInteractive() {
    ::historyInteractive();
}

void ApplicationService::statsInteractive() {
    ::statsInteractive();
}

void ApplicationService::cmdHandler() {
    ::cmdHandler();
}

void ApplicationService::changeTheme(const std::string& theme) {
    ::changeTheme(theme);
}

void ApplicationService::handleThemeChange() {
    std::string theme = uiService.getThemeInput();
    changeTheme(theme);
    
    // Save to config
    configService.setValue("user_interface.theme", theme);
    configService.saveConfig();
    
    uiService.displaySuccess("Theme changed successfully!");
}

bool ApplicationService::shouldApplyAutoTheme() {
    return configService.getValue("behavior.auto_apply_theme", "true") == "true";
}

std::string ApplicationService::getCurrentTheme() {
    return configService.getValue("user_interface.theme", "dark");
}
