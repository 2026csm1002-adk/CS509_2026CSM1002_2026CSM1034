#ifndef SSSP_H
#define SSSP_H

#include <climits>
#include <vector>
using namespace std;
#include "../csr/csr.h"

constexpr long long SSSP_INF = LLONG_MAX;

vector<long long>sssp(const CSRGraph& g, int src);

void ssspDriver();
#endif