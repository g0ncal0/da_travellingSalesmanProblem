#include <iostream>

#include "Graph/Graph.h"
#include <chrono>

int main() {



    Graph g = Graph(40000);

    g.setEdgeDistance(10000, 39000, 10.0, 1);
    g.setEdgeDistance(33999, 12999, 50, 0);
    g.setEdgeDistance(14000, 15000, 30, 1);
    g.setEdgeDistance(32543, 14192, 40, 0);
    g.setEdgeDistance(13323, 34324, 24, 1);
    std::cout << "configuration finished";

    auto start = std::chrono::system_clock::now();

    for(int i = 0; i < 100000; i++){
        g.getDistance(10000, 39000);
        g.getDistance(33999, 12999);
        g.getDistance(14000, 15000);
        g.getDistance(32543, 14192);
        g.getDistance(13323, 34324);
    }

    auto end = std::chrono::system_clock::now();

    auto diff = end - start;

    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::nano>(diff).count() << " ns";
    std::cout << "\nTIME DURATION: " << std::chrono::duration<double, std::milli>(diff).count() << " ms";

    return 0;
}
