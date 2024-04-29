#include <iostream>

#include "Graph/Graph.h"
#include "Algorithms/Algorithms.h"

using namespace std;

#include "Parser.h"

int main() {
    Graph* g = Parser::parse();

    int initialID=0;
    cout<<"\nTriangular Approximation:\n";
    cout << "O custo minimo 2 e: " << Algorithms::TSPwithTriangleApproximation(g,initialID) << endl;
    Vertex* v = g->getVertex(initialID);

    cout<< "O caminho e: "<<initialID;

    while (true) {
        if (v->getNextVertex()==-1)
        {
            cout << " -> " << initialID;
            break;
        }
        cout << " -> " << v->getNextVertex();
        v = g->getVertex(v->getNextVertex());
    }

/*
    for (int i = 0; i < g->getVertexSet().size(); i++) cout << "Id = " << g->getVertexSet()[i]->getId() << "   Lat = " << g->getVertexSet()[i]->getLat() << endl;

    for (int i = 0; i < g->getVertexSet().size(); i++) {
        for (int j = i + 1; j < g->getVertexSet().size(); j++) {
            cout << "i = " << i << "   j = " << j << "   dist = " << g->getDistance(i, j) << endl;
        }
    }
*/
    return 0;
}
