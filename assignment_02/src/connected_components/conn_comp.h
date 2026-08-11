#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

// Function prototypes for connected components
#include<vector>
#include<iostream>
using namespace std;
#include "../../../assignment_01/src/csr/csr.h"

struct ComponentsResult{
    int numComponents =0;
    vector<int> component;
};
ComponentsResult count_connected_components(CSRGraph &g);

void ccDriver();

#endif // CONNECTED_COMPONENTS_H