//main.cpp: Application entry point - clean controller
// Delegates to ApplicationService for all business logic and orchestration
#include <iostream>
#include "../include/application_service.hpp"

int main() {
    try {
        // Initialize application service with all dependencies
        ApplicationService app;
        
        // Initialize application (load config, apply themes, etc.)
        app.initialize();
        
        // Run main application loop
        app.run();
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }
}
