#include "graph_io.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

AdjList readGraph(const std::string& filepath) {
    ifstream inputFile(filepath);
    if (!inputFile.is_open()) {
        throw runtime_error("Could not find or open input file: " + filepath);
    }

    AdjList g;
    inputFile >> g.V >> g.E;
    if (!inputFile || g.V < 0) {
        throw runtime_error("Invalid Header format in file: " + filepath);
    }

    g.adj.assign(g.V, {});
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        inputFile >> u >> degree;
        if (!inputFile || u < 0 || u >= g.V) {
            throw runtime_error("Invalid adjacency line format in file: " + filepath);
        }
        g.adj[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr, weight;
            inputFile >> nbr >> weight;
            if (!inputFile) {
                throw runtime_error("Invalid neighbor/weight list in file: " + filepath);
            }
            if (weight <= 0) {
                throw runtime_error("Non-positive edge weight in file: " + filepath);
            }
            g.adj[u].push_back({nbr, weight});
        }
    }

    string tag1;
    inputFile >> tag1 >> g.source;
    if (!inputFile || tag1 != "SOURCE") {
        throw runtime_error("Missing SOURCE line in file: " + filepath);
    }

    string tag2;
    inputFile >> tag2 >>g.sink;
    if(!inputFile || tag2 != "SINK"){
        throw runtime_error("Missing SINK line in file" + filepath);
    }

    if(g.sink==g.source) {
        throw runtime_error("Souce and Sink file are same please make it different" + filepath);
    }


    return g;
}