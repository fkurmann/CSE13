#include "bubble.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void bubble_sort(uint32_t *A, uint32_t n);

// Temporary main method
int main() {
    uint32_t tester[] = {4, 7, 2, 6, 92, 14, 9, 83, 1};
    
    // Print original array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }

    bubble_sort(tester, 9);
    
    // Print hopefully sorted array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }
    return 0;
}

// Bubble sort method given pointer to an array and its length sorts the array via bubble sort 
void bubble_sort(uint32_t *A, uint32_t n) {
    uint32_t size = n;
    int swapped = 1; //Swapped boolean
    while (swapped == 1)  { 
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

