#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <string>
#include <utility>
#include <vector>
using namespace std;


// Input Format Unweighted
// V E
// node degree neighbour1 neighbour2
// ...
// SOURCE s

struct AdjListUnweighted{
    int V = 0;
    int E = 0;
    vector<vector<int>>adj;
    int source = 0;
};

// Input Format Weighted
// V E
// node degree n1 w1 n2 w2
// ...
// SOURCE s

struct AdjListWeighted{
    int V = 0;
    int E = 0;
    vector<vector<pair<int,int>>>adj;
    int source = 0;
};

// Reads a BFS/DFS-style unweighted adjacency-list

AdjListUnweighted readUnweightedGraph(const string& filepath);


// Reads an SSSP-style positive-weighted adjacency-list

AdjListWeighted readWeightedGraph(const string& filepath);

#endif