#include "sssp.h"
#include <queue>

using namespace std;

vector<long long> sssp(const CSRGraph &g, int src){
    vector<long long> dist(g.V, SSSP_INF);
    if (src < 0 || src >= g.V) {
        return dist; 
    }

    using Node = pair<long long, int>;  // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;  // Path Cost lesser than that is already available

        for (int idx = g.row_ptr[u]; idx < g.row_ptr[u + 1]; ++idx) {
            int v = g.col_idx[idx];
            long long weight = g.values[idx];
            long long nd = d + weight;
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }

    return dist;
}

void ssspDriver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_01/tests/sssp_tests");
            AdjListWeighted g = readWeightedGraph(file);
            CSRGraph csr = buildCSR(g);

            auto start = chrono::high_resolution_clock::now();
            vector<long long> ssspDist = sssp(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(file,"sssp");
            ofstream outputFile(fileName);
            outputFile<<"SSSP Distances: "<<endl;
            for(int i=0; i<ssspDist.size(); i++){
                outputFile << ssspDist[i] << " ";
            }
            outputFile << endl;
            cout<<"Output File Generated : "<<fileName<<endl;
            cout << "Execution Time: " << excutionTime << " ms" << endl;
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_01/tests/sssp_tests");

            for(auto &file : files){
                AdjListWeighted g = readWeightedGraph(file);
                CSRGraph csr = buildCSR(g);

                auto start = chrono::high_resolution_clock::now();
                vector<long long> ssspDist = sssp(csr, g.source);
                auto end = chrono::high_resolution_clock::now();
                double excutionTime = chrono::duration<double,milli>(end-start).count();
                string fileName = createOutputFiles(file,"sssp");
                ofstream outputFile(fileName);
                outputFile<<"SSSP Distances: "<<endl;
                for(int i=0; i<ssspDist.size(); i++){
                    outputFile << ssspDist[i] << " ";
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
            AdjListWeighted g = readWeightedGraph(path);
            CSRGraph csr = buildCSR(g);

            auto start = chrono::high_resolution_clock::now();
            vector<long long> ssspDist = sssp(csr, g.source);
            auto end = chrono::high_resolution_clock::now();
            double excutionTime = chrono::duration<double,milli>(end-start).count();
            string fileName = createOutputFiles(path,"sssp");
            ofstream outputFile(fileName);
            outputFile<<"SSSP Distances: "<<endl;
            for(int i=0; i<ssspDist.size(); i++){
                outputFile << ssspDist[i] << " ";
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