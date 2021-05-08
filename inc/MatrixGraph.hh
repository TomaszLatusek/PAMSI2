#pragma once

#include <iostream>
#include "Graph.hh"
#include "Edge.hh"

class MatrixGraph : Graph
{
    Edge ***matrix;
    Edge **edgeList;

public:
    MatrixGraph(int verticesCount, int edgCount );
    ~MatrixGraph();
    void addEdge(int src, int dst, int weight);
    bool hasEdge(int src, int dst);
    void print();
    void sort();
    int kruskal();
    int prim();
};