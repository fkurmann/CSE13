#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: Functions partition(), quick_sort_stack(), and quick_sort_queue() are inspired by pseudocode provided by Professor Long in the assignment handout.

extern int64_t moves, comparisons;
extern uint32_t max_stack, max_queue;

// Partition helper method called by both quicksort functions
int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    uint32_t pivot = A[lo + ((hi - lo) / 2)], holder;
    int64_t x_lo = lo - 1, x_hi = hi + 1;
    while (x_lo < x_hi) {
        x_lo++;
        // Add comparisons during and one after while loops
        while (A[x_lo] < pivot) {
            x_lo++;
            comparisons++;
        }
        comparisons++;
        x_hi--;
        while (A[x_hi] > pivot) {
            x_hi--;
            comparisons++;
        }
        comparisons++;
        if (x_lo < x_hi) {
            // Swap the components at positions x_hi and x_lo
            holder = A[x_lo];
            A[x_lo] = A[x_hi];
            A[x_hi] = holder;
            moves += 3;
        }
    }
    return x_hi;
}

// Quick sort stack function which uses the stack ADT to conduct and iterative quicksort
void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t lo = 0, hi = n - 1, p;
    Stack *qs_stack = stack_create(n);
    stack_push(qs_stack, lo);
    stack_push(qs_stack, hi);
    // Update max stack size
    if (stack_size(qs_stack) > max_stack) {
        max_stack = stack_size(qs_stack);
    }

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
        // Update max stack size
        if (stack_size(qs_stack) > max_stack) {
            max_stack = stack_size(qs_stack);
        }
    }
    stack_delete(&qs_stack); // Don't forget to free the stack
}

// Quick sort queue function which uses the queue ADT to conduct and iterative quicksort
void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t lo = 0, hi = n - 1, p;
    Queue *qs_queue = queue_create(n);
    enqueue(qs_queue, lo);
    enqueue(qs_queue, hi);
    // Update max queue size
    if (queue_size(qs_queue) > max_queue) {
        max_queue = queue_size(qs_queue);
    }

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
        // Update max queue size
        if (queue_size(qs_queue) > max_queue) {
            max_queue = queue_size(qs_queue);
        }
    }
    queue_delete(&qs_queue); // Don't forget to free the queue
}
