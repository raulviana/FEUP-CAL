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
    /**
     * @brief Construct a new Two Opt
     * 
     * @param graph Pointer to the graph
     */
    TwoOpt(Graph<Node *> *graph);

    /**
     * @brief Two-Opt Algorithm
     * 
     * @param existingPath Path in random order
     * @return vector<Node *> Path in best order or empty if there's no possible path
     */
    vector<Node *> twoOptAlgorithm(vector<Node *> existingPath);

    /**
     * @brief Swaps vector elements between the range [i,k]
     * 
     * @param existingPath Path with nodes with the default order
     * @param i First element of the range 
     * @param k Last element of the range 
     * @return vector<Node *> Path with a new order
     */
    vector<Node *> twoOptSwap(vector<Node *> existingPath, int i, int k) const;

    /**
     * @brief Calculates total weight of the given path
     * 
     * @param existingPath Path to calculate its weight
     * @return double Total weight
     */
    double calcTotalWeight(vector<Node *> existingPath);

    /**
     * @brief Checks if it's possible to make a path with the given ordered nodes
     * 
     * @param existingPath Group of nodes
     * @return True if all nodes are reachable in the given order, false otherwise
     */
    bool isPathValid(vector<Node *> existingPath);
};

#endif /* OPT_H_ */
