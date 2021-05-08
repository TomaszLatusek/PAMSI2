#include "../inc/MatrixGraph.hh"
#include <iostream>
#include <algorithm>

MatrixGraph::MatrixGraph(int vertCount, int edgCount)
{
    verticesCount = vertCount;
    edgesCount = 0;

    parent = new int[verticesCount];
    matrix = new Edge **[verticesCount];
    edgeList = new Edge *[edgCount];
    key = new int[verticesCount];
    mstSet = new bool[verticesCount];

    for (int i = 0; i < verticesCount; i++)
    {
        matrix[i] = new Edge *[verticesCount];
        for (int j = 0; j < verticesCount; j++)
        {
            matrix[i][j] = nullptr;
        }
    }
}

MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < verticesCount; ++i)
    {
        for (int j = 0; j < this->verticesCount; ++j)
        {
            delete matrix[i][j];
        }
        delete[] matrix[i];
    }
    delete[] matrix;
}

void MatrixGraph::addEdge(int src, int dst, int weight)
{

    if (src != dst)
    {
        Edge *e1 = new Edge(src, dst, weight);
        matrix[src][dst] = e1;

        Edge *e2 = new Edge(dst, src, weight);
        matrix[dst][src] = e2;
        e2 = nullptr;

        edgeList[edgesCount++] = e1;
        e1 = nullptr;
    }
}

bool MatrixGraph::hasEdge(int src, int dst)
{
    return matrix[src][dst] != nullptr;
}

void MatrixGraph::print()
{
    for (int i = 0; i < verticesCount; i++)
    {
        for (int j = 0; j < verticesCount; j++)
        {
            if (matrix[i][j] == nullptr)
            {
                std::cout << 0 << " ";
            }
            else
            {
                std::cout << matrix[i][j]->weight << " ";
            }
        }
        std::cout << std::endl;
    }
}


int MatrixGraph::prim()
{
    mst = 0;

    for (int i = 0; i < verticesCount; i++)
    {
        key[i] = 1000;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < verticesCount - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < verticesCount; v++)
        {
            if (matrix[u][v] && mstSet[v] == false && matrix[u][v]->weight < key[v])
            {
                parent[v] = u;
                key[v] = matrix[u][v]->weight;
            }
        }
    }
    for (int i = 0; i < verticesCount; i++)
    {
        mst += key[i];
    }
    return mst;
}

int MatrixGraph::kruskal()
{
    mst = 0;

    for (int i = 0; i < verticesCount; i++)
    {
        parent[i] = i;
    }

    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });

    int uRep, vRep;
    for (int i = 0; i < edgesCount; i++)
    {
        uRep = find(edgeList[i]->source);
        vRep = find(edgeList[i]->destination);

        if (uRep != vRep)
        {
            mst += edgeList[i]->weight;
            union1(uRep, vRep);
        }
    }

    return mst;
}

void MatrixGraph::sort()
{
    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });
}
