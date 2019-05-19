#include "node.h"
#include "cmath"

Node::Node(){};

Node::Node(int idNode, double X, double Y)
{
    this->idNode = idNode;
    this->X = X;
    this->Y = Y;
    this->tag = "";
}

void Node::setNode(int idNode, double X, double Y)
{
    this->idNode = idNode;
    this->X = X;
    this->Y = Y;
    this->tag = "";
}

void Node::setTag(std::string tag)
{
    this->tag = tag;
}

int Node::getIdNode()
{
    return this->idNode;
}

double Node::getX()
{
    return this->X;
}

double Node::getY()
{
    return this->Y;
}

std::string Node::getTag()
{
    return this->tag;
}

double Node::getDistanceToAnotherNode(Node *node)
{
    return sqrt(pow(this->getX() - node->getX(), 2) + pow(this->getY() - node->getY(), 2));
}