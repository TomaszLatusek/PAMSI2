#include "../inc/ListGraph.hh"
#include <iostream>

ListGraph::ListGraph(int vertCount)
{
    verticesCount = vertCount;
    edgesCount = 0;
    parent = new int[verticesCount];

    list = new node *[verticesCount];
    for (int i = 0; i < verticesCount; i++)
    {
        list[i] = nullptr;
    }
}

ListGraph::~ListGraph()
{
    node *ptr = nullptr;
    node *ptrToDelete = nullptr;
    for (int i = 0; i < verticesCount; ++i)
    {
        ptr = list[i];
        while (ptr)
        {
            ptrToDelete = ptr;
            ptr = ptr->next;
            delete ptrToDelete;
        }
    }
    delete[] list;
}

void ListGraph::addEdge(int src, int dst, int weight)
{
    list[src] = new node{dst, weight, list[src]};
    list[dst] = new node{src, weight, list[dst]};
}

bool ListGraph::hasEdge(int src, int dst)
{
    node *x;
    x = list[src];
    while (x)
    {
        if (x->index == dst)
        {
            return true;
        }
        x = x->next;
    }
}

void ListGraph::print()
{
    node *x;
    for (int i = 0; i < verticesCount; i++)
    {
        x = list[i];
        std::cout << i << ": ";
        while (x)
        {
            std::cout << x->index << "(" << x->weight << ") ";
            x = x->next;
        }
        std::cout << std::endl;
    }
}

// int ListGraph::find(int i)
// {
//     while (parent[i] != i)
//     {
//         i = parent[i];
//     }
//     return i;
// }

// void ListGraph::union1(int i, int j)
// {
//     int a = find(i);
//     int b = find(j);
//     parent[a] = b;
// }

int ListGraph::kruskal()
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
        node *x;
        for (int i = 0; i < verticesCount; i++)
        {
            x = list[i];
            while (x)
            {
                if (find(i) != find(x->index) && x->weight < min)
                {
                    min = x->weight;
                    a = i;
                    b = x->index;
                }
                x = x->next;
            }
        }
        union1(a, b);
        mst += min;
        edgeCount++;
    }
    return mst;
}

int ListGraph::prim()
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

    node *x;

    for (int count = 0; count < verticesCount - 1; count++)
    {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        x = list[u];

        while (x)
        {
            if (mstSet[x->index] == false && x->weight < key[x->index])
            {
                parent[x->index] = u;
                key[x->index] = x->weight;
            }
            x = x->next;
        }
    }
    for (int i = 0; i < verticesCount; i++)
    {
        mst += key[i];
    }
    return mst;
}