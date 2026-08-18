#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>
using namespace std;

// f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d
// coefficients[i] is the coefficient of x^i, so coefficients.size() == degree + 1
struct GDInput {
    int degree;
    vector<double> coefficients;
    double initialX;
    double learningRate;
    double tolerance;
    long long maxIterations;
};

struct GDResult {
    int degree;
    double finalX;
    double finalFx;
    long long iterations;
    bool converged;
};

// Evaluates f(x) = c0 + c1*x + c2*x^2 + ... + cd*x^d
double evaluatePolynomial(const vector<double>& coefficients, double x);

// Evaluates f'(x) = c1 + 2*c2*x + 3*c3*x^2 + ... + d*cd*x^(d-1)
double evaluateDerivative(const vector<double>& coefficients, double x);

// Runs Gradient Descent until |f'(x)| <= tolerance or maxIterations is reached.
GDResult runGradientDescent(const GDInput& input);

#endif
