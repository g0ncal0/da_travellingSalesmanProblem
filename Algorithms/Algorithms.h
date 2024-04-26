//
// Created by goncalo on 25-04-2024.
//

#ifndef DAPROJECT2_ALGORITHMS_H
#define DAPROJECT2_ALGORITHMS_H

#include "../Graph/Graph.h"
#include <set>
#include <map>
class Algorithms {
    static bool auxTSPwithBacktracking(Graph* g, int id, int& costToBeat, int numberVisited);
    static void auxTriangleApproximationDFS(Vertex* vert, std::map<Vertex*,std::vector<Vertex*>>& edges,Vertex*& currentLast);
    static void auxMST(Graph* g,Vertex* startVertex,std::map<Vertex*,std::vector<Vertex*>>& edges);
public:
    static int TSPwithBacktracking(Graph* g);

    static float TSPwithTriangleApproximation(Graph* g, int startVertexId);
};


#endif //DAPROJECT2_ALGORITHMS_H
