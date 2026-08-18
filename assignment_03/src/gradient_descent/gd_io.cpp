#include "gd_io.h"
#include <fstream>
#include <stdexcept>
using namespace std;

GDInput readGDInput(const string& filepath) {
    ifstream in(filepath);
    if (!in.is_open()) {
        throw runtime_error("Could not open input file: " + filepath);
    }

    GDInput input;
    string tag;

    // DEGREE d
    in >> tag >> input.degree;
    if (!in || tag != "DEGREE" || input.degree < 0) {
        throw runtime_error("Invalid or missing DEGREE line in file: " + filepath);
    }

    // COEFFICIENTS c0 c1 ... cd  (exactly degree+1 values)
    in >> tag;
    if (!in || tag != "COEFFICIENTS") {
        throw runtime_error("Missing COEFFICIENTS line in file: " + filepath);
    }
    input.coefficients.resize(input.degree + 1);
    for (int i = 0; i <= input.degree; ++i) {
        in >> input.coefficients[i];
        if (!in) {
            throw runtime_error("Coefficient count does not match degree+1 in file: " + filepath);
        }
    }

    // INITIAL_X x0
    in >> tag >> input.initialX;
    if (!in || tag != "INITIAL_X") {
        throw runtime_error("Missing INITIAL_X line in file: " + filepath);
    }

    // LEARNING_RATE alpha
    in >> tag >> input.learningRate;
    if (!in || tag != "LEARNING_RATE" || input.learningRate <= 0) {
        throw runtime_error("Invalid or missing LEARNING_RATE (must be positive) in file: " + filepath);
    }

    // TOLERANCE epsilon
    in >> tag >> input.tolerance;
    if (!in || tag != "TOLERANCE" || input.tolerance <= 0) {
        throw runtime_error("Invalid or missing TOLERANCE (must be positive) in file: " + filepath);
    }

    // MAX_ITERATIONS n
    in >> tag >> input.maxIterations;
    if (!in || tag != "MAX_ITERATIONS" || input.maxIterations <= 0) {
        throw runtime_error("Invalid or missing MAX_ITERATIONS (must be positive) in file: " + filepath);
    }

    return input;
}
