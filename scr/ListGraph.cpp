#include "../inc/ListGraph.hh"
#include <iostream>
#include <algorithm>

ListGraph::ListGraph(int vertCount, int edgCount)
{
    verticesCount = vertCount;
    edgesCount = 0;

    edgeList = new Edge *[edgCount];
    parent = new int[verticesCount];
    key = new int[verticesCount];
    mstSet = new bool[verticesCount];
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
    list[src] = new node{dst, weight, list[src]};
    list[dst] = new node{src, weight, list[dst]};

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

int ListGraph::prim()
{
    mst = 0;

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

int ListGraph::kruskal()
{
    mst = 0;
    
    for (int i = 0; i < verticesCount; i++)
    {
        parent[i] = i;
    }

    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });

    int mst = 0;
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

void ListGraph::sort()
{
    std::sort(edgeList, edgeList + edgesCount, [](Edge *a, Edge *b) { return a->weight < b->weight; });
}