//header file for system_stats.cpp
#ifndef SYSTEM_STATS_HPP
#define SYSTEM_STATS_HPP

#include <string>

class SystemStats {
public:
    static std::string getCPU_Usage();
    static std::string getMemoryUsage();
    static std::string getUptime();
};

void statsInteractive();
#endif

