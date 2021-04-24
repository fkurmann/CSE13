#include "bubble.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//CITATION: The bubblesort function is inspried by pseudocode provided by Professor Long.

extern int64_t moves, comparisons;

// Bubble sort method given pointer to an array and its length sorts the array via bubble sort
void bubble_sort(uint32_t *A, uint32_t n) {
    int swapped = 1; // Swapped boolean
    uint32_t holder; // Holder for swapping
    while (swapped == 1) {
        swapped = 0;
        for (uint32_t i = 1; i < n; i++) {
            comparisons++;
            if (A[i] < A[i - 1]) {
                // Swap the items in array indexes i and i-1
                holder = A[i];
                A[i] = A[i - 1];
                A[i - 1] = holder;
                swapped = 1;

                moves += 3;
            }
        }
        n--;
    }
}
