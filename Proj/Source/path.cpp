#include <algorithm>

#include "path.h"

/*
 * ================================================================================================
 * 1st Iteration - 1 van with unlimited storage
 * ================================================================================================
 */

void pathOfVan(Map *map)
{
    Node *warehouse = map->getWarehouse();
    Node *garage = map->getGarage();

    Graph<Node *> *graph = map->getGraph();
    std::vector<Node *> res = graph->bfs(warehouse);

    if (warehouse->getIdNode() != garage->getIdNode())
    {
        if (find(res.begin(), res.end(), garage) == res.end())
        {
            cout << "Garage can not be reached from the warehouse!\n";
        }
    }

    isReachable(res, map->getDeliveries());
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
