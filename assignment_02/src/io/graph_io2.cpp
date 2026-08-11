#include "graph_io2.h"
#include <fstream>
#include <stdexcept>
using namespace std;
AdjListUnweighted readGraphNoSource(const string& filepath) {
    ifstream in(filepath);
    if (!in.is_open()) {
        throw runtime_error("Could not open input file: " + filepath);
    }

    AdjListUnweighted g;
    in >> g.V >> g.E;
    if (!in || g.V < 0) {
        throw runtime_error("Malformed header (V E) in file: " + filepath);
    }

    g.adj.assign(g.V, {});
    for (int i = 0; i < g.V; ++i) {
        int u, degree;
        in >> u >> degree;
        if (!in || u < 0 || u >= g.V) {
            throw runtime_error("Malformed adjacency line in file: " + filepath);
        }
        g.adj[u].reserve(degree);
        for (int k = 0; k < degree; ++k) {
            int nbr;
            in >> nbr;
            if (!in) {
                throw runtime_error("Malformed neighbor list in file: " + filepath);
            }
            g.adj[u].push_back(nbr);
        }
    }
    g.source = 0;
    return g;
}