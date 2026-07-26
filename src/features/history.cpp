//history.cpp: handle operations of saving command_handler command history.
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "../../include/history.hpp"

//go through and understand all of these functions and what they do. write comments once its clear to follow through.
void history::load() {
    cmdEntries.clear();
    std::ifstream infile("assets/textfiles/history.txt");
    if(!infile.is_open()){
        return;
    }
    
    std::string line;
    while(std::getline(infile, line)) {
        cmdEntries.push_back(line);
    }
}

void history::save() {
    std::ofstream outfile("assets/textfiles/history.txt");

    if(! outfile.is_open()){
        std::cerr <<"Warning: Could not open history file for writing\n";
        return ;
    }
    for(auto& e : cmdEntries) { //for each loop
        outfile << e << "\n";
    }
}

history::history(){
    load();
}
void history::add(const std::string& cmd) {
    cmdEntries.push_back(cmd); //push cmd(command entered) to vector cmdEntries
    save();
}

void history::list(){
    int indexNo = 1;
    std::cout<<"\t--- + --- cmd history --- + --- \n";
    for(auto& e : cmdEntries) { //for each loop
        std::cout << indexNo++ << ". " << e << "\n"; //feature: add latest command indicating label.
    }
}

std::string history::get(int index){
    if(index < 1 || index > static_cast<int>(cmdEntries.size())){
        throw std::out_of_range("Command not found at index: " + std::to_string(index));
    }
    return cmdEntries[index - 1];
}

void history::historyClear(){
    cmdEntries.clear(); //to clear contents of vector cmdEntries.
    save();
}

//interactive mode history operations handler function
void historyInteractive(){ 
    history h; //'h' : object of class 'history'
    char ch;
    std::string historyMethod;
    int cmdIndex;
    std::cout<<"\t-- Available history methods --\n";
    std::cout<<"<list>\t <goto>\t <clear>\n";
    std::cout<<"Enter method to be used: ";
    std::cin>>historyMethod;

    if(historyMethod == "list"){
        h.list();
    }
    else if(historyMethod == "goto"){ //yet to implement
        std::cout<<"Enter index no of the command you want: ";
        std::cin>>cmdIndex;
        try {//try catch block for exceptions and error handling.
            std::string cmd = h.get(cmdIndex); //return command e.g., 'launch chrome'
            if (!cmd.empty()) {
                std::cout << "Command at index "<< cmdIndex << ": " << cmd << "\n";
                // Optionally, execute the command:
                // processCommand(cmd);
            } else {
                std::cout << "No command at that index.\n";
            }
        } catch (const std::exception& e) { //exception handling
                std::cout << "Invalid index.\n";
            }
    }
    else if(historyMethod == "clear"){
       std::cout<<"Danger: All cmd history will be wiped out!. Press 'y' to continue, 'n' to exit cleaning operation.";
       std::cin>>ch;
       if(ch == 'y' || ch == 'Y'){
            h.historyClear();
        }
       else if(ch == 'n' || ch == 'N'){
            std::cout<<"History cleaning process terminated.\n";
            return;
        }
        else{
            std::cout<<"Error!. The application is confused with your intentions. Try again.\n";
        }
    }
    else{
        std::cout<<"Invalid history method!.\n";
    }
}
    
