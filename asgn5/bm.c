#include "bm.h"

#include "bv.h"

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
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    BitVector *vector = bv_create(rows * cols);
    if (m) {
        m->rows = rows;
        m->cols = cols;
        m->vector = vector;
    }
    return m;
}

// Free items, then free the bit vector pointer and set it to null
void bm_delete(BitMatrix **m) {
    if (*m && (*m)->vector) {
        bv_delete(&(*m)->vector);
        free((*m)->vector);
        free(*m);
        *m = NULL;
    }
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

// Set, clear, and get bits by calling the bitVector functions based on the position of the desired bit in the matrix's vector.
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    if (r >= m->rows || c >= m->cols) {
        return;
    }
    uint32_t vector_position = m->cols * r + c;
    bv_set_bit(m->vector, vector_position);
    return;
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    if (r >= m->rows || c >= m->cols) {
        return;
    }
    uint32_t vector_position = m->cols * r + c;
    bv_clr_bit(m->vector, vector_position);
    return;
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    if (r >= m->rows || c >= m->cols) {
        return 2;
    }
    uint32_t vector_position = m->cols * r + c;
    return (bv_get_bit(m->vector, vector_position));
}

// Create a new bit matrix based on the given byte.
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    if (length > 8) {
        return NULL;
    }
    BitMatrix *bm = bm_create(1, length);
    // Using an iterative set method, set all bits in the matrix to match the bits from the input byte.
    for (uint32_t i = 0; i < length; i++) {
        if (byte % 2 == 1) {
            bm_set_bit(bm, 0, i);
        }
        byte = byte >> 1;
    }
    return bm;
}

// Using an iterative process, set the output byte to exactly match the first byte of the input matrix, bit by bit.
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t first_byte = 0;
    for (uint32_t i = 0; i < 8 && i < bm_cols(m); i++) {
        first_byte += (pow(2, i) * bv_get_bit(m->vector, i));
    }
    return first_byte;
}

// Matrix multiplication on two bit matrices
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    // Check if matices are of valid dimensions to be multiplied
    if (bm_cols(A) != bm_rows(B)) {
        return NULL;
    }
    BitMatrix *C = bm_create(bm_rows(A), bm_cols(B));

    // Iterate over the columns of the left matrix and the rows of the right, adding up products and inserting them into the output matrix.
    for (uint32_t i = 0; i < bm_cols(B); i++) {
        for (uint32_t j = 0; j < bm_rows(A); j++) {
            uint32_t sum = 0;
            for (uint32_t k = 0; k < bm_cols(A); k++) {
                sum += (bm_get_bit(A, j, k) * bm_get_bit(B, k, i));
            }
            // Apply the mod 2 part of multiplication so that bit values are
            if (sum % 2 == 1) {
                bm_set_bit(C, j, i);
            }
        }
    }
    return C;
}

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
    return;
}
