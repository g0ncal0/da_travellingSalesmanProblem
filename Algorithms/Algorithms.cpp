//
// Created by goncalo on 25-04-2024.
//

#include <climits>
#include "Algorithms.h"

bool Algorithms::auxTSPwithBacktracking(Graph* g, int id, int& costToBeat, int numberVisited) {
    Vertex* v = g->getVertex(id);

    if (v->isVisited()) return false;

    v->setVisited(true);
    numberVisited++;

    bool isPossible = false;

    if (numberVisited == g->getVertexSet().size()) {
        int cost = g->getDistance(0, id);

        if (cost < costToBeat) {
            costToBeat = cost;
            isPossible = true;
        }
    }

    else {
        for (int i = 0; i < g->getVertexSet().size(); i++) {
            int costEdge = g->getDistance(id, i);
            if (costEdge >= costToBeat) continue;
            int auxCostToBeat = costToBeat - costEdge;

            if (auxTSPwithBacktracking(g, i, auxCostToBeat, numberVisited)) {
                costToBeat = auxCostToBeat + costEdge;
                isPossible = true;
            }
        }
    }

    v->setVisited(false);

    return isPossible;
}

int Algorithms::TSPwithBacktracking(Graph* g) {
    for (Vertex* v : g->getVertexSet()) v->setVisited(false);

    int cost = INT_MAX;

    if (auxTSPwithBacktracking(g, 0, cost, 0)) {
        return cost;
    }

    return -1;
}