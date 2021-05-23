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
        n->left = NULL;
        n->right = NULL;
    }
    return n;
}

// Free items, then free the stack pointer and set it to null
void node_delete(Node **n) {
    if (*n != NULL) {
        // If nodes have children, free those first via recusive calls
        if ((*n)->left != NULL) {
            node_delete(&(*n)->left);
        }
        if (*n == NULL) {
            return;
        }
        if ((*n)->right != NULL) {
            node_delete(&(*n)->right);
        }
        if (*n == NULL) {
            return;
        }

        free(*n);
        *n = NULL;
    }
    return;
}

// Create a new node with pointers to its left and right children
Node *node_join(Node *left, Node *right) {
    Node *n = node_create('$', left->frequency + right->frequency);
    n->left = left;
    n->right = right;
    return n;
}

// Print the node, if it has children, print those too
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
