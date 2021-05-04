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
        v->vector= (uint8_t *) calloc((length/8) + ((length % 8) > 0) , sizeof(uint8_t));

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

void bv_set_bit(BitVector *v, uint32_t i) {
    if(i >= v->length) {
        return;
    }
    uint32_t byte = (i/8);
    uint32_t bit_in_byte = i % 8;
    v->vector[byte] += pow(2, bit_in_byte);
    return;
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    if(i >= v->length) {
        return 2;
    }
    uint32_t byte = (i/8);
    uint32_t bit_in_byte = i % 8;
    uint8_t vector_byte = v->vector[byte];
    vector_byte = vector_byte >> bit_in_byte;
    if (vector_byte % 2 != 0) {
        return 1;
    }
    return 0;
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    if(i >= v->length) {
        return;
    }
    uint32_t byte = (i/8);
    uint32_t bit_in_byte = i % 8;
    v->vector[byte] -= pow(2, bit_in_byte);
    return;
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    if(i >= v->length) {
        return;
    }
    uint32_t byte = (i/8);
    uint32_t bit_in_byte = i % 8;
    bit = bit * pow(2, bit_in_byte);
    v->vector[byte] = v->vector[byte] + bit;
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


// Temporary main function

/*
int main(void) {
    BitVector *tester = bv_create(25);


    printf("%u \n", bv_length(tester));
    bv_set_bit(tester, 13);
    bv_set_bit(tester, 1);
    bv_set_bit(tester, 3);
    bv_set_bit(tester, 8);
    bv_set_bit(tester, 22);
    printf("%u \n", bv_get_bit(tester, 0));
    printf("%u \n", bv_get_bit(tester, 25));
    printf("%u \n", bv_get_bit(tester, 15));
    printf("%u \n", bv_get_bit(tester, 22));
    bv_clr_bit(tester, 22);
    //printf("%u \n", bv_get_bit(tester, 22));
    
    bv_print(tester);
    bv_delete(&tester);
    assert(tester == NULL);

    return 0;
}*/
