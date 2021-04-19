#include "bubble.h"
#include "gaps.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


void quick_sort_stack(uint32_t *A, uint32_t n);
void quick_sort_queue(uint32_t *A, uint32_t n);
int64_t partition();

// Temporary main method
int main() {
    uint32_t tester[] = {4, 7, 2, 6, 92, 14, 9, 83, 1};
    
    // Print original array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }

    quick_sort_stack(tester, 9);
    
    // Print hopefully sorted array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }
    return 0;
}
int64_t partition(uint32_t *A, int lo, int hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)];  // CHECK THE DIVISION IN THIS LINE
    int i = lo - 1, j = hi +i;

    
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    
}






