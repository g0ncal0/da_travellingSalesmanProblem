#include <iostream>

#include "Graph/Graph.h"
#include "Parser.h"
#include <chrono>
#include "Algorithms/Algorithms.h"


int main() {



    Graph* g = Parser::parse();

    auto start = std::chrono::system_clock::now();

    std::cout << "O custo mínimo é: " << Algorithms::TSPwithBacktracking(g) << std::endl;

/*
    for (int i = 0; i < g->getVertexSet().size(); i++) std::cout << "Id = " << g->getVertexSet()[i]->getId() << "   Lat = " << g->getVertexSet()[i]->getLat() << std::endl;

    for (int i = 0; i < g->getVertexSet().size(); i++) {
        for (int j = i + 1; j < g->getVertexSet().size(); j++) {
            std::cout << "i = " << i << "   j = " << j << "   dist = " << g->getDistance(i, j) << std::endl;
        }
    }
*/
    auto end = std::chrono::system_clock::now();

    auto diff = end - start;

    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::nano>(diff).count() << " ns";
    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::milli>(diff).count() << " ms";

    return 0;
}
