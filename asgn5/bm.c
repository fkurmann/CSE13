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
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
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
void bm_delete(BitMatrix **m) {
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

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    if (length > 8) {
        return NULL;
    }
    BitMatrix *bm = bm_create(1, length);
    for (uint32_t i = 0; i < length; i++) {
        if (byte % 2 == 1) {
	    bm_set_bit(bm, 0, i);
        }
	byte = byte >> 1;
    }
    return bm;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t first_byte = 0;
    for (uint32_t i = 0; i < 8 && i < bm_cols(m); i++) {
        first_byte += (pow(2, i) * bv_get_bit(m->vector, i));
    }
    return first_byte;
}

BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    if (bm_cols(A) != bm_rows(B)) {
        return NULL;
    }
    BitMatrix *C = bm_create(bm_rows(A), bm_cols(B));
    for (uint32_t i = 0; i < bm_cols(B); i++) {
        for (uint32_t j = 0; j < bm_rows(A); j++) {
	    uint32_t sum = 0;
            for (uint32_t k = 0; k < bm_cols(A); k++) {
		sum += bm_get_bit(A, j, k) * bm_get_bit(B, k, i);
	    }
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
/*
int main(void) {
    BitMatrix *tester = bm_create(1, 2);
    BitMatrix *tester2 = bm_create(2, 2);

    bm_set_bit(tester, 0, 0);
    bm_set_bit(tester2, 0, 0);
    bm_set_bit(tester2, 0, 1);
    
    bm_print(tester);
    bm_print(tester2);
    bm_print(bm_multiply(tester, tester2));

    bm_delete(&tester);
    bm_delete(&tester2);

    assert(tester == NULL);
    assert(tester2 == NULL);

    return 0;
}*/
