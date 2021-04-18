#include "bubble.h"
#include "gaps.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void shell_sort(uint32_t *A, uint32_t n);

// Temporary main method
int main() {
    uint32_t tester[] = {4, 7, 2, 6, 92, 14, 9, 83, 1};
    
    // Print original array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }

    shell_sort(tester, 9);
    
    // Print hopefully sorted array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }
    return 0;
}

void shell_sort(uint32_t *A, uint32_t n) {
    uint32_t size = n;
    int swapped = 1;
    while (swapped == 1)  { // Check if you can make it just be while swapped
        swapped = 0;
	for (uint32_t i = 1; i < size; i++) {
	    if (A[i] < A[i-1]) {
	        uint32_t holder = A[i]; // Check if this holder is doing it's job and if it's needed
		A[i] = A[i-1];
		A[i-1] = holder;
		swapped = 1;
	    }
	}
    size--;
    }
}

