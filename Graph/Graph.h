//
// Created by Filipe Correia on 24/04/2024.
//

#ifndef DAPROJECT2_GRAPH_H
#define DAPROJECT2_GRAPH_H


#include <vector>
#include <string>
#include <iostream>


// struct com distância, bool ifIsInOriginalGraph
struct VInfo{
    float distance;
    bool isInGraph;
};
float calculateDistance(int latA, int lonA, int latB, int lonB);
int getposition(int noVertexes, int a, int b);
int factorial(int n);


class Vertex{
protected:
    //std::vector<Edge *> adj;
    int id;
    bool visited = false;
    bool processing = false;
    float latitude;
    float longitude;

    Vertex* nextVertex = nullptr; // contains the next vertex in the path
    //std::vector<Edge *> incoming;
    std::string code;

public:
    Vertex(int id,const std::string& code, float lat, float lon) : id(id), code(code), latitude(lat), longitude(lon){};
    int getId() const{return id;}
    float getLat(){return latitude;}
    float getLon(){return longitude;}
    bool isVisited(){return visited;}
    bool isProcessing(){return processing;}
    void setVisited(bool v){visited = v;}
    void setProcessing(bool p){processing = p;}
    friend class Graph;
};

class Graph{
protected:
    std::vector<Vertex*> vertexSet;    // vertex set
    std::vector<float> data; // save it as negative if not in graph - if 0, it has not been calculated yet
    int noVertexes;
    std::vector<VInfo> line;

public:

    // Yes, you need the noVertexes when init the graph.. perharps we can do this by adding a line on each file with info of noVertexes
    Graph(int noVertexes){
        int sizeOfVector = ((float) factorial(noVertexes)) / (2.0 * factorial(noVertexes - 2)); // Calculate combinatorial -> how many combinations of vertexes exist
        data.resize(sizeOfVector);
        this->noVertexes = noVertexes;
        line.resize(noVertexes);
    }
    void setVertexSet(std::vector<Vertex*> set){
        this->vertexSet = set;
    }

    Vertex* getVertex(int id){return vertexSet[id];}

    std::vector<Vertex*> getVertexSet() const{
        return vertexSet;
    }

    float getDistance(int s, int e){
        float distance = data[getposition(noVertexes, s, e)];
        if(distance < 0){
            return -distance;
        }
        if(distance == 0){
            // calculate
            Vertex* sVertex = getVertex(s);
            Vertex* eVertex = getVertex(e);
            float d = calculateDistance(sVertex->getLat(), sVertex->getLon(), eVertex->getLat(), eVertex->getLon());
            // update in table
            data[getposition(noVertexes, s, e)] = d;
        }
        return distance;
    }

    void printDebug(){
        for(float f : data){
            std::cout << f;
        }
    }

    bool setEdgeDistance(int start, int end, float distance, bool existsInGraph){
        if(start >= noVertexes || end >= noVertexes || start < 0 || end < 0){
            return false;
        }
        if(start == end){
            return false;
        }

        if(existsInGraph){
            data[getposition(noVertexes, start, end)] = distance;
        }else{
            data[getposition(noVertexes, start, end)] = -distance;
        }
        return true;
    }
};








#endif //DAPROJECT2_GRAPH_H
