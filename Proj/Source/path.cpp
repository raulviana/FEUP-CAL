#include <algorithm>

#include "path.h"

/*
 * ================================================================================================
 * 1st Iteration - 1 van with unlimited storage | starting point not the same as the ending point
 * ================================================================================================
 */

void pathOfVan(Map *map)
{
    Node *warehouse = map->getWarehouse();
    Node *garage = map->getGarage();

    Graph<Node *> *graph = map->getGraph();
    Two_Opt two(graph);

    vector<Node *> nodesUnordered;
    nodesUnordered.push_back(warehouse);

    for (unsigned int i = 0; i < map->getDeliveries().size(); i++)
    {
        cout << "deliveries size = " << map->getDeliveries().size() << endl;
        nodesUnordered.push_back(map->getDeliveries().at(i)->getNode());
    }

    nodesUnordered.push_back(garage);

    cout << "unordered size = " << nodesUnordered.size() << endl;

    vector<Node *> nodesOrdered = two.performImprovement(nodesUnordered);
    vector<Node *> allNodes;

    for (unsigned int i = 0; i < nodesOrdered.size() - 1; i++)
    {
        graph->dijkstraShortestPath(nodesOrdered.at(i));
        cout << "ordered " << i << " = " << nodesOrdered.at(i)->getIdNode() << endl;
        vector<Node *> pathNodes = graph->getPath(nodesOrdered.at(i), nodesOrdered.at(i + 1));

        for (unsigned int i = 0; i < pathNodes.size(); i++)
        {
            cout << "get path: " << i << " " << pathNodes.at(i)->getIdNode() << endl;
        }

        cout << "size path = " << pathNodes.size() << endl;
        if (pathNodes.size() != 0)
        {
            allNodes.insert((allNodes.end()),
                            (pathNodes.begin()),
                            (pathNodes.end() - 1));
        }
    }
    allNodes.push_back(garage);

    cout << "ordered " << nodesOrdered.size() - 1 << " = " << nodesOrdered.at(nodesOrdered.size() - 1)->getIdNode() << endl;

    for (unsigned int i = 0; i < allNodes.size(); i++)
    {
        if (i != 0)
            std::cout << " -> ";
        std::cout << i << "|" << allNodes.at(i)->getIdNode();
    }

    std::cout << endl;

    // std::vector<Node *> res = graph->bfs(warehouse);

    /*if (warehouse->getIdNode() != garage->getIdNode())
    {
        if (find(res.begin(), res.end(), garage) == res.end())
        {
            cout << "Garage can not be reached from the warehouse!\n";
        }
    }*/

    // isReachable(res, map->getDeliveries());
    //single source diijktra
    //shortest path
    //opt
    //...
}

void isReachable(std::vector<Node *> res, std::vector<Delivery *> deliveries)
{
    for (auto i = 0; i < deliveries.size(); i++)
    {
        if (find(res.begin(), res.end(), deliveries.at(i)->getNode()) == res.end())
        {
            cout << "Delivery " << deliveries.at(i)->getInvoiceNumber()
                 << " in node " << deliveries.at(i)->getNode()->getIdNode()
                 << " cannot be reached from warehouse!" << endl;
        }
        else
        {
            cout << "Reachable\n";
        }
    }
}
