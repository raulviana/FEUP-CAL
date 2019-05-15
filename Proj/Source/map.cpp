#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "map.h"

Map::Map(std::string mapName)
{
    std::string nodeFile = "../Maps/" + mapName + "/T04_nodes_X_Y_" + mapName + ".txt";
    loadNodes(nodeFile);
    std::string edgeFile = "../Maps/" + mapName + "/T04_edges_" + mapName + ".txt";
    loadEdges(edgeFile);
    std::string tagFile = "../Maps/" + mapName + "/T04_tags_" + mapName + ".txt";
    //loadTags(tagFile);
    //initGraphViewer();
}

void Map::initGraphViewer()
{
    GraphViewer *gv = new GraphViewer(1000, 700, true);

    gv->createWindow(1200, 800);

    gv->defineEdgeColor("blue");
    gv->defineVertexColor("yellow");

    gv->defineVertexSize(2);

    int idNode = 0;
    int idEdge = 1;
    double X = 0;
    double Y = 0;

    for (int i = 0; i < map->getNumVertex(); i++)
    {
        idNode = map->getVertexSet().at(i)->getInfo()->getIdNode();
        X = map->getVertexSet().at(i)->getInfo()->getX();
        Y = map->getVertexSet().at(i)->getInfo()->getY();
        gv->addNode(idNode, X, Y);
    }

    for (int i = 0; i < map->getNumVertex(); i++)
    {
        for (int j = 0; j < map->getVertexSet().at(i)->getAdjSet().size(); j++)
        {
            gv->addEdge(idEdge,
                        map->getVertexSet().at(i)->getInfo()->getIdNode(),
                        map->getVertexSet().at(i)->getAdjSet().at(j).getDest()->getInfo()->getIdNode(),
                        EdgeType::DIRECTED); // edgetype still coiso
            idEdge++;
        }
    }

    gv->rearrange();
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
    int counter;

    Node node(idNode, X, Y);

    std::cout << "\n Carregando os Nodes!\n"
              << endl;

    getline(fin, line); // number of nodes
    numberOfNodes = stoi(line);

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

        //showLoadProgress(counter, numberOfNodes, "nodes");
    }

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

    std::cout << "\n Carregando as Edges!\n"
              << endl;

    getline(fin, line); // number of edges
    numberOfEdges = stoi(line);

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
        map->addEdge(nodeOrigin, nodeDestiny, 0);

        showLoadProgress(counter, numberOfEdges, "Edge");
        counter++;
    }

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
    string tag;

    std::cout << "\n Carregando as Tags!\n"
              << endl;

    getline(fin, line); // number of tags
    numberOfTags = stoi(line);

    while (!fin.eof())
    {
        getline(fin, tag); // tagname

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
    }

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

void showLoadProgress(int counter, int number, std::string type)
{
    double percentage;

    std::cout << "Processing " << number << " " << type << "s ..." << endl << endl;

    percentage = (100 * counter) / (double) number;

    std::cout << "\r";
    std::cout << "[" << type << " " << counter << " of " << number << " ] ";
    std::cout << fixed << setprecision(2) << percentage << '%' << endl << endl << endl;
}