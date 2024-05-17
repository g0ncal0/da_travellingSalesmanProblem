//
// Created by Filipe Correia on 14/05/2024.
//

#include "Statistics.h"
#include "Parser.h"
#include <iostream>
#include "Algorithms/Algorithms.h"
#include <chrono>

void Statistics::run(){

    std::cout << "\nGREEDY\n";

    for(int i = 1; i <= 12; i++) {
        Graph *g = Parser::parseExtraFullyConnectedWithId(i);
        auto s = std::chrono::system_clock::now();
        float r;
        std::cout << Algorithms::TSPGreedy(g, r) << ", ";
        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        //std::cout << std::chrono::duration<double, std::micro>(d).count() << ", ";
    }
    std::cout << "\nAPPROXIMATION\n";

    for(int i = 1; i <= 7; i++) {
        Graph *g = Parser::parseExtraFullyConnectedWithId(i);

        auto s = std::chrono::system_clock::now();
        std::cout << Algorithms::TSPwithTriangleApproximation(g, 0) << ", ";
        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        //std::cout << std::chrono::duration<double, std::micro>(d).count() << ", ";
    }
    std::cout << "\nHUBAlgorithm\n";

    for(int i = 4; i <= 12; i++) {
        Graph *g = Parser::parseExtraFullyConnectedWithId(i);
        auto s = std::chrono::system_clock::now();
        double dCost=0;
        Algorithms::HUBAlgorithm(g,0,dCost);
        std::cout << dCost << ", ";
        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        //std::cout << std::chrono::duration<double, std::micro>(d).count() << ", ";
    }

    std::cout << "\nGREEDY COM 2-OPT\n";

    for(int i = 1; i <= 12; i++) {
        Graph *g = Parser::parseExtraFullyConnectedWithId(i);
        auto s = std::chrono::system_clock::now();
        float cost;
        Algorithms::TSPGreedy(g, cost);
        std::cout << Algorithms::twoOpt(g, 0, cost) << ", ";

        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        //std::cout << std::chrono::duration<double, std::micro>(d).count() << ", ";
    }

    std::cout << "\nDijkstra\n";

    for(int i = 1; i <= 12; i++) {
        Graph *g = Parser::parseExtraFullyConnectedWithId(i);
        auto s = std::chrono::system_clock::now();
        double dCost=0;
        Algorithms::TSPrealWorldDijkstra(g, 0, dCost);
        std::cout << dCost << ", ";
        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        //std::cout << std::chrono::duration<double, std::micro>(d).count() << ", ";
    }


}