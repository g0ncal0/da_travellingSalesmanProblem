#include <iostream>

#include "Graph/Graph.h"

int main() {
    Graph g = Graph(4);

    g.setEdgeDistance(0, 1, 10.0, 1);
    g.setEdgeDistance(0, 2, 50, 0);
    g.setEdgeDistance(1, 2, 30, 1);
    g.setEdgeDistance(3, 1, 40, 0);
    g.setEdgeDistance(3, 2, 24, 1);
    g.printDebug();

    return 0;
}
