/*
 * node.h
 */
#ifndef NODE_H_
#define NODE_H_

#include <string>

class Node
{
private:
    int idNode;
    double X;
    double Y;
    std::string tag;

public:
    /**
     * @brief Construct a new Node
     * 
     */
    Node();

    /**
     * @brief Construct a new Node
     * 
     * @param idNode Unique ID of each node
     * @param X X-Position of each node
     * @param Y Y-Position of each node
     */
    Node(int idNode, double X, double Y);

    /**
     * @brief Set a Node
     * 
     * @param idNode Unique ID of each node
     * @param X X-Position of each node
     * @param Y Y-Position of each node
     */
    void setNode(int idNode, double X, double Y);

    /**
     * @brief Set the Tag
     * 
     * @param tag Tag of each node
     */
    void setTag(std::string tag);

    /**
     * @brief Get the Tag of a Node
     * 
     * @return std::string Tag of the Node
     */
    std::string getTag();

    /**
     * @brief Get the ID Node
     * 
     * @return int Unique ID of each node
     */
    int getIdNode();

    /**
     * @brief Get the X-Position of each node
     * 
     * @return double X-Position of each node
     */
    double getX();

    /**
     * @brief Get the X-Position of each node
     * 
     * @return double X-Position of each node
     */
    double getY();

    /**
     * @brief Get the Distance To Another Node
     * 
     * @param node Node used to compute distance
     * @return double Distance to another node
     */
    double getDistanceToAnotherNode(Node *node);
};

#endif /* NODE_H_ */