/*
 * opt.h
 */
#ifndef OPT_H_
#define OPT_H_

#include "graph.h"
#include "node.h"

class Two_Opt
{
private:
    Graph<Node *> *graph;

public:
    Two_Opt(Graph<Node *> *graph);
    vector<Node *> performImprovement(vector<Node *> visitOrder);
    vector<Node *> twoOptSwap(vector<Node *> visitOrder, int i, int k) const;
    double calcPathWeight(vector<Node *> visitOrder);
    bool isVisitOrderValid(vector<Node *> visitOrder);
};

#endif /* OPT_H_ */
