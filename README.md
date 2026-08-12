# CS509 Laboratory Repository (Buddy)

## Repository Overview
This repository contains all assignment programs for the Buddy Tasks of the CS509 – PG Software Lab course. 

## Student / Pair Details
- Student 1: Md Sadruzzama, 2026CSM1034
- Student 2: Aditya Kumar, 2026CSM1002

## Language and Environment
- Language: C++17
- Compiler: g++ Apple clang version 21.0.0 / g++.exe (Rev3, Built by MSYS2 project) 13.2.0
- OS / machine: MacOS/WSL(ubuntu)
- Build tool: `make`

## Directory Structure
```
common_wrapper/        Repo-level menu (build/run any assignment)
assignment_01_buddy/
  driver/               Reads input, builds CSR, times & runs the algorithm
  src/io/                File parsing (unweighted + weighted adjacency lists)
  src/csr/                Adjacency-list -> CSR conversion (untimed)
  src/bfs/, src/dfs/, src/sssp/   Algorithm implementations
  tests/                  One test case per file
  outputs/                Captured run outputs (optional)
```

## Common Wrapper: Build and Usage
```
make            # builds ./cs509
make clean
```
The wrapper menu lets you run a single test file or all test files for
BFS / DFS / SSSP.

## Assignment 01 - Graph Algorithms (BFS, DFS, SSSP)

### Assignment Mode
Double / Buddy

### Objective
Implement BFS, DFS, and SSSP (Dijkstra, positive weights only) over
graphs stored in CSR format, converted from an adjacency-list input file.

### Algorithm / Approach
- **BFS**: queue-based level-order traversal;
- **DFS**: iterative, explicit-stack traversal (neighbor order preserved to match input file order).
- **SSSP**: Dijkstra's algorithm with a binary min-heap (`priority_queue`).

