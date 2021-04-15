#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>

#define EPSILON 0.0000000000001 //Lower precicion for now, MUST updata later maybe try #define EPSILON 1E-10

// Helper Functions:

// Abs is inspired from the provided funtion in Lecture 9
double Abs(double x) {
    return x < 0 ? -x : x;
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

// Exp is inspired from the provided function on the CSE13S Piazza
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k++) {
        term *= x/k;
	sum += term;
    }
    return sum;
}


// Library Functions:

// arcSin function:
double arcSin(double x) {
    if (Abs(x) > 0.8) { // To prevent larger error when x approaches 1, use trig property provided in Piazza
        double value = ((M_PI)/2), plugin_value = (Sqrt((1 - x * x)));
        
	value -= arcSin(plugin_value); // Recursion to the rescue!

	if (Abs(x) != x) { // Since sign of x is removed in plugin_value translation, it is added back into consideration here
	    value *= (-1);
        }
        
	return value;
    }

    else {
        double step_size = x, value = x;
        for (int k = 1; Abs(step_size) > EPSILON; k++) {
            step_size = step_size *(((2 * k - 1) * (2 * k - 1) * x * x)/((2 * k) * (2 * k + 1)));
	    value = value + step_size;
        }
        return value;
    }
}

// arcCos function
double arcCos(double x) {
    double value = ((M_PI)/2);
    return (value - arcSin(x));
}

// arcTan function
double arcTan(double x) {
    double plugin_value = (x/Sqrt((x * x + 1)));
    return (arcSin(plugin_value));
}

// Log function
double Log(double x) {
    double value = 1, step_size = x;
    for (int k = 1; Abs(step_size) > EPSILON; k++) {
        step_size = ((x - Exp(value))/Exp(value));
	value = value + step_size;
    }
    return value;
}
