#include "node.h"

#include <string.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

// Create a node with the specified symbol and frequency
Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n) {
        // Set node's pointer to oldspeak  	
        n->oldspeak = (char *) malloc(strlen(oldspeak) + 1);
	for (uint64_t i = 0; i <= strlen(oldspeak); i++) {
	    n->oldspeak[i] = oldspeak[i];
	}
        
	// If a newspeak is given, set the node's pointer to newspeak
	if (newspeak == NULL) {
	    n->newspeak = NULL;
	} else {
	    n->newspeak = (char *) malloc(strlen(newspeak) + 1);
	    for (uint64_t i = 0; i <= strlen(newspeak); i++) {
	        n->newspeak[i] = newspeak[i];
	    }
	}

	n->next= NULL;
        n->prev = NULL;
    }
    return n;
}

// Free items, then free the stack pointer and set it to null
void node_delete(Node **n) {
    if (*n) {
        // If nodes have children, free those first
        free((*n)->oldspeak);
        if ((*n)->newspeak) {
            free((*n)->newspeak);
	}
        free(*n);
        *n = NULL;
    }
    return;
}

// Print the node, either just the oldspeak, or its applicible newspeak as well
void node_print(Node *n) {
    if (n->newspeak == NULL) {
        printf("%s \n", n->oldspeak);
    } else {
        printf("%s -> %s \n", n->oldspeak, n->newspeak);
    }
    
    // More in depth printing, for debugging only
    /*
    // Show previous and next pointers if applicable
    if (n->next) {
        printf("Next Node: %s \n", (n->next)->oldspeak);
    }
    if (n->prev) {
        printf("Previous Node: %s \n", (n->prev)->oldspeak);
    }*/
    
    return;
}
