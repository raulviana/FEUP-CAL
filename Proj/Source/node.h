/*
 * node.h
 */
#ifndef NODE_H_
#define NODE_H_

class Node
{
private:
    int idNode;
    double X;
    double Y;

public:
    Node(int idNode, double X, double Y);
    void setNode(int idNode, double X, double Y);
    int getIdNode();
};

#endif /* NODE_H_ */