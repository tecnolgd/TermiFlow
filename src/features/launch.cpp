//launch application module: to launch apps via the system() call

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "../../include/launch.hpp"
#include "../../include/shortcuts.hpp"

//interactive mode launch app function
void launchApp() {
    shortcuts s;
    std::string appName;
    std::cout << "Enter App to be launched: ";
    std::getline(std::cin, appName);
    if (s.exists(appName)) { //checks for shortcut if used e.g., 'launch c'
        std::string app = s.getValue(appName);
        std::cout << "Launching " << app << "...\n";
        launchApp(app);
    }
    else {
        std::cout << "Launching " << appName << "...\n";
        launchApp(appName);
    }
}

void launchApp(std::string appName) {
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
        throw std::runtime_error("Unknown app: " + appName);
    }
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
        throw std::runtime_error("Unknown app: " + appName);
    }
    system(command.c_str());
#endif
}
