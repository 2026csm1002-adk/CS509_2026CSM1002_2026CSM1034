#include "betweenness.h"

#include <queue>
#include <stack>
using namespace std;
vector<double> betweennessCentrality(const CSRGraph& g) {
    int V = g.V;
    vector<double> centrality(V, 0.0);

    for (int s = 0; s < V; ++s) {
        // predecessors[w] = list of vertices on a shortest path to w through s
        vector<vector<int>> predecessors(V);
        vector<long long> no_paths(V, 0);   // number of shortest paths from s to each vertex
        vector<int> dist(V, -1);         // BFS distance from s
        vector<double> depend(V, 0.0);    // dependency of s on each vertex

        no_paths[s] = 1;
        dist[s] = 0;

        queue<int> bfsQueue;
        bfsQueue.push(s);

        stack<int> visitOrder;  // vertices in non-decreasing distance order

        while (!bfsQueue.empty()) {
            int v = bfsQueue.front();
            bfsQueue.pop();
            visitOrder.push(v);

            for (int idx = g.row_ptr[v]; idx < g.row_ptr[v + 1]; ++idx) {
                int w = g.col_idx[idx];

                // First time we see w: set its distance, queue it.
                if (dist[w] < 0) {
                    dist[w] = dist[v] + 1;
                    bfsQueue.push(w);
                }

                // w is one step ahead than v along a shortest path: v is a predecessor of w.
                if (dist[w] == dist[v] + 1) {
                    no_paths[w] += no_paths[v];
                    predecessors[w].push_back(v);
                }
            }
        }

        // Accumulate dependencies in reverse BFS order.
        while (!visitOrder.empty()) {
            int w = visitOrder.top();
            visitOrder.pop();

            for (int v : predecessors[w]) {
                double share = (static_cast<double>(no_paths[v]) / static_cast<double>(no_paths[w])) * (1.0 + depend[w]);
                depend[v] += share;
            }

            if (w != s) {
                centrality[w] += depend[w];
            }
        }
    }

    // As path will get counted twice for undirected graph
    for (double& c : centrality) {
        c /= 2.0;
    }

    return centrality;
}
