#include "tri_count.h"
#include <algorithm>
#include <set>
#include <array>
#include <chrono>
#include <fstream>
#include <limits>

#include "../io/graph_io2.h"
#include "../../../common_wrapper/menu.h"
#include "../../../common_wrapper/utilities.h"


using namespace std;
TriangleResult countTriangle(CSRGraph &g){
    TriangleResult result;
    set<array<int,3>> unique_triangles;

    for (int u = 0; u < g.V; u++) {
        for (int i = g.row_ptr[u]; i < g.row_ptr[u+1]; i++) {
            int v = g.col_idx[i];
            if (v == u) continue;

            for (int j = g.row_ptr[v]; j < g.row_ptr[v+1]; j++) {
                int w = g.col_idx[j];
                if (w == u || w == v) continue;

                // check that edge u-w actually exists
                bool uw_edge = binary_search(
                    g.col_idx.begin() + g.row_ptr[u],
                    g.col_idx.begin() + g.row_ptr[u+1],
                    w
                );
                if (!uw_edge) continue;

                array<int,3> triset = {u, v, w};
                sort(triset.begin(), triset.end());
                if (unique_triangles.insert(triset).second) {
                    result.triangles.push_back(triset);
                    result.totalTriangles++;
                }
            }
        }
    }

    return result;
}

namespace {
    void runOne(const string& file) {
        AdjListUnweighted g = readGraphNoSource(file);
        CSRGraph csr = buildCSR(g);

        auto start = chrono::high_resolution_clock::now();
        TriangleResult result = countTriangle(csr);
        auto end = chrono::high_resolution_clock::now();
        double executionTime = chrono::duration<double, milli>(end - start).count();

        string fileName = createOutputFiles2(file, "tc");
        ofstream outputFile(fileName);
        outputFile << "Algorithm: Triangle Counting\n";
        outputFile << "Total triangles: " << result.totalTriangles << "\n";
        if (!result.triangles.empty()) {
            outputFile << "Triangles found:\n";
            for (const auto& t : result.triangles) {
                outputFile << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")\n";
            }
        }
        outputFile << "Execution time: " << executionTime << " ms\n";

        cout << "Output File Generated : " << fileName << endl;
        cout << "Total triangles: " << result.totalTriangles << endl;
        cout << "Execution Time: " << executionTime << " ms" << endl;
    }
}

void tcDriver(){
    int choice = Menu::showInputMenu();
    switch(choice){
        case 1:{
            string file = chooseFiles("./assignment_02/tests/tc");
            runOne(file);
            break;
        }
        case 2:{
            vector<string> files = getTestsFiles("./assignment_02/tests/tc");
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