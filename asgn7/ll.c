#include "ll.h"
#include "node.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables if needed


struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    ll->mtf = mtf;
    // Initialize the sentinel nodes
    ll->head = node_create("Head", NULL);
    ll->tail = node_create("Tail", NULL);
    (ll->head)->next = ll->tail;
    (ll->tail)->prev = ll->head;
    ll->length = 0;
    return ll;
}

void ll_delete(LinkedList **ll) {
    if (*ll) {
        for (Node *current_node = (*ll)->head; current_node != NULL; current_node = current_node->next) {
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
	free(*ll);
	*ll = NULL;
    }
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    for (Node *current_node = ll->head; current_node != NULL; current_node = current_node->next) {
        if (strcmp(current_node->oldspeak, oldspeak) == 0) {
	    // Move to front if the setting is engaged
	    if (ll->mtf == true) {
                // Remove the node from it's current position
		(current_node->prev)->next = (current_node->next);
	        (current_node->next)->prev = (current_node->prev);
		// Clear the current node's pointers
		current_node->prev = NULL;
		current_node->next = NULL;
		// Insert this node at the front by calling regular insertion
	        ll_insert(ll, current_node->oldspeak, current_node->newspeak);
		// Return the node that is now at the front of your linked list, also delete current_node since you're not returning it
		node_delete(&current_node);
		return ((ll->head)->next);
	    } else{
	        return current_node;
	    }
	}
    } 
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // Don't create a duplicate node
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }

    Node *new_node = node_create(oldspeak, newspeak);
    new_node->prev = ll->head;
    new_node->next = (ll->head)->next;

    ((ll->head)->next)->prev = new_node;
    (ll->head)->next = new_node;
    
    ll->length++;
    return;
}

void ll_print(LinkedList *ll) {
    Node *current_node;
    for (Node *current_node = ll->head; current_node != NULL; current_node = current_node->next) {
        if (strcmp(current_node->oldspeak, "Head") == 0 && strcmp(current_node->oldspeak, "Tail") == 0) {
	    node_print(current_node);
	}
    }
    node_delete(&current_node);

    return;
}
