#include "maxflow_mincut.h"


#include "maxflow_mincut.h"
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;


// ------------------------------------------------------------
// Residual edge
// ------------------------------------------------------------
struct ResidualEdge {
    int to;
    int capacity;
    int reverse_index;
};


// ------------------------------------------------------------
// Add an edge to the residual graph
// ------------------------------------------------------------
void addEdge(vector<vector<ResidualEdge>>& graph,int u,int v,int capacity){
    ResidualEdge forward;
    forward.to = v;
    forward.capacity = capacity;
    forward.reverse_index = graph[v].size();

    ResidualEdge backward;
    backward.to = u;
    backward.capacity = 0;
    backward.reverse_index = graph[u].size();

    graph[u].push_back(forward);
    graph[v].push_back(backward);
}


// ------------------------------------------------------------
// BFS
//
// Creates the level graph.
//
// level[v] = distance of v from source
//            in the residual graph.
//
// Returns true if sink is reachable.
// ------------------------------------------------------------
bool bfs(vector<vector<ResidualEdge>>& graph,int source,int sink,vector<int>& level){
    fill(level.begin(), level.end(), -1);

    queue<int> q;

    level[source] = 0;
    q.push(source);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (const ResidualEdge& edge : graph[u]){
            // We can only use an edge that still
            // has some capacity.
            if (edge.capacity > 0 && level[edge.to] == -1){
                level[edge.to] = level[u] + 1;
                q.push(edge.to);
            }
        }
    }

    return level[sink] != -1;
}


// ------------------------------------------------------------
// DFS
//
// Tries to send flow from u to sink.
//
// flow = maximum amount of flow that can currently
//        be sent to u.
// ------------------------------------------------------------
int dfs(vector<vector<ResidualEdge>>& graph,int u,int sink,int flow,vector<int>& level,vector<int>& nextEdge){
    // We reached the sink.
    if (u == sink) return flow;


    // Try edges starting from nextEdge[u].
    for (int& i = nextEdge[u];i < (int)graph[u].size();i++){
        ResidualEdge& edge = graph[u][i];


        // Edge must have capacity
        // AND must go exactly one level forward.
        if (edge.capacity > 0 && level[edge.to] == level[u] + 1){
            int possibleFlow = min(flow, edge.capacity);


            int pushed = dfs(graph,edge.to,sink,possibleFlow,level,nextEdge);


            // DFS successfully sent some flow.
            if (pushed > 0){
                // Reduce forward residual capacity.
                edge.capacity -= pushed;


                // Increase reverse residual capacity.
                graph[edge.to][edge.reverse_index].capacity
                    += pushed;


                return pushed;
            }
        }
    }


    // No flow could be sent from u.
    return 0;
}


// ------------------------------------------------------------
// Dinic's Maxflow-Mincut
// ------------------------------------------------------------
MaxflowResult maxflow_mincut(int source, int sink, CSR& csr)
{
    MaxflowResult result;

    result.source = source;
    result.sink = sink;
    result.maxflow = 0;
    result.min_cut_cap = 0;


    // Number of vertices.
    int V = csr.row_ptr.size() - 1;


    // --------------------------------------------------------
    // STEP 1:
    // Create residual graph.
    // --------------------------------------------------------

    vector<vector<ResidualEdge>> graph(V);


    // Copy original CSR edges into residual graph.
    for (int u = 0; u < V; u++)
    {
        for (int i = csr.row_ptr[u];i < csr.row_ptr[u + 1]; i++)
        {
            int v = csr.col_idx[i];
            int capacity = csr.values[i];

            addEdge(
                graph,
                u,
                v,
                capacity
            );
        }
    }


    // --------------------------------------------------------
    // STEP 2:
    // Dinic's algorithm
    // --------------------------------------------------------

    vector<int> level(V);
    vector<int> nextEdge(V);


    while (bfs(graph, source, sink, level)){
        // Start examining edges from the beginning
        // for every vertex.
        fill(nextEdge.begin(), nextEdge.end(), 0);


        while (true){
            int pushed = dfs(graph,source,sink,INT_MAX,level,nextEdge);


            // No more flow can be sent through
            // this level graph.
            if (pushed == 0)
                break;


            result.maxflow += pushed;
        }
    }


    // --------------------------------------------------------
    // STEP 3:
    // Find source side of minimum cut.
    //
    // Run BFS on FINAL residual graph.
    // Only follow edges with capacity > 0.
    // --------------------------------------------------------

    vector<bool> reachable(V, false);

    queue<int> q;

    reachable[source] = true;
    q.push(source);


    while (!q.empty())
    {
        int u = q.front();
        q.pop();


        for (const ResidualEdge& edge : graph[u])
        {
            if (edge.capacity > 0 &&
                !reachable[edge.to])
            {
                reachable[edge.to] = true;
                q.push(edge.to);
            }
        }
    }


    // --------------------------------------------------------
    // STEP 4:
    // Separate vertices into two sides.
    // --------------------------------------------------------

    for (int v = 0; v < V; v++)
    {
        if (reachable[v])
        {
            result.sourceNode.push_back(v);
        }
        else
        {
            result.sinkNode.push_back(v);
        }
    }


    // --------------------------------------------------------
    // STEP 5:
    // Find cut edges.
    // Cut edge:
    //
    //      u is reachable
    //      v is not reachable
    // Therefore:
    //
    //      u -> v
    //
    // crosses the minimum cut.
    // --------------------------------------------------------

    for (int u = 0; u < V; u++){
        if (!reachable[u])
            continue;


        for (int i = csr.row_ptr[u];i < csr.row_ptr[u + 1];i++){
            int v = csr.col_idx[i];
            int capacity = csr.values[i];


            if (!reachable[v]){

                Edges edge;

                edge.u = u;
                edge.v = v;
                edge.w = capacity;

                result.cutEdges.push_back(edge);

                result.min_cut_cap += capacity;
            }
        }
    }


    return result;
}