#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "map.h"

Map::Map()
{
    map = new Graph<Node *>();
}

void Map::loadMap(std::string mapName)
{
    std::string nodeFile = "../Maps/" + mapName + "/T04_nodes_X_Y_" + mapName + ".txt";
    loadNodes(nodeFile);
    std::string edgeFile = "../Maps/" + mapName + "/T04_edges_" + mapName + ".txt";
    loadEdges(edgeFile);
    removeExtraEdges();
    std::string tagFile = "../Maps/" + mapName + "/T04_tags_" + mapName + ".txt";
    loadTags(tagFile);

    //cout << "antes: " << map->getNumVertex() << endl;
    removeDisconnectedNodes();
    //cout << "depois: " << map->getNumVertex() << endl;
    initGraphViewer();
    std::string deliveryFile = "../Maps/" + mapName + "/deliveries" + mapName + ".txt";
    loadDeliveries(deliveryFile);
}

void Map::initGraphViewer()
{
    int height = 600;
    int width = 800;

    gv = new GraphViewer(width, height, false);

    gv->createWindow(width, height);
    setGraphViewerDefaultAppearance();

    loadNodesToGraphViewer();
    loadEdgesToGraphViewer();

    gv->rearrange();
}

void Map::setGraphViewerDefaultAppearance()
{
    gv->defineEdgeColor(RED);
    gv->defineVertexColor(YELLOW);

    if (allNodes.size() != 0)
    {
        for (int i = 0; i < allNodes.size(); i++)
        {
            gv->setVertexColor(allNodes.at(i)->getIdNode(), YELLOW);

            if (i != allNodes.size() - 1)
            {
                int idEdge = findEdge(allNodes.at(i), allNodes.at(i + 1));
                gv->setEdgeColor(idEdge, RED);
                gv->setEdgeThickness(idEdge, 1);
            }
        }

        gv->setVertexLabel(allNodes.at(0)->getIdNode(), ".");
        gv->setVertexLabel(allNodes.at(allNodes.size() - 1)->getIdNode(), ".");
    }

    gv->rearrange();
}

void Map::viewPath(std::vector<Node *> *allNodes)
{
    this->allNodes = *allNodes;

    for (int i = 0; i < allNodes->size(); i++)
    {
        gv->setVertexColor(allNodes->at(i)->getIdNode(), RED);
        if (i != allNodes->size() - 1)
        {
            int idEdge = findEdge(allNodes->at(i), allNodes->at(i + 1));

            if (idEdge != 0)
            {
                gv->setEdgeColor(idEdge, BLACK);
                gv->setEdgeThickness(idEdge, 3);
            }
            else
            {
                std::cout << "No edges found ...";
            }
        }
    }

    gv->setVertexLabel(allNodes->at(0)->getIdNode(), "Armazém");
    gv->setVertexLabel(allNodes->at(allNodes->size() - 1)->getIdNode(), "Garagem");

    gv->rearrange();
}

int Map::findEdge(Node *nodeB, Node *nodeE)
{
    auto adj = map->findVertex(nodeB)->getAdjSet(); // edges of source vertex
    auto dest = adj.begin();

    while (dest != adj.end())
    {
        if ((*dest).getDest()->getInfo()->getIdNode() == nodeE->getIdNode())
        {
            return (*dest).getID();
        }

        ++dest;
    }

    return 0;
}

void Map::closeGraphViewer()
{
    gv->closeWindow();
}

void Map::loadNodesToGraphViewer()
{
    int idNode = 0;
    double X = map->getVertexSet().at(0)->getInfo()->getX();
    double Y = map->getVertexSet().at(0)->getInfo()->getY();

    for (int i = 0; i < map->getNumVertex(); i++)
    {
        idNode = map->getVertexSet().at(i)->getInfo()->getIdNode();
        int currentX = map->getVertexSet().at(i)->getInfo()->getX() - X;
        int currentY = Y - map->getVertexSet().at(i)->getInfo()->getY();

        gv->addNode(idNode, currentX, currentY);
    }
}

