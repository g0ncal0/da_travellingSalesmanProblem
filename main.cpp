#include <iostream>
#include "Graph/Graph.h"
#include "Parser.h"
#include "Algorithms/Algorithms.h"
#include "Menu.h"
#include "Statistics.h"

int main() {

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
                cost = Algorithms::TSPGreedy(g);
                e= std::chrono::system_clock::now();
                Menu::printInfoPath(g, 0, cost);
                Menu::askOptimize(g, 0, cost);
                break;
            case 5:
                cost = Algorithms::TSPChristofides(g);
                Menu::printInfoPath(g, 0, cost);
                e= std::chrono::system_clock::now();
                break;
            case 6:
                Statistics::run();
                break;
            default:
                c = false;
                break;
        }

        auto d = e - s;
        std::cout << "\nThe duration of this algorithm was: " << std::chrono::duration<double, std::nano>(d).count() << " ns\n";

    }

    Menu::print("Thanks for using our program. This was developed by Filipe Correia, Gabriela Silva and Gonçalo Nunes.");

    /* INSTRUÇÕES PARA TIRAR TEMPOS
        auto s = std::chrono::system_clock::now();
        auto e = std::chrono::system_clock::now();
        auto d = e - s;
        std::cout << "PARSER TIME DURATION: " << std::chrono::duration<double, std::nano>(d).count() << " ns\n";
    */

    return 0;
}
