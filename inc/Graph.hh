#pragma once
#include <stdlib.h>
#include <iostream>

class Graph
{
public:
    int verticesCount, edgesCount;
    int *parent, *key;
    bool *mstSet;

    virtual void addEdge(int src, int dst, int weight) = 0;
    virtual bool hasEdge(int src, int dst) = 0;

    int find(int i)
    {
        while (parent[i] != i)
        {
            i = parent[i];
        }
        return i;
    }
    void union1(int i, int j)
    {
        int a = find(i);
        int b = find(j);
        parent[a] = b;
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
        T *graph = new T(vertCount);
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

// class Graph
// {
// public:
//     int vertCount, edgesCount, startVertex, type;

//     Graph()
//     {
//         this->edgesCount = 0;
//     }

//     Graph(int size, int start)
//     {
//         this->vertCount = size;
//         this->edgesCount = 0;
//         this->startVertex = start;
//     }

//     ~Graph()
//     {
//         // printf("~Graph\n");
//     }

//     // virtual Edge** operator[](std::size_t idx) = 0;
//     virtual void addEdge(int src, int dest, int weight) = 0;
//     virtual List<Edge *> *getNeighbours(int id) = 0;
//     virtual bool hasEdge(int src, int dst) = 0;

//     float density()
//     {
//         return (float)(2 * this->edgesCount) / (this->vertCount * (this->vertCount - 1));
//     }

//     template <typename T>
//     static T *generate_random(int vertCount, int min_weight, int max_weight, float density)
//     {
//         int edges_count = (vertCount * (vertCount - 1) * density) / 2;
//         // printf("Generating %d edges...\n", edges_count);
//         T *graf = new T(vertCount, random<int>(0, vertCount - 1));
//         if (density == 1)
//         {
//             for (int i = 0; i < vertCount; ++i)
//             {
//                 for (int j = i + 1; j < vertCount; ++j)
//                 {
//                     // printf("i: %d, j: %d \n",i,j);
//                     int weight = random<int>(min_weight, max_weight);
//                     graf->addEdge(i, j, weight);
//                 }
//             }
//         }
//         else
//         {
//             while (edges_count)
//             {
//                 int source = random<int>(0, vertCount - 1);
//                 int destination = random<int>(0, vertCount - 1);
//                 if (graf->hasEdge(source, destination))
//                     continue;
//                 int weight = random<int>(min_weight, max_weight);
//                 graf->addEdge(source, destination, weight);
//                 edges_count--;
//             }
//         }

//         return graf;
//     }
// };