#include "../driver/driver.h"
vector<int> bfsTraversal(vector<int> &row_ptr, vector<int> &col_idx, int src){
    vector<int> bfs;
    int V = row_ptr.size() -1;
    queue<int> que;

    vector<int> visited(V,0);
    que.push(src);
    visited[src]=1;

    while(!que.empty()){
        int node = que.front();
        que.pop();
        bfs.push_back(node);
        int start = row_ptr[node];
        int end = row_ptr[node+1];

        for(int i=start; i<end; i++){
            int neigh = col_idx[i];
            if(!visited[neigh]){
                visited[neigh]=1;
                que.push(neigh);
            }
        }
    }

    return bfs;
}