#include <string>
#include <vector>
#include "test_framework.hpp"

// Helper function for theme validation
bool isValidTheme(const std::string& theme) {
    return theme == "light" || theme == "dark" || theme == "auto";
}

// Test valid theme names
TEST(Theme_ValidThemeNamesAccepted) {
    ASSERT_TRUE(isValidTheme("light"));
    ASSERT_TRUE(isValidTheme("dark"));
    ASSERT_TRUE(isValidTheme("auto"));
}

// Test invalid theme names rejected
TEST(Theme_InvalidThemeNamesRejected) {
    ASSERT_FALSE(isValidTheme("invalid"));
    ASSERT_FALSE(isValidTheme(""));
    ASSERT_FALSE(isValidTheme("LIGHT"));  // case-sensitive
}

// Test theme parsing edge cases
TEST(Theme_CaseSensitivity) {
    auto checkTheme = [](const std::string& theme) {
        return theme == "light" || theme == "dark";
    };
    
    ASSERT_FALSE(checkTheme("Light"));
    ASSERT_FALSE(checkTheme("DARK"));
    ASSERT_TRUE(checkTheme("light"));
}
