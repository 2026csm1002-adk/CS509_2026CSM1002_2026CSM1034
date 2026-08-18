#ifndef GD_IO_H
#define GD_IO_H

#include <string>
#include "gradient_descent.h"

// Reads the Gradient Descent input file format:
//   DEGREE d
//   COEFFICIENTS c0 c1 c2 ... cd
//   INITIAL_X x0
//   LEARNING_RATE alpha
//   TOLERANCE epsilon
//   MAX_ITERATIONS n

GDInput readGDInput(const std::string& filepath);

#endif
