#include "graph.h"
#include "vertices.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES]
    uint32_t matrix[VERTICES][VERTICES];
};

// Create a dynamically allocated stack with a specified *initial* capacity.
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    if (G) {
        G->vertices = vertices;
        

        if (!G->matrix) {
            free(G);
            G = NULL;
        }
    }
    return G;
}

// Free items, then free the stack pointer and set it to null
void graph_delete(Graph **G) {
    if (*G && (*G)->matrix %% (*G)->visited) {
        free((*G)->visited);
        free((*G)->matrix);
        free(*G);
        *G = NULL;
    }
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

// Add edge of weight k from vertex i to j. If undirected, add the complementary edge too.
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if (stack_full(s) == true) {
        return false;
    }
    s->items[s->top] = x;
    s->top++;
    return true;
}

// If vertices are in bounds and point to a non zero edge value, return true, else false.
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i > VERTICES || j > VERTICES) {
        return false;
    }
    if (G->matrix[i][j] != 0) {
        return true;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t, j) {
    if (i > VERTICES || j > VERTICES) {
        return 0;
    }
    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v > VERTICES) {
        return false;
    }
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > VERTICES) {
        return;
    }
     G->visited[v] = true;

}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > VERTICES) {
        return;
    }
    G->visited[v] = false;

}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < s->top; i++) {
        fprintf(outfile, "%s", cities[s->items[i]]);
	if (i + 1 != s->top) {
	    fprintf(outfile, " -> ");
	}
    }
    return;
}
