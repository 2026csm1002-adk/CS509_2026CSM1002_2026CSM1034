#include "conn_comp.h"

class Unionfind{
private:
    vector<int> parent;
    vector<int> size;
public:
    Unionfind(int n){
        parent.resize(n);
        size.resize(n, 1);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
    }
    int findUpar(int u){
        if(parent[u] ===u) return u;
        return findUpar(parent[u]);
    }
    void unite(int u, int v){
        int Upar_u = findUpar(u);
        int Upar_v = findUpar(v);
        if(Upar_u != Upar_v){
            if(size[Upar_u] < size[Upar_v]){
                size[Upar_v] += size[Upar_u];
                parent[Upar_u] = Upar_v;
            }else{
                size[Upar_u] += size[Upar_v];
                parent[Upar_v] = Upar_u;
            }
        }
    }
};

ComponentsResult count_connected_components(CSRGGraph &g) {
    ComponentsResult result;
    int V = g.V;
    Unionfind uf(V);

    for(int u=0; u<V; u++){
        for(int i = g.row_ptr[u]; i <g.row_ptr[u+1]; i++){
            int v = g.col_idx[i];
            uf.unite(u,v);
        }
    }

    unordered_map<int,int> existed;

    int component=0;
    for(int u=0; u<V; u++){
        int upar = uf.findUpar(u);
        if(!existed[upar]){
            existed[upar] = component;
            component++;
        }
        result.component.push_back(existed[upar]);
    }
    result.numComponents = component+1;

    return result;
}