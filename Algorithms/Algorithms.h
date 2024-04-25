//
// Created by goncalo on 25-04-2024.
//

#ifndef DAPROJECT2_ALGORITHMS_H
#define DAPROJECT2_ALGORITHMS_H

#include "../Graph/Graph.h"

class Algorithms {
    static bool auxTSPwithBacktracking(Graph* g, int id, int& costToBeat, int numberVisited);

public:
    static int TSPwithBacktracking(Graph* g);
};


#endif //DAPROJECT2_ALGORITHMS_H
