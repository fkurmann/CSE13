#include "hamming.h"
#include "bm.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    return(bm_to_data(bm_multiply(bm_from_data(msg, 4), G)));
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg){
    BitMatrix *Decoded = bm_from_data(code, 4); // First 4 bits of the input are the decoded bits, before they have been error checked

    uint8_t error = bm_to_data(bm_multiply(code, Ht));  //the decoder spits out 4 bits, these are the error message, bm to data turns it into a uint.
    return;
}
