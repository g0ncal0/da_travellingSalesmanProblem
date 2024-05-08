//
// Created by Filipe Correia on 02/03/2024.
//

#include "Parser.h"
#include "Graph/Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

auto getInt = [](istringstream& data, int& toSet, char end = ',') {
    std::string line;
    getline(data, line, end);
    if (line!="")
    {
        toSet = stoi(line);
    }
};

auto getFloat = [](istringstream& data, float& toSet, char end = ',') {
    std::string line;
    getline(data, line, end);
    if (line != "")
    {
        toSet = stof(line);
    }
};

Graph* Parser::parse() {
    int answer;

    cout << "Hello!\nWhat kind of graph do you want to use?\n1. Toy Graphs\n2. Extra Fully Connected Graphs\n3. Real World Graphs\nYour answer: ";
    cin >> answer;

    if (answer == 2) return parseExtraFullyConnected();
    else if (answer == 3) return parseRealWorld();
    else return parseToy();
}

Graph* Parser::parseToy() {
    int answer;
    string filename;

    cout << "\nWhat graph do you want?\n1. Shipping\n2. Stadium\n3. Tourism\nYour answer: ";
    cin >> answer;

    if (answer == 1) filename = "../Data/Toy-Graphs/shipping.csv";
    else if (answer == 2) filename = "../Data/Toy-Graphs/stadiums.csv";
    else filename = "../Data/Toy-Graphs/tourism.csv";

    string line;
    int ori;
    int dest;
    float distance;
    int numberVertex = 0;

    ifstream ifs(filename);

    getline(ifs,line); //The first line doesn't contain valid information
    while (getline(ifs,line)) {
        istringstream iss(line);

        getInt(iss,ori);
        getInt(iss, dest);

        if (ori > numberVertex) numberVertex = ori;
        if (dest > numberVertex) numberVertex = dest;
    }

    numberVertex++;

    Graph* graph = new Graph(numberVertex);
    for (int i = 0; i < numberVertex; i++) graph->addVertex(i);

    ifstream ifs2(filename);

    getline(ifs2,line); //The first line doesn't contain valid information
    while (getline(ifs2,line)) {
        istringstream iss(line);

        getInt(iss,ori);
        getInt(iss, dest);
        getFloat(iss, distance);

        graph->setEdgeDistance(ori, dest, distance, true);
    }

    return graph;
}

Graph* Parser::parseExtraFullyConnected() {
    int answer;
    string filename = "../Data/Extra_Fully_Connected_Graphs/";
    int nVertex;

    cout << "\nHow many nodes do you want in the graph?\n1. 25\n2. 50\n3. 75\n4. 100\n5. 200\n6. 300\n7. 400\n8. 500\n9. 600\n10. 700\n11. 800\n12. 900\nYour answer: ";
    cin >> answer;

    if (answer == 2) {
        filename += "edges_50.csv";
        nVertex = 50;
    }
    else if (answer == 3) {
        filename += "edges_75.csv";
        nVertex = 75;
    }
    else if (answer == 4) {
        filename += "edges_100.csv";
        nVertex = 100;
    }
    else if (answer == 5) {
        filename += "edges_200.csv";
        nVertex = 200;
    }
    else if (answer == 6) {
        filename += "edges_300.csv";
        nVertex = 300;
    }
    else if (answer == 7) {
        filename += "edges_400.csv";
        nVertex = 400;
    }
    else if (answer == 8) {
        filename += "edges_500.csv";
        nVertex = 500;
    }
    else if (answer == 9) {
        filename += "edges_600.csv";
        nVertex = 600;
    }
    else if (answer == 10) {
        filename += "edges_700.csv";
        nVertex = 700;
    }
    else if (answer == 11) {
        filename += "edges_800.csv";
        nVertex = 800;
    }
    else if (answer == 12) {
        filename += "edges_900.csv";
        nVertex = 900;
    }
    else {
        filename += "edges_25.csv";
        nVertex = 25;
    }

    Graph* graph = new Graph(nVertex);

    string line;
    int id;
    float longitude;
    float latitude;
    int ori;
    int dest;
    float distance;

    ifstream nodes("../Data/Extra_Fully_Connected_Graphs/nodes.csv");
    getline(nodes, line);

    for (int i = 0; i < nVertex; i++) {
        getline(nodes, line);
        istringstream iss(line);

        getInt(iss,id);
        getFloat(iss, longitude);
        getFloat(iss, latitude);

        graph->addVertex(id, latitude, longitude);
    }

    ifstream ifs(filename);

    while (getline(ifs,line)) {
        istringstream iss(line);

        getInt(iss,ori);
        getInt(iss, dest);
        getFloat(iss, distance);

        graph->setEdgeDistance(ori, dest, distance, true);
    }

    for (int i = 0; i < nVertex; i++) {
        for (int j = i + 1; j < nVertex; j++) {
            graph->getDistance(i, j);
        }
    }

    return graph;
}

Graph* Parser::parseRealWorld() {
    int answer;
    string nodesFile = "../Data/Real-world-Graphs/";
    string edgesFile = nodesFile;
    int nVertex;

    cout << "\nWhich graph do you want?\n1. Graph 1\n2. Graph 2\n3. Graph3\nYour answer: ";
    cin >> answer;

    if (answer == 2) {
        nodesFile += "graph2/nodes.csv";
        edgesFile += "graph2/edges.csv";
        nVertex = 5000;
    }
    else if (answer == 3) {
        nodesFile += "graph3/nodes.csv";
        edgesFile += "graph3/edges.csv";
        nVertex = 10000;
    }
    else {
        nodesFile += "graph1/nodes.csv";
        edgesFile += "graph1/edges.csv";
        nVertex = 1000;
    }

    Graph* graph = new Graph(nVertex);

    string line;
    int id;
    float longitude;
    float latitude;
    int ori;
    int dest;
    float distance;

    ifstream nodes(nodesFile);
    getline(nodes, line);

    for (int i = 0; i < nVertex; i++) {
        getline(nodes, line);
        istringstream iss(line);

        getInt(iss,id);
        getFloat(iss, longitude);
        getFloat(iss, latitude);

        graph->addVertex(id, latitude, longitude);
    }

    ifstream ifs(edgesFile);
    getline(ifs, line);

    while (getline(ifs,line)) {
        istringstream iss(line);

        getInt(iss,ori);
        getInt(iss, dest);
        getFloat(iss, distance);

        graph->setEdgeDistance(ori, dest, distance, true);
    }

    for (int i = 0; i < nVertex; i++) {
        for (int j = i + 1; j < nVertex; j++) {
            graph->getDistance(i, j);
        }
    }

    return graph;
}
