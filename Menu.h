//
// Created by Filipe Correia on 02/03/2024.
//

#ifndef WM_MENU_H
#define WM_MENU_H

#include <string>
#include <iostream>
#include <vector>
#include "Graph/Graph.h"
#include <fstream>


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

};


#endif //WM_MENU_H
