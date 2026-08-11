#include "betweenness.h"

#include <queue>
#include <stack>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <limits>
using namespace std;

#include "../io/graph_io2.h"
#include "../../../common_wrapper/menu.h"
#include "../../../common_wrapper/utilities.h"

vector<double> betweennessCentrality(const CSRGraph& g) {
    int V = g.V;
    vector<double> centrality(V, 0.0);

    for (int s = 0; s < V; ++s) {
        vector<vector<int>> predecessors(V);
        vector<long long> no_paths(V, 0);
        vector<int> dist(V, -1);
        vector<double> depend(V, 0.0);

        no_paths[s] = 1;
        dist[s] = 0;

        queue<int> bfsQueue;
        bfsQueue.push(s);

        stack<int> visitOrder;

        while (!bfsQueue.empty()) {
            int v = bfsQueue.front();
            bfsQueue.pop();
            visitOrder.push(v);

            for (int idx = g.row_ptr[v]; idx < g.row_ptr[v + 1]; ++idx) {
                int w = g.col_idx[idx];

                if (dist[w] < 0) {
                    dist[w] = dist[v] + 1;
                    bfsQueue.push(w);
                }

                if (dist[w] == dist[v] + 1) {
                    no_paths[w] += no_paths[v];
                    predecessors[w].push_back(v);
                }
            }
        }

        while (!visitOrder.empty()) {
            int w = visitOrder.top();
            visitOrder.pop();

            for (int v : predecessors[w]) {
                double share = (static_cast<double>(no_paths[v]) / static_cast<double>(no_paths[w])) * (1.0 + depend[w]);
                depend[v] += share;
            }

            if (w != s) {
                centrality[w] += depend[w];
            }
        }
    }
    // Due to graph it will get doubled
    for (double& c : centrality) {
        c /= 2.0;
    }

    return centrality;
}

namespace {
    void runOne(const string& file) {
        AdjListUnweighted g = readGraphNoSource(file);
        CSRGraph csr = buildCSR(g);

        auto start = chrono::high_resolution_clock::now();
        vector<double> centrality = betweennessCentrality(csr);
        auto end = chrono::high_resolution_clock::now();
        double executionTime = chrono::duration<double, milli>(end - start).count();

        string fileName = createOutputFiles2(file, "bc");
        ofstream outputFile(fileName);
        outputFile << "Algorithm: Betweenness Centrality\n";
        outputFile << "Vertex Centrality\n";
        outputFile << fixed << setprecision(2);
        for (int v = 0; v < g.V; ++v) {
            outputFile << v << " " << centrality[v] << "\n";
        }
        outputFile << "Execution time: " << executionTime << " ms\n";

        cout << "Output File Generated : " << fileName << endl;
        cout << "Execution Time: " << executionTime << " ms" << endl;
    }
}

void bcDriver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_02/tests/bc");
            runOne(file);
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_02/tests/bc");
            for(auto &file : files){
                runOne(file);
            }
            break;
        }
        case 3:{
            string path;
            cout << "\nEnter file path : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, path);
            runOne(path);
            break;
        }
        case 0:
            cout << "Go Back" << endl;
            return;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}