#include "tri_count.h"
#include <unordered_set>
TriangleResult countTriangle(CSRGraph &g){
    TriangleResult result;

    unordered_set<array<int,3>> unique_triangles;
    for(int u=0; u<g.V; u++){

        for(int i=g.row_ptr[u]; i<g.row_ptr[u+1]; i++){
            int v = g.col_idx[i];
            for(int j=g.row_ptr[v]; j<g.row_ptr[v+1]; j++){
                int w = g.col_idx[j];
                if(u != v && v != w && u != w){
                    array<int,3> triset = {u, v, w};
                    sort(triset.begin(), triset.end());
                    if(unique_triangles.find(triset) == unique_triangles.end()){
                        unique_triangles.insert(triset);
                        result.triangles.push_back(triset);
                        result.totalTriangles++;
                    }
                }
                
            }
        }
    }

    return result;
}