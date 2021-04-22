#include "queue.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
};


Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = q->tail = 0;
	q->capacity = capacity;
	q->items = (int64_t *) calloc (capacity, sizeof(int64_t));
	if (!q->items) {
	    free(q);
	    q = NULL;
	}
    }
    return q;
}

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
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q) == true) {
        return false;
    }
    *x = q->items[q->head];
    // q->items[q->head] = NULL;
    q->head++;
    if (q->head == q->capacity) {
	q->head = 0;
    }
    q->size--;
    return true;
}
void queue_print(Queue *q) {
    
    for (uint32_t i = 0; i < queue_size(q); i++) {
        if (q->head + i >= q->capacity) {
	    printf("%ld \n", q->items[(q->head + i)%q->capacity]);
	}
	else {
	    printf("%ld \n", q->items[q->head + i]);
	}
    }
    return;
}

/*
int main(void) {
    Queue *test_queue = queue_create(10);
    int64_t tester = 46;
    printf("%ld \n", tester);
    printf("queue empty intially %d \n", queue_empty(test_queue));

    for (int64_t i = 0; i < 9; i++) {
	    enqueue(test_queue, i);
    }
    printf("queue size: %d \n", queue_size(test_queue));
    queue_print(test_queue);

    for (int64_t i = 0; i < 8; i++) {
	    dequeue(test_queue, &tester);
    }
    for (int64_t i = 0; i < 5; i++) {
	    enqueue(test_queue, i);
    }
    printf("queue size: %d \n", queue_size(test_queue));
    printf("queue empty %d \n", queue_empty(test_queue));
    queue_print(test_queue);

    queue_delete(&test_queue);
    assert(test_queue == NULL);
}*/
