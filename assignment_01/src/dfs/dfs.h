#ifndef DFS_H
#define DFS_H

#include "../common/graph_io.h"
#include <vector>
#include <stack>

std::vector<int> dfsTraversal(const CSRGraph &g, int src);

#endif //DFS_H