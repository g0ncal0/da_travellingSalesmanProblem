//
// Created by Filipe Correia on 05/05/2024.


#include "Menu.h"
#include "Graph/Graph.h"

// Implementation inspired on the last project "Water Management" by Filipe Correia, Gabriela Silva and Gonçalo Nunes.

std::vector<std::string> Menu::getOptions(){
    return {"Exit Program", "Repeat Instructions", "Backtracking Algorithm (It yields the optimal solution but is infeasible for big instances)", "Triangle Approximation Algorithm", "3º Algoritmo", "4º Algoritmo", "Algoritmo com DFS (muitos false negatives)", "Algorithmo com Dijkstra (muitos false negatives)","Strange Hub Algorithm", "Strange Hub Algorithm 2"};
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
    if(cost == -1){return;}
    std::cout << "O custo minimo é: " << cost << std::endl;

    Vertex* v = g->getVertex(v0);

    int ctn = getNumber("Do you want to see the path? (insert 0 to no)");
    if(!ctn){
        return;
    }
    Menu::print("=============");
    std::cout << "Entre parênteses está o custo do segmento respetivo." << std::endl;
    std::cout << "O caminho é 0";
    while (true) {
        std::cout << " ->(" << g->getDistance(v->getId(), v->getNextVertex()) << ")";
        std::cout << "-> " << v->getNextVertex();
        v = g->getVertex(v->getNextVertex());
        if(v== nullptr){break;}
        if (v->getId() == v0) break;
    }
    Menu::print("\n=============");

}



void Menu::askOptimize(Graph* g, int v0, float cost) {
    std::string answer;

    answer=getInput("\nDo you want to optimize this result?\nYour answer: (y / n) ");

    if (answer == "y") {
        cost = Algorithms::twoOpt(g, v0, cost);

        std::cout << "\nThese are the optimized results:\n";
        Menu::printInfoPath(g, 0, cost);
    }
}
