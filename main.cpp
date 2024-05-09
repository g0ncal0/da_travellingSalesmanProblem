#include <iostream>

#include "Graph/Graph.h"
#include "Parser.h"
#include <chrono>
#include "Algorithms/Algorithms.h"


int main() {



    auto s = std::chrono::system_clock::now();
    Graph* g = Parser::parse();
    auto e = std::chrono::system_clock::now();
    auto d = e - s;


    std::cout << "PARSER TIME DURATION: " << std::chrono::duration<double, std::nano>(d).count() << " ns\n";


    auto start = std::chrono::system_clock::now();
    std::cout << "O custo minimo é: " << Algorithms::TSPwithTriangleApproximation(g,0) << std::endl;

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
    auto end = std::chrono::system_clock::now();

    auto diff = end - start;

   // std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::nano>(diff).count() << " ns";
    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::milli>(diff).count() << " ms\n";



    start = std::chrono::system_clock::now();
    double res;
    std::cout <<"Existe? "<<(Algorithms::TSPrealWorld(g,0,res)?"Sim":"Nao")<< ". O custo minimo e: " << res << std::endl;

    end = std::chrono::system_clock::now();

    diff = end - start;

    //std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::nano>(diff).count() << " ns";
    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::milli>(diff).count() << " ms";

    return 0;
}
