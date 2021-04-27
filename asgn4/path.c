#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    uint32_t length;
    Stack *vertices;
};


//CHECK THIS CONSTRUCTOR FOR MEMORY LEAKS^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// Create a dynamically allocated stack with a specified *initial* capacity.
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    Stack *vertices = stack_create(VERTICES); 
    if (p && vertices) {
        p->length = 0;
        p->vertices = vertices

	// If vertices allocation didn't work properly, free the vertices stack and the path ADT.
        if (!vertices->items) {
            free(vertices);
            vertices = NULL;
	    free(p);
	    p = NULL;
        }
    }
    return p;
}

// Free items, then free the stack pointer and set it to null
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);               //////// CHECK IF YOU ALSO NEED TO FREE THE VERTICES STACK SEPERATLY
        free(*p);
        *p = NULL;
    }
    return;
}

//
bool path_push_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_full(s) == true) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}

// If the stack is empty, it cannot pop, otherwise pop the top item setting the x pointer equal to that item.
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(s) == true) {
        return false;
    }
    s->top--;
    *x = s->items[s->top];
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

// Copy the stack vertices using the stack copy method, then also copy the length to the destination length.
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    stack_print(p->vertices, *outfile, cities);                 ////////////check if cities [] array braces, are needed
    return; 
}
