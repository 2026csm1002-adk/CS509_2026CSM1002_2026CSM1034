#ifndef CSR_H
#define CSR_H

#include <vector>
using namespace std;

#include "../io/graph_io.h"

struct CSRGraph{
    int V = 0;
    vector<int>row_ptr;
    vector<int>col_idx;
    vector<int>values;
};

CSRGraph buildCSR(const AdjListUnweighted & g);

CSRGraph buildCSR(const AdjListWeighted & g);

#endif
