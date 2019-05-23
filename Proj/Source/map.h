/*
 * map.h
 */
#ifndef MAP_H_
#define MAP_H_

#include <string>

#include "graphviewer.h"
#include "graph.h"
#include "node.h"
#include "delivery.h"

class Map
{
private:
    Graph<Node *> *map;
    GraphViewer *gv;
    std::vector<Delivery *> deliveries;
    Node *warehouse;
    Node *garage;

public:
    Map();
    void loadMap(std::string mapName);
    void initGraphViewer();
    void closeGraphViewer();
    void loadNodesToGraphViewer(GraphViewer *gv);
    void loadEdgesToGraphViewer(GraphViewer *gv);
    void loadNodes(std::string filename);
    void loadEdges(std::string filename);
    void loadTags(std::string filename);
    void loadDeliveries(std::string filename);
    Node *findNode(int idNode);
    void removeDisconnectedNodes();

    Graph<Node *> *getGraph() const;
    GraphViewer *getGraphViewer();
    std::vector<Delivery *> getDeliveries() const;
    Node *getWarehouse();
    void setWarehouse(Node *warehouse);
    Node *getGarage();
    void setGarage(Node *garage);
};

void showLoadProgress(int counter, int number, std::string type);

#endif /* MAP_H_ */