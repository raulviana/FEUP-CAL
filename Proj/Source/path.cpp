#include <algorithm>

#include "path.h"

/*
 * ==============================================================================================
 * 1st Iteration - 1 van with unlimited storage | starting point not the same as the ending point
 * ==============================================================================================
 */

void vanPath(Map *map, int vanIndex, bool firstIteration)
{
    Node *warehouse = map->getWarehouse();
    Node *garage = map->getGarage();

    Graph<Node *> *graph = map->getGraph();
    TwoOpt two(graph);

    //join of all nodes given to make the path
    std::vector<Node *> nodesUnordered;
    nodesUnordered.push_back(warehouse);

    std::vector<Delivery *> deliveries;

    if (firstIteration)
    {
        deliveries = *(map->getDeliveries());
    }
    else
    {
        deliveries = map->getVans()->at(vanIndex)->getDeliveries();
    }

    if (deliveries.empty()){
        cout << "No deliveries to deliver. Add some before trying to viewww a path.\n";
        return;
    }

    for (unsigned int i = 0; i < deliveries.size(); i++)
    {
        nodesUnordered.push_back(deliveries.at(i)->getNode());
    }

    nodesUnordered.push_back(garage);

    //Two-Opt Algorithm
    std::vector<Node *> nodesOrdered = two.twoOptAlgorithm(nodesUnordered);
    if (nodesOrdered.empty())
    {
        std::cout << "\nA single path can not be made starting in the warehouse and ending in the garage passing through all given delivery points...\n";
        return;
    }

    //Path between warehouse, deliveries and garage ordered by two-opt algorithm
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

    //Van final path
    cout << "\nPath :\n";
    for (unsigned int i = 0; i < allNodes.size(); i++)
    {
        if (i != 0)
            std::cout << " -> ";
        std::cout << i << "|" << allNodes.at(i)->getIdNode();
    }

    std::cout << endl;

    //List of Deliveries of van with index vanIndex
    if (!firstIteration){
        cout << "\nDeliveries of van " << vanIndex << ":\n";

        for (unsigned int i = 0; i < deliveries.size(); i++){
            std::cout << i + 1 << " - " << deliveries.at(i)->getNode()->getIdNode() << " ("
                          << deliveries.at(i)->getRecipientName() << ")" << std::endl;
        }
        cout << endl;
    }

    map->viewPath(&allNodes);
}

/*
 * =========================================================================================================
 * 2nd Iteration - multiple vans with limited storage | starting point might be the same as the ending point
 * =========================================================================================================
 */

void vanDeliveries(Map *map)
{
    vector<Delivery*> allDeliveries = *map->getDeliveries();

    int i = 0;
    while (!allDeliveries.empty())
    {
        if (i >= map->getVans()->size())
        {
            break;
        }

        map->getVans()->at(i)->calcVans(allDeliveries);
        i++;
    }
}