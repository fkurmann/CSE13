#include "queue.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: The queue constructor, destructor, and structure defenition are those given by Professor Long in the
// assignment handout. The empty, full, dequeue, and enqueue functions are inspired by Professor Long's code from
// the stacks/queues lecture.

struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};

// Create a dynamically allocated stack with a specified capacity.
Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = q->tail = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

// Free items, then free the queue pointer and set it to null
void queue_delete(Queue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

bool queue_empty(Queue *q) {
    return q->head == q->tail;
}

bool queue_full(Queue *q) {
    return q->size == q->capacity;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

// NOTE: Based on the assignment description I was not sure whether to simply make a queue that returned false or grew
// based on demand. As I did in stack.c, I attempted to use realloc to grow the queue, however, found out in the process
// that it simply would not work with an array based queue due to the nature or the circular queue. I am aware that an
// option is to not use a circular queue or to use a linked list for items and have attempted that in a seperate,
// incomplete file, unbounded_queue.c.

// If the queue is full, return false, otherwise add an item to its tail.
bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q) == true) {
        return false;
    }
    q->items[q->tail] = x;
    q->tail++;
    if (q->tail == q->capacity) {
        q->tail = 0;
    }
    q->size++;
    return true;
}

// If the queue is empty, return false, otherwise pop an item from its head.
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q) == true) {
        return false;
    }
    *x = q->items[q->head];
    q->head++;
    if (q->head == q->capacity) {
        q->head = 0;
    }
    q->size--;
    return true;
}

void queue_print(Queue *q) {
    // Makes sure to print the queue in order, potentially having to navigate back to index 0 during the process.
    for (uint32_t i = 0; i < queue_size(q); i++) {
        if (q->head + i >= q->capacity) {
            printf("%ld \n", q->items[(q->head + i) % q->capacity]);
        } else {
            printf("%ld \n", q->items[q->head + i]);
        }
    }
    return;
}
