#ifndef GRAPH_IO3_H
#define GRAPH_IO3_H

#include <string>
#include<vector>
using namespace std;
struct AdjList{
    int V=0;
    int E=0;
    vector<vector<pair<int,int>>>adj;
    int source = 0;
    int sink=0;
};


struct CSR{
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};


AdjList readGraph(const std::string& filepath);

CSR buildCSR(AdjList & g);

#endif