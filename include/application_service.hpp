//header file for application_service.hpp
// Handles core business logic and application orchestration
#ifndef APPLICATION_SERVICE_H
#define APPLICATION_SERVICE_H

#include <string>
#include "config_service.hpp"
#include "ui_service.hpp"
#include "theme_manager.hpp"

class ApplicationService {
private:
    ConfigService configService;
    UIService uiService;
    
public:
    ApplicationService();
    
    // Application initialization
    void initialize();
    
    // Application control flow
    void run();
    
    // Feature handlers
    void handleThemeChange();
    
    // Utility
    bool shouldApplyAutoTheme();
    std::string getCurrentTheme();
};

#endif
