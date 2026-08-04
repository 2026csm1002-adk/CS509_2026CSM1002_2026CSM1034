#include "graph_io.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

AdjListUnweighted readUnweightedGraph(const string& filepath) {
    ifstream in(filepath);
    if (!in.is_open()) {
        throw runtime_error("Could not find or open input file: " + filepath);
    }

    AdjListUnweighted g;
    in >> g.V >> g.E;
    if (!in || g.V < 0) {
        throw runtime_error("Invalid Header format in file: " + filepath);
    }

    g.adj.assign(g.V, {});
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        in >> u >> degree;
        if (!in || u < 0 || u >= g.V) {
            throw runtime_error("Invalid adjacency line format in file: " + filepath);
        }
        g.adj[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr;
            in >> nbr;
            if (!in) {
                throw runtime_error("Invalid neighbor list in file: " + filepath);
            }
            g.adj[u].push_back(nbr);
        }
    }

    string tag;
    in >> tag >> g.source;
    if (!in || tag != "SOURCE") {
        throw runtime_error("Missing SOURCE line in file: " + filepath);
    }

    return g;
}

AdjListWeighted readWeightedGraph(const std::string& filepath) {
    ifstream in(filepath);
    if (!in.is_open()) {
        throw runtime_error("Could not find or open input file: " + filepath);
    }

    AdjListWeighted g;
    in >> g.V >> g.E;
    if (!in || g.V < 0) {
        throw runtime_error("Invalid Header format in file: " + filepath);
    }

    g.adj.assign(g.V, {});
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        in >> u >> degree;
        if (!in || u < 0 || u >= g.V) {
            throw runtime_error("Invalid adjacency line format in file: " + filepath);
        }
        g.adj[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr, weight;
            in >> nbr >> weight;
            if (!in) {
                throw runtime_error("Invalid neighbor/weight list in file: " + filepath);
            }
            if (weight <= 0) {
                throw runtime_error("Non-positive edge weight in file: " + filepath);
            }
            g.adj[u].push_back({nbr, weight});
        }
    }

    string tag;
    in >> tag >> g.source;
    if (!in || tag != "SOURCE") {
        throw runtime_error("Missing SOURCE line in file: " + filepath);
    }

    return g;
}
