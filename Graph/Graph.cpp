//
// Created by Filipe Correia on 24/04/2024.
//

#include "Graph.h"


// From https://stackoverflow.com/questions/1838368/calculating-the-amount-of-combinations
unsigned long long combination(unsigned long long n, unsigned long long k){
    if (k > n) {
        return 0;
    }
    unsigned long long r = 1;
    for (unsigned long long d = 1; d <= k; ++d) {
        r *= n--;
        r /= d;
    }
    return r;
}

double factorial(int n){
    double res = 1;
    for(int i = 1; i <= n; ++i) {
        res *= i;
    }
    return res;
}

/**
 * Get the position of edge. Several sums and subtractions O(1)
 * @param noVertexes
 * @param a
 * @param b
 * @return
 */
int getposition(int noVertexes, int a, int b){
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




float calculateDistance(int latA, int lonA, int latB, int lonB){
    return 0;
}


