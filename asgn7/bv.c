#include "bv.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Create a bit vector of specified length.
BitVector *bv_create(uint32_t length) {
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    if (v) {
        v->length = length;
        v->vector = (uint8_t *) calloc((length / 8) + ((length % 8) > 0), sizeof(uint8_t));

        if (!v->vector) {
            free(v);
            v = NULL;
        }
    }
    return v;
}

// Free items, then free the bit vector pointer and set it to null
void bv_delete(BitVector **v) {
    if (*v && (*v)->vector) {
        free((*v)->vector);
        free(*v);
        *v = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

// Set a bit by finding the byte it belongs to then updating that byte accordingly based on 2 to the power of [position]
void bv_set_bit(BitVector *v, uint32_t i) {
    if (i >= v->length) {
        return;
    }
    uint32_t byte = (i / 8);
    uint32_t bit_in_byte = i % 8;
    v->vector[byte] += pow(2, bit_in_byte);
    return;
}

// Get a bit by shifting the correct byte in the vector until the bit in question is in the one's place. Check if number is odd/even.
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    if (i >= v->length) {
        return 2;
    }
    uint32_t byte = (i / 8);
    uint32_t bit_in_byte = i % 8;
    uint8_t vector_byte = v->vector[byte];
    vector_byte = vector_byte >> bit_in_byte;
    if (vector_byte % 2 != 0) {
        return 1;
    }
    return 0;
}

// Clear a bit by reversing the set bit process, subtracting 2 to the power of [position]
void bv_clr_bit(BitVector *v, uint32_t i) {
    if (i >= v->length) {
        return;
    }
    uint32_t byte = (i / 8);
    uint32_t bit_in_byte = i % 8;
    v->vector[byte] -= pow(2, bit_in_byte);
    return;
}

void bv_print(BitVector *v) {
    printf("(");

    for (uint32_t i = 0; i < v->length; i++) {
        printf(" %u, ", bv_get_bit(v, i));
    }

    printf(") \n");
    return;
}
