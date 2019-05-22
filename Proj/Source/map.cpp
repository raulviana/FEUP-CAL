#include <algorithm>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "map.h"

Map::Map()
{
}

void Map::loadMap(std::string mapName)
{
    std::string nodeFile = "../Maps/" + mapName + "/T04_nodes_X_Y_" + mapName + ".txt";
    loadNodes(nodeFile);
    std::string edgeFile = "../Maps/" + mapName + "/T04_edges_" + mapName + ".txt";
    loadEdges(edgeFile);
    std::string tagFile = "../Maps/" + mapName + "/T04_tags_" + mapName + ".txt";
    loadTags(tagFile);

    //cout << "antes: " << map->getNumVertex() << endl;
    removeNotConnectedNodes();
    //cout << "depois: " << map->getNumVertex() << endl;
    initGraphViewer();
    std::string deliveryFile = "../Maps/" + mapName + "/deliveries" + mapName + ".txt";
    loadDeliveries(deliveryFile);
}

void Map::initGraphViewer()
{
    double graphHeight = map->getLimitTop() - map->getLimitBot();
    double graphWidth = map->getLimitRight() - map->getLimitLeft();

    int windowHeight = 800;
    int windowWidth = windowHeight * graphWidth / graphHeight;
    gv = new GraphViewer(windowWidth, windowHeight, false);

    gv->createWindow(windowWidth, windowHeight);

    gv->defineEdgeColor("blue");
    gv->defineVertexColor("yellow");

    gv->defineVertexSize(5);

    loadNodesToGraphViewer(gv, graphHeight, graphWidth, windowHeight, windowWidth);
    loadEdgesToGraphViewer(gv);

    gv->rearrange();
}

void Map::closeGraphViewer()
{
    gv->closeWindow();
}

void Map::loadNodesToGraphViewer(GraphViewer *gv, double graphHeight, double graphWidth, int windowHeight, int windowWidth)
{
    int idNode = 0;
    double X = 0;
    double Y = 0;

    for (int i = 0; i < map->getNumVertex(); i++)
    {
        idNode = map->getVertexSet().at(i)->getInfo()->getIdNode();
        X = (map->getVertexSet().at(i)->getInfo()->getX() - map->getLimitLeft()) / graphWidth;
        Y = 1.0 - ((map->getVertexSet().at(i)->getInfo()->getY() - map->getLimitBot()) / graphHeight);

        gv->addNode(idNode, X * windowWidth, Y * windowHeight);
    }
}

void Map::loadEdgesToGraphViewer(GraphViewer *gv)
{
    int idEdge = 1;
    int idNode1 = 0;
    int idNode2 = 0;

    auto vec = map->getVertexSet(); //All vertices
    auto first = vec.begin();

    // when it's a bidirectional edge, removes one of the edges from the graph and the other one is added to the viewer as bidirectional
    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet(); //Edges of source vertex
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            auto vec3 = (*second).getDest()->getAdjSet(); //Edges of destiny vertex
            auto third = vec3.begin();

            while (third != vec3.end())
            {
                idNode1 = (*first)->getInfo()->getIdNode();
                idNode2 = (*second).getDest()->getInfo()->getIdNode();

                if ((*third).getDest()->getInfo()->getIdNode() == (*first)->getInfo()->getIdNode())
                {
                    //cout << "return remove = " << map->removeEdge((*second).getDest()->getInfo(), (*first)->getInfo()) << endl;
                    gv->addEdge(idEdge,
                                idNode1,
                                idNode2,
                                EdgeType::UNDIRECTED);
                    break;
                }
                else
                {
                    gv->addEdge(idEdge,
                                idNode1,
                                idNode2,
                                EdgeType::DIRECTED);
                }
                ++third;
            }
            gv->setEdgeWeight(idEdge, (*second).getWeight());
            idEdge++;
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
    int numberOfEdges;
    int it = 0;
    int idNodeOrigin = 0;
    int idNodeDestiny = 0;
    int counter = 1;

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

        /* add edge to the graph */
        map->addEdge(nodeOrigin, nodeDestiny, nodeOrigin->getDistanceToAnotherNode(nodeDestiny));

        showLoadProgress(counter, numberOfEdges, "Edge");
        counter++;
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

        it = line.find(",");
        contentValue = stod(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(",");
        volume = stod(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(",");
        idNode = stoi(line.substr(0, it));
        line.erase(0, it + 2);

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

//removes nodes that don't have edges leaving them and edges that leave and get in the same node
void Map::removeNotConnectedNodes()
{
    auto vec = map->getVertexSet();
    auto first = vec.begin();

    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet(); // edges of source vertex
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            if ((*second).getDest()->getInfo()->getIdNode() == (*first)->getInfo()->getIdNode())
            {
                //cout << "here2" << endl;
                map->removeEdge((*first)->getInfo(), (*first)->getInfo());
            }
            ++second;
        }
        ++first;
    }

    vec = map->getVertexSet();
    first = vec.begin();

    while (first != vec.end())
    {
        if ((*first)->getAdjSet().size() == 0)
        {
            //cout << "here3" << endl;
            map->removeVertex((*first)->getInfo());
        }
        ++first;
    }
}

void showLoadProgress(int counter, int number, std::string type)
{
    double percentage;

    percentage = (100 * counter) / (double)number;

    std::cout << " [" << type << " " << counter << " of " << number << " ] ";
    std::cout << fixed << setprecision(2) << percentage << '%' << "\r";
    std::cout.flush();
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