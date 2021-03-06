#include "pq.h"

#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ASSUMING ITEMS ARE ENQUEUED AT THE TAIL AND DEQUEUED FRON THE HEAD.

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    Node *items;
};

// Create a dynamically allocated stack with a specified capacity.
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->head = pq->tail = 0;
        pq->capacity = capacity;
        pq->items = (Node *) calloc(capacity, sizeof(Node));
        if (!pq->items) {
            free(pq);
            pq = NULL;
        }
    }
    return pq;
}

// Free items, then free the queue pointer and set it to null
void pq_delete(PriorityQueue **pq) {
    if (*pq && (*pq)->items) {
        free((*pq)->items);
        free(*pq);
        *pq = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *pq) {
    return pq->head == pq->tail;
}

bool pq_full(PriorityQueue *pq) {
    return pq->size == pq->capacity;
}

uint32_t pq_size(PriorityQueue *pq) {
    return pq->size;
}

// If the queue is full, return false, otherwise add a node to its tail.
bool enqueue(PriorityQueue *pq, Node *n) {
    if (pq_full(pq) == true) {
        return false;
    }
    pq->size++;
    // While loop to determine insertion position for node to enqueue
    while (pq->tail < pq->head) {
        if ((pq->items[pq->tail]).frequency > n->frequency) {
            pq->tail++;
        } else {
            break;
        }
    }

    // Shift all nodes that are effected by the insertion towards the head, insert the node to enqueue
    uint32_t index = pq->head;
    pq->head++;
    while (index > pq->tail) {
        pq->items[index] = pq->items[index - 1];
        index--;
    }
    pq->items[pq->tail] = *n;

    //Return tail to zero and ajust size
    pq->tail = 0;
    return true;
}

// If the queue is empty, return false, otherwise pop a node from its head.
bool dequeue(PriorityQueue *pq, Node **n) {
    if (pq_empty(pq) == true) {
        return false;
    }
    // Pop item at head
    pq->head--;
    *n = &(pq->items[pq->head]);
    // Adjust size and return
    pq->size--;
    return true;
}

void pq_print(PriorityQueue *pq) {
    for (uint32_t i = 0; i < pq_size(pq); i++) {
        node_print(&pq->items[i]);
    }
    return;
}
