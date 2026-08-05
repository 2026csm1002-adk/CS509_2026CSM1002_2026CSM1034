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


void bfsDriver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_01/tests/bfs_tests");
            cout<<file<<endl;
            break;
        }
        default:
            cout<<"Invalid choice"<<endl;
            break;
    }

    return ;
}