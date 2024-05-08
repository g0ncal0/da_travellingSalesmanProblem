//
// Created by Filipe Correia on 05/05/2024.


#include "Menu.h"
#include "Graph/Graph.h"

// Implementation inspired on the last project "Water Management" by Filipe Correia, Gabriela Silva and Gonçalo Nunes.

std::vector<std::string> Menu::getOptions(){
    return {"Exit Program", "Repeat Instructions", "Backtracking Algorithm (It yields the optimal solution but is infeasible for big instances)", "Triangle Approximation Algorithm", "3º Algoritmo", "4º Algoritmo"};
}

void Menu::print(std::string t){
    std::cout << t << "\n";
}
void Menu::printList(std::vector<std::string> v){
    for(int i = 0; i < v.size(); i++){
        std::cout << i << " : " << v[i] << "\n";
    }
}
void Menu::displayoptions(){
    print("Options:");
    printList(getOptions());
}

int Menu::getNumber(std::string text) {
    int n = -1;
    while (n == -1) {
        try {
            std::cout << text;
            std::cin >> n;
        } catch (...) {
            std::cout << "error. try again";
        }
    }
    return n;
}
int Menu::chooseoption(){

    int choosen = (int) Menu::getOptions().size() + 1;
    while(choosen >= Menu::getOptions().size()  || choosen < 0){
        choosen = getNumber("Your option: ");
        print("");
    }
    return choosen;
}


std::string Menu::getInput(std::string text){
    print(text);
    std::string input;
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    getline(std::cin, input);
    return input;
}

void Menu::printInfoPath(Graph* g, int v0, float cost) {
    std::cout << "O custo minimo 2 é: " << cost << std::endl;

    Vertex* v = g->getVertex(v0);

    std::cout << "Entre parênteses está o custo do segmento respetivo." << std::endl;
    std::cout << "O caminho é 0";
    while (true) {
        std::cout << " ->(" << g->getDistance(v->getId(), v->getNextVertex()) << ")";
        std::cout << "-> " << v->getNextVertex();
        v = g->getVertex(v->getNextVertex());
        if (v->getId() == 0) break;
    }

    std::cout << std::endl << std::endl;
}

void Menu::printInfoPathByEdges(Graph* g, float cost){
    std::cout << "O custo minimo é: " << cost << std::endl;
}
