//shortcuts.cpp file: for creating and managing user-defined shortcuts (for launch commands as of now)
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "../../include/shortcuts.hpp"

void shortcuts::add(const std::string& shortcut, const std::string& app){
    shortMap[shortcut] = app; //store shortMap[shortcut] = app
    save();
}

void shortcuts::add(){
    int appChoice;
    std::string appShortcut;
    std::cout<<"\t-- Available apps for launch --\n";
    std::cout<<"1: chrome\t2. code\t3: notepad\t4: youtube\n";
    std::cout<<"Select the app to create shortcut for(choose 1/2/3): ";
    while (!(std::cin >> appChoice)){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore();
    std::cout << "Create a custom shortcut: ";
    std::getline(std::cin, appShortcut);

    try{
        switch(appChoice){
            case 1: add(appShortcut, "chrome");
                    break;
            case 2: add(appShortcut, "code");
                    break;
            case 3: add(appShortcut, "notepad");
                    break;
            case 4: add(appShortcut, "youtube");
                    break;
            default: std::cout<<"Invalid!. The app you want seems to be missing.\n";
        }
    } catch (const std::exception& e){
        std::cerr << e.what() << "\n";
        return;
    }

}

void shortcuts::remove(){
    std::string appShortcut; //variable to store shortcut to be deleted
    list();
    std::cout<<"Enter shortcut to be removed: ";
    std::cin>>appShortcut;
    std::cin.ignore(); // Clear the input buffer
    remove(appShortcut);
}

void shortcuts::remove(const std::string& shortcut){
    auto it = shortMap.find(shortcut);
    if (it == shortMap.end()) {
        throw std::runtime_error("Shortcut not found: " + shortcut);
    }
    shortMap.erase(it); //erase the shortcut from the map
    save();
}

void shortcuts::save(){
    std::ofstream outfile("assets/textfiles/shortcut_det.txt");

    if(! outfile.is_open()){
        return;
    }
    for(auto& p : shortMap) { //for each loop
        outfile << p.first << "=" << p.second << "\n";
    }
}

void shortcuts::list(){
    std::cout << "Registered shortcuts:\n";
    for(auto& p : shortMap) { //for each loop
        std::cout<<"* "<< p.first << " --> " << p.second << "\n";
    }
}

void shortcuts::load() {
    shortMap.clear();
    std::ifstream infile("assets/textfiles/shortcut_det.txt");
    if(! infile.is_open()) {
        return;  // File doesn't exist yet, that's okay
    }
    std::string line;
    while (std::getline(infile, line)) {
        size_t eq = line.find('=');
        if (eq != std::string::npos) {
            std::string key = line.substr(0, eq);
            std::string value = line.substr(eq + 1);
            shortMap[key] = value;
        }
    }
}

// Constructor: load shortcuts from file
shortcuts::shortcuts() { //needs explanation !!
    load();
}

bool shortcuts::exists(const std::string& shortcut){
    return (shortMap.find(shortcut) != shortMap.end());
}
std::string shortcuts::getValue(const std::string& shortcut){
    auto it = shortMap.find(shortcut);
    if(it != shortMap.end()){
        return it->second;
    }
    return "";  //returns empty string if shortcut not found
}
//interactive mode function which handles all shortcut functions.
void shortcutInteractive(){
    shortcuts s;
    std::string shortcutMethod;
    std::cout<<"\t-- Available shortcut methods --\n";
    std::cout<<"<add>\t <remove>\t<list>\n";
    std::cout<<"Enter method to be used: ";
    std::cin>>shortcutMethod;
    std::cin.ignore(); // Clear the input buffer
                
    if(shortcutMethod == "add"){
        s.add();
    }
    else if(shortcutMethod == "remove"){
        s.remove();
    }
    else if(shortcutMethod == "list"){
        s.list();
    }
    else{
        std::cout<<"Invalid shortcut method!.";
    }
}

