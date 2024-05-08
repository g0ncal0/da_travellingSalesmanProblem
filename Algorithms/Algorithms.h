//
// Created by goncalo on 25-04-2024.
//

#ifndef DAPROJECT2_ALGORITHMS_H
#define DAPROJECT2_ALGORITHMS_H

#include "../Graph/Graph.h"
#include <set>
#include <unordered_map>
class Algorithms {
    static bool auxTSPwithBacktracking(Graph* g, int id, int& costToBeat, int numberVisited);
    /**
     * A recursive depth-first search used by the triangular approximation algorithm to construct the final path.\n
     * Complexity: O(V + E)
     * @param g The graph on which the algorithm is being performed
     * @param vert The vertex which is being explored
     * @param edges The edges which belong to the minimum spanning tree
     * @param currentLast The vertex at the end of the current calculated path
     * @return The length of the path, excluding the final edge to the starting vertex
     */
    static float auxTriangleApproximationDFS(Graph *g,Vertex* vert, std::unordered_map<Vertex*,std::vector<Vertex*>>& edges,Vertex*& currentLast);
    /**
     * An implementation of Kruskal's algorithm, used to construct a minimum spanning tree for the triangular approximation algorithm.\n
     * Complexity: O(V + E)
     * @param g The graph on which the algorithm is being performed
     * @param startVertex The vertex to start the minimum spanning tree with
     * @param edges A container for the valid minimum spanning tree edges which will be generated by this function
     */
    static void auxMST(Graph* g,Vertex* startVertex,std::unordered_map<Vertex*,std::vector<Vertex*>>& edges);
public:


    static float TSPbyEdgeOrdering(Graph* g);

    static int TSPwithBacktracking(Graph* g);

    /**
     * An approximation algorithm for the TSP problem, using a triangular approximation algorithm. \n
     * Complexity: O(E * log(E)))
     * @param g The graph on which to perform the algorithm
     * @param startVertexId The vertex on which the path starts
     * @return The length of the path found
     */
    static float TSPwithTriangleApproximation(Graph* g, int startVertexId);
};


#endif //DAPROJECT2_ALGORITHMS_H