### Input Format
- BFS/DFS: unweighted adjacency list (`V E` / `u degree n1 n2 ...` ).
- SSSP: positive-weighted adjacency list (`V E` / `u degree n1 w1 n2 w2 ...` / `SOURCE s`).
- Graph type: Undirected (each edge listed in both endpoints' adjacency lists).

### Helper Functions / CSR Conversion
`src/csr/csr.cpp` converts either adjacency-list type into CSR
(`row_ptr`, `col_idx`, `values`). Conversion is performed before the
timer starts and is excluded from the reported algorithm time.

### File Structure
See Directory Structure above.

### Compilation
```
make
```

### Execution
```
./cs509
```
Then choose an option from the menu (single file or all files, per algorithm).

### Test Cases and Result Table

| Mode | Test File | Input Type | Input Size | Expected Output | Algorithm Time |
|---|---|---|---|---|---|
| int | bfs_10.txt | Unweighted adjacency list | V=10, E=15 | Traversal / distances | 0.002333 ms |
| int | bfs_100.txt | Unweighted adjacency list | V=100, E=150 | Traversal / distances | 0.00441 ms |
| int | bfs_10000.txt | Unweighted adjacency list | V=10000, E=15000 | Traversal / distances | 0.231208 ms |
| int | bfs_50000.txt | Unweighted adjacency list | V=50000, E=75000 | Traversal / distances | 1.53433  ms |
| int | bfs_100000.txt | Unweighted adjacency list | V=100000, E=150000 | Traversal / distances | 2.02792 ms | 
| int | dfs_10.txt | Unweighted adjacency list | V=10, E=15 | Traversal | 0.001625 ms | 
| int | dfs_100.txt | Unweighted adjacency list | V=100, E=150 | Traversal | 0.003708 ms |
| int | dfs_10000.txt | Unweighted adjacency list | V=10000, E=15000 | Traversal | 0.229416 ms |
| int | dfs_50000.txt | Unweighted adjacency list | V=50000, E=75000 | Traversal | 1.54638 ms |
| int | dfs_100000.txt | Unweighted adjacency list | V=100000, E=150000 | Traversal | 2.31192 ms |
| int | sssp_10.txt | Positive-weighted adjacency list | V=10, E=15 | Shortest distances | 0.001083 ms | 
| int | sssp_100.txt | Positive-weighted adjacency list | V=100, E= 150 | Shortest distances | 0.008167 ms | 
| int | sssp_10000.txt | Positive-weighted adjacency list | V=10000, E=15000 | Shortest distances |0.667083  ms | 
| int | sssp_50000.txt | Positive-weighted adjacency list | V=50000, E=75000 | Shortest distances |  5.95854 ms | 
| int | sssp_100000.txt | Positive-weighted adjacency list | V=100000, E=150000 | Shortest distances | 8.69542 ms |

### Complexity
- BFS: Time O(V + E), Space O(V + E)
- DFS: Time O(V + E), Space O(V + E)
- SSSP (Dijkstra + binary heap): Time O((V + E) log V), Space O(V + E)

### LINK
- [github.com/](https://github.com/2026csm1002-adk/CS509_2026CSM1002_2026CSM1034)


## Assignment - 02
- we have implemented 3 algorithms named with contribution;
- 1. Triangle Counting (contributed by Md Sadruzzama)
- 2. Betweenness Centrality(contributed by Aditya Kumar)
- 3. Connected Components(contributed by Md Sadruzzama)
## Directory Structure
assignment_02/
├── driver/
│   ├── driver.cpp
│   └── driver.h
├── outputs/
├── src/
│   ├── betweenness/
│   │   ├── betweenness.cpp
│   │   └── betweenness.h
│   ├── connected_components/
│   │   ├── conn_comp.cpp
│   │   └── conn_comp.h
│   ├── io/
│   │   ├── graph_io2.cpp
│   │   └── graph_io2.h
│   └── triangle_counting/
│       ├── tri_count.cpp
│       └── tri_count.h
└── tests/
├── bc/
├── cc/
└── tc/
common_wrapper/
├── main.cpp
├── menu.cpp
├── menu.h
└── utilities.h

### 11.2 Graph Analytics Results Table

| Algorithm | Test File | Vertices | Edges | Expected Output | Actual Output | Time | Status |
|---|---|---|---|---|---|---|---|
| Triangle Counting | tc_10.txt | 10 | 15 | Total triangles | Total triangles | 0.00312 ms | Pass |
| Triangle Counting | tc_100.txt | 100 | 150 | Total triangles | Total triangles | 0.01240 ms | Pass |
| Triangle Counting | tc_10000.txt | 10000 | 15000 | Total triangles | Total triangles | 1.84210 ms | Pass |
| Triangle Counting | tc_50000.txt | 50000 | 75000 | Total triangles | Total triangles | 5.27104 ms | Pass |
| Triangle Counting | tc_100000.txt | 100000 | 150000 | Total triangles | Total triangles | 18.6321 ms | Pass |
| Betweenness Centrality | bc_10.txt | 10 | 15 | Centrality per vertex | Centrality per vertex | 0.00845 ms | Pass |
| Betweenness Centrality | bc_100.txt | 100 | 150 | Centrality per vertex | Centrality per vertex | 0.14230 ms | Pass |
| Betweenness Centrality | bc_1000.txt | 1000 | 1500 | Centrality per vertex | Centrality per vertex | 14.8520 ms | Pass |
| Betweenness Centrality | bc_5000.txt | 5000 | 7500 | Centrality per vertex | Centrality per vertex | 382.104 ms | Pass |
| Betweenness Centrality | bc_10000.txt | 10000 | 15000 | Centrality per vertex | Centrality per vertex | 1542.89 ms | Pass |
| Connected Components | cc_10.txt | 10 | 15 | Component per vertex | Component per vertex | 0.00185 ms | Pass |
| Connected Components | cc_100.txt | 100 | 150 | Component per vertex | Component per vertex | 0.00412 ms | Pass |
| Connected Components | cc_10000.txt | 10000 | 15000 | Component per vertex | Component per vertex | 0.28410 ms | Pass |
| Connected Components | cc_50000.txt | 50000 | 75000 | Component per vertex | Component per vertex | 1.62140 ms | Pass |
| Connected Components | cc_100000.txt | 100000 | 150000 | Component per vertex | Component per vertex | 3.10420 ms | Pass |