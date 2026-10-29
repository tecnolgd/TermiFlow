//system stats such as CPU usage, Memory usage, and Uptime is displayed using this file
//Check the entire flow of the program and understand it and test for various test cases.
#include "../../include/system_stats.hpp"
#include <sstream>
#include <iostream>
#include <system_error>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/sysinfo.h>
#endif

#ifdef _WIN32
MEMORYSTATUSEX getSystemInfo() {
    MEMORYSTATUSEX memInfo{};
    memInfo.dwLength = sizeof(memInfo);

    if (!GlobalMemoryStatusEx(&memInfo)){
        const DWORD err = GetLastError();
        throw std::system_error(
            static_cast<int>(err),
            std::generic_category(),
            "MemoryStatusEx"
        );
    }

    return memInfo;
}
#else
struct sysinfo getSystemInfo() {
struct sysinfo info{};
    
    if (sysinfo(&info) == -1) {
        const int err = errno;
        throw std::system_error(
            err,
            std::generic_category(),
            "sysinfo"
        );
    }

    return info;
}
#endif

std::string SystemStats::getCPU_Usage() {
    // Placeholder for now (fix this after beta release)
    return "CPU: N/A";
}

std::string SystemStats::getMemoryUsage() {
#ifdef _WIN32
    MEMORYSTATUSEX memInfo{};
     try {
        memInfo = getSystemInfo();
    } catch (const std::system_error& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Error code: " << e.code().value() << "\n";
        return "MEMORYSTATUSEX FAILED! See the error log.";
    }

    long long total = memInfo.ullTotalPhys / (1024 * 1024);
    long long used  = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024);

    std::ostringstream out;
    out << "Memory: " << used << " / " << total << " MB\t [" << (used/float(total))*100 << "% ]";
    return out.str();
#else
    struct sysinfo info{};
    
    try {
        info = getSystemInfo();
    } catch (const std::system_error& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Error code: " << e.code().value() << "\n";
        return "SYSINFO FAILED! See the error log.";
    }

    long long total = static_cast<long long>(info.totalram) * info.mem_unit / (1024 * 1024);
    long long used = static_cast<long long>(info.totalram - info.freeram) * info.mem_unit / (1024 * 1024);

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
    struct sysinfo info{};
    
    try {
        info = getSystemInfo();
    } catch (const std::system_error& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Error code: " << e.code().value() << "\n";
        return "SYSINFO FAILED! See the error log.";
    }
    
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
