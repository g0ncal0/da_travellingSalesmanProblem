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
