#include "gradient_descent.h"
#include <cmath>

double evaluatePolynomial(const vector<double>& coefficients, double x) {
    double result = 0.0;
    double xPower = 1.0;  // x^0
    for (size_t i = 0; i < coefficients.size(); ++i) {
        result += coefficients[i] * xPower;
        xPower *= x;
    }
    return result;
}

double evaluateDerivative(const vector<double>& coefficients, double x) {
    double result = 0.0;
    double xPower = 1.0;  // x^0, used for the (i-1)th power below
    for (size_t i = 1; i < coefficients.size(); ++i) {
        result += static_cast<double>(i) * coefficients[i] * xPower;
        xPower *= x;
    }
    return result;
}

GDResult runGradientDescent(const GDInput& input) {
    double x = input.initialX;
    long long iterations = 0;
    double fpx = evaluateDerivative(input.coefficients, x);
    bool converged = (fabs(fpx) <= input.tolerance);

    while (!converged && iterations < input.maxIterations) {
        x = x - input.learningRate * fpx;
        iterations++;
        fpx = evaluateDerivative(input.coefficients, x);
        converged = (fabs(fpx) <= input.tolerance);
    }

    GDResult result;
    result.degree = input.degree;
    result.finalX = x;
    result.finalFx = evaluatePolynomial(input.coefficients, x);
    result.iterations = iterations;
    result.converged = converged;
    return result;
}
