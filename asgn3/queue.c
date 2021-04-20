#include "queue.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    return q-> head == 0;
}
bool queue_full(Queue *q) {
    return q->head == q->capacity;
}
uint32_t queue_size(Queue *q) {

}
bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q) == true) {
        return false;
    }
    
}
bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q) == true) {
        return false;
}
void queue_print(Queue *q) {

}

int main(void) {
    Queue *q = queue_create(10);
    queue_delete(&q);
    assert(q == NULL);
}
