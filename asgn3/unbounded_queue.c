#include "queue.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    Node *next;
    item data;
};

static Node *node_creation(item i) {
    Node *n = (int64_t *) malloc(sizeof(int64_t));
    if (n) {
        n->data = i;
        n->next = NULL;
    }
    return n;
}

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

Queue *queue_create(void) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = q->tail = NULL;
        return q;
    }

    void queue_delete(Queue * *q) { // Figure out how to free the nodes too
        if (*q) {
            free(*q);
            *q = NULL;
        }
        return;
    }

    bool queue_empty(Queue * q) {
        return q->head == q->tail;
    }
    bool queue_full(Queue * q) {
        return (q->head + 1) == ((q->tail) % (queue_size(q)));
    }
    uint32_t queue_size(Queue * q) {
        return q->head - q->tail;
    }
    bool enqueue(Queue * q, int64_t x) {
        if (queue_full(q) == true) {
            q->capacity *= 2;
            q->items = (int64_t *) realloc(q->items, q->capacity * sizeof(int64_t));
        }
        q->items[q->head] = x;
        q->head++;
        return true;
    }
    bool dequeue(Queue * q, int64_t * x) {
        if (queue_empty(q) == true) {
            return false;
        }
        *x = q->items[q->tail];
        q->tail++;
        return true;
    }
    void queue_print(Queue * q) {
        for (uint32_t i = 0; i < queue_size(q); i++) {
            printf("%ld \n", q->items[i]);
        }
        return;
    }

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
        printf("queue size: %d \n", queue_size(test_queue));
        printf("queue empty %d \n", queue_empty(test_queue));
        queue_print(test_queue);

        queue_delete(&test_queue);
        assert(test_queue == NULL);
    }
