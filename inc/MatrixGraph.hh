#pragma once

#include <iostream>
#include "Graph.hh"
#include "Edge.hh"

class MatrixGraph : Graph
{
    Edge ***matrix;
    Edge **edgeList;

public:
    MatrixGraph(int verticesCount /* , int density */);
    ~MatrixGraph();
    void addEdge(int src, int dst, int weight);
    bool hasEdge(int src, int dst);
    void print();
    int kruskal();
    int kruskal2();
    int prim();
    // int prim2();
    // int getVert(){return verticesCount;};
};