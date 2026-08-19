#ifndef MAXFLOW_MIN
#define MAXFLOW_MIN

#include "../io/graph_io.h"
#include "../../../common_wrapper/menu.h"
#include "../../../common_wrapper/utilities.h"
#include<vector>
#include<filesystem>
#include<fstream>
using namespace std;
namespace fs = filesystem;
struct Edges{
    int u;
    int v;
    int w;
};
struct MaxflowResult{
    int source;
    int sink;
    int maxflow;
    int min_cut_cap;
    vector<int> sourceNode;
    vector<int> sinkNode;

    vector<Edges> cutEdges;
};

MaxflowResult maxflow_mincut(int srouce, int sink, CSR & csr);
void maxflow_mincut_driver();

#endif //MAXFLOW_MIN