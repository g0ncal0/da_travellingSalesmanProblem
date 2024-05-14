#ifndef DAPROJECT2_PARSER_H
#define DAPROJECT2_PARSER_H
#include <string>

class Graph;
class Parser {
    public:
        static Graph* parse();
        static Graph* parseToy();
        static Graph* parseExtraFullyConnected();
        static Graph* parseExtraFullyConnectedWithId(int id);
        static Graph* parseRealWorld();
};


#endif
