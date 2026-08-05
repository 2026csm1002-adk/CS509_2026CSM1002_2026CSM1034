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
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_01/tests/dfs_tests");
            AdjListUnweighted g = readUnweightedGraph(file);
            CSRGraph csr = buildCSR(g);

            auto start = chrono::high_resolution_clock::now();
            vector<int> dfs = dfsTraversal(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(file,"dfs");
            ofstream outputFile(fileName);
            outputFile<<"DFS Traversal: "<<endl;
            for(int i=0; i<dfs.size(); i++){
                outputFile << dfs[i] << " ";
            }
            outputFile << endl;
            cout<<"Output File Generated : "<<fileName<<endl;
            cout << "Execution Time: " << excutionTime << " ms" << endl;
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_01/tests/dfs_tests");

            for(auto &file : files){
                AdjListUnweighted g = readUnweightedGraph(file);
                CSRGraph csr = buildCSR(g);

                auto start = chrono::high_resolution_clock::now();
                vector<int> dfs = dfsTraversal(csr, g.source);
                auto end = chrono::high_resolution_clock::now();
                double excutionTime = chrono::duration<double,milli>(end-start).count();
                string fileName = createOutputFiles(file,"dfs");
                ofstream outputFile(fileName);
                outputFile<<"DFS Traversal: "<<endl;
                for(int i=0; i<dfs.size(); i++){
                    outputFile << dfs[i] << " ";
                }
                outputFile << endl;
                cout<<"Output File Generated : "<<fileName<<endl;
                cout << "Execution Time: " << excutionTime << " ms" << endl;
            }
            break;
        }
        case 3:{
            string path;

            cout << "\nEnter file path : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, path);
            AdjListUnweighted g = readUnweightedGraph(path);
            CSRGraph csr = buildCSR(g);

            auto start = chrono::high_resolution_clock::now();
            vector<int> dfs = dfsTraversal(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(path,"dfs");
            ofstream outputFile(fileName);
            outputFile<<"DFS Traversal: "<<endl;
            for(int i=0; i<dfs.size(); i++){
                outputFile << dfs[i] << " ";
            }
            outputFile << endl;
            cout<<"Output File Generated : "<<fileName<<endl;
            cout << "Execution Time: " << excutionTime << " ms" << endl;
            break;
        }
        case 0:
            cout<<"Go Back"<<endl;
            return;
        default:
            cout<<"Invalid choice"<<endl;
            break;
    }
    return;
}