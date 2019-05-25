#include <algorithm>

#include "path.h"

/*
 * ==============================================================================================
 * 1st Iteration - 1 van with unlimited storage | starting point not the same as the ending point
 * ==============================================================================================
 */

void vanPath(Map *map)
{
    Node *warehouse = map->getWarehouse();
    Node *garage = map->getGarage();

    Graph<Node *> *graph = map->getGraph();
    Two_Opt two(graph);

    vector<Node *> nodesUnordered;
    nodesUnordered.push_back(warehouse);

    for (unsigned int i = 0; i < map->getDeliveries()->size(); i++)
    {
        nodesUnordered.push_back(map->getDeliveries()->at(i)->getNode());
    }

    nodesUnordered.push_back(garage);

    std::vector<Node *> nodesOrdered = two.performImprovement(nodesUnordered);
    if (nodesOrdered.empty())
    {
        std::cout << "A single path can not be made starting in the warehouse and ending in the garage passing through all given delivery points..\n";
        return;
    }

    std::vector<Node *> allNodes;

    for (unsigned int i = 0; i < nodesOrdered.size() - 1; i++)
    {
        graph->dijkstraShortestPath(nodesOrdered.at(i));

        std::vector<Node *> pathNodes = graph->getPath(nodesOrdered.at(i), nodesOrdered.at(i + 1));

        if (pathNodes.size() != 0)
        {
            allNodes.insert((allNodes.end()),
                            (pathNodes.begin()),
                            (pathNodes.end() - 1));
        }
    }
    allNodes.push_back(garage);

    for (unsigned int i = 0; i < allNodes.size(); i++)
    {
        if (i != 0)
            std::cout << " -> ";
        std::cout << i << "|" << allNodes.at(i)->getIdNode();
    }

    std::cout << endl;
}

/*
 * =========================================================================================================
 * 2nd Iteration - multiple vans with limited storage | starting point might be the same as the ending point
 * =========================================================================================================
 */

void vanDeliveries(Map *map)
{
    Van van;
    vector<Delivery *> dels = van.calcVans(map);
    std::cout << "deliveries size: " << dels.size() << endl;
}
