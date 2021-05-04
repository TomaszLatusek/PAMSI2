#pragma once

class Edge
{
public:
    int source, destination, weight;

    Edge(int source, int destination, int weight)
    {
        this->source = source;
        this->destination = destination;
        this->weight = weight;
    }

    bool operator<(Edge const &b)
    {
        return weight < b.weight;
    }
    friend bool operator<=(Edge const &a, Edge const &b)
    {
        return a.weight <= b.weight;
    }
    friend bool operator>(Edge const &a, Edge const &b)
    {
        return a.weight > b.weight;
    }
    friend bool operator>=(Edge const &a, Edge const &b)
    {
        return a.weight >= b.weight;
    }
    friend bool operator==(Edge const &a, Edge const &b)
    {
        return a.weight == b.weight;
    }
};