void Map::loadEdgesToGraphViewer()
{
    int idNode1 = 0;
    int idNode2 = 0;

    auto vec = map->getVertexSet(); // all vertices
    auto first = vec.begin();

    // when it's a bidirectional edge
    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet(); // edges of source vertex
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            auto vec3 = (*second).getDest()->getAdjSet(); // edges of destiny vertex
            auto third = vec3.begin();

            idNode1 = (*first)->getInfo()->getIdNode();
            idNode2 = (*second).getDest()->getInfo()->getIdNode();

            gv->addEdge((*second).getID(),
                        idNode1,
                        idNode2,
                        EdgeType::DIRECTED);

            gv->setEdgeWeight((*second).getID(), (*second).getWeight());
            ++second;
        }
        ++first;
    }
}

void Map::loadNodes(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file! " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int numberOfNodes;
    int it = 0;
    int idNode = 0;
    double X = 0;
    double Y = 0;
    int counter = 1;

    Node node(idNode, X, Y);

    getline(fin, line); // number of nodes
    numberOfNodes = stoi(line);

    std::cout << "\n--------------- Carregamento --------------\n";
    std::cout << "-------------------------------------------\n\n";
    std::cout << " Processing " << numberOfNodes << " Nodes ..." << endl
              << endl;

    while (!fin.eof())
    {
        getline(fin, line); // (idNode, X.X, Y.Y)
        line = line.substr(1, string::npos);

        it = line.find(",");
        idNode = stoi(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(",");
        X = stod(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(")");
        Y = stod(line.substr(0, it));

        /* add nodes to the graph */
        Node *nodee = new Node(idNode, X, Y);
        map->addVertex(nodee);

        showLoadProgress(counter, numberOfNodes, "Node");
        counter++;
    }

    std::cout << endl;
    fin.close();
}

void Map::loadEdges(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file! " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int idEdge = 1;
    int numberOfEdges;
    int it = 0;
    int idNodeOrigin = 0;
    int idNodeDestiny = 0;

    getline(fin, line); // number of edges
    numberOfEdges = stoi(line);

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << " Processing " << numberOfEdges << " Edges ..." << endl
              << endl;

    while (!fin.eof())
    {
        getline(fin, line); // (idNodeOrigin, idNodeDestiny)
        line = line.substr(1, string::npos);

        it = line.find(",");
        idNodeOrigin = stoi(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(")");
        idNodeDestiny = stod(line.substr(0, it));

        Node *nodeOrigin = findNode(idNodeDestiny);
        Node *nodeDestiny = findNode(idNodeOrigin);

        double distance = nodeOrigin->getDistanceToAnotherNode(nodeDestiny);

        /* add edge to the graph */
        map->addEdge(nodeOrigin, nodeDestiny, distance, idEdge);
        idEdge++;

        map->addEdge(nodeDestiny, nodeOrigin, distance, idEdge);

        showLoadProgress(idEdge, numberOfEdges * 2, "Edge");
        idEdge++;
    }

    std::cout << endl;
    fin.close();
}

void Map::loadTags(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file! " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int numberOfTags;
    int nNodes;
    int idNode = 0;
    int counter = 1;
    std::string tag;

    getline(fin, line); // number of tags
    numberOfTags = stoi(line);

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << " Processing " << numberOfTags << " Tags ..." << endl
              << endl;

    while (!fin.eof())
    {
        getline(fin, tag); // tagname
        tag = tag.substr(0, tag.length() - 1);

        getline(fin, line); // number of nodes with this tag
        nNodes = stoi(line);

        while (nNodes > 0)
        {
            getline(fin, line);
            idNode = stoi(line);
            Node *node = findNode(idNode);

            if (node == NULL)
            {
                std::cout << "Non-existent node!\n";
                exit(1);
            }

            node->setTag(tag);
            nNodes--;
        }

        showLoadProgress(counter, numberOfTags, "Tag");
        counter++;
    }

    std::cout << endl;
    fin.close();
}

void Map::loadDeliveries(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file! " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int numberOfDeliveries;
    std::string recipientName;
    double contentValue;
    double volume;
    int idNode = 0;
    int invoiceNumber = 1;
    int it = 0;
    int counter = 1;

    getline(fin, line); // number of deliveries
    numberOfDeliveries = stoi(line);

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << " Processing " << numberOfDeliveries << " Deliveries ..." << endl
              << endl;

    while (!fin.eof())
    {
        getline(fin, line); // (recipientName, contentValue, volume, idNode, invoiceNumber)

        it = line.find(",");
        recipientName = line.substr(0, it);
        line.erase(0, it + 2);

        cout << "stod\n";

        it = line.find(",");
        contentValue = stod(line.substr(0, it));
        line.erase(0, it + 2);

        cout << "stoi1\n";
        it = line.find(",");
        volume = stod(line.substr(0, it));
        line.erase(0, it + 2);

        cout << "stoi2\n";
        it = line.find(",");
        idNode = stoi(line.substr(0, it));
        line.erase(0, it + 2);

        cout << "stoi3\n";
        it = line.find(",");
        invoiceNumber = stoi(line.substr(0, it));

        deliveries.push_back(new Delivery(recipientName, contentValue, volume, findNode(idNode), invoiceNumber));

        showLoadProgress(counter, numberOfDeliveries, "Delivery");
        counter++;
    }

    std::cout << endl;
    fin.close();
}

Node *Map::findNode(int idNode)
{
    Node *node = NULL;
    auto vec = map->getVertexSet();
    auto first = vec.begin();

    while (first != vec.end())
    {
        if ((*first)->getInfo()->getIdNode() == idNode)
        {
            node = (*first)->getInfo();
            break;
        }
        ++first;
    }

    return node;
}

void Map::removeDisconnectedNodes()
{
    auto vec = map->getVertexSet();
    auto first = vec.begin();

    // removes edges that go from a certain node to the same (self relation)
    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet(); // edges of source vertex
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            if ((*second).getDest()->getInfo()->getIdNode() == (*first)->getInfo()->getIdNode())
            {
                map->removeEdge((*first)->getInfo(), (*first)->getInfo());
            }
            ++second;
        }
        ++first;
    }

    vec = map->getVertexSet();
    first = vec.begin();

    // removes nodes that don't are not connected to
    while (first != vec.end())
    {
        if ((*first)->getAdjSet().size() == 0)
        {
            map->removeVertex((*first)->getInfo());
        }
        ++first;
    }
}

void Map::removeExtraEdges()
{
    auto vs = map->getVertexSet();
    auto v = vs.begin();

    // removes edges that go from a certain node to the same (self relation)
    while (v != vs.end())
    {
        auto es = (*v)->getAdjSet(); // edges of source vertex
        auto e = es.begin();

        while (e != es.end())
        {
            auto e2 = next(e, 1);

            while (e2 != es.end())
            {
                if ((*e).getDest()->getInfo()->getIdNode() == (*e2).getDest()->getInfo()->getIdNode())
                {
                    map->removeEdge((*v)->getInfo(), (*e2).getDest()->getInfo());
                }
                ++e2;
            }
            e++;
        }
        ++v;
    }
}

Graph<Node *> *Map::getGraph() const
{
    return map;
}

GraphViewer *Map::getGraphViewer()
{
    return gv;
}

std::vector<Delivery *> Map::getDeliveries() const
{
    return deliveries;
}

void Map::addDelivery(Delivery* del)
{
    this->deliveries.push_back(del);
}

Node *Map::getWarehouse()
{
    return warehouse;
}

void Map::setWarehouse(Node *warehouse)
{
    this->warehouse = warehouse;
}

Node *Map::getGarage()
{
    return garage;
}

void Map::setGarage(Node *garage)
{
    this->garage = garage;
}

void showLoadProgress(int counter, int number, std::string type)
{
    double percentage;

    percentage = (100 * counter) / (double)number;

    std::cout << " [" << type << " " << counter << " of " << number << " ] ";
    std::cout << fixed << setprecision(2) << percentage << '%' << "\r";
    std::cout.flush();
}