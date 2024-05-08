//
// Created by Filipe Correia on 05/05/2024.
//

#ifndef DAPROJECT2_MENU_H
#define DAPROJECT2_MENU_H


#include <string>
#include <iostream>
#include <vector>
#include <chrono>

class Menu {
private:
public:
    static std::vector<std::string> getOptions();
    static void print(std::string t);
    static void printList(std::vector<std::string> v);
    static void displayoptions();
    static int getNumber();
    static int chooseoption();
};

class Timer {
private:
    static std::chrono::time_point<std::chrono::system_clock> starttime;

public:
    static void start(){
        starttime = std::chrono::system_clock::now();
        Menu::print("Started timing.");
    }
    static void finish(std::string task){
        auto e = std::chrono::system_clock::now();
        auto d = e - starttime;

        std::cout << "The duration of " << task << " was: " << std::chrono::duration<double, std::milli>(d).count() << " ms";
    }

};


#endif //DAPROJECT2_MENU_H
