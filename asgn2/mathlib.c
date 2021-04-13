#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>


// Exp is inspired form the provided function on the CSE13S Piazza
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k++) {
        term *= x/k;
	sum += term;
    }
    return sum;
}

// Sqrt is inspired from the provided function on the CSE13S Piazza
double Sqrt(double x) {
    double y = 1.0; 
    assert(x >= 0);
    for (double guess = 0.0; Abs(y - guess) > EPSILON; y = (y + x / y) / 2.0) {
        guess = y;
    }
    return y;
}
