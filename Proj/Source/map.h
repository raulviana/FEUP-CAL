/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

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
    void loadNodesToGraphViewer(GraphViewer *gv, double graphHeight, double graphWidth, int windowHeight, int windowWidth);
    void loadEdgesToGraphViewer(GraphViewer *gv);
    void loadNodes(std::string filename);
    void loadEdges(std::string filename);
    void loadTags(std::string filename);
    Node *findNode(int idNode);
    void removeExtraEdges();
    void removeNotConnectedNodes();
};

void showLoadProgress(int counter, int number, std::string type);

#endif /* MAP_H_ */