#include "quick.h"
#include "stack.h"
#include "queue.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


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

    quick_sort_queue(tester, 9);
    
    // Print hopefully sorted array
    for (int i = 0; i < 9; i++) {
        printf("%u \n", tester[i]);
    }
    return 0;
}
int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)], holder;  // CHECK THE DIVISION IN THIS LINE
    int64_t x_lo = lo - 1, x_hi = hi + 1;
    while (x_lo < x_hi) {
        x_lo++;
        while (A[x_lo] < pivot) {
	    x_lo++;
	}
	x_hi--;
	while (A[x_hi] > pivot) {
	    x_hi--;
	}
	if (x_lo < x_hi) {
	    holder = A[x_lo];
	    A[x_lo] = A[x_hi];
	    A[x_hi] = holder;
	}
    }
    return x_hi;
    
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0, hi = n - 1, p;
    Stack *qs_stack = stack_create(100);
    stack_push(qs_stack, lo);
    stack_push(qs_stack, hi);
    while (stack_empty(qs_stack) == false) {
       stack_pop(qs_stack, &hi);
       stack_pop(qs_stack, &lo);
       p = partition(A, lo, hi);
       if (lo < p) {
           stack_push(qs_stack, lo);
           stack_push(qs_stack, p);
       } 
       if (hi > p + 1) {
           stack_push(qs_stack, p + 1);
           stack_push(qs_stack, hi);
       }
    }
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0, hi = n - 1, p;
    Queue *qs_queue = queue_create(100);
    enqueue(qs_queue, lo);
    enqueue(qs_queue, hi);
    while (queue_empty(qs_queue) == false) {
       dequeue(qs_queue, &lo);
       dequeue(qs_queue, &hi);
       p = partition(A, lo, hi);
       if (lo < p) {
           enqueue(qs_queue, lo);
           enqueue(qs_queue, p);
       } 
       if (hi > p + 1) {
           enqueue(qs_queue, p + 1);
           enqueue(qs_queue, hi);
       }
    }
}






