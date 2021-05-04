#include "bv.h"
#include "bm.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
};

// Create a bit vector of specified length.
BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitVector *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = bv_create(rows*cols);
        /*
        if (!s->items) {
            free(s);
            s = NULL;
        }
	*/
    }
    return m;
}

// Free items, then free the bit vector pointer and set it to null
void bv_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        free((*m)->vector);
        free(*m);
        *m = NULL;
	// CHECK IF YOU HAVE TO FREE THE BIT VECTOR OR RATHER, DELETE IT.
    }
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return;
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    return;
}

uint8_t bm_to_data(BitMatrix *m) {
    return;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    return;
}

void bv_print(BitVector *v) {
    return;
}
