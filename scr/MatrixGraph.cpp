#include "../inc/MatrixGraph.hh"
#include <iostream>
#include <algorithm>

MatrixGraph::MatrixGraph(int vertCount, int edgCount)
{
    verticesCount = vertCount;
    edgesCount = 0;
    parent = new int[verticesCount];

    // key = new int[verticesCount];
    // mstSet = new bool[verticesCount];

    matrix = new Edge **[verticesCount];
    edgeList = new Edge *[edgCount];

    for (int i = 0; i < verticesCount; i++)
    {
        matrix[i] = new Edge *[verticesCount];
        for (int j = 0; j < verticesCount; j++)
        {
            matrix[i][j] = nullptr;
        }
    }
    // verticesCount = verticesCount;
    // edgesCount = (verticesCount * (verticesCount - 1) * density) / 200;

    // matrix = new Edge **[verticesCount];
    // if (density == 100)
    // {
    //     for (int i = 0; i < verticesCount; i++)
    //     {
    //         matrix[i] = new Edge *[verticesCount];
    //         for (int j = 0; j < verticesCount; j++)
    //         {
    //             int weight = rand() % 25 + verticesCount - 1;
    //             this->addEdge(i, j, weight);
    //         }
    //     }
    // }
}

MatrixGraph::~MatrixGraph()
{
    for (int i = 0; i < verticesCount; ++i)
    {
        for (int j = 0; j < this->verticesCount; ++j)
        {
            delete matrix[i][j];
            // this->adjacencyMatrix[i][j] = nullptr;
        }
        delete[] matrix[i];
        // this->adjacencyMatrix[i] = nullptr;
    }
    delete[] matrix;
}

void MatrixGraph::addEdge(int src, int dst, int weight)
{

    if (src != dst)
    {
        Edge *e1 = new Edge(src, dst, weight);
        matrix[src][dst] = e1;
        e1 = nullptr;

        Edge *e2 = new Edge(dst, src, weight);
        matrix[dst][src] = e2;
        e2 = nullptr;
    }

    edgesCount++;
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

// int MatrixGraph::find(int i)
// {
//     while (parent[i] != i)
//     {
//         i = parent[i];
//     }
//     return i;
// }

// void MatrixGraph::union1(int i, int j)
// {
//     int a = find(i);
//     int b = find(j);
//     parent[a] = b;
// }

int MatrixGraph::kruskal()
{
    int mst = 0;

    for (int i = 0; i < verticesCount; i++)
    {
        parent[i] = i;
    }

    int edgeCount = 0;
    while (edgeCount < verticesCount - 1)
    {
        int min = 1000, a = -1, b = -1;
        for (int i = 0; i < verticesCount; i++)
        {
            for (int j = i + 1; j < verticesCount; j++)
            {
                if (matrix[i][j])
                {
                    if (find(i) != find(j) && matrix[i][j]->weight < min)
                    {
                        min = matrix[i][j]->weight;
                        a = i;
                        b = j;
                    }
                }
            }
        }
        union1(a, b);
        mst += min;
        edgeCount++;
    }
    return mst;
}

// int MatrixGraph::minKey(int key[], bool mstSet[])
// {
//     int min = 1000, min_index;

//     for (int v = 0; v < verticesCount; v++)
//         if (mstSet[v] == false && key[v] < min)
//             min = key[v], min_index = v;

//     return min_index;
// }

int MatrixGraph::prim()
{
    int *parent = new int[verticesCount];
    int *key = new int[verticesCount];
    bool *mstSet = new bool[verticesCount];
    int mst = 0;

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

int MatrixGraph::kruskal2()
{
    for (int i = 0; i < verticesCount; i++)
    {
        parent[i] = i;
    }

    int m = 0;
    for (int i = 0; i < verticesCount; i++)
    {
        for (int j = i + 1; j < verticesCount; j++)
        {
            if (matrix[i][j])
            {
                edgeList[m] = matrix[i][j];
                m++;
            }
        }
    }

    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });

    // for (int i = 0; i < edgesCount; i++)
    // {
    //     std::cout << edgeList[i]->weight << " " << edgeList[i]->source << " " << edgeList[i]->destination << std::endl;
    // }

    int mst = 0;
    int uRep, vRep;
    for (int i = 0; i < edgesCount; i++)
    {
        // if (!parent[edgeList[i]->source] || !parent[edgeList[i]->destination])
        // {
        //     parent[edgeList[i]->source] = 1;
        //     parent[edgeList[i]->destination] = 1;
        //     mst += edgeList[i]->weight;
        // }
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

// int MatrixGraph::prim2()
// {

// }