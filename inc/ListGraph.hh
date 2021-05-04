#pragma once

#include <iostream>
#include "Graph.hh"
#include "Edge.hh"

struct node
{
    int index;
    int weight;
    Edge *edge;
    node *next = nullptr;

    node(int i, int w, Edge *e, node *n = nullptr) : index(i), weight(w), edge(e), next(n) {}
};

class ListGraph : Graph
{
private:
    node **list;
    Edge **edgeList;

public:
    ListGraph(int vertCount, int edgCount);
    ~ListGraph();
    void addEdge(int src, int dst, int weight);
    bool hasEdge(int src, int dst);
    void print();
    void sort();
    int kruskal();
    int kruskal2();
    int prim();
};