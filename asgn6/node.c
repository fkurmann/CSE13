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
    printf("back at the top");
    if (*n != NULL) {
	printf("deleting node\n");
        if ((*n)->left != NULL) {
	    printf("node has left child\n");
            node_print((*n)->left);
	    node_delete(&(*n)->left);
        }
        if (*n == NULL) {
	    return;
	}
        if ((*n)->right != NULL) {
	    printf("node has right child\n");
            node_print((*n)->right);
            node_delete(&(*n)->right);
        }
        if (*n == NULL) {
	    return;
	}
        
	free(*n);
	printf("deleting node 2\n");
        *n = NULL;
	printf("deleting node 3\n");
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
    //Node *right_tester = node_create('a', 7);

    Node *rightleft_tester = node_create('E', 3);
    Node *rightright_tester = node_create('B', 2);
    Node *right_tester = node_join(rightleft_tester, rightright_tester);
    
    Node *tester = node_join(left_tester, right_tester);
    
    node_print(tester);
    node_print(tester->right);

    //node_delete(&tester);
    node_delete(&left_tester);
    node_delete(&right_tester);

    return 0;
}*/
