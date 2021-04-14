#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>

#define EPSILON 0.001 //Lower precicion for now, MUST updata later maybe try #define EPSILON 1E-10

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

// // Pow is inspired from the provided function in Lecture 9 MAY OR MAY NOT NEED
// double Pow(double x, double y) {
//     return Exp(y * Log(x));
// }


// Exp is inspired from the provided function on the CSE13S Piazza
double Exp(double x) {
    double term = 1, sum = 1;
    for (int k = 1; Abs(term) > EPSILON; k++) {
        term *= x/k;
	sum += term;
    }
    return sum;
}

// Tester function main, temporary

int main(void) {
    printf ("arcsin 0.5 = %lf \n", arcSin(0.5));
    printf ("arccos 0.5 = %lf \n", arcCos(0.5));
    printf ("arctan 0.5 = %lf \n", arcTan(0.5));
    printf ("log 2.0 = %lf \n", Log(2.0));
    printf ("e^0.5 = %lf \n", Exp(0.5));

    return 0;
}


// Library Functions:

// arcSin function:
double arcSin(double x) {
    double step_size = x, value = x;

    for (int k = 1; step_size > EPSILON; k++) {
        step_size = step_size *(((2 * k - 1) * (2 * k - 1) * x * x)/((2 * k) * (2 * k + 1)));
	value = value + step_size;
    }
    return value;
}

// arcCos function
double arcCos(double x) {
    double step_size = x, value =((M_PI)/2) - x;

    for (int k = 1; step_size > EPSILON; k++) {
        step_size = step_size *(((2 * k - 1) * (2 * k - 1) * x * x)/((2 * k) * (2 * k + 1)));
	value = value - step_size;
    }
    return value;
}

// arcTan function
double arcTan(double x) {
    double value, plugin_value = (x/Sqrt((x * x + 1)));
    value = arcSin(plugin_value);
    
    return value;
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
