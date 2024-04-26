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

        graph->setEdgeDistance(ori, dest, distance, 1);
    }

    return graph;
}

Graph* Parser::parseExtraFullyConnected() {
    return new Graph(1);
}

Graph* Parser::parseRealWorld() {
    return new Graph(1);
}
