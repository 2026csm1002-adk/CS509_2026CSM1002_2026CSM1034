#ifndef DFS_H
#define DFS_H

#include "../io/graph_io.h"
#include "../csr/csr.h"
#include "../../../common_wrapper/utilities.h"
#include "../../../common_wrapper/menu.h"
#include <vector>
#include <stack>

std::vector<int> dfsTraversal(const CSRGraph &g, int src);

void dfsDriver();

#endif //DFS_H