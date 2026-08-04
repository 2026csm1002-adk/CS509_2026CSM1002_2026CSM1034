#ifndef BFS_H
#define BFS_H

#include "../common/graph_io.h"
#include <vector>
#include <queue>

std::vector<int> bfsTraversal(const CSRGraph &g, int src);

#endif //BFS_H