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
    Node(int idNode, double X, double Y);
    void setNode(int idNode, double X, double Y);
    void setTag(std::string tag);
    int getIdNode();
    double getX();
    double getY();
    std::string getTag();
};

#endif /* NODE_H_ */