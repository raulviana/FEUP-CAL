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
    loadTags(tagFile);

    //cout << "antes: " << map->getNumVertex() << endl;
    removeNotConnectedNodes();
    //cout << "depois: " << map->getNumVertex() << endl;
    removeExtraEdges();
    initGraphViewer();
}

void Map::initGraphViewer()
{
    double graphHeight = map->getLimitTop() - map->getLimitBot();
    double graphWidth = map->getLimitRight() - map->getLimitLeft();

    int windowHeight = 800;
    int windowWidth = max((int)(windowHeight * graphWidth / graphHeight), 800);
    GraphViewer *gv = new GraphViewer(windowWidth, windowHeight, false);

    gv->createWindow(windowWidth, windowHeight);

    gv->defineEdgeColor("blue");
    gv->defineVertexColor("yellow");

    gv->defineVertexSize(5);

    loadNodesToGraphViewer(gv, graphHeight, graphWidth, windowHeight, windowWidth);
    loadEdgesToGraphViewer(gv);

    gv->rearrange();
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

    for (int i = 0; i < map->getNumVertex(); i++)
    {
        for (int j = 0; j < map->getVertexSet().at(i)->getAdjSet().size(); j++)
        {
            idNode1 = map->getVertexSet().at(i)->getInfo()->getIdNode();
            idNode2 = map->getVertexSet().at(i)->getAdjSet().at(j).getDest()->getInfo()->getIdNode();

            if (map->getVertexSet().at(i)->getAdjSet().at(j).isUndirected())
            {
                gv->addEdge(idEdge,
                            idNode1,
                            idNode2,
                            EdgeType::UNDIRECTED);
                cout << "meeeeeeeeeeeeeee";
            }
            else
            {
                gv->addEdge(idEdge,
                            idNode1,
                            idNode2,
                            EdgeType::DIRECTED);
            }

            gv->setEdgeWeight(idEdge, map->getVertexSet().at(i)->getAdjSet().at(j).getWeight());
            idEdge++;
        }
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
    string tag;

    getline(fin, line); // number of tags
    numberOfTags = stoi(line);

    std::cout << "\n-------------------------------------------\n\n";
    std::cout << " Processing " << numberOfTags << " Tags ..." << endl
              << endl;

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

        showLoadProgress(counter, numberOfTags, "Tag");
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

void Map::removeExtraEdges()
{
    auto vec = map->getVertexSet();
    auto first = vec.begin();

    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet();
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            auto vec3 = (*second).getDest()->getAdjSet();
            auto third = vec3.begin();

            while (third != vec3.end())
            {
                if ((*third).getDest()->getInfo()->getIdNode() == (*first)->getInfo()->getIdNode())
                {
                    //cout << "here\n";
                    map->removeEdge((*first)->getInfo(), (*third).getDest()->getInfo());
                    (*second).setUndirected(true);
                    break;
                }
                ++third;
            }

            ++second;
        }
        ++first;
    }
}

void Map::removeNotConnectedNodes()
{
    auto vec = map->getVertexSet();
    auto first = vec.begin();

    while (first != vec.end())
    {
        if ((*first)->getAdjSet().size() == 0)
        {
            map->removeVertex((*first)->getInfo());
        }
        ++first;
    }

    vec = map->getVertexSet();
    first = vec.begin();

    while (first != vec.end())
    {
        auto vec2 = (*first)->getAdjSet();
        auto second = vec2.begin();

        while (second != vec2.end())
        {
            if ((*second).getDest()->getInfo()->getIdNode() == (*first)->getInfo()->getIdNode())
            {
                //cout << "here2" << endl;
                map->removeEdge((*first)->getInfo(), (*first)->getInfo());
            }
            second++;
        }
        first++;
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