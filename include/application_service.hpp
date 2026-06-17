//header file for application_service.hpp
// Handles core business logic and application orchestration
#ifndef APPLICATION_SERVICE_HPP
#define APPLICATION_SERVICE_HPP

#include <string>
#include "config_service.hpp"
#include "ui_service.hpp"
#include "theme_manager.hpp"

class ApplicationService {
private:
    ConfigService configService;
    UIService uiService;
    
    // Feature handlers (delegate to modules)
    void launchApp();
    void shortcutInteractive();
    void sessionManager();
    void handleThemeChange();
    void historyInteractive();
    void statsInteractive();
    void cmdHandler();
    void changeTheme(const std::string& theme);
    
public:
    ApplicationService();
    
    // Application initialization
    void initialize();
    
    // Application control flow
    void run();
    
    // Utility
    bool shouldApplyAutoTheme();
    std::string getCurrentTheme();
};

#endif