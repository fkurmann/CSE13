#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
	s->capacity = capacity;
	s->items = (int64_t *) calloc (capacity, sizeof(int64_t));
	
	if (!s->items) {
	    free(s);
	    s = NULL;
	}
    }
    return s;
}

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
bool stack_push(Stack *s, int64_t x) {
    if (stack_full(s) == true) {
        s->capacity *= 2;
	s->items = (int64_t *)realloc(s->items, s->capacity * sizeof(int64_t));
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}
bool stack_pop(Stack *s, int64_t *x) {
    // Check if it is possible to pop from the stack
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

/*
int main(void) {
    Stack *test_stack  = stack_create(10);
    int64_t tester_long = 54;
    printf("stack empty initially: %d \n", stack_empty(test_stack));
    stack_push(test_stack, 5);
    stack_push(test_stack, 4);
    printf("stack empty: %d \n", stack_empty(test_stack));
    stack_push(test_stack, 3);
    stack_push(test_stack, 2);
    stack_push(test_stack, 17);
    
    stack_pop(test_stack, &tester_long);
    stack_push(test_stack, 2);
    stack_push(test_stack, 2);
    stack_push(test_stack, 2);
    stack_push(test_stack, 2);
    stack_push(test_stack, 2);
    stack_push(test_stack, 2);
    stack_push(test_stack, 10);
    
    printf("stack size: %d \n", stack_size(test_stack));
    stack_print(test_stack);
    stack_print(test_stack);
    printf("\n");
    printf("%ld \n",tester_long);

    for (int64_t i = 0; i < 1000000; i++) {
	    stack_push(test_stack, i);
    }
    for (int64_t i = 0; i < 1000000; i++) {
	    stack_pop(test_stack, &tester_long);
    }
    printf("%ld\n",tester_long);


    stack_delete(&test_stack);
    assert(test_stack == NULL);
    printf("stack delete successful");
}*/
