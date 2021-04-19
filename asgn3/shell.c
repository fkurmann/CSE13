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

// Shell sort method, given pointer to unsorted array and the array's length, sorts using the gap sequence in gaps.h
void shell_sort(uint32_t *A, uint32_t n) {
    for (int i = 0; i < GAPS; i++) {
	uint32_t gap = gaps[i];

        for (uint32_t j = gap; j < n; j++) {
	    uint32_t index = j, holder = A[j];

	    while (index >= gap && holder < A[index - gap]) {
	        // Swap the components seperated by the current gap
		A[index] = A[index-gap];
		A[index-gap] = holder;

		index -= gap;
            }
	    A[index] = holder;	    
	}
    }
}





