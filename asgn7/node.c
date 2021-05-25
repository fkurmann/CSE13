#include "node.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Create a node with the specified symbol and frequency
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        n->*oldspeak = oldspeak;
        n->*newspeak = newspeak;
        n->*next= NULL;
        n->*prev = NULL;
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

// Print the node, either just the oldspeak, or it applicible newspeak as well
void node_print(Node *n) {
    if (n->left != NULL) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    }
    if (n->right != NULL) {
        printf("%s\n", n->oldspeak);
    }
    return;
}
