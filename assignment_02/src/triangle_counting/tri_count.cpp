#include "tri_count.h"
#include <algorithm>
#include <set>
#include <array>

using namespace std;
TriangleResult countTriangle(CSRGraph &g){
    TriangleResult result;
    set<array<int,3>> unique_triangles;

    for (int u = 0; u < g.V; u++) {
        for (int i = g.row_ptr[u]; i < g.row_ptr[u+1]; i++) {
            int v = g.col_idx[i];
            if (v == u) continue;

            for (int j = g.row_ptr[v]; j < g.row_ptr[v+1]; j++) {
                int w = g.col_idx[j];
                if (w == u || w == v) continue;

                // check that edge u-w actually exists
                bool uw_edge = std::binary_search(
                    g.col_idx.begin() + g.row_ptr[u],
                    g.col_idx.begin() + g.row_ptr[u+1],
                    w
                );
                if (!uw_edge) continue;

                array<int,3> triset = {u, v, w};
                sort(triset.begin(), triset.end());
                if (unique_triangles.insert(triset).second) {
                    result.triangles.push_back(triset);
                    result.totalTriangles++;
                }
            }
        }
    }

    return result;
}