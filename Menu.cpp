//
// Created by Filipe Correia on 05/05/2024.
//

#include "Menu.h"

// Implementation inspired on the last project "Water Management" by Filipe Correia, Gabriela Silva and Gonçalo Nunes.

std::vector<std::string> Menu::getOptions(){
    return {"Finish", "TSP With BackTracking", "TSP With Triangle Approximation", ""};
}
void Menu::print(std::string t){
    std::cout << t << "\n";
}
void Menu::printList(std::vector<std::string> v){
    for(int i = 0; i < v.size(); i++){
        std::cout << i << " : " << v[i];
    }
}
void Menu::displayoptions(){
    print("Options:");
    printList(getOptions());
}
int Menu::getNumber() {
    int n = -1;
    while (n != -1) {
        try {
            std::cin >> n;
        } catch (...) {
            std::cout << "error. try again";
        }
    }
    return n;
}
int Menu::chooseoption(){
    int choosen = getOptions().size() + 1;
    while(choosen >= getOptions().size() || choosen < 0){
        choosen = getNumber();
    }
    return choosen;
}