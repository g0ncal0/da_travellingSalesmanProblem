#include <iostream>

#include "Graph/Graph.h"
#include "Parser.h"
#include "Algorithms/Algorithms.h"
#include "Menu.h"

int main() {



    Timer::start();
    Graph* g = Parser::parse();
    Timer::finish("Parser");

    bool c = true;
    while(c){
        Menu::displayoptions();
        int i = Menu::chooseoption();
        switch(i){
            case 0:

        }

    }

    std::cout << "O custo mínimo é: " << Algorithms::TSPwithBacktracking(g) << std::endl;

/*
    for (int i = 0; i < g->getVertexSet().size(); i++) std::cout << "Id = " << g->getVertexSet()[i]->getId() << "   Lat = " << g->getVertexSet()[i]->getLat() << std::endl;
    int initialID=0;
    std::cout<<"\nTriangular Approximation:\n";

    //std::cout << "O custo minimo 2 e: " << Algorithms::TSPwithTriangleApproximation(g,initialID) << std::endl;
    Vertex* v = g->getVertex(initialID);

    /*
    std::cout<< "O caminho e: "<<initialID;

    while (true) {

        std::cout << " -> " << v->getNextVertex();
        v = g->getVertex(v->getNextVertex());
        if(v->getId()==initialID) break;
    }


    for (int i = 0; i < g->getVertexSet().size(); i++) std::cout << "Id = " << g->getVertexSet()[i]->getId() << "   Lat = " << g->getVertexSet()[i]->getLat() << std::endl;

    for (int i = 0; i < g->getVertexSet().size(); i++) {
        for (int j = i + 1; j < g->getVertexSet().size(); j++) {
            std::cout << "i = " << i << "   j = " << j << "   dist = " << g->getDistance(i, j) << std::endl;
        }
    }
    */




    return 0;
}
