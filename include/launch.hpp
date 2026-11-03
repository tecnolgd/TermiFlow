//header file for launch.cpp
#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP
#include <string>

void launchApp();
// Launches the given app. Throws std::runtime_error if the app is unknown
// or if the launch command reports a failure.
void launchApp(std::string appName);

// Returns the platform-specific shell command used to launch appName.
// Throws std::runtime_error for unknown apps.
std::string buildLaunchCommand(const std::string& appName);

// Interprets the raw value returned by system().
// Returns true only if the shell ran and the command exited with status 0.
bool isLaunchSuccessful(int status);

#endif
