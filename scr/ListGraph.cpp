#include "../inc/ListGraph.hh"
#include <iostream>
#include <algorithm>

ListGraph::ListGraph(int vertCount, int edgCount)
{
    verticesCount = vertCount;
    edgesCount = 0;
    edgeList = new Edge *[edgCount];

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
    Edge *e = new Edge(src, dst, weight);
    list[src] = new node{dst, weight, e, list[src]};
    list[dst] = new node{src, weight, e, list[dst]};

    edgeList[edgesCount++] = e;
    e = nullptr;
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
                if (find(i) != find(x->edge->source) && x->edge->weight < min)
                {
                    min = x->edge->weight;
                    a = i;
                    b = x->edge->source;
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
            if (mstSet[x->index] == false && x->edge->weight < key[x->index])
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

int ListGraph::kruskal2()
{
    for (int i = 0; i < verticesCount; i++)
    {
        parent[i] = i;
    }

    int m = 0, n = 0;
    node *x;

    // for (int i = 0; i < verticesCount; i++)
    // {
    //     x = list[i];
    //     while (x)
    //     {
    //         edgeList[m] = x->edge;
    //         m++;
    //         // for (int j = 0; j < edgesCount; j++)
    //         // {
    //         //     //std::cout << edgeList[i];

    //         //     if (x->edge == edgeList[j])
    //         //     {
    //         //         continue;
    //         //     }
    //         //     edgeList[m] = x->edge;
    //         //     m++;
    //         // }
    //         x = x->next;
    //     }
    // }

    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });

    // for (int i = 0; i < 6; i++)
    // {
    //     std::cout << edgeList[i]->source << " " << edgeList[i]->destination << " " << edgeList[i]->weight << std::endl;
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