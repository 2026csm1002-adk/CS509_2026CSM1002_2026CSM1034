#ifndef DRIVER_H
#define DRIVER_H

#include "../assignment_02/src/betweenness/betweenness.h"
#include "../../../assignment_01/src/io/graph_io.h"
#include "../../../assignment_01/src/csr/csr.h"
#include "../../../assignment_01/src/csr/csr.h"
#include "../assignment_02/src/connected_components/conn_comp.h"
#include "../assignment_02/src/triangle_counting/tri_count.h"
#include <string>
using namespace std;

enum class Algorithm2 { TRIANGLE_COUNTING, BETWEENNESS_CENTRALITY, CONNECTED_COMPONENTS };

// Reads the input file, builds CSR (untimed), runs the selected
// algorithm (timed), and prints the result in the format required by
// Assignment_2.pdf.
void runDriver2(Algorithm2 algo, const string& filepath);

// Convenience overload: parses "tc" / "bc" / "cc" (case-insensitive).
void runDriver2(const string& algoName, const string& filepath);

#endif
