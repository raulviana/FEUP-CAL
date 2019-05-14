/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <sys/socket.h>
#include <unistd.h>
#include <string>

#include "graphviewer.h"
#include "graph.h"

class Map
{
private:
    Graph<int> *map;

public:
    Map(std::string mapName);
    void setupGraphViewer();
    void loadNodes(std::string filename);
    void loadEdges(std::string filename);
};

#endif /* MAP_H_ */