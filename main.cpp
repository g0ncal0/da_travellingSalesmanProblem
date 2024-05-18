#include <iostream>
#include <chrono>
#include "Graph/Graph.h"
#include "Parser.h"
#include "Algorithms/Algorithms.h"
#include "Menu.h"
#include "Statistics.h"

#include <chrono>


int main() {

    // Insert this to run statistics
    // Statistics::run();
    // return 0;

    Graph* g = Parser::parse();


    Menu::print("\nWelcome to the TSP Program.");
    Menu::displayoptions();

    int c = true;
    float cost;




    while(c){
        int i = Menu::chooseoption();
        int v0;

        std::chrono::time_point<std::chrono::system_clock> s;
        std::chrono::time_point<std::chrono::system_clock>  e;
        switch (i) {
            case 0:
                c = false;
                break;
            case 1:
                Menu::displayoptions();
                break;
            case 2:
                v0 = Menu::choseInitVertex();
                s  = std::chrono::system_clock::now();
                cost = Algorithms::TSPwithBacktracking(g, v0);
                e= std::chrono::system_clock::now();
                Menu::printInfoPath(g, v0, cost);
                break;

            case 3: {
                v0 = Menu::choseInitVertex();
                s  = std::chrono::system_clock::now();
                cost = Algorithms::TSPwithTriangleApproximationPrim(g, v0);
                e = std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                Menu::askOptimize(g, 0, cost);
            }   break;

            case 4:
            {
                v0 = Menu::choseInitVertex();
                s  = std::chrono::system_clock::now();
                int a = Algorithms::TSPGreedy(g, cost, v0);
                e = std::chrono::system_clock::now();

                if(a == 0){
                    Menu::printInfoPath(g, v0, cost);
                    Menu::askOptimize(g, v0, cost);
                }
                break;
            }
            case 5:
                {
                    v0 = Menu::choseInitVertex();
                    double dCost=0;
                    s  = std::chrono::system_clock::now();
                    bool success= Algorithms::TSPrealWorldDFS(g, v0, dCost);
                    e= std::chrono::system_clock::now();
                    Menu::print((success?"Success!\n":"Failure!\n"));
                    Menu::printInfoPath(g, v0,dCost);
                    if(success) {
                        Menu::askOptimize(g, v0, dCost);
                    }
                }
                break;
            case 6:
            {
                v0 = Menu::choseInitVertex();
                double dCost=0;
                s  = std::chrono::system_clock::now();
                bool success= Algorithms::TSPrealWorldDijkstra(g, v0, dCost);
                e= std::chrono::system_clock::now();
                Menu::print((success?"Success!\n":"Failure!\n"));

                Menu::printInfoPath(g, v0, dCost);
                if(success) {
                    Menu::askOptimize(g, v0, dCost);
                }
            }
                break;
            case 7:
            {
                v0 = Menu::choseInitVertex();
                double dCost=0;
                s  = std::chrono::system_clock::now();
                bool success= Algorithms::HUBAlgorithm(g,v0,dCost);
                e= std::chrono::system_clock::now();
                Menu::print((success?"Success!\n":"Failure!\n"));
                Menu::printInfoPath(g, v0,dCost);
                if(success) {
                    Menu::askOptimize(g, v0, dCost);
                }
            }
                break;
            case 8:
            {
                v0 = Menu::choseInitVertex();
                double dCost=0;
                s  = std::chrono::system_clock::now();
                bool success= Algorithms::HUBAlgorithmSlowerButBetterSearch(g, v0, dCost);
                e= std::chrono::system_clock::now();
                Menu::print((success?"Success!\n":"Failure!\n"));
                Menu::printInfoPath(g, v0,dCost);
                if(success) {
                    Menu::askOptimize(g, v0, dCost);
                }
            }
                break;
            default:
                c = false;
                break;
        }

        if(i == 0) break;

        auto d = e - s;
        std::cout << "\nThe duration of this algorithm was: " << std::chrono::duration<double, std::nano>(d).count() << " ns\n";

    }

    Menu::print("Thanks for using our program. This was developed by Filipe Correia, Gabriela Silva and Gonçalo Nunes.");


    return 0;
}
