//
// Created by Filipe Correia on 05/05/2024.
//

#ifndef DAPROJECT2_MENU_H
#define DAPROJECT2_MENU_H


#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class Graph;

class Menu {
private:
public:
    static std::vector<std::string> getOptions();
    static void print(std::string t);
    static void printList(std::vector<std::string> v);
    static void displayoptions();
    static int getNumber(std::string text);
    static int chooseoption();
    static std::string getInput(std::string text);
    static void printInfoPath(Graph* g, int v0, float cost);
    static void printInfoPathByEdges(Graph* g, float cost);
};


#endif //DAPROJECT2_MENU_H