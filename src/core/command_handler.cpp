//command_handler.cpp: handles command-line interface.
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
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
        std::getline(std::cin, input);
        h.add(input);
        std::stringstream ss(input);
        std::vector<std::string> tokens;
        std::string token;

        while (ss >> token) {
            tokens.push_back(token);
        }

        if (tokens.empty()) continue;

        std::string command = tokens[0];

        try {
            if (command == "launch") {
                if (tokens.size() == 2 && s.exists(tokens[1])) {
                    launchApp(s.getValue(tokens[1]));
                } else if (tokens.size() == 2) {
                    launchApp(tokens[1]);
                } else {
                    throw std::invalid_argument("Usage: launch <app> or launch <shortcut>");
                }
            }
            else if (command == "theme") {
                if (tokens.size() >= 2) {
                    changeTheme(tokens[1]);
                } else {
                    throw std::invalid_argument("Usage: theme <light/dark>");
                }
            }
            else if (command == "shortcut") {
                if (tokens.size() >= 2) {
                    std::string subcmd = tokens[1];
                    if (subcmd == "add" && tokens.size() == 4) {
                        s.add(tokens[3], tokens[2]);
                    } else if (subcmd == "remove" && tokens.size() == 3) {
                        s.remove(tokens[2]);
                    } else if (subcmd == "list") {
                        s.list();
                    } else {
                        throw std::invalid_argument("Invalid shortcut command! Check 'help'");
                    }
                } else {
                    throw std::invalid_argument("Usage: shortcut <add/remove/list> <shortcut>");
                }
            }
            else if (command == "history") {
                if (tokens.size() == 2 && tokens[1] == "clear") {
                    h.historyClear();
                } else if (tokens.size() == 2 && tokens[1] == "list") {
                    h.list();
                } else if (tokens.size() == 3 && tokens[1] == "goto") {
                    int index = std::stoi(tokens[2]);
                    std::string cmd = h.get(index);
                    if (!cmd.empty()) {
                        std::cout << "Command at index " << index << ": " << cmd << "\n";
                    } else {
                        throw std::out_of_range("No command at that index.");
                    }
                } else {
                    throw std::invalid_argument("Invalid history method! Try again.");
                }
            }
            else if (command == "stats") {
                statsInteractive();
            }
            else if (command == "exit" || command == "quit") {
                std::cout << "Command-handler terminated!\n";
                return;
            }
            else if (command == "help") {
                std::cout << "\n\t-- Available commands --\n";
                std::cout << "launch <app>                    : Launch an application\n";
                std::cout << "shortcut <add/remove/list>      : Manage shortcuts\n";
                std::cout << "theme <light/dark>              : Change theme\n";
                std::cout << "history <clear/list/goto>       : Check History\n";
                std::cout << "stats                           : View system stats\n";
                std::cout << "exit/quit                       : Exit\n";
            }
            else {
                throw std::invalid_argument("Unknown command. Type 'help'.");
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Unexpected error: " << e.what() << "\n";
        }
    }
}
