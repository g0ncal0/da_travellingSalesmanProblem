//
// Created by goncalo on 25-04-2024.
//

#include <climits>
#include "Algorithms.h"
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <limits>
#include <stack>

bool Algorithms::auxTSPwithBacktracking(Graph *g, int id, float &costToBeat, int numberVisited) {
    Vertex *v = g->getVertex(id);

    if (v->isVisited()) return false;

    v->setVisited(true);
    numberVisited++;

    bool isPossible = false;

    if (numberVisited == g->getNoVertexes()) {
        float cost = g->getDistance(0, id);

        if ((cost < costToBeat) && (cost > 0)) {
            costToBeat = cost;
            v->setNextVertex(0);
            isPossible = true;
        }
    } else {
        for (int i = 0; i < g->getNoVertexes(); i++) {
            float costEdge = g->getDistance(id, i);
            if (costEdge == 0) continue;
            if (costEdge >= costToBeat) continue;
            float auxCostToBeat = costToBeat - costEdge;

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

float Algorithms::TSPwithBacktracking(Graph *g) {
    for (Vertex *v: g->getVertexSet()) v->setVisited(false);

    float cost = INT_MAX;

    if (auxTSPwithBacktracking(g, 0, cost, 0)) {
        return cost;
    }

    return -1;
}



void Algorithms::auxMST(Graph *g, Vertex *startVertex, std::unordered_map<Vertex *, std::vector<Vertex * >> &edges) {
    edges.clear();

    for (Vertex *other: g->getVertexSet()) {
        edges.emplace(other, std::vector<Vertex *>());
    }


    std::unordered_map<Vertex*,std::unordered_set<Vertex*>*> sets;
    for (Vertex* vert: g->getVertexSet())
    {
        sets[vert]=new std::unordered_set<Vertex*>({vert});
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
float Algorithms::auxTriangleApproximationDFS(Graph *g, Vertex *vert, std::unordered_map<Vertex *, std::vector<Vertex * >> &edges,
                                             Vertex *&currentLast) {

    vert->setVisited(true);
    currentLast->setNextVertex(vert->getId());
    float sum=g->getDistance(currentLast->getId(),vert->getId());
    currentLast=vert;

//for all mst edges, if destination not visited, destination.visit()
    for (Vertex *i: edges[vert]) {
        if (!i->isVisited()) {
             sum+= auxTriangleApproximationDFS(g,i, edges, currentLast);
        }
    }
    return sum;
}


float Algorithms::TSPwithTriangleApproximation(Graph *g, int startVertexId) {

    Vertex *vert = g->getVertex(startVertexId);
    if (!vert) {
        return -1;
    }


    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }
    std::unordered_map<Vertex *, std::vector<Vertex * >> edges;
    auxMST(g, vert, edges);

    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }

    Vertex *currentLast = vert;
    float sum=auxTriangleApproximationDFS(g, vert, edges, currentLast);

    currentLast->setNextVertex(startVertexId);
    sum+=g->getDistance(currentLast->getId(),vert->getId());

    return sum;

}

#define VERY_STUPID_TEST_HEURISTIC


#ifdef VERY_STUPID_TEST_HEURISTIC
bool TSPrealWorldRec(Graph* g, Vertex* currentVertex,int depth,int startVertex,double &length)
{
    depth++;
    currentVertex->setVisited(true);
    if (depth==g->getNoVertexes())
    {
        if(g->isEdgeInGraph(currentVertex->getId(),startVertex))
        {
            currentVertex->setNextVertex(startVertex);
            length+=g->getDistance(currentVertex->getId(),startVertex);
            return true;
        }
        return false;
    }

    Vertex* minVert=0;
    float minLength=std::numeric_limits<float>::max();
    for (Vertex* other:g->getVertexSet()) {
        float dis=g->getDistance(currentVertex->getId(),other->getId());
        if (!other->isVisited()&&g->isEdgeInGraph(currentVertex->getId(),other->getId())&&dis<minLength)
        {
            minLength=dis;
            minVert=other;
        }
    }
    if (minVert)
    {
            length+=minLength;
            currentVertex->setNextVertex(minVert->getId());
            return TSPrealWorldRec(g,minVert,depth,startVertex,length);

    }else
    {
        return false;
    }

}
#endif

bool Algorithms::TSPrealWorld(Graph* g, int startVertex, double &resultLength)
{
   resultLength=0;
   Vertex* vert=g->getVertex(startVertex);
   for (Vertex* v:g->getVertexSet()) {
    v->setVisited(false);
    v->setNextVertex(0);
   }
#ifdef VERY_STUPID_TEST_HEURISTIC
return TSPrealWorldRec(g,vert, 0,startVertex,resultLength);
#endif
}



/**
 * Gives an approximated result to TSP problem by sorting edges and choosing by that order
 * @param g
 * @return
 */
float Algorithms::TSPbyEdgeOrdering(Graph* g){


    std::vector<edgeInfo> sortedEdges = g->getEdgesSorted(); // sort the edges

    int count = g->getNoVertexes(); // how many edges to find before ending
    int index = 0;
    // Cycle through the edges
        // get current edge: name it "E"
        // if the vertexes of E have not yet been visited, add them as visited and mark the edge as used.
        // if the vertexes have been used just once max!, add them too
        // if vertexes have been used twice, ignore

    g->initializeEdgesUsed(); // for edges
    g->initializeVisited(); // for vertexes

    float res = 0;

    while(count != 0){
        if(index >= (g->getNoVertexes() * (g->getNoVertexes() - 1)) / 2){
            return res;
        }
        edgeInfo currentEdge = sortedEdges[index]; // E
        if(currentEdge.distance == 0){
            index++;
            continue;
        }
        if(g->complexGetVisited(currentEdge.e) != 2 && g->complexGetVisited(currentEdge.s) != 2){
            g->complexSetVisited(currentEdge.e, g->complexGetVisited(currentEdge.e) + 1);
            g->complexSetVisited(currentEdge.s, g->complexGetVisited(currentEdge.s) + 1);
            g->setEdgeUsed(currentEdge.e, currentEdge.s,true);
            res = res + currentEdge.distance;
            std::cout << "(" << currentEdge.s << "," << currentEdge.e << ")";
            count--;
        }
        index++;
    }

    std::cout << res;
    return res;
}

std::vector<Vertex*> getOddVertexesInTree(const std::unordered_map<Vertex *, std::vector<Vertex * >>& edges) {
    std::vector<Vertex*> oddVertexes;

    for (const auto& pair: edges) {
        if (pair.second.size() % 2) oddVertexes.push_back(pair.first);
    }

    return oddVertexes;
}

float Algorithms::TSPChristofides(Graph* g) {
    Vertex *vert = g->getVertex(0);
    if (!vert) {
        return -1;
    }

    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }

    std::unordered_map<Vertex *, std::vector<Vertex * >> edges;
    auxMST(g, vert, edges);

    for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }

    std::vector<Vertex*> oddVertexes = getOddVertexesInTree(edges);



    return 0.0;
}

void swap(std::vector<int>& path, int a, int b) {
    std::stack<int> aux;

    int size = path.size();
    int index;
    bool toChange = false;

    for (int i = 0; i < size; i++) {
        if (path[i] == a) {
            toChange = true;
            index = i;
        }

        if (toChange) {
            aux.push(path[i]);
        }

        if (path[i] == b) break;
    }

    while (!aux.empty()) {
        path[index] = aux.top();
        aux.pop();
        index++;
    }
}

float Algorithms::twoOpt(Graph *g, int v0, float cost) {
    std::vector<int> path;

    Vertex* v = g->getVertex(v0);

    while (true) {
        path.push_back(v->getId());
        v = g->getVertex(v->getNextVertex());
        if (v->getId() == 0) break;
    }

    path.push_back(0);

    float oldTrace;
    float newTrace;

    bool better = true;

    while(better) {
        better = false;

        for (int i = 1; i < (path.size() - 2); i++) {
            for (int j = i + 2; j < (path.size() - 1); j++) {
                oldTrace = g->getDistance(path[i], path[i + 1]) + g->getDistance(path[j], path[j + 1]);
                newTrace = g->getDistance(path[i], path[j]) + g->getDistance(path[i + 1], path[j + 1]);

                if (newTrace < oldTrace) {
                    cost -= (oldTrace - newTrace);
                    swap(path, path[i + 1], path[j]);

                    better = true;
                    break;
                }
            }
        }
    }

    //atualizar o path no grafo
    for (int i = 1; i <= g->getNoVertexes(); i++) {
        v->setNextVertex(path[i]);
        v = g->getVertex(v->getNextVertex());
    }

    return cost;
}

