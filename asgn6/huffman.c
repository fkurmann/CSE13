#include "huffman.h"
#include "pq.h"
#include "code.h"
#include "defines.h"
#include "node.h"
#include "stack.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables will be modified by the encoder and decoder functions.
extern uint32_t bytes_processed, uncorrected_errors, corrected_errors;
extern Code c;

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Build the priority queue based on the histogram
    PriorityQueue *build_queue = pq_create(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
	    enqueue(build_queue, node_create(i, hist[i]));
	}
    }
    
    Node *left_holder = node_create('#', 0);
    Node *right_holder = node_create('#', 0);
    // Build the tree by joining nodes
    while (pq_size(build_queue) > 1) {
        // Dequeue 2 nodes, the first will be left, the second right
        dequeue(build_queue, &left_holder);
        dequeue(build_queue, &right_holder);
	
        // Make a replica of both dequeued nodes, this is essential since you are writing over the priority queue
	Node *left = node_create(left_holder->symbol, left_holder->frequency);
	if (left_holder->left != NULL) {	
	    left->left = left_holder->left;
	}
	if (left_holder->right != NULL) {	
	    left->right = left_holder->right;
	}
	
	Node *right = node_create(right_holder->symbol, right_holder->frequency);
	if (right_holder->left != NULL) {	
	    right->left = right_holder->left;
	}
	if (right_holder->right != NULL) {	
	    right->right = right_holder->right;
	}

	// Join and euqueu the left and right (replica) nodes
	enqueue(build_queue, node_join(left, right));
	
    }
    //node_print(left_holder);
    //node_delete(&left_holder);

    // Return the root node
    Node *return_node = node_create('#', 0);
    dequeue(build_queue, &return_node);
    
    //pq_delete(&build_queue);
    return return_node;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    uint8_t popping_bit = 0;
    
    // If a node is NOT a root or interior node, push completed code
    if (root->symbol != '$'|| root->left == NULL || root->right == NULL) {
	table[root->symbol] = c;
	return;
    }

    // If the node is a root or interior node, post order traversal
    else {
        code_push_bit(&c, 0);
	build_codes(root->left, table);
	code_pop_bit(&c, &popping_bit);
	code_push_bit(&c, 1);
	build_codes(root->right, table);
	code_pop_bit(&c, &popping_bit);
    }
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree_dump[static nbytes]) {
    Stack *tree_rebuilder = stack_create((uint32_t) nbytes);
    for (uint16_t i = 0; i < nbytes; i++) {
        if (tree_dump[i] == 'L') {
	    if (i == 0) {
	        stack_push(tree_rebuilder, node_create(tree_dump[i + 1], 0));
	    }
	    else if (i == 1) {
	        continue;
	    }
            else {
	        if (tree_dump[i - 1] != 'L') {	
	            stack_push(tree_rebuilder, node_create(tree_dump[i + 1], 0));
		}
	        if (tree_dump[i - 1] == 'L') {
		    //printf("weird stuff is happening with L\n");	
	            if (tree_dump[i - 2] == 'L') { 	
	                stack_push(tree_rebuilder, node_create(tree_dump[i + 1], 0));
		    }
		}
	     }
        }
        
	if (tree_dump[i] == 'I') {
	    if (tree_dump[i - 1] == 'L' && tree_dump[i - 2] != 'L') {
		 //printf("weird stuff is happening with I\n");	
	         continue;
	    }		 
	    
	    Node *right_holder = node_create('#', 0);
	    Node *left_holder = node_create('#', 0);

	    //printf("%u \n", stack_pop(tree_rebuilder, &right_holder));
	    //printf("%u \n", stack_pop(tree_rebuilder, &left_holder));
	    stack_pop(tree_rebuilder, &right_holder);
	    stack_pop(tree_rebuilder, &left_holder);
            
	    // Make a replica of both dequeued nodes, this is essential since you are writing over the stack
	    Node *right = node_create(right_holder->symbol, 0);
	    if (right_holder->left != NULL) {	
	        right->left = right_holder->left;
	    }
	    if (right_holder->right != NULL) {	
	        right->right = right_holder->right;
	    }
	    
	    Node *left = node_create(left_holder->symbol, 0);
	    if (left_holder->left != NULL) {	
	        left->left = left_holder->left;
	    }
	    if (left_holder->right != NULL) {	
	        left->right = left_holder->right;
	    }
	    
	    stack_push(tree_rebuilder, node_join(left, right));
	}
    }
    if (stack_size(tree_rebuilder) != 1) {
        printf("An error has occured in the tree rebuilding\n");
	printf("Stack size after popping: %u \n", stack_size(tree_rebuilder));
	stack_print(tree_rebuilder);
    }
    Node *return_node = node_create('#', 0);
    stack_pop(tree_rebuilder, &return_node);
    return return_node;
}

void delete_tree(Node **root) {
    if ((*root)->left != NULL) {
        delete_tree(&(*root)->left);
    }
    if ((*root)->right != NULL) {
        delete_tree(&(*root)->right);
    }
    node_delete(&(*root));
}

