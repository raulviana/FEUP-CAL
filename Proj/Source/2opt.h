/*
 * opt.h
 */
#ifndef OPT_H_
#define OPT_H_

#include "graph.h"
#include "node.h"

class TwoOpt
{
private:
    Graph<Node *> *graph;

public:
    TwoOpt(Graph<Node *> *graph);
    vector<Node *> twoOptAlgorithm(vector<Node *> existingPath);
    vector<Node *> twoOptSwap(vector<Node *> existingPath, int i, int k) const;
    double calcTotalWeight(vector<Node *> existingPath);
    bool isPathValid(vector<Node *> existingPath);
};

#endif /* OPT_H_ */
