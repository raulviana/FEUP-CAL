/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <sys/socket.h>
#include <string>

#include "graphviewer.h"
#include "graph.h"
#include "node.h"

class Map
{
private:
    Graph<Node *> *map;

public:
    Map(std::string mapName);
    void setupGraphViewer();
    void loadNodes(std::string filename);
    void loadEdges(std::string filename);
    Node *findNode();
};

#endif /* MAP_H_ */