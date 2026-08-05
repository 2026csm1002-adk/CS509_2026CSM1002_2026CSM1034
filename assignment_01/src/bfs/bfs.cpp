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
            AdjListUnweighted g = readUnweightedGraph(file);
            CSRGraph csr = buildCSR(g);

            auto start = chrono::high_resolution_clock::now();
            vector<int> bfs = bfsTraversal(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(file,"bfs");
            ofstream outputFile(fileName);
            outputFile<<"BFS Traversal: "<<endl;
            for(int i=0; i<bfs.size(); i++){
                outputFile << bfs[i] << " ";
            }
            outputFile << endl;
            cout<<"Output File Generated : "<<fileName<<endl;
            cout << "Execution Time: " << excutionTime << " ms" << endl;
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_01/tests/bfs_tests");

            for(auto &file : files){
                AdjListUnweighted g = readUnweightedGraph(file);
                CSRGraph csr = buildCSR(g);

                auto start = chrono::high_resolution_clock::now();
                vector<int> bfs = bfsTraversal(csr, g.source);
                auto end = chrono::high_resolution_clock::now();
                double excutionTime = chrono::duration<double,milli>(end-start).count();
                string fileName = createOutputFiles(file,"bfs");
                ofstream outputFile(fileName);
                outputFile<<"BFS Traversal: "<<endl;
                for(int i=0; i<bfs.size(); i++){
                    outputFile << bfs[i] << " ";
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
            vector<int> bfs = bfsTraversal(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(path,"bfs");
            ofstream outputFile(fileName);
            outputFile<<"BFS Traversal: "<<endl;
            for(int i=0; i<bfs.size(); i++){
                outputFile << bfs[i] << " ";
            }
            outputFile << endl;
            cout<<"Output File Generated : "<<fileName<<endl;
            cout << "Execution Time: " << excutionTime << " ms" << endl;
            break;
        }
        case 0:
            cout<<"God Back"<<endl;
            return;
        default:
            cout<<"Invalid choice"<<endl;
            break;
    }

    return ;
}