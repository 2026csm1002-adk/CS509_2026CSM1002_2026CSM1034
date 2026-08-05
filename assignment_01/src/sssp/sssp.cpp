#include "sssp.h"
#include <queue>

using namespace std;

vector<long long> sssp(const CSRGraph &g, int src){
    vector<long long> dist(g.V, SSSP_INF);
    if (src < 0 || src >= g.V) {
        return dist; 
    }

    using Node = pair<long long, int>;  // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // Path Cost lesser than that is already available

        for (int idx = g.row_ptr[u]; idx < g.row_ptr[u + 1]; ++idx) {
            int v = g.col_idx[idx];
            long long weight = g.values[idx];
            long long nd = d + weight;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    return dist;
}

void ssspDriver(){
    return;
}