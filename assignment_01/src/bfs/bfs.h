#ifndef BFS_H
#define BFS_H

#include<iostream>
#include "../io/graph_io.h"
#include "../csr/csr.h"
#include "../../../common_wrapper/utilities.h"
#include "../../../common_wrapper/menu.h"
#include <vector>
#include <queue>

std::vector<int> bfsTraversal(const CSRGraph &g, int src);

void bfsDriver();

#endif //BFS_H