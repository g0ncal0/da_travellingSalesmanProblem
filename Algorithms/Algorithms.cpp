//
// Created by goncalo on 25-04-2024.
//

#include <climits>
#include "Algorithms.h"
#include <queue>

bool Algorithms::auxTSPwithBacktracking(Graph *g, int id, int &costToBeat, int numberVisited) {
    Vertex *v = g->getVertex(id);

    if (v->isVisited()) return false;

    v->setVisited(true);
    numberVisited++;

    bool isPossible = false;

    if (numberVisited == g->getVertexSet().size()) {
        int cost = g->getDistance(0, id);

        if (cost < costToBeat) {
            costToBeat = cost;
            v->setNextVertex(0);
            isPossible = true;
        }
    } else {
        for (int i = 0; i < g->getVertexSet().size(); i++) {
            int costEdge = g->getDistance(id, i);
            if (costEdge >= costToBeat) continue;
            int auxCostToBeat = costToBeat - costEdge;

            if (auxTSPwithBacktracking(g, i, auxCostToBeat, numberVisited)) {
                costToBeat = auxCostToBeat + costEdge;
                v->setNextVertex(i);
                isPossible = true;
            }
        }
    }

    v->setVisited(false);

    return isPossible;
}

int Algorithms::TSPwithBacktracking(Graph *g) {
    for (Vertex *v: g->getVertexSet()) v->setVisited(false);

    int cost = INT_MAX;

    if (auxTSPwithBacktracking(g, 0, cost, 0)) {
        return cost;
    }

    return -1;
}


#include <vector>
#include <algorithm>

//#include <pair>
void Algorithms::auxMST(Graph *g, Vertex *startVertex, std::map<Vertex *, std::vector<Vertex * >> &edges) {
    edges.clear();

    for (Vertex *other: g->getVertexSet()) {
        edges.emplace(other, std::vector<Vertex *>());
    }


    std::map<Vertex*,std::set<Vertex*>*> sets;
    for (Vertex* vert: g->getVertexSet())
    {
        sets[vert]=new std::set<Vertex*>({vert});
    }

    std::vector<std::pair<Vertex*,Vertex*>> edgeVec;

    for (Vertex* v1: g->getVertexSet())
    {
        for (Vertex* v2: g->getVertexSet())
        {
            if (v1->getId()<v2->getId())
            {
                edgeVec.emplace_back(v1,v2);
            }
        }
    }

    std::sort(edgeVec.begin(), edgeVec.end(),
              [&g](
                      const std::pair<Vertex *, Vertex *> &l,
                      const std::pair<Vertex *, Vertex *> &r
              ) {
                  return g->getDistance(l.first->getId(), l.second->getId()) <
                         g->getDistance(r.first->getId(), r.second->getId());
              });

    while(!edgeVec.empty()&&sets.size()!=1)
    {
        auto edge=edgeVec[0];
        edgeVec.erase(edgeVec.begin());
        if(sets[edge.first]!=sets[edge.second])
        {
            auto second= sets[edge.second];
            for (auto e: *second) {
                sets[e]=sets[edge.first];
                sets[edge.first]->emplace(e);
            }
            delete second;

            edges[edge.second].emplace_back(edge.first);
            edges[edge.first].emplace_back(edge.second);
        }
    }
    delete sets[startVertex];

    return;

}

//could be optimized to calculate the distance, rather than leaving it to the loop at the end
void Algorithms::auxTriangleApproximationDFS(Vertex *vert, std::map<Vertex *, std::vector<Vertex * >> &edges,
                                             Vertex *&currentLast) {

    vert->setVisited(true);
    currentLast->setNextVertex(vert->getId());
    currentLast=vert;
//for all mst edges, if destination not visited, destination.visit()
    for (Vertex *i: edges[vert]) {
        if (!i->isVisited()) {
            auxTriangleApproximationDFS(i, edges, currentLast);
        }

    }
}


float Algorithms::TSPwithTriangleApproximation(Graph *g, int startVertexId) {

    Vertex *vert = g->getVertex(startVertexId);
    if (!vert) {
        return -1;
    }


    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }
    std::map<Vertex *, std::vector<Vertex * >> edges;
    auxMST(g, vert, edges);

    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }
    Vertex *currentLast = vert;
    auxTriangleApproximationDFS(vert, edges, currentLast);


    Vertex *help = vert;
    float sum = 0;
    while (help != currentLast) {
   //     std::cout<<g->getDistance(help->getId(), help->getNextVertex())<<"\n";
        sum += g->getDistance(help->getId(), help->getNextVertex());
        help=g->getVertex(help->getNextVertex());
    }
    sum += g->getDistance(currentLast->getId(), vert->getId());
    return sum;

}