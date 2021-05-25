#include "ll.h"

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
    LinkedList *l = (LinkedList *) malloc(sizeof(LinkedList));
    ll->mtf = mtf;
    ll->head = node_create("Head", NULL);
    ll->tail = node_create("Tail", NULL);
    ll->length = 0;
    return;
}

ll_delete(LinkedList **ll) {
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
    return;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    return;
}

void ll_print(LinkedList *ll) {
    return;
}
