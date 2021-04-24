#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: The stack constructor, destructor, and structure defenition are those given by Professor Long in the
// assignment handout. The empty, full, size, push, pop functions are inspired by Professor Long's code from the
// stacks/queues lecture.

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

// Create a dynamically allocated stack with a specified *initial* capacity.
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));

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

// NOTE: Based on the assignment description I was not sure whether to simply make a stack that returned false or
// grew based on demand. Since this reallocation method was demonstrated in lecture and it seems more interesting
// and powerful, I decided to do it this way.

// If the stack is full, expand it, otherwise simply push an item to the top of the stack.
bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s) == true) {
        s->capacity *= 2;
        // Reallocate the items array to a place where there is room for it to double in size.
        s->items = (int64_t *) realloc(s->items, s->capacity * sizeof(int64_t));
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}

// If the stack is empty, it cannot pop, otherwise pop the top item setting the x pointer equal to that item.
bool stack_pop(Stack *s, int64_t *x) {
    if (stack_empty(s) == true) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    return true;
}

void stack_print(Stack *s) {
    for (uint32_t i = 0; i < stack_size(s); i++) {
        printf("%ld \n", s->items[i]);
    }
    return;
}
