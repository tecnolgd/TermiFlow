//launch application module: to launch apps via the system() call

#include <iostream>
#include "../../include/launch.hpp"
#include "../../include/shortcuts.hpp"
#include <regex>
//interactive mode launch app function
void launchApp() {
    shortcuts s;
    std::string command;
    std::string appName;
    std::cout<<"Enter App to be launched: "; 
    std::getline(std::cin, appName);
    if (s.exists(appName)) { //checks for shortcut if used e.g., 'launch c'
        std::string app = s.getValue(appName);
        launchApp(app);
    }
    else {
        launchApp(appName);
    }
}
bool isValidAppName(const std::string& appName) {
    // केवल सुरक्षित कैरेक्टर्स की अनुमति दें (अल्फा-न्यूमेरिक)
    const std::regex pattern("^[a-zA-Z0-9._-]+$");
    return std::regex_match(appName, pattern);
}

void launchApp(std::string appName) {
    if (!isValidAppName(appName)) {
        std::cout << "Security Alert: Invalid characters detected in input!" << std::endl;
        return; 
    }
    std::string command;
    
#ifdef _WIN32
    if (appName == "chrome") {
        command = "start chrome";
    }
    else if (appName == "code") {
        command = "code";
    }
    else if (appName == "notepad") {
        command = "notepad";
    }
    else if(appName == "youtube"){
        command = "start https://www.youtube.com";
    }
    else {
        std::cout << "Unknown app: " << appName << "\n";
        return;
    }
    std::cout << "Launching " << appName << "...\n";
    system(command.c_str());
#else
    // Linux commands
    if (appName == "chrome") {
        command = "google-chrome &";
    }
    else if (appName == "code") {
        command = "code &";
    }
    else if (appName == "notepad") {
        command = "gedit &";
    }
    else if(appName == "youtube"){
        command = "xdg-open https://www.youtube.com &";
    }
    else {
        std::cout << "Unknown app: " << appName << "\n";
        return;
    }
    std::cout << "Launching " << appName << "...\n";
    system(command.c_str());
#endif
    
}