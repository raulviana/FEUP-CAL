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

    // join of all nodes given to make the path
    std::vector<Node *> nodesUnordered;
    nodesUnordered.push_back(warehouse);

    std::vector<Delivery *> deliveries;

    if (firstIteration)
    {
        deliveries = *(map->getDeliveries());
    }
    else
    {
        if (vanIndex < 0 && vanIndex >= map->getVans()->size())
        {
            std::cout << "\n\n--------------------------------\n";
            std::cout << "Carrinha selecionada não existe!";
            std::cout << "\n--------------------------------\n\n";
            return;
        }
        deliveries = map->getVans()->at(vanIndex)->getDeliveries();
    }

    if (deliveries.empty())
    {
        std::cout << "\n\n--------------------------------------------------------------\n";
        std::cout << "Sem encomendas para entregar, adicione algumas para continuar!";
        std::cout << "\n--------------------------------------------------------------\n\n";
        return;
    }

    for (unsigned int i = 0; i < deliveries.size(); i++)
    {
        nodesUnordered.push_back(deliveries.at(i)->getNode());
    }

    nodesUnordered.push_back(garage);

    // two-opt algorithm
    std::vector<Node *> nodesOrdered = two.twoOptAlgorithm(nodesUnordered);
    if (nodesOrdered.empty())
    {
        std::cout << "\nA single path can not be made starting in the warehouse and ending in the garage passing through all given delivery points...\n";
        return;
    }

    // path between warehouse, deliveries and garage ordered by two-opt algorithm
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

    // van final path
    cout << "\nPath:\n";
    cout << "-----\n";
    for (unsigned int i = 0; i < allNodes.size(); i++)
    {
        if (i != 0)
            std::cout << " -> ";
        std::cout << i << "|" << allNodes.at(i)->getIdNode();
    }

    std::cout << endl;

    // list of deliveries of van with index vanIndex
    if (!firstIteration)
    {
        std::cout << "\n\n-----------------------------------------\n\n";
        cout << "Carrinha: " << vanIndex + 1 << " | Capacidade: " << map->getVans()->at(vanIndex)->getMaxVol() << endl
             << endl; // Carrinha: X | Capacidade: Y

        for (unsigned int i = 0; i < deliveries.size(); i++)
        {
            std::cout << i + 1 << " - "
                      << "Destinatário: " << deliveries.at(i)->getNode()->getIdNode() << " (" // i - Destinatário: X | Volume: Y
                      << deliveries.at(i)->getRecipientName() << ")"
                      << " | Volume: " << deliveries.at(i)->getVolume() << std::endl;
        }

        std::cout << "\n-----------------------------------------\n\n";
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
    vector<Delivery *> allDeliveries = *map->getDeliveries();

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