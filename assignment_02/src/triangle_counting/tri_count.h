#ifndef TRI_COMP_H
#define TRI_COMP_H

#include<vector>
#include<iostream>
#include "../../../assignment_01/src/csr/csr.h"
using namespace std;
struct TriangleResult{
    long long totalTriangles=0;
    vector<array<int, 3>> triangles;
};

TriangleResult countTriangle(CSRGraph &g);


#endif //TRI_COMP_H