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
/*
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    return;
}*/

uint8_t bm_to_data(BitMatrix *m) {
    return 0;
}
/*
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    return;
}*/

void bm_print(BitMatrix *m) {
    bv_print(m->vector);
    return;
}

int main(void) {
    BitMatrix *tester = bm_create(4, 8);
    BitMatrix *tester2 = bm_create(9, 11);

    bm_set_bit(tester, 3, 5);
    bm_set_bit(tester, 0, 0);
    bm_set_bit(tester, 2, 1);
    
    bm_set_bit(tester2, 3, 5);
    printf("%u \n", bm_get_bit(tester2, 3, 5));
    bm_clr_bit(tester2, 3, 5);
    printf("%u \n", bm_get_bit(tester2, 3, 5));
    
    printf("%u \n", bm_get_bit(tester, 0, 0));
    printf("%u \n", bm_get_bit(tester, 2, 1));
    printf("%u \n", bm_get_bit(tester, 4, 4));

    bm_print(tester);
    
    bm_delete(&tester);
    bm_delete(&tester2);

    assert(tester == NULL);
    assert(tester2 == NULL);

    return 0;
}
