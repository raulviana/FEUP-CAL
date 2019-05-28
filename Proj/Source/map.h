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
     * @brief Construct a new Map
     * 
     */
    Map();

    /**
     * @brief Loads the chosen Map
     * 
     * @param mapName Name of the Map to load
     */
    void loadMap(std::string mapName);

    /**
     * @brief Starts the GraphViewer
     * 
     */
    void initGraphViewer();

    /**
     * @brief Sets the GraphViewer Default Appearance
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
     * @brief Finds the Edge that connects two Nodes
     * 
     * @param nodeB Node where the Edge starts
     * @param nodeE Node where the Edge ends
     * @return int ID of the found edge, 0 if not found
     */
    int findEdge(Node *nodeB, Node *nodeE);

    /**
     * @brief Closes the GraphViewer and deletes the Graph and the GraphViewer
     * 
     */
    void closeGraphViewer();

    /**
     * @brief Loads the Nodes from the Graph to the GraphViewer
     * 
     */
    void loadNodesToGraphViewer();

    /**
     * @brief Loads the Edges from the Graph to the GraphViewer
     * 
     */
    void loadEdgesToGraphViewer();

    /**
     * @brief Loads the Nodes from a file to the Graph
     * 
     * @param filename Name of the file where the Nodes are
     */
    void loadNodes(std::string filename);

    /**
     * @brief Loads the Edges from a file to the Graph
     * 
     * @param filename Name of the file where the Edges are
     */
    void loadEdges(std::string filename);

    /**
     * @brief Loads the Tags from a file to the Graph
     * 
     * @param filename Name of the file where the Tags are
     */
    void loadTags(std::string filename);

    /**
     * @brief Loads the Deliveries from a file to a vector of Deliveries on the Map
     * 
     * @param filename Name of the file where the Deliveries are
     */
    void loadDeliveries(std::string filename);

    /**
     * @brief Finds the Node from a specified ID
     * 
     * @param idNode ID of the Node to be found
     * @return Node* Pointer to the found Node, NULL otherwise
     */
    Node *findNode(int idNode);

    /**
     * @brief Removes the Nodes not connected to any other Node
     * 
     */
    void removeDisconnectedNodes();

    /**
     * @brief Removes Repeated Edges
     * 
     */
    void removeExtraEdges();

    /**
     * @brief Get the Graph
     * 
     * @return Graph<Node *>* Pointer to graph of pointers to nodes
     */
    Graph<Node *> *getGraph() const;

    /**
     * @brief Get the Graph Viewer
     * 
     * @return GraphViewer* Pointer to graphviewer
     */
    GraphViewer *getGraphViewer();

    /**
     * @brief Get the Map's deliveries
     * 
     * @return std::vector<Delivery *>* Map's deliveries
     */
    std::vector<Delivery *> *getDeliveries();

    /**
     * @brief Add delivery to map's deliveries
     * 
     * @param del Delivery to add
     */
    void addDelivery(Delivery *del);

    /**
     * @brief Get the Warehouse
     * 
     * @return Node* Warehouse's node
     */
    Node *getWarehouse();

    /**
     * @brief Set the Warehouse
     * 
     * @param warehouse Warehouse's node
     */
    void setWarehouse(Node *warehouse);

    /**
     * @brief Get the Garage
     * 
     * @return Node* Garage's node
     */
    Node *getGarage();

    /**
     * @brief Set the Garage
     * 
     * @param garage Garage's node
     */
    void setGarage(Node *garage);

    /**
     * @brief Get the map's vans
     * 
     * @return std::vector<Van *>* Map's vans
     */
    std::vector<Van *> *getVans();

    /**
     * @brief Add van to map's vans
     * 
     * @param van New van to add
     */
    void addVan(Van *van);
};

/**
 * @brief Shows the loading progress of a certain reading operation
 * 
 * @param counter Number of objects read until this point
 * @param number Total number of objects to read
 * @param type Type of object to be loaded
 */
void showLoadProgress(int counter, int number, std::string type);

#endif /* MAP_H_ */