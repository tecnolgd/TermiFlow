//header file for theme_manager.cpp
#ifndef THEME_MANAGER_HPP
#define THEME_MANAGER_HPP

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

void changeTheme(std::string theme);
void changeTheme();
void saveThemeToConfig(const std::string & theme);

#endif
