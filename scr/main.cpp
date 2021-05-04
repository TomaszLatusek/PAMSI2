#include "../inc/MatrixGraph.hh"
#include "../inc/ListGraph.hh"
// #include "../inc/GrafXD.hh"
#include <iostream>
#include <chrono>
#include <fstream>

void printResult(int graphSize, int graphDensity, long int averageK, long int averageP, int m, char graphType)
{
    if (graphType == 'm')
    {
        std::cout << "Matrix" << std::endl;
    }
    else
    {
        std::cout << "List" << std::endl;
    }
    std::cout << "Vertices: " << graphSize << " Density: " << graphDensity << std::endl;
    std::cout << "K: " << averageK << std::endl;
    std::cout << "P: " << averageP << std::endl;
    std::cout << std::endl;
}

int main()
{
    std::ofstream dataMK("MatrixKruskal.txt");
    std::ofstream dataMP("MatrixPrim.txt");
    std::ofstream dataLK("ListKruskal.txt");
    std::ofstream dataLP("ListPrim.txt");

    int graphSize[] = {10, 50, 100, 150, 200};
    float graphDensity[] = {25, 50, 75, 100};

    int testCount = 10;
    int sizes = sizeof(graphSize) / sizeof(graphSize[0]);
    int densities = sizeof(graphDensity) / sizeof(graphDensity[0]);

    long int averagesKruskalMatrix[sizes * densities];
    long int averagesPrimMatrix[sizes * densities];
    auto totalDurationKruskalMatrix = 0;
    auto totalDurationPrimMatrix = 0;

    long int averagesKruskalList[sizes * densities];
    long int averagesPrimList[sizes * densities];
    auto totalDurationKruskalList = 0;
    auto totalDurationPrimList = 0;

    int m = 0;

    // MatrixGraph *graf = Graph::generateRandom<MatrixGraph>(100, 100);
    // //graf->print();

    // std::cout << graf->prim() << std::endl;
    // std::cout << graf->kruskal2() << std::endl;

    for (int i = 0; i < sizes; i++)
    {
        for (int j = 0; j < densities; j++)
        {
            totalDurationKruskalMatrix = 0;
            totalDurationPrimMatrix = 0;

            for (int k = 0; k < testCount; k++)
            {
                MatrixGraph *graphMatrix = Graph::generateRandom<MatrixGraph>(graphSize[i], graphDensity[j]);

                    graphMatrix->sort();
                auto start1M = std::chrono::high_resolution_clock::now();
                graphMatrix->kruskal2();
                auto stop1M = std::chrono::high_resolution_clock::now();
                int duration1M = std::chrono::duration_cast<std::chrono::microseconds>(stop1M - start1M).count();
                totalDurationKruskalMatrix += duration1M;

                auto start2M = std::chrono::high_resolution_clock::now();
                graphMatrix->prim();
                auto stop2M = std::chrono::high_resolution_clock::now();
                int duration2M = std::chrono::duration_cast<std::chrono::microseconds>(stop2M - start2M).count();
                totalDurationPrimMatrix += duration2M;

                delete graphMatrix;

                ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                ListGraph *graphList = Graph::generateRandom<ListGraph>(graphSize[i], graphDensity[j]);

                    graphList->sort();
                auto start1L = std::chrono::high_resolution_clock::now();
                graphList->kruskal2();
                auto stop1L = std::chrono::high_resolution_clock::now();
                int duration1L = std::chrono::duration_cast<std::chrono::microseconds>(stop1L - start1L).count();
                totalDurationKruskalList += duration1L;

                auto start2L = std::chrono::high_resolution_clock::now();
                graphList->prim();
                auto stop2L = std::chrono::high_resolution_clock::now();
                int duration2L = std::chrono::duration_cast<std::chrono::microseconds>(stop2L - start2L).count();
                totalDurationPrimList += duration2L;

                delete graphList;
            }
            averagesKruskalMatrix[m] = totalDurationKruskalMatrix / testCount;
            averagesPrimMatrix[m] = totalDurationPrimMatrix / testCount;
            printResult(graphSize[i], graphDensity[j], averagesKruskalMatrix[m], averagesPrimMatrix[m], m, 'm');

            averagesKruskalList[m] = totalDurationKruskalList / testCount;
            averagesPrimList[m] = totalDurationPrimList / testCount;
            printResult(graphSize[i], graphDensity[j], averagesKruskalList[m], averagesPrimList[m], m, 'l');

            m++;
        }
    }
    m = 0;
    for (int i = 0; i < sizes; i++)
    {
        for (int j = 0; j < densities; j++)
        {
            dataMK << std::endl
                   << "Vertices: " << graphSize[i] << " Density: " << graphDensity[j] << std::endl
                   << averagesKruskalMatrix[m] << std::endl;
            dataMP << std::endl
                   << "Vertices: " << graphSize[i] << " Density: " << graphDensity[j] << std::endl
                   << averagesPrimMatrix[m] << std::endl;

            dataLK << std::endl
                   << "Vertices: " << graphSize[i] << " Density: " << graphDensity[j] << std::endl
                   << averagesKruskalList[m] << std::endl;
            dataLP << std::endl
                   << "Vertices: " << graphSize[i] << " Density: " << graphDensity[j] << std::endl
                   << averagesPrimList[m] << std::endl;

            m++;
        }
    }

    return 0;
}
