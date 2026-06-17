//header file for history.cpp
#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
#include <vector>

class history {
public:
    void load(); //load commands
    void save(); //save commands
    history();
    void add(const std::string& cmd); //add command to history
    void list(); //list the past commands
    std::string get(int index);
    void historyClear();

private:
    std::string filePath;
    std::vector<std::string> cmdEntries; //vector to store commands or instructions typed in the command-line interface(menu choice: 8)
};

void historyInteractive(); //for interactive/ menu mode history display operation.

#endif