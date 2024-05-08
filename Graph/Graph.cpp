//
// Created by Filipe Correia on 24/04/2024.
//

#include "Graph.h"
#include <cmath>



float calculateDistance(int latA, int lonA, int latB, int lonB){
    double dLat = (latB - latA) * M_PI / 180.0;
    double dLon = (lonB - lonA) * M_PI / 180.0;

    latA = (latA) * M_PI / 180.0;
    latB = (latB) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(latA) * cos(latB);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}


/**
 * Get the position of edge. Several sums and subtractions O(1)
 * @param noVertexes
 * @param a
 * @param b
 * @return
 */
int Graph::getposition(int a, int b){
    // eg: if we had 3 vertexes:
    // these would be the elements:
    // [d(0,1) , d(0, 2), d(1, 2)]
    if(b < a){
        int temp = b;
        b = a;
        a = temp;
    }
    // temos de fazer um somatório entre noVertexes - 1 e noVertexes - 1 - (a - 1);
    int auxsum = noVertexes - 1 + (noVertexes - 1 - (a-1));
    int auxdif = (noVertexes -1 - (noVertexes - 1 - (a- 1))) + 1;

    int indexFirstElementOfA = (auxsum * auxdif) / 2;

    int offset = b - a; // distance after reaching the space of the "a" vertex - eg. if we were looking for d(1, 2), it would be 1.

    return indexFirstElementOfA + offset - 1;

}
