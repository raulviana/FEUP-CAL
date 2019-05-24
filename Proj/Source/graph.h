/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdbool.h>
#include <cmath>
#include <limits>
#include <list>
#include <queue>
#include <vector>

#include "MutablePriorityQueue.h"

using namespace std;

template <class T>
class Edge;
template <class T>
class Graph;
template <class T>
class Vertex;

#define INF std::numeric_limits<double>::max()

/****************** Structures  ********************/

/************************* Vertex  **************************/
template <class T>
class Vertex
{
    T info;              // contents
    vector<Edge<T>> adj; // list of outgoing edges
    bool visited;        // auxiliary field used by dfs and bfs
    int indegree;        // auxiliary field used by topsort
    double dist = 0;
    Vertex<T> *path = NULL;
    int queueIndex = 0; // required by MutablePriorityQueue
    bool processing;    // auxiliary field used by isDAG

    void addEdge(Vertex<T> *dest, double w, int id);
    bool removeEdgeTo(Vertex<T> *d);

public:
    Vertex(T in);
    bool operator<(Vertex<T> &vertex) const; // // required by MutablePriorityQueue
    T getInfo() const;
    double getDist() const;
    Vertex *getPath() const;
    vector<Edge<T>> getAdjSet() const;

    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};

/********************** Edge  ****************************/

