//system stats such as CPU usage, Memory usage, and Uptime is displayed using this file
//Check the entire flow of the program and understand it and test for various test cases.
#include "../../include/system_stats.hpp"
#include <sstream>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/sysinfo.h>
#endif

std::string SystemStats::getCPU_Usage() {
    // Placeholder for now (fix this after beta release)
    return "CPU: N/A";
}

std::string SystemStats::getMemoryUsage() {
#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(memInfo);
    GlobalMemoryStatusEx(&memInfo);

    long long total = memInfo.ullTotalPhys / (1024 * 1024);
    long long used  = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024);

    std::ostringstream out;
    out << "Memory: " << used << " / " << total << " MB\t [" << (used/float(total))*100 << "% ]";
    return out.str();
#else
    struct sysinfo info;
    sysinfo(&info);
    
    long long total = info.totalram / (1024 * 1024);
    long long used = (info.totalram - info.freeram) / (1024 * 1024);
    
    std::ostringstream out;
    out << "Memory: " << used << " / " << total << " MB\t [" << (used/float(total))*100 << "% ]";
    return out.str();
#endif
}

std::string SystemStats::getUptime() {
#ifdef _WIN32
    DWORD uptimeMs = GetTickCount();
    int seconds = uptimeMs / 1000.0;
    int minutes = seconds / 60.0;
    int hours = minutes / 60.0;

    std::ostringstream outputString;
    outputString << "Uptime: " << hours << "h " << minutes << "m";
    return outputString.str();
#else
    struct sysinfo info;
    sysinfo(&info);
    
    long uptime_seconds = info.uptime;
    int hours = uptime_seconds / 3600;
    int minutes = (uptime_seconds % 3600) / 60;
    
    std::ostringstream outputString;
    outputString << "Uptime: " << hours << "h " << minutes << "m";
    return outputString.str();
#endif
}

//fuction which displays all of the three details
void statsInteractive(){
    std::cout<<"Stats loading...\n";
    std::cout<<">>>>>>>>>>>>>>\n";
    std::string cpuDetails= SystemStats::getCPU_Usage();
    std::string memoryDetails= SystemStats::getMemoryUsage();
    std::string uptimeDetails= SystemStats::getUptime();
    std::cout<<cpuDetails<<"\n"<<memoryDetails<<"\n"<<uptimeDetails<<"\n";
}