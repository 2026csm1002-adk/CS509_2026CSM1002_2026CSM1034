#include "graph_io.h"

#include <vector>
using namespace std;

CSR buildCSR(AdjList & g){
    CSR csr;  

    csr.row_ptr.assign(g.V + 1, 0);

    for (int u = 0; u < g.V; ++u) {
        csr.row_ptr[u + 1] = csr.row_ptr[u] + static_cast<int>(g.adj[u].size());
    }

    int total = csr.row_ptr[g.V];
    csr.col_idx.assign(total, 0);
    csr.values.assign(total, 0);

    for (int u = 0; u < g.V; ++u) {
        int offset = csr.row_ptr[u];
        for (const auto& [nbr, weight] : g.adj[u]) {
            csr.col_idx[offset] = nbr;
            csr.values[offset] = weight;
            ++offset;
        }
    }
    return csr;

}