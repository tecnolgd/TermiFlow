// Implementation of ConfigService
// Handles all file I/O operations for configuration
#include "../../include/config_service.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

ConfigService::ConfigService(const std::string& path) : configPath(path) {
    loadConfig();
}

Config ConfigService::loadConfig() {
    config.values.clear();
    std::ifstream file(configPath);

    if (!file.is_open()) {
        // Set default config parameters
        config.values["user_interface.theme"] = "dark";
        config.values["user_interface.show_banner"] = "true";
        config.values["behavior.auto_apply_theme"] = "true";
        return config;
    }

    std::string line, section;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
        } else {
            auto pos = line.find('=');
            if (pos == std::string::npos) continue;

            std::string key = section + "." + line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config.values[key] = value;
        }
    }

    file.close();
    return config;
}

void ConfigService::saveConfig() {
    std::ofstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file for writing!\n";
        return;
    }

    // Write organized config sections
    file << "[user_interface]\n"
         << "theme=" << getValue("user_interface.theme", "dark") << "\n"
         << "show_banner=" << getValue("user_interface.show_banner", "true") << "\n\n"
         << "[behavior]\n"
         << "auto_apply_theme=" << getValue("behavior.auto_apply_theme", "true") << "\n";
    
    file.close();
}

std::string ConfigService::getValue(const std::string& key, const std::string& defaultValue) {
    auto it = config.values.find(key);
    if (it != config.values.end()) {
        return it->second;
    }
    return defaultValue;
}

void ConfigService::setValue(const std::string& key, const std::string& value) {
    config.values[key] = value;
}

Config ConfigService::getConfig() const {
    return config;
}
