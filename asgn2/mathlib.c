#include "mathlib.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1E-10

// Helper Functions:

// CITATION: Abs is inspired from the provided funtion in Lecture 9
double Abs(double x) {
    return x < 0 ? -x : x;
}

// CITATION: Sqrt is inspired from the provided function on the CSE13S Piazza
double Sqrt(double x) {
    double value = 1.0;
    for (double guess = 0.0; Abs(value - guess) > EPSILON; value = (value + x / value) / 2.0) {
        guess = value;
    }
    return value;
}

// CITATION: Exp is inspired from the provided function on the CSE13S Piazza
double Exp(double x) {
    double step_size = 1, value = 1;
    for (int k = 1; Abs(step_size) > EPSILON; k++) {
        step_size *= x / k;
        value += step_size;
    }
    return value;
}

// Homemade Library Functions:

// arcSin function, using Taylor Series to solve for inverse sin
double arcSin(double x) {
    // To prevent larger error when x approaches 1, use trig property provided in Piazza
    if (Abs(x) > 0.71) {
        double value = ((M_PI) / 2), plugin_value = (Sqrt((1 - x * x)));
        value -= arcSin(plugin_value); // Recusivly call arcSin of a value further from |1|
        if (Abs(x)
            != x) { // Since sign of x is removed in plugin_value translation, it is added back into consideration here
            value *= (-1);
        }
        return value;
    }
    // Normal case of arcSin, when input to function is not close to |1|.
    else {
        double step_size = x, value = x;
        for (int k = 1; Abs(step_size) > EPSILON; k++) {
            step_size = step_size * (((2 * k - 1) * (2 * k - 1) * x * x) / ((2 * k) * (2 * k + 1)));
            value = value + step_size;
        }
        return value;
    }
}

// arcCos function, using the trig property (arcCos = Pi/2 - arcSin), thus calling arcSin to solve
double arcCos(double x) {
    return (((M_PI) / 2) - arcSin(x));
}

// arcTan function, using the trip property (arcTan = arcSin ((x)/sqrt(x^2 + 1)), thus calling arcSin to solve
double arcTan(double x) {
    double plugin_value = (x / Sqrt((x * x + 1)));
    return (arcSin(plugin_value));
}

// Log function, using Newton's method to iterativly solve for ln(x)
double Log(double x) {
    double value = 1, step_size = x;
    for (int k = 1; Abs(step_size) > EPSILON; k++) {
        step_size = ((x - Exp(value)) / Exp(value));
        value = value + step_size;
    }
    return value;
}
