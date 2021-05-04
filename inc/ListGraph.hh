#pragma once

#include <iostream>
#include "Graph.hh"
#include "Edge.hh"

struct node
{
    int index;
    int weight;
    node *next = nullptr;

    node(int i, int w, node *n = nullptr) : index(i), weight(w), next(n) {}
};

class ListGraph : Graph
{
private:
    node **list;

public:
    ListGraph(int vertCount);
    ~ListGraph();
    void addEdge(int src, int dst, int weight);
    bool hasEdge(int src, int dst);
    void print();
    int kruskal();
    int prim();
};