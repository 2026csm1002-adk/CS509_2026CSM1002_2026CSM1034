// Generates connected, undirected random graphs and writes them in the
// input formats required by Assignment_1.pdf:
//   - Unweighted (BFS/DFS): V E / u degree n1 n2 ... / SOURCE s
//   - Weighted   (SSSP)   : V E / u degree n1 w1 n2 w2 ... / SOURCE s
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

namespace fs = std::filesystem;
 
 
// Encodes an undirected edge (a < b) into a single 64-bit key for
// fast duplicate detection in an unordered_set.
static long long edgeKey(int a, int b, int V) {
    if (a > b) swap(a, b);
    return 1LL * a * V + b;
}
 
// Builds a connected, undirected, simple graph on V vertices and targetE edges
static vector<pair<int,int>> generateConnectedGraph(int V, int targetE, mt19937& rng) {
    vector<pair<int,int>> edges;
    edges.reserve(targetE);
    unordered_set<long long> seen;
    seen.reserve(targetE * 2);
 
    // 1. Random spanning tree: shuffle vertices, connect consecutive pairs.
    //    Guarantees connectivity with exactly V-1 edges.
    vector<int> perm(V);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);
 
    for (int i = 0; i + 1 < V; ++i) {
        int a = perm[i], b = perm[i + 1];
        long long key = edgeKey(a, b, V);
        seen.insert(key);
        edges.push_back({a, b});
    }
 
    // 2. Add extra random edges until we reach targetE (or give up after
    //    a bounded number of attempts, to stay fast for large sparse V).
    uniform_int_distribution<int> pick(0, V - 1);
    int remaining = targetE - static_cast<int>(edges.size());
    int attempts = 0;
    int maxAttempts = remaining * 20 + 1000;
 
    while (remaining > 0 && attempts < maxAttempts) {
        ++attempts;
        int a = pick(rng);
        int b = pick(rng);
        if (a == b) continue;
        long long key = edgeKey(a, b, V);
        if (seen.count(key)) continue;
        seen.insert(key);
        edges.push_back({a, b});
        --remaining;
    }
 
    return edges;
}
 
static void writeUnweighted(const string& path, int V, const vector<pair<int,int>>& edges, int source) {
    vector<vector<int>> adj(V);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (auto& nbrs : adj) sort(nbrs.begin(), nbrs.end());
 
    ofstream out(path);
    out << V << " " << edges.size() << endl;
    for (int u = 0; u < V; ++u) {
        out << u << " " << adj[u].size();
        for (int v : adj[u]) out << " " << v;
        out << endl;
    }
    out << "SOURCE " << source << endl;
}
 
static void writeWeighted(const string& path, int V, const vector<pair<int,int>>& edges,
                           const vector<int>& weights, int source) {
    vector<vector<pair<int, int>>> adj(V);
    for (size_t i = 0; i < edges.size(); ++i) {
        adj[edges[i].first].push_back({edges[i].second, weights[i]});
        adj[edges[i].second].push_back({edges[i].first, weights[i]});
    }
    for (auto& nbrs : adj) sort(nbrs.begin(), nbrs.end());
 
    ofstream out(path);
    out << V << " " << edges.size() << "\n";
    for (int u = 0; u < V; ++u) {
        out << u << " " << adj[u].size();
        for (const auto& [v, w] : adj[u]) out << " " << v << " " << w;
        out << "\n";
    }
    out << "SOURCE " << source << "\n";
}
 
int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <output_dir> [seed]\n";
        return 1;
    }

    string outDir = argv[1];
    int seed = (argc > 2) ? stoi(argv[2]) : 42;

    fs::create_directories(outDir + "/bfs");
    fs::create_directories(outDir + "/dfs");
    fs::create_directories(outDir + "/sssp");

    vector<int> sizes = {10, 100, 10000, 50000, 100000};

    for (int V : sizes) {
        mt19937 rng(seed + V);

        int E = max((int)(1.5 * V), V - 1);

        auto edges = generateConnectedGraph(V, E, rng);

        vector<int> weights(edges.size());
        uniform_int_distribution<int> dist(1, 10);

        for (int &w : weights)
            w = dist(rng);

        writeUnweighted(outDir + "/bfs/bfs_" + to_string(V) + ".txt",
                        V, edges, 0);

        writeUnweighted(outDir + "/dfs/dfs_" + to_string(V) + ".txt",
                        V, edges, 0);

        writeWeighted(outDir + "/sssp/sssp_" + to_string(V) + ".txt",
                      V, edges, weights, 0);

        cout << "Generated graph with " << V
             << " vertices and " << edges.size()
             << " edges\n";
    }

    return 0;
}