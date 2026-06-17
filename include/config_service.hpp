//header file for config_service.hpp
// Handles all file I/O operations for configuration
#ifndef CONFIG_SERVICE_HPP
#define CONFIG_SERVICE_HPP

#include <string>
#include <unordered_map>

struct Config {
    std::unordered_map<std::string, std::string> values;
};

class ConfigService {
private:
    Config config;
    std::string configPath;
    
public:
    ConfigService(const std::string& path = "config/termiflow.conf");
    
    // File I/O operations
    Config loadConfig();
    void saveConfig();
    
    // Config access
    std::string getValue(const std::string& key, const std::string& defaultValue = "");
    void setValue(const std::string& key, const std::string& value);
    
    // Config getters
    Config getConfig() const;
};

#endif
