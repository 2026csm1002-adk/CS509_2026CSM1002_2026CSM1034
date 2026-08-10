#include "driver.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <array>
using namespace std;

namespace{
void runBetweennessCentrality(const string& filepath) {
    AdjListUnweighted g = readUnweightedGraph(filepath);
    CSRGraph csr = buildCSR(g);

    auto start = chrono::high_resolution_clock::now();
    vector<double> centrality = betweennessCentrality(csr);
    auto end = chrono::high_resolution_clock::now();
    double elapsed_ms = chrono::duration<double, milli>(end - start).count();

    cout << "Algorithm: Betweenness Centrality\n";
    cout << "Vertex Centrality\n";
    cout << fixed << setprecision(2);
    for (int v = 0; v < g.V; ++v) {
        cout << v << " " << centrality[v] << "\n";
    }
    cout.unsetf(ios::fixed);
    cout << "Execution time: " << elapsed_ms << " ms\n";
}

void runTriangleCounting(const string& filepath) {
    AdjListUnweighted g = readUnweightedGraph(filepath);
    
    CSRGraph csr = buildCSR(g);

    // Listing individual triangles is required only for the two
    // smallest graph sizes (Assignment_2.pdf Section 7.3).
    bool listTriangles = (g.V <= 100);

    
    auto start = chrono::high_resolution_clock::now();
    TriangleResult result = countTriangle(csr);
    auto end = chrono::high_resolution_clock::now();
    double elapsed_ms = chrono::duration<double, milli>(end - start).count();

    
    cout << "Algorithm: Triangle Counting\n";
    cout << "Total triangles: " << result.totalTriangles << "\n";
    if (listTriangles) {
        cout << "Triangles found:\n";
        for (const array<int, 3>& t : result.triangles) {
            cout << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
        }
    }
    cout << "Execution time: " << elapsed_ms << " ms\n";
}

}
void runConnectedComponents(const string& filepath) {
    AdjListUnweighted g = readUnweightedGraph(filepath);
    CSRGraph csr = buildCSR(g);

    auto start = chrono::high_resolution_clock::now();
    ComponentsResult result = count_connected_components(csr);
    auto end = chrono::high_resolution_clock::now();
    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();

    cout << "Algorithm: Connected Components\n";
    cout << "Number of components: " << result.numComponents << "\n";
    cout << "Vertex Component\n";
    for (int v = 0; v < g.V; ++v) {
        cout << v << " " << result.component[v] << "\n";
    }
    cout << "Execution time: " << elapsed_ms << " ms\n";
}




void runDriver2(Algorithm2 algo, const string& filepath) {
    switch (algo) {
        case Algorithm2::TRIANGLE_COUNTING:
            runTriangleCounting(filepath);
            break;
        case Algorithm2::BETWEENNESS_CENTRALITY:
            runBetweennessCentrality(filepath);
            break;
        case Algorithm2::CONNECTED_COMPONENTS:
            runConnectedComponents(filepath);
            break;
    }
}

void runDriver2(const string& algoName, const string& filepath) {
    string name = algoName;
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    if (name == "tc") {
        runDriver2(Algorithm2::TRIANGLE_COUNTING, filepath);
    } else if (name == "bc") {
        runDriver2(Algorithm2::BETWEENNESS_CENTRALITY, filepath);
    } else if (name == "cc") {
        runDriver2(Algorithm2::CONNECTED_COMPONENTS, filepath);
    } else {
        throw std::runtime_error("Unknown algorithm: " + algoName);
    }
}
