#include "shell.h"

#include "gaps.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: The shellsort function is inspired by pseudocode provided by Professor Long.
// The Gap Sequence was provided by Professor Long.

extern int64_t moves, comparisons;

// Shell sort method, given pointer to unsorted array and the array's length, sorts using the gap sequence in gaps.h
void shell_sort(uint32_t *A, uint32_t n) {
    for (int i = 0; i < GAPS; i++) {
        uint32_t gap = gaps[i];
        for (uint32_t j = gap; j < n; j++) {
            uint32_t index = j, holder = A[j];
            moves++;

            while (index >= gap && holder < A[index - gap]) {
                // Swap the components seperated by the current gap
                A[index] = A[index - gap];
                index -= gap;

                comparisons++;
                moves++;
            }
            //Check that short circuit logic did not kick in
            if (index >= gap) {
                comparisons++;
            }
            A[index] = holder;
            moves++;
        }
    }
}
