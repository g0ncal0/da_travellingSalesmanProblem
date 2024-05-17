#include <iostream>
#include "Graph/Graph.h"
#include "Parser.h"
#include "Algorithms/Algorithms.h"
#include "Menu.h"
#include "Statistics.h"

#include <chrono>
int ask_where_to_start()
{
    auto num=Menu::getNumber("In which vertex would you like to start? ");
   std::cout<<num;
    return num;
}

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
            case 3: {
             auto start=ask_where_to_start();
                cost = Algorithms::TSPwithTriangleApproximationPrim(g, start);
                e = std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                Menu::askOptimize(g, 0, cost);
            }   break;
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
                    int start=ask_where_to_start();
                        double dCost=0;

                    bool success= Algorithms::TSPrealWorldDFS(g, start, dCost);
                    e= std::chrono::system_clock::now();
                    std::cout<<(success?"Success!\n":"Failure!\n");
                    Menu::printInfoPath(g, start,dCost);
                    Menu::askOptimize(g, start, dCost);
                }
                break;
            case 7:
            {   int start=ask_where_to_start();

                double dCost=0;
                bool success= Algorithms::TSPrealWorldDijkstra(g, start, dCost);
                e= std::chrono::system_clock::now();
                std::cout<<(success?"Success!\n":"Failure!\n");
                Menu::printInfoPath(g, start,dCost);
                Menu::askOptimize(g, start, dCost);
            }
                break;
            case 8:
            {int start=ask_where_to_start();

                double dCost=0;
                bool success= Algorithms::HUBAlgorithm(g,start,dCost);
                e= std::chrono::system_clock::now();
                std::cout<<(success?"Success!\n":"Failure!\n");
                Menu::printInfoPath(g, start,dCost);
                Menu::askOptimize(g, start, dCost);
            }
                break;
            case 9:
            {
                int start=ask_where_to_start();

                double dCost=0;
                bool success= Algorithms::HUBAlgorithm2(g,start,dCost);
                std::cout<<(success?"Success!\n":"Failure!\n");
                Menu::printInfoPath(g, start,dCost);
                Menu::askOptimize(g, start, dCost);
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