template <class T>
class Edge
{
    Vertex<T> *dest; // destination vertex
    double weight;   // edge weight
    int ID;

public:
    Edge(Vertex<T> *d, double w, int id);
    Vertex<T> *getDest();
    double getWeight();
    int getID();
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph
{
    vector<Vertex<T> *> vertexSet; // vertex set
    double **W = nullptr;          // dist
    int **P = nullptr;             // path
    int findVertexIdx(const T &in) const;

    void dfsVisit(Vertex<T> *v, vector<T> &res) const;
    bool dfsIsDAG(Vertex<T> *v) const;

public:
    ~Graph();
    int getNumVertex() const;
    bool addVertex(const T &in);
    bool removeVertex(const T &in);
    bool addEdge(const T &sourc, const T &dest, double w, int id);
    bool removeEdge(const T &sourc, const T &dest);
    vector<T> dfs() const;
    vector<T> bfs(const T &source) const;
    vector<T> topsort() const;
    int maxNewChildren(const T &source, T &inf) const;
    bool isDAG() const;
    Vertex<T> *findVertex(const T &in) const;
    vector<Vertex<T> *> getVertexSet() const;

    // Single source
    void dijkstraShortestPath(const T &s);
    bool analize(Vertex<T> *v, Vertex<T> *w, double weight);
    void dijkstraShortestPathOld(const T &s);
    void unweightedShortestPath(const T &s);
    void bellmanFordShortestPath(const T &s);
    vector<T> getPath(const T &origin, const T &dest);
    double getDistOfVertex(const T &content);

    //Duoble Source

    // All pairs
    void floydWarshallShortestPath();
    vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
};

/****************** Constructors and functions ********************/

/************************* Vertex  **************************/
template <class T>
Vertex<T>::Vertex(T in) : info(in) {}

template <class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const
{
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const
{
    return this->info;
}

template <class T>
double Vertex<T>::getDist() const
{
    return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const
{
    return this->path;
}

template <class T>
vector<Edge<T>> Vertex<T>::getAdjSet() const
{
    return this->adj;
}

/************************* Edge  **************************/
template <class T>
Edge<T>::Edge(Vertex<T> *d, double w, int id) : dest(d), weight(w)
{
    this->ID = id;
}

template <class T>
Vertex<T> *Edge<T>::getDest()
{
    return this->dest;
}

template <class T>
double Edge<T>::getWeight()
{
    return this->weight;
}

template <class T>
int Edge<T>::getID()
{
    return this->ID;
}

/*************************** Graph  **************************/
template <class T>
int Graph<T>::getNumVertex() const
{
    return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const
{
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> *Graph<T>::findVertex(const T &in) const
{
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in)
{
    if (findVertex(in) != NULL)
        return false;

    vertexSet.push_back(new Vertex<T>(in));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w, int id)
{
    Vertex<T> *vs = findVertex(sourc);
    Vertex<T> *vd = findVertex(dest);

    if (vs == NULL || vd == NULL)
        return false;

    vs->addEdge(vd, w, id);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w, int id)
{
    adj.push_back(Edge<T>(d, w, id));
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest)
{
    Vertex<T> *va = findVertex(sourc);
    Vertex<T> *vd = findVertex(dest);

    if (va == NULL || vd == NULL)
        return false;

    return va->removeEdgeTo(vd);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d)
{
    for (typename vector<Edge<T>>::iterator it = adj.begin(); it != adj.end(); it++)
        if (it->dest == d)
        {
            adj.erase(it);
            return true;
        }

    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in)
{
    if (findVertex(in) == NULL)
        return false;

    for (typename vector<Vertex<T> *>::iterator it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info == in)
        {
            Vertex<T> *v = *it;
            vertexSet.erase(it);
            for (Vertex<T> *u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }

    return false;
}

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const
{
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;

    for (auto v : vertexSet)
        if (!v->visited)
            dfsVisit(v, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> &res) const
{
    v->visited = true;
    res.push_back(v->info);

    for (auto edge : v->adj)
    {
        Vertex<T> *w = edge.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T &source) const
{
    vector<T> res;
    queue<Vertex<T> *> Q;
    Vertex<T> *s = findVertex(source);

    if (s == NULL)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    Q.push(s);
    s->visited = true;

    while (!Q.empty())
    {
        Vertex<T> *v = Q.front();
        Q.pop();
        res.push_back(v->info);

        for (auto w : v->adj)
        {
            if (!w.dest->visited)
            {
                Q.push(w.dest);
                w.dest->visited = true;
            }
        }
    }

    return res;
}

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template <class T>
vector<T> Graph<T>::topsort() const
{
    vector<T> res;

    for (auto v : vertexSet)
        v->indegree = 0;

    for (auto v : vertexSet)
        for (auto w : v->adj)
            w.dest->indegree++;

    queue<Vertex<T> *> C;

    for (auto v : vertexSet)
        if (v->indegree == 0)
        {
            C.push(v);
        }

    while (!C.empty())
    {
        Vertex<T> *v = C.front();
        C.pop();
        res.push_back(v->info);
        for (auto w : v->adj)
        {
            Vertex<T> *e = w.dest;
            e->indegree--;
            if (e->indegree == 0)
                C.push(e);
        }
    }

    if (res.size() != vertexSet.size())
    {
        std::cout << "FAIL - O grafo tem ciclos!\n";
        res.clear();
    }

    return res;
}

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T &source, T &inf) const
{
    queue<Vertex<T> *> Q;
    Vertex<T> *s = findVertex(source);

    if (s == NULL)
        return 0;

    int maxChild = 0;
    inf = s->info;

    for (auto v : vertexSet)
        v->visited = false;

    Q.push(s);
    s->visited = true;

    while (!Q.empty())
    {
        Vertex<T> *v = Q.front();
        Q.pop();
        int children = 0;

        for (auto w : v->adj)
        {
            if (!w.dest->visited)
            {
                w.dest->visited = true;
                Q.push(w.dest);
                children++;
            }
        }

        if (children > maxChild)
        {
            maxChild = children;
            inf = v->info;
        }
    }

    return maxChild;
}

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const
{
    for (auto v : vertexSet)
    {
        v->visited = false;
        v->processing = false;
    }

    for (auto v : vertexSet)
        if (!v->visited)
            if (!dfsIsDAG(v))
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const
{
    v->processing = true;
    v->visited = true;

    for (auto edge : v->adj)
    {
        Vertex<T> *w = edge.dest;
        if (w->processing)
            return false;

        if (!w->visited)
            if (!dfsIsDAG(w))
            {
                return false;
            }
    }
    v->processing = false;
    return true;
}

/********************************************************************/
/**************** Single Source Shortest Path algorithms ************/

template <class T>
void Graph<T>::dijkstraShortestPath(const T &origin)
{
    for (unsigned int i = 0; i < vertexSet.size(); i++)
    {
        vertexSet.at(i)->dist = INF;
        vertexSet.at(i)->path = NULL;
    }

    Vertex<T> *s = findVertex(origin);

    s->dist = 0;

    MutablePriorityQueue<Vertex<T>> q;

    q.insert(s);

    while (!q.empty())
    {
        Vertex<T> *v = q.extractMin();

        for (unsigned int i = 0; i < v->adj.size(); i++)
        {
            double oldDist = v->adj.at(i).dest->dist;

            if (analize(v, v->adj.at(i).dest, v->adj.at(i).weight))
            {
                if (oldDist == INF)
                {
                    q.insert(v->adj.at(i).dest);
                }
                else
                {
                    q.decreaseKey(v->adj.at(i).dest);
                }
            }
        }
    }
}

template <class T>
bool Graph<T>::analize(Vertex<T> *v, Vertex<T> *w, double weight)
{
    if (v->dist + weight < w->dist)
    {
        w->dist = v->dist + weight;
        w->path = v;
        return true;
    }
    else
        return false;
}

template <class T>
vector<T> Graph<T>::getPath(const T &origin, const T &dest)
{
    vector<T> res;
    Vertex<T> *v = findVertex(dest);

    if (v == nullptr || v->dist == INF) // missing or disconnected
        return res;

    for (; v != nullptr; v = v->path)
    {
        res.push_back(v->info);
    }

    reverse(res.begin(), res.end());

    return res;
}

template <class T>
double Graph<T>::getDistOfVertex(const T &content)
{
    return findVertex(content)->getDist();
}

template <class T>
void Graph<T>::unweightedShortestPath(const T &orig)
{
    for (unsigned int i = 0; i < vertexSet.size(); i++)
    {
        vertexSet.at(i)->dist = INF;
        vertexSet.at(i)->path = NULL;
    }

    Vertex<T> *s = findVertex(orig);

    s->dist = 0;

    queue<Vertex<T> *> q;

    q.push(s);

    while (!q.empty())
    {
        Vertex<T> *v = q.front();
        q.pop();

        for (unsigned int i = 0; i < v->adj.size(); i++)
        {
            double oldDist = v->adj.at(i).dest->dist;

            if (oldDist == INF)
            {
                v->adj.at(i).dest->path = v;
                v->adj.at(i).dest->dist = v->dist + 1;
                q.push(v->adj.at(i).dest);
            }
        }
    }
}

template <class T>
void Graph<T>::bellmanFordShortestPath(const T &orig)
{
    for (unsigned int i = 0; i < vertexSet.size(); i++)
    {
        vertexSet.at(i)->dist = INF;
        vertexSet.at(i)->path = nullptr;
    }

    Vertex<T> *s = findVertex(orig);

    s->dist = 0;

    for (unsigned i = 1; i < vertexSet.size(); i++)
        for (auto v : vertexSet)
            for (auto e : v->adj)
                analize(v, e.dest, e.weight);
}

/**************** All Pairs Shortest Path  ***************/

/*
 * Finds the index of the vertex with a given content.
 */
template <class T>
int Graph<T>::findVertexIdx(const T &in) const
{
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->info == in)
            return i;
    return -1;
}
template <class T>
void deleteMatrix(T **m, int n)
{
    if (m != nullptr)
    {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}
template <class T>
Graph<T>::~Graph()
{
    deleteMatrix(W, vertexSet.size());
    deleteMatrix(P, vertexSet.size());
}

template <class T>
void Graph<T>::floydWarshallShortestPath()
{
    unsigned n = vertexSet.size();
    deleteMatrix(W, n);
    deleteMatrix(P, n);
    W = new double *[n];
    P = new int *[n];
    for (unsigned i = 0; i < n; i++)
    {
        W[i] = new double[n];
        P[i] = new int[n];
        for (unsigned j = 0; j < n; j++)
        {
            W[i][j] = i == j ? 0 : INF;
            P[i][j] = -1;
        }
        for (auto e : vertexSet[i]->adj)
        {
            int j = findVertexIdx(e.dest->info);
            W[i][j] = e.weight;
            P[i][j] = i;
        }
    }

    for (unsigned k = 0; k < n; k++)
        for (unsigned i = 0; i < n; i++)
            for (unsigned j = 0; j < n; j++)
            {
                if (W[i][k] == INF || W[k][j] == INF)
                    continue; // avoid overflow
                int val = W[i][k] + W[k][j];
                if (val < W[i][j])
                {
                    W[i][j] = val;
                    P[i][j] = P[k][j];
                }
            }
}

template <class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const
{
    vector<T> res;
    int i = findVertexIdx(orig);
    int j = findVertexIdx(dest);
    if (i == -1 || j == -1 || W[i][j] == INF) // missing or disconnected
        return res;
    for (; j != -1; j = P[i][j])
        res.push_back(vertexSet[j]->info);
    reverse(res.begin(), res.end());
    return res;
}

#endif /* GRAPH_H_ */