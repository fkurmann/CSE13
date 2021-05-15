#include "huffman.h"
#include "pq.h"
#include "code.h"
#include "defines.h"
#include "node.h"

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
    //pq_print(build_queue);
    
    Node *left_holder = node_create('#', 0);
    Node *right_holder = node_create('#', 0);
    // Build the tree by joining nodes
    while (pq_size(build_queue) > 1) {
        dequeue(build_queue, &left_holder);
        //printf("Left Node \n");
	//node_print(left);
        dequeue(build_queue, &right_holder);
        //printf("Right Node \n");
	//node_print(right);
        //printf("Joined Node left\n");
	
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

	Node *joined = node_join(left, right);

	//node_print(joined->left);
        //printf("Joined Node right before euqueueuing\n");
	//node_print(joined->right);
        //node_print((joined->right)->right);

	enqueue(build_queue, joined);
        //printf("Joined node Right After euqueuing\n");
	//node_print(joined->right);
        //node_print((joined->right)->right);
	
	//node_delete(&right);
	//node_delete(&left);
    }
    
    //node_delete(&left_holder); //YOU ARE gonna have to modeify the node delete function to also delete a node's children, left and right WILL have to be deleted here. Yeah.
    //node_delete(&right_holder);
	    
    
    Node *return_node = node_create('#', 0);
    dequeue(build_queue, &return_node);
    
    return return_node;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    /*
    printf("Root \n");
    node_print(root);
    printf("Left \n");
    node_print(root->left);
    printf("Right \n");
    node_print(root->right);
    */
    
    uint8_t popping_bit = 0;
    
    // If a node is NOT a root or interior node, push completed code
    if (root->symbol != '$') {
	printf("%u\n", code_size(&c));
	code_print(&c);
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

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Node *bitch_node = node_create('b', 16);
    return bitch_node;
}

void delete_tree(Node **root) {
    return;
}

//DONT FORGET ABOUT MEMORY LEEKS
