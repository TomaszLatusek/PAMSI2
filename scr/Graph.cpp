// #include "../inc/Graph.hh"
// #include <random>

// template <typename T>
// static T Graph::*generateRandom(int verticesCount, int density)
// {
//     int edgesCount = (verticesCount * (verticesCount - 1) * density) / 200;
//     T *graph = new T(verticesCount);
//     if (density == 1)
//     {
//         for (int i = 0; i < verticesCount; ++i)
//         {
//             for (int j = i + 1; j < verticesCount; ++j)
//             {
//                 int weight = std::uniform_int_distribution<int>(1, 25);
//                 graph->addEdge(i, j, weight);
//             }
//         }
//     }
//     else
//     {
//         while (edgesCount)
//         {
//             int source = std::uniform_int_distribution<int>(0, verticesCount - 1);
//             int destination = std::uniform_int_distribution<int>(0, verticesCount - 1);
//             if (graph->hasEdge(source, destination))
//                 continue;
//             int weight = std::uniform_int_distribution<int>(1, 25);
//             graph->addEdge(source, destination, weight);
//             edgesCount--;
//         }
//     }

//     return graph;
// }


