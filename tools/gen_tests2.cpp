#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

struct Edge {
    int u;
    int v;
};
vector<Edge> generateGraph(int V, int targetEdgeCount, mt19937& rng) {
    vector<Edge> edges;
    set<pair<int, int>> usedEdges;

    vector<int> order(V);
    for (int i = 0; i < V; ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end(), rng);

    for (int i = 0; i + 1 < V; ++i) {
        int a = order[i];
        int b = order[i + 1];
        pair<int, int> key = (a < b) ? make_pair(a, b) : make_pair(b, a);
        usedEdges.insert(key);
        edges.push_back({a, b});
    }

    uniform_int_distribution<int> randomVertex(0, V - 1);
    int edgesNeeded = targetEdgeCount - (int)edges.size();
    int maxAttempts = edgesNeeded * 20 + 1000;

    for (int attempt = 0; attempt < maxAttempts && edgesNeeded > 0; ++attempt) {
        int a = randomVertex(rng);
        int b = randomVertex(rng);
        if (a == b) {
            continue;
        }
        pair<int, int> key = (a < b) ? make_pair(a, b) : make_pair(b, a);
        if (usedEdges.count(key) > 0) {
            continue;
        }
        usedEdges.insert(key);
        edges.push_back({a, b});
        edgesNeeded--;
    }

    return edges;
}

// Writes the no-SOURCE adjacency-list format shared by TC / BC / CC.
void writeGraphFile(const string& path, int V, const vector<Edge>& edges) {
    vector<vector<int>> adjacencyList(V);
    for (int i = 0; i < (int)edges.size(); ++i) {
        int a = edges[i].u;
        int b = edges[i].v;
        adjacencyList[a].push_back(b);
        adjacencyList[b].push_back(a);
    }
    for (int u = 0; u < V; ++u) {
        sort(adjacencyList[u].begin(), adjacencyList[u].end());
    }

    ofstream out(path);
    out << V << " " << edges.size() << "\n";
    for (int u = 0; u < V; ++u) {
        out << u << " " << adjacencyList[u].size();
        for (int i = 0; i < (int)adjacencyList[u].size(); ++i) {
            out << " " << adjacencyList[u][i];
        }
        out << "\n";
    }
    // No SOURCE line for TC / BC / CC.
}

void generateForAlgorithm(const string& tag, const string& folder, const vector<int>& sizes, unsigned int seed) {
    fs::create_directories(folder);

    for (int i = 0; i < (int)sizes.size(); ++i) {
        int V = sizes[i];
        mt19937 rng(seed + (unsigned int)V + (unsigned int)tag.size());

        int targetEdgeCount = (int)(V * 1.5);
        if (targetEdgeCount < V - 1) {
            targetEdgeCount = V - 1;
        }

        vector<Edge> edges = generateGraph(V, targetEdgeCount, rng);

        string path = folder + "/" + tag + "_" + to_string(V) + ".txt";
        writeGraphFile(path, V, edges);

        cout << "Generated " << tag << " V=" << V << " E=" << edges.size() << " -> " << path << endl;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <tests_folder> [seed]" << endl;
        return 1;
    }

    string testsFolder = argv[1];
    unsigned int seed = 42;
    if (argc >= 3) {
        seed = (unsigned int)stoul(argv[2]);
    }

    // Sizes per Assignment_2.pdf Section 4.2
    vector<int> tcSizes = {10, 100, 10000, 50000, 100000};
    vector<int> bcSizes = {10, 100, 1000, 5000, 10000};
    vector<int> ccSizes = {10, 100, 10000, 50000, 100000};

    generateForAlgorithm("tc", testsFolder + "/tc", tcSizes, seed);
    generateForAlgorithm("bc", testsFolder + "/bc", bcSizes, seed);
    generateForAlgorithm("cc", testsFolder + "/cc", ccSizes, seed);

    return 0;
}
