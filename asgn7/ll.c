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
    ll->head = node_create("Head", NULL);
    ll->tail = node_create("Tail", NULL);
    (ll->head)->next = ll->tail;
    (ll->tail)->prev = ll->head;
    ll->length = 0;
    return ll;
}

void ll_delete(LinkedList **ll) {
    if (*ll) {
        node_delete(&(*ll)->head);
        node_delete(&(*ll)->tail);
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
	    return current_node;
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
