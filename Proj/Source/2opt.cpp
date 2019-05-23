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
    double bestWeight = calcPathWeight(visitOrder);
    vector<Node *> bestVisitOrder = visitOrder;

    //Node* startNode = visitOrder.at(0);
    //Node* finishNode = visitOrder.at(visitOrder.size() - 1);

    // start and finish node can't be included, since they have fixed positions in the visit order
    u_int numNodesForSwap = visitOrder.size() - 2;

    double lastBestWeight = -1;
    double visitOrderWeight;

    // repeat until no improvement
    while (lastBestWeight != bestWeight)
    {
        lastBestWeight = bestWeight;

        for (u_int i = 1; i <= numNodesForSwap - 1; i++)
        {
            for (u_int k = i + 1; k <= numNodesForSwap; k++)
            {
                visitOrder = twoOptSwap(bestVisitOrder, i, k);
                std::cout << "swapped\n";

                if (!isVisitOrderValid(visitOrder))
                {
                    continue;
                }

                visitOrderWeight = calcPathWeight(visitOrder);

                if (visitOrderWeight < bestWeight)
                {
                    bestVisitOrder = visitOrder;
                    bestWeight = visitOrderWeight;
                }
            }
        }
    }
    return bestVisitOrder;
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

    cout << "Weight = " << weight << endl;
    return weight;
}

bool Two_Opt::isVisitOrderValid(vector<Node *> visitOrder)
{
    for (auto i = 0; i < visitOrder.size() - 1; i++)
    {
        std::vector<Node *> res = graph->bfs(visitOrder[i]);

        if (find(res.begin(), res.end(), visitOrder[i + 1]) == res.end())
        {
            /*cout << "Delivery " << deliveries.at(i)->getInvoiceNumber()
                 << " in node " << deliveries.at(i)->getNode()->getIdNode()
                 << " cannot be reached from the warehouse!" << endl;*/
            std::cout << "Not Reachable :(\n";
            return false;
        }
        else
        {
            std::cout << "Reachable :)\n";
            return true;
        }
    }

    std::cout << "Cheguei aqui :o\n";
    return false;
}
