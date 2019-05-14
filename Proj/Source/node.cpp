#include "node.h"

Node::Node(int idNode, double X, double Y)
{
    this->idNode = idNode;
    this->X = X;
    this->Y = Y;
}

void Node::setNode(int idNode, double X, double Y)
{
    this->idNode = idNode;
    this->X = X;
    this->Y = Y;
}

int Node::getIdNode() {
    return this->idNode;
}