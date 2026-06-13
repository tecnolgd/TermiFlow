#include <iostream>
#include "system_stats.hpp"
#include "test_framework.hpp"

// Test that getCPU_Usage returns a non-empty string
TEST(SystemStats_GetCPUUsageReturnsString) {
    SystemStats stats;
    std::string cpu = stats.getCPU_Usage();
    ASSERT_FALSE(cpu.empty());
    ASSERT_NE(cpu.find("CPU:"), std::string::npos);
}

// Test that getMemoryUsage returns a properly formatted string
TEST(SystemStats_GetMemoryUsageReturnsValidString) {
    SystemStats stats;
    std::string memory = stats.getMemoryUsage();
    ASSERT_FALSE(memory.empty());
    ASSERT_NE(memory.find("Memory:"), std::string::npos);
    ASSERT_NE(memory.find("MB"), std::string::npos);
    ASSERT_NE(memory.find("%"), std::string::npos);
}

// Test that getUptime returns a properly formatted string
TEST(SystemStats_GetUptimeReturnsValidString) {
    SystemStats stats;
    std::string uptime = stats.getUptime();
    ASSERT_FALSE(uptime.empty());
    ASSERT_NE(uptime.find("Uptime:"), std::string::npos);
    ASSERT_NE(uptime.find("h"), std::string::npos);
}

// Test that statsInteractive doesn't crash
TEST(SystemStats_StatsInteractiveDoesNotCrash) {
    // Redirect cout to suppress output
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(nullptr);
    
    ASSERT_NO_THROW(statsInteractive());
    
    std::cout.rdbuf(old_cout);
}
