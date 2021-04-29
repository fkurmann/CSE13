#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: The stack constructor, destructor, and structure defenition are those given by Professor Long in the
// assignment 3 handout. The empty, full, size, push, pop functions are inspired by Professor Long's code from the
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


// If the stack is full, return false, otherwise simply push an item to the top of the stack.
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s) == true) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}

// If the stack is empty, it cannot pop, otherwise pop the top item setting the x pointer equal to that item.
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    return true;
}

// If the stack is empty, return false, otherwise send to x the value on top of the stack (top - 1)
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s) == true) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

// Copy the items and the value of the top to the destination stack
void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t i = 0; i < stack_size(src); i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = stack_size(src);	
    return;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
	if (i + 1 != s->top) {
	    fprintf(outfile, " -> ");
	}
    }
    fprintf(outfile, "\n");
    return; //////////////////////////////////////////CHECK IF THIS LINE IS ESSENTIAL/HARMFUL
}


// Temporary main function:
/*
int main(void) {
    uint32_t return_integer = 54;
    Stack *test = stack_create(VERTICES);

    stack_push(test, 49);
    stack_push(test, 29);
    stack_push(test, 32);
    printf("%u \n", stack_size(test));
    
    stack_peek(test, &return_integer);
    printf("%u \n", return_integer);       //Should print 32


    Stack *duplicate = stack_create(VERTICES);
    stack_copy(duplicate, test);
    printf("%u \n", stack_size(duplicate));
    
    stack_pop(duplicate, &return_integer);
    printf("%u \n", return_integer);       //Should print 32
    stack_peek(duplicate, &return_integer);
    printf("%u \n", return_integer);       //Should print 29


    stack_delete(&test);
    assert (test == NULL);
    stack_delete(&duplicate);
    assert (duplicate == NULL);

    return 0;
}*/
