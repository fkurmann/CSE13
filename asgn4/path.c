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

// Create a path which contains it's own stack of vertices and length variable.
Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    Stack *vertices = stack_create(100);
    if (p && vertices) {
        p->length = 0;
        p->vertices = vertices;
    }
    return p;
}

// Free the path's stack then free the path pointer and set it to null
void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        stack_delete(&(*p)->vertices);
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

// If the path's vertices stack is full, return false, else add the vertex to the vertices stack and adjust path length
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_full(p->vertices) == true) {
        return false;
    }
    uint32_t old_top;
    // Check if you are adding to a started stack or you have to start from the origin (0, 0)
    if (stack_empty(p->vertices) == true) {
        old_top = 0;
    } else {
        stack_peek(p->vertices, &old_top); // old_top holds the prior vertex's value
    }
    stack_push(p->vertices, v);
    p->length
        += graph_edge_weight(G, old_top, v); // Find the length from old_top to v in the map graph
    return true;
}

// If the path is empty it cannot pop, else pop the top vertex in the stack and adjust the path length
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices) == true) {
        return false;
    }
    uint32_t old_top, new_top;
    stack_peek(p->vertices, &old_top); // old_top holds the to be removed vertex's value
    stack_pop(p->vertices, v);
    if (stack_empty(p->vertices) == true) {
        p->length = 0;
    } else {
        stack_peek(p->vertices, &new_top); // new_top holds the new top vertex value
        p->length -= graph_edge_weight(G, new_top, old_top);
    }
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
    stack_print(p->vertices, outfile, cities);
    return;
}
