#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Create a node with the specified symbol and frequency
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->symbol = symbol;
        n->frequency = frequency;
    }
    return n;
}

// Free items, then free the stack pointer and set it to null
void node_delete(Node **n) {
    if (*n) {
        //free((*n)->CHILDREN); // FREE CHILDREN NODES PERHAPS
        free(*n);
        *n = NULL;
    }
    return;
}

Node *node_join(Node *left, Node *right) {
    Node *n = node_create('$', left->frequency + right->frequency);
    n->left = left;
    n->right = right;
    return n;
}

void node_print(Node *n) {
    printf("Symbol: %u, frequency: %lu \n", n->symbol, n->frequency);
    if (n->left != NULL) {
        printf("Left child symbol: %u \n", n->left->symbol);
    }
    if (n->right != NULL) {
        printf("Right child symbol: %u \n", n->right->symbol);
    }
    return;
}

/*
// Temporary Main Method
int main(void) {
    //Node *tester = node_create('k', 43);
    Node *left_tester = node_create('A', 16);
    Node *right_tester = node_create('a', 7);

    node_print(node_join(left_tester, right_tester));

    //node_delete(&tester);
    node_delete(&left_tester);
    node_delete(&right_tester);

    return 0;
}*/
