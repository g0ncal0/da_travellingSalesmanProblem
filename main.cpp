#include <iostream>
#include "Graph/Graph.h"
#include "Parser.h"
#include "Algorithms/Algorithms.h"
#include "Menu.h"
#include "Statistics.h"

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
        auto s = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock>  e;
        switch (i) {
            case 0:
                c = false;
                break;
            case 1:
                Menu::displayoptions();
                break;
            case 2:
                cost = Algorithms::TSPwithBacktracking(g);
                e= std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                break;
            case 3:
                cost = Algorithms::TSPwithTriangleApproximation(g, 0);
                e = std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                Menu::askOptimize(g, 0, cost);
                break;
            case 4:
            {
                int a = Algorithms::TSPGreedy(g, cost);
                e= std::chrono::system_clock::now();
                if(a == 0){
                    Menu::printInfoPath(g, 0, cost);
                    Menu::askOptimize(g, 0, cost);
                }

                break;
            }
            case 5:
                cost = Algorithms::TSPChristofides(g);
                e= std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                break;
            case 6:
                {
                    double dCost=0;
                    bool success= Algorithms::TSPrealWorldDFS(g, 0, dCost);
                    e= std::chrono::system_clock::now();
                    std::cout<<(success?"Success!\n":"Failure!\n");
                    Menu::printInfoPath(g, 0,dCost);
                    Menu::askOptimize(g, 0, dCost);
                }
                break;
            case 7:
            {   double dCost=0;
                bool success= Algorithms::TSPrealWorldDijkstra(g, 0, dCost);
                e= std::chrono::system_clock::now();
                std::cout<<(success?"Success!\n":"Failure!\n");
                Menu::printInfoPath(g, 0,dCost);
                Menu::askOptimize(g, 0, dCost);
            }
                break;
            case 8:
            {
                double dCost=0;
                bool success= Algorithms::HUBAlgorithm(g,0,dCost);
                e= std::chrono::system_clock::now();
                std::cout<<(success?"Success!\n":"Failure!\n");
                Menu::printInfoPath(g, 0,dCost);
                Menu::askOptimize(g, 0, dCost);
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
