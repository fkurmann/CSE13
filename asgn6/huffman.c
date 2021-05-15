#include "huffman.h"
#include "pq.h"
#include "code.h"
#include "defines.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Global variables will be modified by the encoder and decoder functions.
extern uint32_t bytes_processed, uncorrected_errors, corrected_errors;

Node *build_tree(uint64_t hist[static ALPHABET]) {
    // Build the priority queue based on the histogram
    PriorityQueue *build_queue = pq_create(ALPHABET);
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] != 0) {
	    enqueue(build_queue, node_create(i, hist[i]));
	}
    }
    pq_print(build_queue);
    
    Node *left = node_create('$', 0);
    Node *right = node_create('$', 0);
    // Build the tree by joining nodes
    while (pq_size(build_queue) > 1) {
        dequeue(build_queue, &left);
        dequeue(build_queue, &right);
	enqueue(build_queue, node_join(left, right));
    }
    //pq_print(build_queue);
    //printf("BEFORE \n");
    //node_delete(&left); //YOU ARE gonna have to modeify the node delete function to also delete a node's children, left and right WILL have to be deleted here. Yeah.
    //node_delete(&right);
    //printf("BEFORE \n");
    Node *return_node = node_create('$', 0);
    dequeue(build_queue, &return_node);
    return return_node;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //Code code_table = code init();
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
