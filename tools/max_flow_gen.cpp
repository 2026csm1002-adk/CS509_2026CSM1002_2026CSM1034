#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int capacity;
};

int main() {
    // Files to generate
    vector<int> sizes = {10, 100, 10000, 50000};

    // Random number generator
    random_device rd;
    mt19937 rng(rd());

    uniform_int_distribution<int> capacityDist(1, 100);

    for (int V : sizes) {

        int E;

        if (V == 10)
            E = 20;
        else if (V == 100)
            E = 300;
        else if (V == 10000)
            E = 30000;
        else
            E = 150000;
        long long maxEdges = 1LL * V * (V - 1);
        E = min<long long>(E, maxEdges);

        vector<vector<Edge>> graph(V);

        // Store edges to prevent duplicates.
        unordered_set<long long> usedEdges;
        usedEdges.reserve(E * 2);

        auto edgeKey = [V](int u, int v) -> long long {
            return 1LL * u * V + v;
        };
        for (int u = 0; u < V - 1; u++) {
            int v = u + 1;

            graph[u].push_back({v, capacityDist(rng)});
            usedEdges.insert(edgeKey(u, v));
        }

        int currentEdges = V - 1;


        uniform_int_distribution<int> vertexDist(0, V - 1);

        while (currentEdges < E) {
            int u = vertexDist(rng);
            int v = vertexDist(rng);

            if (u == v)
                continue;

            long long key = edgeKey(u, v);

        
            if (usedEdges.find(key) != usedEdges.end())
                continue;

            graph[u].push_back({v, capacityDist(rng)});
            usedEdges.insert(key);

            currentEdges++;
        }


        string filename = "maxflow_" + to_string(V) + ".txt";

        ofstream out(filename);

        if (!out) {
            cerr << "Error opening " << filename << endl;
            continue;
        }

        // First line:
        // V E
        out << V << " " << E << "\n";

        for (int u = 0; u < V; u++) {

            out << u << " " << graph[u].size();

            for (const auto &edge : graph[u]) {
                out << " " << edge.to
                    << " " << edge.capacity;
            }

            out << "\n";
        }

        // Source and sink
        out << "SOURCE 0\n";
        out << "SINK " << V - 1 << "\n";

        out.close();

        cout << "Generated " << filename
             << " | Vertices: " << V
             << " | Edges: " << E << endl;
    }

    return 0;
}