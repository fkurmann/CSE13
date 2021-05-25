#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Variables if needed


struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    return;
}

ll_delete(LinkedList **ll) {
    return;
}

uint32_t ll_length(LinkedList *ll) {
    return;
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
