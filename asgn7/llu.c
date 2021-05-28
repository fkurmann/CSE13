#include "llu.h"
#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables if needed


struct LinkedListUntracked {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedListUntracked *llu_create(bool mtf) {
    LinkedListUntracked *llu = (LinkedListUntracked *) malloc(sizeof(LinkedListUntracked));
    llu->mtf = mtf;
    // Initialize the sentinel nodes
    llu->head = node_create("Head", NULL);
    llu->tail = node_create("Tail", NULL);
    (llu->head)->next = llu->tail;
    (llu->tail)->prev = llu->head;
    llu->length = 0;
    return llu;
}

void llu_delete(LinkedListUntracked **llu) {
    if (*llu) {
        for (Node *current_node = (*llu)->head; current_node != NULL; current_node = current_node->next) {
	    // Delete the node before current, if it isn't null
	    if (current_node->prev != NULL) {
	        node_delete(&current_node->prev);
	    }
	    // Finally, if you are on the last node, delete that node itself in addition to it's previous, then break the loop
	    if (current_node->next == NULL) {
                node_delete(&current_node);
		break;
	    }
	}
	// Free and set ll to null
	free(*llu);
	*llu = NULL;
    }
    return;
}

uint32_t llu_length(LinkedListUntracked *llu) {
    return llu->length;
}

Node *llu_lookup(LinkedListUntracked *llu, char *oldspeak) {
    for (Node *current_node = llu->head; current_node != NULL; current_node = current_node->next) {
        if (strcmp(current_node->oldspeak, oldspeak) == 0) {
	    // Move to front if the setting is engaged
	    if (llu->mtf == true) {
                // Remove the node from it's current position
		(current_node->prev)->next = (current_node->next);
	        (current_node->next)->prev = (current_node->prev);
		// Clear the current node's pointers
		current_node->prev = NULL;
		current_node->next = NULL;
		// Insert this node at the front by calling regular insertion
	        llu_insert(llu, current_node->oldspeak, current_node->newspeak);
		// Return the node that is now at the front of your linked list, also delete current_node since you're not returning it
		node_delete(&current_node);
		return ((llu->head)->next);
	    } else{
	        return current_node;
	    }
	}
    } 
    return NULL;
}

void llu_insert(LinkedListUntracked *llu, char *oldspeak, char *newspeak) {
    // Don't create a duplicate node
    if (llu_lookup(llu, oldspeak) != NULL) {
        return;
    }

    Node *new_node = node_create(oldspeak, newspeak);
    new_node->prev = llu->head;
    new_node->next = (llu->head)->next;

    ((llu->head)->next)->prev = new_node;
    (llu->head)->next = new_node;
    
    llu->length++;
    return;
}

void llu_print(LinkedListUntracked *llu) {
    Node *current_node;
    for (Node *current_node = llu->head; current_node != NULL; current_node = current_node->next) {
        if (strcmp(current_node->oldspeak, "Head") == 0 && strcmp(current_node->oldspeak, "Tail") == 0) {
	    node_print(current_node);
	}
    }
    node_delete(&current_node);

    return;
}
