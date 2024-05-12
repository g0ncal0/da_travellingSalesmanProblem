//
// Created by Filipe Correia on 24/04/2024.
//

#ifndef DAPROJECT2_GRAPH_H
#define DAPROJECT2_GRAPH_H


#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


float calculateDistance(int latA, int lonA, int latB, int lonB);
int getposition(int noVertexes, int a, int b);



struct edgeInfo{
    int s;
    int e;
    float distance;
};

bool sortedgeInfo(edgeInfo& a, edgeInfo& b);



class Vertex{
protected:
    int id;
    bool visited = false;
    bool processing = false;
    float latitude;
    float longitude;
    std::vector<int> adjVertex;

    //-1 for invalid...
    int nextVertex=-1; // contains the next vertex in the path

    Vertex* prev= nullptr;
    double distanceFromSource=0;
public:
    Vertex(int id, float lat, float lon) : id(id), latitude(lat), longitude(lon){};
    Vertex(int id) : id(id) {};
    int getId() const{return id;}
    double getDistanceFromSource()const {return distanceFromSource;}
    void setDistanceFromSource(double newDistance) {distanceFromSource=newDistance;}
    float getLat(){return latitude;}
    float getLon(){return longitude;}
    bool isVisited(){return visited;}
    bool isProcessing(){return processing;}
    void setVisited(bool v){visited = v;}
    void setProcessing(bool p){processing = p;}
    int getNextVertex(){return nextVertex;}
    void setNextVertex(int nextVertex){this->nextVertex = nextVertex;}
    Vertex* getPrevVertex(){return prev;}
    void setPrevVertex(Vertex* prevVertex){this->prev = prevVertex;}
    friend class Graph;
};

class Graph{
protected:
    std::vector<Vertex*> vertexSet;    // vertex set
    std::vector<std::vector<float>*>* data; // save it as negative if not in graph - if 0, it has not been calculated yet
    int noVertexes;
    std::vector<unsigned char>* visited; // 0: unvisited, 1: visited, 2+: for special algorithms
    std::vector<bool>* edgeUsed;


private:
    int getposition(int a, int b);

public:

    // Yes, you need the noVertexes when init the graph.. perharps we can do this by adding a line on each file with info of noVertexes
    Graph(int noVertexes){
        data = new std::vector<std::vector<float>*>(noVertexes - 1);
        edgeUsed = new std::vector<bool>((noVertexes * (noVertexes - 1))/ 2); // to store the edges that were used.
        for(int i = 0; i < noVertexes; i++){
            (*data)[i] = new std::vector<float>(noVertexes - 1 - i);
        }
        for(int i = 0; i < noVertexes; i++){
            (*edgeUsed)[i] = false;
        }
        this->noVertexes = noVertexes;
        visited = new std::vector<unsigned char>(noVertexes, false);

    }


    int getNoVertexes(){
        return noVertexes;
    }

    void addVertex(int id) {
        Vertex* v = new Vertex(id);
        vertexSet.push_back(v);
    }

    void initializeVisited(){
        for(int i = 0; i < noVertexes; i++){
            (*this->visited)[i] = 0;
        }
    }
    std::vector<float> getEdges(){
        std::vector<float> v ((noVertexes * (noVertexes - 1) / 2));
        int index = 0;

        for(auto vec : *data){
            for(auto e : *vec){
                v[index] = e;
                index++;
            }
        }
        return v;
    }

    std::vector<edgeInfo> getEdgesSorted(){
        std::vector<float> edges = getEdges();
        std::vector<edgeInfo> edgeSorted;
        int s = 0;
        int e = 1;
        for(float edg : edges){
            edgeInfo currentEdge = {s, e, edg};
            e++;
            edgeSorted.push_back(currentEdge);
            if(e == noVertexes){
                s++;
                e = s +1;
            }
        }
        std::sort(edgeSorted.begin(), edgeSorted.end(), sortedgeInfo);
        return edgeSorted;
    }


    void setVisited(int id, bool visited){
        (*this->visited)[id] = visited ? 1 : 0;
    }
    void complexSetVisited(int id, unsigned char visited){
        (*this->visited)[id] = visited;
    }
    unsigned char complexGetVisited(int id){
        return (*this->visited)[id];
    }
    bool getVisited(int id){
        return (*this->visited)[id] != 0;
    }

    void addVertex(int id, float latitude, float longitude) {
        Vertex* v = new Vertex(id, latitude, longitude);
        vertexSet.push_back(v);
    }

    void setVertexSet(std::vector<Vertex*> set){
        this->vertexSet = set;
    }

    Vertex* getVertex(int id){return vertexSet[id];}

    const std::vector<Vertex*>& getVertexSet() const{
        return vertexSet;
    }

    bool isEdgeInGraph(int s, int e){
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
        if(distance <= 0){
            return false;
        }
        return true;
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

        // Acho que esta função está mal, se for negativo deve retornar negativo -> a verificação deve ser feita do outro lado

        if(distance == 0){
            // calculate
            Vertex* sVertex = getVertex(s);
            Vertex* eVertex = getVertex(e);
            distance = - (calculateDistance(sVertex->getLat(), sVertex->getLon(), eVertex->getLat(), eVertex->getLon())); //aqui deve ser negativo, isto só vai chegar aqui caso o edge não exista no grafo
            // update in table
            (*(*data)[s])[e - s - 1] = distance;
        }
        if(distance < 0){
            return -distance;
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


    void initializeEdgesUsed(){
        for(int i = 0; i < (noVertexes * (noVertexes - 1)) / 2; i++){
            (*edgeUsed)[i] = false;
        }
    }


    void setEdgeUsed(int start, int end, bool used){
        if(start >= noVertexes || end >= noVertexes || start < 0 || end < 0){
            return;
        }
        if(start == end){
            return;
        }
        (*edgeUsed)[getposition(start, end)] = used;
    }

    bool getEdgeUsed(int start, int end){
        return (*edgeUsed)[getposition(start, end)];
    }
};

#endif //DAPROJECT2_GRAPH_H
