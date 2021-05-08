#pragma once
#include <stdlib.h>
#include <iostream>

class Graph
{
public:
    int verticesCount, edgesCount, mst;
    int *parent, *key;
    bool *mstSet;

    virtual void addEdge(int src, int dst, int weight) = 0;
    virtual bool hasEdge(int src, int dst) = 0;

    int find(int i)
    {
        if (i == parent[i])
            return i;
        else
            return find(parent[i]);
    }
    void union1(int i, int j)
    {
        parent[i] = parent[j];
    }
    int minKey(int key[], bool mstSet[])
    {
        int min = 1000, minIndex;

        for (int v = 0; v < verticesCount; v++)
            if (mstSet[v] == false && key[v] < min)
            {
                min = key[v];
                minIndex = v;
            }

        return minIndex;
    }

    template <typename T>
    static T *generateRandom(int vertCount, int density)
    {
        int edgCount = (vertCount * (vertCount - 1) * density) / 200;
        T *graph = new T(vertCount, edgCount);
        if (density == 100)
        {
            for (int i = 0; i < vertCount; ++i)
            {
                for (int j = i + 1; j < vertCount; ++j)
                {
                    int wght = rand() % 25 + 1;
                    graph->addEdge(i, j, wght);
                }
            }
        }
        else
        {
            while (edgCount)
            {
                int src = rand() % vertCount;
                int dst = rand() % vertCount;
                if (graph->hasEdge(src, dst))
                    continue;
                int wght = rand() % 25 + 1;
                graph->addEdge(src, dst, wght);
                edgCount--;
            }
        }

        return graph;
    }
};
