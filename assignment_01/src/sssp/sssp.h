#ifndef SSSP_H
#define SSSP_H

#include <climits>
#include <vector>
#include "../csr/csr.h"
#include<iostream>
#include "../io/graph_io.h"
#include "../csr/csr.h"
#include "../../../common_wrapper/utilities.h"
#include "../../../common_wrapper/menu.h"
#include <queue>
using namespace std;

constexpr long long SSSP_INF = LLONG_MAX;

vector<long long>sssp(const CSRGraph& g, int src);

void ssspDriver();
#endif