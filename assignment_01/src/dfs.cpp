vector<int> dfsTraversal(vector<int> &row_ptr, vector<int> &col_idx, int src){
    vector<int> dfs;
    int V = row_ptr.size()-1;
    stack<int> stk; //stack

    vector<int> visited(V,0);
    stk.push(src);
    visited[src]=1;
    while(!stk.empty()){
        int node = stk.top();
        stk.pop();
        dfs.push_back(node);
        int start = row_ptr[node];
        int end = row_ptr[node+1];

        for(int i=end-1; i>=start; i--){
            int neigh = col_idx[i];
            if(!visited[neigh]){
                visited[neigh]=1;
                stk.push(neigh);
            }
        }
    }

    return dfs;
}