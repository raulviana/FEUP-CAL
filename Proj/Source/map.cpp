#include <fstream>
#include <sstream>

#include "map.h"

Map::Map(std::string mapName)
{
    std::string nodeFile = "../Maps/" + mapName + "/T04_nodes_X_Y_" + mapName + ".txt";
    //setupGraphViewer();
    loadNodes(nodeFile);
    std::string edgeFile = "../Maps/" + mapName + "/T04_edges_" + mapName + ".txt";
    loadEdges(edgeFile);
}

void Map::setupGraphViewer()
{
    GraphViewer *gv = new GraphViewer(1000, 600, false);

    gv->createWindow(1000, 600);

    gv->defineEdgeColor("blue");
    gv->defineVertexColor("yellow");
}

void Map::loadNodes(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int it = 0;
    int idNode = 0;
    double X = 0;
    double Y = 0;

    Node node(idNode, X, Y);

    getline(fin, line);

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

        node.setNode(idNode, X, Y);
        map->addVertex(&node);
    }

    fin.close();
}

void Map::loadEdges(std::string filename)
{
    std::ifstream fin;
    fin.open(filename);

    if (!fin)
    {
        cerr << "Unable to open file " << filename << endl;
        exit(1); // call system to stop
    }

    std::string line;
    int it = 0;
    int idNodeOrigin = 0;
    int idNodeDestiny = 0;

    getline(fin, line);

    while (!fin.eof())
    {
        getline(fin, line); // (idNodeOrigin, idNodeDestiny)
        line = line.substr(1, string::npos);

        it = line.find(",");
        idNodeOrigin = stoi(line.substr(0, it));
        line.erase(0, it + 2);

        it = line.find(")");
        idNodeDestiny = stod(line.substr(0, it));
    }

    fin.close();
}

Node *Map::findNode() {
    for (unsigned int i = 0; i < map->getNumVertex; i++) {
        //if (map->getVertexSet().at(i)->getInfo)

    }
}