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
    return;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    return;
}

void delete_tree(Node **root) {
    return;
}


