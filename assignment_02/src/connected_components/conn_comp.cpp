#include "conn_comp.h"
#include <unordered_map>
#include <chrono>
#include <fstream>
#include <limits>

#include "../io/graph_io2.h"
#include "../../../common_wrapper/menu.h"
#include "../../../common_wrapper/utilities.h"

using namespace std;

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
        if(parent[u] == u) return u;
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

ComponentsResult count_connected_components(CSRGraph &g) {
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
        if(existed.find(upar) == existed.end()){
            existed[upar] = component;
            component++;
        }
        result.component.push_back(existed[upar]);
    }
    result.numComponents = component;

    return result;
}

namespace {
    void runOne(const string& file) {
        AdjListUnweighted g = readGraphNoSource(file);
        CSRGraph csr = buildCSR(g);

        auto start = chrono::high_resolution_clock::now();
        ComponentsResult result = count_connected_components(csr);
        auto end = chrono::high_resolution_clock::now();
        double executionTime = chrono::duration<double, milli>(end - start).count();

        string fileName = createOutputFiles2(file, "cc");
        ofstream outputFile(fileName);
        outputFile << "Algorithm: Connected Components\n";
        outputFile << "Number of components: " << result.numComponents << "\n";
        outputFile << "Vertex Component\n";
        for (int v = 0; v < g.V; ++v) {
            outputFile << v << " " << result.component[v] << "\n";
        }
        outputFile << "Execution time: " << executionTime << " ms\n";

        cout << "Output File Generated : " << fileName << endl;
        cout << "Number of components: " << result.numComponents << endl;
        cout << "Execution Time: " << executionTime << " ms" << endl;
    }
}

void ccDriver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_02/tests/cc");
            runOne(file);
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_02/tests/cc");
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