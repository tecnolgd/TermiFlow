#include <stdexcept>
#include <string>
#include "launch.hpp"
#include "test_framework.hpp"

#ifndef _WIN32
#include <cstdlib>
#endif

// Unknown apps must be rejected before any command is run
TEST(Launch_UnknownAppThrows) {
    ASSERT_THROW(buildLaunchCommand("definitely-not-an-app"));
}

// Known apps map to a launch command
TEST(Launch_KnownAppsBuildCommand) {
    ASSERT_NO_THROW(buildLaunchCommand("chrome"));
    ASSERT_NO_THROW(buildLaunchCommand("code"));
    ASSERT_NO_THROW(buildLaunchCommand("notepad"));
    ASSERT_NO_THROW(buildLaunchCommand("youtube"));
}

// system() returning -1 means the shell could not be started
TEST(Launch_ShellFailureIsReported) {
    ASSERT_FALSE(isLaunchSuccessful(-1));
}

#ifndef _WIN32
// Linux commands check that the executable exists before backgrounding it
TEST(Launch_LinuxCommandChecksExecutable) {
    std::string command = buildLaunchCommand("chrome");
    ASSERT_TRUE(command.find("command -v google-chrome") != std::string::npos);
    ASSERT_TRUE(command.find("exit 127") != std::string::npos);
}

// Real exit statuses from the shell are interpreted correctly
TEST(Launch_InterpretsShellExitStatus) {
    ASSERT_TRUE(isLaunchSuccessful(std::system("exit 0")));
    ASSERT_FALSE(isLaunchSuccessful(std::system("exit 1")));
    ASSERT_FALSE(isLaunchSuccessful(std::system("command -v termiflow-missing-app >/dev/null 2>&1 || exit 127; termiflow-missing-app &")));
}
#endif
