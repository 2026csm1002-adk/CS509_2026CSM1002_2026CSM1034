#include "../driver/driver.h"
#include "bfs.h"
using namespace std;
std::vector<int> bfsTraversal(const CSRGraph &g, int src){
    std::vector<int> bfs;
    int V = g.V;
    std::queue<int> que;

    vector<int> visited(V,0);
    que.push(src);
    visited[src]=1;

    while(!que.empty()){
        int node = que.front();
        que.pop();
        bfs.push_back(node);
        int start = g.row_ptr[node];
        int end = g.row_ptr[node+1];

        for(int i=start; i<end; i++){
            int neigh = g.col_idx[i];
            if(!visited[neigh]){
                visited[neigh]=1;
                que.push(neigh);
            }
        }
    }

    return bfs;
}