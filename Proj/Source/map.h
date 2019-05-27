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
#include "van.h"

class Map
{
private:
    Graph<Node *> *map;
    GraphViewer *gv;
    std::vector<Delivery *> deliveries;
    Node *warehouse;
    Node *garage;
    std::vector<Node *> allNodes;
    std::vector<Van *> vans;

public:
    /**
     * @brief Construct a new Map object
     * 
     */
    Map();

    /**
     * @brief 
     * 
     * @param mapName 
     */
    void loadMap(std::string mapName);

    /**
     * @brief 
     * 
     */
    void initGraphViewer();

    /**
     * @brief Set the Graph Viewer Default Appearance object
     * 
     */
    void setGraphViewerDefaultAppearance();

    /**
     * @brief 
     * 
     * @param allNodes 
     */
    void viewPath(std::vector<Node *> *allNodes);

    /**
     * @brief 
     * 
     * @param nodeB 
     * @param nodeE 
     * @return int 
     */
    int findEdge(Node *nodeB, Node *nodeE);

    /**
     * @brief 
     * 
     */
    void closeGraphViewer();

    /**
     * @brief 
     * 
     */
    void loadNodesToGraphViewer();

    /**
     * @brief 
     * 
     */
    void loadEdgesToGraphViewer();

    /**
     * @brief 
     * 
     * @param filename 
     */
    void loadNodes(std::string filename);

    /**
     * @brief 
     * 
     * @param filename 
     */
    void loadEdges(std::string filename);

    /**
     * @brief 
     * 
     * @param filename 
     */
    void loadTags(std::string filename);

    /**
     * @brief 
     * 
     * @param filename 
     */
    void loadDeliveries(std::string filename);

    /**
     * @brief 
     * 
     * @param idNode 
     * @return Node* 
     */
    Node *findNode(int idNode);

    /**
     * @brief 
     * 
     */
    void removeDisconnectedNodes();

    /**
     * @brief 
     * 
     */
    void removeExtraEdges();

    /**
     * @brief Get the Graph object
     * 
     * @return Graph<Node *>* 
     */
    Graph<Node *> *getGraph() const;

    /**
     * @brief Get the Graph Viewer object
     * 
     * @return GraphViewer* 
     */
    GraphViewer *getGraphViewer();

    /**
     * @brief Get the Deliveries object
     * 
     * @return std::vector<Delivery *>* 
     */
    std::vector<Delivery *> *getDeliveries();

    /**
     * @brief 
     * 
     * @param del 
     */
    void addDelivery(Delivery *del);

    /**
     * @brief Get the Warehouse object
     * 
     * @return Node* 
     */
    Node *getWarehouse();

    /**
     * @brief Set the Warehouse object
     * 
     * @param warehouse 
     */
    void setWarehouse(Node *warehouse);

    /**
     * @brief Get the Garage object
     * 
     * @return Node* 
     */
    Node *getGarage();

    /**
     * @brief Set the Garage object
     * 
     * @param garage 
     */
    void setGarage(Node *garage);

    /**
     * @brief Get the Vans object
     * 
     * @return std::vector<Van *>* 
     */
    std::vector<Van *> *getVans();

    /**
     * @brief 
     * 
     * @param van 
     */
    void addVan(Van *van);
};

/**
 * @brief 
 * 
 * @param counter 
 * @param number 
 * @param type 
 */
void showLoadProgress(int counter, int number, std::string type);

#endif /* MAP_H_ */