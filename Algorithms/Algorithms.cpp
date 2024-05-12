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
#include <limits>

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

bool TSPrealWorld1Rec(Graph* g, Vertex* currentVertex, int depth, int startVertex, double &length)
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
            return TSPrealWorld1Rec(g, minVert, depth, startVertex, length);

    }else
    {
        return false;
    }

}

bool Algorithms::TSPrealWorld1(Graph* g, int startVertex, double &resultLength)
{
   resultLength=0;
   Vertex* vert=g->getVertex(startVertex);
   for (Vertex* v:g->getVertexSet()) {
    v->setVisited(false);
    v->setNextVertex(0);
   }
return TSPrealWorld1Rec(g, vert, 0, startVertex, resultLength);

   return false;
}

#include <list>

bool Algorithms::TSPrealWorld2(Graph *g, int startVertex, double &resultLength)
{
    const double MAX_DOUBLE=std::numeric_limits<double>::max();
    Vertex* source;

    std::unordered_set<Vertex*> unvisited;
    for(Vertex* vert:g->getVertexSet())
    {
        vert->setDistanceFromSource(MAX_DOUBLE);
        vert->setNextVertex(-1);
        vert->setPrevVertex(nullptr);
        if(vert->getId()==startVertex)
        {
            source=vert;
        }
        unvisited.emplace(vert);
    }
    source->setDistanceFromSource(0);
    std::vector<Vertex*> verts;
    verts.push_back(source);

    auto pickClosestVertex=[&verts,&unvisited](){


        std::sort(verts.begin(),verts.end(),[](const Vertex* l,const Vertex* r)
        {

            return r->getDistanceFromSource()<l->getDistanceFromSource();
        }
        );

        auto res=*verts.rbegin();
        verts.resize(verts.size()-1);
        unvisited.erase(res);
        return res;
    };



    while(!verts.empty())
    {
        auto vert=pickClosestVertex();
        for(auto other: unvisited)
        {
            if (g->isEdgeInGraph(vert->getId(),other->getId()))
            {
                auto dist=(vert->getDistanceFromSource()==MAX_DOUBLE?MAX_DOUBLE:vert->getDistanceFromSource()+g->getDistance(vert->getId(),other->getId()));
                // maybe this overflow checking isn't necessary
                if (other->getDistanceFromSource()>dist)
                {
                    other->setDistanceFromSource(dist);
                    other->setPrevVertex(vert);
                }
            } else if(other->getPrevVertex()== nullptr)
            {
                other->setPrevVertex(vert);
            }
        }
    }

    //now I need to invert this, somehow...
    for(auto vert: g->getVertexSet())
    {
        auto prev=vert->getPrevVertex();

        if(prev== nullptr)
        {
            continue;
        }

        if (prev->getNextVertex()!=-1)
        {
            while (true) {
                if (prev->getNextVertex() == -1)
                {
                    break;
                }else
                {
                    prev=g->getVertex(prev->getNextVertex());
                }
            }

        }
        prev->setNextVertex(vert->getId());

    }

    Vertex* v = source;
    resultLength=0;
    while (true) {
        if (v->getNextVertex()==-1)
        {
            v->setNextVertex(startVertex);

        }
        if (g->isEdgeInGraph(v->getId(),v->getNextVertex()))
        {
            resultLength+=g->getDistance(v->getId(),v->getNextVertex());
        } else
        { return false;}
        v = g->getVertex(v->getNextVertex());
        if (v->getId() == startVertex) {break;}
    }

    //this does just a dijkstra's for now...
    return true;
}




/**
 * Gives an approximated result to TSP problem using greedy approach
 * @param g Graph assumed to be complete
 * @return
*/
float Algorithms::TSPGreedy(Graph* g){
    g->initializeVisited();
    float sum = 0;

    int i = g->getNoVertexes() - 1;
    Vertex* current = g->getVertex(0); // starts at vertex 0

    while(i > 0){
        float min = std::numeric_limits<float>::max(); //
        int indexNext = -1;
        for(int j = 0; j < g->getNoVertexes(); j++){
            if(current->getId() != j && !g->getVisited(j)){ // is not the same vertex and is not visited yet
                int cmin = g->getDistance(current->getId(),j); // get the distance between i and other vertexes to find min.
                if(cmin < min){
                    min = cmin;
                    indexNext = j; // the index of the element that will follow current
                }
            }
        }
        sum += min;
        current->setNextVertex(indexNext);
        g->setVisited(current->getId(), true);
        i--;
        current = g->getVertex(indexNext);
    }

    current->setNextVertex(0);
    sum += g->getDistance(0, current->getId());
    return sum;
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

    //first mst algorithm
    /*std::unordered_map<Vertex *, std::vector<Vertex * >> edges;
    auxMST(g, vert, edges);

    for (auto& p : edges) {
        for (auto& v : p.second) {
            std::cout << p.first->getId() << " -> " << v->getId() << std::endl;
        }
    }*/

    //second mst algorithm
    anotherMST(g, 0);
    for (int i = 0; i < g->getNoVertexes(); i++) {
        for (int j = i + 1; j < g->getNoVertexes(); j++) {
            if (g->getEdgeUsed(i, j)) {
                std::cout << g->getVertex(i)->getId() << " -> " << g->getVertex(j)->getId() << std::endl;
            }
        }
    }

    /*for (auto vertex: g->getVertexSet()) {
        vertex->setVisited(false);
    }

    std::vector<Vertex*> oddVertexes = getOddVertexesInTree(edges);*/



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

bool isValidEdge(int u, int v, Graph* g) {
    bool uInMST = g->getVertex(u)->isVisited();
    bool vInMST = g->getVertex(v)->isVisited();

    if (uInMST && vInMST)
        return false;
    if ((!uInMST) && (!vInMST))
        return false;

    return true;
}

void Algorithms::anotherMST(Graph* g, int v0) {
    //estou a assumir que o vetor que armazena se a edge existe começa com tudo a falso para eu usar esse valor para dizer se a edge está ou não na MST, talvez seja preciso inicializar isso à mão depois

    g->getVertex(v0)->setVisited(true);
    int sizeMST = 1;
    int sizeGraph = g->getNoVertexes();
    float distance;
    int a, b;

    while (sizeMST < sizeGraph) {
        float min = std::numeric_limits<float>::max();
        a = b = -1;

        for (int i = 0; i < sizeGraph; i++) {
            for (int j = i + 1; j < sizeGraph; j++) {
                distance = g->getDistance(i, j);
                if (distance < min) {
                    if (isValidEdge(i, j, g)) {
                        min = distance;
                        a = i;
                        b = j;
                    }
                }
            }
        }

        if (a != -1 && b != -1) {
            sizeMST++;
            g->getVertex(a)->setVisited(true);
            g->getVertex(b)->setVisited(true);
            g->setEdgeUsed(a, b, true);
        }
        else break;
    }
}