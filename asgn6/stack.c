#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

// Create a dynamically allocated stack with a specified *initial* capacity.
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));

        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// Free items, then free the stack pointer and set it to null
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    return s->top == 0;
}

bool stack_full(Stack *s) {
    return s->top == s->capacity;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

// If the stack is full, return false, otherwise simply push an item to the top of the stack.
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s) == true) {
        return false;
    }
    s->items[s->top] = n;
    s->top++;
    return true;
}

// If the stack is empty, it cannot pop, otherwise pop the top item setting the x pointer equal to that item.
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s) == true) {
        return false;
    }
    s->top--;
    *n = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < stack_size(s); i++) {
        node_print(s->items[i]);
    }
    return;
}
