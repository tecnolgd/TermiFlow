//command_handler.cpp: handles command-line interface.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../../include/command_handler.hpp"
#include "../../include/launch.hpp"
#include "../../include/theme_manager.hpp"
#include "../../include/shortcuts.hpp"
#include "../../include/history.hpp"
#include "../../include/system_stats.hpp"

void cmdHandler() {
    shortcuts s;
    history h;
    std::string input;
    
    while (true) {
        std::cout << "\n>>>";
        std::getline(std::cin, input);//reads the entire string
        h.add(input); //history addition
        std::stringstream ss(input); // need explanation!! 
        std::vector<std::string> tokens; //vector to store all seperate words of the input string
        std::string token; //token: single word in the input string

        while (ss >> token) { //needs explanation !
            tokens.push_back(token);
        }

        if (tokens.empty()){
            continue;
        }
        std::string command = tokens[0];

        if (command == "launch") {
            if (tokens.size() == 2 && s.exists(tokens[1])) { //checks for shortcut if used e.g., 'launch c'
                std::string app = s.getValue(tokens[1]);
                launchApp(app);
            } else if (tokens.size() == 2) { //for no shortcuts, i.e., if default 'launch chrome'
                launchApp(tokens[1]);
            } else {
                std::cout << "Usage: launch <app> or launch <shortcut>" << std::endl;
            }
        }
        else if (command == "theme") {
            if (tokens.size() >= 2) {
                changeTheme(tokens[1]);
            } else {
                std::cout << "Usage: theme <light/dark>" << std::endl;
            }
        }
        else if (command == "shortcut") {
            if (tokens.size() >= 2) {
                std::string subcmd = tokens[1];
                if (subcmd == "add" && tokens.size() == 4) {   //e.g., shortcut(0) add(1) chrome(2) c(3), token size=4.
                    s.add(tokens[3], tokens[2]);   //'ch' and 'chrome' are passed as parameters
                } else if (subcmd == "remove" && tokens.size() == 3) {
                    s.remove(tokens[2]);    //remove 'c' from list of shortcuts mapped to 'chrome' 
                } else if (subcmd == "list") {
                    s.list();
                }else {
                    std::cout << "Invalid shortcut command! Check 'help'\n";
                }
            } 
            else {
                std::cout << "Usage: shortcut <add/remove/list>  <shortcut>" << std::endl;
            }
        }
        else if(command == "history"){
            if (tokens.size() == 2 && tokens[1] == "clear") {
                h.historyClear();//for clearing the vector cmdEntries.
            } 
            else if(tokens.size()==2 && tokens[1] == "list") {
                h.list();
            }
            else if(tokens.size() == 3 && tokens[1] == "goto"){ 
               try {//try catch block for exceptions and error handling.
                    int index = std::stoi(tokens[2]); //convertion of string to integer.
                    std::string cmd = h.get(index); //return command e.g., 'launch chrome'
                    if (!cmd.empty()) {
                        std::cout << "Command at index" << index << ": " << cmd << "\n";
                        // Optionally, execute the command:
                        // processCommand(cmd);
                        } else {
                        std::cout << "No command at that index.\n";
                        }
            } catch (const std::exception& e) { //exception handling
                std::cout << "Invalid index.\n";
            }
                // work on this, make a new fuction cmdHandler(std::string); for the goto command which executes the command.
            }
            else {
                std::cout<<"Invalid history method!. Try again.";
            }
        }
        else if (command == "stats") {
                statsInteractive();
                } 
        else if (command == "exit" || command == "quit") {
            std::cout << "Command - handler terminated !\n";
            return;
        }
       else if (command == "help") {
    std::cout << "\n\t-- Available commands --\n";
    std::cout << "launch <app>                    : Launch an application\n";
    std::cout << "shortcut <add/remove/list>      : Manage shortcuts\n";
    std::cout << "tasks                           : View running tasks\n";
    std::cout << "theme <light/dark>              : Change theme\n";
    std::cout << "config                          : Config settings\n";
    std::cout << "history <clear/list/goto>       : View history commands\n";
    std::cout << "stats                           : View system stats\n";
    std::cout << "sm                              : Session manager\n";
    std::cout << "exit/quit                       : Exit\n";
}
        else {
            std::cout << "Unknown command. Type 'help'.\n";
        }
    }
}

           
