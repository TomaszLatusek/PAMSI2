// #include <algorithm>
// #include <iostream>
// #include <vector>
// #include "Graph.hh"

// using namespace std;

// #define edge pair<int, int>

// class GrafXDD : Graph
// {
// private:
//     vector<pair<int, edge>> G; // graph
//     vector<pair<int, edge>> T; // mst
//     int *parent;
//     int V; // number of vertices/nodes in graph
// public:
//     GrafXDD(int V);
//     void addEdge(int u, int v, int w);
//     bool hasEdge(int src, int dst);
//     int find_set(int i);
//     void union_set(int u, int v);
//     void kruskal();
//     void print();
// };

// bool GrafXDD::hasEdge(int src, int dst)
// {
//     return G
// }

// void GrafXDD::print()
// {
//     cout << "Edge :"
//          << " Weight" << endl;
//     for (int i = 0; i < T.size(); i++)
//     {
//         cout << T[i].second.first << " - " << T[i].second.second << " : "
//              << T[i].first;
//         cout << endl;
//     }
// }

// GrafXDD::GrafXDD(int V)
// {
//     parent = new int[V];

//     //i 0 1 2 3 4 5
//     //parent[i] 0 1 2 3 4 5
//     for (int i = 0; i < V; i++)
//         parent[i] = i;

//     G.clear();
//     T.clear();
// }
// void GrafXDD::addEdge(int u, int v, int w)
// {
//     G.push_back(make_pair(w, edge(u, v)));
// }
// int GrafXDD::find_set(int i)
// {
//     // If i is the parent of itself
//     if (i == parent[i])
//         return i;
//     else
//         // Else if i is not the parent of itself
//         // Then i is not the representative of his set,
//         // so we recursively call Find on its parent
//         return find_set(parent[i]);
// }

// void GrafXDD::union_set(int u, int v)
// {
//     parent[u] = parent[v];
// }
// void GrafXDD::kruskal()
// {
//     int i, uRep, vRep;
//     sort(G.begin(), G.end()); // increasing weight
//     for (i = 0; i < G.size(); i++)
//     {
//         uRep = find_set(G[i].second.first);
//         vRep = find_set(G[i].second.second);
//         if (uRep != vRep)
//         {
//             T.push_back(G[i]); // add to tree
//             union_set(uRep, vRep);
//         }
//     }
// }