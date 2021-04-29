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
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

// Create a dynamically allocated stack with a specified *initial* capacity.
Graph *graph_create(uint32_t vertices, bool undirected) {
    // Check that graph input meets specification
    if (vertices > VERTICES) {
        return NULL;
    }
    Graph *G = (Graph *) malloc(sizeof(Graph));
    if (G) {
        G->vertices = vertices;
	G->undirected = undirected;
    }
    return G;
}

// Free items, then free the stack pointer and set it to null
void graph_delete(Graph **G) {
    if (*G) {
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
    if (i > G->vertices || j > G->vertices) {
        return false;
    }

    G->matrix[i][j] = k;
    if (G->undirected == true) {
        G->matrix[j][i] = k;
    }

    return true;
}

// If vertices are in bounds and point to a non zero edge value, return true, else false.
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if (i > G->vertices || j > G->vertices) {
        return false;
    }
    if (G->matrix[i][j] != 0) {
        return true;
    }
    return false;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (i > G->vertices || j > G->vertices) {
        return 0;
    }
    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
        return false;
    }
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
        return;
    }
     G->visited[v] = true;

}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > G->vertices) {
        return;
    }
    G->visited[v] = false;

}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i++) {
	for (uint32_t j = 0; j < G->vertices; j++) {
            printf("%13" PRIu32, G->matrix[i][j]);
	}
	printf("\n");
	printf("\n");
    }
    return;
}

// Temporary main function:
/*
int main(void) {
    uint32_t return_integer = 54;
    printf("%u \n", return_integer);
    Graph *test_graph = graph_create(5, false);

    printf("%d \n", graph_visited(test_graph, 4)); //Should return 0
    graph_mark_visited(test_graph, 4);
    printf("%d \n", graph_visited(test_graph, 4)); //Should return 1
    graph_mark_unvisited(test_graph, 4);
    printf("%d \n", graph_visited(test_graph, 4)); //Should return 0

    printf("%u \n", graph_vertices(test_graph));
    graph_print(test_graph);

    printf("%d \n", graph_has_edge(test_graph, 4, 3)); //Should return 0
    graph_add_edge(test_graph, 4, 3, 18);
    printf("%d \n", graph_has_edge(test_graph, 4, 3)); //Should return 1
    printf("%d \n", graph_edge_weight(test_graph, 4, 3)); //Should return 18

    graph_add_edge(test_graph, 2, 1, 6);
    graph_add_edge(test_graph, 2, 6, 2);
    graph_add_edge(test_graph, 5, 2, 38);
    graph_print(test_graph);
    
    graph_delete(&test_graph);
    assert(test_graph == NULL);
}*/



