#include <algorithm>
#include <iostream>

#include "2opt.h"

TwoOpt::TwoOpt(Graph<Node *> *graph)
{
    this->graph = graph;
}

// performs  iterations in attempt to improve current solution until no improvement is found
vector<Node *> TwoOpt::twoOptAlgorithm(vector<Node *> existingPath)
{
    double bestWeight;

    if ((bestWeight = calcTotalWeight(existingPath)) == 0)
    {
        bestWeight = INF;
    }

    vector<Node *> newPath = existingPath;
    vector<Node *> bestPath = existingPath;

    // start and finish will not be included, since they have fixed positions in the existingPath
    u_int numNodesForSwap = existingPath.size() - 2;

    double lastBestWeight = -1;
    double newWeight;
    int iterations = 0;

    // repeat until no improvement or two many iterations are made without bestWeight having a value
    while (iterations <= numNodesForSwap)
    {
        if (bestWeight != INF && lastBestWeight == bestWeight)
            break;

        lastBestWeight = bestWeight;

        for (u_int i = 1; i <= numNodesForSwap - 1; i++)
        {
            for (u_int k = i + 1; k <= numNodesForSwap; k++)
            {
                existingPath = twoOptSwap(newPath, i, k);

                if (!isPathValid(existingPath))
                {
                    newPath = existingPath;
                    continue;
                }

                newWeight = calcTotalWeight(existingPath);

                if (newWeight < bestWeight)
                {
                    bestWeight = newWeight;
                    bestPath = existingPath;
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

    return bestPath;
}

vector<Node *> TwoOpt::twoOptSwap(vector<Node *> existingPath, int i, int k) const
{
    // swap the vector elements between the range [i,k]
    while (i < k)
    {
        std::swap(existingPath.at(i), existingPath.at(k));
        i++;
        k--;
    }

    return existingPath;
}

double TwoOpt::calcTotalWeight(vector<Node *> existingPath)
{
    double weight = 0;

    for (unsigned int i = 0; i < existingPath.size() - 1; i++)
    {
        graph->dijkstraShortestPath(existingPath.at(i));
        auto ww = graph->getPath(existingPath.at(i), existingPath.at(i + 1));
        weight += graph->getDistOfVertex(existingPath.at(i + 1));

        if (ww.size() == 0)
        {
            return false;
        }
    }

    return weight;
}

bool TwoOpt::isPathValid(vector<Node *> existingPath)
{
    for (auto i = 0; i < existingPath.size() - 1; i++)
    {
        std::vector<Node *> res = graph->bfs(existingPath[i]);

        if (find(res.begin(), res.end(), existingPath[i + 1]) == res.end())
        {
            return false; // not reacheable
        }
    }

    return true;
}
