#ifndef CONNECTED_COMPONENTS_H
#define CONNECTED_COMPONENTS_H

// Function prototypes for connected components
#include<vector>
#include<iostream>
using namespace std;

struct ComponentsResult{
    int numComponents =0;
    vector<int> component;
};
ComponentsResult count_connected_components(CSRGraph &g);

#endif // CONNECTED_COMPONENTS_H