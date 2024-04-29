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
    float distance = 0;
    bool isInGraph = false;
};
float calculateDistance(int latA, int lonA, int latB, int lonB);
int getposition(int noVertexes, int a, int b);



class Vertex{
protected:
    //std::vector<Edge *> adj;
    int id;
    bool visited = false;
    bool processing = false;
    float latitude;
    float longitude;

    int nextVertex; // contains the next vertex in the path
    //std::vector<Edge *> incoming;

public:
    Vertex(int id, float lat, float lon) : id(id), latitude(lat), longitude(lon){};
    Vertex(int id) : id(id) {};
    int getId() const{return id;}
    float getLat(){return latitude;}
    float getLon(){return longitude;}
    bool isVisited(){return visited;}
    bool isProcessing(){return processing;}
    void setVisited(bool v){visited = v;}
    void setProcessing(bool p){processing = p;}
    int getNextVertex(){return nextVertex;}
    void setNextVertex(int nextVertex){this->nextVertex = nextVertex;}
    friend class Graph;
};

class Graph{
protected:
    std::vector<Vertex*> vertexSet;    // vertex set
    std::vector<std::vector<float>*>* data; // save it as negative if not in graph - if 0, it has not been calculated yet
    int noVertexes;
    std::vector<VInfo> line;

public:

    // Yes, you need the noVertexes when init the graph.. perharps we can do this by adding a line on each file with info of noVertexes
    Graph(int noVertexes){
        data = new std::vector<std::vector<float>*>(noVertexes - 1);
        for(int i = 0; i < noVertexes; i++){
            (*data)[i] = new std::vector<float>(noVertexes - 1 - i);
        }
        this->noVertexes = noVertexes;
        std::cout << "done" << std::endl;
    }

    void addVertex(int id) {
        Vertex* v = new Vertex(id);
        vertexSet.push_back(v);
    }

    void addVertex(int id, float latitude, float longitude) {
        Vertex* v = new Vertex(id, latitude, longitude);
        vertexSet.push_back(v);
    }

    void setVertexSet(std::vector<Vertex*> set){
        this->vertexSet = set;
    }

    Vertex* getVertex(int id){return vertexSet[id];}

    std::vector<Vertex*> getVertexSet() const{
        return vertexSet;
    }

    float getDistance(int s, int e){
        if(s >= noVertexes || e >= noVertexes || s < 0 || e < 0){
            return false;
        }
        if(s == e){
            return false;
        }
        if(s > e){
            std::swap(s,e);
        }

        float distance = (*(*data)[s])[e - s - 1];
        /*if(distance < 0){
            return -distance;
        }*/
        //Acho que esta função está mal, se for negativo deve retornar negativo -> a verificação deve ser feita do outro lado
        //Vou alterar isto, qualquer coisa altera-se outra vez

        if(distance == 0){
            // calculate
            Vertex* sVertex = getVertex(s);
            Vertex* eVertex = getVertex(e);
            distance = - (calculateDistance(sVertex->getLat(), sVertex->getLon(), eVertex->getLat(), eVertex->getLon())); //aqui deve ser negativo, isto só vai chegar aqui caso o edge não exista no grafo
            // update in table
            (*(*data)[s])[e - s - 1] = distance;
        }
        return distance;
    }


    bool setEdgeDistance(int start, int end, float distance, bool existsInGraph){
        if(start >= noVertexes || end >= noVertexes || start < 0 || end < 0){
            return false;
        }
        if(start == end){
            return false;
        }
        if(start > end){
            std::swap(start,end);
        }


        if(existsInGraph){
            (*(*data)[start])[end - start - 1] = distance;
        }else{
            (*(*data)[start])[end - start - 1] = -distance;
        }

        return true;
    }
};

#endif //DAPROJECT2_GRAPH_H
