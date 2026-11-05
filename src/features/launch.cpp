//launch application module: to launch apps via the system() call

#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include "../../include/launch.hpp"
#include "../../include/shortcuts.hpp"

#ifndef _WIN32
#include <sys/wait.h>
#endif

//interactive mode launch app function
void launchApp() {
    shortcuts s;
    std::string appName;
    std::cout << "Enter App to be launched: ";
    std::getline(std::cin, appName);

    try{

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
    catch (const std::exception& e){
        std::cerr << e.what() << "\n";
        return;
    }
}

#ifndef _WIN32
// Builds a Linux command that fails with exit code 127 when the executable is
// not installed, and otherwise starts the app in the background.
static std::string backgroundCommand(const std::string& executable, const std::string& args = "") {
    std::string run = args.empty() ? executable : executable + " " + args;
    return "command -v " + executable + " >/dev/null 2>&1 || exit 127; " + run + " &";
}
#endif

std::string buildLaunchCommand(const std::string& appName) {
#ifdef _WIN32
    // Windows commands
    if (appName == "chrome") {
        return "start chrome";
    }
    else if (appName == "code") {
        return "code";
    }
    else if (appName == "notepad") {
        return "notepad";
    }
    else if(appName == "youtube"){
        return "start https://www.youtube.com";
    }
#else
    // Linux commands
    if (appName == "chrome") {
        return backgroundCommand("google-chrome");
    }
    else if (appName == "code") {
        return backgroundCommand("code");
    }
    else if (appName == "notepad") {
        return backgroundCommand("gedit");
    }
    else if(appName == "youtube"){
        return backgroundCommand("xdg-open", "https://www.youtube.com");
    }
#endif
    throw std::runtime_error("Unknown app: " + appName);
}

bool isLaunchSuccessful(int status) {
    if (status == -1) { // the shell itself could not be started
        return false;
    }
#ifdef _WIN32
    return status == 0;
#else
    return WIFEXITED(status) && WEXITSTATUS(status) == 0;
#endif
}

void launchApp(std::string appName) {
    std::string command = buildLaunchCommand(appName);
    int status = system(command.c_str());

    if (isLaunchSuccessful(status)) {
        return;
    }
    if (status == -1) {
        throw std::runtime_error("Failed to launch " + appName + ": could not start the system shell.");
    }

    int exitCode = status;
#ifndef _WIN32
    if (WIFEXITED(status)) {
        exitCode = WEXITSTATUS(status);
        if (exitCode == 127) {
            throw std::runtime_error("Failed to launch " + appName + ": application not found. Is it installed?");
        }
    }
#endif
    throw std::runtime_error("Failed to launch " + appName + " (exit code " + std::to_string(exitCode) + ").");
}
