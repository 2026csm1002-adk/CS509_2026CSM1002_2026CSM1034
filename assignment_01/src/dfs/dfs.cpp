#include "dfs.h"
using namespace std;
std::vector<int> dfsTraversal(const CSRGraph &g, int src){
    std::vector<int> dfs;
    int V = g.V;
    std::stack<int> stk; //stack

    vector<int> visited(V,0);
    stk.push(src);
    visited[src]=1;
    while(!stk.empty()){
        int node = stk.top();
        stk.pop();
        dfs.push_back(node);
        int start = g.row_ptr[node];
        int end = g.row_ptr[node+1];

        for(int i=end-1; i>=start; i--){
            int neigh = g.col_idx[i];
            if(!visited[neigh]){
                visited[neigh]=1;
                stk.push(neigh);
            }
        }
    }


    return dfs;
}


void dfsDriver(){
    return;
}