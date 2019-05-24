#include <algorithm>
#include <iostream>

#include "2opt.h"

Two_Opt::Two_Opt(Graph<Node *> *graph)
{
    this->graph = graph;
}

// performs  iterations in attempt to improve current solution until no improvement is found
vector<Node *> Two_Opt::performImprovement(vector<Node *> visitOrder)
{
    double bestWeight;

    if ((bestWeight = calcPathWeight(visitOrder)) == 0)
    {
        bestWeight = INF;
    }

    vector<Node *> bestVisitOrder = visitOrder;
    vector<Node *> bbb = visitOrder;

    //Node* startNode = visitOrder.at(0);
    //Node* finishNode = visitOrder.at(visitOrder.size() - 1);

    // start and finish will not be included, since they have fixed positions in the visit order
        u_int numNodesForSwap = visitOrder.size() - 2;

    double lastBestWeight = -1;
    double visitOrderWeight;
    int iterations = 0;

    // repeat until no improvement
    while (iterations <= numNodesForSwap)
    {
        if (bestWeight != INF && lastBestWeight == bestWeight)
            break;

        lastBestWeight = bestWeight;
        cout << "algo_bestWeight = " << bestWeight << endl;

        for (u_int i = 1; i <= numNodesForSwap-1 ; i++)
        {
            for (u_int k = i + 1; k <= numNodesForSwap; k++)
            {
                visitOrder = twoOptSwap(bestVisitOrder, i, k);

                if (!isVisitOrderValid(visitOrder))
                {
                    bestVisitOrder = visitOrder;
                    continue;
                }

                visitOrderWeight = calcPathWeight(visitOrder);

                if (visitOrderWeight < bestWeight && visitOrderWeight!= 0)
                {
                    bestWeight = visitOrderWeight;
                    bbb = visitOrder;
                }
            }
        }
        iterations++;
    }

    if (bestWeight == INF)
    {
        vector<Node *> error;
        return error;
    }
    
    return bbb;
}

vector<Node *> Two_Opt::twoOptSwap(vector<Node *> visitOrder, int i, int k) const
{
    // swap the vector elements between the range [i,k]
    while (i < k)
    {
        std::swap(visitOrder.at(i), visitOrder.at(k));
        i++;
        k--;
    }

    return visitOrder;
}

double Two_Opt::calcPathWeight(vector<Node *> visitOrder)
{
    double weight = 0;

    for (unsigned int i = 0; i < visitOrder.size() - 1; i++)
    {
        graph->dijkstraShortestPath(visitOrder.at(i));
        auto ww = graph->getPath(visitOrder.at(i), visitOrder.at(i + 1));
        weight += graph->getDistOfVertex(visitOrder.at(i + 1));

        if (ww.size() == 0)
        {
            return false;
        }
    }

    return weight;
}

bool Two_Opt::isVisitOrderValid(vector<Node *> visitOrder)
{
    for (auto i = 0; i < visitOrder.size() - 1; i++)
    {
        std::vector<Node *> res = graph->bfs(visitOrder[i]);

        if (find(res.begin(), res.end(), visitOrder[i + 1]) == res.end())
        {
            return false; //not reacheable
        }
    }

    return true;
}
