//header file for shortcuts.cpp 
#ifndef SHORTCUTS_HPP
#define SHORTCUTS_HPP

#include <string>
#include <sstream>
#include <unordered_map>

class shortcuts {
    private:
    std::unordered_map<std::string, std::string> shortMap;
    std::string filepath;

    public:
    void add(const std::string& key, const std::string& value ); //key: default app_name; value: user's new shortcut
    void remove(const std::string& key);
    void save();
    void list();
    void load();
    shortcuts();
    bool exists(const std::string& value);
    std::string getValue(const std::string& key);

    void add(); //here add() and remove() --> used for interactive/ menu mode.
    void remove();
    


};

void shortcutInteractive(); //for interactive/ menu mode shortcuts operation.

#endif
