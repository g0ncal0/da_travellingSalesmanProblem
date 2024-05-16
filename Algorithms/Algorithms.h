//
// Created by goncalo on 25-04-2024.
//

#ifndef DAPROJECT2_ALGORITHMS_H
#define DAPROJECT2_ALGORITHMS_H

#include "../Graph/Graph.h"
#include <set>
#include <unordered_map>
class Algorithms {
    static bool auxTSPwithBacktracking(Graph* g, int id, float& costToBeat, int numberVisited);
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


    static float TSPwithBacktracking(Graph* g);

    /**
     * An approximation algorithm for the TSP problem, using a triangular approximation algorithm. \n
     * Complexity: O(E * log(E)))
     * @param g The graph on which to perform the algorithm
     * @param startVertexId The vertex on which the path starts
     * @return The length of the path found
     */
    static float TSPwithTriangleApproximation(Graph* g, int startVertexId);


    /**
     * An approximation algorithm for the TSP problem, using a DFS algorithm. There is a high likelihood of false negatives, especially in graphs with very few edges. \n
     * Complexity: O(V + E)) => O(V^2)
     * @param g The graph on which to perform the algorithm
     * @param startVertex The vertex on which the path starts
     * @param resultLength The length of the tour found. This result will not yield conclusive information if the return value is false.
     * @return True if a tour containing all vertices found, false otherwise
     */
    static bool TSPrealWorldDFS(Graph* g, int startVertex, double &resultLength);


    /**
     * An approximation algorithm for the TSP problem, using Dijkstra's algorithm. There is a high likelihood of false negatives. It doesn't work well when the starting vertex has a direct edge to a lot of other vertices. \n
     * Complexity: O(V ^ 3)
     * @param g The graph on which to perform the algorithm
     * @param startVertex The vertex on which the path starts
     * @param resultLength The length of the tour found. If no path is found, this yields the length of a tour containing nonexistent edges.
     * @return True if a tour containing all vertices found, false otherwise
     */
    static bool TSPrealWorldDijkstra(Graph* g, int startVertex, double &resultLength);

    static float TSPGreedy(Graph* g);

    static float TSPChristofides(Graph* g);

    static float twoOpt(Graph* g, int v0, float cost);

    static void anotherMST(Graph* g, int v0);

    /**
     * An approximation algorithm for the TSP problem, using a triangular approximation algorithm. \n
     * Complexity: O(E * log(V)))
     * @param g The graph on which to perform the algorithm
     * @param startVertexId The vertex on which the path starts
     * @return The length of the path found
     */
    static double TSPwithTriangleApproximation2(Graph* g, int startVertex);


    /**
     * An approximation algorithm for the TSP problem that always returns a tour. There is a possibility of false negatives. \n
     * Complexity: O(V ^ 2)
     * @param g The graph on which to perform the algorithm
     * @param startVertex The vertex on which the path starts
     * @param resultLength The length of the tour found. If no path is found, this yields the length of a tour that doesn't contain all the vertices.
     * @return True if a tour containing all vertices found, false otherwise
     */
    static bool HUBAlgorithm(Graph* g, int v0,double &resultLength);
};


#endif //DAPROJECT2_ALGORITHMS_H
