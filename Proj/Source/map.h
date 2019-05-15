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
    Graph<Node *> *map = (Graph<Node *> *)malloc(4096);

public:
    Map(std::string mapName);
    void initGraphViewer();
    void loadNodes(std::string filename);
    void loadEdges(std::string filename);
    void loadTags(std::string filename);
    Node *findNode(int idNode);
};

void showLoadProgress(int counter, int number, std::string type);

#endif /* MAP_H_ */