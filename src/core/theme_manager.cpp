//theme_manager.cpp: Handles theme application logic only
// File I/O for theme persistence is handled by ConfigService
//theme_manager.cpp: Handles theme application logic only
#include "../../include/theme_manager.hpp"
#include <map>
#include <fstream>


std::map<std::string, std::string> themeMap;


void loadThemes() {
    themeMap.clear();
    
    
    #ifdef _WIN32
        themeMap["light"] = "color 70";
        themeMap["dark"] = "color 07";
        themeMap["hacker"] = "color 0A"; 
    #else
        themeMap["light"] = "\033[47;30m";
        themeMap["dark"] = "\033[40;37m";
        themeMap["hacker"] = "\033[40;32m"; 
    #endif

   
    std::ifstream infile("assets/textfiles/themes.txt");
    if(infile.is_open()) {
        std::string line;
        while(std::getline(infile, line)) {
            size_t eq = line.find('=');
            if(eq != std::string::npos) {
                std::string key = line.substr(0, eq);
                std::string value = line.substr(eq + 1);
                themeMap[key] = value;
            }
        }
    }
}

void changeTheme(std::string theme) {
   
    if(themeMap.empty()) {
        loadThemes();
    }

  
    auto it = themeMap.find(theme);
    
    if(it != themeMap.end()) {
     
        #ifdef _WIN32
            system("cls");
            system(it->second.c_str());
        #else
            std::cout << it->second;
        #endif
    } else {
        std::cerr << "Invalid theme: " << theme << "\n";
    }
}